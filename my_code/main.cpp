/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-29 15:15:53
 * @LastEditTime: 2024-04-09 16:58:28
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

int main() {
    // 设置时钟启动
    Timer timer;
    // 定义部分
    FileReader reader; // 定义读取部分（std::vector<Entry> entries; ）
    RCindicesToSRC csr;
    // 定义路径
    std::string DataPath = "/home/parallels/Documents/design/banchmark-matrix0222/case1_1.txt";
    // 调用函数读取并存储数据
    reader.readAndStoreData(DataPath);
    const std::vector<FileReader::Entry>& entries = reader.getEntries();
    csr.ConvertToCSR(reader.getEntries(), reader.getDim(), reader.getEntries().size());
    
    auto arrays = csr.getCSRArrays();
    // 获取 Ap, Ai, Ax
    std::vector<int> Ap = std::get<0>(arrays);
    std::vector<int> Ai = std::get<1>(arrays);
    std::vector<double> Ax = std::get<2>(arrays);
    
    // 调用 perform_lu_decomposition 函数
    int check_lu = perform_lu_decomposition(Ap.size() - 1, Ap.data(), Ai.data(), Ax.data());
    if(check_lu == 0){
        print_lu_decomposition(Ap.size() - 1, Ap.data(), Ai.data(), Ax.data());
    }
   
    // 时钟计时结果
    std::cout << "Total time: " << timer.elapsed() << " seconds" << std::endl;
    
    // 检测部分
    char check = false;
    if(check == true){
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
