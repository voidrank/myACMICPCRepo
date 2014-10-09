#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
int n;
struct node{int f, sum, l0, l1, r0, r1, max1, max0;} a[1000000]; //f = 0 不变   f = 1 改变    f = 2 全变成0    f = 3 全变成1
struct node2{int l, r, maxx;}; 
node change(int l, int r, int rt)
{
	node p; p.l0 = p.r0 = p.max0 = p.sum = p.l1 = p.r1 = p.max1 = 0;
	if(a[rt].f == 0) p = a[rt];
	else if(a[rt].f == 1)
	{
		p = a[rt];
		swap(p.l0, p.l1); swap(p.r0, p.r1); swap(p.max0, p.max1);
		p.sum = r - l + 1 - p.sum;
	}
	else if(a[rt].f == 2) p.l0 = p.r0 = p.max0 = r - l + 1;
	else if(a[rt].f == 3) p.l1 = p.r1 = p.max1 = p.sum = r - l + 1;
	return p;
}
void pushup(int l, int r, int rt){
	int m = (l + r) >> 1, lm = m - l + 1, rm = r - m;
	node chl = change(lson), chr = change(rson);
	a[rt].sum = chl.sum + chr.sum;
	a[rt].l0 = (chl.l0 == lm) ? (lm + chr.l0) : chl.l0; a[rt].r0 = (chr.r0 == rm) ? (rm + chl.r0) : chr.r0;
	a[rt].l1 = (chl.l1 == lm) ? (lm + chr.l1) : chl.l1; a[rt].r1 = (chr.r1 == rm) ? (rm + chl.r1) : chr.r1;
	a[rt].max0 = max(chl.max0, chr.max0); a[rt].max0 = max(a[rt].max0, chl.r0 + chr.l0);
	a[rt].max1 = max(chl.max1, chr.max1); a[rt].max1 = max(a[rt].max1, chl.r1 + chr.l1);
}
void pushdown(int l, int r, int rt)
{
	if(a[rt].f == 1)
	{
		if(a[rt<<1].f == 0 || a[rt<<1].f == 1) a[rt<<1].f = 1 - a[rt<<1].f;
		else a[rt<<1].f = (a[rt<<1].f == 2) ? 3 : 2;
		if(a[rt<<1|1].f == 0 || a[rt<<1|1].f == 1) a[rt<<1|1].f = 1-a[rt<<1|1].f;
		else a[rt<<1|1].f = (a[rt<<1|1].f == 2) ? 3 : 2;
		a[rt].f = 0;
	}
	else if(a[rt].f) a[rt<<1].f = a[rt<<1|1].f = a[rt].f, a[rt].f = 0;
}
void pushdown(int l, int r, int rt)
{
	if(a[rt].f == 1)
	{
		if(a[rt << 1].f == 0 || a[rt << 1].f == 1) a[rt << 1].f = 1 - a[rt << 1].f;
		else a[rt << 1].f = (a[rt << 1].f == 2) ? 3 : 2; 
		if(a[rt << 1 | 1].f == 0 || a[rt << 1 | 1].f == 1) a[rt << 1 | 1].f = 1 - a[rt << 1 | 1].f;
		else a[rt << 1 | 1].f = (a[rt << 1 | 1].f == 2) ? 3 : 2;
		a[rt].f = 0;
	}
	else if(a[rt].f) a[rt << 1].f = a[rt << 1 | 1].f = a[rt].f, a[rt].f = 0;
}
void updata(int L, int R, int c, int l, int r, int rt)
{
	if(L <= l && r <= R)
	{
		if(a[rt].f == 0) a[rt].f = c;
		else if(a[rt].f == 1) a[rt].f = (c == 1) ? 0 : c;
		else if(a[rt].f == 2) a[rt].f = (c == 1) ? 3 : c;
		else if(a[rt].f == 3) a[rt].f = (c == 1) ? 2 : c;
		return;
	}
	int m = (l + r) >> 1;
	pushdown(l, r, rt);
	if(L <= m) updata(L, R, c, lson);
	if(R > m) updata(L, R, c, rson);
	pushup(l, r, rt);
}
node2 query(int L, int R, int l, int r, int rt)
{
	if(L <= l && r <= R)
	{
		node2 p; node p1 = change(l, r, rt);
		p.l = p1.l1; p.r = p1.r1; p.maxx = p1.max1;
		
	}
}
node2 query(int L, int R, int l, int r, int rt)
{
	if(L <= l && r <= R)
	{
		node2 p; node p1 = change(l, r, rt);
		p.l = p1.l1; p.r = p1.r1; p.maxx = p1.max1;
		return p;
	}
	pushdown(l, r, rt);
	int m = (l + r) >> 1;
	node2 p1, p2, ans; p1.l = p1.r = p1.maxx = p2.l = p2.r = p2.maxx = 0;
	if(L <= m) p1 = query(L, R, lson);
	if(R > m) p2 = query(L, R, rson);
	ans.maxx = max(p1.maxx, p2.maxx); ans.maxx = max(ans.maxx, p1.r + p2.l);
	ans.l = (p1.l == m - l + 1) ? (p1.l + p2.l) : p1.l; ans.r = (p2.r == r - m) ? (p1.r + p2.r) : p2.r;
	pushup(l, r, rt);
	return ans;
}
int query2(int L, int R, int l, int r, int rt)
{
	if(L <= l && r <= R && a[rt].f != -1) return change(l, r, rt).sum;
	int ans = 0, m = (l + r) >> 1;
	pushdown(l ,r, rt);
	if(L <= m) ans += query2(L, R, lson);
	if(R > m) ans += query2(L, R, rson);
	pushup(l, r, rt);
	return ans;
}
void build(int l, int r, int rt)
{
	if(l == r)
	{
		scanf("%d", &a[rt].sum);
		a[rt].l1 = a[rt].r1 = a[rt].max1 = a[rt].sum;
		a[rt].l0 = a[rt].r0 = a[rt].max0 = 1 - a[rt].sum;
		return;
	}
	int m = (l + r) >> 1;
	build(lson); build(rson);
	pushup(l, r, rt);
}
int main()
{
	freopen("bzoj1858.in", "r", stdin);
	int k, x, y, i, m; scanf("%d%d", &n, &m);
	memset(a, 0, sizeof(a)); build(1, n, 1);
	for(i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &k, &x, &y); ++x; ++y;
		if(k == 3) printf("%d\n", query2(x, y, 1, n, 1));
		else if(k == 4) printf("%d\n", query(x, y, 1, n, 1).maxx);
		else updata(x, y, (k+1)%3+1, 1, n, 1);
	}
return 0;
}
aaav00102101887
