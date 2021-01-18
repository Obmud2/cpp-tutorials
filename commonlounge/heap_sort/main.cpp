//
//  main.cpp
//  heap_sort
//
//  Created by Jon Pring on 17/01/2021.
//

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Heap {
    vector<int> arr;
    
    int find_child(int node){
        int child{(node+1) * 2 - 1};
        if (child < arr.size() && arr[child] > arr[child+1]){
            child++;
        }
        return (child < arr.size() && arr[node] > arr[child]) ? child : 0;
    }
public:
    void insert(int n){
        arr.push_back(n);
        int node   {static_cast<int>(arr.size() - 1)};
        int parent {(node + 1) / 2 - 1};
        while (parent >= 0 && arr[node] < arr[parent]){
            swap(arr[node], arr[parent]);
            node = parent;
            parent = (node + 1) / 2 - 1;
        }
    }
    int pop(){
        int result {arr[0]};
        arr[0] = arr.back();
        arr.pop_back();
        int node{0};
        int child;
        while ((child = find_child(node)) != 0){
            swap(arr[node], arr[child]);
            node = child;
        }
        return result;
    }
    void print(){
        for (int a:arr){
            cout << a << " ";
        }
        cout << endl;
    }
};

void heap_sort(int arr[], size_t arrSize){
    Heap h;
    for (int i{0}; i<arrSize; i++){
        h.insert(arr[i]);
    }
    for (int i{0}; i<arrSize; i++){
        arr[i] = h.pop();
    }
}

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
