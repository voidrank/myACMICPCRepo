#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
const int maxn = 80010;
int n, K, root, dist[maxn];
struct Node{
	int u, w;
	Node() {}
	Node(int _1, int _2) : u(_1), w(_2) {}
} ;
vector <Node> G[maxn];
struct LCA
{
	int Time;
	int dfn[maxn*2], deep[maxn], first[maxn], maxx[maxn], pos[maxn];
	bool vis[maxn];
	struct node{
		int pos, deep;
		node() {pos = 0;}
		node(int _1, int _2) : deep(_1), pos(_2) {}
		bool operator< (const node &a) {return deep < a.deep;}
	} d[20][maxn*2];
	void dfs(int u, int D, int Dist)
	{
		vis[u] = 1;
		dfn[++Time] = u; first[u] = Time; deep[u] = D; dist[u] = Dist;
		for(int i = 0; i < G[u].size(); i++) if(!vis[G[u][i].u])
		{
			dfs(G[u][i].u, D+1, Dist+G[u][i].w);
			dfn[++Time] = u;
		}
	}
	void build()
	{
		int N = n*2-1;
		for(int i = 1; i <= N; i++) d[0][i] = node(deep[dfn[i]], dfn[i]);
		for(int i = 1; i <= log(N)/log(2); i++) for(int j = 1; j <= N+1-(1<<i); j++)
			d[i][j] = d[i-1][j] < d[i-1][j+(1<<(i-1))] ? d[i-1][j] : d[i-1][j+(1<<(i-1))];
	}
	node query(int i, int j) 
	{
		if(i > j) swap(i, j);
		int k = (int)(log(j-i+1)/log(2));
		return d[k][i] < d[k][j-(1<<k)+1] ? d[k][i] : d[k][j-(1<<k)+1];
	}
	int lca(int x, int y) {return query(first[x], first[y]).pos;}
	void work()
	{
		for(int i = 0; i < maxn; i++) G[i].clear();
		Time = 0;
		for(int i = 1; i < n; i++)
		{
			int u, v, w; char s[10];
			scanf("%d%d%d%s", &u, &v, &w, s);
			G[u].push_back(Node(v, w)); G[v].push_back(Node(u, w));
		}
		memset(vis, 0, sizeof(vis));
		dfs(1, 0, 0);
		build();
	}
} lca;
int main()
{
	int i, m;
	freopen("t.in", "r", stdin);
	while(~scanf("%d%d", &n, &K))
	{
		lca.work();
		scanf("%d", &m);
		for(i = 1; i <= m; i++)
		{
			int x, y; scanf("%d%d", &x, &y);
			printf("%d\n", dist[x] + dist[y] - dist[lca.lca(x, y)]*2);
		}
	}
return 0;
}
