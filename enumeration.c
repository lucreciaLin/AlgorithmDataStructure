//
//  enumeration.c
//
//  Created by LucreciaLin on 2019/5/19.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

/*
 兩個三位數相加後相等於一個三位數。
 => 以上9個數字皆不重複
 e.g. 173 + 286 = 459
 請找出共有幾種可能？
 */

#include <stdio.h>

int main()
{
    int ary[10];            // 只有1~9的可能。因索引從0開始，但之後想要從索引1開始算，所以給10。
    int i;
    int combinations = 0;       // 用來記錄最後共有幾種可能。
    int book[10];           // 因國外演算法書在處理需標記的問題，大都用「book」命名。用類似bucket sort做「數字彼此互不相等計算」。
    int sum;
    
    for (ary[1] = 1; ary[1] <= 9; ary[1]++)
        for (ary[2] = 1; ary[2] <= 9; ary[2]++)
            for (ary[3] = 1; ary[3] <= 9; ary[3]++)
                for (ary[4] = 1; ary[4] <= 9; ary[4]++)
                    for (ary[5] = 1; ary[5] <= 9; ary[5]++)
                        for (ary[6] = 1; ary[6] <= 9; ary[6]++)
                            for (ary[7] = 1; ary[7] <= 9; ary[7]++)
                                for (ary[8] = 1; ary[8] <= 9; ary[8]++)
                                    for (ary[9] = 1; ary[9] <= 9; ary[9]++)
                                    {
                                        for (i = 1; i <= 9; i++)
                                        {
                                            book[i] = 0;            // 初始化book陣列。
                                        }
                                        for (i = 1; i <= 9; i++)
                                        {
                                            book[ary[i]] = 1;       // 如果ary中某數出現過，就標記為1。
                                        }
                                        
                                        sum = 0;                    // 初始化總和。
                                        for (i = 1; i <= 9; i++)
                                        {
                                            sum += book[i];         // 加總所有數字出現的次數。
                                        }
                                        
                                        if (sum == 9 && ary[1] * 100 + ary[2] * 10 + ary[3] + ary[4] * 100 + ary[5] * 10
                                            + ary[6] == ary[7] * 100 + ary[8] * 10 + ary[9])
                                        {   // 「sum == 9」代表所有數字皆個自出現過一次
                                            combinations++;
                                            printf("%d%d%d+%d%d%d=%d%d%d\n", ary[1], ary[2], ary[3], ary[4], ary[5],
                                                   ary[6], ary[7], ary[8], ary[9]);
                                        }
                                    }
    printf("combinations=%d", combinations / 2);    //「除以2」是為了減掉重複的排列組合，e.g. 173 + 286 = 459 和 286 + 173 = 459 為同一種組合。
    getchar();                              // 因緩衝區仍有data。
    getchar();                              // 用來暫停程式，看結果。
    
    return 0;
}
