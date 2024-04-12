/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-04-10 18:41:16
 * @LastEditTime: 2024-04-11 17:04:26
 * @LastEditors:  
 */
#ifndef WRITE_LU_IN_SRC_H
#define WRITE_LU_IN_SRC_H

#include <stdio.h>

void write_base(FILE *file, int p_len, int i_len, int x_len){
    fprintf(file, "LU_case; 2023; BohanWang\n");
    int total = int(p_len / 6) + int(i_len / 6) + int(x_len / 4) + 3;
    fprintf(file, "%12d", total);
    fprintf(file, "%12d", int(p_len / 6) + 1);
    fprintf(file, "%12d", int(i_len / 6) + 1);
    fprintf(file, "%12d\n", int(x_len / 4) + 1);
    fprintf(file, "rsa%21d%12d%12d\n", p_len, p_len, x_len);
    fprintf(file, "                  (6I12)      (6I12)     (4E9.9)  \n" );
}

void write_int_array(FILE *file, const int *array, int length) {
    for (int i = 0; i < length; ++i) {
        fprintf(file, "%10d", array[i]);
        if ((i + 1) % 6 == 0) {
            fprintf(file, "\n");
        }
    }
    if (length % 6 != 0) {
        fprintf(file, "\n");
    }
}

void write_double_array(FILE *file, const double *array, int length) {
    for (int i = 0; i < length; ++i) {
        fprintf(file, "%16.2f", array[i]);
        if ((i + 1) % 4 == 0) {
            fprintf(file, "\n");
        }
    }
    if (length % 4 != 0) {
        fprintf(file, "\n");
    }
}

#endif /* WRITE_LU_IN_SRC_H */
