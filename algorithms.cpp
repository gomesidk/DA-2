// By: Gonçalo Leão

#include <vector>
#include <algorithm> // for sort
#include <iostream>
#include <ostream>
#include <ranges>

#include "dataset.h"
using namespace std;

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
    for (unsigned int i = 0; i < n; i++) {
        if(usedItems[i]) {
            cout << i << endl;
        }
    }
    return maxValue;
}

unsigned int knapsackDP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxValue[100][101]; // assumes maxWeight <= 100 and n <= 100

    // Step 1: Initialize the DP matrix with the values for the base cases
    for(unsigned int k = 0; k <= maxWeight; k++) {
        maxValue[0][k] = (k >= weights[0]) ? values[0] : 0; // base case considers using the first item
    }
    for(unsigned int i = 1; i <= n; i++) {
        maxValue[i][0] = 0; // value of 0 for knapsacks of capacity = 0
    }

    // Step 2: Compute values of the DP matrix for the recursive cases
    for(unsigned int i = 1; i < n; i++) {
        for(unsigned int k = 1; k <= maxWeight; k++) {
            if(k < weights[i]) {
                maxValue[i][k] = maxValue[i - 1][k]; // item is too big for the knapsack, so the optimal solution is the same as not considering it
            }
            else {
                unsigned int valueUsingItemI = maxValue[i - 1][k - weights[i]] + values[i];
                if(valueUsingItemI > maxValue[i - 1][k]) {
                    maxValue[i][k] = valueUsingItemI; // using item i improves the solution
                }
                else {
                    maxValue[i][k] = maxValue[i - 1][k]; // using item i does not improve the solution
                }
            }
        }
    }

    // Step 3: Build the solution
    for(unsigned int i = 0; i < n; i++) {
        usedItems[i] = false;
    }
    unsigned int remainingWeight = maxWeight;
    unsigned int curItem = n - 1;
    for(unsigned int i = n - 1; i > 0; i--) {
        // Stop earlier of the all the items have already been added to the solution
        if(remainingWeight == 0) break;

        // An item is used if not including reduces the total value for a knapsack of the same size
        if(maxValue[i][remainingWeight] != maxValue[i-1][remainingWeight]) {
            usedItems[i] = true;
            remainingWeight -= weights[i];
            curItem--;
        }
    }
    // If remainingWeight > 0, then the first item is used
    if(remainingWeight > 0) {
        usedItems[0] = true;
    }

    for(unsigned int i = 1; i < n; i++) {
        if (usedItems[i]) {
            cout << i << endl;
        }
    }

    return maxValue[n-1][maxWeight];
}

// Comparator uses floating-point division
bool compare(const Pallet& a, const Pallet& b) {
    double r1 = static_cast<double>(a.profit) / a.weight;
    double r2 = static_cast<double>(b.profit) / b.weight;
    return r1 > r2;
}

unsigned int knapsackGreedy(vector<Pallet> pallets, unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    sort(pallets.begin(), pallets.end(), compare);
    unsigned int maxValue = 0;
    unsigned int idx = 0;

    while (maxWeight > 0 && idx < n) {
        if (pallets[idx].weight <= maxWeight) {  // check if pallet fits
            maxValue += pallets[idx].profit;
            maxWeight -= pallets[idx].weight;
            usedItems[pallets[idx].pallet] = true;
        }
        idx++;
    }

    cout << "Selected pallets IDs:" << endl;
    for (unsigned int i = 0; i < n; i++) {  // print starting at 0
        if (usedItems[i]) {
            cout << i << endl;
        }
    }

    return maxValue;
}

