#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxs = 2100000;
int n, pos, str[maxs];
struct splay_tree
{
	struct node
	{
		int size, data;
		node *left, *right, *father;
		int lsize() {return left ? left->size : 0;}
		int rsize() {return right ? right->size : 0;}
	};
	node *root, SS[maxs];
	int used;
	node *newnode(int data, node *p)
	{
		SS[used].left = SS[used].right = NULL;
		SS[used].father = p;
		SS[used].size = 1;
		SS[used].data = data;
		used++;
		return SS + used - 1;
	}
	void init() {used = 0; root = newnode('#', NULL);}
	void updata(node *x) {x->size = x->lsize() + x->rsize() + 1;}
	void right(node *x)
	{
		node *y = x->father;
		y->left = x->right;
		if(x->right) x->right->father = y;
		x->father = y->father;
		if(y->father) (y->father->left == y) ? y->father->left = x : y->father->right = x;
		y->father = x; x->right = y;
		updata(y); updata(x);
	}
	void left(node *x)
	{
		node *y = x->father;
		y->right = x->left;
		if(x->left) x->left->father = y;
		x->father = y->father;
		if(y->father) (y->father->left == y) ? y->father->left = x : y->father->right = x;
		y->father = x; x->left = y;
		updata(y); updata(x);
	}
	void splay(node *x, node *p)
	{
		while(x->father != p)
		{
			if(x->father->father == p) (x->father->left == x) ? right(x) : left(x);
			else if(x->father->father->left == x->father)
				(x->father->left == x) ? (right(x->father), right(x)) : (left(x), right(x));
			else 
				(x->father->right == x) ? (left(x->father), left(x)) : (right(x), left(x));
		}
		if(p == NULL) root = x;
	}
	void select(int k, node *p)
	{
		node *x = root;
		for(int l; k != (l = x->lsize()) + 1; )
		{
			if(k <= l) x = x->left;
			else k -= l + 1, x = x->right;
		}
		splay(x, p);
	}
	void insert(int *Str, int len)
	{
		node *x = newnode(Str[1], NULL), *y, *r;
		r = x;
		for(int i = 2; i <= len; i++)
		{
			x->right = newnode(Str[i], x);
			x = x->right;
		}
		if(root->right)
		{
			select(root->lsize() + 2, root);
			y = root->right;
			y->left = r;
		}
		else y = root, y->right = r;
		r->father = y;
		for(; x; x = x->father) updata(x);
	}
	void del(int len)
	{
		if(root->lsize() + 2 + len <= root->size)
		{
			select(root->lsize() + 2 + len, root);
			root->right->left = NULL;
			updata(root->right);
		}
		else root->right = NULL;
		updata(root);
	}
	void get(int len)
	{
		node *x = root;
		int k = x->lsize() + 1;
		for(int i = 1; i <= len; i++)
		{
			select(k + i, root);
			putchar(root->right->data);
		}
		putchar('\n');
	}
}splay;
int main()
{
	int i, c;
	freopen("editor.in", "r", stdin);
	scanf("%d", &n);
	splay.init();
	for(i = 1; i <= n; i++)
	{
		char s[10]; int t;
		while((c=getchar())==10 || c==13);ungetc(c,stdin);
		for(t=0; (c=getchar())!=' ' && c!=10 && c!=13; ) s[++t]=c;
		switch(s[1])
		{
			case 'M' : scanf("%d", &t); splay.select(t + 1, 0); pos = t + 1; break;
			case 'I' : 
				scanf("%d", &t);
				for(int l = 0; l < t; )
				{
					while((c = getchar()) == 10 || c == 13);
					str[++l] = c;
				}
				splay.insert(str, t);
				break;
			case 'D' : scanf("%d", &t); splay.del(t); break;
			case 'G' : scanf("%d", &t); splay.get(t); break;
			case 'P' : splay.select(--pos, 0); break;
			case 'N' : splay.select(++pos, 0); break;
		}
	}
return 0;
}
