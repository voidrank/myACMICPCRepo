#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn = 100010;
int n, m;
int f[maxn];
inline int gf(int x) {return f[x] == x ? f[x] : f[x] = gf(f[x]);}
struct node{
	int data, dist;
	node *l, *r;
	node() {}
	node(int _1) : data(_1) {l = r = NULL; dist = 0;}
	int ldist() {return l ? l->dist : 0;}
	int rdist() {return r ? r->dist : 0;}
} ;
node *merge(node *a, node *b)
{
	if(!a) return b; if(!b) return a;
	if(a->data < b->data) swap(a, b);
	a->r = merge(a->r, b);
	if(a->rdist() > a->ldist()) swap(a->l, a->r);
	a->dist = a->rdist() + 1;
	return a;
}
struct left_tree
{
	node *root;
	void insert(int k)
	{
		if(!root) {root = new node(k); return;}
		node *p = new node(k); 
		root = merge(root, p);
	}
	void pop()
	{
		node *p = merge(root->l, root->r);
		delete(root);
		root = p;
	}
	int top() {return root->data;}
	void clear(node *p)
	{
		if(p->l) clear(p->l); if(p->r) clear(p->r);
		delete(p);
	}
} q[maxn];
int main()
{
	int i;
	freopen("t.in", "r", stdin);
	while(~scanf("%d", &n))
	{
		for(i = 1; i <= n; i++) q[i].root = 0;
		for(i = 1; i <= n; i++) 
		{
			int x; scanf("%d", &x);
			q[i].insert(x);
		}
		scanf("%d", &m);
		for(i = 1; i <= n; i++) f[i] = i;
		for(i = 1; i <= m; i++)
		{
			int x, y; scanf("%d%d", &x, &y);
			int x1 = gf(x), y1 = gf(y);
			if(x1 == y1) printf("-1\n");
			else
			{
				int u = q[x1].top(), v = q[y1].top();
				q[x1].pop(); q[y1].pop();
				q[x1].insert(u/2); q[y1].insert(v/2);
				q[x1].root = merge(q[x1].root, q[y1].root);
				f[y1] = x1;
				printf("%d\n", q[x1].root->data);
			}
		}
	}
	while(~scanf("%d", &n))
	{
		for(i = 1; i <= n; i++) q[i].root = 0;
		for(i = 1; i <= n; i++)
		{
			
		}
	}
return 0;
}
