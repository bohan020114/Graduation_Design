<!--
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-03-16 14:54:54
 * @LastEditTime: 2024-03-18 13:04:09
 * @LastEditors:  
-->
This dictionary provides matrices of two cases, the smaller one is case2, the bigger one is case1.
Case1_1 and case1_2 are matrices belong to case1, case2_1 and case2_2 are matrices belong to case2.

The dim of case1 is 867713.
The dim of case2 is 125180.

We print matrix in the form of CSR(Compressed Sparse Row format).

You cound see statements in the following format in any matrix file:
"(j:m,jcol:m,i:x,irow:y)     D"

this means the value of y-row and m-column of the matrix equals to D before ordering,
also the value of x-row and m-column of the matrix equals to D after ordering.

这个字典提供了两种情况下的矩阵，其中较小的是 case2，较大的是 case1。
Case1_1 和 case1_2 是属于 case1 的矩阵，case2_1 和 case2_2 是属于 case2 的矩阵。

Case1 的维度是 867713。
Case2 的维度是 125180。

我们以 CSR（Compressed Sparse Row format）格式打印矩阵。

在任何矩阵文件中，您可以看到以下格式的语句：
"(j:m,jcol:m,i:x,irow:y) D"

这表示在排序之前，矩阵的第 y 行和第 m 列的值等于 D，
同时在排序之后，矩阵的第 x 行和第 m 列的值也等于 D。

