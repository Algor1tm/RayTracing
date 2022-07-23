#pragma once

#include "Core/Debug.h"

#include <vector>
#include <thread>
#include <future>
#include <condition_variable>
#include <queue>
#include <functional>


class ThreadPool
{
public:
	ThreadPool() = default;
	~ThreadPool() = default;

	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;
	ThreadPool(ThreadPool&&) = delete;
	ThreadPool& operator=(ThreadPool&& ) = delete;

	void Init(uint32_t threadsCount)
	{
		ASSERT(threadsCount != 0, "ERROR: ThreadPool must have at least one thread!\n");

		m_Exit = false;

		m_Threads.reserve(threadsCount);
		for (size_t i = 0; i < threadsCount; ++i)
		{
			m_Threads.emplace_back([this]() { Work(); });
		}
	}

	void Shutdown()
	{
		// Wake up all threads and wait for them to exit
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_Exit = true;
		}

		m_Notifier.notify_all();

		for (auto& thread : m_Threads)
		{
			if (thread.joinable())
				thread.join();
		}
	}

	template <typename Func, typename... Args>
	std::future<std::invoke_result_t<Func, Args...>> AddTask(Func&& function, Args&&... args)
	{
		using return_type = std::invoke_result_t<Func, Args...>;
		
		if (!std::is_same_v<return_type, void>)
			ASSERT(false, "Function return type must void");

		auto task = std::make_shared<std::packaged_task<return_type()>>(
			std::bind(std::forward<Func>(function), std::forward<Args>(args)...));

		std::future<return_type> result = task->get_future();

		// Add Task
		{
            std::unique_lock<std::mutex> lock(m_Mutex);
            m_TaskQueue.emplace([task]() { (*task)(); });
		}

		// Force one thread to work
		m_Notifier.notify_one();

		return result;
	}

private:
	void Work()
	{
        while (true)
        {
            std::function<void()> task;
            
            // Wait for new task
            {
                std::unique_lock<std::mutex> lock(m_Mutex);
                m_Notifier.wait(lock, [this]() {return !m_TaskQueue.empty() || m_Exit; });
                
                if (m_Exit)
                	return;
                
                task = std::move(m_TaskQueue.front());
                m_TaskQueue.pop();
            }
            
            task();
        }
    }

private:
	std::vector<std::thread> m_Threads;
	std::queue<std::function<void()>> m_TaskQueue;
	std::mutex m_Mutex;
	std::condition_variable m_Notifier;
	bool m_Exit;
};
