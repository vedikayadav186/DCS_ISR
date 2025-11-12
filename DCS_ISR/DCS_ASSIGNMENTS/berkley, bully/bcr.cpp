#include <iostream>
using namespace std;
//Without vector
// ========== BERKELEY ==========
void berkeley() {
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
}

// ========== BULLY ==========
void bully() {
    int nodes[6] = {1, 2, 3, 4, 5, 6};
    int failed = 5;   // node 5 is down
    int starter = 2;  // node 2 starts election
    int newLeader = starter;

    cout << "\n--- Bully Algorithm ---\n";
    cout << "Node " << failed << " is down.\n";
    cout << "Node " << starter << " starts election...\n";

    for (int i = 0; i < 6; i++) {
        int n = nodes[i];
        if (n > starter && n != failed) {
            cout << "Node " << n << " responds (higher).\n";
            if (n > newLeader) newLeader = n;
        }
    }
    cout << "New leader is Node " << newLeader << "\n";
}

// ========== RING ==========
void ring() {
    int nodes[5] = {1, 2, 3, 4, 5};
    int failed = 5;   // node 5 is down
    int starter = 2;
    int maxNode = starter;

    cout << "\n--- Ring Algorithm ---\n";
    cout << "Node " << failed << " is down.\n";
    cout << "Node " << starter << " starts ring election...\n";

    for (int i = 0; i < 5; i++) {
        int n = nodes[i];
        if (n != failed) {
            cout << "Node " << n << " passes token.\n";
            if (n > maxNode) maxNode = n;
        }
    }
    cout << "Leader elected: Node " << maxNode << "\n";
}

// ========== MAIN ==========
int main() {
    int ch;
    cout << "Choose an algorithm:\n";
    cout << "1. Berkeley\n";
    cout << "2. Bully\n";
    cout << "3. Ring\n";
    cout<<"hii";
    cout << "Enter choice: ";
    cin >> ch;

    if (ch == 1)
        berkeley();
    else if (ch == 2)
        bully();
    else if (ch == 3)
        ring();
    else
        cout << "Invalid choice.\n";

    return 0;
}
