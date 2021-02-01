//
//  main.cpp
//  longest_substring_problem
//
//  Created by Jon Pring on 27/01/2021.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void print_grid(int **paths, string s1, string s2, int rows, int cols){
    cout << "  ";
    for (auto s:s2){
        cout << s << " ";
    }
    cout << endl;
    
    for (int row{0}; row < rows; row++){
        cout << s1[row] << " ";
        for (int col{0}; col < cols; col++){
            cout << paths[row][col] << " ";
        }
        cout << endl;
    }
}

int** generate_grid(int rows, int cols){
    int **paths;
    paths = new int* [rows];
    for (int row{0}; row < rows; row++){
        paths[row] = new int [cols];
    }
    return paths;
}

void delete_grid(int **grid, int rows, int cols){
    for (int row {0}; row < rows; row++)
            delete[] grid[row];
        delete[] grid;
}


int max_int(int a, int b){
    return (a > b) ? a : b;
}


int find_longest_substring(string s1, string s2){
    int longest_substring {0};
    
    int rows {static_cast<int>(s1.length())};
    int cols {static_cast<int>(s2.length())};
    
    string substr;
    
    int **paths {generate_grid(rows, cols)};
    
    for (int row{0}; row < rows; row++){
        for (int col{0}; col < cols; col++){
            if (row == 0 && col == 0){
                paths[row][col] = (s1[row] == s2[col]) ? 1 : 0;
                if (longest_substring < paths[row][col]){
                    longest_substring = paths[row][col];
                    substr += s1[row];
                };
            }
            else if (row == 0){
                paths[row][col] = (s1[row] == s2[col]) ? 1 : paths[row][col-1];
                if (longest_substring < paths[row][col]){
                    longest_substring = paths[row][col];
                    substr += s1[row];
                };
            }
            else if (col == 0){
                paths[row][col] = (s1[row] == s2[col]) ? 1 : paths[row-1][col];
                if (longest_substring < paths[row][col]){
                    longest_substring = paths[row][col];
                    substr += s1[row];
                };
            }
            else if (s1[row] == s2[col]){
                paths[row][col] = paths[row-1][col-1] + 1;
                if (longest_substring < paths[row][col]){
                    longest_substring = paths[row][col];
                    substr += s1[row];
                };
            }
            else {
                paths[row][col] = max(paths[row-1][col], paths[row][col-1]);
            }
        }
    }
    
    print_grid(paths, s1, s2, rows, cols);
    
    cout << substr << endl;
    
    return longest_substring;
}

int main() {
    
    string string1 {"CCJFCFIGEAAAEBHHDIKAGIHCDGCAGIAKHFIKJCEJDBEBKDCGBEDFK"};
    string string2 {"HCGEIDJCHHDDKECBBEFDHCCHKGHCFKGIJJGHIIFFKADGFBAECABDAJIGDFJBEDKIICAKIKKEIHCEHH"};
    
    cout << find_longest_substring(string2, string1) << endl;
}
