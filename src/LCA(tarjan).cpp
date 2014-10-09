#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
int n, K, used = 0, Time = 0;
int f[200010], last[200010], ll[200010], dfn[200010], ST[200010];
vector <int> G[200010];
struct node{int a, dis, id;} root[200010];
inline bool cmp(node a1, node a2) {return a1.a < a2.a;}
inline bool cmp3(node a1, node a2) {return a1.id < a2.id;}
struct node2
{
	int u, v, a, ans;
	node2(){}
	node2(int _u, int _v, int _a) : u(_u), v(_v), a(_a){}
} q[200010];
inline bool cmp2(node2 a1, node2 a2){return a1.u < a2.u;}
inline void dfs(int u, int l)
{
	root[u].dis = l; dfn[u] = ++Time;
	for(int i = 0; i < G[u].size(); i++) dfs(G[u][i], l + 1);
}
inline int gf(int x){return (x == f[x] ? f[x] : (f[x] = gf(f[x])));}
inline void LCA(int u)
{
	f[u] = u;
	for(int i = ST[u]; q[i].u == u; i++) q[i].ans = gf(q[i].v);
	for(int i = 0; i < G[u].size(); i++)
	{
		LCA(G[u][i]);
		f[G[u][i]] = u;
	}
}
int main()
{
	int i;
	freopen("bzoj1776.in", "r", stdin);
	cin>>n>>K; int ROOT;
	memset(ll, 0, sizeof(ll));
	for(i = 1; i <= n; i++)
	{
		int x; cin>>root[i].a>>x; root[i].id = i;
		if(x) G[x].push_back(i); else ROOT = i;
	}
	dfs(ROOT, 0);
	for(i = 1; i <= n; i++) if(root[i].dis > ll[root[i].a]) ll[root[i].a] = root[i].dis, last[root[i].a] = i;
	sort(root + 1, root + 1 + n, cmp);
	int j = 1;
	for(i = 1; i <= K; i++)
		for(;root[j].a == i; ++j)
		{
			if(root[j].id == last[i]) continue;
			if(dfn[last[i]] > dfn[root[j].id]) q[++used] = node2(last[i], root[j].id, i); 
			else q[++used] = node2(root[j].id, last[i], i); 
		}
	sort(root + 1, root + 1 + n, cmp3);
	sort(q + 1, q + used + 1, cmp2);
	for(i = used; i >= 1; i--) ST[q[i].u] = i;
	LCA(ROOT);
	int ans[200010]; memset(ans, 0, sizeof(ans));
	for(i = 1; i <= used; i++)
		ans[q[i].a] = max(ans[q[i].a], root[q[i].u].dis + root[q[i].v].dis - 2 * root[q[i].ans].dis);
	for(i = 1; i <= K; i++) cout<<ans[i]<<endl;	
return 0;
}
