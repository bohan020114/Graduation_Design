/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-05-07 00:49:53
 * @LastEditTime: 2024-05-13 14:25:42
 * @LastEditors:  
 */
#ifndef MYLU_H
#define MYLU_H

#include <iostream>
#include <vector>
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

public:
    // 构造函数
    DoublyCircularLinkedList() : head(nullptr) {}
    
    // 插入节点到双向循环链表末尾
    void insert(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            // 空链表的情况
            head = newNode;
            head->prev = head;
            head->next = head; // 形成双向循环
        } else {
            // 非空链表的情况，找到尾部节点
            Node* tail = head->prev; // 尾节点是头节点的前驱节点
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
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

        Node* current = head->prev; // 初始指向尾节点
        cout << "Circular Linked List (Reverse Order): ";
        do {
            cout << current->data << " ";
            current = current->prev;
        } while (current != head->prev); // 循环直到回到尾节点
        cout << endl;
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
        head = nullptr;
    }
};

// Function to solve Lx = A(:, k)
vector<double> solveLx(const vector<int>& Ai, const vector<double>& Av, // 目标列
                    const vector<int>& Xi, const vector<double>& Xv, // 操作列
                    std::vector<int>& Bi, std::vector<int>& Bv, // 保存返回列
                    int k, int n){ // K是标记运算的位置，n是矩阵的长宽
    // 建立常数值
    int X_J = Xv[k];
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
    }
    // 检查Bi与Bv长度是否相同，验证通过后可删除
    





    // 建立哈希表，用于快速查找 Xi 中的元素（位置信息）
    std::unordered_map<int, int> indexMap;
    for (int i = 0; i < Xi.size(); ++i) {
        indexMap[Xi[i]] = i;
    }
    
    // 初始化结果数组 Bi 和 Bv
    Bi.clear();
    Bv.clear();
    
    // 遍历位置信息 k 内的循环
    for (int j = k; j <= n; ++j) {

        int currentXi = j;  // 当前位置 j 对应的 Xi 中的元素
        int currentValue = Xv[j];  // 当前位置 j 对应的 Xv 中的值

        // 在 Xi 中查找当前位置 j 对应的元素是否存在
        auto it = indexMap.find(currentXi);
    

    vector<double> x(N, 0.0); // Initialize x with zeros
    for (int i = 0; i < N; ++i) {
        x[i] = A[i][k]; // Initialize x with A(:, k)
    }

    // Perform forward substitution
    for (int j = 0; j < k; ++j) {
        double Ljk = L[j][k]; // Get L(j, k)
        if (Ljk != 0.0) {
            for (int i = j + 1; i < N; ++i) {
                x[i] -= Ljk * x[j]; // Update x(i) using L(j, k)
            }
        }
    }

    return x;
}

int perform_lu_decomposition_Parallel(int n, int *Ap, int *Ai, double *Ax) {
    std::cout << "In perform_lu_decomposition_Parallel" << std::endl;
    // 首先，初始化L（并未等于I）
    std::vector<std::vector<int>> Li_pos(n); // 填入元素的位置（横坐标）
    std::vector<std::vector<double>> Lx_number(n); // 元素值
    std::vector<int> Lp_half(n, 0); 
    std::vector<std::vector<int>> final(n, std::vector<int>(n));
    
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
        lay_on[1].displayReverse();
        int num = lay_on[1].countElements();
        cout << "num:" << num << endl;
    }

    // check!!

    
    


    






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
