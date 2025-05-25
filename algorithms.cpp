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
unsigned int knapsackDP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxValue[100][1000];

    for(unsigned int k = 0; k <= maxWeight; k++) {
        maxValue[0][k] = (k >= weights[0]) ? values[0] : 0;
    }
    for(unsigned int i = 1; i < n; i++) {
        maxValue[i][0] = 0;
    }

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

    for(unsigned int i = 0; i < n; i++) usedItems[i] = false;

    unsigned int remainingWeight = maxWeight;
    for(int i = n - 1; i > 0; i--) {
        if (remainingWeight == 0) break;
        if (maxValue[i][remainingWeight] != maxValue[i - 1][remainingWeight]) {
            usedItems[i] = true;
            remainingWeight -= weights[i];
        }
    }
    if (remainingWeight >= weights[0]) usedItems[0] = true;

    for(unsigned int i = 0; i < n; i++) {
        if (usedItems[i]) cout << i + 1 << endl;
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
unsigned int knapsackDP1(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    vector maxValue(n, vector<unsigned int>(maxWeight + 1, 0));

    for (unsigned int k = 0; k <= maxWeight; k++) {
        maxValue[0][k] = (k >= weights[0]) ? values[0] : 0;
    }

    for (unsigned int i = 1; i < n; i++) {
        maxValue[i][0] = 0;
    }

    for (unsigned int i = 1; i < n; i++) {
        for (unsigned int k = 1; k <= maxWeight; k++) {
            if (k < weights[i]) {
                maxValue[i][k] = maxValue[i - 1][k];
            } else {
                unsigned int valUsing = maxValue[i - 1][k - weights[i]] + values[i];
                maxValue[i][k] = (valUsing > maxValue[i - 1][k]) ? valUsing : maxValue[i - 1][k];
            }
        }
    }

    for (unsigned int i = 0; i < n; i++) usedItems[i] = false;

    unsigned int remainingWeight = maxWeight;
    for (int i = n - 1; i > 0; i--) {
        if (remainingWeight == 0) break;
        if (maxValue[i][remainingWeight] != maxValue[i - 1][remainingWeight]) {
            usedItems[i] = true;
            remainingWeight -= weights[i];
        }
    }
    if (remainingWeight >= weights[0]) usedItems[0] = true;

    for (unsigned int i = 0; i < n; i++) {
        if (usedItems[i]) cout << i + 1 << endl;
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
                bound += ((double)values[i] / weights[i]) * remain;
                break;
            }
        }

        return bound;
    };

    Node bestNode = {0, 0, 0, {}, 0.0};
    for (unsigned int i = 0; i < n; i++) bestNode.decisions[i] = false;

    vector<Node> stack;
    Node root = {0, 0, 0, {}, 0.0};
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

        if (node.weight + weights[node.level] <= maxWeight) {
            Node withItem = node;
            withItem.level++;
            withItem.weight += weights[node.level];
            withItem.value += values[node.level];
            withItem.decisions[node.level] = true;
            withItem.bound = computeBound(withItem);
            if (withItem.bound >= bestNode.value) {
                stack.push_back(withItem);
            }
        }

        Node withoutItem = node;
        withoutItem.level++;
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
