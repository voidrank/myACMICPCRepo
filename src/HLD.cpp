#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
const int maxn = 20010;
int n, tot = 0;
int top[maxn], w[maxn], size[maxn], deep[maxn], son[maxn], fa[maxn], d[maxn][3], data[maxn<<1];
vector <int> G[maxn];
void updata(int p, int x, int l, int r, int rt)
{
	if(l == r) {data[rt] = x; return;}
	int m = (l+r) >> 1;
	if(p <= m) updata(p, x, lson); else updata(p, x, rson);
	data[rt] = max(data[rt<<1], data[rt<<1|1]);
}
int query(int L, int R, int l, int r, int rt)
{
	if(L <= l && r <= R) return data[rt];
	int m = (l+r) >> 1, p1 = 0, p2 = 0;
	if(L <= m) p1 = query(L, R, lson); if(R > m) p2 = query(L, R, rson);
	return max(p1, p2);
}
void dfs(int u)
{
	son[u] = 0; size[u] = 1;
	for(int i = 0; i < G[u].size(); i++) if(fa[u] != G[u][i])
	{
		int v = G[u][i];
		fa[v] = u; deep[v] = deep[u] + 1;
		dfs(v);
		size[u] += size[v];
		if(size[v] > size[son[u]]) son[u] = v;
	}
}
void build(int u, int tp)
{
	top[u] = tp; w[u] = ++tot;
	if(son[u]) build(son[u], tp);
	for(int i = 0; i < G[u].size(); i++) if(G[u][i] != fa[u] && G[u][i] != son[u]) build(G[u][i], G[u][i]);
}
int find(int u, int v)
{
	int f1 = top[u], f2 = top[v], tmp = 0;
	while(f1 != f2)
	{
		if(deep[f1] < deep[f2]) swap(f1, f2), swap(u, v);
		tmp = max(tmp, query(w[f1], w[u], 1, tot, 1));
		u = fa[f1]; f1 = top[u];
	}
	if(u == v) return tmp;
	if(deep[u] > deep[v]) swap(u, v);
	return max(tmp, query(w[son[u]], w[v], 1, tot, 1));
}
int main()
{
	int i, T;
	freopen("t.in", "r", stdin);
	scanf("%d", &T);
	size[0] = 0;
	while(T--)
	{
		for(i = 0; i < maxn; i++) G[i].clear();
		tot = deep[1] = size[1] = 0;
		scanf("%d", &n);
		for(i = 1; i < n; i++)
		{
			scanf("%d%d%d", &d[i][0], &d[i][1], &d[i][2]);
			G[d[i][0]].push_back(d[i][1]); G[d[i][1]].push_back(d[i][0]);
		}
		dfs(1); build(1, 1);
		for(i = 1; i < n; i++)
		{
			if(deep[d[i][0]] > deep[d[i][1]]) swap(d[i][0], d[i][1]);
			updata(w[d[i][1]], d[i][2], 1, tot, 1);
		}
		char s[10];
		while(1)
		{
			scanf("%s", s); if(s[0] == 'D') break;
			int x, y; scanf("%d%d", &x, &y);
			if(s[0] == 'Q') printf("%d\n", find(x, y));
			else updata(w[d[x][1]], y, 1, tot, 1);
		}
	}
return 0;
}
