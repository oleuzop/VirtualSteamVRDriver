#pragma once

#include <windows.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>


struct Position {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

struct EulerAngles {
	float h = 0.0f;
	float p = 0.0f;
	float r = 0.0f;
};

struct Headpose {
	Position pos;
	EulerAngles angles;
};

class EvenHooks
{
public:
	EvenHooks();
	~EvenHooks();
	void run();

	const float getPoseX();
	const float getPoseY();

	const float getHeading();
	const float getPitch();

private:
	std::thread t_;
	std::atomic<bool> keepRunning_;
};
