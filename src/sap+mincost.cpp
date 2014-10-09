#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
const int maxn = 1010, maxm = 40010;
const int inf = 1e9;
int n, m, tot = 0, K, S, T, maxflow;
int list[maxn];
struct node{
	int from, to, flow, cost, next;
	node() {}
	node(int _1, int _2, int _3, int _4, int _5) : from(_1), to(_2), flow(_3), cost(_4), next(_5) {}
} e[maxm], a[maxm];
inline void add(int u, int v, int flow, int cost)
{
	e[tot] = node(u, v, flow, cost, list[u]); list[u] = tot++; 
	e[tot] = node(v, u, 0, -cost, list[v]); list[v] = tot++;
}
struct SAP
{
	int gap[maxn], d[maxn];
	int dfs(int i, int s)
	{
		int j, s1 = 0, x;
		if(i == T) return s;
		for(j = list[i]; j != -1; j = e[j].next) if(d[i] == d[e[j].to] + 1)
		{
			x = dfs(e[j].to, min(s-s1, e[j].flow));
			e[j].flow -= x; e[j^1].flow += x;
			s1 += x;
			if(s1 == s) return s;
		}
		if(d[S] >= T) return s1;
		if(!--gap[d[i]]) d[S] = T;
		++gap[++d[i]];
		return s1;
	}
	int work()
	{
		memset(gap, 0, sizeof(gap)); memset(d, 0, sizeof(d));
		gap[0] = T;
		maxflow = 0;
		while(d[S] < T) maxflow += dfs(S, inf);
		return maxflow;
	}
} sap;
#define x from
#define y to
#define dis dist
struct COST
{
	int dist[maxn], pre[maxn];
	bool vis[maxn];
	queue <int> q;
	bool spfa() 
	{ 
		while(!q.empty()) q.pop(); 
		memset(dis, 0x4f, sizeof(dis)); memset(vis, 0, sizeof(vis));  
		int maxt = dis[S]; pre[S] = -1; dis[S] = 0; vis[S] = 1; q.push(S); 
		while(!q.empty()) 
		{ 
			int v = q.front(); q.pop(); vis[v] = 0; 
			for(int k = list[v]; k != -1; k = e[k].next) if(dis[v] + e[k].cost < dis[e[k].y] && e[k].flow) 
			{ 
				dis[e[k].y] = dis[v] + e[k].cost; pre[e[k].y] = k; 
				if(!vis[e[k].y]) {vis[e[k].y] = 1; q.push(e[k].y); } 
			} 
		}
		return dis[T] < maxt; 
	}
	int updata()
	{
		int Min = K, k, ans = 0;
		for(k = pre[T]; k != -1; k = pre[e[k].x]) Min = min(Min, e[k].flow);
		for(k = pre[T]; k != -1; k = pre[e[k].x]) 
		{
			e[k].flow -= Min; e[k^1].flow += Min; 
			ans += e[k].cost;
		} 
		return dist[T] * Min;
	}
	int work()
	{
		int i, ans = 0, TT = tot;
		for(i = 1; i <= m; i++) add(a[i].from, a[i].to, K, a[i].cost);
		S = n+1; add(S, 1, K, 0);
		while(spfa()) ans += updata();
		return ans;
	}
} cost;
#undef from
#undef to
#undef dis
int main()
{
	int i;
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &K);
	S = 1; T = n;
	memset(list, -1, sizeof(list));
	for(i = 1; i <= m; i++)
	{
		int u, v, f, c; scanf("%d%d%d%d", &u, &v, &f, &c);
		add(u, v, f, 0);
		a[i] = node(u, v, f, c, 0);
	}
	cout<<sap.work()<<" "; cout<<cost.work();
return 0;
}
