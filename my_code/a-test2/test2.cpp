/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-26 10:44:33
 * @LastEditTime: 2024-03-29 11:59:46
 * @LastEditors:  
 */
#include <iostream>
#include <umfpack.h>

int main() {
    // 构造稀疏矩阵A和向量b
    double values[5] = {1.0, 2.0, 3.0, 4.0, 5.0}; // 非零元素数组
    SuiteSparse_long row_indices[5] = {0, 1, 2, 3, 4}; // 非零元素所在行的索引数组
    SuiteSparse_long col_indices[5] = {0, 1, 2, 3, 4}; // 非零元素所在列的索引数组
    SuiteSparse_long num_nonzeros = 5; // 非零元素的个数
    SuiteSparse_long num_rows = 5; // 矩阵的行数
    SuiteSparse_long num_cols = 5; // 矩阵的列数
    double b[5] = {1.0, 2.0, 3.0, 4.0, 5.0}; // 右侧向量

    // 符号分解
    void *Symbolic, *Numeric;
    umfpack_dl_symbolic(num_rows, num_cols, row_indices, col_indices, values, &Symbolic, NULL, NULL);
    
    // 数值分解
    umfpack_dl_numeric(row_indices, col_indices, values, Symbolic, &Numeric, NULL, NULL);

    // 求解线性方程组
    double x[5];
    umfpack_dl_solve(UMFPACK_A, row_indices, col_indices, values, x, b, Numeric, NULL, NULL);

    // 打印结果
    std::cout << "Solution x:" << std::endl;
    for (int i = 0; i < num_cols; ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;

    // 释放内存
    umfpack_dl_free_symbolic(&Symbolic);
    umfpack_dl_free_numeric(&Numeric);

    return 0;
}
