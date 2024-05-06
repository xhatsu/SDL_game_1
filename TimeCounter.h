#pragma once
#include<chrono>
#include<vector>
class TimeCounter {
private:
    std::chrono::steady_clock::time_point start_time_;
    std::chrono::seconds duration_;
public:
    double currentSeconds=0;
    TimeCounter(int seconds) : duration_(seconds) {
        start_time_ = std::chrono::steady_clock::now();
    }

    // Check if the timer is still running
    bool isRunning() const {
        auto now = std::chrono::steady_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - start_time_);
        return elapsed_seconds < duration_;
    }
    double getCurrentSecond() {
        auto now = std::chrono::steady_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - start_time_);
        currentSeconds = elapsed_seconds.count();
        return currentSeconds;
    }
};

