/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-29 15:15:53
 * @LastEditTime: 2024-05-12 20:41:15
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
#include "UMFPACKDecomposition.h"
#include "simple_LU.h"

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
    std::vector<int> Ai(reader.getEntries().size());
    std::vector<int> Aj(reader.getEntries().size());
    std::vector<double> Avalue(reader.getEntries().size());
    int n = reader.getDim();
    // auto [Ap, Ai, Ax] = csr.ConvertToCSR(reader.getEntries(), reader.getDim(), reader.getEntries().size());
    for (size_t idx = 0; idx < entries.size(); ++idx) {
        const auto& entry = entries[idx];
        Ai[idx] = entry.i;
        Aj[idx] = entry.j;
        Avalue[idx] = entry.value;
    }
    
    int check = true;
    if(check == true){
        size_t num_elements = std::min({Ai.size(), Aj.size(), Avalue.size(), size_t(20)});

        // 输出每个数组的前20个元素
        std::cout << "Ai: ";
        for (size_t idx = 0; idx < num_elements; ++idx) {
            std::cout << Ai[idx] << " ";
        }
        std::cout << std::endl;

        std::cout << "Aj: ";
        for (size_t idx = 0; idx < num_elements; ++idx) {
            std::cout << Aj[idx] << " ";
        }
        std::cout << std::endl;

        std::cout << "Avalue: ";
        for (size_t idx = 0; idx < num_elements; ++idx) {
            std::cout << Avalue[idx] << " ";
        }
        std::cout << std::endl;
    }
    
    // 设置时钟启动
    Timer timer;
    vector<Triple> L, U;
    perform_lu_decomposition_simple(n, Ai, Aj, Avalue, L, U);
    std::cout << "Total time: " << timer.elapsed() << " seconds" << std::endl;
    return 0;
}
