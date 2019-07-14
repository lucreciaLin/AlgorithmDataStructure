//
//  islandExploration_dfs.c
//
//  Created by LucreciaLin on 2019/7/13.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

/*
 尋找島嶼遊戲：
 
 探險者得到一張含有多個島嶼的地圖：0代表海洋、1~9代表陸地。
 當探險者站在某點時，想知道其所在的島嶼大小面積是多少？
 */

#include <stdio.h>

int map[51][51];                        // 假設地圖最多空間為50 * 50。因從(1, 1)開始算，所以給51 * 51。
int book[51][51];                       // 用來記錄已找過的位置，避免重複尋找。因配合記錄已在地圖找過的位置，book陣列大小需和地圖一樣大。
int totalMapCols;
int totalMapRows;
int exploredIslandArea;                 // 用來計數島嶼面積。

void doDFS(int currentMapCol, int currentMapRow, int playedIsland);        // 進行深度優先搜尋。

int main()
{
    printf("請輸入尋島地圖大小，第一個數為欄，第二個數為列：\n");
    scanf("%d %d", &totalMapCols, &totalMapRows);
    
    int startingMapCol;
    int startingMapRow;
    printf("請輸入探險者開始探險位置：\n");
    scanf("%d %d", &startingMapCol, &startingMapRow);
    
    // 以下為建造尋島地圖。
    printf("請建造尋島地圖內容：\n");
    for (int i = 1; i <= totalMapCols; i++)
    {
        for (int j = 1; j <= totalMapRows; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }
    
    // 從探險者一開始位置開始嘗試可能
    book[startingMapCol][startingMapRow] = 1;               // 記錄已找過的位置。避免之後重複尋找。
    exploredIslandArea = 1;                                 // 計數島嶼面積。
    int playedIsland = -1;                                  // 用來標示探險者所在島嶼位置在地圖上。-1代表探險者所在島嶼區域。
    doDFS(startingMapCol, startingMapRow, playedIsland);
    
    printf("\n得到島嶼的大小：%d\n", exploredIslandArea);
    // 輸出含有探險者已玩過的地圖：
    printf("得到含有探險者已玩過的地圖：\n");
    for (int i = 1; i <= totalMapCols; i++)
    {
        for (int j = 1; j <= totalMapRows; j++)
        {
            printf("%3d", map[i][j]);
        }
        printf("\n");
    }
    
    getchar();  // 因緩衝區仍有data。
    getchar();  // 用來暫停程式，看結果。
    
    return 0;
}

void doDFS(int currentMapCol, int currentMapRow, int playedIsland)
{
    int nextPossiblePosition[4][2] = {                                          // 方便程式設計，定義一個方向陣列。
        {0, 1},                                                                 // 代表從某點向右走。
        {1, 0},                                                                 // 代表從某點向下走。
        {0, -1},                                                                // 代表從某點向左走。
        {-1, 0}                                                                 // 代表從某點向上走。
    };
    map[currentMapCol][currentMapRow] = playedIsland;                           // 標示探險者所在島嶼位置在地圖上。
    int nextPossibleCol;                                                        // 下一步所在的行。
    int nextPossibleRow;                                                        // 下一步所在的列。
    int fourDirections = 3;                                                     // 因從某點可能的下一步方向共有4種：右、下、左、上。
    for (int i = 0; i <= fourDirections; i++)                                   // 列舉4種走法，這裡規定順序為「順時針列舉」，也就是分別依「右、下、左、上」順序嘗試每種可能走法。
    {
        nextPossibleCol = currentMapCol + nextPossiblePosition[i][0];           // 計算下一步的行。
        nextPossibleRow = currentMapRow + nextPossiblePosition[i][1];           // 計算下一步的列。
        
        if (nextPossibleCol < 1 || nextPossibleCol > totalMapCols ||
            nextPossibleRow < 1 || nextPossibleRow > totalMapRows)              // 確認下一步是否有越界（超出地圖範圍）。
        {
            continue;
        }
        
        if (map[nextPossibleCol][nextPossibleRow] > 0 && book[nextPossibleCol][nextPossibleRow] == 0)   // 判斷是否為陸地與是否為尚未找過的位置。
        {
            exploredIslandArea++;                                               // 計數島嶼面積。
            book[nextPossibleCol][nextPossibleRow] = 1;                         // 記錄已找過的位置。避免之後重複尋找。
            doDFS(nextPossibleCol, nextPossibleRow, playedIsland);              // 繼續嘗試下個位置的可能走法。
        }
    }
    
    return;
}
