#include <iostream>
using namespace std;

void ring() {
    int nodes[6] = {1, 2, 3, 4, 5, 6};
    int failed = 5;   // Node 5 is down
    int starter = 2;
    int maxNode = starter;

    cout << "\n--- Ring Algorithm ---\n";
    cout << "Node " << failed << " is down.\n";
    cout << "Node " << starter << " starts ring election...\n";

    for (int i = 0; i < 6; i++) {
        int n = nodes[i];
        if (n != failed) {
            cout << "Node " << n << " passes token.\n";
            if (n > maxNode) maxNode = n;
        }
    }

    cout << "Leader elected: Node " << maxNode << "\n";
}

int main() {
    ring();
    return 0;
}

