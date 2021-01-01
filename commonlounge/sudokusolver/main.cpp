//
//  main.cpp
//  sudokusolver
//
//  Created by Jon Pring on 27/12/2020.
//

#include <iostream>
using namespace std;

const int UNASSIGNED = 0;
const int N = 9;

bool isValid(int grid[N][N], int row, int col, int number){
    for (int i{0}; i<N; i++){
        if (number == grid[i][col] || number == grid[row][i])
            return false;
    }
    for (int i{3*(row/3)}; i<3*(row/3)+3; i++){
        for (int j{3*(col/3)}; j<3*(col/3)+3; j++){
            if (number == grid[i][j])
                return false;
        }
    }
    return true;
}

bool findUnassignedLocation(int grid[N][N], int &row, int &col){
    for (int i{0}; i<N; i++){
        for (int j{0}; j<N; j++){
            if (!grid[i][j]){
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

void displayGrid(int grid[N][N]){
    for (int i{0}; i<N; i++){
        for (int j{0}; j<N; j++){
            if (grid[i][j]){
                cout << grid[i][j] << " ";
            }
            else {
                cout << "  ";
            }
                
            if (j%3==2 && j != N-1)
                cout << "| ";
        }
        cout << endl;
        if (i%3==2 && i!=N-1)
            cout << "------ ------- ------" << endl;
    }
}

bool solveSudoku(int grid[N][N]){
    int row{0}, col{0};
    
    // base case - if no unassigned location, return true
    if (!findUnassignedLocation(grid, row, col))
        return true;
    
    for (int num{1}; num<=9; num++){
        if (isValid(grid, row, col, num)){
            grid[row][col] = num;
            
            if (solveSudoku(grid)){
                return true;
            }
            
            grid[row][col] = UNASSIGNED;
        }
    }
    
    return false;
}

int main() {

    int grid[N][N] = {
      {5,3,0, 0,7,0, 0,0,0},
      {6,0,0, 1,9,5, 0,0,0},
      {0,9,8, 0,0,0, 0,6,0},
        
      {8,0,0, 0,6,0, 0,0,3},
      {4,0,0, 8,0,3, 0,0,1},
      {7,0,0, 0,2,0, 0,0,6},
        
      {0,6,0, 0,0,0, 2,8,0},
      {0,0,0, 4,1,9, 0,0,5},
      {0,0,0, 0,8,0, 0,7,9}
    };
    
    solveSudoku(grid);
    
    displayGrid(grid);
    
    return 0;
}
