//
//  main.cpp
//  heap_sort
//
//  Created by Jon Pring on 17/01/2021.
//

#include <iostream>
#include <fstream>
#include "heapsort.hpp"
using namespace std;


void get_arr(ifstream& i, int arr[], size_t arrSize){
    for (int n{0}; n<arrSize; n++){
        i >> arr[n];
    }
}
void output_arr(ofstream& o, int arr[], size_t arrSize){
    for (int n{0}; n<arrSize; n++){
        o << arr[n] << " ";
    }
    o << endl;
}

void print_arr(int arr[], size_t arrSize){
    for (int n{0}; n<arrSize; n++){
        cout << arr[n] << " ";
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    ifstream ifs;
    ofstream ofs;
    ifs.open("input");
    ofs.open("output");
    
    int T;
    ifs >> T;
    
    for (int t{0}; t<T; t++){
        int N;
        ifs >> N;
        auto *arr ( new int[N]{} );
        
        get_arr(ifs, arr, N);
        
        heap_sort(arr, N);
        
        output_arr(ofs, arr, N);
        //print_arr(arr, N);
        cout << "N = " << N << endl;
    }
}
