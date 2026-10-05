#include <iostream>

#include "Network.h"

using namespace std;

int main() {
    int n;

    cout << "=====================================\n";
    cout << "      NETWORK ROUTING SIMULATOR\n";
    cout << "=====================================\n\n";
    // Get number of routers
    while (true) {
        cout << "Enter number of routers: ";
        cin >> n;
        if (n > 0) {
            break;
        }
        cout << "Number of routers must be greater than 0.\n";
    }
    Network network(n);
    int choice;

    while (true) {
        cout << "\n=====================================\n";
        cout << "              MENU\n";
        cout << "=====================================\n";
        cout << "1. Add connection\n";
        cout << "2. Remove connection\n";
        cout << "3. Update connection latency\n";
        cout << "4. Fail a router\n";
        cout << "5. Recover a router\n";
        cout << "6. Display network\n";
        cout << "7. Find shortest route\n";
        cout << "8. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        // Add connection
        if (choice == 1) {
            int u, v, latency;

            cout << "\nEnter source router: ";
            cin >> u;

            cout << "Enter destination router: ";
            cin >> v;

            cout << "Enter latency (ms): ";
            cin >> latency;

            network.addConnection(u, v, latency);
        }
        // Remove connection
        else if (choice == 2) {
            int u, v;

            cout << "\nEnter source router: ";
            cin >> u;

            cout << "Enter destination router: ";
            cin >> v;

            network.removeConnection(u, v);
        }
        // Update latency
        else if (choice == 3) {
            int u, v, newLatency;

            cout << "\nEnter source router: ";
            cin >> u;

            cout << "Enter destination router: ";
            cin >> v;

            cout << "Enter new latency (ms): ";
            cin >> newLatency;

            network.updateLatency(u, v, newLatency);
        }
        // Fail a router
        else if (choice == 4) {
            int router;

            cout << "\nEnter router to fail: ";
            cin >> router;

            network.failRouter(router);
        }
        // Recover a router
        else if (choice == 5) {
            int router;

            cout << "\nEnter router to recover: ";
            cin >> router;

            network.recoverRouter(router);
        }
        // Display network
        else if (choice == 6) {
            network.displayNetwork();
        }
        // Find shortest route
        else if (choice == 7) {
            int source, destination;

            cout << "\nEnter source router: ";
            cin >> source;

            cout << "Enter destination router: ";
            cin >> destination;

            network.findShortestPath(source, destination);
        }
        // Exit
        else if (choice == 8) {
            cout << "\nExiting simulator...\n";
            break;
        }
        // Invalid choice
        else {
            cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}