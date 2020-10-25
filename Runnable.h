#pragma once

#include <atomic>
#include <thread>
#include <Windows.h>

class Runnable
{
	std::atomic_bool  _Stop;
	std::thread		  _Thread;

public:
	Runnable()
		:_Stop(), _Thread()
	{
	}
	virtual ~Runnable()
	{
		Stop();
	}

	Runnable(Runnable const&) = delete;
	Runnable& operator=(Runnable const&) = delete;


	void Start()
	{
		_Thread = std::thread(&Runnable::DoWork, this);
	}

	void Stop()
	{
		_Stop = true;
		_Thread.join();
	}

	void Suspend()
	{
		SuspendThread(_Thread.native_handle());
	}

	void Resume()
	{
		ResumeThread(_Thread.native_handle());
	}

	bool IsStop() const
	{
		return _Stop;
	}

protected:
	virtual void DoWork() = 0;
};

