#ifdef unix
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#define Nit vector<Node*>::iterator
#define ll long long
#define pb push_back
#define ci const int&
#define inf 1000002012
#define Rep(i,n) for(int i=1;i<=n;++i)
#define rep(i,n) for(int i=0;i<n;++i)
#define lowbit(x) ((x)&-(x))
#define Maxn 52012
#define Maxm

using namespace std;

int N, M, MaxSize, x, y, k;
char Opt;

struct Node
{
	Node *l, *r;
	int Ct; 
} Data[ Maxn * 200 ], *New = Data, *root[ Maxn ];

int s[ Maxn ];
vector<Node*>SumP[ 2 ];

inline void Add( Node *Now, int x, int t )
{
	int L = 1, R = MaxSize;
	while ( L != R )
	{
		Now->Ct += t;
		int mid = (L + R) >> 1;
		if ( x > mid )
		{
			if ( !Now->r ) Now->r = New++;
			Now = Now->r;
			L = mid + 1;
		}
		else
		{
			if ( !Now->l ) Now->l = New++;
			Now = Now->l;
			R = mid;
		}
	}
	Now->Ct += t;
}

inline void upd( int x, int p, int t )
{
	for ( ; x <= N; x += lowbit( x ) ) Add( root[ x ], p, t );
}

inline void GET( int x, vector<Node*>& p )
{
	p.clear();
	for ( ; x; x -= lowbit( x ) ) p.pb( root[ x ] );
}

inline void EnterLeft()
{
	for ( int i = 0; i < 2; ++i )
	for ( Nit j = SumP[ i ].begin(); j != SumP[ i ].end(); ++j )
	if ( *j ) (*j) = (*j)->l; 
}

inline void EnterRight()
{
	for ( int i = 0; i < 2; ++i )
	for ( Nit j = SumP[ i ].begin(); j != SumP[ i ].end(); ++j )
	if ( *j ) (*j) = (*j)->r; 
}

inline int GetLeftSize()
{
	int q = 0;
	for ( Nit j = SumP[ 1 ].begin(); j != SumP[ 1 ].end(); ++j )
	if ( *j&& (*j)->l ) q += (*j)->l->Ct;
	for ( Nit j = SumP[ 0 ].begin(); j != SumP[ 0 ].end(); ++j )
	if ( *j&& (*j)->l ) q -= (*j)->l->Ct;
	return q;
}

int main(){
	//freopen("d476.in","r",stdin);freopen("d476.out","w",stdout);
	
	scanf( "%d%d", &N, &M );
	for ( int i = 0; i <= N; ++i ) root[ i ] = New++; 
	for ( int i = 1; i <= N; ++i ) scanf( "%d", s + i ), MaxSize = max( MaxSize, s[ i ] );
	
	for ( int i = 1; i <= N; ++i ) upd( i, s[ i ], 1 );
	
	for ( int i = 1; i <= M; ++i )
	{
		scanf( " %c", &Opt );
		if ( Opt == 'C' )
		{
			scanf( "%d%d", &x, &y );
			upd( x, s[ x ], -1 ); upd( x, y, 1 ); s[ x ] = y;
		}
		else
		{
			scanf( "%d%d%d", &x, &y, &k );
			int L = 1, R = MaxSize;
			GET( x - 1, SumP[ 0 ] ); GET( y, SumP[ 1 ] );
			while( L != R )
			{
				int t = GetLeftSize(), mid = (L + R) >> 1;
				if ( k > t )
				{
					k -= t;
					EnterRight();
					L = mid + 1;
				}
				else
				{
					EnterLeft();
					R = mid;
				}
			}
			printf("%d\n",L);
		}
	}
	
	//fclose(stdin);fclose(stdout);
	return 0;
}

