#include <iostream>
#include <string>
#include <vector>
#include "dataset.h"
#include "data_loader.h"
#include "menu.h"

#include <algorithm>
#include <bits/ranges_algo.h>

#include "algorithms.h"
using namespace std;

int menu() {
    int choice;
    int dataset;
    string pallets_filename;
    string trucks_filename;
    while (true) {
        cout << "Please select the dataset that you would like to use:" << endl;
        cin >> dataset;
        if (dataset < 10) {
            pallets_filename = "Pallets_0" + to_string(dataset) + ".csv";
            trucks_filename = "TruckAndPallets_0" + to_string(dataset) + ".csv";
        }
        else {
            pallets_filename = "Pallets_" + to_string(dataset) + ".csv";
            trucks_filename = "TruckAndPallets_" + to_string(dataset) + ".csv";
        }
        vector<Pallet> pallets;
        Truck truck;
        pallets = load_data_pallets(pallets_filename);
        truck = load_data_trucks(trucks_filename);
        unsigned int n = truck.pallets;
        unsigned int values[n];
        unsigned int weights[n];
        for (unsigned int i = 0; i < n; i++) {
            values[i] = pallets[i].profit;
            weights[i] = pallets[i].weight;
        }
        unsigned int maxWeight = truck.capacity;
        bool usedItems[n];
        for (int i = 0; i < n; i++) {
            usedItems[i] = false;
        }
        cout << "\nNow select the algorithmic approach you would like to use to solve this problem" << endl;
        cout << "1. Brute-Force Approach" << endl;
        cout << "2. Dynamic Programming Approach" << endl;
        cout << "3. Approximation Approach" << endl;
        cout << "4. ILP Approach" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                unsigned int res = knapsackBF(values, weights, n, maxWeight, usedItems);
                cout << "\nThe best solution is " << res << endl;
                break;
            }
            case 2: {
                unsigned int res = knapsackDP(values, weights, n, maxWeight, usedItems);
                cout << "\nThe best solution is " << res << endl;
                break;
            }
            case 3: {
                unsigned int res = knapsackGreedy(pallets, n, maxWeight, usedItems);
                cout << "\nThe best solution is " << res << endl;
                break;
            }
            case 4:
            return 0;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
