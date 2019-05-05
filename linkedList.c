//
//  linkedList.c
//
//  Created by LucreciaLin on 2019/5/5.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>     // 用到malloc()，因而載入。

struct node             // 定義一結構體代表linked list裡node節點。
{
    int data;           // 用以儲存值、資料。
    struct node *next;  // 用以指向下個node節點。這個指標又稱為「後繼指標」。
};

int main()
{
    struct node *head;      // 代表用於頭指標，方便以後能從頭開始iterate整個linked list。
    struct node *current;   // 代表用於新增時的「現在、當前的這個指標」。
    struct node *prev;      // 代表用於「該指標的上一個指標」。
    struct node *temp;      // 代表用於「臨時、暫時性指標」。
    int i;
    int totalNum;
    int input;
    
    printf("請輸入linked list裡值的總個數為：");
    scanf("%d", &totalNum);
    head = NULL;            // 頭指標初始化為NULL。
    prev = NULL;            // 初始化，
    printf("請輸入linked list全部的值：");
    for (i = 1; i <= totalNum; i++)
    {
        scanf("%d", &input);
        current = (struct node *)malloc(sizeof(struct node));   // 動態新增一個struct node型別的記憶體空間，用以存放node節點。並用current指標指向該node節點。
        current->data = input;  // 把資料存入node節點。
        current->next = NULL;   // 設定current指標的後繼指標，也就是next指標，指向NULL。
        if (head == NULL)       // 代表linked list裡尚無任何node節點。
        {
            head = current;     // 如果為linked list裡第一個node節點。那麼就將head指標指向這個node節點。
        }
        else
        {
            prev->next = current;   // 如果非第一個node節點。那麼就將上一個指標的後繼指標，也就是prev指標的next指標，指向當前這個current指標。
        }
        prev = current;         // 用於為了下一次loop中，prev指標為該次current指標的上一個指標的實作。
    }
    
    printf("請輸入想插入linked list裡的值為：");
    scanf("%d", &input);
    temp = head;            // 為了從一開始iterate整個linked list。
    while (temp != NULL)    // 如果還沒到linked list的末尾，就持續loop。
    {
        if (temp->next->data > input)       // 如果目前這個臨時temp指標指向的下個node節點的data大於插入值 => 代表找到該插入值適合的插入點了。
        {
            current = (struct  node *)malloc(sizeof(struct node));  // 動態新增一個struct node型別的記憶體空間，用以存放node節點。並用current指標指向該node節點。
            current->data = input;          // 把插入值存入node節點。
            current->next = temp->next;     // 將新增好的current指標的後繼指標，也就是next指標，指向「目前temp指標的next指標」所指向的node節點。
            temp->next = current;           // 將「目前temp指標的next指標」指向這個「新增好的current指標」。
            break;                          // 做完新增，就break掉loop。
        }
        temp = temp->next;                  // 繼續往下一個node節點，尋找適合的插入點。
    }
    
    temp = head;                            // 為了從一開始iterate整個linked list。
    printf("插入值後linked list的結果：");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        prev = temp;                        // 將上一個指標指向當前指標。
        temp = temp->next;                  // 並用當前指標指向下一個node節點。繼續往下一個node節點。
        free(prev);                         // 釋放因malloc()未歸還的記憶體空間。
    }
    
    getchar();      // 因緩衝區仍有data。
    getchar();      // 用來暫停程式，看結果。
    
    return 0;
}
