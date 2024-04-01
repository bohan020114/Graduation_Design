/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-30 20:02:58
 * @LastEditTime: 2024-04-02 00:05:56
 * @LastEditors:  
 */
#ifndef CSR_CONVERTER_H
#define CSR_CONVERTER_H

#include <vector>
#include "Read.h"

class RCindicesToSRC{
public:
    // 定义CSR格式的结构体
    struct CSRMatrix {
        std::vector<long long> Ap;  // 行指针（每一列有多少元素）
        std::vector<long long> Ai;  // 列索引（第j列的元素位置）
        std::vector<long double> Ax; // 非零值
    };

    void ConvertToCSR(const std::vector<FileReader::Entry>& entries,
                  long long int row_num, long long int row_pos){
        row_num = row_num + 1;
        long long int pos = 0;
        // 初始化 csrformat 向量
        csrformat.resize(1); // 设置为 1 个元素
        
        std::cout << "size for en: " << row_pos << std::endl;
        std::cout << "size for dim: " << row_num << std::endl;
        // 为所有 CSRMatrix 结构体分配内存并初始化长度
        for (auto& csr : csrformat) {
            std::cout << "here" << std::endl;
            // 初始化 Ap、Ai、Ax 数组为 0
            csr.Ap.resize(row_num, 0); // 使用 resize() 初始化为 0
            csr.Ai.resize(row_pos, 0);
            csr.Ax.resize(row_pos, 0.0);
            // 遍历 entries，并对 CSRMatrix 进行格式转化
            for (const auto& entry : entries) {
                csr.Ap[entry.j + 1]++;
                csr.Ax[pos] = entry.value;
                csr.Ai[pos] = entry.i;
                pos++;
            }
        }

        // 打印 CSRMatrix 结构体中的三个队列
        std::cout << "Printing CSRMatrix structures:" << std::endl;
        for (const auto& csr : csrformat) {
            std::cout << "------------------------------------" << std::endl;
            std::cout << "CSRMatrix:" << std::endl;
            std::cout << "Ap length: " << csr.Ap.size() << std::endl;
            std::cout << "Ai length: " << csr.Ai.size()<< std::endl;
            std::cout << "Ax length: " << csr.Ax.size() << std::endl;
            // 打印前20项
            std::cout << "First 20 items of Ap: ";
            for (int i = 0; i < 20; ++i) {
                std::cout << csr.Ap[i] << " ";
            }
            std::cout << std::endl;
            std::cout << "First 20 items of Ai: ";
            for (int i = 0; i < 20; ++i) {
                std::cout << csr.Ai[i] << " ";
            }
            std::cout << std::endl;
            std::cout << "First 20 items of Ax: ";
            for (int i = 0; i < 20; ++i) {
                std::cout << csr.Ax[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    void printCSR(const CSRMatrix& csr, long long int row_num, long long int row_pos) {
        
        std::cout << "Ap: ";
        for (int i = 0; i <= row_num; ++i) {
            std::cout << csr.Ap[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Ai: ";
        for (int i = 0; i < row_pos; ++i) {
            std::cout << csr.Ai[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Ax: ";
        for (int i = 0; i < row_pos; ++i) {
            std::cout << csr.Ax[i] << " ";
        }
        std::cout << std::endl;
    }

    std::size_t getApLength(const CSRMatrix& csr) const {
        // 计算 Ap 数组的长度
        std::size_t length = 0;
        while (csr.Ap[length] != 0) {
            ++length;
        }
        return length;
    }

    std::size_t getAiLength(const CSRMatrix& csr) const {
        // 计算 Ai 数组的长度
        std::size_t length = 0;
        while (csr.Ai[length] != 0) {
            ++length;
        }
        return length;
    }

    std::size_t getAxLength(const CSRMatrix& csr) const {
        // 计算 Ai 数组的长度
        std::size_t length = 0;
        while (csr.Ax[length] != 0) {
            ++length;
        }
        return length;
    }

private:
    std::vector<CSRMatrix> csrformat;
};


#endif //CSR_CONVERTER_H
