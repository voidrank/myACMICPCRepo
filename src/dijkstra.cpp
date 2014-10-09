#include<cstdio>
#include<algorithm>
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
#define pb push_back
int n, m, dist[10000];
struct node
{
	int to, l;
	node() {}
	node(int _1, int _2) : to(_1), l(_2) {}
	bool operator < (const node &a) const {return a.l < l;}
};
vector <node> G[5000];
priority_queue <node> q;
void dijkstra(int st)
{
	int i, j;
	memset(dist, 0x3f, sizeof(dist)); dist[st] = 0; 
	q.push(node(st, 0));
	while(!q.empty())
	{
		int u = q.top().to, l = q.top().l; q.pop();	
		if(dist[u] != l) continue;
		for(i = 0; i < G[u].size(); i++)
			if(G[u][i].l + l < dist[G[u][i].to])
			{
				dist[G[u][i].to] = G[u][i].l + l;
				q.push(node(G[u][i].to, dist[G[u][i].to]));
			}
	}
}
int main()
{
	int i;
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(i = 1; i <= m; i++)
	{
		int x, y; node p;
		scanf("%d%d%d", &x, &y, &p.l);
		p.to = y; G[x].pb(p);
	}
	dijkstra(1);
	for(i = 1; i <= n; i++) cout<<dist[i]<<" ";
return 0;
}
