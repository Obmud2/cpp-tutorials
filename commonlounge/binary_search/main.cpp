//
//  main.cpp
//  binary_search
//
//  Created by Jon Pring on 05/01/2021.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iterator>
using namespace std;

int binary_search2(vector<int> array, int element, int low, int high){
    int mid = (high - low) / 2 + low;
    //for (int i{low}; i<high+1; i++){cout << array[i] << " ";}
    //cout << endl;
    if (array[mid] == element){
        return mid;
    }
    else if (low == high){
        return -1;
    }
    else if (array[mid] < element){
        return binary_search2(array, element, mid + 1, high);
    }
    else {
        return binary_search2(array, element, low, mid - 1);
    }
}

long binary_search3(const vector<int> &arr, const int element, const int arraySize){
    //for (auto a:arr){cout << a << " ";}
    //cout << "Query " << element << endl;
    
    auto low = arr.begin();
    auto high = arr.end();
    //int count{0};
    //cout << distance(low,high) << " " << element << endl;
    
    while ((high - low)){
        //count++;
        auto mid = low + distance(low, high)/2;
        //cout << *low << " " << *mid << " " << *high << " Dist: "<< distance(arr.begin(), mid)<< endl;
        if (element == *mid){
            return mid - arr.begin();
        }
        else if (element > *mid){
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }
    return -1;
}

int main(int argc, const char * argv[]) {
    
    ofstream ofs;
    ifstream ifs;
    ofs.open("output");
    ifs.open("input");
    
    // Store the number of test cases
    int testCases;
    ifs >> testCases;
    
    for (int t{0}; t<testCases; t++){
        int N, Q, num, query;
        int n{0};
        long result;
        vector<int> array;
        vector<int> results;
        ifs >> N >> Q;
        
        while (n++ < N && ifs >> num){
            array.push_back(num);
        }
        
        int arraySize {static_cast<int>(array.size())};
        
        for (int q{0}; q<Q; q++){
            ifs >> query;
            result = binary_search3(array, query, arraySize);
            //if (q%1000==0){cout << q << endl;}
            ofs << result << " ";
        }
        ofs << endl;
    }
    
    ifs.close();
    ofs.close();
}
