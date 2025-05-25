#include <vector>
#include <string>
using namespace std;

#ifndef DATA_LOADER_H
#define DATA_LOADER_H

/**
 * @brief Loads pallet data from a CSV file.
 * 
 * @param filename Path to the CSV file containing pallet data.
 * @return Vector of Pallet objects loaded from the file.
 */
vector<Pallet> load_data_pallets(string filename);

/**
 * @brief Loads truck data from a CSV file.
 * 
 * @param filename Path to the CSV file containing truck data.
 * @return Truck object loaded from the file.
 */
Truck load_data_trucks(string filename);

#endif //DATA_LOADER_H
