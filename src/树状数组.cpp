#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n, c[200000];
int lowbit(int x){return x & (-x);}

void ins(int p, int x){ while(p <= n) c[p] += x, p += lowbit(p);}
int sum(int p)
{
	int ans = 0;
	while(p > 0)
	{
		ans += c[p];
		p -= lowbit(p);
	}
	return ans;
}

int main()
{
	int T;
	freopen("hdu1166.in", "r", stdin);
	scanf("%d", &T);
	for(int t = 1; t <= T; t++)
	{
		memset(c, 0, sizeof(c));
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) 
		{
			int x; scanf("%d", &x);
			ins(i, x);
		}
		printf("Case %d:\n", t);
		while(1)
		{
			char a[10];
			int i, j;
			scanf("%s", a); 
			if(a[0] == 'E') break;
			scanf("%d%d\n", &i, &j);
			if(a[0] == 'S') ins(i, -j);
			else if(a[0] == 'A') ins(i, j);
			else if(a[0] == 'Q')printf("%d\n", sum(j) - sum(i - 1));
		}
	}
return 0;
}
