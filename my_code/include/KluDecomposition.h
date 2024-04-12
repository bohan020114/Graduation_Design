/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-04-02 15:59:12
 * @LastEditTime: 2024-04-11 17:12:38
 * @LastEditors:  
 */
#ifndef KLU_DECOMPOSITION_H
#define KLU_DECOMPOSITION_H

#include <stdio.h>
#include <klu.h>
#include <iostream>
#include <vector>
#include "WriteLUinSRC.h"

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

int perform_lu_decomposition(int n, int *Ap, int *Ai, double *Ax) {
    std::cout << "---perform_lu_decomposition---" << std::endl;
    klu_symbolic *Symbolic;
    klu_numeric *Numeric;
    klu_common Common;
    
    // 设置KLU库的参数
    klu_defaults(&Common);
    char print = false;
    if(print == true){    
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
    }

    char dprint = false;
    if(dprint == true){
        int size_of_Ap = sizeof(Ap) / sizeof(Ap[0]);
        int size_of_Ai = sizeof(Ai) / sizeof(Ai[0]);
        int size_of_Ax = sizeof(Ax) / sizeof(Ax[0]);
        std::cout << "in function: " << size_of_Ap << " " << size_of_Ai << " " << size_of_Ax << std::endl;
    }

    // 进行符号分析
    Symbolic = klu_analyze(n, Ap, Ai, &Common);
    // std::cout << "Symbolic_rank:" << Symbolic->structural_rank << std::endl;
    // std::cout << Symbolic->n << std::endl;
    // std::cout << Symbolic->do_btf << std::endl;
    if (Symbolic == nullptr) {
        // 分析失败，打印错误信息
        std::cerr << "Error: klu_analyze failed." << std::endl;
        // 可以释放相关资源，如Common
        klu_free_symbolic(&Symbolic, &Common);
        std::cout << "---perform_lu_decomposition error---" << std::endl;
        return -1;
    }
    // std::cout << "Symbolic_rank:" << Symbolic->structural_rank << std::endl;
   
   
    // 执行数值LU分解
    Numeric = klu_factor(Ap, Ai, Ax, Symbolic, &Common);
    std::cout << "Numeric: " << Numeric->lnz << std::endl;
    // if (Numeric != KLU_OK) {
    //     printf("Error: Numeric factorization failed.\n");
    //     klu_free_symbolic(&Symbolic, &Common); // 释放Symbolic对象
    //     return -1;
    // }
    char write_in = true;
    if(write_in == true){    
        int lnz = Numeric->lnz;
        int unz = Numeric->unz;
            std::vector<int> Lp(n + 1);
            std::vector<int> Li(lnz);
            std::vector<int> Up(n + 1);
            std::vector<int> Ui(unz);
            std::vector<double> Lx(lnz);
            std::vector<double> Ux(unz);
        // std::cout << "here1" << std::endl;
        int success = klu_extract(Numeric, Symbolic,
                              Lp.data(), Li.data(), Lx.data(),
                              Up.data(), Ui.data(), Ux.data(),
                              NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                              &Common);
        // std::cout << "here2" << std::endl;
        FILE *fileL;
        fileL = fopen("L.txt", "w");
        if (fileL == NULL) {
            printf("Error opening the file.\n");
        return 1;
        }
        write_base(fileL, n + 1, lnz, lnz);
        write_int_array(fileL, Lp.data(), n + 1);
        write_int_array(fileL, Li.data(), lnz);
        write_double_array(fileL, Lx.data(), lnz);
        FILE *fileU;
        fileU = fopen("U.txt", "w");
        if (fileU == NULL) {
            printf("Error opening the file.\n");
        return 1;
        }
        write_base(fileU, n + 1, unz, unz);
        write_int_array(fileU, Up.data(), n + 1);
        write_int_array(fileU, Ui.data(), unz);
        write_double_array(fileU, Ux.data(), unz);
    }
    
    // 释放符号对象
    klu_free_symbolic(&Symbolic, &Common);
    // 释放数值对象
    klu_free_numeric(&Numeric, &Common);
    std::cout << "---perform_lu_decomposition finish---" << std::endl;
    return 0;
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