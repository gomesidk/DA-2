// By: Gonçalo Leão

#include <vector>
#include <algorithm> // for sort
#include <iostream>
#include <ostream>
#include "algorithms.h"
#include "dataset.h"
using namespace std;

unsigned int knapsackBF(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    bool curCandidate[4097];  // current solution candidate being built
    unsigned int maxValue = 0;  // value of the best solution found so far
    unsigned int bestNumItems = n + 1; // Initialize to a value greater than the max number of items (n)
    unsigned int bestSumPallets = UINT_MAX;  // Initialize to a large number
    bool foundSol = false;

    // Prepare the first candidate (no items selected initially)
    for (unsigned int i = 0; i < n; i++) {
        curCandidate[i] = false;
    }

    // Iterate over all the candidates
    while (true) {
        unsigned int totalValue = 0;
        unsigned int totalWeight = 0;
        unsigned int numItems = 0;  // To count the number of items selected in this candidate
        unsigned int sumPallets = 0;  // To calculate the sum of pallet IDs in this candidate

        // Calculate totalValue, totalWeight, and sum of pallet IDs for the current candidate
        for (unsigned int k = 0; k < n; k++) {
            if (curCandidate[k]) {
                totalValue += values[k];
                totalWeight += weights[k];
                numItems++;
                sumPallets += k;  // Add pallet ID (index) to the sum
            }
        }

        // Only consider valid solutions where the total weight doesn't exceed maxWeight
        if (totalWeight <= maxWeight) {
            // Compare based on the three criteria:
            if (!foundSol || totalValue > maxValue ||
                (totalValue == maxValue && numItems < bestNumItems) ||
                (totalValue == maxValue && numItems == bestNumItems && sumPallets < bestSumPallets)) {

                foundSol = true;
                maxValue = totalValue;
                bestNumItems = numItems;
                bestSumPallets = sumPallets;

                // Save the current candidate as the best solution so far
                for (unsigned int k = 0; k < n; k++) {
                    usedItems[k] = curCandidate[k];
                }
            }
        }

        // Get the next candidate by incrementing the binary representation
        unsigned int curIndex = 0;
        while (curCandidate[curIndex]) {
            curIndex++;
            if (curIndex == n) break;
        }
        if (curIndex == n) break;

        // Reset all the previous items and move to the next candidate
        for (unsigned int i = 0; i < curIndex; i++) {
            curCandidate[i] = false;
        }
        curCandidate[curIndex] = true;
    }

    // Output the selected items (pallets)
    for (unsigned int i = 0; i < n; i++) {
        if (usedItems[i]) {
            cout << i + 1 << endl;  // Printing the index of the selected pallet
        }
    }

    return maxValue;
}


unsigned int knapsackDP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxValue[100][1000]; // example size: maxWeight up to 999; increase as needed

    // Initialize DP matrix
    for(unsigned int k = 0; k <= maxWeight; k++) {
        maxValue[0][k] = (k >= weights[0]) ? values[0] : 0;
    }
    for(unsigned int i = 1; i < n; i++) {
        maxValue[i][0] = 0;
    }

    // Fill DP matrix
    for(unsigned int i = 1; i < n; i++) {
        for(unsigned int k = 1; k <= maxWeight; k++) {
            if(k < weights[i]) {
                maxValue[i][k] = maxValue[i - 1][k];
            } else {
                unsigned int valUsing = maxValue[i - 1][k - weights[i]] + values[i];
                maxValue[i][k] = (valUsing > maxValue[i - 1][k]) ? valUsing : maxValue[i - 1][k];
            }
        }
    }

    // Backtrack to find which items to use
    for(unsigned int i = 0; i < n; i++) {
        usedItems[i] = false;
    }
    unsigned int remainingWeight = maxWeight;
    for(int i = n - 1; i > 0; i--) {
        if(remainingWeight == 0) break;
        if(maxValue[i][remainingWeight] != maxValue[i - 1][remainingWeight]) {
            usedItems[i] = true;
            remainingWeight -= weights[i];
        }
    }
    if(remainingWeight >= weights[0]) {
        usedItems[0] = true;
    }

    // Print used items
    for(unsigned int i = 0; i < n; i++) {
        if(usedItems[i]) {
            cout << i + 1 << endl;
        }
    }

    return maxValue[n - 1][maxWeight];
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
            cout << i + 1 << endl;
        }
    }

    return maxValue;
}

unsigned int knapsackILP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    struct Node {
        int level;
        unsigned int value;
        unsigned int weight;
        bool decisions[20];
        double bound;
    };

    auto computeBound = [&](Node& node) {
        unsigned int totalWeight = node.weight;
        double bound = node.value;
        for (unsigned int i = node.level; i < n; i++) {
            if (node.decisions[i]) continue;
            if (totalWeight + weights[i] <= maxWeight) {
                totalWeight += weights[i];
                bound += values[i];
            } else {
                int remain = maxWeight - totalWeight;
                bound += static_cast<double>(values[i]) / weights[i] * remain;
                break;
            }
        }
        return bound;
    };

    Node bestNode;
    bestNode.value = 0;
    bestNode.weight = 0;
    bestNode.level = 0;
    bestNode.bound = 0;
    for (unsigned int i = 0; i < n; i++) bestNode.decisions[i] = false;

    std::vector<Node> stack;
    Node root;
    root.value = 0;
    root.weight = 0;
    root.level = 0;
    for (unsigned int i = 0; i < n; i++) root.decisions[i] = false;
    root.bound = computeBound(root);
    stack.push_back(root);

    while (!stack.empty()) {
        Node node = stack.back();
        stack.pop_back();

        if (node.level == n) {
            if (node.value > bestNode.value) {
                bestNode = node;
            }
            continue;
        }

        // Branch 1: Include item
        if (node.weight + weights[node.level] <= maxWeight) {
            Node withItem = node;
            withItem.level = node.level + 1;
            withItem.weight += weights[node.level];
            withItem.value += values[node.level];
            withItem.decisions[node.level] = true;
            withItem.bound = computeBound(withItem);
            if (withItem.bound >= bestNode.value) {
                stack.push_back(withItem);
            }
        }

        // Branch 2: Exclude item
        Node withoutItem = node;
        withoutItem.level = node.level + 1;
        withoutItem.decisions[node.level] = false;
        withoutItem.bound = computeBound(withoutItem);
        if (withoutItem.bound >= bestNode.value) {
            stack.push_back(withoutItem);
        }
    }

    for (unsigned int i = 0; i < n; i++) {
        usedItems[i] = bestNode.decisions[i];
        if (usedItems[i]) {
            cout << i + 1 << endl;
        }
    }

    return bestNode.value;
}