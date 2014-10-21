/*
给你一个树，树上有N个节点，每个节点上有一个值, N<=10^5。给你一个K, 0 <=K<10^6+3.
求树上的一个链，使得这个链上的所有节点的值的乘积模10^6+3得K.
输出两个端点，如果有相同的答案，输出字典需最小的。
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
#pragma comment(linker,"/STACK:102400000,102400000") 
#define maxN 202014
#define inf 1000002014
#define ll long long
#define it map<int,int>::iterator
#define pr pair<int,int>
#define Mod 1000003
#define rep(i,N) for (int i = 0; i < N; ++i)

using namespace std;

map<int,int> T;
pr ans;
int rev[Mod];
int N, K, cnt;
int p, minSize;
int H[maxN], Nxt[maxN], B[maxN], c[maxN], size[maxN], maxSize[maxN];
int Used[maxN];

inline void add(int x, int y){
	++cnt;
	Nxt[cnt] = H[x]; H[x] = cnt; B[cnt] =y;
}

void ask(int x, int father){
	size[x] = 1;
	maxSize[x] = 0;
	for (int i = H[x]; i; i = Nxt[i])
		if (!Used[B[i]]&& B[i] != father){
			ask(B[i], x);
			size[x] += size[B[i]];
			maxSize[x] = max(maxSize[x], size[B[i]]);
		}
}

void reask(int x, int father, int add){
	if (max(add, maxSize[x]) < minSize){
		minSize = max(add, maxSize[x]);
		p = x;
	}
	for (int i = H[x]; i; i = Nxt[i])
		if (!Used[B[i]]&& B[i] != father){
			reask(B[i], x, add+size[x]-size[B[i]]);
		}
}

void check(int x, int father, ll C){
	//cout<<C<<endl;
	it p = T.find(C);
	if (p != T.end()){
		pr pans = make_pair(min(x,p->second),max(x,p->second));
		//cout<<"enter"<<endl;
		if (pans < ans)
			ans = pans;
	}
	for (int i = H[x]; i; i = Nxt[i])
		if (father != B[i]&& !Used[B[i]])
			check(B[i], x, C*c[B[i]]%Mod);
}

void record(int x, int father, ll C){
	//cout<<C<<endl;
	it p = T.find(C);
	if (p == T.end()){
		T[C] = x;
	}
	else if (p->second > x){
		T[C] = x;
	}
	for (int i = H[x]; i; i = Nxt[i])
		if (father != B[i]&& !Used[B[i]])
			record(B[i], x, C*rev[c[B[i]]]%Mod);
}

void travel(int x){
	ask(x, -1);
	minSize = inf;
	reask(x, -1, 0);
	Used[p] = 1;
	T.clear();
	T[K] = p;
	//cout<<p<<endl;
	/*
	if (c[p]%Mod == K){
		pr pans;
		pans.first = p;
		pans.second = p;
		if (pans < ans)
			ans = pans;
	}
	*/
	for (int i = H[p]; i; i = Nxt[i])
		if (!Used[B[i]]){
			check(B[i], p, 1LL*c[p]*c[B[i]]%Mod);
			record(B[i], p, 1LL*K*rev[c[B[i]]]%Mod);
		}
	for (int i = H[p]; i; i = Nxt[i])
		if (!Used[B[i]])
			travel(B[i]);
}

ll exgcd(ll x, ll y, ll& a, ll& b){
	if (y==0){
		a = 1;
		b = 0;
		return x;
	}
	else{
		ll GCD = exgcd(y, x%y, a, b);
		ll tmp = b;
		b = a-x/y*b;
		a = tmp;
		return GCD;
	}
}

int main(){
	//freopen("t.in", "r", stdin);
	for (int i = 1; i < Mod; ++i){
		ll a, b;
		exgcd(i, Mod, a, b);
		while (a<0)
			a += Mod;
		rev[i] = a;
	}

	while (scanf("%d%d", &N, &K)!=-1){
		for (int i = 1; i <= N; ++i){
			scanf("%d", c+i);
		}
		cnt = 1;
		rep(i,2*N+100){
			Nxt[i] = B[i] = H[i] = Used[i] = 0;
		}
		rep(i,N-1){
			int x, y;
			scanf("%d%d", &x, &y);
			add(x, y);
			add(y, x);
		}
		ans = make_pair(inf,inf);
		travel(1);
		if (ans.first != inf){
			printf("%d %d\n", ans.first, ans.second);
		}
		else{
			puts("No solution");
		}
	}
}