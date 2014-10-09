#include<cstdio>
#include<algorithm>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
crope list;
char s[2500005];
int main()
{
	int i, n, now, k;
	char cmd[25], c;
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	while(n--)
	{
		scanf("%s", cmd);
		if(cmd[0] == 'M') scanf("%d", &now);
		else if(cmd[0] == 'I')
		{
			int k; scanf("%d%*c", &k);
			for(i = 0; i < k; i++) do {scanf("%c", &s[i]);} while(s[i] == '\n');
			s[k] = 0;
			list.insert(now, s);
		}
		else if(cmd[0] == 'D')
		{
			int k; scanf("%d", &k);
			list.erase(now, k);
		}
		else if(cmd[0] == 'G')
		{
			int k; scanf("%d", &k);
			list.copy(now, k, s); s[k] = 0;
			printf("%s\n", s);
		}
		else if(cmd[0] == 'P') --now; 
		else ++now;
	}
return 0;
}
