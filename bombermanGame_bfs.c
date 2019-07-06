//
//  bombermanGame_bfs.c
//
//  Created by LucreciaLin on 2019/7/6.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

/*
 炸彈人遊戲 -- 使用BFS：
 只有一個炸彈。
 . 代表平地。
 # 代表牆壁。
 E 代表要消滅的敵人。
 
 目的：尋找二維迷宮中何處放置炸彈能一次炸最多敵人？
 */

#include <stdio.h>

struct note                 // 用一個結構體實作queue。
{
    int mazeCol;
    int mazeRow;
};

char maze[20][20];          // 假設迷宮最多空間為20 * 20。
int sumOfEnemyInPos;        // 用來計數該位置能炸的敵人總數。

void calDestroyedEnemyInPos(int currentMazeCol, int currentMazeRow, int direction);

int main()
{
    struct note queue[401];                 // 因迷宮大小範圍為20 * 20以內，因此queue擴展不超過400個。這邊因從1開始算，所以為401。
    int head = 1;                           // queue初始化。
    int tail = 1;                           // queue初始化。
    int book[20][20] = {0};                 // 用來記錄已走過的位置，避免重複走到。因配合記錄已在迷宮走過的位置，book陣列大小需和迷宮一樣大。
    int maxSumOfEnemy = 0;
    int finalMazeCol = 0;
    int finalMazeRow = 0;
    int totalMazeCols;
    int totalMazeRows;
    int nextPossiblePosition[4][2] = {      // 方便程式設計，定義一個方向陣列。
        {0, 1},                             // 代表從某點向右走。
        {1, 0},                             // 代表從某點向下走。
        {0, -1},                            // 代表從某點向左走。
        {-1, 0}                             // 代表從某點向上走。
    };
    
    printf("請輸入迷宮大小，第一個數為欄，第二個數為列：\n");
    scanf("%d %d", &totalMazeCols, &totalMazeRows);
    
    int startingMazeCol;
    int startingMazeRow;
    printf("請輸入小人的起始位置：\n");
    scanf("%d %d", &startingMazeCol, &startingMazeRow);
    
    
    // 以下為建造迷宮。
    printf("請建造迷宮內容：\n");
    int totalMazeColsIdxs = totalMazeCols - 1;
    for (int i = 0; i <= totalMazeColsIdxs; i++)
    {
        scanf("%s", maze[i]);
    }
    
    // 將小人一開始位置塞入queue中。
    queue[tail].mazeCol = startingMazeCol;
    queue[tail].mazeRow = startingMazeRow;
    tail++;                                                             // 代表入queue。
    book[startingMazeCol][startingMazeRow] = 1;                         // 記錄已走過的位置。避免之後重複走到。
    
    sumOfEnemyInPos = 0;                                                // 計算在該空地放炸彈時能炸的敵人總數。
    calDestroyedEnemyInPos(startingMazeCol, startingMazeRow, 1);        // 從該空地往上面方向炸，能炸多少敵人。1代表往上。
    calDestroyedEnemyInPos(startingMazeCol, startingMazeRow, -1);       // 從該空地往下面方向炸，能炸多少敵人。-1代表往下。
    calDestroyedEnemyInPos(startingMazeCol, startingMazeRow, 2);        // 從該空地往右邊方向炸，能炸多少敵人。2代表往右。
    calDestroyedEnemyInPos(startingMazeCol, startingMazeRow, -2);       // 從該空地往左邊方向炸，能炸多少敵人。-2代表往左。
    maxSumOfEnemy = sumOfEnemyInPos;
    finalMazeCol = startingMazeCol;
    finalMazeRow = startingMazeRow;
    
    int nextPossibleCol;                            // 下一步所在的行。
    int nextPossibleRow;                            // 下一步所在的列。
    int fourDirections = 3;                         // 因從某點可能的下一步方向共有4種：右、下、左、上。
    while (head < tail)                             // 如果queue不為空，代表所有可能還未全部嘗試完，需繼續loop。head和tail相等代表為空。
    {
        for (int i = 0; i <= fourDirections; i++)   // 列舉4種走法，這裡規定順序為「順時針列舉」，也就是分別依「右、下、左、上」順序嘗試每種可能走法。
        {
            nextPossibleCol = queue[head].mazeCol + nextPossiblePosition[i][0];     // 計算下一步的行。
            nextPossibleRow = queue[head].mazeRow + nextPossiblePosition[i][1];     // 計算下一步的列。
            if (nextPossibleCol < 0 || nextPossibleCol > totalMazeCols - 1 ||
                nextPossibleRow < 0 || nextPossibleRow > totalMazeRows - 1)         // 確認下一步是否有越界（超出迷宮範圍）。其中減1是因「迷宮起始點為從(0, 0)開始」。
            {
                continue;
            }
            if (maze[nextPossibleCol][nextPossibleRow] == '.' &&
                book[nextPossibleCol][nextPossibleRow] == 0)                        // 判斷是否為平地與是否為尚未走過的位置。
            {
                book[nextPossibleCol][nextPossibleRow] = 1;                         // 記錄已走過的位置。避免之後重複走到。
                queue[tail].mazeCol = nextPossibleCol;                              // 可能位置入queue。
                queue[tail].mazeRow = nextPossibleRow;                              // 可能位置入queue。
                tail++;                                                             // 入queue。
                
                sumOfEnemyInPos = 0;                                                // 計算在該空地放炸彈時能炸的敵人總數。
                calDestroyedEnemyInPos(nextPossibleCol, nextPossibleRow, 1);        // 從該空地往上面方向炸，能炸多少敵人。1代表往上。
                calDestroyedEnemyInPos(nextPossibleCol, nextPossibleRow, -1);       // 從該空地往下面方向炸，能炸多少敵人。-1代表往下。
                calDestroyedEnemyInPos(nextPossibleCol, nextPossibleRow, 2);        // 從該空地往右邊方向炸，能炸多少敵人。2代表往右。
                calDestroyedEnemyInPos(nextPossibleCol, nextPossibleRow, -2);       // 從該空地往左邊方向炸，能炸多少敵人。-2代表往左。
                // 以下為是否更新「一次能炸最多敵人」的記錄。
                if (sumOfEnemyInPos > maxSumOfEnemy)
                {
                    maxSumOfEnemy = sumOfEnemyInPos;
                    finalMazeCol = nextPossibleCol;
                    finalMazeRow = nextPossibleRow;
                }
            }
        }
        head++;     // 當一個位置擴展結束後，這個位置要head++，也就是代表出queue，這樣才能繼續對下個位置進行擴展。
    }
    
    printf("將炸彈放置在（%d, %d），最多可以消滅%d個敵人\n", finalMazeCol, finalMazeRow, maxSumOfEnemy);
    getchar();      // 因緩衝區仍有data。
    getchar();      // 用來暫停程式，看結果。
    
    return 0;
}

void calDestroyedEnemyInPos(int currentMazeCol, int currentMazeRow, int direction)
{
    while (maze[currentMazeCol][currentMazeRow] != '#')         // 如果還沒碰到不能炸的牆壁。
    {
        if (maze[currentMazeCol][currentMazeRow] == 'E')        // 如果碰到敵人存在的位置。
        {
            sumOfEnemyInPos++;                                  // 就計數能炸的敵人總數。
        }
        switch (direction)
        {
            case 1:                                             // 往上。
                currentMazeCol--;                               // 繼續往上方統計能炸的敵人。
                break;
            case -1:                                            // 往下
                currentMazeCol++;                               // 繼續往下方統計能炸的敵人。
                break;
            case 2:                                             // 往右。
                currentMazeRow++;                               // 繼續往右方統計能炸的敵人。
                break;
            case -2:                                            // 往左。
                currentMazeRow--;                               // 繼續往左方統計能炸的敵人。
                break;
            default:
                printf("請確認方向規格是否有誤");
                break;
        }
    }
}
