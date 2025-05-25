//
// Created by joaog on 22/05/2025.
//

#ifndef DATASET_H
#define DATASET_H

/**
 * @struct Pallet
 * @brief Represents a pallet with an ID, weight, and profit value.
 */
struct Pallet {
    int pallet; ///< Pallet ID
    int weight; ///< Weight of the pallet
    int profit; ///< Profit associated with the pallet

    /**
     * @brief Constructor to initialize a Pallet.
     * @param p Pallet ID
     * @param w Weight of the pallet
     * @param pr Profit of the pallet
     */
    Pallet(int p, int w, int pr) : pallet(p), weight(w), profit(pr) {}
};

/**
 * @struct Truck
 * @brief Represents a truck with capacity and number of pallets it can carry.
 */
struct Truck {
    int capacity; ///< Maximum capacity of the truck
    int pallets;  ///< Number of pallets the truck can carry

    /**
     * @brief Default constructor initializes capacity and pallets to zero.
     */
    Truck() : capacity(0), pallets(0) {}

    /**
     * @brief Constructor to initialize Truck with capacity and pallets.
     * @param c Capacity of the truck
     * @param p Number of pallets
     */
    Truck(int c, int p) : capacity(c), pallets(p) {}
};

#endif //DATASET_H
