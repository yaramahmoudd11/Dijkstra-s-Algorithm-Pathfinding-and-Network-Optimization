#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Class to represent a graph edge
class Edge {
public:
    int destination;
    int weight;

    Edge(int dest, int w) : destination(dest), weight(w) {}
};

// Class to represent a graph node
class Node {
public:
    int id;
    vector<Edge> neighbors;

    Node(int i) : id(i) {}
};

// Comparator for priority queue based on distance
class CompareDistance {
public:
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // Min-heap
    }
};

// Function to perform Dijkstra's algorithm
vector<int> dijkstra(vector<Node>& graph, int source) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX); // Initialize distances to infinity
    dist[source] = 0; // Distance from source to source is 0

    // Priority queue to store nodes with their distances
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareDistance> pq;
    pq.push({ source, 0 });

    // Dijkstra's algorithm
    while (!pq.empty()) {
        int u = pq.top().first;
        pq.pop();

        for (const Edge& edge : graph[u].neighbors) {
            int v = edge.destination;
            int weight = edge.weight;

            // Relaxation step
            if (dist[u] != INT_MAX && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({ v, dist[v] });
            }
        }
    }

    return dist;
}

int main() {
    int n = 6; // Number of nodes
    vector<Node> graph(n, Node(-1)); // Create graph with n nodes

    // Add edges to the graph (node, weight)
    graph[0].neighbors.push_back(Edge(1, 5));
    graph[0].neighbors.push_back(Edge(2, 3));
    graph[1].neighbors.push_back(Edge(3, 6));
    graph[1].neighbors.push_back(Edge(2, 2));
    graph[2].neighbors.push_back(Edge(4, 4));
    graph[2].neighbors.push_back(Edge(5, 2));
    graph[3].neighbors.push_back(Edge(4, 1));
    graph[4].neighbors.push_back(Edge(5, 4));

    // Perform Dijkstra's algorithm from node 0
    vector<int> distances = dijkstra(graph, 0);

    // Print distances from source node
    cout << "Shortest distances from source node 0:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i << ": " << distances[i] << endl;
    }

    return 0;
}