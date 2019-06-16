//
//  dfs.c
//
//  Created by LucreciaLin on 2019/6/16.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

/*
 兩個三位數相加後相等於一個三位數。
 => 以上9個數字皆不重複
 e.g. 173 + 286 = 459
 請找出共有幾種可能？
 */

#include <stdio.h>

void doDFS(int which);  // 進行「深度優先搜尋（DFS: Depth First Search）」演算法。

int ary[10];            // 只有1~9的可能。因索引從0開始，但之後想要從索引1開始算，所以給10。
int book[10];           // 因國外演算法書在處理需標記的問題，大都用「book」命名。用類似bucket sort做「數字彼此互不相等計算」。C語言的全域變數在沒給值時，預設值為0。因而book變數不用全部再次指定初始值為0。
int combinations = 0;   // 用來記錄最後共有幾種可能。
int main()
{
    doDFS(1);           // 總共有1~9（共9種可能），從第1種可能開始嘗試。
    
    printf("\ncombinations=%d", combinations / 2);   //「除以2」是為了減掉重複的排列組合，e.g. 173 + 286 = 459 和 286 + 173 = 459 為同一種組合。
    getchar();          // 因緩衝區仍有data。
    getchar();          // 用來暫停程式，看結果。
    
    return 0;
}

void doDFS(int which)
{
    if (which == 10)    // 當已來到第10種可能時，代表前9種可能，已給好1~9可能的值。
    {
        if (ary[1] * 100 + ary[2] * 10 + ary[3] +
            ary[4] * 100 + ary[5] * 10 + ary[6] ==
            ary[7] * 100 + ary[8] * 10 + ary[9])    // 判斷是否滿足e.g. 173 + 286 = 459 等式。
        {
            combinations++;
            printf("%d%d%d + %d%d%d = %d%d%d\n",
                   ary[1], ary[2], ary[3], ary[4], ary[5],
                   ary[6], ary[7], ary[8], ary[9]);     // 印出這回合的第which種可能的結果。
        }
        
        return;         // 代表返回之前的一步，也就是指「最近呼叫的地方」。
    }
    
    for (int i = 1; i <= 9; i++)    // 分別為第1~9每種可能，依照「1、2、3、...、9順序」一一嘗試。
    {
        if (book[i] == 0)           // 代表1~9中的某值未給出去。
        {
            ary[which] = i;         // 將某值給到第which種可能裡。
            book[i] = 1;            // 代表1~9中的某值已給出去。
            
            doDFS(which + 1);       // 因第which種可能已給好值，因而到第which + 1種可能中，繼續嘗試給值。使用遞迴（自己呼叫自己）實作這過程。
            
            book[i] = 0;            // 因為「這回合的第which種可能」已嘗試完，要還原以便給「下一回合的第which種可能」去嘗試。
        }
    }
    
    return;
}
