//
//  main.cpp
//  grid_problem
//
//  Created by Jon Pring on 25/01/2021.
//

#include <iostream>
using namespace std;

const int M{8};
const int N{16};


void print_grid(char grid[M][N]){
    for (int i{0}; i<M; i++){
        for (int j{0}; j<N; j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void print_paths(int grid[M][N]){
    for (int i{0}; i<M; i++){
        for (int j{0}; j<N; j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int count_paths(char grid[M][N]){
    int paths[M][N] {0};
    
    for (int i{M-1}; i>=0; i--){
        for (int j{N-1}; j>=0; j--){
            if (grid[i][j] == '#'){
                paths[i][j] = 0;
            }
            else if (i == (M-1) && j == (N-1)){
                paths[i][j] = 1;
            }
            else if (i == (M-1)){
                paths[i][j] = paths[i][j+1];
            }
            else if (j == (N-1)){
                paths[i][j] = paths[i+1][j];
            }
            else {
                paths[i][j] = paths[i][j+1] + paths[i+1][j];
            }
            print_paths(paths);
        }
    }
    return paths[0][0];
}

int main() {
    
    char grid[M][N] {
        {'.','.','#','.','.','.','.','.','#','.','.','.','#','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','#','.','.','.'},
        {'#','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','#','.','.','.','.','.','.','#'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'}
    };
    print_grid(grid);
    cout << count_paths(grid);
}
