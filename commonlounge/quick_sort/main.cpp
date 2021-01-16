//
//  main.cpp
//  quick_sort
//
//  Created by Jon Pring on 16/01/2021.
//

#include <iostream>
#include <fstream>
using namespace std;

int qs_partition(int arr[], int begin, int end){
    int temp_arr[end - begin];
    int temp_i{0};
    int pivot {rand() % (end - begin) + begin};
    //cout << "Pivot: " << pivot << " Begin: " << begin << " End: " << end << endl;
    
    for (int i{begin}; i<end; i++){
        if (arr[i] <= arr[pivot] && i != pivot){
            temp_arr[temp_i] = arr[i];
            temp_i++;
        }
    }
    temp_arr[temp_i] = arr[pivot];
    int pivot_result {begin + temp_i};
    temp_i++;
    for (int i{begin}; i<end; i++){
        if (arr[i] > arr[pivot]){
            temp_arr[temp_i] = arr[i];
            temp_i++;
        }
    }
    for (int i{begin}; i<end; i++){
        arr[i] = temp_arr[i-begin];
    }
    
    return pivot_result;
}

void quick_sort(int arr[], int begin, int end){
    if ((end - begin) <= 1){
        return;
    }
    
    int pivot{qs_partition(arr, begin, end)};
    
    quick_sort(arr, begin, pivot);
    quick_sort(arr, pivot+1, end);
    
}

int main(int argc, const char * argv[]) {
    
    srand(97);
    
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
        
        int *array { new int[N]{} };
        
        for (int n{0}; n<N; n++){
            ifs >> array[n];            // Read N elements
        }
        quick_sort(array, 0, N);   // Sort array
        
        for (int n{0}; n<N; n++){
            ofs << array[n] << " ";     // Write array to output
        }
        delete [] array;
        ofs << endl;
    }
    
    return 0;
}
