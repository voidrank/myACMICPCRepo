#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int n, Min;
struct Splay
{
	struct node
	{
		int key, size; node *s[2], *p;
		node() {}
		node(int k) {key = k; size = 1; p = s[1] = s[0] = 0;}
		bool getlr() {return p->s[1] == this;}
		void updata() {size = (s[0] ? s[0]->size : 0) + (s[1] ? s[1]->size : 0) + 1;}
		node *link(int w, node *t) {s[w] = t; if(t) t->p = this; return this;}
	} *root;
	void rot(node *p)
	{
		node *q = p->p->p;
		p->getlr() ? p->link(0, p->p->link(1, p->s[0])) : p->link(1, p->p->link(0, p->s[1]));
		p->p->updata();
		if(q) q->link(p->p == q->s[1], p); else root = p, p->p = 0;
	}
	void splay(node *p)
	{
		while(p->p && p->p->p) p->getlr() == p->p->getlr() ? (rot(p->p), rot(p)) : (rot(p), rot(p));
		if(p->p) rot(p);
		p->updata();
	}
	void ins(int k)
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
	int get(int k)
	{
		if(!root || root->size < k) return -1;
		node *p = root;
		while(1)
		{
			int s1 = p->s[1] ? p->s[1]->size : 0;
			if(k == s1+1) {splay(p); return p->key;}
			if(k <= s1) {p = p->s[1]; continue;}
			k -= s1+1; p = p->s[0];
		}
	}
	void add(int k, node *p)
	{
		p->key += k;
		if(p->s[0]) add(k, p->s[0]); if(p->s[1]) add(k, p->s[1]);
	}
	void work()
	{
		int i, sum = 0;
		for(i = 1; i <= n; i++)
		{
			char s[10]; int k, ss; scanf("%s%d", s, &k);
			if(s[0] == 'I') {if(k >= Min) ins(k);}
			if(s[0] == 'A') add(k, root);
			if(s[0] == 'S')
			{
				add(-k, root);
				ins(Min-1);
				sum += root->s[0] ? root->s[0]->size : 0;
				if(root->s[1]) root->s[1]->p = 0; root = root->s[1];
			}
			if(s[0] == 'F') {printf("%d\n", get(k));}
		}
		printf("%d", sum);
	}
} splay;
int main()
{
	int i;
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &Min);
	splay.work();
return 0;
}
