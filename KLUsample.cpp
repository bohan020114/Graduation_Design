/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-04-09 21:52:31
 * @LastEditTime: 2024-04-11 16:57:25
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
#include <iostream>
#include <vector>
#include "klu.h"

int    n = 5 ;
int    Ap [ ] = {0, 2, 5, 9, 10, 12} ;
int    Ai [ ] = { 0,  1,  0,   2,  4,  1,  2,  3,   4,  2,  1,  4} ;
double Ax [ ] = {2., 3., 3., -1., 4., 4., -3., 1., 2., 2., 6., 1.} ;
double b [ ] = {8., 45., -3., 3., 19.} ;

void write_base(FILE *file, int p_len, int i_len, int x_len){
    fprintf(file, "LU_case; 2023; BohanWang\n");
    int total = int(p_len / 16) + int(i_len / 16) + int(x_len / 8) + 3;
    fprintf(file, "%12d", total);
    fprintf(file, "%12d", int(p_len / 16) + 1);
    fprintf(file, "%12d", int(i_len / 16) + 1);
    fprintf(file, "%12d\n", int(x_len / 8) + 1);
    fprintf(file, "rsa%21d%12d%12d\n", p_len, p_len, x_len);
    fprintf(file, "                 (16I12)     (16I12)     (8E9.9)  \n" );
}
void print_array_int(const int *array, int length) {
    printf("[");
    for (int i = 0; i < length; ++i) {
        printf("%d", array[i]);
        if (i != length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void print_array_double(const double *array, int length) {
    printf("[");
    for (int i = 0; i < length; ++i) {
        printf("%.2f", array[i]);
        if (i != length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void write_int_array(FILE *file, const int *array, int length) {
    for (int i = 0; i < length; ++i) {
        fprintf(file, "%6d", array[i]);
        if ((i + 1) % 16 == 0) {
            fprintf(file, "\n");
        }
    }
    if (length % 16 != 0) {
        fprintf(file, "\n");
    }
}

void write_double_array(FILE *file, const double *array, int length) {
    for (int i = 0; i < length; ++i) {
        fprintf(file, "%8.2f", array[i]);
        if ((i + 1) % 8 == 0) {
            fprintf(file, "\n");
        }
    }
    if (length % 8 != 0) {
        fprintf(file, "\n");
    }
}

int main(void) {
    klu_symbolic *Symbolic = NULL;
    klu_numeric *Numeric = NULL;
    klu_common Common ;
    int i ;
    klu_defaults (&Common) ;
    Symbolic = klu_analyze (n, Ap, Ai, &Common) ;
    Numeric = klu_factor (Ap, Ai, Ax, Symbolic, &Common) ;
    int lnz = Numeric->lnz;
    int unz = Numeric->unz;
    int nzoff = Numeric->nzoff;
    int ok ;
        std::vector<int> Lp(n + 1);
        std::vector<int> Up(n + 1);
        std::vector<double> Lx(lnz);
        std::vector<int> Li(lnz);
        std::vector<double> Ux(unz);
        std::vector<int> Ui(unz);
        int success = klu_extract(Numeric, Symbolic,
                              Lp.data(), Li.data(), Lx.data(),
                              Up.data(), Ui.data(), Ux.data(),
                              NULL, NULL, NULL,
                              NULL, NULL, NULL, NULL,
                              &Common);
    if (success) {
        printf("klu_extract succeeded!\n");
        std::cout << "Lp & Li & Lx:" << std::endl;
        print_array_int(Lp.data(), n + 1);
        print_array_int(Li.data(), lnz);
        print_array_double(Lx.data(), lnz);
        std::cout << "Up & Ui & Ux:" << std::endl;
        print_array_int(Up.data(), n + 1);
        print_array_int(Ui.data(), unz);
        print_array_double(Ux.data(), unz);
        // std::cout << "Fp & Fi & Fx:" << std::endl;
        // print_array_int(Fp.data(), n + 1);
        // print_array_int(Fi.data(), nzoff);
        // print_array_double(Fx.data(), nzoff);
        FILE *file;
        file = fopen("L.txt", "w");
        if (file == NULL) {
            printf("Error opening the file.\n");
        return 1;
        }
        write_base(file, n + 1, lnz, lnz);
        write_int_array(file, Lp.data(), n + 1);
        write_int_array(file, Li.data(), lnz);
        write_double_array(file, Lx.data(), lnz);
        // Your code to use the extracted factors
    } else {
        printf("klu_extract failed!\n");
    }
    

    std::cout << Numeric->lnz << std::endl;

    // // Output L and U
    // if (Numeric != NULL && Numeric->Lip != NULL && Numeric->LUbx != NULL) {
    //     print_matrix("L", Numeric->n, Numeric->Lip, Numeric->LUbx);
    //     print_matrix("U", Numeric->n, Numeric->Uip, Numeric->LUbx);
    // } else {
    //     printf("Numeric or its components are NULL\n");
    // }
    
    klu_solve (Symbolic, Numeric, 5, 1, b, &Common) ;
    klu_free_symbolic (&Symbolic, &Common) ;
    klu_free_numeric (&Numeric, &Common) ;
    for (i = 0 ; i < n ; i++) printf ("x [%d] = %g\n", i, b [i]) ;
    return (0) ;
}
