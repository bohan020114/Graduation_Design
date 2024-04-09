/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-29 20:25:28
 * @LastEditTime: 2024-04-06 16:01:51
 * @LastEditors:  
 */
#ifndef READ_H
#define READ_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip> // for std::fixed and std::setprecision
#include <algorithm>

class FileReader {
public:
    struct Entry {
        long long j;
        long long jcol;
        long long i;
        long long irow;
        long double value;
    };

    void readAndStoreData(const std::string& filename) {
        std::cout << "---readAndStoreData---" << std::endl;
        dim = 0;
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
            struct Entry entry;
            if (line.empty())
                continue;
            // 使用scanf开始读入
            if (sscanf(line.c_str(), "(j:%lld,jcol:%lld,i:%lld,irow:%lld) %Lf",
                       &entry.j, &entry.jcol, &entry.i, &entry.irow, &entry.value) != 5) {
                std::cerr << "Error parsing line: " << line << std::endl;
                continue;
            }
            // 将解析出的数据存入entries数组中
            entries.push_back(entry);
        }
        // 计算dim
        dimCalculation();
        // 关闭文件
        file.close();
        std::cout << "---readAndStoreData finish---" << std::endl;
    }

    const std::vector<Entry>& getEntries() const {
        return entries;
    }
    
    void dimCalculation() {
        for (const auto& entry : entries) {
            dim = std::max({dim, entry.i, entry.j});
        }
    }

    int getDim() const {
        return dim;
    }

private:
    std::vector<Entry> entries;
    long long int dim;
};

#endif // READ_H
