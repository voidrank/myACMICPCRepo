#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define sqr(x) (x)*(x)
const int maxn = 20;
const double eps = 0.0000001;
int n;
double a[maxn][maxn], c[maxn][maxn];
void gauss()
{
	int i, j, k;
	for(i = 1; i <= n; i++) for(j = 1; j <= n; j++) if(i != j)
	{
		for(k = 1; k <= n+1; k++) if(k != i) c[j][k] -= c[i][k]*c[j][i]/c[i][i];
		c[j][i] = 0;
	}
}
int main()
{
	int i, j;
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(i = 1; i <= n+1; i++) for(j = 1; j <= n; j++) scanf("%lf", &a[i][j]);
	for(i = 1; i <= n; i++) for(j = 1; j <= n; j++) c[i][j] = 2*(a[i+1][j]-a[i][j]);
	for(i = 1; i <= n; i++) 
	{ 	
		c[i][n+1] = 0;
		for(j = 1; j <= n; j++) c[i][n+1] += sqr(a[i][j]) - sqr(a[i+1][j]);
	}
	for(i = 1; i <= n; i++)
	gauss();
	for(i = 1; i < n; i++) printf("%.3f ", -c[i][n+1]/c[i][i]);
	printf("%.3f", -c[n][n+1]/c[n][n]);
return 0;
}
