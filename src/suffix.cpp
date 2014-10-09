//poj1743
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define mem(x) memset((x), 0, sizeof((x)))
const int maxn = 100010, maxlen = 100000;
int n, sum[maxn], trank[maxn], rank[maxn], sa[maxn], height[maxn], tsa[maxn], s[maxn];
void sorting(int j)
{
	int i;
	memset(sum, 0, sizeof(sum));
	for(i = 1; i <= n; i++) ++sum[rank[i+j]];
	for(i = 1; i <= maxlen; i++) sum[i] += sum[i-1];
	for(i = n; i; i--) tsa[sum[rank[i+j]]--] = i;
	memset(sum, 0, sizeof(sum));
	for(i = 1; i <= n; i++) ++sum[rank[i]];
	for(i = 1; i <= maxlen; i++) sum[i] += sum[i-1];
	for(i = n; i; i--) sa[sum[rank[tsa[i]]]--] = tsa[i];
}
void get_sa()
{
	int i, j, p;
	for(i = 0; i < n; i++) trank[i+1] = s[i];
	for(i = 1; i <= n; i++) ++sum[trank[i]];
	for(i = 1; i <= maxlen; i++) sum[i] += sum[i-1];
	for(i = n; i; i--) sa[sum[trank[i]]--] = i;
	rank[sa[1]] = 1;
	for(i = 2, p = 1; i <= n; i++)
	{
		if(trank[sa[i]] != trank[sa[i-1]]) ++p;
		rank[sa[i]] = p;
	}
	for(j = 1; j <= n; j <<= 1)
	{
		sorting(j);
		trank[sa[1]] = 1;
		for(i = 2, p = 1; i <= n; i++)
		{
			if(rank[sa[i]] != rank[sa[i-1]] || rank[sa[i]+j] != rank[sa[i-1]+j]) ++p;
			trank[sa[i]] = p;
		}
		for(i = 1; i <= n; i++) rank[i] = trank[i];
	}
}
void get_height()
{
	for(int i = 1, j = 0; i <= n; i++)
	{
		if(rank[i] == 1) continue;
		for(; s[i+j-1] == s[sa[rank[i]-1]+j-1]; ) ++j;
		height[rank[i]] = j;
		if(j) --j;
	}
}
bool check(int mid)
{
	int minn = sa[1], maxx = sa[1];
	for(int i = 1; i <= n; i++)
	{
		if(height[i] < mid)
		{
			minn = sa[i]; maxx = sa[i];
			continue;
		}
		minn = min(minn, sa[i]);
		maxx = max(maxx, sa[i]);
		if(maxx - minn > mid) return 1;
	}
	return 0;
}
bool check(int mid)
{
	int minn = sa[1], maxx = sa[1];
	for(int i = 1; i <= n; i++)
	{
		if(height[i] < mid)
		{
			minn = sa[i]; maxx = sa[i];
			continue;
		}
		minn = min(minn, sa[i]);
		maxx = max(maxx, sa[i]);
		if(maxx - minn > mid) return 1;
	}
	return 0;
}
int main()
{
	int i, last, now, ans;
	freopen("t.in", "r", stdin);
	while(1)
	{
		n = 0; scanf("%d", &n); if(!n) return 0;
		n--; scanf("%d", &last);
		mem(sum); mem(rank); mem(trank); mem(sa); mem(height); mem(tsa); mem(s);
		for(i = 0; i < n; i++)
		{
			scanf("%d", &now);
			s[i] = now - last; s[i] += 100;
			last = now;
		}
		get_sa(); get_height();
		int l = 0, r = n;
		while(l < r - 1)
		{
			int m = (l + r) >> 1;
			if(check(m)) l = m; else r = m;
		}
		if(check(r)) ans = r; else ans = l;
		if(ans >= 4) cout<<(ans+1)<<endl; else cout<<"0\n";
	}
return 0;
}
