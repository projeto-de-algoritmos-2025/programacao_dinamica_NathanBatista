#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool canPartition(int* nums, int numsSize) {
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }

    if (sum % 2 != 0) return false;

    int target = sum / 2;
    
    bool* dp = (bool*)calloc(target + 1, sizeof(bool));
    
    dp[0] = true;

    for (int i = 0; i < numsSize; i++) {
        for (int w = target; w >= nums[i]; w--) {
            dp[w] = dp[w] || dp[w - nums[i]];
        }
    }

    bool result = dp[target];
    free(dp);
    return result;
}