/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-29 15:15:53
 * @LastEditTime: 2024-03-29 15:46:10
 * @LastEditors:  
 */
#include <iostream>
#include <thread>
#include "timer.h"
#include "function.h"

int main() {
    // 设置时钟启动
    Timer timer;

    //功能性部分
    int a = 5;
    int b = 7;
    int sum = add(a, b);
    std::cout << "The sum of " << a << " and " << b << " is: " << sum << std::endl;

    //时钟计时结果
    std::cout << "Total time: " << timer.elapsed() << " seconds" << std::endl;
    return 0;
}
