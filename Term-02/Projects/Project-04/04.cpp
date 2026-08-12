#include <iostream>
#include <string>
#include <vector>
using namespace std;
string pos_to_name(int row, int col){
    string s;
    s += char('A'+ row);
    s += char('1'+ col);
    return s;
}
bool Can_Move(char board[7][7] ,int row, int col, int row_direct, int col_direct, int& row_mid, int& col_mid, int& new_row, int& new_col){
    new_row = row + 2*row_direct;
    new_col = col + 2*col_direct;
    row_mid = row + row_direct;
    col_mid = col + col_direct;
    if (new_row<0 || new_row>=7 || new_col<0 || new_col>=7) return false;
    if (board[row][col] != 'N') return false;
    if (board[row_mid][col_mid] != 'N') return false;
    if (board[new_row][new_col] != 'O') return false;
    return true;
}
void Do_Move(char board[7][7], int row, int col, int row_mid, int col_mid, int new_row, int new_col){
    board[new_row][new_col] = 'N';
    board[row_mid][col_mid] = 'O';
    board[row][col] = 'O';
}
void Undo_Move(char board[7][7], int row, int col, int row_mid, int col_mid, int new_row, int new_col){
    board[new_row][new_col] = 'O';
    board[row_mid][col_mid] = 'N';
    board[row][col] = 'N';
}
bool Is_Win(char board[7][7]){
    int counter=0;
    bool is_middle = false;
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            if(board[i][j] == 'N'){
                counter++;
                if(i==3 && j==3) is_middle = true;
            }

        }
    }
    return (counter==1 && is_middle);
}
bool Calculate(char board[7][7], vector<string>& moves, const vector<int>& direct_col, const vector<int>& direct_row){
    if(Is_Win(board)) return true;
    for(int row=0; row<7; row++){
        for(int col=0; col<7; col++){
            if(board[row][col] == 'N'){
                for(int direct=0; direct<4; direct++){
                    int midR, midC, newR, newC;
                    if(Can_Move(board, row, col, direct_row[direct], direct_col[direct], midR, midC, newR, newC)){
                        Do_Move(board, row, col, midR, midC, newR, newC);
                        string str_move = pos_to_name(row, col) + " " + (direct==0 ? "UP" :(direct==1 ? "DOWN" :(direct==2 ? "LEFT" :"RIGHT")));
                        moves.push_back(str_move);
                        if(Calculate(board, moves, direct_col, direct_row)) return true;
                        moves.pop_back();
                        Undo_Move(board, row, col, midR, midC, newR, newC);
                    }
                }
            }
        }
    }
    return false;
}
void Print_Answer(vector<string>& moves){
    for (int i=0; i<moves.size(); i++){
        cout << moves[i] << endl;
    }
}
int main(){
    char board[7][7];
    vector<int> direct_col = {0,0,-1,1};
    vector<int> direct_row = {-1,1,0,0};
    vector<string> moves;
    for(int i=0; i<7; i++){
        string GetLine;
        cin >> GetLine;
        for(int j=0; j<7; j++){
            board[i][j] = GetLine[j];
        }
    }
    if(Calculate(board, moves, direct_col, direct_row)){
        Print_Answer(moves);
    }else{
        cout << "Loser" << endl;
    }
    return 0;
}
