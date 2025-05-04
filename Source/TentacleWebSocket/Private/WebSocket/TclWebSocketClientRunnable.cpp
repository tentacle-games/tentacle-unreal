// © 2025 Backside4Charter & Deadsun. All rights reserved.

#include "WebSocket/TclWebSocketClientRunnable.h"
#include <websocketpp/config/asio_no_tls_client.hpp>

DEFINE_LOG_CATEGORY(LogWebSocketClientRunnable);

bool
FWebSocketClientRunnable::Init()
{
	return true;
}

uint32
FWebSocketClientRunnable::Run()
{
	UE_LOG(LogWebSocketClientRunnable, Display, TEXT("Running in new thread"))

	// Set logging settings
	Client.set_access_channels(websocketpp::log::alevel::all);
	Client.clear_access_channels(websocketpp::log::alevel::frame_payload);

	// Initialize Asio
	Client.init_asio();

	// Register callbacks.
	Client.set_open_handler(
		[this](ConnectionHandle Handle)
		{
			HandleConnectionOpen(Handle);
		}
	);

	Client.set_close_handler(
		[this](ConnectionHandle Handle)
		{
			HandleConnectionClose(Handle);
		}
	);

	Client.set_fail_handler(
		[this](ConnectionHandle Handle)
		{
			HandleConnectionFail(Handle);
		}
	);

	Client.set_pong_handler(
		[this](ConnectionHandle Handle, std::string Msg)
		{
			HandlePong(Handle);
		}
	);

	Client.set_message_handler(
		[this](ConnectionHandle Handle, MsgPtr MsgPtr)
		{
			HandleMessage(Handle, MsgPtr);
		}
	);

	AsioPingTimer = MakeUnique<AsioSteadyTimer>(Client.get_io_service());
	SchedulePing();

	// Start the client.
	std::error_code ErrorCode;
	const auto Connection = Client.get_connection(TCHAR_TO_ANSI(*Uri), ErrorCode);
	Client.connect(Connection);

	Client.run();

	return 0;
}

void
FWebSocketClientRunnable::Stop()
{
	Client.stop();
}

void
FWebSocketClientRunnable::SendPing()
{
	WSError Error;
	Client.ping(ConnectionHdl, "heartbeat", Error);
	if (Error)
	{
		const auto ErrorMessage = FString::Printf(TEXT("PING error: %s"), *FString(Error.message().c_str()));
		UE_LOG(LogWebSocketClientRunnable, Display, TEXT("%s"), *ErrorMessage)
	}
}

void
FWebSocketClientRunnable::SchedulePing()
{
	AsioPingTimer->expires_after(std::chrono::seconds(30));
	AsioPingTimer->async_wait([this](const WSError& Error) {
		if (Error)
		{
			const auto ErrorMessage = FString::Printf(TEXT("PING timer error: %s"), *FString(Error.message().c_str()));
			UE_LOG(LogWebSocketClientRunnable, Display, TEXT("%s"), *ErrorMessage)
		}

		SendPing();
		SchedulePing();
	});
}

void
FWebSocketClientRunnable::HandleConnectionOpen(ConnectionHandle Handle)
{
	UE_LOG(LogWebSocketClientRunnable, Display, TEXT("Connection opened"))
	ConnectionHdl = Handle.lock();
}

void
FWebSocketClientRunnable::HandleConnectionClose(ConnectionHandle Handle)
{
	UE_LOG(LogWebSocketClientRunnable, Display, TEXT("Connection closed"))
}

void
FWebSocketClientRunnable::HandleConnectionFail(ConnectionHandle Handle)
{
	UE_LOG(LogWebSocketClientRunnable, Display, TEXT("Connection failed"))
}

void
FWebSocketClientRunnable::HandlePong(ConnectionHandle Handle)
{
	// Do nothing.
}

void
FWebSocketClientRunnable::HandleMessage(ConnectionHandle Handle, MsgPtr MsgPtr)
{
	const auto Msg = FString(MsgPtr->get_payload().c_str());
	UE_LOG(LogWebSocketClientRunnable, Display, TEXT("Message received: %s"), *Msg)

	if (OnMsgReceived.IsBound())
		OnMsgReceived.Execute(Msg);
}

void
FWebSocketClientRunnable::Send(const FString& Msg)
{
	if (!ConnectionHdl.expired())
		Client.send(ConnectionHdl, TCHAR_TO_ANSI(*Msg), websocketpp::frame::opcode::text);
}
