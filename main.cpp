#include <iostream>
#include "Network.h"
using namespace std;

int main() {
    // Create a network with 6 routers
    Network network(6);
    // Add connections
    network.addConnection(1, 2, 10);
    network.addConnection(1, 3, 5);
    network.addConnection(2, 3, 2);
    network.addConnection(2, 4, 1);
    network.addConnection(3, 2, 3);
    network.addConnection(3, 4, 9);
    network.addConnection(3, 5, 2);
    network.addConnection(4, 5, 4);
    network.addConnection(4, 6, 8);
    network.addConnection(5, 4, 6);
    network.addConnection(5, 6, 3);
    // Display network
    network.displayNetwork();
    // Find shortest route
    network.findShortestPath(1, 6);
    return 0;
}