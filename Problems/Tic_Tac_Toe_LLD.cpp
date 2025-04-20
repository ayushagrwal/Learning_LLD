// Problem Statement
// Let's look at the game of Tic Tac Toe. Tic Tac Toe is a two-player strategy game played on a 3*3 grid. There are 9 empty cells and 9 pieces - 5 pieces of 'X' and 4 pieces of 'O'

// The game starts with an empty grid.

// Rules of the game
// The game is played between two players. One player owns the X pieces and can put it on any of the empty cells in the grid. The other player owns the O pieces and can in any of the empty cells.
// The player with X makes the first turn. Each player plays alternately after that.
// The first player to form a horizontal/vertical/diagonal sequence wins.
// Requirements
// Create a command-line application for tic tac toe with the following requirements:

// Ask the user for the names of the two players
// Print the grid after initializing
// Allow the user to make moves on behalf of both the players.
// The user will make a move by entering the cell position.
// You need to determine the piece (X/O) and make the move if it is valid.
// Valid move:
// The piece is controlled by the player having the current turn
// The cell is empty
// If the move is invalid
// print 'Invalid Move'
// the same player plays again
// If the move is valid:
// put the piece on the cell
// print the board after the move
// Determine if a player has won or if there are no valid moves left. Ignore all moves mentioned after that.
// A position in the cell is represented by two values: row number (1-3) and column number (1-3).

// Examples
// 3 1 represents the cell at the extreme bottom-left (3rd row, 1st column)
// 1 3 represents the cell at the extreme top-right (1st row, 3rd column)
// Input/Output Format
// The code should strictly follow the input/output format and will be tested with provided test cases.

// Input Format
// Multiple lines with each line containing the Cell Position. The row and column numbers will be separated by a space.

// Stop taking the input when you encounter the word exit.

// Output Format
// Print the initial grid. This would be followed by the grid after each move. In case of an invalid move, do not print the grid and instead print:

// Invalid Move

// The board needs to be printed in the following format based on the respective position:

// X X O
// - - X
// O O -
// Here,

// X and O represent the different pieces. An empty cell is represented by a hyphen (-).

// The initial position of the board would be

// - - -
// - - -
// - - -
// If the player wins after a move, print: 'Player_Name won the game'

// If there are no valid moves left for any player, print 'Game Over'

// Examples
// Sample Input
// X Gaurav
// O Sagar
// 2 2
// 1 3
// 1 1
// 1 2
// 2 2
// 3 3
// exit
// Expected Output
// - - -
// - - -
// - - -
// - - -
// - X -
// - - -
// - - O
// - X -
// - - -
// X - O
// - X -
// - - -
// X O O
// - X -
// - - -
// Invalid Move
// X O O
// - X -
// - - X
// Gaurav won the game
// Sample Input
// X Gaurav
// O Sagar
// 2 3
// 1 2
// 2 2
// 2 1
// 1 1
// 3 3
// 3 2
// 3 1
// 1 3
// exit
// Expected Output
// - - -
// - - -
// - - -
// - - -
// - - X
// - - -
// - O -
// - - X
// - - -
// - O -
// - X X
// - - -
// - O -
// O X X
// - - -
// X O -
// O X X
// - - -
// X O -
// O X X
// - - O
// X O -
// O X X
// - X O
// X O X
// O X X
// O X O
// Game Over
// Sample Input
// X Gaurav
// O Sagar
// exit
// Expected Output
// - - -
// - - -
// - - -



#include <bits/stdc++.h>
using namespace std;

class Board{
    private:
        map<char,string> userMap;  //blocks X,O --> userNames
        map<pair<int,int>, char> boardMap;    //board positions 1,1 - 3,3 --> blocks X,O
    public:
        Board() {
            for(int i=1;i<=3;i++){
                for(int j=1;j<=3;j++){
                    boardMap.insert({{i,j},'-'});
                }
            }
        }

        void addUser(pair<char,string> pr){
            userMap[pr.first] = pr.second;
            return;
        }

        void printBoard(){
            int ct=0;
            for(auto it: boardMap){
                cout<<it.second;
                ++ct;
                if(ct%3==0){
                    cout<<endl;
                } else {
                    cout<<" ";
                }
            }
        }

        bool checkWinner(){
            if(boardMap[{1,1}] != '-' && boardMap[{1,1}] == boardMap[{2,2}] && boardMap[{3,3}] == boardMap[{2,2}]){
                cout<< userMap[boardMap[{1,1}]] + " " + "won the game"<<endl;
                return 1;
            }
            if(boardMap[{1,1}] != '-' && boardMap[{1,1}] == boardMap[{1,2}] && boardMap[{1,3}] == boardMap[{1,2}]){
                cout<< userMap[boardMap[{1,1}]] + " " + "won the game"<<endl;
                return 1;
            }
            if(boardMap[{1,1}] != '-' && boardMap[{1,1}] == boardMap[{2,1}] && boardMap[{3,1}] == boardMap[{2,1}]){
                cout<< userMap[boardMap[{1,1}]] + " " + "won the game"<<endl;
                return 1;
            }
            if(boardMap[{2,1}] != '-' && boardMap[{2,1}] == boardMap[{2,2}] && boardMap[{2,1}] == boardMap[{2,3}]){
                cout<< userMap[boardMap[{2,1}]] + " " + "won the game"<<endl;
                return 1;
            }
            if(boardMap[{3,1}] != '-' && boardMap[{3,1}] == boardMap[{3,2}] && boardMap[{3,1}] == boardMap[{3,3}]){
                cout<< userMap[boardMap[{3,1}]] + " " + "won the game"<<endl;
                return 1;
            }
            if(boardMap[{1,2}] != '-' && boardMap[{1,2}] == boardMap[{2,2}] && boardMap[{1,2}] == boardMap[{3,2}]){
                cout<< userMap[boardMap[{1,2}]] + " " + "won the game"<<endl;
                return 1;
            }
            if(boardMap[{1,3}] != '-' && boardMap[{1,3}] == boardMap[{2,3}] && boardMap[{1,3}] == boardMap[{3,3}]){
                cout<< userMap[boardMap[{1,3}]] + " " + "won the game"<<endl;
                return 1;
            }
            if(boardMap[{1,3}] != '-' && boardMap[{1,3}] == boardMap[{2,2}] && boardMap[{1,3}] == boardMap[{3,1}]){
                cout<< userMap[boardMap[{1,3}]] + " " + "won the game"<<endl;
                return 1;
            }
            return 0;
        }
        
        bool checkFilled(){
            for(auto it: boardMap){
                if(it.second == '-'){
                    return 0;
                }
            }
            return 1;
        }

        bool putBlock(char block, pair<int,int> position){
            if(boardMap.find(position) == boardMap.end()){
                return 0;
            } else {
                auto it = boardMap.find(position);
                if((*it).second == '-'){
                    (*it).second = block;
                    printBoard();
                    return 1;
                } else {
                    return 0;
                }
            }
            return 0;
        }

};

int main(){

    string cmd;
    map<char,string> umap;
    int ct=0;
    char currentBlock = 'X';

    Board B1;

    while(getline(cin,cmd)){
        if(ct<2){
            stringstream ss(cmd);
            string s;
            char c;
            ss>>c;
            ss>>s;
            ++ct;
            B1.addUser({c,s});
        } else {
            if(cmd == "exit"){
                B1.printBoard();
                break;
            } else {
                stringstream ss1(cmd);
                int x,y;
                ss1>>x;
                ss1>>y;
                bool pb = B1.putBlock(currentBlock, {x,y});
                if(pb){
                    if(currentBlock == 'X'){
                        currentBlock = 'O';
                    } else {
                        currentBlock = 'X';
                    }
                } else {
                    cout<<"Invalid Move"<<endl;
                }

                bool cw = B1.checkWinner();
                if(cw){
                    break;
                } else {
                    bool cf = B1.checkFilled();
                    if(cf){
                        cout<<"Game Over"<<endl;
                        break;
                    }
                }
            }
        }
    }


    return 0;
}