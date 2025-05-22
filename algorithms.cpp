// By: Gonçalo Leão

#include <vector>
#include <algorithm> // for sort

unsigned int knapsackBF(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    // Static memory allocation is used since it's faster but this assumes there are at most 20 items (n <= 20).
    bool curCandidate[20]; // current solution candidate being built
    // Prepare the first candidate
    for(unsigned int i = 0; i < n; i++) {
        curCandidate[i] = false;
    }
    // Iterate over all the candidates
    bool foundSol = false;
    unsigned int maxValue; // value of the best solution found so far
    while (true) {
        // Verify if the candidate is a solution
        unsigned int totalValue = 0;
        unsigned int totalWeight = 0;
        for(unsigned int k = 0; k < n; k++) {
            totalValue += values[k]*curCandidate[k];
            totalWeight += weights[k]*curCandidate[k];
        }
        if(totalWeight <= maxWeight) {
            // Check if the solution is better than the previous one (or if it's the first one)
            if(!foundSol || totalValue > maxValue) {
                foundSol = true;
                maxValue = totalValue;
                for(unsigned int k = 0; k < n; k++) {
                    usedItems[k] = curCandidate[k];
                }
            }
        }

        // Get the next candidate
        unsigned int curIndex = 0;
        while(curCandidate[curIndex]) {
            curIndex++;
            if(curIndex == n) break;
        }
        if(curIndex == n) break;
        for(unsigned int i = 0; i < curIndex; i++) {
            curCandidate[i] = false;
        }
        curCandidate[curIndex] = true;
    }
    return maxValue;
}



