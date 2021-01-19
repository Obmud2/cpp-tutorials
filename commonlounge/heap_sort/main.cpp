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

void k_sort_import(){
    
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
        int K;
        int len_vec {0};
        ifs >> K;
        
        vector<deque<int>> vec;
        vector<int> output_vec;
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
        
        //print_vec_vec(vec);
        
        Heap h;
        for (int k{0}; k<K; k++){
            h.insert(k, vec[k][0]);
            vec[k].pop_front();
        }
        //h.print();
        
        pair<int, int> pop_vec;
        while (output_vec.size() < len_vec){
            pop_vec = h.pop();
            output_vec.push_back(pop_vec.second);
            if (!vec[pop_vec.first].empty()){
                h.insert(pop_vec.first, vec[pop_vec.first][0]);
                vec[pop_vec.first].pop_front();
            }
            //h.print();
        }
        for (int o:output_vec){
            ofs << o << " ";
        }
        ofs << endl;
        cout << t << endl;
    }
    
    
}
