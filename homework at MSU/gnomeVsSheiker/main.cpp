//
//  main.cpp
//  156335
//
//  Created by Дмитрий Голубев on 11.09.2022.
//

#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

vector<int>generateVector(size_t size)
{
    vector<int> V(size, 0);
    random_device rd;
    mt19937 gen(rd());
    generate(V.begin(), V.end(), gen);
    return V;
}

void sheikerSort(std::vector<int> &vect) {
    int exc_count = 0, com_count = 0;
        bool check = 1;
        while (check != 0)
        {
            check = 0;
            int r = int(vect.size() - 1), l = 0;
            for (size_t i = l; i < vect.size()-1; i++)
            {
                com_count++;
                if (vect[i] > vect[i + 1])
                {
                    exc_count++;
                    std::swap(vect[i], vect[i + 1]);
                    check = 1;
                }
            }
            r--;
            for (size_t i = r; i > 0; i--)
            {
                com_count++;
                if (vect[i] < vect[i - 1])
                {
                    exc_count++;
                    std::swap(vect[i], vect[i - 1]);
                    check = 1;
                }
            }
            l++;
        }
}

void gnomeSort(std::vector<int> &vec)
{
    int i = 1;
    while (i < vec.size())
    {
        if (vec[i] >= vec[i-1])
        {
            i++;
        }
        else
        {
            int temp = vec[i];
            vec[i] = vec[i-1];
            vec[i-1] = temp;
            if (i > 1)
            { i--; }
        }
    }
}

void oneForwardBumble(vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++) {
          if (vec[i] > vec[i + 1]) {
              swap(vec[i], vec[i+1]);
        }
    }
}

void oneBackBumble(vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++) {
          if (vec[i] < vec[i + 1]) {
              swap(vec[i], vec[i+1]);
        }
    }
}

vector<vector<int>> generateMatrix(size_t size, size_t count) {
    auto vec = generateVector(size);
    vector<vector<int>> testMatrix((size/count) * 2 + 1);
    auto center = size/count;
    testMatrix[center] = vec;
    auto vec1 = vec;
    for (int i = 1; i <= size; i++) {
        oneForwardBumble(vec);
        if (i%count == 0 ) {
            testMatrix[center + int(i/count)] = vec;
        }
    }
    
    for (int i = 1; i <= size; i++) {
        oneBackBumble(vec1);
        if (i%count == 0 ) {
            testMatrix[center - int(i/count)] = vec1;
        }
    }
    
    return testMatrix;
}

void firstTest(size_t count) {
    auto vec1 = generateVector(count);
    auto vec2 = vec1;
    auto start = std::chrono::steady_clock::now();
    sheikerSort(vec1);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Шейкерная сортировка в векторе размера " << vec1.size() <<  " заняла " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mks" << std::endl;
    start = std::chrono::steady_clock::now();
    gnomeSort(vec2);
    end = std::chrono::steady_clock::now();
    std::cout << "Гномья сортировка в векторе размера " << vec1.size() <<  " заняла " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mks" << std::endl;
}

void secondTest(size_t size, size_t count) {
    auto testMatrix = generateMatrix(size, count);
    auto testMatrix1 = testMatrix;
    ofstream fout;
    fout.open("/Users/dmitry/Desktop/cpp/6th semester/find/sheker vs gnom/sheikerRes.txt");
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    for (int i = 0; i < testMatrix.size(); i++) {
        cout << "sheiker: " << i;
        start = std::chrono::steady_clock::now();
        sheikerSort(testMatrix[i]);
        end = std::chrono::steady_clock::now();
        fout << i << " " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << endl;
    }
    fout.close();
    
    fout.open("/Users/dmitry/Desktop/cpp/6th semester/find/sheker vs gnom/GnomeRes.txt");
    for (int i = 0; i < testMatrix1.size(); i++) {
        cout << "gnome: " << i;
        start = std::chrono::steady_clock::now();
        gnomeSort(testMatrix1[i]);
        end = std::chrono::steady_clock::now();
        fout << i << " " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << endl;
    }
    fout.close();
}


int main() {
    firstTest(500);
    firstTest(1000);
    firstTest(5000);
    firstTest(10000);
    firstTest(50000);
    secondTest(10000, 100);
    return 0;
}
