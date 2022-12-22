#pragma once
#include <string>
#include <chrono>
#include "InputBuffer.cpp"

class Player {
public:
	double x;
	double y;
	double speedX;
	double speedY;

	double walkSpeed;

	InputBuffer input;

	Player()
		: x(0), y(0), walkSpeed(120), input(InputBuffer()){}

	void setInput(const std::string* inputData) {
		this->input.readBuffer(inputData);
	}

	void updateVelocity() {
		this->speedX = 0;
		this->speedY = 0;

		if (input.wannaGoUp())
			this->speedY -= 1;

		if (input.wannaGoDown())
			this->speedY += 1;

		if (input.wannaGoLeft())
			this->speedX -= 1;

		if (input.wannaGoRight())
			this->speedX += 1;
	}

	void updatePosition(double deltaTime) {
		this->x += this->speedX * this->walkSpeed * deltaTime;
		this->y += this->speedY * this->walkSpeed * deltaTime;
	}

	void update(double deltaTime) {
		this->updateVelocity();
		this->updatePosition(deltaTime);
	}
};