//
//  overlapping_intervals.cpp
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

int qs_partition(pair<int, int> arr[], int begin, int end){
    // Select pivot
    int pivot_i {rand() % (end - begin) + begin};
    int pivot {arr[pivot_i].first};
    //cout << "B:" << begin << " E:" << end << " Pv:" << pivot << endl;
    
    // Initiate selectors
    int low{begin}, high{end-1};
    int last_low{-1}, last_high{end};
    
    while (low < high){
        // Move to next pair to swap
        while (arr[low].first  < pivot && low  <  end  ) {low++;}
        while (arr[high].first > pivot && high >= begin) {high--;}
        
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

void quick_sort(pair<int, int> arr[], int begin, int end){
    if ((end - begin) <= 1){
        return;
    }
    
    int pivot{qs_partition(arr, begin, end)};
    
    quick_sort(arr, begin, pivot);
    quick_sort(arr, pivot+1, end);
    
}

void print_array(pair<int, int> arr[], size_t arrSize){
    for (int n{0}; n<arrSize; n++){
        cout << "(" << arr[n].first << ", " << arr[n].second << ") ";
    }
    cout << endl;
}

void import_array(pair<int, int> arr[], size_t arrSize, ifstream &ifs){
    string temp;
    for (int n{0}; n<arrSize; n++){
        ifs >> arr[n].first >> temp;
        arr[n].second = stoi(temp);
    }
}

bool check_overlap(pair<int, int> arr[], size_t arrSize){
    bool overlap_flag {false};
    
    // Sort array by first element O(nlog(n))
    quick_sort(arr, 0, arrSize);
    //print_array(array, N);
    
    // Check for overlap of second element with next first element O(n)
    for (int n{0}; n<arrSize-1; n++){
        if (arr[n].second >= arr[n+1].first){
            overlap_flag = true;
            break;
        }
    }
    return overlap_flag;
}

int main(){
    ifstream ifs;
    ofstream ofs;
    ifs.open("overlapping_intervals_input");
    ofs.open("overlapping_intervals_output");
    
    // Read number of test cases T
    int T;
    ifs >> T;
    string output;
    
    for (int t{0}; t<T; t++){
        // Get number of pairs
        size_t N;
        ifs >> N;
        
        auto *array { new pair<int, int>[N] {} }; // Dynamic array of pairs for file read
        import_array(array, N, ifs);              // Import array
        
        output = (check_overlap(array, N)) ? "YES" : "NO"; // Check for overlaps and save output text
        
        cout << "t = " << t+1 << " " << output << endl;
        
        delete [] array;
        
    }
    
    ifs.close();
    ofs.close();
    return 0;
}
