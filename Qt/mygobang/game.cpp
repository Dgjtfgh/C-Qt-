#include "game.h"
#include <QDebug>

game::game()
{

}

void game::startGame(){
    board.clear();
    board.fill(QVector<int>(kBoardSizeNum ,0),kBoardSizeNum);
    stack.clear();
    // 白方下为true,黑方下位false
    playflag = true;
}

void game::updateGameMap(int row, int col)
{
    if (playflag)
        board[row][col] = 1;
    else
        board[row][col] = -1;
    // 换手
    playflag = !playflag;
}

 void game::actionByPerson(int row, int col) {
     updateGameMap(row, col);
     stack.append(std::make_pair(row, col));
 }

 bool game::isWin(int row, int col){
     // 水平方向
     for (int i = 0; i < 5; i++) {
         if(col-i >= 0 && col-i+4 < kBoardSizeNum &&
                 board[row][col-i] == board[row][col-i+1] &&
                 board[row][col-i] == board[row][col-i+2] &&
                 board[row][col-i] == board[row][col-i+3] &&
                 board[row][col-i] == board[row][col-i+4]) {
             return true;
         }
     }
     // 竖直方向
     for (int i = 0; i < 5; i++) {
         if(row-i >= 0 && row-i+4 < kBoardSizeNum &&
                 board[row-i][col] == board[row-i+1][col] &&
                 board[row-i][col] == board[row-i+2][col] &&
                 board[row-i][col] == board[row-i+3][col] &&
                 board[row-i][col] == board[row-i+4][col]) {
             return true;
         }
     }
     // 左斜方向
     for (int i = 0; i < 5; i++) {
         if(row+i < kBoardSizeNum && row+i-4 >= 0 &&
                 col-i >= 0 && col-i+4 < kBoardSizeNum &&
                 board[row+i][col-i] == board[row+i-1][col-i+1] &&
                 board[row+i][col-i] == board[row+i-2][col-i+2] &&
                 board[row+i][col-i] == board[row+i-3][col-i+3] &&
                 board[row+i][col-i] == board[row+i-4][col-i+4]) {
             return true;
         }
     }
     // 右斜方向
     for (int i = 0; i < 5; i++) {
         if(row-i >= 0 && row-i+4 < kBoardSizeNum &&
                 col-i >= 0 && col-i+4 < kBoardSizeNum &&
                 board[row-i][col-i] == board[row-i+1][col-i+1] &&
                 board[row-i][col-i] == board[row-i+2][col-i+2] &&
                 board[row-i][col-i] == board[row-i+3][col-i+3] &&
                 board[row-i][col-i] == board[row-i+4][col-i+4]) {
             return true;
         }
     }
     return false;
 }

 bool game::isDeadGame(){
     // 遍历棋盘看是否填满
     for (int i=0; i <kBoardSizeNum; i++) {
         for (int j=0; j < kBoardSizeNum; j++) {
             if (!(board[i][j] == 1 || board[i][j] == -1))
                 return false;
         }
     }
     return true;
 }

 void game::regret(){
     if (status == OPEN) {
         return;
     }
     if (!stack.empty()) {
         std::pair<int, int>lastPos = stack.last();
         qDebug()<<lastPos;
         int row = lastPos.first;
         int col = lastPos.second;
         board[row][col] = 0;
         playflag = !playflag;
         stack.removeLast();
     }
 }
