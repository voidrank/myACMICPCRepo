//hdu2222
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int M = 10010;
struct trie {
	int flag, fail, next[26];
	void clear()
	{
		flag = 0; fail = -1;
		for(int i = 0; i < 26; i++) next[i] = -1;
	}
}t[M << 6];
int used;
char str[55], s[M << 8];
queue <int> q;

void insert(char *a)
{
	int i = 0, p = 0, j, x;
	while(a[i])
	{
		x = t[p].next[a[i] - 'a'];
		if(x < 0) {t[p].next[a[i] - 'a'] = x = ++used; t[x].clear();}
		p = x;
		++i;
	}
	++t[p].flag;
}
void build()
{
	int x, y, i, p;
	t[0].fail = -1;
	q.push(0);
	while(!q.empty())
	{
		x = q.front(); q.pop();
		for(i = 0; i < 26; i++)
		{
			y = t[x].next[i];
			if(y < 0) continue;
			if(!x) t[y].fail = 0;
			else
			{
				p = t[x].fail;
				while(p >= 0)
				{
					if(t[p].next[i] >= 0) {t[y].fail = t[p].next[i]; break;}
					p = t[p].fail;
				}
				if(p < 0) t[y].fail = 0;
			}
			q.push(y);
		}
	}
}
int query()
{
	int i = 0, j, p = 0, x, num = 0;
	while(s[i])
	{
		j = s[i] - 'a';
		while(t[p].next[j] < 0 && p) p = t[p].fail;
		p = t[p].next[j];
		if(p < 0) p = 0;
		x = p;
		while(x && t[x].flag != -1)
		{
			num += t[x].flag;
			t[x].flag = -1;
			x = t[x].fail;
		}
		++i;
	}
return num;
}
int main()
{
	int T, n, i;
	scanf("%d", &T);
	while(T--)
	{
		used = 0; t[0].clear(); while(!q.empty()) q.pop();
		scanf("%d", &n);
		while(n--)
		{
			scanf("%s", str);
			insert(str);
		}
		build();
		scanf("%s", s);
		printf("%d\n", query());
	}
return 0;
}
