#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <limits>

struct Edge {
    int from, to;
    int64_t weight;
    Edge(int u, int v, int64_t w) : from(u), to(v), weight(w) {}
};

class Graph {
public:
    Graph(int vertices) : n(vertices), adj(vertices) {}

    void addEdge(int u, int v, int64_t w) {
        adj[u].emplace_back(u, v, w);
    }

    std::pair<std::vector<uint64_t>, std::vector<std::pair<int, int>>> dijkstra(int s) const {
        constexpr uint64_t INF = std::numeric_limits<uint64_t>::max();
        std::vector<uint64_t> dist(n, INF);
        std::vector<std::pair<int, int>> pre(n, {-1, -1});  // {prev_node, edge_index}
        using que_t = std::pair<uint64_t, int>;
        std::priority_queue<que_t, std::vector<que_t>, std::greater<>> pq;

        dist[s] = 0;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [dv, v] = pq.top(); pq.pop();
            if (dv != dist[v]) continue;

            for (size_t i = 0; i < adj[v].size(); ++i) {
                const Edge& e = adj[v][i];
                int u = e.to;
                if (dist[v] + e.weight < dist[u]) {
                    dist[u] = dist[v] + e.weight;
                    pre[u] = {v, static_cast<int>(i)};
                    pq.push({dist[u], u});
                }
            }
        }

        return {dist, pre};
    }

    std::pair<int64_t, std::vector<std::pair<int, int>>> shortestPath(int s, int t) const {
        constexpr uint64_t INF = std::numeric_limits<uint64_t>::max();
        auto [dist, pre] = dijkstra(s);
        std::vector<std::pair<int, int>> path;

        if (dist[t] == INF) return {-1, path}; // unreachable

        for (int v = t; v != s; v = pre[v].first) {
            if (v == -1) break;
            path.push_back(pre[v]);
        }
        std::reverse(path.begin(), path.end());
        return {dist[t], path};
    }

    void printShortestPath(int s, int t) const {
        auto [dist, path] = shortestPath(s, t);
        if (dist == -1) {
            std::cout << "No path from " << s << " to " << t << "\n";
        } else {
            std::cout << "Shortest distance: " << dist << "\nPath:\n";
            int current = s;
            for (const auto& [prev, idx] : path) {
                const Edge& e = adj[prev][idx];
                std::cout << e.from << " -> " << e.to << " (weight " << e.weight << ")\n";
                current = e.to;
            }
        }
    }

private:
    int n;
    std::vector<std::vector<Edge>> adj;
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 4, 1);

    g.printShortestPath(0, 4);
    return 0;
}
