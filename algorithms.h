//
// Created by joaog on 23/05/2025.
//

#include "dataset.h"
#include <vector>
using namespace std;

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

/**
 * @brief Brute-force solution for the 0/1 Knapsack problem.
 * 
 * @param values Array of item values.
 * @param weights Array of item weights.
 * @param n Number of items.
 * @param maxWeight Maximum total weight allowed.
 * @param usedItems Output array marking which items are used.
 * @return Maximum total value that fits in the knapsack.
 */
unsigned int knapsackBF(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

/**
 * @brief Dynamic programming solution with static arrays for the knapsack problem.
 * 
 * @param values Array of item values.
 * @param weights Array of item weights.
 * @param n Number of items.
 * @param maxWeight Maximum total weight allowed.
 * @param usedItems Output array marking which items are used.
 * @return Maximum total value that fits in the knapsack.
 */
unsigned int knapsackDP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

/**
 * @brief Dynamic programming solution using std::vector for the knapsack problem.
 * 
 * @param values Array of item values.
 * @param weights Array of item weights.
 * @param n Number of items.
 * @param maxWeight Maximum total weight allowed.
 * @param usedItems Output array marking which items are used.
 * @return Maximum total value that fits in the knapsack.
 */
unsigned int knapsackDP1(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

/**
 * @brief Greedy heuristic solution for the knapsack problem based on profit-to-weight ratio.
 * 
 * @param pallets Vector of Pallet items.
 * @param n Number of items.
 * @param maxWeight Maximum total weight allowed.
 * @param usedItems Output array marking which items are used.
 * @return Total profit obtained by the greedy algorithm.
 */
unsigned int knapsackGreedy(vector<Pallet> pallets, unsigned int n, unsigned int maxWeight, bool usedItems[]);

/**
 * @brief Branch-and-bound (ILP) solution for the knapsack problem.
 * 
 * @param values Array of item values.
 * @param weights Array of item weights.
 * @param n Number of items.
 * @param maxWeight Maximum total weight allowed.
 * @param usedItems Output array marking which items are used.
 * @return Maximum total value found by branch-and-bound.
 */
unsigned int knapsackILP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

#endif //ALGORITHMS_H
