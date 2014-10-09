#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn = 1010;
int n, m, K, tot = 0, S, T, SS, TT;
int c[maxn], f[maxn], list[maxn], num[maxn][maxn], d[maxn], gap[maxn], list2[maxn];
bool b[maxn][maxn];
struct node{
	int v, f, next;
	node() {}
	node(int _1, int _2, int _3) : v(_1), f(_2), next(_3) {}
} e[maxn*maxn*2], e2[maxn*maxn*2];
inline void add(int u, int v, int f)
{
	e[tot] = node(v, f, list[u]); list[u] = tot++;
	e[tot] = node(u, 0, list[v]); list[v] = tot++;
}
int dfs(int u, int s)
{
	int i, s1 = 0;
	if(u == TT) return s;
	for(i = list[u]; i != -1; i = e[i].next) if(d[u] == d[e[i].v]+1)
	{
		int x = dfs(e[i].v, min(e[i].f, s-s1));
		e[i].f -= x; e[i^1].f += x;
		s1 += x;
		if(s1 == s) return s1;
	}
	if(d[SS] >= TT) return s1;
	if(!--gap[d[u]]) d[SS] = TT;
	++gap[++d[u]];
	return s1;
}
int main()
{
	int i, j, F;
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &K);
	memset(f, 0, sizeof(f)); memset(list, -1, sizeof(list)); memset(num, 0, sizeof(num));
	S = n+m+1; T = n+m+2; SS = n+m+3; TT = n+m+4;
	for(i = 1; i <= n; i++)
	{
		scanf("%d", &c[i]);
		for(j = 1; j <= c[i]; j++) 
		{
			int x; scanf("%d", &x);
			++num[i][x];
		}
	}
	scanf("%d", &F);
	cout<<F<<endl;
	for(i = 1; i <= F; i++)
	{
		int x, y; scanf("%d%d", &x, &y);
		cout<<x<<" "<<y<<endl;
		b[x][y] = 1;
	}
	for(i = 1; i <= n; i++) for(j = 1; j <= m; j++)
	{
		if(b[i][j]) --f[i], ++f[j+n], add(i, j+n, num[i][j]-1);
		else add(i, j+n, num[i][j]);
	}
	for(i = 1; i <= m; i++) 
	{
		int x; scanf("%d", &x);
		add(i+n, T, x);
	}
	for(i = 1; i <= n; i++)
	{
		int x, y; scanf("%d%d", &x, &y);
		add(S, i, x-y);
		f[S] -= y; f[i] += y;
	}
	add(T, S, 1e9);
	for(i = 1; i <= n+m; i++) if(f[i] > 0) add(SS, i, f[i]); else if(f[i] < 0) add(i, TT, -f[i]);
	int l = 0, r = K;
	int wssc = tot;
	for(i = 0; i < tot; i++) e2[i] = e[i];
	for(i = 0; i < maxn; i++) list2[i] = list[i];
	while(l<r)
	{
		int mid = (l+r+1) >> 1;
		tot = wssc;
		for(i = 0; i < tot; i++) e[i] = e2[i];
		for(i = 0; i < maxn; i++) list[i] = list2[i];
		f[S] += mid; f[T] -= mid;
		if(f[S] > 0) add(SS, S, f[S]); else if(f[S] < 0) add(S, TT, -f[S]);
		if(f[T] > 0) add(SS, T, f[T]); else if(f[T] < 0) add(T, TT, -f[T]);
		f[S] -= mid; f[T] += mid;
		memset(d, 0, sizeof(d)); memset(gap, 0, sizeof(gap));
		gap[0] = TT;
		int ans = 0;
//		cout<<mid<<" "<<ans<<endl;
		while(d[SS] < TT) ans += dfs(SS, 1e9);
		bool f = 1;
		for(i = list[SS]; i != -1; i = e[i].next) if(e[i].v != TT) if(e[i].f) {f = 0; break;}
		if(f) l = mid; else r = mid-1;
	}
	cout<<l;
return 0;
}
