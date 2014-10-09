#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int n;
char s[1000010];
struct node
{
	int len;
	node *p, *trans[27];
	node() {}
	node(int _1) : len(_1) {p = 0; memset(trans, 0, sizeof(trans));}
} *root, *now, *p, *q;
int main()
{
	int i;
	freopen("t.in", "r", stdin);
	scanf("%s", s+1); n = strlen(s+1);
	now = p = root = new node(0);
	for(i = 1; i <= n; i++)
	{
		node *NEW = new node(i);
		for(p = now; p && !p->trans[s[i]-'a']; p = p->p) p->trans[s[i]-'a'] = NEW;
		if(!p) {NEW->p = root; now = NEW; continue;}
		q = p->trans[s[i]-'a'];
		if(p->len+1 == q->len) NEW->p = q;
		else
		{
			node *r = new node(*q); r->len = p->len+1;
			for(; p && p->trans[s[i]-'a'] == q; p = p->p) p->trans[s[i]-'a'] = r;
			q->p = NEW->p = r;
		}
		now = NEW;
	}
return 0;
}
