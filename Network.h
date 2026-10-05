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
    vector<bool>routerActive;
    bool isValidRouter(int router);

public:
    Network(int n);
    void addConnection(int u, int v, int latency);
    void removeConnection(int u, int v);
    void updateLatency(int u, int v, int newLatency);
    void displayNetwork();
    void findShortestPath(int source, int destination);
    void failRouter(int router);
    void recoverRouter(int router);
};

#endif