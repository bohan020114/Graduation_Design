#ifndef SIMPLE_H
#define SIMPLE_H

#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <fstream>
#include <iomanip> // 用于控制输出格式
#include <functional>

using namespace std;

// 用于输出的元组类型
using Triple = tuple<int, int, double>;

// 定义一个自定义的哈希结构，用于 std::pair<int, int>
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ hash2; // 可以用更复杂的方式合并这两个哈希值
    }
};

// 使用unordered_map和自定义哈希函数作为稀疏矩阵的存储
using SparseMatrix = unordered_map<pair<int, int>, double, pair_hash>;

// LU分解函数，直接处理向量输入
void perform_lu_decomposition_simple(int n, const vector<int>& i, const vector<int>& j, const vector<double>& value,
                                     vector<Triple>& L, vector<Triple>& U) {
    SparseMatrix A;

    std::cout << "here" << std::endl;
    // 填充稀疏矩阵A
    for (size_t index = 0; index < i.size(); ++index) {
        std::cout << i.size() << ":" << index << std::endl;
        A[{i[index], j[index]}] = value[index];
    }

    L.clear();
    U.clear();

    // 进行LU分解
    for (int k = 0; k < n; ++k) {
        std::cout << k << std::endl;
        for (int j = k; j < n; ++j) {
            double sum = 0.0;
            for (int p = 0; p < k; ++p) {
                sum += A[{k, p}] * A[{p, j}];
            }
            A[{k, j}] -= sum;
            if (A[{k, j}] != 0) U.push_back({k, j, A[{k, j}]});
        }

        for (int i = k + 1; i < n; ++i) {
            double sum = 0.0;
            for (int p = 0; p < k; ++p) {
                sum += A[{i, p}] * A[{p, k}];
            }
            A[{i, k}] = (A[{i, k}] - sum) / A[{k, k}];
            if (A[{i, k}] != 0) L.push_back({i, k, A[{i, k}]});
        }
        
        // 添加L的对角线元素，对角线元素固定为1
        L.push_back({k, k, 1.0});
    }
}

// 函数来将L或U矩阵写入到文件
void write_matrix_to_file(const vector<Triple>& matrix, const string& file_name) {
    ofstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error opening file: " << file_name << endl;
        return;
    }
    for (const auto& [row, col, val] : matrix) {
        file << row << " " << col << " " << fixed << setprecision(4) << val << "\n";
    }
    file.close();
}

#endif
