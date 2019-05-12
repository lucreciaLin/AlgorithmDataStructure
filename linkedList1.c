//
//  linkedList1.c
//
//  Created by LucreciaLin on 2019/5/12.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

#include <stdio.h>

int main()
{
    int data[100];      // 用以儲存每個node的data。先分配100 * sizeof(int) 個bytes。
    int next[100];      // 用以儲存每個node的「下個node」是誰。簡單說，就是「記錄每個node位置的陣列」。先分配100 * sizeof(int) 個bytes。
    int i;
    int totalNum;
    int temp;           // 用以代表「臨時、暫時性指標」。
    int len;            // 用以代表「新增的這個當下的node吧的data索引」。
    int head = 1;       // 用以代表頭指標，方便以後能從頭開始iterate整個linked list。
    int null = 0;       // 用以代表「最後一個node」，其指標是指向null。在這裡用「0」表示「沒有下個node」意思。
    
    printf("請輸入linked list裡值的總個數為：");
    scanf("%d", &totalNum);
    
    printf("請輸入linked list全部的值：");
    for (i = 1; i <= totalNum; i++)
    {
        scanf("%d", &data[i]);
    }
    len = totalNum;     // 初始化len。
    
    // 以下初始化next array。
    for (i = 1; i <= totalNum; i++)
    {
        if (i != totalNum)      // 如果不是最後一個node，就記錄下個node在的位置為何。
        {
            next[i] = i + 1;
        }
        else                    // 如果是最後一個node，就標示為0。
        {
            next[i] = null;
        }
    }
    
    len++;                      // 因要新增node，所以len++。
    printf("請輸入想插入linked list裡的值為：");
    scanf("%d", &data[len]);
    
    
    temp = head;            // 為了從一開始iterate整個linked list。
    while (temp != null)    // 如果還沒到linked list的末尾，就持續loop。
    {
        if (data[next[temp]] > data[len]) // 如果目前這個臨時temp指標指向的下個node的data大於插入值 => 代表找到該插入值適合的插入點了。
        {
            next[len] = next[temp];       // next[temp]就是那個大於插入值的位置值，將這個位置值assign給「插入值在的位置」，表示「插入值的下個node」的位置為何。
            next[temp] = len;             // len就是「插入值的位置值」，將這個位置值assign給「插入值前個node在的位置」，表示「插入值這個node」的位置為何。
            break;          // 做完新增，就break掉loop。
        }
        temp = next[temp];  // 繼續往下一個node，尋找適合的插入點。
    }
    
    printf("插入值後linked list的結果：");
    temp = head;            // 為了從一開始iterate整個linked list。
    while (temp != null)
    {
        printf("%d ", data[temp]);
        temp = next[temp];  // 繼續往下一個node。
    }
    
    getchar();  // 因緩衝區仍有data。
    getchar();  // 用來暫停程式，看結果。
    
    return 0;
}
