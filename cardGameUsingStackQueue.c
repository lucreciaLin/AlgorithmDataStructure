//
//  cardGameUsingStackQueue.c
//
//  Created by LucreciaLin on 2019/4/28.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

/*
兩人玩紙牌遊戲：
1. 兩個玩家，每個玩家各有個6個1~9間任意整數的queue。
2. 桌上有一堆疊可放玩家出的紙牌。
3. 如何玩：玩家出牌，發現與桌上牌面數字不同，則留牌在桌上；反之，若出的牌與桌上某牌面相同，即可將兩張相同的牌&其中間所夾的牌全取走。
4. 當任一玩家手中牌都出完後，遊戲結束，對方獲勝。
*/

#include <stdio.h>

struct queue            // 玩家的紙牌。
{
    int data[1000];     // 先分配1000 * sizeof(int) 個bytes。
    int head;
    int tail;
};

struct stack            // 桌上的紙牌。
{
    int data[10];       // 先分配10 * sizeof(int) 個bytes。用來儲存stack中的元素，因只有1~9種牌面，所以桌上最多只有9張牌。但因索引從0開始，但之後想要從索引1開始算，所以給10。
    int top;
};

void getPlayerInput(struct queue *queue);
void play(struct queue *queue, int *book, struct stack *stack);
int showGameResult(struct queue *queue, struct stack *stack, char *player);

int main()
{
    struct queue aQueue;
    struct queue bQueue;
    struct stack stack;
    int book[10];       // 因國外演算法書在處理需標記的問題，大都用「book」命名。用類似bucket sort取代跑loop的方式，去記錄目前桌上已有哪些牌面。
    
    // 以下初始化，其中之前在queue.c說過：當head和tail的索引重合，代表queue為空。
    aQueue.head = 1;
    aQueue.tail = 1;
    bQueue.head = 1;
    bQueue.tail = 1;
    stack.top = 0;      // 一開始桌上沒任何紙牌。
    
    for (int i = 1; i<= 9; i++)
    {
        book[i] = 0;    // 初始化。
    }
    
    printf("請輸入第一個玩家的紙牌：\n");
    getPlayerInput(&aQueue);    // 得到玩家1號的queue
    printf("請輸入第二個玩家的紙牌：\n");
    getPlayerInput(&bQueue);    //得到玩家2號的queue
    
    while (aQueue.head < aQueue.tail && bQueue.head < bQueue.tail)   // 當任一玩家手上沒紙牌時，代表遊戲結束。
    {
        play(&aQueue, (int *)book, &stack);
        play(&bQueue, (int *)book, &stack);
    }
    
    if (bQueue.head == bQueue.tail)     // 當玩家2號輸了時，輸出玩家1號結果。
    {
        showGameResult(&aQueue, &stack, "Jim");
    }
    else                                // 當玩家1號輸了時，輸出玩家2號結果。
    {
        showGameResult(&bQueue, &stack, "Amy");
    }
}

void getPlayerInput(struct queue *queue)
{
    for (int i = 1; i <= 6; i++)
    {
        scanf("%d", &queue->data[queue->tail]);
        queue->tail++;
    }
}

void play(struct queue *queue, int *book, struct stack *stack)
{
    int showCardVal = queue->data[queue->head];     // 玩家出牌。
    if (book[showCardVal] == 0)                     // 發現桌上沒有相同牌面的牌。
    {
        queue->head++;                              // 因出牌了，就head++。
        stack->top++;                               // 把牌留桌上了，所以top++。
        stack->data[stack->top] = showCardVal;      // 把牌留桌上了，所以也儲存其牌面值。
        book[showCardVal] = 1;                      // 標記一下桌上多了這個牌面數字。
    }
    else                                            // 發現桌上有相同牌面的牌。
    {
        queue->head++;                              // 因出牌了，就head++。
        queue->data[queue->tail] = showCardVal;     // 玩家將自己出的牌放在自己紙牌queue末端。
        queue->tail++;                              // 因末端增加值，所以tail++。上一行先儲存值，這行再加tail索引，是因：1.一開始的紙牌queue加牌時，也是後加tail++。2.如同在queue.c所說，不想當queue中只有一個元素時，head和tail重合的麻煩。
        while (stack->data[stack->top] != showCardVal)  // 將桌上能贏得的牌依序放到玩家自己紙牌末端。
        {
            book[stack->data[stack->top]] = 0;      // 因桌上牌被玩家取走，標記一下桌上少了這個牌面數字。
            queue->data[queue->tail] = stack->data[stack->top];     // 將桌上牌的值放入玩家紙牌末端。
            queue->tail++;                                          // 因玩家多了牌，所以tail++。
            stack->top--;                                           // 因桌上少紙牌，所以top--。
        }
    }
}

int showGameResult(struct queue *queue, struct stack *stack, char *player)
{
    if (queue->tail-queue->head+stack->top != 12)   // 處理一些無法結束遊戲的情形，其中12是因總牌數為12，以此當「判斷遊戲是否正常執行」標準。
    {
        printf("永不結束的遊戲，不分勝負。\n");
        return 1;   // 代表error code。
    }
    
    // 以下印出結果。
    printf("%s win\n", player);
    printf("%s目前手中的牌是", player);
    for (int i = queue->head; i <= queue->tail - 1; i++)
    {
        printf(" %d", queue->data[i]);
        
    }
    if (stack->top > 0)
    {
        printf("\n桌上的牌是");
        for (int i = 1; i <= stack->top; i++)
            printf(" %d", stack->data[i]);
    }
    else
    {
        printf("\n桌上已經沒有牌了");
    }
    
    getchar();  // 因緩衝區仍有data。
    getchar();  // 用來暫停程式，看結果。
    
    return 0;
}
