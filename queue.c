//
//  queue.c
//
//  Created by LucreciaLin on 2019/4/14.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

#include <stdio.h>

struct queue    //  將queue的三大基本元素包成一個struct。
{
    int data[100];  // 用來儲存資料的陣列。
    int head;       // 記錄queue的頭部，用來將資料出queue用。
    int tail;       // 記錄queue的尾部，用來將資料入queue用。
};

int main()
{
    struct queue queue;
    queue.head = 1;     // 從1開始為個人習慣或偏好，也可從0開始。
    queue.tail = 1;
    
    for (int i = 1; i <= 9; i++)
    {
        scanf("%d", &queue.data[queue.tail]);   // 將要排序的原始資料讀入。
        queue.tail++;   // tail在最後再++，是為了防止「當queue中只剩一個資料時，head和tail會重合」的麻煩情形。因而「當為空queue時，head和tail才會重合」。
    }
    
    printf("排序結果：");
    while (queue.head < queue.tail)
    {
        printf("%d ", queue.data[queue.head]);  // 先印出要出queue的資料，也就是印出「此次FIFO結果」。當迴圈結束時，就會印出所有的FIFO結果。
        queue.head++;                           // 將head++，因想用來成為入queue的資料。
        queue.data[queue.tail] = queue.data[queue.head];    // 將head++後所對應的資料放到tail處，也就是入queue。
        queue.tail++;                           // 將tail++，因queue已有資料入queue了。
        queue.head++;                           // 將head++，為了在下個迴圈開始時印出queue的資料。
    }
    
    getchar();  // 因緩衝區仍有data。
    getchar();  // 用來暫停程式，看排序結果。
    
    return 0;
}
