//
//  equationOfMatch.c
//
//  Created by LucreciaLin on 2019/6/2.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

/*
 
火柴棒等式：
- 有n根火柴棒，想拼出如A + B = C 的等式。
- A、Ｂ、C為0~9之間的數字。
- 數字0~9的拼法各需的火柴棒根數：
 0 -> 6根； 1 -> 2根； 2 -> 5根； 3 -> 5根； 4 -> 4根； 5 -> 5根；
 6 -> 6根； 7 -> 3根； 8 -> 7根； 9 -> 6根
- 如果A != B，則A + B = C 和 B + A = C 視為不同的等式（A、B、C 皆 > 0）
- 全部的火柴棒需都用上。
- 當火柴棒總數為24根時，規定程式執行時限為1秒。
 
e.g. 如果共有18根火柴棒，則共可拼出9個不同的等式：
0 + 4 = 4； 0 + 11 = 11； 1 + 10 = 11； 2 + 2 = 4； 2 + 7 = 9；
4 + 0 = 4； 7 + 2 = 9； 10 + 1 = 11； 11 + 0 = 11

*/

#include <stdio.h>

int getMatchesSumOfNum(int num);

int main()
{
    /*
     要找出A + B = C的等式，最簡單方式就是「列舉法」。但列舉範圍是什麼？
     => 如果題目是「共24根火柴棒」，則24-4（即加號的2根加上等號的2根）= 20根。
     => 而數字0~9中，1用到的火柴棒數量最少（只需2根）。
     => 因而20根最多能組成10個1。
     => 也就是A、B、Ｃ中的任一個範圍在0~11111之間。
     => 但因此題有時間限制。儘管用列舉法，也要考慮效能，解法有2個：
        1. 因為 A + B = C，所以只需列舉A和B，C用算的就可求得。
        2. 可事先找出A和B較接近的範圍上限在哪裡：為何當24根火柴棒時，A或B的可能上限值為711。而當18根火柴棒時，A或B的可能上限值為11。
           可看possibleHighestEnumNum.c的求值過程。因是實驗究竟上限值為何，執行時間會超過1秒。
          （因目前題目在24根時有時間限制，因而以此為基準，這邊上限值直接先固定為711）。
     */
    int possibleHighestNum = 711;
    int SumOfAnumBnum;
    int totalMatches;
    int equationCombinationCounts = 0;
    
    printf("請輸入火柴棒總數為：\n");
    scanf("%d", &totalMatches);
    int totalMatchesWithoutPlusEqualSign = totalMatches - 4;             // 減4代表「減掉加號的2根和等號的2根」。
    
    // 開始列舉A和B。
    for (int aNum = 0; aNum <= possibleHighestNum; aNum++)
    {
        for (int bNum = 0; bNum <= possibleHighestNum; bNum++)
        {
            SumOfAnumBnum = aNum + bNum;                                 // A + B = C。
            if (getMatchesSumOfNum(aNum) + getMatchesSumOfNum(bNum) + getMatchesSumOfNum(SumOfAnumBnum) == totalMatchesWithoutPlusEqualSign)                        // 當A + B + C 的火柴棒總數等於totalMatchesWithoutPlusEqualSign時
            {
                printf("%d + %d = %d\n", aNum, bNum, SumOfAnumBnum);
                equationCombinationCounts++;
            }
        }
    }
    printf("總共可以拼出%d個不同的火柴棒等式", equationCombinationCounts);
    getchar();      // 因緩衝區仍有data。
    getchar();      // 用來暫停程式，看結果。
    
    return 0;
}

int getMatchesSumOfNum(int num)
{
    int matchesSum = 0;
    int matchesSumListOfEachNum[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};   // 用雜湊表儲存0~9中，分別「要將數字拼出來所需要的火柴數」。
    
    while (num / 10 != 0)     // 如果數字一開始大於個位數。
    {
        matchesSum += matchesSumListOfEachNum[num % 10];    // 得到個位數的數字，並將它對應到雜湊表取得相對應的火柴棒個數。
        num = num / 10;                                     // 繼續找出其他位數的數字。找出下一個個位數的數字。
    }
    matchesSum += matchesSumListOfEachNum[num];             // 如果該數字一開始就是個位數時，可直接對應到雜湊表取得相對應的火柴棒個數。
    return matchesSum;
}
