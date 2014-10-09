#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int map[20][20], a[20], linky[20], lx[20], ly[20], s[20][20];
int n = 11, m = 11, tot;
bool visx[20], visy[20];
bool dfs(int x)
{
	visx[x]=1;
	for(int i = 0; i < m; i++)
    {
        if(visy[i]) continue;
        int t = lx[x] + ly[i] - map[x][i];
        if(!t)
        {
            visy[i] = 1;
            if(linky[i] == -1 || dfs(linky[i]))
			{
				linky[i] = x;
				return 1;
			}
		}
		else tot = min(tot, t);
	}
	return 0;
}
int km()
{
	memset(linky, -1, sizeof(linky));
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)
		lx[i] = max(lx[i],map[i][j]);
	for(int i = 0; i < n; i++)
	{
		while(1)
		{
			memset(visx, 0, sizeof(visx)); memset(visy, 0, sizeof(visy));
			tot = 1e9;
			if(dfs(i)) break;
			for(int j = 0; j < n; j++) if(visx[j]) lx[j] -= tot;
			for(int j = 0; j < m; j++) if(visy[j]) ly[j] += tot;
		}
	}
	int res = 0;
	for(int i = 0; i < m; i++) if(linky[i] != -1) res += lx[linky[i]] + ly[i];
    return res;
}

int main()
{
	int i, T, j;
	freopen("t.in", "r", stdin);
	cin>>T;
	while(T--)
	{
		memset(map, 0, sizeof(map));
		for(i = 0; i < 11; i++) for(j = 0; j < 11; j++) 
		{
			int x; cin>>x;
			if(x) map[i][j] = x; else map[i][j] = -100000000;
		}
		cout<<km()<<endl;
	}
return 0;
}
