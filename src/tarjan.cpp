#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<iostream>
#include<stack>
using namespace std;
int n, id[20000], scc = 0, idx = 0, dfn[20000], low[20000], out[20000], num[20000];
bool flag[20000];
vector <int> G[20000];
stack <int> s;

void Tarjan(int x1)
{
	int i;
	dfn[x1] = low[x1] = ++idx;
	s.push(x1); flag[x1] = true;
	for(i = 0; i < G[x1].size(); i++)
	{
		int x = G[x1][i];
		if(dfn[x] == 0) Tarjan(x);
		if(flag[x]) low[x1] = min(low[x], low[x1]);
	}
	if(low[x1] == dfn[x1])
	{
		int p; ++scc;
		do
		{
			p = s.top(); s.pop();
			flag[p] = false;
			id[p] = scc;
		}while(p != x1);
	}
}
int main()
{
	int i, t = 0, ans = 0, m, j;
	freopen("bzoj1051.in", "r", stdin);
	scanf("%d%d", &n, &m);
	memset(dfn, 0, sizeof(dfn));memset(low, 0, sizeof(low)); memset(id, 0, sizeof(id)); 
	memset(flag, false, sizeof(flag)); memset(out, 0, sizeof(out)); memset(num, 0, sizeof(num));
	for(i = 1; i <= m; i++)	
	{
		int x, y; scanf("%d%d", &x, &y);
		G[x].push_back(y);
	}
	for(i = 1; i <= n; i++) if(!dfn[i]) Tarjan(i);
	
	for(i = 1; i <= n; i++)
	{
		++num[id[i]];
		for(j = 0; j < G[i].size(); j++) if(id[G[i][j]] != id[i]) ++out[id[i]];
	}
	for(i = 1; i <= scc; i++) if(!out[i]) ++t, ans += num[i];
	if(t == 1) cout<<ans; else cout<<"0";


return 0;
}
