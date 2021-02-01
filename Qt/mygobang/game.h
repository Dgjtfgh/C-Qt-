#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QPoint>
//#include <QStack>

const int kBoardMargin = 35; // 棋盘边缘空隙
const int kRadius = 15;      // 棋子半径
const int kMarkSize = 9;     // 落子标记边长
const int kBlockSize = 40;   // 格子的大小
const int kPosDelta = 19;    // 鼠标点击的模糊距离上限
const int kBoardSizeNum = 15; // 棋盘尺寸

// 游戏状态
enum GameStatus
{
    PLAYING,
    WIN,
    DEAD,
    OPEN
};

class game
{
public:
    game();
    QVector<QVector<int>> board; // 空白为0，白子1，黑子-1
    QVector <std::pair<int, int>> stack;  // 栈  悔棋
    bool playflag;
    GameStatus status;

    void startGame(); // 开始游戏
    void actionByPerson(int row, int col);
    void updateGameMap(int row, int col); // 每次落子后更新游戏棋盘
    bool isWin(int row, int col); // 判断游戏是否胜利
    bool isDeadGame(); // 判断是否和棋
    void regret();//悔棋
};

#endif // GAME_H
