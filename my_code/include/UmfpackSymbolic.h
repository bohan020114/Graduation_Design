/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-30 15:25:29
 * @LastEditTime: 2024-03-30 17:00:00
 * @LastEditors:  
 */
#ifndef UMFPACKSYMBOLIC_H
#define UMFPACKSYMBOLIC_H

#include <iostream>
#include <umfpack.h>
#include <vector>

void MatrixDataProcessUmfpack(const std::vector<double>& values,
                        const std::vector<SuiteSparse_long>& row_indices,
                        const std::vector<SuiteSparse_long>& col_indices,
                        SuiteSparse_long num_nonzeros,
                        SuiteSparse_long num_rows,
                        SuiteSparse_long num_cols,
                        SuiteSparse_long matrix_dim,
                        const std::vector<double>& right_vec) {
    if (values.size() != num_nonzeros || row_indices.size() != num_nonzeros || col_indices.size() != num_nonzeros) {
        std::cerr << "Error: Sizes of input arrays do not match num_nonzeros." << std::endl;
        return;
    }
    double ans_value[matrix_dim];
    
}

#endif // UMFPACKSYMBOLIC_H
