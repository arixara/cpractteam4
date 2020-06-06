#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <string>
#include <thread>
#include <iomanip>


template <size_t N, class T>
class ThreadController {
	/**/

	std::mutex mutex1, mutex2;
	std::condition_variable done;

	std::vector<T> algVector;
	std::deque<std::string> PATHS;
	bool Finished[N];

	// 
	void threadTask(size_t id) {

		while (true) {
			std::unique_lock<std::mutex> lock(mutex1);
			if (algVector.empty()) {
				std::unique_lock<std::mutex> lock(mutex2);
				Finished[id] = true;
				done.notify_all();
				lock.unlock();
				return;
			}

			auto algorithm = algVector.back();
			algVector.pop_back();

			std::string fileName = PATHS.back();
			PATHS.pop_back();

			lock.unlock();
			algorithm->start(fileName);

			std::string s2 = fileName;
			std::cout.setf(std::ios::left);

			std::cout << "|" << std::setfill('-') << std::setw(61) << '-' << '|' << std::endl;
			std::cout << '|' << std::setfill(' ') << std::setw(3) << ' ' <<
				std::setw(17) << std::this_thread::get_id() << '|' <<
				std::setw((40 - s2.size()) / 2) << ' ' << std::setw(40 - (40 - s2.size()) / 2) << s2 << '|' << std::endl;
		}
	}

	void waitFinished() {
		std::unique_lock<std::mutex> lock(mutex2);
		done.wait(lock, [this] {
			return std::all_of(Finished, Finished + N, [](bool e) { return e; });
		});
	}

public:
	ThreadController() {}

	ThreadController& push(T algorithm, const std::string path) {
		algVector.push_back(algorithm);
		PATHS.push_back(path);
		return *this;
	}

	ThreadController& push(std::pair<T, std::string> algorithm) {
		algVector.push_back(algorithm.first);
		PATHS.push_back(algorithm.second);
		return *this;
	}

	ThreadController& push(std::vector<std::pair<T, std::string>>data) {
		for (auto i : data) {
			algVector.push_back(i.first);
			PATHS.push_back(i.second);
		}
		return *this;
	}

	ThreadController& push(std::vector<T>algorithms, std::vector<std::string>filenames) {
		for (auto i : algorithms)
			algVector.push_back(i);
		for (auto j : filenames)
			PATHS.push_back(j);
		return *this;
	}

	void start() {

		std::cout.setf(std::ios::left);
		std::cout << std::setw(7) << ' ' << std::setw(14) << "Thread id" << '|' << std::setw(18)\
			<< ' ' << std::setw(24) << "Directory" << std::endl;

		for (bool& i : Finished)
			i = false;

		for (size_t i = 0; i < N; ++i) {
			std::thread worker([this, i]() {
				threadTask(i);
			});
			worker.detach();
		}

		this->waitFinished();
	}

};
