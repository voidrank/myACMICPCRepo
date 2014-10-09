#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn = 200010;
int n, tot;
int root[maxn];
struct node{
	int data, id, a;
} c[maxn];
bool cmp1(node a1, node a2) {return a1.data < a2.data;}
bool cmp2(node a1, node a2) {return a1.id < a2.id;}
struct chairtree
{
	struct node {int data, ls, rs;} a[maxn*60];
	int used;
	void build(int l, int r, int rt)
	{
		if(l == r) 
		{	
			if(c[1].a == l) a[rt].data = 1; else a[rt].data = 0;
			a[rt].ls = a[rt].rs = 0;
			return;
		}
		int m = (l+r) >> 1;
		a[rt].ls = ++used; a[rt].rs = ++used;
		build(l, m, a[rt].ls); build(m+1, r, a[rt].rs);
		a[rt].data = a[a[rt].ls].data + a[a[rt].rs].data;
	}
	void add(int p, int last, int l, int r, int rt)
	{
		if(l == r)
		{
			a[rt].data = a[last].data+1;
			a[rt].ls = a[rt].rs = 0;
			return;
		}
		int m = (l+r) >> 1;
		a[rt].ls = a[last].ls; a[rt].rs = a[last].rs;
		if(c[p].a <= m) {a[rt].ls = ++used; a[a[rt].ls] = a[a[last].ls]; add(p, a[last].ls, l, m, a[rt].ls);}
		else {a[rt].rs = ++used; a[a[rt].rs] = a[a[last].rs]; add(p, a[last].rs, m+1, r, a[rt].rs);}
		a[rt].data = a[a[rt].ls].data + a[a[rt].rs].data;
	}
	int query(int k, int l, int r, int rt1, int rt2)
	{
		if(l == r) return a[rt2].data-a[rt1].data;
		int m = (l+r) >> 1;
		if(k <= a[a[rt2].ls].data - a[a[rt1].ls].data) return query(k, l, m, a[rt1].ls, a[rt2].ls);
		else return query(k-a[a[rt2].ls].data+a[a[rt1].ls].data, m+1, r, a[rt1].rs, a[rt2].rs);
	}
/*	int query(int k, int l, int r, int rt1, int rt2)
	{
		if(l == r) return a[rt2].data-a[rt1].data;
		int m = (l+r) >> 1;
		if(k <= m) return query(k, l, m, a[rt1].ls, a[rt2].ls);
		else return query(k, m+1, r, a[rt1].rs, a[rt2].rs);
	}*/
	void make()
	{
		used = 0;
		for(int i = 1; i <= n*60; i++) a[i].data = a[i].ls = a[i].rs = 0;
		root[1] = ++used; build(1, tot, 1);
		root[0] = a[0].ls = a[0].rs = a[0].data = 0;
		for(int i = 2; i <= n; i++) root[i] = ++used, add(i, root[i-1], 1, tot, root[i]);
	}
} tree;
int dfs(int l, int r)
{
	int i, j;
	if(l == r) return 1;
	if(r-l == 1) if(c[l].a == c[r].a) return 0; else return 1;
	for(i = l, j = r; i <= j; ++i, --j)
	{
		if(tree.query(c[i].a, 1, tot, root[l-1], root[r]) == 1) 
		{
			bool f = 1;
			if(l <= i-1) f &= dfs(l, i-1);
			if(r >= i+1) f &= dfs(i+1, r);
			return f;
		}
		if(i < j && tree.query(c[j].a, 1, tot, root[l-1], root[r]) == 1)
		{
			bool f = 1;
			if(l <= j-1) f &= dfs(l, j-1);
			if(r >= j+1) f &= dfs(j+1, r);
			return f;
		}
	}
	return 0;
} 
int main()
{
	int i, T;
	freopen("t.in", "r", stdin);
	cin>>T;
	while(T--)
	{
		scanf("%d", &n);
		for(i = 1; i <= n; i++) {scanf("%d", &c[i].data); c[i].id = i;}
		sort(c+1, c+1+n, cmp1);
		tot = 1; c[1].a = 1;
		for(i = 2; i <= n; i++) if(c[i].data != c[i-1].data) c[i].a = ++tot; else c[i].a = tot;
		sort(c+1, c+1+n, cmp2);
		tree.make();
		if(!dfs(1, n)) cout<<"boring\n"; else cout<<"non-boring\n";
	}
return 0;
}
