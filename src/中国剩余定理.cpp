#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn  =100000;
typedef long long LL;
int k;
LL a[maxn], n[maxn];
LL exgcd(LL a, LL b, LL &x, LL &y)
{
	if(b == 0) {x = 1; y = 0; return a;}
	LL xx, yy;
	LL t = exgcd(b, a%b, xx, yy);
	x = yy; y = xx - a/b*yy;
	return t;
}
// x % n[i] = a[i];  x = a[i] (mod n[i])
LL china()
{
	int i;
	LL N = 1, ans = 0;
	for(i = 1; i <= k; i++) N *= n[i];
	for(i = 1; i <= k; i++)
	{
		LL m = N/n[i], x, y;
		LL t = exgcd(m, n[i], x, y);
		x = (x%n[i]+n[i])%n[i];
		ans = (ans+x*m*a[i]%N)%N;
	}
	return ans;
}
int main()
{
	int i;
	freopen("t.in", "r", stdin);
	bool f = 1;
	while(cin>>k)
	{
		for(i = 1; i <= k; i++) 
		{
			cin>>n[i]>>a[i];
			if(n[i] <= a[i]) f = 0;
		}
		if(!f) {cout<<"-1"<<endl; continue;}
		cout<<china()<<endl; 
	}
return 0;
}
