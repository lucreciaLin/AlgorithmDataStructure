//
//  stack.c
//
//  Created by LucreciaLin on 2019/4/21.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

#include <stdio.h>
#include <string.h>

typedef unsigned int UINT32;    //  這裡標示，可作為：1.縮寫用、2.方便移植程式用，因unsigned int包含16或32位元，這裡明訂用32位元。

int main() {
    char oriAry[101];   // 先分配100 * sizeof(char) 個bytes。
    char stack[101];    // 先分配100 * sizeof(char) 個bytes。
    int i;
    int top = 0;        // 因stack只在一端出或入資料，這裡命名那一端為「top」。
    int startComparingIdx;  // 是另一半迴文資料用以「比對是否為迴文的起始位置」。
    
    fgets(oriAry, sizeof(oriAry), stdin);   // 用以取得使用者輸入的一串文字，會包含最後按下的Enter字元。注意：gets()已deprecated，改用fgets()較安全。
    
    int len = (UINT32) strlen(oriAry) - 1;  // 因為strlen出來是「unsigned long」，所以要轉型。而這裡「選用unsigned int為因結果一定大於0」。另外，「-1是為了扣除之前的Enter字元」。
    int beforeMidIdx = (len / 2) - 1;       // 因爲「迴文如果取中點後，其左右會是對稱關係」。注意：C語言中，「整數相除，結果會無條件捨去」，e.g. 當迴文為「xyzyx」時，5/2 = 2，得到中點索引值為2，而再-1是為了之後取不要放入中點位置的資料。e.g. 當迴文為「anna」，4/2 = 2，得到中點索引值為2，而再-1是為了之後取不要放入中點位置的資料。
    if (len % 2 == 0)
    {
        startComparingIdx = beforeMidIdx + 1;     // 當字串為偶數長度時，這裡+1是為了越過中點，取得要比對的另一半迴文資料，e.g. 「anna」中的「na」。
    }
    else
    {
        startComparingIdx = beforeMidIdx + 2;     // 當字串為奇數長度時，這裡+2是為了越過中點，取得要比對的另一半迴文資料，e.g. 「xyzyx」中的「yx」。
    }
    
    for (i = 0; i <= beforeMidIdx; i++)
    {
        stack[++top] = oriAry[i];           // 將中點之前的資料放入stack。
    }
    
    int endComparingIdx = len - 1;
    for (i = startComparingIdx; i <= endComparingIdx; i++)
    {
        if (oriAry[i] != stack[top])        // 將「另一半迴文資料」與「stack裡的資料」一一比對，一旦不符，就break掉。
        {
            break;
        }
        top--;  // 發現該筆資料符合時，就top--，用以在「下一次迴圈中，比對下一筆資料是否也符合」。
    }
    
    if (top == 0)   // 因top = 0代表所有資料都成功符合了。
    {
        printf("YES, it's a palindrome!");
    }
    else
    {
        printf("NO, it's not a palindrome!");
    }
    
    getchar();  // 因緩衝區仍有data。
    getchar();  // 用來暫停程式，看結果。
    
    return 0;
}
