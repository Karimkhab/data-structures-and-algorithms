// Karim Khabibrakhmanov DSAI - 05
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

template<typename T, typename U>
class DuffStall {
public:
    T name;
    int tax;
    DuffStall(const T& n, int t) : name(n), tax(t) {}
};

template<typename U>
class DuffConnection {
public:
    int from, to;
    U cost;

    DuffConnection(int f, int t, U c) : from(f), to(t), cost(c) {}

    bool operator>(const DuffConnection<U>& other) const {
        return cost > other.cost;
    }
};

template<typename T, typename U>
class DuffGraph {
private:
    vector<DuffStall<T, U>> stalls;
    vector<vector<DuffConnection<U>>> adjList;

    int getIndexByName(const T& name) const {
        for (int i = 0; i < stalls.size(); ++i) {
            if (stalls[i].name == name) return i;
        }
        return -1;
    }

public:
    void addStall(const T& name, int tax) {
        stalls.emplace_back(name, tax);
        adjList.emplace_back();
    }

    void connectStalls(const T& name1, const T& name2, U distance) {
        int idx1 = getIndexByName(name1);
        int idx2 = getIndexByName(name2);
        U cost = distance / (stalls[idx1].tax + stalls[idx2].tax);
        adjList[idx1].emplace_back(idx1, idx2, cost);
        adjList[idx2].emplace_back(idx2, idx1, cost);
    }

    vector<pair<T, T>> KarimKhabibrakhmanov_mst_prim() {
        vector<pair<T, T>> mstEdges;
        int n = stalls.size();
        if (n == 0) return mstEdges;

        vector<bool> inMST(n, false);
        vector<U> minCost(n, numeric_limits<U>::max());
        priority_queue<DuffConnection<U>, vector<DuffConnection<U>>, greater<DuffConnection<U>>> pq;

        for (int start = 0; start < n; ++start) {
            if (!inMST[start]) {
                minCost[start] = 0;
                pq.emplace(-1, start, 0);

                while (!pq.empty()) {
                    DuffConnection<U> current = pq.top();
                    pq.pop();

                    int u = current.to;
                    if (inMST[u]) continue;

                    inMST[u] = true;
                    if (current.from != -1) {
                        mstEdges.emplace_back(stalls[current.from].name, stalls[u].name);
                    }

                    for (const auto& conn : adjList[u]) {
                        int v = conn.to;
                        if (!inMST[v] && conn.cost < minCost[v]) {
                            minCost[v] = conn.cost;
                            pq.emplace(u, v, conn.cost);
                        }
                    }
                }
            }
        }

        return mstEdges;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    DuffGraph<string, double> graph;
    int commandCount;
    cin >> commandCount;

    while (commandCount--) {
        string command;
        cin >> command;

        if (command == "ADD") {
            string name;
            int tax;
            cin >> name >> tax;
            graph.addStall(name, tax);
        } else if (command == "CONNECT") {
            string name1, name2;
            double distance;
            cin >> name1 >> name2 >> distance;
            graph.connectStalls(name1, name2, distance);
        } else if (command == "PRINT_MIN") {
            auto mst = graph.KarimKhabibrakhmanov_mst_prim();
            for (size_t i = 0; i < mst.size(); ++i) {
                if (i > 0) cout << " ";
                cout << mst[i].first << ":" << mst[i].second;
            }
            cout << '\n';
        }
    }
}