/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-05-07 11:21:58
 * @LastEditTime: 2024-05-07 11:22:01
 * @LastEditors:  
 */
#ifndef AMD_H
#define AMD_H

#include <vector>
#include <SuiteSparse/AMD.hpp>  // SuiteSparse 库中的 AMD 头文件

// 函数声明：对稀疏矩阵进行 AMD 排序
void amd_sparse_ordering(int n, const std::vector<int>& rows, const std::vector<int>& cols, std::vector<int>& perm) {
    // 初始化 AMD 控制参数和信息数组
    double control[AMD_CONTROL];
    double info[AMD_INFO];
    amd_defaults(control);
    control[AMD_DENSE] = 10.0; // 设置稠密度阈值，这里是默认值

    // 调用 SuiteSparse 中的 AMD 进行矩阵排序
    amd_order(n, rows.data(), cols.data(), perm.data(), control, info);
}

#endif  // AMD_H
