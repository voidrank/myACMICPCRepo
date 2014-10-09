#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int maxn = 15 + 10;
const int maxl = 1000000 + 5;
int n, used = 0; LL x, y;
int c[maxn], p[maxn], l[maxn];
struct node{int a, b, l;} rec[maxn * maxn];
inline int exgcd(int a, int b, LL &x, LL &y)
{
	if(b == 0) {x = 1; y = 0; return a;}
	LL x1, y1;
	int t = exgcd(b, a % b, x1, y1);
	x = y1; y = x1 - a / b * y1;
	return t;
}
int main()
{
	int i, j, ii = 0;
	freopen("savage.in", "r", stdin);
	cin>>n;
	for(i = 1; i <= n; i++) {cin>>c[i]>>p[i]>>l[i]; ii = max(ii, c[i]);}
	for(i = 1; i < n; i++) for(j = i + 1; j <= n; j++)
	{
		rec[++used].a = p[i] - p[j]; rec[used].b = c[j] - c[i];
		if(rec[used].a < 0) {rec[used].a = -rec[used].a; rec[used].b = -rec[used].b;}
		rec[used].l = min(l[i], l[j]);
	}
	for(; ii <= maxl; ii++)
	{
		bool f = 1;
		for(j = 1; j <= used; j++)
		{	
			int t = exgcd(rec[j].a, ii, x, y);
			if(rec[j].b % t) continue;
			int w = ii / t;
			t = rec[j].b / t;
			x = (x * t % w + w) % w;
			if(x <= rec[j].l) {f = 0; break;}
		}
		if(f) break;
	}
	cout<<ii;
return 0;
}
