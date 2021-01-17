//
//  main.cpp
//  quick_sort
//
//  Created by Jon Pring on 16/01/2021.
//

#include <iostream>
#include <fstream>
using namespace std;

void swap(int &a, int &b){
    int temp{a};
    a = b;
    b = temp;
}

int qs_partition(int arr[], int begin, int end){

    // Select pivot
    int pivot_i {rand() % (end - begin) + begin};
    int pivot {arr[pivot_i]};
    //cout << "B:" << begin << " E:" << end << " Pv:" << pivot << endl;
    
    // Initiate selectors
    int low{begin}, high{end-1};
    int last_low{-1}, last_high{end};
    
    while (low < high){
        // Move to next pair to swap
        while (arr[low]  < pivot && low  <  end  ) {low++;}
        while (arr[high] > pivot && high >= begin) {high--;}
        
        // Check the swap is not repeated in the case of duplicate pivots
        if (low == last_low && high == last_high){
            low++;
            continue;
        }
        
        // Swap elements
        swap(arr[low], arr[high]);
        
        // Store last swap
        last_low = low;
        last_high = high;
    }
    
    // Return pivot index
    return low;
}

void quick_sort(int arr[], int begin, int end, long &count){
    if ((end - begin) <= 1){
        return;
    }
    
    int pivot{qs_partition(arr, begin, end)};
    count++;
    
    quick_sort(arr, begin, pivot, count);
    quick_sort(arr, pivot+1, end, count);
    
}

int main(int argc, const char * argv[]) {
    
    srand(97);
    long count{0};
    
    ifstream ifs;
    ofstream ofs;
    ifs.open("input");
    ofs.open("output");
    
    int T;
    size_t N;
    
    // Read number of test cases T
    ifs >> T;
    
    // Read, sort and output for each test case
    for (int t{0}; t<T; t++){
        ifs >> N;                       // Get number of elements N
        
        string s {to_string(N)};
        cout << "N = " << s;
        
        for (int i{8}; i>s.size(); i--){
            cout << " ";
        }
        cout << endl;
        
        int *array { new int[N]{} }; // Dynamic array for file read
        
        for (int n{0}; n<N; n++){
            ifs >> array[n];            // Read N elements
        }
        quick_sort(array, 0, N, count);   // Sort array
        
        for (int n{0}; n<N; n++){
            ofs << array[n] << " ";     // Write array to output
        }
        delete [] array;
        ofs << endl;
    }
    
    ifs.close();
    ofs.close();
    
    return 0;
}
