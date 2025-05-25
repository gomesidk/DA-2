#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "dataset.h"
#include "data_loader.h"
using namespace std;

/**
 * @brief Loads pallet data from a CSV file.
 * 
 * The CSV file is expected to have a header line, followed by lines
 * containing pallet ID, profit, and weight, separated by commas.
 * 
 * @param filename Path to the CSV file containing pallet data.
 * @return Vector of Pallet objects loaded from the file.
 */
vector<Pallet> load_data_pallets(string filename) {

    ifstream file(filename);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return {};
    }

    string line;

    // Skip the header line
    getline(file, line);

    vector<Pallet> pallets;

    while (getline(file, line)) {
        stringstream ss(line);
        string palletid, profit, weight;

        // Extract the data by separating based on commas
        getline(ss, palletid, ',');   // Read pallet ID
        getline(ss, profit, ',');     // Read profit
        getline(ss, weight, ',');     // Read weight

        // Convert string values to integers
        int palletid_int = stoi(palletid);
        int profit_int = stoi(profit);
        int weight_int = stoi(weight);

        // Create a Pallet object and add it to the vector
        pallets.push_back(Pallet(palletid_int, profit_int, weight_int));
    }

    file.close();

    return pallets;
}

/**
 * @brief Loads truck data from a CSV file.
 * 
 * The CSV file is expected to have a header line, followed by a single
 * line containing truck capacity and number of pallets, separated by commas.
 * 
 * @param filename Path to the CSV file containing truck data.
 * @return Truck object loaded from the file. Returns Truck(0, 0) on error.
 */
Truck load_data_trucks(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return {0, 0};
    }
    string line;
    int capacity_int, pallets_int;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string capacity, pallets;
        getline(ss, capacity, ',');
        getline(ss, pallets, ',');
        capacity_int = stoi(capacity);
        pallets_int = stoi(pallets);
    }
    file.close();
    return Truck(capacity_int, pallets_int);
}
