#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
    int profit;
} Job;

int compareJobs(const void* a, const void* b) {
    return ((Job*)a)->end - ((Job*)b)->end;
}

int findPreviousCompatibleJob(Job* jobs, int currentIndex) {
    int low = 0;
    int high = currentIndex - 1;
    int p_j = -1; 

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (jobs[mid].end <= jobs[currentIndex].start) {
            p_j = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return p_j;
}

int jobScheduling(int* startTime, int startTimeSize, int* endTime, int endTimeSize, int* profit, int profitSize) {
    int n = startTimeSize;
    
    Job* jobs = (Job*)malloc(n * sizeof(Job));
    for (int i = 0; i < n; i++) {
        jobs[i].start = startTime[i];
        jobs[i].end = endTime[i];
        jobs[i].profit = profit[i];
    }

    qsort(jobs, n, sizeof(Job), compareJobs);

    int* dp = (int*)malloc(n * sizeof(int));

    dp[0] = jobs[0].profit;

    for (int i = 1; i < n; i++) {
        int currentProfit = jobs[i].profit;
        
        int prevCompatibleIndex = findPreviousCompatibleJob(jobs, i);
        
        if (prevCompatibleIndex != -1) {
            currentProfit += dp[prevCompatibleIndex];
        }

        if (currentProfit > dp[i - 1]) {
            dp[i] = currentProfit;
        } else {
            dp[i] = dp[i - 1];
        }
    }

    int result = dp[n - 1];

    // Limpeza
    free(jobs);
    free(dp);

    return result;
}