# Network Routing Simulator

A C++ based network routing simulator that models routers as a weighted graph and uses **Dijkstra's algorithm** to find the shortest route between routers.

## Features

The simulator currently provides the following features:

1. **Add Connection**

   * Add a directed connection between two routers.
   * Specify the latency of the connection in milliseconds.

2. **Remove Connection**

   * Remove an existing connection between two routers.

3. **Update Connection Latency**

   * Change the latency of an existing connection.

4. **Fail Router**

   * Mark a router as `DOWN`.
   * Failed routers are not considered while finding routes.

5. **Recover Router**

   * Bring a failed router back to the `UP` state.
   * The router can participate in routing again.

6. **Display Network**

   * Display all routers and their connections.
   * Shows the current status of each router (`UP`/`DOWN`).
   * Displays connection latency.

7. **Find Shortest Route**

   * Uses Dijkstra's shortest-path algorithm.
   * Displays:

     * Source router
     * Destination router
     * Shortest latency
     * Number of hops
     * Actual route

## Tech Stack

* **Language:** C++
* **Algorithm:** Dijkstra's Algorithm
* **Data Structure:** Adjacency List
* **Build:** g++

## Project Structure

```text
Network_routing/
│
├── main.cpp
├── Network.h
├── Network.cpp
└── README.md
```

## How to Run

Compile the project using:

```bash
g++ main.cpp Network.cpp -o simulator
```

Run:

### Windows

```powershell
.\simulator.exe
```

### Linux / macOS

```bash
./simulator
```

## Example

A network can be created by adding connections such as:

```text
Router 1 → Router 2 : 10 ms
Router 1 → Router 3 : 5 ms
Router 3 → Router 4 : 3 ms
Router 4 → Router 5 : 5 ms
```

The simulator can then find the shortest route between two routers.

Example:

```text
Source      : Router 1
Destination : Router 5
Latency     : 13 ms
Hops        : 3
Route       : Router 1 → Router 3 → Router 4 → Router 5
```

## Current Limitations

* Router IDs are numbered from `1` to `N`.
* Connections are currently directed.
* The simulator runs through a command-line interface.
* Network data is maintained only while the program is running.
