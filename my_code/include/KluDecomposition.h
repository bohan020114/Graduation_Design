/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-04-02 15:59:12
 * @LastEditTime: 2024-04-05 15:10:34
 * @LastEditors:  
 */
#ifndef KLU_DECOMPOSITION_H
#define KLU_DECOMPOSITION_H

#include <stdio.h>
#include <klu.h>
#include <iostream>

void print_LU_factors(const klu_numeric *Numeric) {
    std::cout << "LU Decomposition Result:" << std::endl;

    int n = Numeric->n;
    int nblocks = Numeric->nblocks;
    int *Lip = Numeric->Lip;
    int *Uip = Numeric->Uip;
    void **LUbx = Numeric->LUbx;

    for (int block = 0; block < nblocks; ++block) {
        std::cout << "Block " << block + 1 << ":" << std::endl;

        int *Lip_block = Lip + n * block;
        int *Uip_block = Uip + n * block;
        int *Llen_block = Numeric->Llen + n * block;
        int *Ulen_block = Numeric->Ulen + n * block;
        int *LUip = (int *)LUbx[block];

        for (int col = 0; col < n; ++col) {
            int Lstart = Lip_block[col];
            int Lend = Lstart + Llen_block[col];
            int Ustart = Uip_block[col];
            int Uend = Ustart + Ulen_block[col];

            std::cout << "Column " << col + 1 << " of L:" << std::endl;
            for (int i = Lstart; i < Lend; ++i) {
                std::cout << "Lx[" << i << "]: " << ((double *)LUbx[block])[i] << std::endl;
            }

            std::cout << "Column " << col + 1 << " of U:" << std::endl;
            for (int i = Ustart; i < Uend; ++i) {
                std::cout << "Ux[" << i << "]: " << ((double *)LUbx[block])[i] << std::endl;
            }
        }
    }
}

void perform_lu_decomposition(int n, int *Ap, int *Ai, double *Ax) {
    klu_symbolic *Symbolic;
    klu_numeric *Numeric;
    klu_common Common;
    
    // 设置KLU库的参数
    klu_defaults(&Common);
    std::cout << "n_in_perform_lu_decomposition:" << n << std::endl;
    // 打印 Ap 数组的前五项
    std::cout << "Ap array:";
    for (int i = 0; i < 5; ++i) {
        std::cout << " " << Ap[i];
    }
    std::cout << std::endl;

    // 打印 Ai 数组的前五项
    std::cout << "Ai array:";
    for (int i = 0; i < 5; ++i) {
        std::cout << " " << Ai[i];
    }
    std::cout << std::endl;

    // 进行符号分析
    Symbolic = klu_analyze(n, Ap, Ai, &Common);
    std::cout << "Symbolic_rank:" << Symbolic->structural_rank << std::endl;
    if (Symbolic == NULL) {
        printf("Error: Symbolic analysis failed.\n");
        return;
    }

    // 执行数值LU分解
    Numeric = klu_factor(Ap, Ai, Ax, Symbolic, &Common);
    // std::cout << "Numeric" << Numeric << std::endl;
    if (Numeric != KLU_OK) {
        printf("Error: Numeric factorization failed.\n");
        klu_free_symbolic(&Symbolic, &Common); // 释放Symbolic对象
        return;
    }

    
    // 释放符号对象
    klu_free_symbolic(&Symbolic, &Common);
    // 释放数值对象
    klu_free_numeric(&Numeric, &Common);
}

void print_lu_decomposition(const int n, const int *Ap, const int *Ai, const double *Ax) {
    std::cout << "LU Decomposition Result:" << std::endl;

    std::cout << "Ap: ";
    for (int i = 0; i < 20; ++i) {
        std::cout << Ap[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Ai: ";
    for (int i = 0; i < std::min(Ap[n], 20); ++i) {
        std::cout << Ai[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Ax: ";
    for (int i = 0; i < std::min(Ap[n], 20); ++i) {
        std::cout << Ax[i] << " ";
    }
    std::cout << std::endl;
}



#endif // KLU_DECOMPOSITION_H
