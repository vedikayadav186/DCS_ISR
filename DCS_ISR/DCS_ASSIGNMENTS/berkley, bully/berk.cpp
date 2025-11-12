#include <iostream>
using namespace std;

int main() {
    int clocks[4] = {100, 110, 95, 105};
    int sum = 0, avg = 0;

    for (int i = 0; i < 4; i++)
        sum += clocks[i];

    avg = sum / 4;

    cout << "\n--- Berkeley Algorithm ---\n";
    cout << "Average time = " << avg << "\n";

    for (int i = 0; i < 4; i++) {
        int offset = avg - clocks[i];
        clocks[i] += offset;
        cout << "Node " << i + 1 << " adjusted by " << offset 
             << " => " << clocks[i] << "\n";
    }
     return 0;
}





