// © 2025 Backside4Charter & Deadsun. All rights reserved.

#pragma once

// Have WebSocket++ use the bundled ASIO library instead of Boost.
#define ASIO_STANDALONE
#define ASIO_NO_EXCEPTIONS

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "websocketpp/roles/client_endpoint.hpp"

DECLARE_LOG_CATEGORY_EXTERN(LogWebSocketClientRunnable, Verbose, All);

class TENTACLEWEBSOCKET_API FWebSocketClientRunnable : public FRunnable
{
	using AsioSteadyTimer = websocketpp::lib::asio::steady_timer;
	using WSClient = websocketpp::client<websocketpp::config::asio>;
	using WSError = websocketpp::lib::error_code;
	using ConnectionHandle = websocketpp::connection_hdl;
	using MsgPtr = websocketpp::config::asio_client::message_type::ptr;

	DECLARE_DELEGATE_OneParam(FWebSocketRunnable_OnMsgReceivedDelegate, const FString)

	FString
	Uri;

	WSClient
	Client;

	ConnectionHandle
	ConnectionHdl;

	TUniquePtr<AsioSteadyTimer>
	AsioPingTimer;

public:
	FWebSocketRunnable_OnMsgReceivedDelegate
	OnMsgReceived;

	explicit
	FWebSocketClientRunnable(const FString& Uri)
	{
		this->Uri = Uri;
	}

	virtual ~FWebSocketClientRunnable() override {}

	virtual bool
	Init() override;

	virtual uint32
	Run() override;

	virtual void
	Stop() override;

	void
	SendPing();

	void
	SchedulePing();

	void
	HandleConnectionOpen(ConnectionHandle Handle);

	void
	HandleConnectionClose(ConnectionHandle Handle);

	void
	HandleConnectionFail(ConnectionHandle Handle);

	void
	HandlePong(ConnectionHandle Handle);

	void
	HandleMessage(ConnectionHandle Handle, MsgPtr MsgPtr);

	void
	Send(const FString& Msg);
};
