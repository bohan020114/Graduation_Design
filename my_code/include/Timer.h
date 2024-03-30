/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-29 15:42:23
 * @LastEditTime: 2024-03-29 15:56:46
 * @LastEditors:  
 */
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>
#include <iostream>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

public:
    // 构造函数
    Timer() {
        reset();
    }

    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    double elapsed() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(end_time - start_time).count();
    }
};

#endif // TIMER_H

