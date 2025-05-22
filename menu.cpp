#include <iostream>
#include <string>

using namespace std;

int menu() {
    int choice;
    int dataset;
    while (true) {
        cout << "Please select the dataset that you would like to use:" << endl;
        cin >> dataset;
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
