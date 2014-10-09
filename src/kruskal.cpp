#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int n, m, used = 0, f[1010];
bool map[1010][1010];
struct node{int x, int y, double l;} e[1000010];
struct node2{int x, y;} a[1010];
double dis(int i, int j) {return sqrt((a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y));}
bool cmp(node a1, node a2) {return a1.l < a2.l;}

int gf(int x){return (x == f[x]) ? x : f[x] = gf(f[x]);}

int main()
{
	int i;
	freopen("bzoj1626.in", "r", stdin);
	cin>>n>>m; memset(map, 0, sizeof(map));
	for(i = 1; i <= n; i++) {cin>>a[i].x>>a[i].y; f[i] = i;}
	for(i = 1; i <= m; i++)
	{
		int x, y; cin>>x>>y;
		map[x][y] = 1;
		e[++used] = {x, y, 0.0};
	}
	for(i = 1; i <= n; i++) for(j = 1; j < i; j++) if(!map[i][j]) e[++used] = {i, j, dis(i, j)};
	sort(e + 1, e + 1 + used, cmp);
	(f[e[1].x] < f[e[1].y]) ? (f[e[1].y] = f[e[1].x]) : (f[e[1].x] = f[e[1].y]);
	double ans = e[1].l; i = 2;
	int vis = 0;
	while(vis < n - 2)
	{
		int x = e[i].x, y = e[i].y;
		int xx = gf(x), yy = gf(y);
		if(xx != yy)
		{
			(xx < yy) ? (f[yy] = xx) : (f[xx] = yy);
			ans = max(ans, e[i].l);
			++vis;
		}
		++i;
	} 

return 0;
}
