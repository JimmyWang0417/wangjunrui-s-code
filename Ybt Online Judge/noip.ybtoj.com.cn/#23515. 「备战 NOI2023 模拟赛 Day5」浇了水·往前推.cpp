#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long int LL;
const int MOD(1000000000 + 7);

constexpr int Mult(int a, int b)
{
	return a * 1LL * b % MOD;
}

constexpr int Add(int a, int b)
{
	return a + b >= MOD ? a + b - MOD : a + b;
}

constexpr int Sub(int a, int b)
{
	return a - b < 0 ? a - b + MOD : a - b;
}

int power(int a, int n)
{
	int Ret(1);
	while (n)
	{
		if (n & 1)
			Ret = Mult(Ret, a);
		a = Mult(a, a), n >>= 1;
	}
	return Ret;
}

inline void update(int &a, int b)
{
	a = Add(a, b);
}

int N, K, L, R;

struct Matrix
{
	Matrix() {memset(v, 0, sizeof(v));}
	int v[8][8];
};

LL temp[8][8];
Matrix operator*(const Matrix &a, const Matrix &b)
{
	memset(temp, 0, sizeof(temp));
	for (int k = 0;k < 8;++k)
		for (int i = 0;i < 8;++i)
			for (int j = 0;j < 8;++j)
				temp[i][j] += a.v[i][k] * 1LL * b.v[k][j];
	Matrix c;
	for (int i = 0;i < 8;++i)
		for (int j = 0;j < 8;++j)
			c.v[i][j] = temp[i][j] % MOD;
	return c;
}

Matrix operator^(Matrix a, int n)
{
	Matrix Ret;
	for (int i = 0;i < 8;++i)
		Ret.v[i][i] = 1;
	while (n)
	{
		if (n & 1)
			Ret = Ret * a;
		a = a * a, n >>= 1;
	}
	return Ret;
}

constexpr int get(int v0, int v1, int v2)
{
	return v0 + (v1 << 1) + (v2 << 2);
}

int work(int c, int a, int b, int k)
{
	if (a > b)
		swap(a, b), c ^= (N & 1);
	if (b == 0)
		return (k == 0) * power(2, N - 1);
	int w;
	for (w = (1 << 29);;w >>= 1)
		if (b & w)
			break;
	if ((w << 1) - 1 < k)
		return 0;
	Matrix zy;
	for (int v0 = 0;v0 <= 1;++v0)
		for (int v1 = 0;v1 <= 1;++v1)
			for (int v2 = 0;v2 <= 1;++v2)
			{
				update(zy.v[get(v0, v1, v2)][get(v0 ^ 1, v1, v2)], b - w + 1);
				if (v1)
					update(zy.v[get(v0, v1, v2)][get(v0, 1, v2)], w);
				else
					update(zy.v[get(v0, v1, v2)][get(v0, 1, v2)], 1);
				if (a & w)
				{
					update(zy.v[get(v0, v1, v2)][get(v0 ^ 1, v1, v2 ^ 1)], a - w + 1);
					if (v1)
						update(zy.v[get(v0, v1, v2)][get(v0, 1, v2 ^ 1)], w);
					else
						update(zy.v[get(v0, v1, v2)][get(v0, 1, v2 ^ 1)], 1);
				}
				else
					update(zy.v[get(v0, v1, v2)][get(v0, v1, v2 ^ 1)], a + 1);
			}
	zy = (zy ^ N);
	return Add(zy.v[get(0, 0, 0)][get((k & w) != 0, 1, c)], work(c, (a & w) ? (a ^ w) : a, b ^ w, k ^ ((a & w) * c) ^ (w * (c ^ (N & 1)))));
}

constexpr int get(int v0, int v1)
{
	return v0 + (v1 << 1);
}

int work(int b, int k)
{
	if (b == 0)
		return k == 0;
	int w;
	for (w = (1 << 29);;w >>= 1)
		if (b & w)
			break;
	if ((w << 1) - 1 < k)
		return 0;
	Matrix zy;
	for (int v0 = 0;v0 <= 1;++v0)
		for (int v1 = 0;v1 <= 1;++v1)
		{
			update(zy.v[get(v0, v1)][get(v0 ^ 1, v1)], b - w + 1);
			if (v1)
				update(zy.v[get(v0, v1)][get(v0, 1)], w);
			else
				update(zy.v[get(v0, v1)][get(v0, 1)], 1);
		}
	zy = (zy ^ N);
	return Add(zy.v[get(0, 0)][get((k & w) != 0, 1)], work(b ^ w, k ^ (w * (N & 1))));
}

int main()
{
	freopen("equation.in", "r", stdin);
	freopen("equation.out", "w", stdout);
	int Q;
	scanf("%d", &Q);
	while (Q--)
	{
		scanf("%d%d%d%d", &N, &K, &L, &R);
		if (L == 0)
			printf("%d\n", work(R, K));
		else
			printf("%d\n", Sub(work(0, L - 1, R, K), work(1, L - 1, R, K)));
	}
	return 0;
}
