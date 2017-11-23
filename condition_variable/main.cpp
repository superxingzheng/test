#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread() {
	// wait until main() sends data
	std::unique_lock < std::mutex > lk(m);
	cv.wait(lk, [] {return ready;});
	
	std::string local_data = data;
	
	// manual unlocking is done before notifying, to avoid waking up
	// the waiting thread only to block again
	lk.unlock();
	processed = true;
	cv.notify_all();
	
	// after the wait, we own the lock.

	std::thread::id this_id = std::this_thread::get_id();
	std::cout << "thread " << this_id << ": data = " << data << std::endl;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	
	std::cout << "thread " << this_id << ": done." << std::endl;
}

int main() {
	int thread_num = 2;
	std::thread threads[thread_num];

	for (int i = 0; i < thread_num; i++) {
		threads[i] = std::thread(worker_thread);
	}

	for (int j = 0; j < 10; j++) {
		data = "Example data ";
		// send data to the worker thread
		{
			std::lock_guard < std::mutex > lk(m);
			ready = true;
			std::cout << "main() signals data ready for processing\n";
		}
		cv.notify_all();
		
		{
			std::unique_lock < std::mutex > lk(m);
			cv.wait(lk, [] {return processed;});
		}
	}
	

	
	std::cout << "Back in main(), data = " << data << '\n';

	for (int i = 0; i < 5; i++) {
		threads[i].join();
	}

	return 0;
}
