/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-29 20:25:28
 * @LastEditTime: 2024-03-29 20:58:13
 * @LastEditors:  
 */
#ifndef READ_H
#define READ_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct Entry {
    int j;
    int jcol;
    int i;
    int irow;
    double value;
};

void readAndStoreData(const std::string& filename, std::vector<Entry>& entries) {
    // 打开文件
    std::ifstream file(filename);
    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    // 读取文件内容，跳过第一行
    std::getline(file, line);
    // 逐行读取文件内容
    while (std::getline(file, line)) {
        // 使用字符串流解析数据
        std::istringstream iss(line);
        Entry entry;
        char discard;
        // 从字符串流中提取数据
        iss >> discard >> entry.j >> discard >> discard >> entry.jcol >> discard >> entry.i >> discard >> entry.irow >> discard >> entry.value;
        // 将解析出的数据存入entries数组中
        entries.push_back(entry);
    }

    // 关闭文件
    file.close();
}

#endif // READ_H
