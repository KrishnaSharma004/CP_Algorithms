#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

struct Edge {
    int from, to;
    int64_t weight;
    Edge(int u, int v, int64_t w) : from(u), to(v), weight(w) {}
};

class DSU {
public:
    DSU(int n) : parent(n) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] != v)
            parent[v] = find(parent[v]);
        return parent[v];
    }

    bool unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA == rootB) return false;
        parent[rootA] = rootB;
        return true;
    }

private:
    std::vector<int> parent;
};

class Graph {
public:
    Graph(int vertices) : n(vertices) {}

    void addEdge(int u, int v, int64_t w) {
        edges.emplace_back(u, v, w);
    }

    std::pair<int64_t, std::vector<Edge>> computeMST() const {
        std::vector<Edge> sortedEdges = edges;
        std::sort(sortedEdges.begin(), sortedEdges.end(),
                  [](Edge const& a, Edge const& b) { return a.weight < b.weight; });

        DSU dsu(n);
        int64_t totalWeight = 0;
        std::vector<Edge> mstEdges;

        for (auto const& e : sortedEdges) {
            if (dsu.unite(e.from, e.to)) {
                totalWeight += e.weight;
                mstEdges.push_back(e);
            }
        }

        return {totalWeight, mstEdges};
    }

private:
    int n;
    std::vector<Edge> edges;
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    auto [totalWeight, mstEdges] = g.computeMST();

    std::cout << "Total MST weight: " << totalWeight << "\n";
    std::cout << "Edges in MST:\n";
    for (auto const& e : mstEdges) {
        std::cout << e.from << " -- " << e.to << " == " << e.weight << "\n";
    }

    return 0;
}
