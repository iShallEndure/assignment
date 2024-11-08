#include <iostream>
#include <vector>

class DisjointSetUnion {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DisjointSetUnion(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int main() {
    DisjointSetUnion dsu(10);

    dsu.unionSets(0, 1);
    dsu.unionSets(1, 2);
    dsu.unionSets(3, 4);

    std::cout << dsu.find(2) << std::endl;
    std::cout << dsu.find(3) << std::endl;
    std::cout << dsu.find(4) << std::endl;

    return 0;
}