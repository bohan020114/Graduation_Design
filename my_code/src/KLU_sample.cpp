/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-04-01 17:29:42
 * @LastEditTime: 2024-04-09 17:23:38
 * @LastEditors:  
 */
//------------------------------------------------------------------------------
// KLU/Demo/klu_simple: simple demo program for KLU
//------------------------------------------------------------------------------

// KLU, Copyright (c) 2004-2022, University of Florida.  All Rights Reserved.
// Authors: Timothy A. Davis and Ekanathan Palamadai.
// SPDX-License-Identifier: LGPL-2.1+

//------------------------------------------------------------------------------

/* klu_simple: a simple KLU demo; solution is x = (1,2,3,4,5) */

#include <stdio.h>
#include <klu.h>
#include <iostream>
#include <vector>

int n = 9000;
std::vector<long int> Ap = {0, 2, 5, 9, 10, 12};
std::vector<long int> Ai = {0, 1, 0, 2, 4, 1, 2, 3, 4, 2, 1, 4};
std::vector<double> Ax = {2., 3., 3., -1., 4., 4., -3., 1., 2., 2., 6., 1.};
std::vector<double> b = {8., 45., -3., 3., 19.};

int main(void) {
    std::cout << "Ap array   :";
    for (int i = 0; i < 5; ++i) {
        std::cout << " " << Ap[i];
    }
    std::cout << std::endl;
    klu_l_symbolic *Symbolic;
    klu_l_numeric *Numeric;
    klu_l_common Common;
    int i;
    klu_l_defaults(&Common);
    Symbolic = klu_l_analyze(n, Ap.data(), Ai.data(), &Common);
    if (Symbolic == nullptr) {
        // 分析失败，打印错误信息
        std::cerr << "Error: klu_l_analyze failed." << std::endl;
        // 可以释放相关资源，如Common
        klu_l_free_symbolic(&Symbolic, &Common);
        std::cout << "---perform_lu_decomposition error---" << std::endl;
        return -1;
    }
    std::cout << "Symbolic_rank:" << Symbolic->structural_rank << std::endl;
    Numeric = klu_l_factor(Ap.data(), Ai.data(), Ax.data(), Symbolic, &Common);
    klu_l_solve(Symbolic, Numeric, 5, 1, b.data(), &Common);
    klu_l_free_symbolic(&Symbolic, &Common);
    klu_l_free_numeric(&Numeric, &Common);
    for (i = 0; i < n; i++) printf("x [%d] = %g\n", i, b[i]);
    return (0);
}
