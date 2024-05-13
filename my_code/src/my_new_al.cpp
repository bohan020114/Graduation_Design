/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-29 15:15:53
 * @LastEditTime: 2024-05-13 16:44:32
 * @LastEditors:  
 */
#include <iostream>
#include <thread>
#include <vector>
#include "Timer.h"
#include "Function.h"
#include "Read.h"
#include "RCindicesToSRC.h"
#include "KluDecomposition.h"
#include "WriteLUinSRC.h"
#include "LuDecompositionPrint.h"
#include "myLU.h"

int main() {
    // 定义部分
    FileReader reader; // 定义读取部分（std::vector<Entry> entries; ）
    RCindicesToSRC csr;
    // 定义路径
    std::string DataPath = "/home/parallels/Documents/design/banchmark-matrix0222/case2_1.txt";
    // 调用函数读取并存储数据
    reader.readAndStoreData(DataPath);
    const std::vector<FileReader::Entry>& entries = reader.getEntries();
    std::cout << "dim: " << reader.getDim() << std::endl;
    auto [Ap, Ai, Ax] = csr.ConvertToCSR(reader.getEntries(), reader.getDim(), reader.getEntries().size());

    // 设置时钟启动
    Timer timer;
    int check = perform_lu_decomposition_Parallel_noParallel(reader.getDim() + 1, Ap, Ai, Ax);
    // 时钟计时结果
    std::cout << "Total time: " << timer.elapsed() << " seconds" << std::endl;
    
    if(check == 0){
        std::cout << "LU OK" << std::endl;
    }
   
    // 释放内存
    delete[] Ap;
    delete[] Ai;
    delete[] Ax;
    // 检测部分
    char mycheck = false;
    if(mycheck == true){
        // 遍历 entries 向量的前 20 个元素并打印每个元素
        std::cout << "Printing first 20 entries:" << std::endl;
        int count = 0;
        for (const auto& entry : entries) {
            if (count >= 20) {
                break;
            }
            std::cout << "Entry: (" << entry.i << ", " << entry.j << "), Value: " << entry.value << std::endl;
            count++;
        }
        std::cout << "dim: " << reader.getDim() << std::endl;
        std::cout << "Total valid lines:(useget)" << reader.getEntries().size() << std::endl;
    }
    return 0;
}
