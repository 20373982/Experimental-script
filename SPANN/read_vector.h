//
// Created by 郑荘霖 on 2024/4/25.
//
#include<bits/stdc++.h>
#include <string>

#ifdef __linux__
#include "monitor.h"
#endif

using namespace std;

#ifndef SPANN_READ_VECTOR_H
#define SPANN_READ_VECTOR_H
vector<vector<float>> vectors;


class read_vector {
public:

    vector<float> priority_queue_vector;
    vector<float> violence_vector;
    int dim;

    explicit read_vector(const string &filename, const int dim, const int N) {
        this->dim = dim;
        ifstream file(filename, ios::in);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file" << filename << endl;
            return;
        }
        string line;
        int index = 0;
        while (getline(file, line)) {
            vector<float> vector = this->parse_query(line);
            vectors.push_back(vector);
            index++;
            if (index == N) {
                break;
            }
        }
        file.close();
    }

    void get_nearest_neighbors_priority_queue(string q, int k, int &usedMemory, bool out = false) {
        // 解析查询向量
        vector<float> vq = this->parse_query(q);
        // 遍历vectors获取距离
        priority_queue<pair<float, int>, vector<pair<float, int>>, less<>> distances;
        for (size_t i = 0; i < vectors.size(); i++) {
            float distance = this->distance(vq, vectors[i]);
            // 利用priority_queue存储距离最小的k个向量
            if (distances.size() < k) {
                distances.push(make_pair(distance, i));
            } else if (distance < distances.top().first) {
                distances.pop();
                distances.push(make_pair(distance, i));
            }
        }
        this->get_used_memory(usedMemory);
        // 遍历distances输出索引对应的向量
        while (!distances.empty()) {
            vector<float> vec = vectors[distances.top().second];
            this->priority_queue_vector.push_back(distances.top().first);
            // 输出vec中的每个浮点数，以空格分隔
            if (out) {
                print_vector(vec);
            }
            distances.pop();
        }
        this->get_used_memory(usedMemory);
    }

    void get_nearest_neighbors_violence(string q, int k, int& usedMemory, bool out = false) {
        // 解析查询向量
        vector<float> vq = this->parse_query(q);
        // 遍历vectors获取距离
        vector<pair<float, int>> distances;
        for (size_t i = 0; i < vectors.size(); i++) {
            float distance = this->distance(vq, vectors[i]);
            distances.push_back(make_pair(distance, i));
        }
        // distances按照距离排序
        sort(distances.begin(), distances.end(),
             [](const pair<float, int> &a, const pair<float, int> &b) {
                 return a.first < b.first;
             });
        this->get_used_memory(usedMemory);
        // 输出distances中的前k个向量
        for (int i = 0; i < k; i++) {
            vector<float> vec = vectors[distances[i].second];
            this->violence_vector.push_back(distances[i].first);
            // 输出vec中的每个浮点数，以空格分隔
            if (out) {
                print_vector(vec);
            }
        }
        this->get_used_memory(usedMemory);
    }

    // 计算vector之间的距离
    float distance(const vector<float> &v1, const vector<float> &v2) {
        float sum = 0;
        for (int i = 0; i < v1.size(); i++) {
            sum += pow(v1[i] - v2[i], 2);
        }
        return sqrt(sum);
    }

    //解析查询向量
    vector<float> parse_query(string q) {
        istringstream iss(q);
        vector<float> vq;
        float value;
        int index = 0;
        while (iss >> value) {
            vq.push_back(value);
            iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            index++;
            if (index == this->dim) {
                break;
            }
        }
        return vq;
    }

    // 判断两个算法结果是否相同
    bool is_same(vector<float> v1, vector<float> v2) {
        // 将v1,v2进行排序
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        if (v1.size() != v2.size()) {
            return false;
        }
        for (int i = 0; i < v1.size(); i++) {
            if (v1[i] != v2[i]) {
                return false;
            }
        }
        return true;
    }

    // 输出vector向量
    void print_vector(vector<float> v) {
        for (auto i: v) {
            cout << i << " ";
        }
        cout << "\n";
    }

    //统计使用内存
    int get_used_memory(int &usedMemory) {
#ifdef __linux__
        watchSolutionOnce(getpid(), usedMemory);
#endif
        return 0;
    }

};

#endif //SPANN_READ_VECTOR_H
