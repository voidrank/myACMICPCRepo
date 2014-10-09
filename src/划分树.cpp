#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn = 100001;
struct node {int l, r; }a[maxn << 2];
int n, m, len, toleft[20][maxn], val[20][maxn], sorted[maxn];
void build(int l, int r, int d, int rt)
{
	a[rt].l = l; a[rt].r = r;
	if(a[rt].l == a[rt].r) return;
	int mid = (a[rt].l + a[rt].r) >> 1, lsame = mid - l + 1;
	for(int i = l; i <= r; i++) if(val[d][i] < sorted[mid]) --lsame;
	int lpos = l, rpos = mid + 1, same = 0;
	for(int i = l; i <= r; i++)
	{
		if(i == l) toleft[d][i] = 0; else toleft[d][i] = toleft[d][i - 1];
		if(val[d][i] < sorted[mid]) toleft[d][i]++, val[d + 1][lpos++] = val[d][i];
		else if(val[d][i] > sorted[mid]) val[d + 1][rpos++] = val[d][i];
		else
		{
			if(same < lsame){++same; ++toleft[d][i]; val[d + 1][lpos++] = val[d][i];}
			else val[d + 1][rpos++] = val[d][i];
		}
	} 
	build(l, mid, d + 1, rt << 1);
	build(mid + 1, r, d + 1, rt << 1 | 1);
}
int query(int l, int r, int k, int d, int rt)
{
	if(l == r) return val[d][l];
	int s, ss;
	if(l == a[rt].l) s = toleft[d][r], ss = 0;
	else s = toleft[d][r] - toleft[d][l - 1], ss = toleft[d][l - 1];
	if(s >= k) return query(a[rt].l + ss, a[rt].l + ss + s - 1, k, d + 1, rt << 1);
	else
	{
		int mid = (a[rt].l + a[rt].r) >> 1;
		int bb = l - a[rt].l - ss, b = r - l + 1 - s;
		return query(mid + bb + 1, mid + bb + b, k - s, d + 1, rt << 1 | 1);
	}
}
int main()
{
	int i;
	freopen("kth.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(i = 1; i <= n; i++){scanf("%d", &val[0][i]); sorted[i] = val[0][i];}
	sort(sorted + 1, sorted + 1 + n);
	build(1, n, 0, 1);
	while(m--)
	{
		int l, r, k; scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", query(l, r, k, 0, 1));
	}
return 0;
}
