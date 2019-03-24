//
//  bubbleSort1.c
//
//  Created by LucreciaLin on 2019/3/24.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

#include <stdio.h>

int main() {
    int ary[100];   // 先分配100 * sizeof(int) 個bytes
    int i;
    int temp;
    int totalNums;
    
    scanf("%d", &totalNums);
    for (i = 1; i <= totalNums; i++)
    {
        scanf("%d", &ary[i]);
    }
    
    for (i = 1; i <= totalNums-1; i++)  // 如果totalNums是5，則需4趟才能台排好一個數字
                                        // e.g. 5 4 3 2 1 => 總共需要4趟才能台排序完成。
    {
        for (int j = 1; j <= totalNums-i; j++)  // 單趟中，每個數字需比較的相鄰兩個數，從第1個算到未排序好的那個是數。
                                                // e.g. 5 4 3 2 1 => 如要排序5時，單趟需要比較1&2位、2&3位、3&4位、4＆5位（所以是4次），才能排好5。接著排序4時，單趟需要比較1&2位、2&3位、3&4位（所以是3次），才能排好4。以此類推
        {
            if (ary[j] > ary[j+1])  // 希望「由小到大」排序，當前一個數大於後一個數時，則兩數交換
            {
                temp = ary[j];
                ary[j] = ary[j+1];
                ary[j+1] = temp;
            }
        }
    }
    
    printf("排序結果：");
    for (i = 1; i <= totalNums; i++)
        printf("%d ", ary[i]);
    
    getchar();  // 因緩衝區已有data
    getchar();  // 用來暫停程式，看排序結果
    return 0;
}
