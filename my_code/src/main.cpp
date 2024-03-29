/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-29 15:15:53
 * @LastEditTime: 2024-03-29 20:54:00
 * @LastEditors:  
 */
#include <iostream>
#include <thread>
#include <vector>
#include "timer.h"
#include "function.h"
#include "read.h"


int main() {
    // 设置时钟启动
    Timer timer;

    //功能性部分
    std::vector<Entry> entries;
    // 调用函数读取并存储数据
    readAndStoreData("/home/parallels/Documents/design/banchmark-matrix0222/case1_1.txt", entries);

    // 输出前20次从文件中读取的数据
    std::cout << "First 20 entries read from file:\n";
    int count = 0;
    for (const auto& entry : entries) {
        std::cout << "Entry: (j:" << entry.j << ", jcol:" << entry.jcol << ", i:" << entry.i << ", irow:" << entry.irow << ") " << entry.value << std::endl;
        count++;
        if (count >= 20) // 仅输出前20次
            break;
    }

    //时钟计时结果
    std::cout << "Total time: " << timer.elapsed() << " seconds" << std::endl;
    return 0;
}
