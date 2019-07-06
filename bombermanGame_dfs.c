//
//  bombermanGame_dfs.c
//
//  Created by LucreciaLin on 2019/7/6.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

/*
 炸彈人遊戲 -- 使用DFS：
 只有一個炸彈。
 . 代表平地。
 # 代表牆壁。
 E 代表要消滅的敵人。
 
 目的：尋找二維迷宮中何處放置炸彈能一次炸最多敵人？
 */

#include <stdio.h>

char maze[20][20];              // 假設迷宮最多空間為20 * 20。
int book[20][20];               // 用來記錄已走過的位置，避免重複走到。因配合記錄已在迷宮走過的位置，book陣列大小需和迷宮一樣大。
int sumOfEnemyInPos;            // 用來計數該位置能炸的敵人總數。
int maxSumOfEnemy = 0;
int finalMazeCol = 0;
int finalMazeRow = 0;
int totalMazeCols;
int totalMazeRows;

void calDestroyedEnemyInPos(int currentMazeCol, int currentMazeRow, int direction);
void doDFS(int currentMazeCol, int currentMazeRow);                    // 進行深度優先搜尋。

int main()
{
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
    
    // 從小人一開始位置開始嘗試可能
    book[startingMazeCol][startingMazeRow] = 1;                         // 記錄已走過的位置。避免之後重複走到。
    sumOfEnemyInPos = 0;                                                // 計算在該空地放炸彈時能炸的敵人總數。
    calDestroyedEnemyInPos(startingMazeCol, startingMazeRow, 1);        // 從該空地往上面方向炸，能炸多少敵人。1代表往上。
    calDestroyedEnemyInPos(startingMazeCol, startingMazeRow, -1);       // 從該空地往下面方向炸，能炸多少敵人。-1代表往下。
    calDestroyedEnemyInPos(startingMazeCol, startingMazeRow, 2);        // 從該空地往右邊方向炸，能炸多少敵人。2代表往右。
    calDestroyedEnemyInPos(startingMazeCol, startingMazeRow, -2);       // 從該空地往左邊方向炸，能炸多少敵人。-2代表往左。
    maxSumOfEnemy = sumOfEnemyInPos;
    finalMazeCol = startingMazeCol;
    finalMazeRow = startingMazeRow;
    
    doDFS(startingMazeCol, startingMazeRow);
    
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

void doDFS(int currentMazeCol, int currentMazeRow)
{
    int nextPossiblePosition[4][2] = {                                // 方便程式設計，定義一個方向陣列。
        {0, 1},                                                       // 代表從某點向右走。
        {1, 0},                                                       // 代表從某點向下走。
        {0, -1},                                                      // 代表從某點向左走。
        {-1, 0}                                                       // 代表從某點向上走。
    };
    
    sumOfEnemyInPos = 0;                                              // 計算在該空地放炸彈時能炸的敵人總數。
    calDestroyedEnemyInPos(currentMazeCol, currentMazeRow, 1);        // 從該空地往上面方向炸，能炸多少敵人。1代表往上。
    calDestroyedEnemyInPos(currentMazeCol, currentMazeRow, -1);       // 從該空地往下面方向炸，能炸多少敵人。-1代表往下。
    calDestroyedEnemyInPos(currentMazeCol, currentMazeRow, 2);        // 從該空地往右邊方向炸，能炸多少敵人。2代表往右。
    calDestroyedEnemyInPos(currentMazeCol, currentMazeRow, -2);       // 從該空地往左邊方向炸，能炸多少敵人。-2代表往左。
    // 以下為是否更新「一次能炸最多敵人」的記錄。
    if (sumOfEnemyInPos > maxSumOfEnemy)
    {
        maxSumOfEnemy = sumOfEnemyInPos;
        finalMazeCol = currentMazeCol;
        finalMazeRow = currentMazeRow;
    }
    
    int nextPossibleCol;                                                    // 下一步所在的行。
    int nextPossibleRow;                                                    // 下一步所在的列。
    int fourDirections = 3;                                                 // 因從某點可能的下一步方向共有4種：右、下、左、上。
    for (int i = 0; i <= fourDirections; i++)                               // 列舉4種走法，這裡規定順序為「順時針列舉」，也就是分別依「右、下、左、上」順序嘗試每種可能走法。
    {
        nextPossibleCol = currentMazeCol + nextPossiblePosition[i][0];      // 計算下一步的行。
        nextPossibleRow = currentMazeRow + nextPossiblePosition[i][1];      // 下一步所在的列。
        if (nextPossibleCol < 0 || nextPossibleCol > totalMazeCols - 1 ||
            nextPossibleRow < 0 || nextPossibleRow > totalMazeRows - 1)     // 確認下一步是否有越界（超出迷宮範圍）。其中減1是因「迷宮起始點為從(0, 0)開始」。
        {
            continue;
        }
        
        if (maze[nextPossibleCol][nextPossibleRow] == '.' &&
            book[nextPossibleCol][nextPossibleRow] == 0)                    // 判斷是否為平地與是否為尚未走過的位置。
        {
            book[nextPossibleCol][nextPossibleRow] = 1;                     // 記錄已走過的位置。避免之後重複走到。
            doDFS(nextPossibleCol, nextPossibleRow);                        // 繼續嘗試下個位置的可能走法。
        }
    }
    
    return;
}
