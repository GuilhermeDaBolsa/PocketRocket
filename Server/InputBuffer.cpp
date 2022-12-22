#pragma once
#include <string>

class InputBuffer {
private:
	static constexpr const size_t m_bufferSize = 4;
public:
	static constexpr const char emptyBuffer[m_bufferSize] = {0, 0, 0, 0};
	char buffer[m_bufferSize];

	InputBuffer() {
		setBuffer((char*)emptyBuffer);
	}

	void setBuffer(char* buffer) {
		memcpy(this->buffer, buffer, m_bufferSize);
	}

	void readBuffer(const std::string* buffer) {
		if (buffer->size() == m_bufferSize)
			setBuffer((char*)buffer->data());
		else
			setBuffer((char*)emptyBuffer);
	}

	bool wannaGoUp() {
		return this->buffer[0];
	}

	bool wannaGoDown() {
		return this->buffer[1];
	}

	bool wannaGoLeft() {
		return this->buffer[2];
	}

	bool wannaGoRight() {
		return this->buffer[3];
	}
};