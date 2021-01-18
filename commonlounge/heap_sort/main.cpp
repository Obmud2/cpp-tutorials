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
        if (arr[child] > arr[child+1]){
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
        h.print();
    }
    for (int i{0}; i<arrSize; i++){
        arr[i] = h.pop();
        h.print();
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int V[] {3,4,1,12,15,7,2,0,44,35,6};
    size_t N {sizeof(V) / sizeof(*V)};
    
    heap_sort(V, N);
    
    for (int v:V){
        cout << v << " ";
    }
    cout << endl;
}
