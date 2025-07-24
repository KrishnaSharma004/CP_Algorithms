#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class Graph {
public:
    Graph(int vertices) : adj(vertices), state(vertices, 0), parentEdge(vertices, -1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected graph
    }

    std::vector<int> findCycle() {
        std::vector<int> cycle;
        for (int i = 0; i < adj.size(); ++i) {
            if (state[i] == 0 && dfs(i, -1, cycle)) {
                std::reverse(cycle.begin(), cycle.end());
                break;
            }
        }
        return cycle;
    }

private:
    std::vector<std::vector<int>> adj;
    std::vector<char> state; // 0 = unvisited, 1 = visiting, 2 = visited
    std::vector<int> parentEdge;

    bool dfs(int v, int parent, std::vector<int>& cycle) {
        state[v] = 1;
        for (int u : adj[v]) {
            if (u == parent) continue;
            if (state[u] == 0) {
                parentEdge[u] = v;
                if (dfs(u, v, cycle)) {
                    if (cycle.empty() || cycle.front() != v) {
                        cycle.push_back(v);
                    }
                    return true;
                }
            } else if (state[u] == 1) {
                cycle.push_back(u);
                cycle.push_back(v);
                return true;
            }
        }
        state[v] = 2;
        return false;
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 2); // Creates a cycle

    std::vector<int> cycle = g.findCycle();
    if (!cycle.empty()) {
        std::cout << "Cycle found: ";
        for (int node : cycle)
            std::cout << node << " ";
        std::cout << "\n";
    } else {
        std::cout << "No cycle found\n";
    }

    return 0;
}
