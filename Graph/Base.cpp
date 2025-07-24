#include <iostream>
#include <vector>
#include <utility>

class Graph {
public:
    Graph(int vertices) : adj(vertices) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // because it's undirected
    }

    void printGraph() const {
        for (size_t i = 0; i < adj.size(); ++i) {
            std::cout << "Node " << i << ": ";
            for (int neighbor : adj[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }

private:
    std::vector<std::vector<int>> adj;
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.printGraph();
    return 0;
}
