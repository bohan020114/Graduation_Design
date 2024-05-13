'''
Description: 
Author: Bohan Wang
Date: 2024-05-12 18:56:48
LastEditTime: 2024-05-13 06:00:08
LastEditors:  
'''
import numpy as np

def lu_decomposition(A):
    n = A.shape[0]
    L = np.eye(n)
    U = A.copy()
    
    for i in range(n):
        for j in range(i+1, n):
            L[j, i] = U[j, i] / U[i, i]
            U[j, :] = U[j, :] - L[j, i] * U[i, :]
    
    return L, U

# 定义 4x4 矩阵 A
A = np.array([
    [2, 1, 2, 1],
    [0, 3, 1, 0],
    [0, 1, 9, 0],
    [4, 2, 0, 8]
], dtype=float)

L, U = lu_decomposition(A)

print("Lower triangular matrix L:")
print(L)
print("Upper triangular matrix U:")
print(U)
