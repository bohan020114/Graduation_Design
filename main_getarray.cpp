/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-29 15:15:53
 * @LastEditTime: 2024-05-04 13:34:21
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

void writeToTextFiles(const std::vector<FileReader::Entry>& entries) {
    // 写入 new.txt
    std::ofstream newFile("new.txt");
    if (!newFile.is_open()) {
        std::cerr << "Failed to open new.txt for writing." << std::endl;
        return;
    }

    for (const auto& entry : entries) {
       if (entry.i < 2000 && entry.j < 2000) {
        newFile << entry.i << std::endl;       // 写入 i
        newFile << entry.j << std::endl;       // 写入 j
        newFile << entry.value << std::endl;   // 写入 value
        }
    }

    newFile.close();

    // 写入 old.txt
    std::ofstream oldFile("old.txt");
    if (!oldFile.is_open()) {
        std::cerr << "Failed to open old.txt for writing." << std::endl;
        return;
    }

    for (const auto& entry : entries) {
        oldFile << entry.irow << std::endl;    // 写入 irow
        oldFile << entry.jcol << std::endl;    // 写入 jcol
        oldFile << entry.value << std::endl;   // 写入 value
    }

    oldFile.close();
}

int main() {
    FileReader reader; // 定义读取部分（std::vector<Entry> entries; ）
    RCindicesToSRC csr;
    // 定义路径
    std::string DataPath = "/home/parallels/Documents/design/banchmark-matrix0222/case1_1.txt";
    // 调用函数读取并存储数据
    reader.readAndStoreData(DataPath);
    const std::vector<FileReader::Entry>& entries = reader.getEntries();
    writeToTextFiles(entries);
    return 0;
}
