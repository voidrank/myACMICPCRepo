#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define LS rt<<1
#define RS rt<<1|1
const int maxn = 80010;
int n, m, tot = 0;
int data[maxn], w[maxn], son[maxn], top[maxn], size[maxn], fa[maxn], deep[maxn], pos[maxn];
bool f;
vector <int> G[maxn];
struct node
{
	int key, size; node *s[2], *p;
	node() {}
	node(int k) {key = k; size = 0; p = s[1] = s[0] = 0;}
	bool getlr() {return p->s[1] == this;}
	void updata() {size = (s[0] ? s[0]->size : 0) + (s[1] ? s[1]->size : 0) + 1;}
	node *link(int w, node *t) {s[w] = t; if(t) t->p = this; return this;}
} ;
struct Splay
{
	node *root;
	void rot(node *p)
	{
		node *q = p->p->p;
		p->getlr() ? p->link(0, p->p->link(1, p->s[0])) : p->link(1, p->p->link(0, p->s[1]));
		p->p->updata();
		if(q) q->link(p->p == q->s[1], p); else{root = p; p->p = 0;}
	}
	void splay(node *p)
	{
		while(p->p && p->p->p) p->getlr() == p->p->getlr() ? (rot(p->p), rot(p)) : (rot(p), rot(p));
		if(p->p) rot(p);
		p->updata();
	}
	void insert(int k)
	{
		if(!root) {root = new node(k); root->updata(); return;}
		node *p = root, *q;
		while(p)
		{
			q = p;
			if(k < p->key) p = p->s[0]; else p = p->s[1];
		}
		p = new node(k); p->updata(); q->link(k >= q->key, p);
		splay(p);
	}
	void find(int x)
	{
		node *p = root;
		while(p->key != x) p = p->s[p->key < x];
		splay(p);
	}
	void del(int x)
	{
		find(x);
		node *l = root->s[0], *r = root->s[1], *p;
		delete(root);
		if(!l && !r) {root = 0; return;}
		if(!l) {root = r; root->p = 0; return;}
		if(!r) {root = l; root->p = 0; return;}
		root = r; root->p = 0;
		while(r) p = r, r = r->s[0];
		r = l; p->link(0, l);
		while(p != root) {p->updata(); p = p->p;}
		root->updata();
	}
	int count(int t, int w)
	{
		if(!root) return 0;
		node *p = root; int num = 0;
		while(p)
		{
			if(p->key >= w+t) num += (p->s[1] ? p->s[1]->size : 0) + 1, p = p->s[0];
			else p = p->s[1];
		}
		return num;
	}
} a[80010<<2];
int query(int b, int L, int R, int w, int l, int r, int rt)
{
	if(L <= l && r <= R) return a[rt].count(b, w);
	int m = (l+r) >> 1, num = 0;
	if(L <= m) num += query(b, L, R, w, lson); if(R > m) num += query(b, L, R, w, rson);
	return num;
}
int updata(int p, int c, int l, int r, int rt)
{
	if(l == r) {int x = a[rt].root->key; a[rt].root->key = c; return x;}	
	int m = (l+r) >> 1, x;
	if(p <= m) x = updata(p, c, lson); else x = updata(p, c, rson);
	a[rt].del(x); a[rt].insert(c);
	return x;
}
void ins(node *p, int rt)
{
	if(p) a[rt].insert(p->key);
	if(p->s[0]) ins(p->s[0], rt); if(p->s[1]) ins(p->s[1], rt);
}
void build(int l, int r, int rt)
{
	if(l == r) {a[rt].insert(data[pos[l]]); return;}
	int m = (l+r) >> 1;
	build(lson); build(rson);
	ins(a[LS].root, rt); ins(a[RS].root, rt);
}
void build2(int u, int tp)
{
	w[u] = ++tot; pos[tot] = u; top[u] = tp;
	if(son[u]) build2(son[u], tp);
	for(int i = 0; i < G[u].size(); i++) if(G[u][i] != fa[u] && G[u][i] != son[u]) build2(G[u][i], G[u][i]);
}
void dfs(int u)
{
	size[u] = 1; son[u] = 0;
	for(int i = 0; i < G[u].size(); i++) if(G[u][i] != fa[u])
	{
		int v = G[u][i];
		deep[v] = deep[u]+1; fa[v] = u;
		dfs(v);
		size[u] += size[v];
		if(size[v] > size[son[u]]) son[u] = v;
	}
}
int find(int b, int u, int v, int m)
{
	int f1 = top[u], f2 = top[v], t = 0;
	while(f1 != f2)
	{
		if(deep[f1] < deep[f2]) swap(f1, f2), swap(u, v);
		t += query(b, w[f1], w[u], m, 1, n, 1);
		u = fa[f1]; f1 = top[u];
	}
	if(deep[u] < deep[v]) swap(u, v);
	return t + query(b, w[v], w[u], m, 1, n, 1);
}
int main()
{
	int i;
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	size[0] = 0;
	for(i = 1; i <= n; i++) scanf("%d", &data[i]);
	for(i = 1; i < n; i++) 
	{
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v); G[v].push_back(u);
	}
	dfs(1); build2(1, 1);
	build(1, n, 1);
	for(i = 1; i <= m; i++)
	{
		int k, a, b; scanf("%d%d%d", &k, &a, &b);
		if(k == 0) updata(w[a], b, 1, n, 1);
		else 
		{
			int l = 0, r = 1e9;
			while(l<r-1)
			{
				int m = (l+r) >> 1; // x1 >    x2 >=
				int x1 = find(1, a, b, m), x2 = find(0, a, b, m);
				if(x2 < k) r = m; else l = m;
			}
			int x1 = find(1, a, b, r), x2 = find(0, a, b, r);
			if(x1 < k && x2 >= k) {printf("%d\n", r); continue;} 
			x1 = find(1, a, b, l), x2 = find(0, a, b, l);
			if(x1 < k && x2 >= k) {printf("%d\n", l); continue;} 
			printf("invalid request!\n");
		}
	}
return 0;
}
