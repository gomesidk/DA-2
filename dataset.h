//
// Created by joaog on 22/05/2025.
//

#ifndef DATASET_H
#define DATASET_H

struct Pallet {
    int pallet;
    int weight;
    int profit;

    Pallet(int p, int w, int pr) : pallet(p), weight(w), profit(pr) {}

};

struct Truck {
    int capacity;
    int pallets;

    Truck() : capacity(0), pallets(0) {}
    Truck(int c, int p) : capacity(c), pallets(p) {}
};

#endif //DATASET_H
