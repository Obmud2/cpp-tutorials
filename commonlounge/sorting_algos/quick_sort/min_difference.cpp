//
//  min_difference.cpp
//  quick_sort
//
//  Created by Jon Pring on 17/01/2021.
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

void quick_sort(int arr[], int begin, int end){
    if ((end - begin) <= 1){
        return;
    }
    
    int pivot{qs_partition(arr, begin, end)};
    
    quick_sort(arr, begin, pivot);
    quick_sort(arr, pivot+1, end);
}

void print_array(int arr[], size_t arrSize){
    for (int n{0}; n<arrSize; n++){
        cout << arr[n] << " ";
    }
    cout << endl;
}

void import_array(int arr[], size_t arrSize, ifstream &ifs){
    for (int n{0}; n<arrSize; n++){
        ifs >> arr[n];
    }
}

int check_diff(int arr[], size_t arrSize, int k){
    int min_diff {0x7FFFFFFF}, diff;
    for (int i{0}; i<(arrSize - (k-1)); i++){
        diff = arr[i + (k-1)] - arr[i];
        if (min_diff > diff){
            min_diff = diff;
        }
    }
    return min_diff;
}

int main(){
    ifstream ifs;
    ofstream ofs;
    ifs.open("min_diff_input");
    ofs.open("min_diff_output");
    
    int T, k, min_diff;
    size_t N;
    
    // Read number of test cases T
    ifs >> T;
    
    // Read, sort and output for each test case
    for (int t{0}; t<T; t++){
        ifs >> N >> k;                       // Get number of elements N
        
        
        int *array { new int[N]{} }; // Dynamic array for file read
        
        import_array(array, N, ifs);
        quick_sort(array, 0, static_cast<int>(N));   // Sort array
        
        min_diff = check_diff(array, N, k);
        
        
        delete [] array;
        ofs << min_diff << endl;
        cout << "N = " << N << " " << min_diff << endl;
    }
    
    ifs.close();
    ofs.close();
}
