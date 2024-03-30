/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-29 20:25:28
 * @LastEditTime: 2024-03-30 21:04:13
 * @LastEditors:  
 */
#ifndef READ_H
#define READ_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip> // for std::fixed and std::setprecision

struct Entry {
    long long j;
    long long jcol;
    long long i;
    long long irow;
    long double value;
};

void readAndStoreData(const std::string& filename, std::vector<Entry>& entries) {
    // 定义量
    int count = 0;
    int total_num = 0;
    long long max_j = 0;
    long long max_i = 0;
    std::string line;
    // 打开文件
    std::ifstream file(filename);
    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    // 读取文件内容，跳过第一行
    std::getline(file, line);
    // 逐行读取文件内容
    while (std::getline(file, line)) {
        Entry entry;
        total_num++; // 计算非空行数
        if (line.empty())
            continue;
        // 使用scanf开始读入
        if (sscanf(line.c_str(), "(j:%lld,jcol:%lld,i:%lld,irow:%lld) %Lf",
                   &entry.j, &entry.jcol, &entry.i, &entry.irow, &entry.value) != 5) {
            std::cerr << "Error parsing line: " << line << std::endl;
            total_num--; 
            continue;
        }
        // 输出本行应该是什么
        // std::cout << "Line:  " << line << std::endl;
        // 将解析出的数据存入entries数组中
        entries.push_back(entry);
        if (entry.j > max_j)
            max_j = entry.j;
        if (entry.i > max_i)
            max_i = entry.i;
        // 输出十位小数的判定
        // std::cout << std::fixed << std::setprecision(9);
        // 检测entries是否正确
        // std::cout << "Entry: (j:" << entry.j << ",jcol:" << entry.jcol << ",i:" << entry.i << ",irow:" << entry.irow << ")     " << entry.value << std::endl;
        // count++;
        // 仅输出前20次
        // if (count >= 20) 
            // break;  
        // std::cout << count << std::endl; 
    }
    // 输出 max_j & max_i
    std::cout << "Max j: " << max_j << std::endl;
    std::cout << "Max i: " << max_i << std::endl;
    // 输出总行数
    std::cout << "Total valid lines: " << total_num << std::endl;
    // 关闭文件
    file.close();
}

#endif // READ_H