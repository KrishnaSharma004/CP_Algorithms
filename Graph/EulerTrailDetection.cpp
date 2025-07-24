#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class Edge {
public:
    int from, to;
    Edge(int u, int v) : from(u), to(v) {}
};

class Graph {
public:
    Graph(int vertices) : n(vertices), deg(vertices, 0), adj(vertices) {}

    void addEdge(int u, int v) {
        int index = edges.size();
        edges.emplace_back(u, v);          // Forward edge
        adj[u].push_back(index);
        edges.emplace_back(v, u);          // Back edge
        adj[v].push_back(index + 1);
        deg[u]++;
        deg[v]++;
    }

    int eulerStart() const {
        int res = 0;
        std::vector<int> degree(n, 0);

        for (size_t i = 0; i < edges.size(); i += 2) {
            int u = edges[i ^ 1].to;
            int v = edges[i].to;
            res = u;
            degree[u]++;
            degree[v]--;
        }

        for (auto& d : degree) d = std::abs(d % 2);

        int countOdd = std::count(degree.begin(), degree.end(), 1);
        if (countOdd == 0) return res;
        if (countOdd == 2) {
            for (int i = 0; i < n; ++i) {
                if (degree[i] == 1) return i;
            }
        }
        return -1;
    }

    std::pair<int, std::vector<int>> eulerTrail() {
        int start = eulerStart();
        std::vector<int> trail;

        if (start == -1) return {start, trail};

        std::vector<bool> used(edges.size() / 2, false);
        std::vector<int> head(n);
        for (int i = 0; i < n; ++i) head[i] = 0;

        std::vector<size_t> index(n, 0);
        auto dfs = [&](auto&& self, int v) -> void {
            while (index[v] < adj[v].size()) {
                int e = adj[v][index[v]++];
                int eID = e / 2;
                if (used[eID]) continue;
                used[eID] = true;
                self(self, edges[e].to);
                trail.push_back(e);
            }
        };

        dfs(dfs, start);
        std::reverse(trail.begin(), trail.end());
        return {start, trail};
    }

    void printTrail(const std::pair<int, std::vector<int>>& result) const {
        if (result.first == -1) {
            std::cout << "No Euler trail or circuit exists.\n";
        } else {
            std::cout << "Euler trail starting from node " << result.first << ":\n";
            for (int e : result.second) {
                std::cout << edges[e].from << " -> " << edges[e].to << "\n";
            }
        }
    }

private:
    int n;
    std::vector<int> deg;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> adj;
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 1);

    auto result = g.eulerTrail();
    g.printTrail(result);
    return 0;
}
