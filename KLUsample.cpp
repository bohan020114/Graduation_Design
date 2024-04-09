/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-04-09 21:52:31
 * @LastEditTime: 2024-04-10 00:51:48
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
#include "klu.h"

int    n = 5 ;
int    Ap [ ] = {0, 2, 5, 9, 10, 12} ;
int    Ai [ ] = { 0,  1,  0,   2,  4,  1,  2,  3,   4,  2,  1,  4} ;
double Ax [ ] = {2., 3., 3., -1., 4., 4., -3., 1., 2., 2., 6., 1.} ;
double b [ ] = {8., 45., -3., 3., 19.} ;

int main (void)
{
    int size_of_Ap = sizeof(Ap) / sizeof(Ap[0]);
    int size_of_Ai = sizeof(Ai) / sizeof(Ai[0]);
    int size_of_Ax = sizeof(Ax) / sizeof(Ax[0]);
    std::cout << size_of_Ap << " " << size_of_Ai << " " << size_of_Ax << std::endl;
    klu_symbolic *Symbolic ;
    std::cout << Symbolic->n << std::endl;
    std::cout << Symbolic->do_btf << std::endl;
    klu_numeric *Numeric ;
    klu_common Common ;
    int i ;
    klu_defaults (&Common) ;
    Symbolic = klu_analyze (n, Ap, Ai, &Common) ;
    Symbolic->do_btf = 0;
    std::cout << Symbolic->do_btf << std::endl;
    std::cout << Symbolic->n << std::endl;
    std::cout << Symbolic->structural_rank << std::endl;
    Numeric = klu_factor (Ap, Ai, Ax, Symbolic, &Common) ;
    klu_solve (Symbolic, Numeric, 5, 1, b, &Common) ;
    klu_free_symbolic (&Symbolic, &Common) ;
    klu_free_numeric (&Numeric, &Common) ;
    for (i = 0 ; i < n ; i++) printf ("x [%d] = %g\n", i, b [i]) ;
    return (0) ;
}

