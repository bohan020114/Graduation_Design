/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-05-13 23:00:30
 * @LastEditTime: 2024-05-13 23:00:33
 * @LastEditors:  
 */
#include <iostream>
#include <omp.h>

int main() {
    // 获取系统支持的最大线程数
    int max_threads = omp_get_max_threads();

    std::cout << "Max threads supported by system: " << max_threads << std::endl;

    return 0;
}
