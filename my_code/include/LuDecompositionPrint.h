/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-05-06 23:28:44
 * @LastEditTime: 2024-05-06 23:39:10
 * @LastEditors:  
 */
#ifndef LU_DECOMPOSITION_PRINT_H
#define LU_DECOMPOSITION_PRINT_H

#include <iostream>
#include <stdio.h>
#include <klu.h>
#include <iostream>
#include <vector>
#include "WriteLUinSRC.h"

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

// 输出前20个整数数组元素
void print_first_20_integers(const int *arr) {
    std::cout << "First 20 integers:" << std::endl;
    int count = 20;
    for (int i = 0; i < count; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// 输出前20个双精度数组元素
void print_first_20_doubles(const double *arr) {
    std::cout << "First 20 doubles:" << std::endl;
    int count = 20;
    for (int i = 0; i < count; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
#endif
