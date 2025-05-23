//
// Created by joaog on 23/05/2025.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

unsigned int knapsackBF(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);
unsigned int knapsackDP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);
unsigned int knapsackGreedy(vector<Pallet> pallets, unsigned int n, unsigned int maxWeight, bool usedItems[]);

#endif //ALGORITHMS_H
