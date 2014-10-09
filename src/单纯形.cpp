#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;
const int MaxN = 1000, MaxM = 10000;
int n, m;
int mat[MaxN + 1][MaxM + 1];
void pivot(int l, int e)
{
	int i, prev = 0;
	static int next[MaxM + 1];
	mat[l][e] = -1;
	for(i = 1; i <= m; i++) if(mat[l][i] != 0) next[prev] = i, prev = i;
	next[prev] = -1;
	for(i = 0; i <= n; i++) if(i != l && mat[i][e] != 0)
	{
		int zoom = mat[i][e];
		mat[i][e] = 0;
		for (int j = 0; j != -1; j = next[j]) mat[i][j] += mat[l][j] * zoom;
	}
}
int solve()
{
	while(1)
	{
		int i, e = 0, val = 1e9, l;
		for(i = 1; i <= m; i++) if(mat[0][i] > 0) {e = i; break;}
		if(!e) return mat[0][0];
		for(i = 1; i <= n; i++) if (mat[i][e] < 0 && mat[i][0] < val) val = mat[i][0], l = i;
		pivot(l, e);
	}
}
int main()
{
	int i, j;
	cin>>n>>m;
	for(i = 1; i <= n; i++) cin>>mat[i][0];
	for(i = 1; i <= m; i++)
	{
		int l, r, d; cin>>l>>r>>d;
		for(j = l; j <= r; j++) mat[j][i] = -1;
		mat[0][i] = d;
	}
	cout<<solve()<<endl;
	return 0;
}
