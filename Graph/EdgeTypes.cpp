#include <iostream>
#include <vector>
#include <algorithm>

class Edge {
public:
    int from, to;
    Edge(int u, int v) : from(u), to(v) {}
};

class Graph {
public:
    Graph(int vertices) : adj(vertices), n(vertices) {}

    void addEdge(int u, int v) {
        int index = edges.size();
        edges.emplace_back(u, v);         // forward edge
        adj[u].push_back(index);
        edges.emplace_back(v, u);         // back edge
        adj[v].push_back(index + 1);
    }

    std::vector<int> findCycle() const {
        std::vector<char> state(n, 0);
        std::vector<int> cycle;

        auto dfs = [&](auto&& self, int v, int pe) -> bool {
            state[v] = 1;
            bool found = false;

            for (int e : adj[v]) {
                if (e / 2 == pe / 2) continue;
                int u = edges[e].to;
                if (state[u] == 0) {
                    if (self(self, u, e)) {
                        if (!cycle.empty() &&
                            edges[cycle[0]].to != edges[cycle.back() ^ 1].to) {
                            cycle.push_back(e);
                        }
                        found = true;
                        break;
                    }
                } else if (state[u] == 1) {
                    cycle = {e};
                    found = true;
                    break;
                }
            }

            state[v] = 2;
            return found;
        };

        for (int i = 0; i < n; ++i) {
            if (state[i] == 0 && dfs(dfs, i, -2)) break;
        }

        std::reverse(cycle.begin(), cycle.end());
        return cycle;
    }

    void printCycle(const std::vector<int>& cycle) const {
        if (cycle.empty()) {
            std::cout << "No cycle found\n";
        } else {
            std::cout << "Cycle edges:\n";
            for (int e : cycle) {
                std::cout << edges[e].from << " -> " << edges[e].to << "\n";
            }
        }
    }

private:
    int n;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> adj;
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 1);  // creates a cycle
    g.addEdge(3, 4);

    std::vector<int> cycle = g.findCycle();
    g.printCycle(cycle);
    return 0;
}
