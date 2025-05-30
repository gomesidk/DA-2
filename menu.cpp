#include <iostream>
#include <string>
#include <vector>
#include "dataset.h"
#include "data_loader.h"
#include "menu.h"
#include "algorithms.h"
using namespace std;

/**
 * @brief Displays the interactive menu to the user to select dataset and algorithm,
 * loads the data, runs the selected knapsack algorithm, and outputs the result.
 *
 * The menu allows the user to choose among multiple datasets and algorithmic
 * approaches to solve the knapsack problem, including Brute Force, Dynamic Programming,
 * Approximation (Greedy), and Integer Linear Programming (ILP).
 *
 * The function loops until the user chooses to exit by pressing 0.
 */
void menu() {
    int choice;
    int dataset;
    string pallets_filename;
    string trucks_filename;
    unsigned int res = 0;
    while (true) {
        cout << "Welcome to the menu. If you would like to exit at any time, just press 0." << endl;
        cout << "Please select the dataset that you would like to use:" << endl;
        cin >> dataset;
        if (dataset < 5) {
            if (dataset == 0) {
                cout << "exiting..." << endl;
                break;
            }
            pallets_filename = "../datasets/Pallets_0" + to_string(dataset) + ".csv";
            trucks_filename = "../datasets/TruckAndPallets_0" + to_string(dataset) + ".csv";
        }
        else {
            if (dataset >= 10) {
                pallets_filename = "../datasets-extra/Pallets_" + to_string(dataset) + ".csv";
                trucks_filename = "../datasets-extra/TruckAndPallets_" + to_string(dataset) + ".csv";
            }
            else {
                pallets_filename = "../datasets-extra/Pallets_0" + to_string(dataset) + ".csv";
                trucks_filename = "../datasets-extra/TruckAndPallets_0" + to_string(dataset) + ".csv";
            }
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
            case 0: {
                cout << "exiting..." << endl;
                exit(0);
            }
            case 1: {
                res = knapsackBF(values, weights, n, maxWeight, usedItems);
                cout << "\nThe best solution is " << res << endl;
                break;
            }
            case 2: {
                if (maxWeight <= 1000 && n <= 100) {
                    res = knapsackDP(values, weights, n, maxWeight, usedItems);
                } else {
                    res = knapsackDP1(values, weights, n, maxWeight, usedItems);
                }
                cout << "\nThe best solution is " << res << endl;
                break;
            }
            case 3: {
                res = knapsackGreedy(pallets, n, maxWeight, usedItems);
                cout << "\nThe best solution is " << res << endl;
                break;
            }
            case 4:
                res = knapsackILP(values, weights, n, maxWeight, usedItems);
                cout << "\nThe best solution is " << res << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }

}
