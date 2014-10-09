#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<iostream>
#define pb push_back
using namespace std;
int n, m;
int vis[100010], mark[100010];
vector <int> G[10010];
int dfs(int v)
{
	for(int i = 0; i < G[v].size(); i++) if(!vis[G[v][i]])
	{
		vis[G[v][i]] = 1;
		if(mark[G[v][i]] == -1 || dfs(mark[G[v][i]]))
		{
			mark[G[v][i]] = v; 
			mark[v] = G[v][i];
			return 1;
		}
	}
	return 0;
}
int main()
{
	int i, ans = 0;
	freopen("bzoj1191.in", "r", stdin);
	cin>>n>>m;
	memset(mark, -1, sizeof(mark));
	for(i = 0; i < m; i++) 
	{
		int x, y; cin>>x>>y;
		G[i].pb(x + m); G[i].pb(y + m);
	}
	for(i = 0; i < m; i++)
	{
		memset(vis, 0, sizeof(vis)); 
		if(!dfs(i)) break;
	}
	cout<<i;
return 0;    
}