// Copyright (c) 2023 Deadsun & Backside4Charter. All rights reserved.

#pragma once

// Have WebSocket++ use the bundled ASIO library instead of Boost.
#define ASIO_STANDALONE
#define ASIO_NO_EXCEPTIONS

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "websocketpp/roles/server_endpoint.hpp"

DECLARE_LOG_CATEGORY_EXTERN(LogWebSocketServerRunnable, Verbose, All);
DECLARE_DELEGATE_OneParam(FWebSocketRunnable_OnMsgReceivedDelegate, const FString)

class TENTACLEWEBSOCKET_API FWebSocketServerRunnable : public FRunnable
{
	using WSServer = websocketpp::server<websocketpp::config::asio>;
	using ConnectionHandle = websocketpp::connection_hdl;
	using MsgPtr = websocketpp::config::asio_client::message_type::ptr;

	int32 Port;
	WSServer Server;
	std::list<std::shared_ptr<void>> Connections;

public:
	FWebSocketRunnable_OnMsgReceivedDelegate OnMsgReceived;

	explicit FWebSocketServerRunnable(int32 Port) : Port(Port) {}
	virtual ~FWebSocketServerRunnable() override;

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	void HandleConnectionOpen(ConnectionHandle Handle);
	void HandleConnectionClose(ConnectionHandle Handle);
	void HandleConnectionFail(ConnectionHandle Handle);
	void HandleMessage(ConnectionHandle Handle, MsgPtr MsgPtr);
	void Destroy();

	void Broadcast(const FString& Msg);
};
