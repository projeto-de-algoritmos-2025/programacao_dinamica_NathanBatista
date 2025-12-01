#include <stdio.h>
#include <stdlib.h>

int lengthOfLIS(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int* dp = (int*)malloc(numsSize * sizeof(int));
    int maxL = 1; 

    for (int i = 0; i < numsSize; i++) {
        dp[i] = 1;
    }

    for (int j = 1; j < numsSize; j++) {
        for (int i = 0; i < j; i++) {
            if (nums[j] > nums[i]) {
                if (dp[i] + 1 > dp[j]) {
                    dp[j] = dp[i] + 1;
                }
            }
        }
        if (dp[j] > maxL) {
            maxL = dp[j];
        }
    }

    free(dp);
    return maxL;
}