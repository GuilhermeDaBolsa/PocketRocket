#pragma once
#include "Crow_all.h"
#include "ConnectionStatus.cpp"

class UserConnection {
public:
	
	ConnectionStatus status;
	unsigned int missedPkgsInARow;
	unsigned int avgLatency;
	crow::websocket::connection* connection;

	UserConnection()
		: status(ConnectionStatus::NotConnected), connection(nullptr), missedPkgsInARow(0), avgLatency(0) { }

	void waitConnection() {
		this->status = ConnectionStatus::Waiting;
	}

	void connect(crow::websocket::connection& conn) {
		this->connection = &conn;
		this->status = ConnectionStatus::Connected;
	}

	void disconnect() {
		this->connection = nullptr;
		this->status = ConnectionStatus::NotConnected;
	}
};