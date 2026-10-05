#include "Network.h"

#include <iostream>
#include <set>
#include <climits>
#include <algorithm>

using namespace std;
// Constructor
Network::Network(int n) {
    this->n = n;
    // Routers are numbered from 1 to n
    adj.resize(n + 1);
}
// Add a directed connection
void Network::addConnection(int u, int v, int latency) {
    adj[u].push_back({v, latency});
}
// Display the network
void Network::displayNetwork() {
    cout << "\n===== Network Topology =====\n";
    for (int u = 1; u <= n; u++) {
        cout << "Router " << u << " -> ";
        for (auto edge : adj[u]) {
            int v = edge.first;
            int latency = edge.second;
            cout << "(Router " << v
                 << ", " << latency << " ms) ";
        }
        cout << '\n';
    }
}
// Find shortest path using Dijkstra
void Network::findShortestPath(int source, int destination) {
    vector<int> dist(n + 1, INT_MAX);
    // parent[v] stores the previous router
    // on the shortest path to v
    vector<int> parent(n + 1, -1);
    set<pair<int, int>> st;
    // Distance from source to itself
    dist[source] = 0;
    st.insert({0, source});
    // Dijkstra
    while (!st.empty()) {
        auto current = *st.begin();
        int currentDist = current.first;
        int u = current.second;
        st.erase(st.begin());
        // Explore all neighbours
        for (auto edge : adj[u]) {
            int v = edge.first;
            int latency = edge.second;
            // Relaxation
            if (dist[v] > currentDist + latency) {
                // Remove old value if it exists
                auto old = st.find({dist[v], v});
                if (old != st.end()) {
                    st.erase(old);
                }
                // Update distance
                dist[v] = currentDist + latency;
                // Store parent
                parent[v] = u;
                // Insert new distance
                st.insert({dist[v], v});
            }
        }
    }


    // Destination unreachable
    if (dist[destination] == INT_MAX) {
        cout << "\nNo route exists from Router "
             << source << " to Router "
             << destination << ".\n";

        return;
    }
    // Reconstruct path
    vector<int> path;
    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    // Display result
    cout << "\n===== Routing Result =====\n";
    cout << "Source      : Router " << source << '\n';
    cout << "Destination : Router " << destination << '\n';
    cout << "Latency     : " << dist[destination]
         << " ms\n";
    cout << "Hops        : " << path.size() - 1 << '\n';
    cout << "Route       : ";
    for (int i = 0; i < path.size(); i++) {
        cout << "Router " << path[i];
        if (i != path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << '\n';
}