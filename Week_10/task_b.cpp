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
        Vertex* before;
        vector<Vertex*> adjacency;
        int d;
        int f;
        bool visited;

        Vertex(V value): value(value), color("WHITE"), before(nullptr), d(0), f(0), visited(false) {}
    };

    class Edge {
    public:
        T value;
        Vertex* from;
        Vertex* to;
        Edge(T value, Vertex* from, Vertex* to): value(value), from(from), to(to) {}
    };

    vector<Vertex*> vertices;
    vector<Edge*> edges;

    Vertex* findVertex(V value) {
        for (Vertex* v : vertices) {
            if (v->value == value){
                return v;
            }
        }
        return nullptr;
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

    void KarimKhabibrakhmanov_bfs(V mainRoot) {
        Vertex* start = findVertex(mainRoot);
        if (!start){
            return;
        }
        vector<Vertex*> queueExample;
        queueExample.push_back(start);
        start->visited = true;
        int curPos = 0;
        while (curPos < queueExample.size()) {
            Vertex* current = queueExample[curPos];
            curPos++;
            for (Vertex* neighbor : current->adjacency) {
                if (!neighbor->visited) {
                    neighbor->visited = true;
                    queueExample.push_back(neighbor);
                }
            }
        }
    }

    void makeGraph(vector<int> memory) {
        for (int i = 0; i < memory.size(); ++i) {
            addVertex(i);
        }
        for (int i = 0; i < memory.size(); ++i) {
            if (memory[i] >= 0) {
                addEdge(0, findVertex(i), findVertex(memory[i]));
            }
        }
    }
};

class Block{
public:
    int startId;
    int sizeOfBlock;
    Block(int startId, int sizeOfBlock): startId(startId),sizeOfBlock(sizeOfBlock){}
};

void findBlocks(Graph<int, int> graphGarbage,vector<Block>& blocksResults){
    for (int i = 0; i < graphGarbage.vertices.size(); ) {
        Graph<int, int>::Vertex* current = graphGarbage.findVertex(i);
        if (!current->visited) {
            int start = i;
            while (i < graphGarbage.vertices.size() && !graphGarbage.findVertex(i)->visited) {
                i++;
            }
            Block block(start, i - start);
            blocksResults.push_back(block);
        } else {
            i++;
        }
    }
}


int main() {
    int n, r;
    cin >> n >> r;
    vector<int> memory(n);
    for (int i = 0; i < n; ++i) {
        cin >> memory[i];
    }
    vector<int> roots(r);
    for (int i = 0; i < r; ++i) {
        cin >> roots[i];
    }

    Graph<int, int> graphGarbage;
    graphGarbage.makeGraph(memory);

    for (int root : roots) {
        Graph<int, int>::Vertex* rootVertex = graphGarbage.findVertex(root);
        if (rootVertex && !rootVertex->visited) {
            graphGarbage.KarimKhabibrakhmanov_bfs(root);
        }
    }

    vector<Block> blocksResults;

    findBlocks(graphGarbage,blocksResults);

    cout << blocksResults.size() << "\n";

    for (Block block : blocksResults) {
        cout<<block.startId<<" "<< block.sizeOfBlock<< "\n";
    }
}