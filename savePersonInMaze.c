//
//  savePersonInMaze.c
//
//  Created by LucreciaLin on 2019/6/23.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

/*
 
 在二維迷宮中，如何用最少步數搜救到迷路的人？
 
 */

#include <stdio.h>

int mazeCols;                       // 迷宮總行數。
int mazeRows;                       // 迷宮總列數。
int lostedPersonCol;                // 迷路的人所在的行。
int lostedPersonRow;                // 迷路的人所在的列。
int minFindingStep = 99999999;      // 從全部搜救路徑中記錄某次搜救路徑為「所需的最少步數」。
int mazeWithObstacles[51][51];      // 代表迷宮內容，0為空地，1為障礙物。迷宮最大為50 * 50，因想從1開始算，所以給51 * 51。
int book[51][51];                   // 用來記錄該次搜救路徑已走過的位置，避免重複走到。因配合記錄已在迷宮走過的位置，book陣列大小需和迷宮一樣大。

void doDFS(int currentCol, int currentRow, int currentFindingStep);     // 進行深度優先搜尋。

int main()
{
    int initialCol;                             // 為搜救者一開始所在的行。
    int initialRow;                             // 為搜救者一開始所在的列。
    printf("請輸入迷宮總行數和總列數：\n");
    scanf("%d %d", &mazeCols, &mazeRows);
    
    printf("請建造迷宮內容：\n");
    for (int i = 1; i <= mazeCols; i++)
    {
        for (int j = 1; j <= mazeRows; j++)
        {
            scanf("%d", &mazeWithObstacles[i][j]);
        }
    }
    
    printf("請輸入迷宮起點（也就是找人的起點）：\n");
    scanf("%d %d", &initialCol, &initialRow);
    printf("請輸入迷路的人的位置（也就是要找的人位置）：\n");
    scanf("%d %d", &lostedPersonCol, &lostedPersonRow);
    
    book[initialCol][initialRow] = 1;                           // 記錄已走過的位置。避免之後重複走到。
    int initialFindingStep = 0;                                 // 初始化尋找步數。
    doDFS(initialCol, initialRow, initialFindingStep);
    
    printf("得到最短尋找路徑的所需步數： %d", minFindingStep);
    getchar();                                                  // 因緩衝區仍有data。
    getchar();                                                  // 用來暫停程式，看結果。
    
    return 0;
}

void doDFS(int currentCol, int currentRow, int currentFindingStep)
{
    int nextPossiblePosition[4][2] = {        // 方便程式設計，定義一個方向陣列。
        {0, 1},                               // 代表從某點向右走。
        {1, 0},                               // 代表從某點向下走。
        {0, -1},                              // 代表從某點向左走。
        {-1, 0}                               // 代表從某點向上走。
    };
    int nextPossibleCol;                      // 下一步所在的行。
    int nextPossibleRow;                      // 下一步所在的列。
    
    if (currentCol == lostedPersonCol && currentRow == lostedPersonRow)     // 代表是否已到達迷路的人所在的位置。
    {
        if (currentFindingStep < minFindingStep)          // 是否更新「所需最小路徑」。
        {
            minFindingStep = currentFindingStep;
            return;                                       // 代表返回之前的一步，也就是指「最近呼叫的地方」。
        }
    }
    
    int fourDirections = 3;                         // 因從某點可能的下一步方向共有4種：右、下、左、上。
    for (int i = 0; i <= fourDirections; i++)       // 列舉4種走法，這裡規定順序為「順時針列舉」，也就是分別依「右、下、左、上」順序嘗試每種可能走法。
    {
        nextPossibleCol = currentCol + nextPossiblePosition[i][0];      // 計算下一步的行。
        nextPossibleRow = currentRow + nextPossiblePosition[i][1];      // 計算下一步的列。
        if (nextPossibleCol < 1 || nextPossibleCol > mazeCols ||
            nextPossibleRow < 1 || nextPossibleRow > mazeRows)          // 確認下一步是否有越界（超出迷宮範圍）。
        {
            continue;
        }
        if (mazeWithObstacles[nextPossibleCol][nextPossibleRow] == 0 &&
            book[nextPossibleCol][nextPossibleRow] == 0)                        // 確認下一步是否沒走到障礙物所在位置和是否沒有重複走到。
        {
            book[nextPossibleCol][nextPossibleRow] = 1;                         // 記錄已走過的位置。避免之後重複走到。
            doDFS(nextPossibleCol, nextPossibleRow, currentFindingStep + 1);    // 繼續嘗試下個位置的可能走法。
            book[nextPossibleCol][nextPossibleRow] = 0;                         // 因該位置的可能走法已嘗試結束，要還原以便給其他位置的可能走法去嘗試。
        }
    }
    
    return;
}
