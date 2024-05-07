#include <string>
#include "read_vector.h"

#ifdef __linux__
#include "monitor.h"
#endif

#ifdef __linux__
program_t begProg, endProg;
program_t begProg_baseline, endProg_baseline;
#endif

using namespace std;

int main(int argc, char *argv[]) {
    // 读入参数
    string parameter_file = argv[1];
    string prefix = argv[2];
    ifstream file_arg(parameter_file);
    if (!file_arg.is_open()) {
        std::cerr << "Error opening file: " << parameter_file << std::endl;
        return 1;
    }
    vector<int> parameters;
    int parameter;
    while (file_arg >> parameter) {
        parameters.push_back(parameter);
    }
    int k = parameters[0];
    int n = parameters[1];
    int D = parameters[2];
    int N = parameters[3];
    const string filename = prefix + "/enron/enron_dataset.txt";
    read_vector reader(filename, D, N);
    const string target = prefix + "/enron/enron_query.txt";
    ifstream file(target, ios::in);
    ifstream file_baseline(target, ios::in);
    string query;
    int index = 0, usedMemory = 0;
#ifdef __linux__
    save_time(begProg_baseline);
#endif
    while (getline(file_baseline, query)) {
        reader.get_nearest_neighbors_brute_force(query, k, usedMemory);
        index++;
        if (index == n) break;
    }
#ifdef __linux__
    watchSolutionOnce(getpid(), usedMemory);
    save_time(endProg_baseline);
    double usedTime = calc_time(begProg_baseline, endProg_baseline);
    printf("LinearScan %.6lf %d\n", usedTime, usedMemory/1024);
#endif
    index = 0, usedMemory = 0;
#ifdef __linux__
    save_time(begProg);
    usedMemory = 0;
#endif
    while (getline(file, query)) {
        reader.get_nearest_neighbors_priority_queue(query, k, usedMemory);
        index++;
        if (index == n) break;
    }
#ifdef __linux__
    watchSolutionOnce(getpid(), usedMemory);
    save_time(endProg);
    usedTime = calc_time(begProg, endProg);
    printf("HeapKNN %.6lf %d\n", usedTime, usedMemory/1024);
#endif
    //cout << "query result: " << reader.is_same(reader.priority_queue_vector, reader.brute_force_vector) << "\n";
    file.close();
    file_baseline.close();
    return 0;
}