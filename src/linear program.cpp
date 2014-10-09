#include <cstdio>
#include <cstring>
const int MaxN = 1e4 + 1, MaxM = 1e4 + 1;
const double M = 10000000.0;
struct TTT
{
	double a[MaxM][MaxN];
	double b[MaxM], c[MaxN];
	double v;
	int n, m;
	int getint()
	{
		int x; scanf("%d", &x);
		return x;
	}
	double getdouble()
	{
		double x; scanf("%lf", &x);
		return x;
	}
	void pivot(int x, int y)	//将基本变量x替换为非基本变量y
	{
		b[x] /= a[x][y];
		for (int i = 1; i <= n; i++)
		{
			if (i != y) a[x][i] /= a[x][y];
		}
		a[x][y] = 1 / a[x][y];
		for (int i = 1; i <= m; i ++)
		{
			if (i == x) continue;
			b[i] -= a[i][y] * b[x];
			for (int j = 1; j <= n; j ++) if (j != y) a[i][j] -= a[i][y] * a[x][j];
			a[i][y] = - a[i][y] * a[x][y];
		}
		v += c[y] * b[x];
		for (int i = 1; i <= n; i ++) if (i != y) c[i] -= c[y] * a[x][i];
		c[y] = - c[y] * a[x][y];
	}
	void simplex()
	{
		while (1)
		{
			int t = 0;
			for (int i = 1; i <= n; i++)
			{
				if (c[i] > 0)
				{
					t = i;
					int min = M, p;
					for (int i = 1; i <= m; i++) if (a[i][t] > 0 && b[i] / a[i][t] < min)
					{
						min = b[i] / a[i][t];
						p = i;
					}
					if (min == M) {v = - 1.0; return;} else pivot(p, t);
				}
			}
			if (!t) break;
		}
	}
	void prepare()
	{
		n = getint(); m = getint();
		v = 0.0;
		for (int i = 1; i <= n; i ++) c[i] = getdouble();
		for (int i = 1; i <= m; i ++)
		{
			for (int j = 1; j <= n; j ++) a[i][j] = getdouble();
			b[i] = getdouble();
		}
	}
	void getans()
	{
		prepare(); simplex();
		printf("%.5lf ", v);
	}
} program;
int main()
{
	freopen("lp.in", "r", stdin);
	freopen("lp.out", "w", stdout);
	program.getans();
	return 0;
}
