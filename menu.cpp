#include <iostream>
#include <string>
#include <vector>
#include "dataset.h"
#include "data_loader.h"
#include "menu.h"
using namespace std;

int menu() {
    int choice;
    int dataset;
    while (true) {
        cout << "Please select the dataset that you would like to use:" << endl;
        cin >> dataset;
        string pallets_filename = "Pallets_0" + to_string(dataset) + ".csv";
        string trucks_filename = "TruckAndPallets_0" + to_string(dataset) + ".csv";
        vector<Pallet> pallets;
        Truck truck;
        pallets = load_data_pallets(pallets_filename);
        truck = load_data_trucks(trucks_filename);
        cout << "\nNow select the algorithmic approach you would like to use to solve this problem" << endl;
        cout << "1. Brute-Force Approach" << endl;
        cout << "2. Dynamic Programming Approach" << endl;
        cout << "3. Approximation Approach" << endl;
        cout << "4. ILP Approach" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
            break;
            case 2:
            break;
            case 3:
            break;
            case 4:
            return 0;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
