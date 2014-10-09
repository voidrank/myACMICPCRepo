#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<ctime>
using namespace std;
typedef long long LL;
const int maxn = 100010;
int n, tot = 0, N = 0;
int list[maxn], f[maxn], col[maxn];
struct rec{
	int l, r, id; LL ans;
	rec() {}
	rec(int _1, int _2, LL _3) : l(_1), r(_2), ans(_3) {}
} q[maxn], a[maxn*200];
inline bool cmp1(const rec &a1, const rec &a2) {return a1.l == a2.l ? a1.r > a2.r : a1.l < a2.l;}
inline bool cmp2(const rec &a1, const rec &a2) {return a1.r == a2.r ? a1.l > a2.l : a1.r < a2.r;}
inline bool cmp3(const rec &a1, const rec &a2) {return a1.id < a2.id;}
inline bool cmp(const rec &a1, const rec &a2) {return a1.ans < a2.ans;}
struct node{
	int u, v, next, l;
	node() {}
	node(int _1, int _2, LL _3, int _4) : u(_1), v(_2), l(_3), next(_4) {}
} e[maxn*10];
inline void add1(const int &u, const int &v, const LL &l) {a[++N] = rec(u, v, l);}
inline void add(const int &u, const int &v, const LL &l) 
{
	e[tot] = node(u, v, l, list[u]); list[u] = tot++;
	e[tot] = node(v, u, l, list[v]); list[v] = tot++;
}
inline LL dis(const rec &a1, const rec &a2) {return abs(a1.l-a2.l) + abs(a1.r-a2.r);}
inline int gf(int x) {return x == f[x] ? x : f[x] = gf(f[x]);}
LL tmp = 0;
int num[maxn];
inline LL mult(LL x) {return LL(x*(x-1));}
inline void Add(const int &l, const int &r) 
{	for(int i = l; i <= r; i++) tmp -= mult(num[col[i]]), tmp += mult(++num[col[i]]);}
inline void del(const int &l, const int &r) 
{	for(int i = l; i <= r; i++) tmp -= mult(num[col[i]]), tmp += mult(--num[col[i]]);}
void dfs(const int &x, const int &l, const int &r)
{
	if(q[x].ans != -1) return;
	if(q[x].r < l || q[x].l > r)
	{
		del(l, r); Add(q[x].l, q[x].r);
		q[x].ans = tmp;
		for(int i = list[x]; i != -1; i = e[i].next) dfs(e[i].v, q[x].l, q[x].r);
		del(q[x].l, q[x].r); Add(l, r);
		return;
	}
	if(l < q[x].l) del(l, q[x].l-1); if(l > q[x].l) Add(q[x].l, l-1);
	if(r < q[x].r) Add(r+1, q[x].r); if(r > q[x].r) del(q[x].r+1, r);
	q[x].ans = tmp;
	for(int i = list[x]; i != -1; i = e[i].next) dfs(e[i].v, q[x].l, q[x].r);
	if(l < q[x].l) Add(l, q[x].l-1); if(l > q[x].l) del(q[x].l, l-1);
	if(r < q[x].r) del(r+1, q[x].r); if(r > q[x].r) Add(q[x].r+1, r);
}
inline LL gcd(const LL &a, const LL &b) {return b == 0 ? a : gcd(b, a%b);}
inline LL getrand(int l, int r) {return rand()%(r-l)+1+l;}
int main()
{
	int i, m;
	freopen("t.in", "r", stdin);
//	freopen("t.out", "w", stdout);
	scanf("%d%d", &n, &m);
	memset(list, -1, sizeof(list)); memset(num, 0, sizeof(num));
	for(i = 1; i <= n; i++) scanf("%d", &col[i]);
	for(i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i, q[i].ans = -1;
	srand(n*2+m*3+5);
	int t = sqrt(m) / log2(m);
	sort(q+1, q+1+m, cmp1);
	for(i = 1; i < m; i++) {if(q[i].id != q[i+1].id) add1(q[i].id,q[i+1].id,dis(q[i],q[i+1]));}
	for(i = 1; i <= m; i++) for(int j = 1; j <= t; j++)
	{
		int l = max(i-50, 1), r = min(i+50, m);
		LL p = getrand(l, r);
		if(q[i].id != q[p].id) add1(q[i].id, q[p].id, dis(q[i], q[p]));
	}
	sort(q+1, q+1+m, cmp2);
	for(i = 1; i < m; i++) {if(q[i].id != q[i+1].id) add1(q[i].id,q[i+1].id,dis(q[i],q[i+1]));}
	for(i = 1; i <= m; i++) for(int j = 1; j <= t; j++)
	{
		int l = max(i-50, 1), r = min(i+50, m);
		LL p = getrand(l, r);
		if(q[i].id != q[p].id) add1(q[i].id, q[p].id, dis(q[i], q[p]));
	}
	sort(q+1, q+1+m, cmp3);
	sort(a+1, a+1+N, cmp);
	for(i = 1; i <= m; i++) f[i] = i;
	int x = gf(a[1].l), y = gf(a[1].r), vis = 1;
	f[x] = y;
	add(a[1].l, a[1].r, dis(q[a[1].l], q[a[1].r])); 
	i = 2;
	while(vis < m-1)
	{
		int u = a[i].l, v = a[i].r;
		int x = gf(u), y = gf(v);
		if(x != y)
		{
			f[x]=  y;
			add(u, v, dis(q[u], q[v]));
			++vis;
		}
		++i;
	}
	tmp = 0; ++num[col[1]];
	dfs(1, 1, 1);
	for(i = 1; i <= m; i++)
	{
		if(q[i].ans == 0) {printf("0/1\n"); continue;}
		LL p = mult(q[i].r - q[i].l+1);
		LL q1 = gcd(p, q[i].ans);
		printf("%I64d/%I64d\n", q[i].ans/q1, p/q1);	
		printf("%lld/%lld\n", q[i].ans/q1, p/q1);	
	}
return 0;
}
