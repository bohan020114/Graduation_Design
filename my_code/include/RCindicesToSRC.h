/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-30 20:02:58
 * @LastEditTime: 2024-05-13 04:17:30
 * @LastEditors:  
 */
#ifndef CSR_CONVERTER_H
#define CSR_CONVERTER_H

#include <vector>
#include "Read.h"
#include "CSRWriter.h"

class RCindicesToSRC{
public:
    int size_of_Ap = 0;
    int size_of_Ai = 0;
    int size_of_Ax = 0;
    // 定义CSR格式的结构体
    struct CSRMatrix {
        int* Ap;  // 行指针（每一列有多少元素）
        int* Ai;  // 列索引（第j列的元素位置）
        double* Ax; // 非零值
    };

    std::tuple<int*, int*, double*> ConvertToCSR(const std::vector<FileReader::Entry>& entries,
                  int row_num, int row_pos){
        std::cout << "---ConvertToCSR---" << std::endl;
        row_num = row_num + 2;
        int pos = 0;
        std::cout << "row_num:" << row_num << std::endl;
        std::cout << "row_pos:" << row_pos << std::endl;
        // 初始化 csrformat 向量
        csrformat.resize(1); // 设置为 1 个元素
        // std::cout << "size for en: " << row_pos << std::endl;
        // std::cout << "size for dim: " << row_num << std::endl;
        // 为所有 CSRMatrix 结构体分配内存并初始化长度
        for (auto& csr : csrformat) {
            // 初始化 Ap、Ai、Ax 数组为 0
            csr.Ap = new int[row_num]{};
            csr.Ai = new int[row_pos]{};
            csr.Ax = new double[row_pos]{};
            
            // 遍历 entries，并对 CSRMatrix 进行格式转化
            for (const auto& entry : entries) {
                csr.Ap[entry.j + 1]++;
                csr.Ax[pos] = entry.value;
                csr.Ai[pos] = entry.i;
                pos++;
            }
            // 更新 csr.Ap 数组
            for (int i = 1; i < row_num; ++i) {
                csr.Ap[i] += csr.Ap[i - 1];
            }
        }
        
        char print_me = true;
        if (print_me == true){
            // 打印 CSRMatrix 结构体中的三个队列
            std::cout << "Printing CSRMatrix structures:" << std::endl;
            for (const auto& csr : csrformat) {
                std::cout << "------------------------------------" << std::endl;
                std::cout << "CSRMatrix:" << std::endl;
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
        std::cout << "---ConvertToCSR finish---" << std::endl;
        return std::make_tuple(csrformat[0].Ap, csrformat[0].Ai, csrformat[0].Ax);
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

    const std::vector<CSRMatrix>& getCSRMatrix() const {
        return csrformat;
    }

private:
    std::vector<CSRMatrix> csrformat;
};


#endif //CSR_CONVERTER_H
