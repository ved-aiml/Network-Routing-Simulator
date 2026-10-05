#ifndef NETWORK_H
#define NETWORK_H
#include <vector>
#include <utility>
using namespace std;
class Network {
private:
    int n;
    // adj[u] = {destination router, latency}
    vector<vector<pair<int, int>>> adj;
public:
    // Constructor
    Network(int n);
    // Add a directed connection
    void addConnection(int u,int v,int latency);
    // Display complete network
    void displayNetwork();
    // Find shortest route using Dijkstra
    void findShortestPath(int source, int destination);
};
#endif