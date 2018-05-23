#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

const int maxn = 150;
const int INF = numeric_limits<int>::max();

struct Edge {
	int from, to, dist;
	Edge(int from, int to, int dist) : from(from), to(to), dist(dist) {}
};

struct HeapNode {
	int d, u;
	HeapNode(int d, int u) : d(d), u(u) {}
	bool operator < (const HeapNode& hns) const {
		return d > hns.d;
	}
};

struct Dijstra {
	int d[maxn], p[maxn], n;
	bool v[maxn];
	vector<Edge> edges;
	vector<int> G[maxn];

	void Init(int n) {
		this->n = n;
		edges.clear();
		for (int i = 0; i < n; i++) G[i].clear();
		for (int i = 0; i < n; i++) d[i] = INF;
		memset(v, false, sizeof(v));
	}

	void AddEdges(int from, int to, int dist) {
		int m;
		edges.push_back(Edge(from, to, dist));   //将edges的位置哈希到G中
		m = edges.size();
		G[from].push_back(m - 1);

		edges.push_back(Edge(to, from, dist));
		m = edges.size();
		G[to].push_back(m - 1);
	}

	void dijstra(int s) {
		d[s] = 0;
		priority_queue<HeapNode> Q;
		Q.push(HeapNode(0, s));
		while (!Q.empty()) {
			HeapNode hn = Q.top(); Q.pop();
			int u = hn.u;
			if (v[u]) continue;
			v[u] = true;
			for (int i = 0; i < G[u].size(); i++) {
				Edge& e = edges[G[u][i]];
				if (d[e.to] > d[e.from] + e.dist) {
					d[e.to] = d[e.from] + e.dist;
					p[e.to] = G[u][i];
					//push()
					Q.push(HeapNode(d[e.to], e.to));
				}
			}
		}
	}

};

int main()
{
	int N, M;
	Dijstra dij;
	while (~scanf("%d%d", &N, &M) && (N || M)) {
		dij.Init(N);
		int from, to, dist;
		for (int i = 0; i < M; i++) {
			scanf("%d%d%d", &from, &to, &dist);
			dij.AddEdges(from - 1, to - 1, dist);
		}
		dij.dijstra(0);
		printf("%d\n", dij.d[N - 1]);
	}
	return 0;
}
