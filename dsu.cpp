#include <iostream>
#include <vector>

using namespace std;

struct Graph {
    int num_nodes;
    vector<pair<int, int>> edges;
};

class DSU {
private:
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // path compression
        return parent[x];
    }

    void unite(int x, int y) {
        int xr = find(x);
        int yr = find(y);
        if (xr == yr) return;

        if (rank[xr] < rank[yr]) {
            parent[xr] = yr;
        } else if (rank[xr] > rank[yr]) {
            parent[yr] = xr;
        } else {
            parent[yr] = xr;
            rank[xr]++;
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    Graph G;
    G.num_nodes = 5;
    G.edges = {{0, 1}, {1, 2}, {3, 4}};

    DSU dsu(G.num_nodes);

    for (auto [u, v] : G.edges) {
        dsu.unite(u, v);
    }

    cout << "0 and 2 connected? " << (dsu.connected(0, 2) ? "Yes" : "No") << "\n";
    cout << "0 and 4 connected? " << (dsu.connected(0, 4) ? "Yes" : "No") << "\n";

    return 0;
}
