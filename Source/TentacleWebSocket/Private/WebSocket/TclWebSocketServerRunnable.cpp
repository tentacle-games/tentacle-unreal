// Copyright (c) 2023 Deadsun & Backside4Charter. All rights reserved.

#include "WebSocket/TclWebSocketServerRunnable.h"
#include <websocketpp/config/asio_no_tls_client.hpp>

DEFINE_LOG_CATEGORY(LogWebSocketServerRunnable);

FWebSocketServerRunnable::~FWebSocketServerRunnable()
{
	Destroy();
}

bool FWebSocketServerRunnable::Init()
{
	return true;
}

uint32 FWebSocketServerRunnable::Run()
{
	// Set logging settings
	Server.set_access_channels(websocketpp::log::alevel::all);
	Server.clear_access_channels(websocketpp::log::alevel::frame_payload);

	// Initialize Asio
	Server.init_asio();

	// Register callbacks.
	Server.set_open_handler([this](ConnectionHandle Handle) {
		HandleConnectionOpen(Handle);
	});

	Server.set_close_handler([this](ConnectionHandle Handle) {
		HandleConnectionClose(Handle);
	});

	Server.set_fail_handler([this](ConnectionHandle Handle) {
		HandleConnectionFail(Handle);
	});

	Server.set_message_handler([this](ConnectionHandle Handle, MsgPtr MsgPtr) {
		HandleMessage(Handle, MsgPtr);
	});

	// Start the server. This will block until the server is stopped.
	Server.listen(Port);
	Server.start_accept();
	Server.run();

	return 0;
}

void FWebSocketServerRunnable::Stop()
{
	Destroy();
}

void FWebSocketServerRunnable::Destroy()
{
	for (const auto& Connection : Connections)
		Server.close(Connection, websocketpp::close::status::going_away, "Server shutting down");

	Server.stop();
	Connections.clear();
}

void FWebSocketServerRunnable::HandleConnectionOpen(ConnectionHandle Handle)
{
	Connections.push_back(Handle.lock());
	UE_LOG(LogWebSocketServerRunnable, Display, TEXT("Connection opened (connections: %llu)"), Connections.size())
}

void FWebSocketServerRunnable::HandleConnectionClose(ConnectionHandle Handle)
{
	Connections.remove(Handle.lock());
	UE_LOG(LogWebSocketServerRunnable, Display, TEXT("Connection closed (connections: %llu)"), Connections.size())
}

void FWebSocketServerRunnable::HandleConnectionFail(ConnectionHandle Handle)
{
	Connections.remove(Handle.lock());
	UE_LOG(LogWebSocketServerRunnable, Display, TEXT("Connection failed (connections: %llu)"), Connections.size())
}

void FWebSocketServerRunnable::HandleMessage(ConnectionHandle Handle, MsgPtr MsgPtr)
{
	const auto Msg = FString(MsgPtr->get_payload().c_str());
	UE_LOG(LogWebSocketServerRunnable, Display, TEXT("Message received: %s"), *Msg)

	if (OnMsgReceived.IsBound())
		OnMsgReceived.Execute(Msg);
}

void FWebSocketServerRunnable::Broadcast(const FString& Msg)
{
	for (const auto& Connection : Connections)
		Server.send(Connection, TCHAR_TO_ANSI(*Msg), websocketpp::frame::opcode::text);
}
