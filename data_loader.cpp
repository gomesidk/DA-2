#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "dataset.h"
#include "data_loader.h"
using namespace std;

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
        getline(ss, palletid, ',');   // Read Name
        getline(ss, profit, ','); // Read Age
        getline(ss, weight, ',');   // Read City

        // Convert age from string to integer
        int palletid_int = stoi(palletid);
        int profit_int = stoi(profit);
        int weight_int = stoi(weight);

        // Create a Person object and store it in the vector
        pallets.push_back(Pallet(palletid_int, profit_int, weight_int));
    }

    file.close();

    return pallets;
}

Truck load_data_trucks(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return {0, 0};
    }
    string line;
    int capacity_int, pallets_int;
    getline(file, line);
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
