#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define LS rt << 1
#define RS rt << 1 | 1
struct Tree
{
	const int maxn = 2222;
	int cnt[maxn << 2], m;
	double sum[maxn << 2], X[maxn << 2];
	Tree() {m = 0; memset(sum, 0, sizeof(sum)); memset(cnt, 0, sizeof(cnt));}
	struct node
	{
		double l, r, h; int s;
		node() {}
		node(double _l, double _r, double _h, int _s) : l(_l), r(_r), h(_h), s(_s) {}
		bool operator < (const node &a) const {return h < a.h;}
	} a[maxn];
	void pushup(int rt, int l, int r)
	{
		if(cnt[rt]) sum[rt] = X[r + 1] - X[l];
		else if(l == r) sum[rt] = 0;
		else sum[rt] = sum[LS] + sum[RS];
	}
	void updata(int L, int R, int c, int l, int r, int rt)
	{
		if(L <= l && r <= R)
		{
			cnt[rt] += c;
			pushup(rt, l, r);
			return;
		}
		int m = (l + r) >> 1;
		if(L <= m) updata(L, R, c, lson); if(R > m) updata(L, R, c, rson);
		pushup(rt, l, r);
	}
	int Bin(double key, int n, double X[])
	{
		int l = 0, r = n - 1;
		while(l <= r)
		{
			int m = (l + r) >> 1;
			if(X[m] == key) return m;
			if(X[m] < key) l = m + 1; else r = m - 1;
		}
		return -1;
	}
	void insert(double aa, double b, double c, double d)
	{
		X[m] = aa; a[m++] = node(aa, c, b, 1);
		X[m] = c; a[m++] = node(aa, c, d, -1);
	}
	double work()
	{
		sort(X, X + m); sort(a, a + m);
		int k = 1, i;
		for(i = 1; i < m; i++) if(X[i] != X[i - 1]) X[k++] = X[i];
		double ans = 0;
		for(i = 0; i < m - 1; i++)
		{
			int l = Bin(a[i].l, k, X), r = Bin(a[i].r, k, X) - 1;
			if(l <= r) updata(l, r, a[i].s, 0, k - 1, 1);
			ans += sum[1] * (a[i + 1].h - a[i].h);
		}
		return ans;		
	}
}tree;
int main()
{
	int i, n, cas = 1;
	while(n--)
	{
		double aa, b, c, d; scanf("%lf%lf%lf%lf", &aa, &b, &c, &d);
		tree.insert(aa, b, c, d);
	}
	cout<<tree.work();
return 0;
}
