#pragma once

#include <windows.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>

class EvenHooks
{
public:
	EvenHooks();
	~EvenHooks();
	void run();

private:
	std::thread t_;
	std::atomic<bool> keepRunning_;
};
