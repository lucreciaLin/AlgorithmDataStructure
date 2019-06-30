//
//  bfs.c
//
//  Created by LucreciaLin on 2019/6/30.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

#include <stdio.h>

struct note                          // 用一個結構體實作queue。
{
    int mazeCol;
    int mazeRow;
    int parentNoInQueue;             // 指向前一個head，用以輸出路徑。但本次練習先不要求。
    int findingStep;                 // 尋找步數。
};

struct note queue[2501];             // 因迷宮大小範圍為50 * 50以內，因此queue擴展不超過2500個。這邊因從1開始算，所以為2501。
int mazeCols;
int mazeRows;
int lostedPersonCol;
int lostedPersonRow;
int mazeWithObstacles[51][51];       // 代表迷宮內容，0為空地，1為障礙物。迷宮最大為50 * 50，因想從1開始算，所以給51 * 51。
int book[51][51];                    // 用來記錄該次搜救路徑已走過的位置，避免重複走到。因配合記錄已在迷宮走過的位置，book陣列大小需和迷宮一樣大。
int tail = 1;                        // queue初始化。
int head = 1;                        // queue初始化。
int isArrivedLostedPersonLoc = 0;    // 標記是否到達迷路的人的位置。0為false，1為true。

void doBFS(int currentCol, int currentRow);     // 進行廣度優先搜尋（寬度優先搜尋）。

int main()
{
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
    
    int initialCol;
    int initialRow;
    printf("請輸入迷宮起點（也就是找人的起點）：\n");
    scanf("%d %d", &initialCol, &initialRow);

    printf("請輸入迷路的人的位置（也就是要找的人位置）：\n");
    scanf("%d %d", &lostedPersonCol, &lostedPersonRow);
    
    // 將搜救者一開始位置塞入queue中。
    queue[tail].mazeCol = initialCol;
    queue[tail].mazeRow = initialRow;
    tail++;                             // 代表入queue。
    book[initialCol][initialRow] = 1;   // 記錄已走過的位置。避免之後重複走到。
    
    doBFS(initialCol, initialRow);

    printf("得到最短尋找路徑的所需步數： %d", queue[tail-1].findingStep);     // 這邊tail - 1是因「tail是指queue尾（指最後有值的位置）的下一個位置」。
    getchar();                                                           // 因緩衝區仍有data。
    getchar();                                                           // 用來暫停程式，看結果。
    
    return 0;
}

void doBFS(int currentCol, int currentRow)
{
    int nextPossiblePosition[4][2] = {              // 方便程式設計，定義一個方向陣列。
        {0, 1},                                     // 代表從某點向右走。
        {1, 0},                                     // 代表從某點向下走。
        {0, -1},                                    // 代表從某點向左走。
        {-1, 0}                                     // 代表從某點向上走。
    };
    int nextPossibleCol;                            // 下一步所在的行。
    int nextPossibleRow;                            // 下一步所在的列。
    int fourDirections = 3;                         // 因從某點可能的下一步方向共有4種：右、下、左、上。
    while (head < tail)                             // 如果queue不為空，代表所有可能還未全部嘗試完，需繼續loop。head和tail相等代表為空。
    {
        for (int i = 0; i <= fourDirections; i++)   // 列舉4種走法，這裡規定順序為「順時針列舉」，也就是分別依「右、下、左、上」順序嘗試每種可能走法。
        {
            nextPossibleCol = queue[head].mazeCol + nextPossiblePosition[i][0];     // 計算下一步的行。
            nextPossibleRow = queue[head].mazeRow + nextPossiblePosition[i][1];     // 計算下一步的列。
            if (nextPossibleCol < 1 || nextPossibleCol > mazeCols ||
                nextPossibleRow < 1 || nextPossibleRow > mazeRows)                  // 確認下一步是否有越界（超出迷宮範圍）。
            {
                continue;
            }
            if (mazeWithObstacles[nextPossibleCol][nextPossibleRow] == 0 &&
                book[nextPossibleCol][nextPossibleRow] == 0)                        // 確認下一步是否沒走到障礙物所在位置和是否沒有重複走到。
            {
                book[nextPossibleCol][nextPossibleRow] = 1;                         // 記錄已走過的位置。避免之後重複走到。注意：BFS和DFS不同的是每個位置只會入queue一次，因而book陣列之後不需做還原標記的事。
                queue[tail].mazeCol = nextPossibleCol;                              // 可能位置入queue。
                queue[tail].mazeRow = nextPossibleRow;                              // 可能位置入queue。
                queue[tail].parentNoInQueue = head;                                 // 因從上一個head開始擴展（擴展是指搜索所有可走的位置）可能位置，因而記錄該點的上一個head。
                queue[tail].findingStep = queue[head].findingStep + 1;              // 增加尋找步數，會比上個位置多一步。
                tail++;                                                             // 入queue。
            }
            if (nextPossibleCol == lostedPersonCol && nextPossibleRow == lostedPersonRow)   // 代表是否已到達迷路的人所在的位置。如果到了就停止擴展可能位置。
            {
                isArrivedLostedPersonLoc = 1;
                break;
            }
        }
        if (isArrivedLostedPersonLoc == 1)  // 有時可能在跑完迷宮所有位置前就已找到迷路的人了，因而break掉。
        {
            break;
        }
        head++; // 當一個位置擴展結束後，這個位置要head++，也就是代表出queue，這樣才能繼續對下個位置進行擴展。
    }
}
