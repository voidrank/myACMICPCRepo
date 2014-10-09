#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n, m, next[100000], ex[100000];
char a[100000], b[100000];
int main()
{
	int i, j, p = 1, L, k = 1;
	scanf("%s%s", a, b);
	n = strlen(a); m = strlen(b);
	for(i = 0; i < m - 1; i++) if(b[i] != b[i + 1]) {next[1] = i; break;}
	for(i = 2; i < m; i++)
	{
		p = k + next[k] - 1; L = next[i - k];
		if(i + L <= p) next[i] = L;
		else
		{
			j = p - i + 1;
			if(j < 0) j = 0;
			while(i + j < m && b[i + j] == b[j]) ++j;
			next[i] = j; k = i;
		}
	}
	int minlen = (n <= m) ? n : m;
	ex[0] = minlen;
	for(i = 0; i < minlen; i++) if(a[i] != b[i]) {ex[0] = i; break;}
	k = 0;
	for(i = 1; i < n; i++)
	{
		p = k + ex[k] - 1; L = next[i - k];
		if(i + L <= p) ex[i] = L;
		else
		{
			j = p - i + 1;
			if(j < 0) j = 0;
			while(i + j < n && j < m && a[i + j] == b[j]) ++j;
			ex[i] = j; k = i;
		}
	}
	for(i = 0; i < n; i++) printf("%d ", ex[i]);
return 0;
}
