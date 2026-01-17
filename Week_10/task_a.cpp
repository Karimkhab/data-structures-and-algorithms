// Karim Khabibrakhmanov DSAI - 05
#include <iostream>
#include <vector>

using namespace std;

template<typename V, typename T>
class Graph {
public:
    class Vertex {
    public:
        V value;
        string color;
        bool isFree;
        Vertex* before;
        Vertex* after;
        vector<Vertex*> adjacency;
        int d;
        int f;
        Vertex(V value) : value(value), color("WHITE"), isFree(true), before(nullptr), after(nullptr), d(0), f(0) {}
    };

    class Edge {
    public:
        T value;
        Vertex* from;
        Vertex* to;
        Edge(T value, Vertex* from, Vertex* to) : value(value), from(from), to(to) {}
    };

private:
    void dfs_visit(Vertex* u, int& time, vector<Vertex*>& newVertices) {
        time++;
        u->d = time;
        u->color = "GRAY";
        for (Vertex* v : u->adjacency) {
            if (v->color == "WHITE") {
                v->before = u;
                dfs_visit(v, time, newVertices);
            }
        }
        u->color = "BLACK";
        time++;
        u->f = time;
        newVertices.push_back(u);
    }

    static bool compareVertex(Vertex* a, Vertex* b) {
        return a->f > b->f;
    }

public:
    vector<Vertex*> vertices;
    vector<Edge*> edges;

    void bubbleSort(vector<Vertex*>& arr, bool (*compare)(Vertex*, Vertex*)) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (compare(arr[j + 1], arr[j])) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
    Vertex* addVertex(V value) {
        Vertex* ver = new Vertex(value);
        vertices.push_back(ver);
        return ver;
    }

    Edge* addEdge(T value, Vertex* from, Vertex* to) {
        Edge* edge = new Edge(value, from, to);
        edges.push_back(edge);
        from->adjacency.push_back(to);
        return edge;
    }

    vector<Vertex*> KarimKhabibrakhmanov_dfs() {
        vector<Vertex*> newVertices;
        int time = 0;

        for (Vertex* u : vertices) {
            u->color = "WHITE";
            u->before = nullptr;
            u->d = 0;
            u->f = 0;
        }

        for (Vertex* u : vertices) {
            if (u->color == "WHITE") {
                dfs_visit(u, time, newVertices);
            }
        }
        return newVertices;
    }

    vector<V> KarimKhabibrakhmanov_topsort() {
        vector<Vertex*> resultFromDFS = KarimKhabibrakhmanov_dfs();
        vector<V> verticesTop;

        for (Edge* e : edges) {
            if (e->from->f <= e->to->f) {
                return vector<V>();
            }
        }

        bubbleSort(resultFromDFS, compareVertex);
        for (Vertex* v : resultFromDFS) {
            verticesTop.push_back(v->value);
        }

        return verticesTop;
    }
};

int main() {
    int N;
    cin >> N;
    vector<string> words(N);
    for (int i = 0; i < N; i++) {
        cin >> words[i];
    }

    Graph<char, int> graph;
    vector<Graph<char, int>::Vertex*> nodes(256, nullptr);

    for (const string& word : words) {
        for (char c : word) {
            if (nodes[c] == nullptr) {
                nodes[c] = graph.addVertex(c);
            }
        }
    }

    for (int i = 0; i < N - 1; i++) {
        int minLength = min(words[i].size(), words[i+1].size());
        bool flag = 0;
        for (int j = 0; j < minLength; j++) {
            if (words[i][j] != words[i+1][j]) {
                graph.addEdge(0, nodes[words[i][j]], nodes[words[i+1][j]]);
                flag = 1;
                break;
            }
        }

        if (flag==0 && words[i].size() > words[i+1].size()) {
            cout << "Doh" << endl;
            return 0;
        }
    }

    vector<char> result = graph.KarimKhabibrakhmanov_topsort();

    if (result.empty()) {
        cout << "Doh" << endl;
    } else {
        for (int i = 0; i<result.size();i++) {
            cout << result[i];
        }
    }
}