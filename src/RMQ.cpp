#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
const int maxn = 50010;
int n;
int d1[20][maxn<<1], d2[20][maxn<<1];
void build()
{
	for(int i = 1; 1<<i <= n; i++) for(int j = 1; j <= n; j++)
		d1[i][j] = max(d1[i-1][j], d1[i-1][j+(1<<(i-1))]), d2[i][j] = min(d2[i-1][j], d2[i-1][j+(1<<(i-1))]);
}
int query(int x, int y)
{
	int k = log2(y-x);
	return max(d1[k][x], d1[k][y-(1<<k)+1]) - min(d2[k][x], d2[k][y-(1<<k)+1]);
}
int main()
{
	int i, q, j;
	freopen("t.in", "r", stdin);
	cin>>n>>q;
	memset(d1, 0, sizeof(d1)); memset(d2, 0x3f, sizeof(d2));
	for(i = 1; i <= n; i++) scanf("%d", &d1[0][i]), d2[0][i] = d1[0][i];
	build();
	while(q--)
	{
		int x, y; scanf("%d%d", &x, &y);
		if(x == y) printf("0\n"); else printf("%d\n", query(x, y));
	}
return 0;
}
