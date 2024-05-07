# 分别为k,n,D,N
import copy
import os

info = {
    'k': 0,
    'n': 1,
    'D': 2,
    'N': 3,
}
default = [10, 10, 1300, 50000]
scope = {
    'k': [1, 10, 50, 100, 200],
    'n': [5, 10, 30, 50, 100],
    'D': [50, 100, 500, 1000, 1300],
    'N': [1000, 5000, 10000, 50000, 90000],
}


def generateData():
    global info, default, scope
    for key in scope.keys():
        no = info[key]
        lst = scope[key]
        tmp = copy.deepcopy(default)
        for i in range(len(lst)):
            tmp[no] = lst[i]
            tmpPath = f'../SPANN/data/{key}_{i}_param_{tmp[0]}_{tmp[1]}_{tmp[2]}_{tmp[3]}'
            if not os.path.exists(tmpPath):
                os.mkdir(tmpPath)
            tmpFilePath = tmpPath + '/data_0.dat'
            with open(tmpFilePath, 'w') as f:
                f.write(f"{tmp[0]} {tmp[1]} {tmp[2]} {tmp[3]}")


if __name__ == '__main__':
    generateData()
