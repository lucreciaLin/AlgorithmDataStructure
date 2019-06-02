//
//  possibleHighestEnumNum.c
//
//  Created by LucreciaLin on 2019/6/2.
//  Copyright © 2019 LucreciaLin. All rights reserved.
//

/*
 
此程式與equationOfMatch.c搭配，算出列舉範圍中的可能上限值。

*/

#include <stdio.h>

int getMatchesSumOfNum(int num);

int main()
{
    int possibleHighestEnumNum = 0;
    int SumOfAnumBnum;
    
    int totalMatches;
    printf("請輸入火柴棒總數為：\n");
    scanf("%d", &totalMatches);
    int totalMatchesWithoutPlusEqualSign = totalMatches - 4;    // 減4代表「減掉加號的2根和等號的2根」。
    
    // 開始列舉A和B。
    for (int aNum = 0; aNum <= 12000; aNum++)       // 因為A範圍為0~11111，這邊直接取到12000。
    {
        for (int bNum = 0; bNum <= 12000; bNum++)   // 因為B範圍為0~11111，這邊直接取到12000。
        {
            SumOfAnumBnum = aNum + bNum;            // A + B = C。
            if (getMatchesSumOfNum(aNum) + getMatchesSumOfNum(bNum) + getMatchesSumOfNum(SumOfAnumBnum) == totalMatchesWithoutPlusEqualSign)   // 當A + B + C 的火柴棒總數等於totalMatchesWithoutPlusEqualSign時
            {
                if (bNum > possibleHighestEnumNum)  // 更新可能上限值。用aNum或bNum皆為相同結果。
                {
                    possibleHighestEnumNum = bNum;
                }
            }
        }
    }
    printf("單個數字可能的最大估計值： %d", possibleHighestEnumNum);
    getchar();  // 因緩衝區仍有data。
    getchar();  // 用來暫停程式，看結果。
    
    return 0;
}

int getMatchesSumOfNum(int num)
{
    int matchesSum = 0;
    int matchesSumListOfEachNum[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};   // 用雜湊表儲存0~9中，分別「要將數字拼出來所需要的火柴數」。
    
    while (num / 10 != 0)       // 如果數字一開始大於個位數。
    {
        matchesSum += matchesSumListOfEachNum[num % 10];    // 得到個位數的數字，並將它對應到雜湊表取得相對應的火柴棒個數。
        num = num / 10;                                     // 繼續找出其他位數的數字。找出下一個個位數的數字。
    }
    matchesSum += matchesSumListOfEachNum[num];             // 如果該數字一開始就是個位數時，可直接對應到雜湊表取得相對應的火柴棒個數。
    return matchesSum;
}
