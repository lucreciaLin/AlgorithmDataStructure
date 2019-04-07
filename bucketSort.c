//
//  bucketSort.c
//
//  Created by LucreciaLin on 2019/4/7.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

#include <stdio.h>

int main()
{
    int ary[1000];  // 先分配1000 * sizeof(int) 個bytes。
    int i;
    int temp;
    int totalNum;
    
    for (i = 1; i <= 1000; i++)
    {
        ary[i] = 0; // 初始化陣列中每個索引值。
    }
    
    scanf("%d", &totalNum);
    
    for (i = 1; i <= totalNum; i++)
    {
        scanf("%d", &temp);
        ary[temp]++;    //  計算次數，對編號為temp的桶子做++。
    }
    
    for (i = 1; i <= 1000; i++)
    {
        for (int j = 1; j <= ary[i]; j++)   // 把該編號的桶子裡總共有或出現幾次，去一一印出。
        {
            printf("%d ", i);
        }
    }
    
    getchar();  // 因緩衝區仍有data
    getchar();  // 用來暫停程式，看排序結果
    
    return 0;
}
