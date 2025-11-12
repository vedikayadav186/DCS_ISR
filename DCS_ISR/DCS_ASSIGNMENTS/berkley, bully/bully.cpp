#include <iostream>
using namespace std;

int main () {
    int nodes[6] = {1, 2, 3, 4, 5, 6};
    int failed = 5;   // Node 5 is down
    int starter = 2;  // Node 2 starts election
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


return 0;
}
