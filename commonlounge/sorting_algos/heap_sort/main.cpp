//
//  main.cpp
//  heap_sort
//
//  Created by Jon Pring on 17/01/2021.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
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

/*
void heap_sort_test() {
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
}*/

void print_vec_vec(vector<deque<int>> vec){
    
    for (int i{0}; i<vec.size(); i++){
        for (int j{0}; j<vec[i].size(); j++){
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}

vector<deque<int>> read_vec(ifstream &ifs, int K, int& len_vec){
    vector<deque<int>> vec;
    for (int k{0}; k<K; k++){
        int N, input;
        ifs >> N;
        deque<int> temp_vec;
        for (int n{0}; n<N; n++){
            ifs >> input;
            temp_vec.push_back(input);
            len_vec++;
        }
        vec.push_back(temp_vec);
    }
    return vec;
}

void write_output (ofstream &ofs, vector<int> vec){
    for (int v:vec){
        ofs << v << " ";
    }
    ofs << endl;
}

int main(){
    //heap_sort_test();
    
    ifstream ifs;
    ofstream ofs;
    ifs.open("k_sort_input");
    ofs.open("k_sort_output");
    
    int T;
    
    ifs >> T;
    cout << T << endl;
    
    for (int t{0}; t<T; t++){
        // Read input from ifs
        int K;
        int len_vec {0};
        ifs >> K;
        vector<deque<int>> vec {read_vec(ifs, K, len_vec)};
        
        // Initiate heap of length K
        Heap h;
        for (int k{0}; k<K; k++){
            h.insert(k, vec[k][0]);
            vec[k].pop_front();
        }
        
        vector<int> output_vec;
        
        // Pop and replace item in heap for each k until all inputs are empty
        pair<int, int> pop_vec;
        while (output_vec.size() < len_vec){
            pop_vec = h.pop();
            output_vec.push_back(pop_vec.second);
            if (!vec[pop_vec.first].empty()){
                h.insert(pop_vec.first, vec[pop_vec.first][0]);
                vec[pop_vec.first].pop_front();
            }
        }
        write_output(ofs, output_vec);
        cout << t << endl;
    }
    
    ifs.close();
    ofs.close();
}
