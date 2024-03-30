/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-29 15:15:53
 * @LastEditTime: 2024-03-30 21:02:36
 * @LastEditors:  
 */
#include <iostream>
#include <thread>
#include <vector>
#include "Timer.h"
#include "Function.h"
#include "Read.h"

int main() {
    // 设置时钟启动
    Timer timer;
    // 定义部分
    std::vector<Entry> entries; //存储使用的结构体
    // 定义路径
    std::string DataPath = "/home/parallels/Documents/design/banchmark-matrix0222/case1_1.txt";
    // 调用函数读取并存储数据
    readAndStoreData(DataPath, entries);

    //时钟计时结果
    std::cout << "Total time: " << timer.elapsed() << " seconds" << std::endl;
    return 0;
}
