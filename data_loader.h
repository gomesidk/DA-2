#include <vector>
#include <string>
using namespace std;

#ifndef DATA_LOADER_H
#define DATA_LOADER_H

vector<Pallet> load_data_pallets(string filename);
Truck load_data_trucks(string filename);

#endif //DATA_LOADER_H
