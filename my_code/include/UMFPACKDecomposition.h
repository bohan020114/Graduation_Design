/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-04-02 15:59:12
 * @LastEditTime: 2024-05-07 00:34:03
 * @LastEditors:  
 */
#ifndef UMFPACK_DECOMPOSITION_H
#define UMFPACK_DECOMPOSITION_H

#include <stdio.h>
#include <umfpack.h>
#include <iostream>
#include <vector>
#include "WriteLUinSRC.h"
#include "LuDecompositionPrint.h"

int perform_lu_decomposition_UMFPACK(int n, int *Ap, int *Ai, double *Ax) {
    std::cout << "---perform_lu_decomposition_UMFPACK---" << std::endl;
    void *Symbolic, *Numeric;

    // 执行符号分析
    int status = umfpack_di_symbolic(n, n, Ap, Ai, Ax, &Symbolic, NULL, NULL);
    if (status != UMFPACK_OK) {
        std::cerr << "UMFPACK symbolic analysis failed with status " << status << std::endl;
        return 1;
    }

    // 执行数值分解
    status = umfpack_di_numeric(Ap, Ai, Ax, Symbolic, &Numeric, NULL, NULL);
    if (status != UMFPACK_OK) {
        std::cerr << "UMFPACK numeric factorization failed with status " << status << std::endl;
        umfpack_di_free_symbolic(&Symbolic);
        return 1;
    }

    // 释放符号对象
    umfpack_di_free_symbolic(&Symbolic);

    int check_out = false;
    if(check_out == true){
        // 提取 LU 分解因子数据
        int *Lp, *Li, *Up, *Ui;
        double *Lx, *Ux;
        int lnz, unz;
        int do_recip = 0; // 不计算倒数

        umfpack_di_get_lunz(&lnz, &unz, NULL, NULL, NULL, Numeric); // 获取 LU 因子的非零元素数量
        Lp = new int[n + 1];
        Li = new int[lnz];
        Lx = new double[lnz];
        Up = new int[n + 1];
        Ui = new int[unz];
        Ux = new double[unz];

        umfpack_di_get_numeric(Lp, Li, Lx, Up, Ui, Ux, NULL, NULL, NULL, &do_recip, NULL, Numeric);

        // 在这里可以使用 Lp, Li, Lx, Up, Ui, Ux 数组进行进一步处理或分析
        std::cout << "LP:" ;
        print_first_20_integers(Lp);
        std::cout << "Li:" ;
        print_first_20_integers(Li);
        std::cout << "Lx:" ;
        print_first_20_doubles(Lx);
        std::cout << "UP:" ;
        print_first_20_integers(Up);
        std::cout << "Ui:" ;
        print_first_20_integers(Ui);
        std::cout << "Ux:" ;
        print_first_20_doubles(Ux);
        
        // 释放动态分配的内存
        delete[] Lp;
        delete[] Li;
        delete[] Lx;
        delete[] Up;
        delete[] Ui;
        delete[] Ux;
    }
    // 释放数值对象
    umfpack_di_free_numeric(&Numeric);

    return 0;
}

#endif // UMFPACK_DECOMPOSITION_H