//
//  heapsort.hpp
//  heap_sort
//
//  Created by Jon Pring on 18/01/2021.
//

#ifndef heapsort_hpp
#define heapsort_hpp

#include <stdio.h>
#include <vector>

class Heap {
    std::vector<int> arr;
    int find_child(int node);
public:
    void insert(int n);
    int pop();
    void print();
};

void heap_sort(int arr[], size_t arrSize);

#endif /* heapsort_hpp */
