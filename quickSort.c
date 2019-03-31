//
//  quickSort.c
//
//  Created by LucreciaLin on 2019/3/31.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

#include <stdio.h>

void doQuickSort(int front, int end);

int ary[100];   // 先分配100 * sizeof(int) 個bytes
int totalNums;

int main()
{
    int i;
    
    scanf("%d", &totalNums);
    for (i = 1; i <= totalNums; i++)
    {
        scanf("%d", &ary[i]);
    }
    doQuickSort(1, totalNums);  // 1代表第1個索引
    
    printf("排序結果：\n");
    for (i = 1; i <= totalNums; i++)
    {
        printf("%d ", ary[i]);
    }
    
    getchar();  // 因緩衝區仍有data
    getchar();  // 用來暫停程式，看排序結果
    return 0;
}

void doQuickSort(int front, int end)
{
    if (front > end)    // 防呆。
    {
        return;
    }
    
    int i = front;  // 設定從陣列左邊找至右邊的索引叫i。
    int j = end;    // 設定從陣列右邊找至左邊的索引叫j。
    int pivot = ary[front]; // 設定基準值是「陣列第1個位置的值」。
    
    while (i != j)  // 也就是當i和j彼此未相等、相遇在同一索引位置時 => 代表仍不改變pivot下，繼續做「交換數字」的排序動作。
    {
        while (ary[j] >= pivot && i < j)    // 先做（注意：如果先從左邊找，會造成i和j錯過相遇點，而排序失敗）從右邊開始找直到找到「值小於pivot」的情形，找到後，就將j--。
        {
            j--;
        }
        
        while (ary[i] <= pivot && i < j)    // 再做從左邊開始找直到找到「值大於pivot」的情形，找到後，就將i--。
        {
            i++;
        }
        
        // 以下3行做兩值交換
        int temp = ary[i];
        ary[i] = ary[j];
        ary[j] = temp;
    }
    
    // 這裡代表i和j相遇了，需要將「相遇位置的值」與「基準值」交換，結束舊的基準值情形下的交換數字回合。
    ary[front] = ary[i];    // 這裡的ary[i]成為新的基準值。
    ary[i] = pivot;
    
    doQuickSort(front, i - 1);  // 用遞迴做左半邊的divide and conquer
    doQuickSort(i + 1, end);    // 用遞迴做右半邊的divide and conquer
}
