//
//  islandNumbers_bfs.c
//
//  Created by LucreciaLin on 2019/7/13.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

#include <stdio.h>

/*
 實作「Floodfill 漫水填滿法（種子填滿法）」：用不同編號標出地圖中的各個島嶼。
 */

struct note                                     // 用一個結構體實作queue。
{
    int mapCol;
    int mapRow;
};

int main()
{
    struct note queue[2501];                    // 因地圖大小範圍為50 * 50以內，因此queue擴展不超過2500個。這邊因從1開始算，所以為2501。
    int map[51][51];                            // 假設地圖最多空間為50 * 50。因從(1, 1)開始算，所以給51 * 51。
    int book[51][51];                           // 用來記錄已找過的位置，避免重複尋找。因配合記錄已在地圖找過的位置，book陣列大小需和地圖一樣大。
    int totalMapCols;
    int totalMapRows;
    int nextPossiblePosition[4][2] = {          // 方便程式設計，定義一個方向陣列。
        {0, 1},                                 // 代表從某點向右走。
        {1, 0},                                 // 代表從某點向下走。
        {0, -1},                                // 代表從某點向左走。
        {-1, 0}                                 // 代表從某點向上走。
    };
    int islandNo = 0;                           // 初始化島嶼標號器。島嶼編號將由-1開始遞減。因地圖中0代表海洋，1~9代表陸地。
    
    printf("請輸入尋島地圖大小，第一個數為欄，第二個數為列：\n");
    scanf("%d %d", &totalMapCols, &totalMapRows);
    
    // 以下為建造尋島地圖。
    printf("請建造尋島地圖內容：\n");
    for (int i = 1; i <= totalMapCols; i++)
    {
        for (int j = 1; j <= totalMapRows; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }
    
    int head = 1;                                       // queue初始化。
    int tail = 1;                                       // queue初始化。
    
    // 以下計算總共有多少個島嶼。
    for (int i = 1; i <= totalMapCols; i++)
    {
        for (int j = 1; j <= totalMapRows; j++)
        {
            if (map[i][j] > 0)                                          // 當該位置大於0，代表是陸地，便有成為某島嶼的可能。
            {
                islandNo--;                                             // 給定島嶼編號。每當發現一個島嶼，就給一個編號。
                book[i][j] = 1;                                         // 記錄已找過的位置。避免之後重複尋找。
                queue[tail].mapCol = i;                                 // 可能位置入queue。
                queue[tail].mapRow = j;                                 // 可能位置入queue。
                map[i][j] = islandNo;                                   // 標示該島嶼編號在地圖上。
                tail++;                                                 // 代表入queue後tail要加1。
                
                int nextPossibleCol;                                    // 下一步所在的行。
                int nextPossibleRow;                                    // 下一步所在的列。
                int fourDirections = 3;                                 // 因從某點可能的下一步方向共有4種：右、下、左、上。
                while (head < tail)                                     // 如果queue不為空，代表所有可能還未全部嘗試完，需繼續loop。head和tail相等代表為空。
                {
                    for (int i = 0; i <= fourDirections; i++)           // 列舉4種走法，這裡規定順序為「順時針列舉」，也就是分別依「右、下、左、上」順序嘗試每種可能走法。
                    {
                        nextPossibleCol = queue[head].mapCol + nextPossiblePosition[i][0];      // 計算下一步的行。
                        nextPossibleRow = queue[head].mapRow + nextPossiblePosition[i][1];      // 計算下一步的列。
                        
                        if (nextPossibleCol < 1 || nextPossibleCol > totalMapCols ||
                            nextPossibleRow < 1 || nextPossibleRow > totalMapRows)              // 確認下一步是否有越界（超出地圖範圍）。
                        {
                            continue;
                        }
                        
                        if (map[nextPossibleCol][nextPossibleRow] > 0 && book[nextPossibleCol][nextPossibleRow] == 0)   // 判斷是否為陸地與是否為尚未找過的位置。
                        {
                            book[nextPossibleCol][nextPossibleRow] = 1;                         // 記錄已找過的位置。避免之後重複尋找。
                            queue[tail].mapCol = nextPossibleCol;                               // 可能位置入queue。
                            queue[tail].mapRow = nextPossibleRow;                               // 可能位置入queue。
                            map[nextPossibleCol][nextPossibleRow] = islandNo;                   // 標示該島嶼編號在地圖上。
                            tail++;                                                             // 代表入queue後tail要加1。
                        }
                    }
                    head++;                                                                     // 當一個位置擴展結束後，這個位置要head++，也就是代表出queue，這樣才能繼續對下個位置進行擴展。
                }
            }
        }
    }

    // 輸出含有各個島嶼編號的地圖：
    printf("得到含有各個島嶼編號的地圖：\n");
    for (int i = 1; i <= totalMapCols; i++)
    {
        for (int j = 1; j <= totalMapRows; j++)
        {
            printf("%3d", map[i][j]);
        }
        printf("\n");
    }
    
    // 輸出總共有幾個島嶼。
    printf("總共有%d個島嶼。\n", -islandNo);     // 這邊「加負號」是因編號為負的。
    
    getchar();                                // 因緩衝區仍有data。
    getchar();                                // 用來暫停程式，看結果。
    
    return 0;
}
