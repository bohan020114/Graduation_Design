/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-05-07 00:49:53
 * @LastEditTime: 2024-05-14 00:48:21
 * @LastEditors:  
 */
#ifndef MYLU_H
#define MYLU_H

#include <iostream>
#include <vector>
#include <omp.h> 
#include "Timer.h"
using namespace std;

struct ElementInfo {
    int index;
    double value;
};

// 定义双向循环链表节点类
class Node {
public:
    int data;
    Node* prev;
    Node* next;

    // 构造函数
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// 定义双向循环链表类
class DoublyCircularLinkedList {
private:
    Node* head; // 头指针
    Node* tail;

public:
    // 构造函数
    DoublyCircularLinkedList() : head(nullptr), tail(nullptr) {}
    
    // 插入节点到双向循环链表末尾
    void insert(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            // 空链表的情况
            head = newNode;
            head->prev = head;
            head->next = head; // 形成双向循环
            tail = head; // 更新尾节点
        } else {
            // 非空链表的情况，在尾部插入新节点
            newNode->prev = tail;
            newNode->next = head;
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode; // 更新尾节点
        }
    }

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* start) : current(start) {}

        int& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };


    // 定义 begin() 函数返回迭代器指向第一个节点
    Iterator begin() const {
        return Iterator(head);
    }

    // 定义 end() 函数返回迭代器指向尾后位置
    Iterator end() const {
        return Iterator(head); // 尾后位置指向头节点
    }
    
    // 计算双向循环链表中的总元素数量
    int countElements() const {
        if (head == nullptr) {
            return 0; // 空链表
        }

        int count = 0;
        Node* current = head;
        do {
            count++;
            current = current->next;
        } while (current != head);

        return count;
    }

    // 打印循环链表（逆序）
    void displayReverse() {
        if (head == nullptr) {
            cout << "Circular Linked List is empty." << endl;
            return;
        }

        Node* current = tail; // 初始指向尾节点
        cout << "Circular Linked List (Reverse Order): ";
        do {
            cout << current->data << " ";
            current = current->prev;
        } while (current != head); // 循环直到回到头节点
        cout << endl;
    }

    // 返回链表中的最小元素
    int findMin() const {
        if (!head) {
            std::cerr << "Error: List is empty" << std::endl;
            return std::numeric_limits<int>::max(); // 返回 int 类型的最大值
        }

        Node* current = head;
        int minValue = std::numeric_limits<int>::max(); // 初始值设为 int 类型的最大值

        do {
            if (current->data < minValue) {
                minValue = current->data;
            }
            current = current->next;
        } while (current != head);

        return minValue;
    }
    
    // 获取链表头节点
    Node* getHead() const {
        return head;
    }

    // 获取链表尾节点
    Node* getTail() const {
        return tail;
    }

    // 返回链表头节点的值
    int getHeadValue() const {
        if (head) {
            return head->data;
        }
        // 如果链表为空，返回一个极大值
        return std::numeric_limits<int>::max();
    }
    
    // 释放链表内存
    ~DoublyCircularLinkedList() {
        if (head == nullptr) {
            return;
        }

        Node* current = head;
        Node* temp;
        do {
            temp = current;
            current = current->next;
            delete temp;
        } while (current != head);

        head = nullptr; // 将 head 置为空指针
    }
};

// Function to solve Lx = A(:, k)
void solveLx(const vector<int>& Ai, const vector<double>& Av, // 目标列
             vector<int>& Xi, vector<double>& Xv, // 操作列
             int k){ // K是标记运算的位置，n是矩阵的长宽
    std::vector<int> Bi;
    std::vector<double> Bv; // 保存返回列
    int line = -1;
    for (size_t i = 0; i < Xi.size(); ++i) {
        if (Xi[i] == k) {
            line = i;
            break;
        }
    }
    if(line == -1){
        std::cerr << "line = -1" << std::endl;
        return;
    }
    // 建立常数值
    int X_J = Xv[line];
    // 建立哈希表，用于快速查找 Ai 和 Xi 中的元素及其索引和值
    std::unordered_map<int, ElementInfo> indexMap_Ai;
    for (int i = 0; i < Ai.size(); ++i) {
        indexMap_Ai[Ai[i]] = {i, Av[i]};
    }
    std::unordered_map<int, ElementInfo> indexMap_Xi;
    for (int i = 0; i < Xi.size(); ++i) {
        indexMap_Xi[Xi[i]] = {i, Xv[i]};
    }
    // 清空数组 Bi
    Bi.clear();  
    // 合并 Xi 和 Ai 的元素到 Bi 中
    for (int x : Xi) {
        Bi.push_back(x);
    }
    for (int a : Ai) {
        Bi.push_back(a);
    }
    // 对 Bi 数组进行排序，从小到大
    std::sort(Bi.begin(), Bi.end());
    // 移除重复元素，保留唯一元素
    Bi.erase(std::unique(Bi.begin(), Bi.end()), Bi.end());
    // 清空原始的 Xi 和 Xv
    Xi.clear();
    Xv.clear();
    for (int num : Bi) {
        bool isInAi = (indexMap_Ai.find(num) != indexMap_Ai.end());
        bool isInXi = (indexMap_Xi.find(num) != indexMap_Xi.end());
        // 根据检查结果执行不同的操作
        if (isInAi && isInXi) {
            // 如果 num 同时在 Ai 和 Xi 中存在
            int indexAi = indexMap_Ai.at(num).index;
            int indexXi = indexMap_Xi.at(num).index;
            double valueAv = Av[indexAi];
            double valueXv = Xv[indexXi];
            Bv.push_back(valueXv - valueAv * X_J);
        } else if (isInAi) {
            // 如果 num 在 Ai 中存在，但不在 Xi 中
            int indexAi = indexMap_Ai.at(num).index;
            double valueAv = Av[indexAi];
            Bv.push_back(-valueAv * X_J);
        } else if (isInXi) {
            // 如果 num 在 Xi 中存在，但不在 Ai 中
            int indexXi = indexMap_Xi.at(num).index;
            double valueXv = Xv[indexXi];
            Bv.push_back(valueXv);
        } else {
            // 如果 num 在 Ai 和 Xi 中都不存在，可以添加默认的处理操作
            std::cout << "ERROR: Bi WORNING" << num << " is not found in Ai or Xi" << std::endl;
            // 在这里添加针对不存在情况的处理代码
        }
        // 将 num 加入到 Xi 中
        Xi.push_back(num);
        // 将对应的 Bv 值加入到 Xv 中
        Xv.push_back(Bv.back()); // 添加刚刚加入的 Bv 的最后一个元素
    }
    // 检查Xi与Xv长度是否相同，验证通过后可删除
    if (Xi.size() != Xv.size()) {
        std::cout << "ERROR: Xi&Xv WORNING: Do Not Match!" << std::endl;
        return;
    }
    // 检查Bi与Bv长度是否相同，验证通过后可删除
    if (Bi.size() != Bv.size()) {
        std::cout << "ERROR: Bi&Bv WORNING: Do Not Match!" << std::endl;
        return;
    }
    // 检查Bi与Xi长度是否相同，验证通过后可删除
    if (Bi.size() != Xi.size()) {
        std::cout << "ERROR: Bi&Bv WORNING: Do Not Match!" << std::endl;
        return;
    }
}

void LUdivision(vector<double>& Xv, vector<int>& Xi, int k){
    int line = -1;
    for (size_t i = 0; i < Xi.size(); ++i) {
        if (Xi[i] == k) {
            line = i;
            break;
        }
    }
    if(line == -1){
        std::cerr << "line = -1" << std::endl;
        return;
    }
    // 遍历 Xi 向量
    // U的对角线列没加！！
    for (int j = line; j < Xi.size(); ++j) {
        if (Xv[line] != 0.0) {
            Xv[j] /= Xv[line];
        } else {
            std::cerr << "Error: Division by zero" << std::endl;
            return;
        }
        
    }
}

void processRange(std::vector<int>& Ai,std::vector<double>& Av, int start, int end) {
    std::vector<int> Xi;
    std::vector<double> Xv;
    // 将 Ai 数组中的元素存入 Xi 向量
    for (int i = start; i < end; ++i) {
        Xi.push_back(Ai[i]);
    }
    // 将 Av 数组中的元素存入 Xv 向量
    for (int i = start; i < end; ++i) {
        Xv.push_back(Av[i]);
    }
    // 调用 LUdivision 函数处理 Xi 和 Xv
    int k = 0; // 假设 k 是某个值，需要根据实际情况设定
    LUdivision(Xv, Xi, k);
}

// 返回所有头节点中值最小的链表的头节点值
int minHeadValue(DoublyCircularLinkedList lay_on[], int n) {
    int minVal = std::numeric_limits<int>::max();
    int minIndex = -1;

    for (int i = 0; i < n; ++i) {
        int headValue = lay_on[i].getHeadValue();
        if (headValue < minVal) {
            minVal = headValue;
            minIndex = i;
        }
    }
    // std::cout << minIndex << std::endl;
    // 返回最小值对应的链表的头节点值
    return lay_on[minIndex].getHeadValue();
}

// 将稀疏矩阵数据转换为 vector 形式
void convertToVectors(int n, int *Ap, int *Ai, double *Ax,
                      std::vector<int> &ap_vec,
                      std::vector<int> &ai_vec,
                      std::vector<double> &ax_vec) {
    // 将 Ap 转换为 vector
    ap_vec.clear();
    for (int i = 0; i <= n; ++i) {
        ap_vec.push_back(Ap[i]);
    }

    // 将 Ai 转换为 vector
    ai_vec.clear();
    for (int i = 0; i < Ap[n]; ++i) {
        ai_vec.push_back(Ai[i]);
    }

    // 将 Ax 转换为 vector
    ax_vec.clear();
    for (int i = 0; i < Ap[n]; ++i) {
        ax_vec.push_back(Ax[i]);
    }
}

void IntoXforPRE(const std::vector<int>& ap_vec, const std::vector<int>& ai_vec,
                const std::vector<double>& ax_vec, int j,
                std::vector<double>& Xv, std::vector<int>& Xi) {// j对应变化列，i对应左侧固定列

    // Extract data for Xv and Xi based on j
    int pos_j = ap_vec[j + 1] - ap_vec[j];
    int start_index_j = ap_vec[j];
    Xi.clear();
    Xv.clear();
    for (int k = 0; k < pos_j; ++k) {
        Xi.push_back(ai_vec[start_index_j + k]);
        Xv.push_back(ax_vec[start_index_j + k]);
    }
}

void IntoAforPRE(const std::vector<int>& ap_vec, const std::vector<int>& ai_vec,
                const std::vector<double>& ax_vec, int i,
                std::vector<double>& Av, std::vector<int>& Ai) {// j对应变化列，i对应左侧固定列
    // Extract data for Av and Ai based on i
    int pos_i = ap_vec[i + 1] - ap_vec[i];
    int start_index_i = ap_vec[i];
    Ai.clear();
    Av.clear();
    for (int k = 0; k < pos_i; ++k) {
        Ai.push_back(ai_vec[start_index_i + k]);
        Av.push_back(ax_vec[start_index_i + k]);
    }
}

// 将双向链表中的数据存入数组
std::vector<int> extractDataToArray(DoublyCircularLinkedList lay_on[], int i) {
    std::vector<int> dataArray;
    Node* head = lay_on[i].getHead();
    if (head == nullptr)
        return dataArray; // 如果链表为空，直接返回空数组

    Node* current = head;

    do {
        dataArray.push_back(current->data);
        current = current->next;
    } while (current != head);

    return dataArray;
}

int perform_lu_decomposition_Parallel_noParallel(int n, int *Ap, int *Ai, double *Ax) {
    std::cout << "In perform_lu_decomposition_Parallel" << std::endl;
    // 首先，初始化L（并未等于I）
    // std::vector<std::vector<int>> Li_pos(n); // 填入元素的位置（横坐标）
    // std::vector<std::vector<double>> Lx_number(n); // 元素值
    // std::vector<int> Lp_half(n, 0); 
    // std::vector<std::vector<int>> final(n, std::vector<int>(n));
    // 定义存储转换后数据的 vector
    std::vector<int> ap_vec;
    std::vector<int> ai_vec;
    std::vector<double> ax_vec;

    // 将稀疏矩阵数据转换为 vector 形式
    convertToVectors(n, Ap, Ai, Ax, ap_vec, ai_vec, ax_vec);
    Timer timer_relay;
    // 建立依赖关系
    DoublyCircularLinkedList lay_on[n];
    // 将数据插入循环链表
    for (int j_size = 1; j_size < n; ++j_size) {
        for (int i_size = Ap[j_size - 1]; i_size < Ap[j_size]; ++i_size) {
            lay_on[j_size - 1].insert(Ai[i_size]);
        }
    }
    std::cout << "relay time: " << timer_relay.elapsed() << " seconds" << std::endl;

    // 打印循环链表
    for (int i = 0; i < 1; ++i) {
        cout << "Chain " << "2: ";
        lay_on[0].displayReverse();
        int num = lay_on[0].countElements();
        cout << "num:" << num << endl;
    }

    // check!!
    unsigned int num_threads = std::thread::hardware_concurrency(); // Get number of hardware threads
    
    for (int i = 0; i < n; ++i){
        std::vector<double> Av;
        std::vector<int> Ai;
        std::vector<int> layon;
        IntoAforPRE(ap_vec, ai_vec, ax_vec, i, Av, Ai);
        LUdivision(Av, Ai, i);
        cout << i << endl;
        if(i == 0)  continue;
        layon = extractDataToArray(lay_on, i);
        // 并行处理
        // 使用 OpenMP 进行并行计算
        omp_set_num_threads(4);
        #pragma omp parallel for
        for (int i = 0; i < layon.size(); ++i) {
            int j = layon[i];
            std::vector<double> Xv;
            std::vector<int> Xi;
            IntoXforPRE(ap_vec, ai_vec, ax_vec, j, Xv, Xi);
            // 在这里调用 solveLx，并行化处理每个 j
            solveLx(Ai, Av, Xi, Xv, j);
            // std::cout << "Thread for j = " << j << " finished." << std::endl;
        }
    }

   
    // // 遍历每一行的非零元素范围
    // for (int i = 0; i < n; ++i) {
    //     int start = Ap[i]; // 当前行的起始索引
    //     int end = Ap[i + 1]; // 当前行的结束索引
    //     // 处理当前范围
    //     processRange(AiVec, AxVec, start, end);
    // }




    
    // 找到头节点值最小的链表的头节点值并输出
    int minValue = minHeadValue(lay_on, n);
    std::cout << "Minimum head node value: " << minValue << std::endl;
    

    // std::cout << "Min Element: " << minElement << std::endl;
    
    // solve Lx = A(:, k)
    
    
    
    


    






    // // 初始化 Li_pos 中每行的长度
    // for (int i = 0; i < n; ++i) {
    //     int row_length = Ap[i + 1] - Ap[i];
    //     Li_pos[i].resize(row_length);  // 设置每行的长度
    // }
    
    // for (int j_size = 1; j_size < n + 1; ++j_size) {
    //     for (int i_size = 0; i_size < Ap[j_size] - Ap[j_size - 1]; ++i_size) {
    //         // 计算 Ai 中的索引
    //         int Ai_index = Ap[j_size - 1] + i_size;
    //         // 将 Ai[Ai_index] 的值传递给 Li_pos[j_size - 1][i_size]
    //         Li_pos[j_size - 1][i_size] = Ai[Ai_index];
    //     }
    // }


    return 0;
    
}

#endif
