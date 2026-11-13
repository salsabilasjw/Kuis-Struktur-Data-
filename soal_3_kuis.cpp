#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <limits>
using namespace std;

const int V = 6;
const int INF = numeric_limits<int>::max();

char vertex[V] = {'A', 'B', 'C', 'D', 'E', 'F'};

int graph[V][V] = {
    {0, 4, 2, 0, 0, 0},
    {4, 0, 1, 5, 3, 0},
    {2, 1, 0, 8, 6, 0},
    {0, 5, 8, 0, 2, 4},
    {0, 3, 6, 2, 0, 3},
    {0, 0, 0, 4, 3, 0}
};

int indeksVertex(char v) {
    if (v >= 'A' && v <= 'F') {
        return v - 'A';
    }
    return -1;
}

void BFS(int awal) {
    bool visited[V] = {false};
    queue<int> q;

    visited[awal] = true;
    q.push(awal);

    cout << "BFS: ";

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << vertex[current] << " ";

        for (int i = 0; i < V; i++) {
            if (graph[current][i] != 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    cout << "\n";
}

void DFS(int awal) {
    bool visited[V] = {false};
    stack<int> s;

    s.push(awal);

    cout << "DFS: ";

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        if (!visited[current]) {
            visited[current] = true;
            cout << vertex[current] << " ";

            for (int i = V - 1; i >= 0; i--) {
                if (graph[current][i] != 0 && !visited[i]) {
                    s.push(i);
                }
            }
        }
    }

    cout << "\n";
}

void Dijkstra(int awal, int tujuan) {
    int jarak[V];
    int sebelumnya[V];
    bool visited[V] = {false};

    for (int i = 0; i < V; i++) {
        jarak[i] = INF;
        sebelumnya[i] = -1;
    }

    jarak[awal] = 0;

    for (int i = 0; i < V; i++) {
        int current = -1;
        int jarakMinimum = INF;

        for (int j = 0; j < V; j++) {
            if (!visited[j] && jarak[j] < jarakMinimum) {
                jarakMinimum = jarak[j];
                current = j;
            }
        }

        if (current == -1) {
            break;
        }

        visited[current] = true;

        for (int j = 0; j < V; j++) {
            if (graph[current][j] != 0 && !visited[j]) {
                if (jarak[current] + graph[current][j] < jarak[j]) {
                    jarak[j] = jarak[current] + graph[current][j];
                    sebelumnya[j] = current;
                }
            }
        }
    }

    if (jarak[tujuan] == INF) {
        cout << "Tidak ada rute yang ditemukan.\n";
        return;
    }

    vector<int> rute;
    int current = tujuan;

    while (current != -1) {
        rute.push_back(current);
        current = sebelumnya[current];
    }

    cout << "Rute terpendek: ";

    for (int i = rute.size() - 1; i >= 0; i--) {
        cout << vertex[rute[i]];

        if (i > 0) {
            cout << " -> ";
        }
    }

    cout << "\nTotal jarak: " << jarak[tujuan] << "\n";
}

int main() {
    char awal, tujuan;
    int indeksAwal, indeksTujuan;

    cout << "=== SISTEM PENCARIAN RUTE KAMPUS ===\n";

    cout << "Vertex tersedia: A, B, C, D, E, F\n";

    cout << "Masukkan vertex awal: ";
    cin >> awal;

    cout << "Masukkan vertex tujuan: ";
    cin >> tujuan;

    indeksAwal = indeksVertex(awal);
    indeksTujuan = indeksVertex(tujuan);

    if (indeksAwal == -1 || indeksTujuan == -1) {
        cout << "Vertex tidak valid.\n";
        return 0;
    }

    BFS(indeksAwal);
    DFS(indeksAwal);
    Dijkstra(indeksAwal, indeksTujuan);

    return 0;
}