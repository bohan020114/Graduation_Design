<!--
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-29 16:21:14
 * @LastEditTime: 2024-03-29 16:23:46
 * @LastEditors:  
-->
> #include "umfpack.h"
#include <stdio.h>
int main() {
    // 定义稀疏矩阵的维度和非零元素个数
    int n_row = 3;
    int n_col = 3;
    int n_elements = 5;
    // 稀疏矩阵的非零元素
    int Ap[] = {0, 2, 3, 5}; // 列指针数组
    int Ai[] = {0, 2, 1, 0, 2}; // 行索引数组
    double Ax[] = {1.0, 2.0, 3.0, 4.0, 5.0}; // 非零元素数组
    // UMFPACK 的对象
    void *Symbolic, *Numeric;
    double *null = (double *) NULL;
    // 分析稀疏矩阵的结构
    umfpack_di_symbolic(n_row, n_col, Ap, Ai, Ax, &Symbolic, null, null);
    // 数值分解
    umfpack_di_numeric(Ap, Ai, Ax, Symbolic, &Numeric, null, null);
    // 求解线性方程组
    double b[] = {1.0, 2.0, 3.0}; // 右侧向量
    double x[n_col]; // 解向量
    umfpack_di_solve(UMFPACK_A, Ap, Ai, Ax, x, b, Numeric, null, null);
    // 输出解向量
    printf("Solution:\n");
    for (int i = 0; i < n_col; i++) {
        printf("%f\n", x[i]);
    }
    // 释放 UMFPACK 对象
    umfpack_di_free_symbolic(&Symbolic);
    umfpack_di_free_numeric(&Numeric);
    return 0;
}

- 存储方式：
    - 列指针索引


