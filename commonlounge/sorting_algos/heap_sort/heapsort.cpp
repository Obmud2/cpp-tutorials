//
//  heapsort.cpp
//  heap_sort
//
//  Created by Jon Pring on 18/01/2021.
//

#include "heapsort.hpp"
#include <iostream>
#include <vector>

using namespace std;

int Heap::find_child(int node){
    int child{(node+1) * 2 - 1};
    if (child < arr.size() && arr[child].second > arr[child+1].second){
        child++;
    }
    return (child < arr.size() && arr[node].second > arr[child].second) ? child : 0;
}
    
void Heap::insert(int n, int val){
    arr.push_back({n, val});
    int node   {static_cast<int>(arr.size() - 1)};
    int parent {(node + 1) / 2 - 1};
    while (parent >= 0 && arr[node].second < arr[parent].second){
        swap(arr[node], arr[parent]);
        node = parent;
        parent = (node + 1) / 2 - 1;
    }
}

pair<int, int> Heap::pop(){
    pair<int, int> result {arr[0]};
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

void Heap::print(){
    for (pair<int, int> a:arr){
        cout << "(" << a.first << ")" << a.second << " ";
    }
    cout << endl;
}


/*
void heap_sort(int arr[], size_t arrSize){
    Heap h;
    for (int i{0}; i<arrSize; i++){
        h.insert(arr[i]);
    }
    for (int i{0}; i<arrSize; i++){
        arr[i] = h.pop();
    }
}
*/
