#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
char a[1000], b[1000];
int next[1000], n, m;
int main()
{
	int i, j = 0, ans = 0;
	scanf("%s%s", a + 1, b + 1);
	n = strlen(a + 1); m = strlen(b + 1);
	memset(next, 0, sizeof(next));
	for(i = 2; i <= m; i++)
	{
		while(j && b[j + 1] != b[i]) j = next[j];
		if(b[j + 1] == b[i]) ++j;
		next[i] = j;
	}
	cout<<endl;
	j = 0;
	for(i = 1; i <= n; i++)
	{
		while(j && b[j + 1] != a[i]) j = next[j];
		if(b[j + 1] == a[i]) ++j;
		if(j == m) 
		{
			++ans;
			j = next[j];
		}
	}
	cout<<ans<<endl;
return 0;
}
