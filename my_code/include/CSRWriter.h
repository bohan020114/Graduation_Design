/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-04-10 02:15:29
 * @LastEditTime: 2024-04-10 02:24:02
 * @LastEditors:  
 */
#ifndef CSR_WRITER_H
#define CSR_WRITER_H

#include <fstream>
#include <tuple>
#include <string>

class CSRWriter {
public:
    static void WriteToTextFiles(int* Ap, int* Ai, double* Ax, int row_num, int row_pos) {
        // 定义文件名
        const std::string ap_filename = "Ap.txt";
        const std::string ai_filename = "Ai.txt";
        const std::string ax_filename = "Ax.txt";
        // 写入到文件
        std::ofstream ap_file(ap_filename);
        for (int i = 0; i < row_num; ++i) {
            ap_file << Ap[i] << std::endl;
        }
        ap_file.close();

        std::ofstream ai_file(ai_filename);
        for (int i = 0; i < row_pos; ++i) {
            ai_file << Ai[i] << std::endl;
        }
        ai_file.close();

        std::ofstream ax_file(ax_filename);
        ax_file << std::fixed << std::setprecision(9); // 设置输出格式为九位小数
        for (int i = 0; i < row_pos; ++i) {
            ax_file << Ax[i] << std::endl;
        }
        ax_file.close();
    }
};

#endif // CSR_WRITER_H
