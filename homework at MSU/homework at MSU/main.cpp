//
//  main.cpp
//  find
//
//  Created by Дмитрий Голубев on 11.09.2022.
//

#include <iostream>
#include <vector>
using namespace std;

vector<int>generateVector(size_t size)
{
    vector<int> V(size, 0);
    srand(int(time(0)));
    generate(V.begin(), V.end(), []() {
        return rand();
    });
    return V;
}

int myFind(vector<int> v, int x) {
    auto start = std::chrono::steady_clock::now();
    int i = 0;
    while (i < v.size() && v[i] != x){
        i++;
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "результат обычного поиска в векторе с размером " << v.size() <<  " " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mks" << std::endl;
    if (i == v.size()) {
        return -1;
    } else {
        return i;
    }
}

int myBarrierFind(vector<int> v, int x){
    auto start = std::chrono::steady_clock::now();
    int i = 0;
    v[v.size()] = x;
    while (v[i]!=x) {
        i++;
    }
    auto end = std::chrono::steady_clock::now();
    
    std::cout << "результат поиска с барьером в векторе с размером " << v.size() <<  " " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mks" << std::endl;
    return i == v.size() - 1? -1: i;
}

void testFind(size_t size){
    vector<int> testVector = generateVector(size);
    int x = rand();

    myFind(testVector, x);
    myBarrierFind(testVector, x);
}

int main() {
    int size = 100;
    for (int i = 0; i < 7; i++){
        size*= 10;
        testFind(size);
    }
    return 0;
}

