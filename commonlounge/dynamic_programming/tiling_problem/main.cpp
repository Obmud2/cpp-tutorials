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
long tile(int n, long ans[], long ans_g[]); //Helper function:   combinations of tiles for n x 2 matrix.
long tile_g(int n, long ans[], long ans_g[]); //Helper function: combinations of tiles for n x 2 matrix with additional block.

 
int main() {
    int input[] {1, 2, 3, 5};
    int result[4];
    
    tile_solve(input, result, 4);
    
    /*
    for (auto i:result){
        cout << i << " ";
    }
    cout << endl;
     */
}





void tile_solve(int n[], int result[], int T){
    int N{0};
    for (int t{0}; t<T; t++){
        N = (n[t] > N) ? n[t] : N;
    }
    
    long *ans { new long[N]{} };
    long *ans_g { new long[N]{} };
    
    for (int i{0}; i<N; i++){
        ans[i] = -1;
        ans_g[i] = -1;
    }
    
    for (int t{0}; t<T; t++){
        result[t] = static_cast<int>(tile(n[t], ans, ans_g) % 100003);
        cout << "n = " << n[t] << ": " << result[t] << endl;
    }
    
    delete [] ans;
    delete [] ans_g;
}

long tile(int n, long ans[], long ans_g[]){
    if (ans[n-1] != -1){ return ans[n-1]; }
    
    if (n == 1){ return ans[n-1] = 1; }
    if (n == 2){ return ans[n-1] = 2; }
    if (n == 3){ return ans[n-1] = 5; }
    
    return ans[n-1] = tile(n-1, ans, ans_g) + tile(n-2, ans, ans_g) + 2*tile_g(n-2, ans, ans_g);
}

long tile_g(int n, long ans[], long ans_g[]){
    if (ans_g[n-1] != -1){ return ans_g[n-1]; }
    
    if (n == 1){ return ans_g[n-1] = 1; }
    if (n == 2){ return ans_g[n-1] = 2; }
    
    return ans_g[n-1] = tile(n-1, ans, ans_g) + tile_g(n-1, ans, ans_g);
}
