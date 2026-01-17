// Karim Khabibrakhmanov DSAI - 05
#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <typename T>
class Vertex {
public:
    list<Vertex<T>*> adjVertices;
    int index;

    Vertex( int idx): index(idx) {}
};

template <typename T>
class Edge {
public:
    Vertex<T>* from;
    Vertex<T>* to;

    Edge(Vertex<T>* f, Vertex<T>* t) : from(f), to(t) {}
};


class DSU {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int u) {
        return parent[u] == u ? u : (parent[u] = find(parent[u]));
    }

    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (rank[u] < rank[v])
                swap(u, v);
            parent[v] = u;
            if (rank[u] == rank[v])
                rank[u]++;
        }
    }
};

template <typename T>
class Graph {
private:
    vector<Vertex<T>*> vertices;
    vector<Edge<T>*> edges;

public:

    Vertex<T>* addVertex(T label) {
        int idx = vertices.size();
        Vertex<T>* v = new Vertex<T>(idx);
        vertices.push_back(v);
        return v;
    }

    Vertex<T>* getVertex(int index) {
        if (index >= 0 && index < vertices.size()){
            return vertices[index];
        }
        return nullptr;
    }

    Edge<T>* addEdge(Vertex<T>* from, Vertex<T>* to) {
        Edge<T>* e = new Edge<T>(from, to);
        edges.push_back(e);
        from->adjVertices.push_back(to);
        to->adjVertices.push_back(from);
        return e;
    }

    int countConnectedComponents() {
        DSU dsu(vertices.size());

        for (Edge<T>* e : edges) {
            int u = e->from->index;
            int v = e->to->index;
            dsu.unite(u, v);
        }

        int components = 0;
        for (int i = 0; i < vertices.size(); i++) {
            if (dsu.find(i) == i)
                components++;
        }

        return components;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    Graph<int> graph;

    for (int i = 1; i <= N; i++) {
        graph.addVertex(i);
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(graph.getVertex(u-1), graph.getVertex(v-1));
    }

    cout << graph.countConnectedComponents() << "\n";
}