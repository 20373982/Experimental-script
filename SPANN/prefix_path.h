//
// Created by 郑荘霖 on 2024/4/26.
//
# include <string>

using namespace std;
#ifndef SPANN_PREFIX_PATH_H
#define SPANN_PREFIX_PATH_H

string prefix_path() {
    //如果当前操作系统是windows返回"../",否则返回"./"
#if defined(_WIN32) || defined(_WIN64)
    return "../";
#else
    return "./";
#endif
}

#endif //SPANN_PREFIX_PATH_H
