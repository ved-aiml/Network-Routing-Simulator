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
    routerActive.assign(n + 1, true);
}

// Check whether router number is valid
bool Network::isValidRouter(int router) {
    return router >= 1 && router <= n;
}

// Add a directed connection
void Network::addConnection(int u, int v, int latency) {
    if (!isValidRouter(u)) {
        cout << "Invalid source router!\n";
        cout << "Please enter a router between 1 and " << n << ".\n";
        return;
    }

    if (!isValidRouter(v)) {
        cout << "Invalid destination router!\n";
        cout << "Please enter a router between 1 and " << n << ".\n";
        return;
    }

    if (latency <= 0) {
        cout << "Latency must be greater than 0.\n";
        return;
    }

    // Check whether connection already exists
    for (auto &edge : adj[u]) {
        if (edge.first == v) {
            cout << "Connection already exists!\n";
            cout << "Use 'Update latency' to change its latency.\n";
            return;
        }
    }

    // Add connection
    adj[u].push_back({v, latency});
    cout << "Connection added successfully!\n";
}

// Remove a directed connection
void Network::removeConnection(int u, int v) {
    if (!isValidRouter(u)) {
        cout << "Invalid source router!\n";
        return;
    }

    if (!isValidRouter(v)) {
        cout << "Invalid destination router!\n";
        return;
    }

    if (!routerActive[u]) {
        cout << "Source router is DOWN.\n";
        return;
    }

    if (!routerActive[v]) {
        cout << "Destination router is DOWN.\n";
        return;
    }

    // Search for the connection
    for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
        if (it->first == v) {
            adj[u].erase(it);
            cout << "Connection removed successfully!\n";
            return;
        }
    }

    // Connection was not found
    cout << "Connection does not exist!\n";
}

// Update latency of an existing connection
void Network::updateLatency(int u, int v, int newLatency) {
    if (!isValidRouter(u)) {
        cout << "Invalid source router!\n";
        return;
    }

    if (!isValidRouter(v)) {
        cout << "Invalid destination router!\n";
        return;
    }

    if (newLatency <= 0) {
        cout << "Latency must be greater than 0.\n";
        return;
    }

    // Search for the connection
    for (auto &edge : adj[u]) {
        if (edge.first == v) {
            int oldLatency = edge.second;
            edge.second = newLatency;

            cout << "Latency updated successfully!\n";
            cout << "Router " << u << " -> Router " << v << " : "
                 << oldLatency << " ms -> " << newLatency << " ms\n";
            return;
        }
    }

    // Connection was not found
    cout << "Connection does not exist!\n";
}

// Fail a router
void Network::failRouter(int router) {
    if (!isValidRouter(router)) {
        cout << "Invalid router!\n";
        return;
    }

    if (!routerActive[router]) {
        cout << "Router " << router << " is already DOWN.\n";
        return;
    }

    routerActive[router] = false;
    cout << "\nRouter " << router << " has FAILED.\n";
    cout << "It will no longer participate in routing.\n";
}

// Recover a router
void Network::recoverRouter(int router) {
    if (!isValidRouter(router)) {
        cout << "Invalid router!\n";
        return;
    }

    if (routerActive[router]) {
        cout << "Router " << router << " is already UP.\n";
        return;
    }

    routerActive[router] = true;
    cout << "\nRouter " << router << " has been RECOVERED.\n";
    cout << "It can now participate in routing again.\n";
}

// Display network
void Network::displayNetwork() {
    cout << "\n===== Network Topology =====\n";

    for (int u = 1; u <= n; u++) {
        cout << "Router " << u << " [";
        if (routerActive[u]) {
            cout << "UP";
        } else {
            cout << "DOWN";
        }
        cout << "] -> ";

        if (adj[u].empty()) {
            cout << "No connections";
        } else {
            for (auto edge : adj[u]) {
                int v = edge.first;
                int latency = edge.second;
                cout << "(Router " << v << ", " << latency << " ms) ";
            }
        }
        cout << '\n';
    }
}

// Find shortest path
void Network::findShortestPath(int source, int destination) {
    if (!isValidRouter(source)) {
        cout << "Invalid source router!\n";
        return;
    }

    if (!isValidRouter(destination)) {
        cout << "Invalid destination router!\n";
        return;
    }

    // Source cannot be DOWN
    if (!routerActive[source]) {
        cout << "\nSource router is DOWN.\n";
        return;
    }

    // Destination cannot be DOWN
    if (!routerActive[destination]) {
        cout << "\nDestination router is DOWN.\n";
        return;
    }

    vector<int> dist(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);
    set<pair<int, int>> st;

    dist[source] = 0;
    st.insert({0, source});

    // Dijkstra
    while (!st.empty()) {
        auto current = *st.begin();
        int currentDist = current.first;
        int u = current.second;
        st.erase(st.begin());

        // If router has failed, skip it
        if (!routerActive[u]) {
            continue;
        }

        // Explore neighbours
        for (auto edge : adj[u]) {
            int v = edge.first;
            int latency = edge.second;

            // Do not use failed routers
            if (!routerActive[v]) {
                continue;
            }

            // Relaxation
            if (dist[v] > currentDist + latency) {
                auto old = st.find({dist[v], v});
                if (old != st.end()) {
                    st.erase(old);
                }

                dist[v] = currentDist + latency;
                parent[v] = u;
                st.insert({dist[v], v});
            }
        }
    }

    // Destination unreachable
    if (dist[destination] == INT_MAX) {
        cout << "\nNo active route exists from Router " << source
             << " to Router " << destination << ".\n";
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
    cout << "Latency     : " << dist[destination] << " ms\n";
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