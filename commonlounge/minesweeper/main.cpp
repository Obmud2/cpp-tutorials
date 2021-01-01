//
//  main.cpp
//  minesweeper
//
//  Created by Jon Pring on 27/12/2020.
//

#include <iostream>
#include <string>
#include <ctime>
#include <regex>
using namespace std;

int N_ROWS{7};
int N_COLUMNS{12};
int N_MINES{2};

enum class GameState{
    player_turn,
    player_win,
    player_lose
};

void selectDifficulty (){
    int difficulty{1};
    cout << "Select difficulty level (1-3): " << endl;
    cin >> difficulty;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (difficulty) {
        case 1:
            N_ROWS = 9;
            N_COLUMNS = 9;
            N_MINES = 10;
            break;
        case 2:
            N_ROWS = 16;
            N_COLUMNS = 16;
            N_MINES = 40;
            break;
        case 3:
            N_ROWS = 16;
            N_COLUMNS = 30;
            N_MINES = 99;
            break;
        default:
            break;
    }
}

void drawBoard(char **board){
    auto drawHead = [](){
        cout << "    ";
        for (int j{0}; j<N_COLUMNS; j++){
            cout << j << " ";
            if (j<9){cout << " ";}
        }
        cout << endl;
    };
    
    drawHead();
    cout << endl;
    
    for (int i{0}; i<N_ROWS; i++){
        cout << i << "  ";
        if (i < 10){cout << " ";}
        for (int j{0}; j<N_COLUMNS; j++){
            cout << board[i][j] << "  ";
        }
        cout << "  " << i << endl;
    }
    
    cout << endl;
    drawHead();
}
const vector<string> split(const string& s, const char& c){
    string buff{""};
    vector<string> v;
    for (auto n:s){
        if (n != c){
            buff += n;
        }
        else if (n == c && buff != ""){
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != ""){
        v.push_back(buff);
    }
    return v;
}
void generateMineBoard(char **mineBoard){
    
    // Set grid to '0'
    for (int i{0}; i<N_ROWS; i++){
        for (int j{0}; j<N_COLUMNS; j++){
            mineBoard[i][j] = '0';
        }
    }
    
    // Generate N_MINES * mines
    for (int m{0}; m<N_MINES; m++){
        int mColumn {rand() % N_COLUMNS};
        int mRow    {rand() % N_ROWS};
        //cout << "mine = (" << mRow << ", " << mColumn << ")" << endl;
        if (mineBoard[mRow][mColumn] != '#'){
            mineBoard[mRow][mColumn] = '#';
        }
        else{
            m-=1;
        }
    }
    
    // Fill in numbers
    for (int i{0}; i<N_ROWS; i++){
        for (int j{0}; j<N_COLUMNS; j++){
            if (mineBoard[i][j] == '#'){
                if (i > 0 && j > 0 && mineBoard[i-1][j-1] != '#')
                    mineBoard[i-1][j-1]++;
                if (i > 0 && mineBoard[i-1][j] != '#')
                    mineBoard[i-1][j]++;
                if (i > 0 && j < (N_COLUMNS - 1) && mineBoard[i-1][j+1] != '#')
                    mineBoard[i-1][j+1]++;
                if (j > 0 && mineBoard[i][j-1] != '#')
                    mineBoard[i][j-1]++;
                if (j < (N_COLUMNS - 1) && mineBoard[i][j+1] != '#')
                    mineBoard[i][j+1]++;
                if (i < (N_ROWS - 1) && j > 0 && mineBoard[i+1][j-1] != '#')
                    mineBoard[i+1][j-1]++;
                if (i < (N_ROWS - 1) && mineBoard[i+1][j] != '#')
                    mineBoard[i+1][j]++;
                if (i < (N_ROWS - 1) && j < (N_COLUMNS - 1) && mineBoard[i+1][j+1] != '#')
                    mineBoard[i+1][j+1]++;
            }
        }
    }
    
}
void generateGameBoard(char **gameBoard){
    // Set grid to '.'
    for (int i{0}; i<N_ROWS; i++){
        for (int j{0}; j<N_COLUMNS; j++){
            gameBoard[i][j] = '.';
        }
    }
}
void deleteBoard(char **board){
    for (int i = 0; i < N_ROWS; i++)
            delete[] board[i];
        delete[] board;
}
void uncoverBoard(char **gameBoard, char **mineBoard, const int row, const int col){
    
    bool row_min{!!row};                     // =0 if top edge
    bool row_max{!!(N_ROWS - (row + 1))};    // =0 if bottom edge
    bool col_min{!!col};                     // =0 if left edge
    bool col_max{!!(N_COLUMNS - (col + 1))}; // =0 if right edge
    
    for (int i{-row_min}; i<(1+row_max); i++){
        for (int j{-col_min}; j<(1+col_max); j++){
            if (i == 0 && j == 0){
                continue;
            }
            else if (mineBoard[row + i][col + j] != '0' && mineBoard[row + i][col + j] != '.'){
                gameBoard[row + i][col + j] = mineBoard[row + i][col + j];
                mineBoard[row + i][col + j] = '.';
            }
            else if (mineBoard[row + i][col + j] == '0'){
                gameBoard[row + i][col + j] = '0';
                mineBoard[row + i][col + j] = '.';
                uncoverBoard(gameBoard, mineBoard, row + i, col + j);
            }
        }
    }
}

bool checkBoard(char **gameBoard){
    for (int i{0}; i<N_ROWS; i++){
        for (int j{0}; j<N_COLUMNS; j++){
            if (gameBoard[i][j] == '.'){
                return false;
            }
        }
    }
    return true;
}

void boom(char **gameBoard, char **mineBoard){
    cout << "BOOM!!! Game over!" << endl;
    for (int i{0}; i<N_ROWS; i++){
        for (int j{0}; j<N_COLUMNS; j++){
            if (mineBoard[i][j] == '#')
                gameBoard[i][j] = '#';
        }
    }
}
GameState playerMove(char **gameBoard, char **mineBoard, int& flags){
    string playerInput;
    vector<string> playerInputVector;
    int row, col;
    char type;
    while(true){
        cout << "Enter your move, (row, column, safe(s) / flag(f)): " << endl;
        getline(cin, playerInput);
        
        // check input format
        if (!regex_match(playerInput, regex("\\d+ \\d+ [a-z]"))){
            cout << "Invalid input! ";
            continue;
        }
        
        // convert input to row, col, type variables
        vector<string> playerInputVector {split(playerInput, ' ')};
        row = stoi(playerInputVector[0]);
        col = stoi(playerInputVector[1]);
        type = playerInputVector[2][0];
        
        // if input == valid, break from player input loop
        if (row < N_ROWS &&
            col < N_COLUMNS &&
            mineBoard[row][col] != '.' &&
            (type == 's' ||
            (type == 'f' && flags > 0))){
            break;
        }
        
        // if input != valid, print error and repeat loop.
        if (row >= N_ROWS) {cout << "Row out of range. ";}
        if (col >= N_COLUMNS){cout << "Column out of range. ";}
        if (type != 's' && type != 'f'){cout << "Invalid mark. ";}
        if (type == 'f' && flags < 1){cout << "No flags remaining. ";}
        if (mineBoard[row][col] == '.'){cout << "Square already selected. ";}
    }
    
    // action based on player input and mineBoard
    if (gameBoard[row][col] == '*'){flags++;}   // if flag is replaced, add flag to count
    if (type == 'f'){                           // if type = flag, add flag to gameboard
        gameBoard[row][col] = '*';
        flags--;
    }
    else if (mineBoard[row][col] == '#'){       // if player hits mine, end game
        boom(gameBoard, mineBoard);
        return GameState::player_lose;
    }
    else if (mineBoard[row][col] == '0'){       // if player hits 0, uncover board recursively
        uncoverBoard(gameBoard, mineBoard, row, col);
    }
    else {                                      // if player hits number, uncover element only
        gameBoard[row][col] = mineBoard[row][col];
        mineBoard[row][col] = '.';
    }
    
    // check if game is complete
    if (checkBoard(gameBoard)){
        return GameState::player_win;
    }
    
    drawBoard(gameBoard);
    cout << "You have " << flags << " flags remaining." << endl;;
    return GameState::player_turn;
}
void playMinesweeper(){
    
    selectDifficulty();
    
    int flags{N_MINES};
    
    auto** mineBoard = new char*[N_ROWS];
    for(int i = 0; i < N_ROWS; ++i)
        mineBoard[i] = new char[N_COLUMNS];
    
    auto** gameBoard = new char*[N_ROWS];
    for(int i = 0; i < N_ROWS; ++i)
        gameBoard[i] = new char[N_COLUMNS];
    
    GameState gameState{GameState::player_turn};
    
    generateMineBoard(mineBoard);
    generateGameBoard(gameBoard);
    
    drawBoard(gameBoard);
    cout << endl;
    
    while(gameState == GameState::player_turn){
        gameState = playerMove(gameBoard, mineBoard, flags);
    }
    
    drawBoard(gameBoard);
    
    deleteBoard(gameBoard);
    deleteBoard(mineBoard);
    
    switch (gameState){
        case GameState::player_win:
            cout << "Congratuations, you win!" << endl;
            return;
        case GameState::player_lose:
            cout << "You lose, try again." << endl;
            return;
        default:
            cout << "Unknown result" << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    playMinesweeper();

    return 0;
}
