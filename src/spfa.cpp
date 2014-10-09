#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
int n, m, used;
int ST[100010], c[100010];
bool b[100010], flag = true;
LL dist[100010];
struct node
{
	int x, y, z;
	node(){}
	node(int _x, int _y, int _z) : x(_x), y(_y), z(_z){}
}a[300010];
bool cmp(node a1, node a2){return a1.x < a2.x;}
void spfa()
{
	int i, st = a[1].x;
	queue <int> q;
	for(i = 1; i <= n; i++) {b[i] = c[i] = dist[i] = 1; q.push(i);}
	while(!q.empty()) 
	{
		int u = q.front(); q.pop(); b[u] = 0;
		for(int i = ST[u]; a[i].x == u; i++)
		{
			if(dist[a[i].x] + (LL)a[i].z > dist[a[i].y])
			{
				if(++c[a[i].y] > n) {flag = false; return;}
				dist[a[i].y] = dist[a[i].x] + (LL)a[i].z;
				if(!b[a[i].y]) {q.push(a[i].y); b[a[i].y] = 1; ++c[a[i].y];}
			}
		}
	}
}
int main()
{
	int i, no = 0;
	freopen("bzoj2330.in", "r", stdin);
	cin>>n>>m;
	memset(ST, 0, sizeof(ST)); memset(b, 0, sizeof(b));
	for(i = 1; i <= m; i++)
	{
		int k, x, y; cin>>k>>x>>y;
		if(k == 1) {a[++used] = node(x, y, 0); a[++used] = node(y, x, 0);}
		else if(k == 2)
		{
			if(x == y) {cout<<"-1"; return 0;}
			a[++used] = node(x, y, 1);
		}
		else if(k == 3) {a[++used] = node(y, x, 0);}
		else if(k == 4) 
		{
			if(x == y) {cout<<"-1"; return 0;}
			a[++used] = node(y, x, 1);
		}
		else if(k == 5) {a[++used] = node(x, y, 0);}
	}
	sort(a+1, a+1+used, cmp);
	for(i = used; i >= 1; i--) ST[a[i].x] = i;
	spfa();
	if(flag)
	{
		LL ans = 0;
		for(i = 1; i <= n; i++) ans += dist[i];
		ans += no;
		cout<<ans;
	}
	else cout<<"-1";
return 0;
}
