//
//  main.cpp
//  tiling_problem
//
//  Created by Jon Pring on 24/01/2021.
//

#include <iostream>
using namespace std;

void tile_solve(int n[], int result[], int T); // Calculate possible tile combinations in n * 2 matrix
/* Possible tiles:
 __    __
|  |  |  |__
|__|  |_____|

*/
long long tile(int n, long long ans[], long long ans_g[]); //Helper function:   combinations of tiles for n x 2 matrix.
long long tile_g(int n, long long ans[], long long ans_g[]); //Helper function: combinations of tiles for n x 2 matrix with additional block.

 
int main() {
    int T {10};
    int input[] {3, 10, 23, 60, 269, 832, 1597, 5189, 25987, 76401};
    int result[T];
    
    tile_solve(input, result, T);
}


void tile_solve(int n[], int result[], int T){
    int N{0};
    for (int t{0}; t<T; t++){
        N = (n[t] > N) ? n[t] : N;
    }
    
    auto *ans { new long long[N]{} };
    auto *ans_g { new long long[N]{} };
    //long long ans[N], ans_g[N];
    
    for (int i{0}; i<N; i++){
        ans[i] = -1;
        ans_g[i] = -1;
    }
    
    for (int t{0}; t<T; t++){
        result[t] = static_cast<int>(tile(n[t], ans, ans_g) % 1000003);
        cout << "n = " << n[t] << ": " << result[t] << endl;
    }
    
    delete [] ans;
    delete [] ans_g;
}

long long tile(int n, long long ans[], long long ans_g[]){
    if (ans[n-1] != -1){ return ans[n-1]; }
    
    if (n == 1){ return ans[n-1] = 1; }
    if (n == 2){ return ans[n-1] = 2; }
    
    return ans[n-1] = (tile(n-1, ans, ans_g) + tile(n-2, ans, ans_g) + 2*tile_g(n-2, ans, ans_g)) % 1000003;
}

long long tile_g(int n, long long ans[], long long ans_g[]){
    if (ans_g[n-1] != -1){ return ans_g[n-1]; }
    
    if (n == 1){ return ans_g[n-1] = 1; }
    if (n == 2){ return ans_g[n-1] = 2; }
    
    return ans_g[n-1] = (tile(n-1, ans, ans_g) + tile_g(n-1, ans, ans_g)) % 1000003;
}
