//
//  bombermanGame.c
//
//  Created by LucreciaLin on 2019/5/26.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

/*
 簡化版炸彈人遊戲：
 只有一個炸彈。
 . 代表是可放炸彈的空地。
 # 代表牆壁。
 E 代表要消滅的敵人。
 
 目的：尋找二維迷宮中何處放置炸彈能一次炸最多敵人？
 */


#include <stdio.h>

void calDestroyedEnemy(int currentColumn, int currentRow, int direction);

char maze[20][20];  // 假設迷宮最多空間為20 * 20。
int sumOfEnemy;

int main()
{
    int i;
    int maxSumOfEnemy = 0;
    int finalColumn = 0;
    int finalRow = 0;
    int totalColumns;
    int totalRows;
    
    printf("請輸入迷宮大小，第一個數為欄，第二個數為列：\n");
    scanf("%d %d", &totalColumns, &totalRows);
    
    // 以下為建造迷宮。
    int totalColumnsIdxs = totalColumns - 1;
    for (i = 0; i <= totalColumnsIdxs; i++)
    {
        scanf("%s", maze[i]);
    }
    
    // 以下列舉迷宮中每個位置。
    int totalRowsIdxs = totalRows - 1;
    for (i = 0; i <= totalColumnsIdxs; i++)
    {
        for (int j = 0; j <= totalRowsIdxs; j++)
        {
            if (maze[i][j] == '.')                  // 如果該位置是空地。
            {
                sumOfEnemy = 0;                     // 計算在該空地放炸彈時能炸的敵人總數。
                calDestroyedEnemy(i, j, 1);         // 從該空地往上面方向炸，能炸多少敵人。1代表往上。
                
                calDestroyedEnemy(i, j, -1);        // 從該空地往下面方向炸，能炸多少敵人。-1代表往下。
                
                calDestroyedEnemy(i, j, 2);         // 從該空地往右邊方向炸，能炸多少敵人。2代表往右。
                
                calDestroyedEnemy(i, j, -2);        // 從該空地往左邊方向炸，能炸多少敵人。-2代表往左。
                
                // 以下為是否更新「一次能炸最多敵人」的記錄
                if (sumOfEnemy > maxSumOfEnemy)
                {
                    maxSumOfEnemy = sumOfEnemy;
                    finalColumn = i;
                    finalRow = j;
                }
            }
        }
    }
    
    printf("將炸彈放置在（%d, %d），最多可以消滅%d個敵人\n", finalColumn, finalRow, maxSumOfEnemy);
    getchar();      // 因緩衝區仍有data。
    getchar();      // 用來暫停程式，看結果。
    
    return 0;
}

void calDestroyedEnemy(int currentColumn, int currentRow, int direction)
{
    while (maze[currentColumn][currentRow] != '#')      // 如果還沒碰到不能炸的牆壁。
    {
        if (maze[currentColumn][currentRow] == 'E')     // 如果碰到敵人存在的位置。
        {
            sumOfEnemy++;                               // 就計數能炸的敵人總數。
        }
        switch (direction)
        {
            case 1:                                     // 往上
                currentColumn--;                        // 繼續往上方統計能炸的敵人
                break;
            case -1:                                    // 往下
                currentColumn++;                        // 繼續往下方統計能炸的敵人
                break;
            case 2:                                     // 往右
                currentRow++;                           // 繼續往右方統計能炸的敵人
                break;
            case -2:                                    // 往左
                currentRow--;                           // 繼續往左方統計能炸的敵人
                break;
            default:
                printf("請確認方向規格是否有誤");
                break;
        }
    }
}
