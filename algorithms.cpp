// By: Gonçalo Leão

#include <vector>
#include <algorithm>
#include <iostream>
#include <ostream>
#include "algorithms.h"
#include "dataset.h"

using namespace std;

/**
 * @brief Brute-force solution for the 0/1 Knapsack problem.
 * 
 * This function tries all combinations of items to find the one with the maximum value
 * without exceeding the maximum weight. In the case of equal values, it prefers the one
 * with fewer items; if still equal, it prefers the one with a lower sum of indices.
 * 
 * @param values Array containing the values of the items.
 * @param weights Array containing the weights of the items.
 * @param n Total number of items.
 * @param maxWeight The maximum total weight the knapsack can carry.
 * @param usedItems Output array indicating which items are selected in the optimal solution.
 * @return The maximum total value for the given constraints.
 */
unsigned int knapsackBF(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    bool curCandidate[4097];  // all initialized to false
    unsigned int maxValue = 0;
    unsigned int bestNumItems = n + 1;
    unsigned int bestSumPallets = UINT_MAX;
    bool foundSol = false;

    for (unsigned int i = 0; i < n; i++) {
        curCandidate[i] = false;
    }

    while (true) {
        unsigned int totalValue = 0;
        unsigned int totalWeight = 0;
        unsigned int numItems = 0;
        unsigned int sumPallets = 0;

        for (unsigned int k = 0; k < n; k++) {
            if (curCandidate[k]) {
                totalValue += values[k];
                totalWeight += weights[k];
                numItems++;
                sumPallets += k;
            }
        }

        if (totalWeight <= maxWeight) {
            if (!foundSol || totalValue > maxValue ||
                (totalValue == maxValue && numItems < bestNumItems) ||
                (totalValue == maxValue && numItems == bestNumItems && sumPallets < bestSumPallets)) {
                foundSol = true;
                maxValue = totalValue;
                bestNumItems = numItems;
                bestSumPallets = sumPallets;

                for (unsigned int k = 0; k < n; k++) {
                    usedItems[k] = curCandidate[k];
                }
            }
        }

        unsigned int curIndex = 0;
        while (curCandidate[curIndex]) {
            curIndex++;
            if (curIndex == n) break;
        }
        if (curIndex == n) break;

        for (unsigned int i = 0; i < curIndex; i++) {
            curCandidate[i] = false;
        }
        curCandidate[curIndex] = true;
    }

    for (unsigned int i = 0; i < n; i++) {
        if (usedItems[i]) {
            cout << i + 1 << endl;
        }
    }

    return maxValue;
}

/**
 * @brief Dynamic programming solution for the 0/1 Knapsack problem using static arrays.
 * 
 * Constructs a DP table of size [n][maxWeight+1] and backtracks to find which items were selected.
 * 
 * @param values Array of item values.
 * @param weights Array of item weights.
 * @param n Number of items.
 * @param maxWeight Maximum allowable total weight.
 * @param usedItems Output array indicating selected items.
 * @return Maximum value that can be obtained.
 */
unsigned int knapsackDP(
    unsigned int values[],
    unsigned int weights[],
    unsigned int n,
    unsigned int maxWeight,
    bool usedItems[])
{
    // DP arrays
    // maxValue[i][w]: max value for first i items and capacity w
    // minCount[i][w]: min number of items for maxValue[i][w]
    // minSumIDs[i][w]: min sum of pallet IDs for tie breaks
    unsigned int maxValue[100][1000];
    unsigned int minCount[100][1000];
    unsigned int minSumIDs[100][1000];

    // Initialize for first item
    for (unsigned int w = 0; w <= maxWeight; w++) {
        if (w >= weights[0]) {
            maxValue[0][w] = values[0];
            minCount[0][w] = 1;
            minSumIDs[0][w] = 0; // pallet ID = 0 for first item
        } else {
            maxValue[0][w] = 0;
            minCount[0][w] = 0;
            minSumIDs[0][w] = UINT_MAX; // no items
        }
    }

    // Fill dp for other items
    for (unsigned int i = 1; i < n; i++) {
        for (unsigned int w = 0; w <= maxWeight; w++) {
            // Option 1: don't take item i
            unsigned int val1 = maxValue[i - 1][w];
            unsigned int cnt1 = minCount[i - 1][w];
            unsigned int sum1 = minSumIDs[i - 1][w];

            if (w < weights[i]) {
                // Can't take item i
                maxValue[i][w] = val1;
                minCount[i][w] = cnt1;
                minSumIDs[i][w] = sum1;
            } else {
                unsigned int prevW = w - weights[i];
                unsigned int val2 = maxValue[i - 1][prevW] + values[i];
                unsigned int cnt2 = minCount[i - 1][prevW] + 1;
                unsigned int sum2 = minSumIDs[i - 1][prevW] + i;

                if (val2 > val1 ||
                    (val2 == val1 && cnt2 < cnt1) ||
                    (val2 == val1 && cnt2 == cnt1 && sum2 < sum1)) {
                    maxValue[i][w] = val2;
                    minCount[i][w] = cnt2;
                    minSumIDs[i][w] = sum2;
                } else {
                    maxValue[i][w] = val1;
                    minCount[i][w] = cnt1;
                    minSumIDs[i][w] = sum1;
                }
            }
        }
    }

    // Backtracking
    for (unsigned int i = 0; i < n; i++) {
        usedItems[i] = false;
    }

    unsigned int w = maxWeight;
    for (int i = n - 1; i > 0; i--) {
        if (w == 0) break;

        if (maxValue[i][w] != maxValue[i - 1][w] ||
            minCount[i][w] != minCount[i - 1][w] ||
            minSumIDs[i][w] != minSumIDs[i - 1][w])
        {
            usedItems[i] = true;
            w -= weights[i];
        }
    }
    // Check first item
    if (w >= weights[0] && maxValue[0][w] > 0) {
        usedItems[0] = true;
    }

    // Print chosen items (1-based indexing)
    cout << "Selected items (1-based indices):" << endl;
    for (unsigned int i = 0; i < n; i++) {
        if (usedItems[i]) {
            cout << (i + 1) << endl;
        }
    }

    return maxValue[n - 1][maxWeight];
}

/**
 * @brief Dynamic programming solution using vectors instead of static arrays.
 * 
 * Functionally similar to knapsackDP but uses std::vector for flexibility.
 * 
 * @param values Array of item values.
 * @param weights Array of item weights.
 * @param n Number of items.
 * @param maxWeight Maximum allowable total weight.
 * @param usedItems Output array indicating selected items.
 * @return Maximum value that can be obtained.
 */

unsigned int knapsackDP1(
    unsigned int values[],
    unsigned int weights[],
    unsigned int n,
    unsigned int maxWeight,
    bool usedItems[])
{
    // DP tables
    vector<vector<unsigned int>> maxValue(n, vector<unsigned int>(maxWeight + 1, 0));
    vector<vector<unsigned int>> minCount(n, vector<unsigned int>(maxWeight + 1, UINT_MAX));
    vector<vector<unsigned int>> minSumIDs(n, vector<unsigned int>(maxWeight + 1, UINT_MAX));

    // Initialize first row
    for (unsigned int k = 0; k <= maxWeight; k++) {
        if (k >= weights[0]) {
            maxValue[0][k] = values[0];
            minCount[0][k] = 1;
            minSumIDs[0][k] = 0; // pallet id 0 for first item
        } else {
            maxValue[0][k] = 0;
            minCount[0][k] = 0;
            minSumIDs[0][k] = UINT_MAX;
        }
    }

    // Initialize minCount for k=0 in other rows
    for (unsigned int i = 1; i < n; i++) {
        maxValue[i][0] = 0;
        minCount[i][0] = 0;
        minSumIDs[i][0] = UINT_MAX;
    }

    // Fill DP tables with tie-breaks
    for (unsigned int i = 1; i < n; i++) {
        for (unsigned int k = 1; k <= maxWeight; k++) {
            if (k < weights[i]) {
                maxValue[i][k] = maxValue[i - 1][k];
                minCount[i][k] = minCount[i - 1][k];
                minSumIDs[i][k] = minSumIDs[i - 1][k];
            } else {
                unsigned int valUsing = maxValue[i - 1][k - weights[i]] + values[i];
                unsigned int cntUsing = minCount[i - 1][k - weights[i]] + 1;
                unsigned int sumUsing = minSumIDs[i - 1][k - weights[i]] + i;

                unsigned int valNotUsing = maxValue[i - 1][k];
                unsigned int cntNotUsing = minCount[i - 1][k];
                unsigned int sumNotUsing = minSumIDs[i - 1][k];

                // Tie-break logic:
                if (valUsing > valNotUsing ||
                    (valUsing == valNotUsing && cntUsing < cntNotUsing) ||
                    (valUsing == valNotUsing && cntUsing == cntNotUsing && sumUsing < sumNotUsing)) {
                    maxValue[i][k] = valUsing;
                    minCount[i][k] = cntUsing;
                    minSumIDs[i][k] = sumUsing;
                } else {
                    maxValue[i][k] = valNotUsing;
                    minCount[i][k] = cntNotUsing;
                    minSumIDs[i][k] = sumNotUsing;
                }
            }
        }
    }

    // Backtrack to find used items
    for (unsigned int i = 0; i < n; i++) {
        usedItems[i] = false;
    }
    unsigned int remainingWeight = maxWeight;
    for (int i = n - 1; i > 0; i--) {
        if (remainingWeight == 0) break;

        // Check if item i was used by comparing values and tie-break arrays
        if (maxValue[i][remainingWeight] != maxValue[i - 1][remainingWeight] ||
            minCount[i][remainingWeight] != minCount[i - 1][remainingWeight] ||
            minSumIDs[i][remainingWeight] != minSumIDs[i - 1][remainingWeight]) {
            usedItems[i] = true;
            remainingWeight -= weights[i];
        }
    }
    if (remainingWeight >= weights[0] && maxValue[0][remainingWeight] > 0) {
        usedItems[0] = true;
    }

    // Print chosen items 1-based
    for (unsigned int i = 0; i < n; i++) {
        if (usedItems[i]) cout << (i + 1) << endl;
    }

    return maxValue[n - 1][maxWeight];
}

/**
 * @brief Comparator for sorting Pallet items by profit-to-weight ratio.
 * 
 * @param a First pallet
 * @param b Second pallet
 * @return True if a has a better ratio than b
 */
bool compare(const Pallet& a, const Pallet& b) {
    double r1 = (double)a.profit / a.weight;
    double r2 = (double)b.profit / b.weight;
    return r1 > r2;
}

/**
 * @brief Greedy approximation algorithm for the knapsack problem.
 * 
 * Selects items by highest value-to-weight ratio until capacity is full.
 * 
 * @param pallets Vector of Pallet items.
 * @param n Number of items.
 * @param maxWeight Maximum allowed weight.
 * @param usedItems Output array indicating selected items.
 * @return Total profit achieved by the greedy algorithm.
 */
unsigned int knapsackGreedy(vector<Pallet> pallets, unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    sort(pallets.begin(), pallets.end(), compare);
    unsigned int maxValue = 0;
    unsigned int idx = 0;

    while (maxWeight > 0 && idx < n) {
        if (pallets[idx].weight <= maxWeight) {
            maxValue += pallets[idx].profit;
            maxWeight -= pallets[idx].weight;
            usedItems[pallets[idx].pallet] = true;
        }
        idx++;
    }

    cout << "Selected pallets IDs:" << endl;
    for (unsigned int i = 0; i < n; i++) {
        if (usedItems[i]) {
            cout << i + 1 << endl;
        }
    }

    return maxValue;
}

/**
 * @brief Branch-and-bound (ILP) solution to the 0/1 knapsack problem.
 * 
 * Prunes branches of the solution tree that cannot yield better results using upper-bound estimates.
 * 
 * @param values Array of item values.
 * @param weights Array of item weights.
 * @param n Number of items.
 * @param maxWeight Maximum allowable weight.
 * @param usedItems Output array marking selected items.
 * @return The optimal value found using branch-and-bound.
 */
unsigned int knapsackILP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    struct Node {
        unsigned int level;
        unsigned int value;
        unsigned int weight;
        unsigned int decisionsMask;  // bit i = whether item i used
        double bound;
    };

    // Compute bound for a node given decisions mask
    auto computeBound = [&](unsigned int level, unsigned int currValue, unsigned int currWeight, unsigned int decisionsMask) -> double {
        unsigned int totalWeight = currWeight;
        double bound = (double) currValue;

        for (unsigned int i = level; i < n; i++) {
            if ((decisionsMask & (1U << i)) != 0) continue;
            if (totalWeight + weights[i] <= maxWeight) {
                totalWeight += weights[i];
                bound += values[i];
            } else {
                unsigned int remain = maxWeight - totalWeight;
                bound += ((double)values[i] / weights[i]) * remain;
                break;
            }
        }
        return bound;
    };

    // Stack of nodes
    vector<Node> stack;

    // Initialize root node
    Node root = {0, 0, 0, 0, 0.0};
    root.bound = computeBound(0, 0, 0, 0);
    stack.push_back(root);

    unsigned int bestValue = 0;
    unsigned int bestNumItems = UINT_MAX;
    unsigned int bestSumIds = UINT_MAX;
    unsigned int bestDecisionsMask = 0;

    while (!stack.empty()) {
        Node node = stack.back();
        stack.pop_back();

        if (node.level == n) {
            // Count items and sum pallet IDs in decisionsMask
            unsigned int numItems = 0;
            unsigned int sumIds = 0;
            for (unsigned int i = 0; i < n; i++) {
                if ((node.decisionsMask & (1U << i)) != 0) {
                    numItems++;
                    sumIds += i;
                }
            }

            if (node.value > bestValue
                || (node.value == bestValue && numItems < bestNumItems)
                || (node.value == bestValue && numItems == bestNumItems && sumIds < bestSumIds)) {
                bestValue = node.value;
                bestNumItems = numItems;
                bestSumIds = sumIds;
                bestDecisionsMask = node.decisionsMask;
            }
            continue;
        }

        // Prune
        if (node.bound < bestValue) {
            continue;
        }

        // Branch 1: Include current item if possible
        if (node.weight + weights[node.level] <= maxWeight) {
            Node withItem;
            withItem.level = node.level + 1;
            withItem.value = node.value + values[node.level];
            withItem.weight = node.weight + weights[node.level];
            withItem.decisionsMask = node.decisionsMask | (1U << node.level);
            withItem.bound = computeBound(withItem.level, withItem.value, withItem.weight, withItem.decisionsMask);
            if (withItem.bound >= bestValue) {
                stack.push_back(withItem);
            }
        }

        // Branch 2: Exclude current item
        Node withoutItem;
        withoutItem.level = node.level + 1;
        withoutItem.value = node.value;
        withoutItem.weight = node.weight;
        withoutItem.decisionsMask = node.decisionsMask;
        withoutItem.bound = computeBound(withoutItem.level, withoutItem.value, withoutItem.weight, withoutItem.decisionsMask);
        if (withoutItem.bound >= bestValue) {
            stack.push_back(withoutItem);
        }
    }

    // Fill usedItems from bestDecisionsMask
    for (unsigned int i = 0; i < n; i++) {
        usedItems[i] = (bestDecisionsMask & (1U << i)) != 0;
        if (usedItems[i]) cout << i + 1 << endl;
    }

    return bestValue;
}