//
//  main.cpp
//  merge_sort
//
//  Created by Jon Pring on 14/01/2021.
//

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
using namespace std;

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;
    
    std::chrono::time_point<clock_t> m_beg;
    
public:
    Timer() : m_beg(clock_t::now()){}
    
    void reset(){
        m_beg = clock_t::now();
    }
    
    double elapsed() const {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};

void swap(int *a, int *b){
    int temp {*a};
    *a = *b;
    *b = temp;
}

void merge(int *left, size_t leftSize, int *right, size_t rightSize, long *count){
    int ii{0}, jj{0};
    int result[leftSize + rightSize];
    
    while ((ii < leftSize) || (jj < rightSize)){
        if ((ii < leftSize) && ((jj == rightSize) || (left[ii] <= right[jj]))){
            result[ii + jj] = left[ii];
            ii++;
        }
        else {
            result[ii + jj] = right[jj];
            jj++;
            (*count) += (leftSize - ii);
        }
    }
    
    for (int i{0}; i<(leftSize + rightSize); i++){
        left[i] = result[i];
    }
    
}

void merge_sort(int *arr, size_t arrSize, long *count){
    // Base case, array must have > 1 element
    if (arrSize < 2){
        return;
    }
    
    // Split array into L / R
    int *left {arr};
    size_t leftSize{arrSize/2};
    int *right {arr + arrSize/2};
    size_t rightSize{arrSize - leftSize};
    
    // Sort split arrays
    merge_sort(left, leftSize, count);
    merge_sort(right, rightSize, count);
    
    // Merge split arrays
    merge(left, leftSize, right, rightSize, count);
}

int main(int argc, const char * argv[]) {
    
    ifstream ifs;
    ofstream ofs;
    ifs.open("inversion_input");
    ofs.open("output");
    
    int T;
    size_t N;
    
    // Read number of test cases T
    ifs >> T;
    
    // Read, sort and output for each test case
    for (int t{0}; t<T; t++){
        Timer time;
        ifs >> N;                       // Get number of elements N
        long count {0};
        
        string s {to_string(N)};
        cout << "N = " << s;
        
        for (int i{8}; i>s.size(); i--){
            cout << " ";
        }
        
        int *array { new int[N]{} };
        
        for (int n{0}; n<N; n++){
            ifs >> array[n];            // Read N elements
        }
        merge_sort(array, N, &count);   // Sort array
        
        for (int n{0}; n<N; n++){
            ofs << array[n] << " ";     // Write array to output
        }
        delete [] array;
        cout << " Count: " << count << endl;;
        ofs << endl;
    }
    
    ifs.close();
    ofs.close();
    
}
