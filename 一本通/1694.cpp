#include<cstring>
#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
typedef long long s64;
const int ONE = 800005;
const int Base = 10007;
const int MOD = 1e9 + 7;
int n, m, Q;
int x, y;
char c[5], A[ONE], B[ONE];
int Pow[ONE];
int pre_A[ONE], pre_B[ONE], suc_A[ONE], suc_B[ONE];
s64 F[ONE], G[ONE];
s64 Sum_F[ONE], Sum_G[ONE];
struct power
{
	int l, r;
};
inline int get()
{
	int res=1,Q=1;
	char c;
	while( (c=getchar())<48 || c>57 )
		if(c=='-')Q=-1;
	res=c-48;
	while( (c=getchar())>=48 && c<=57 )
		res=res*10+c-48;
	return res*Q;
}

inline void Deal_first()
{
	Pow[0] = 1;
	for(re int i = 1; i <= max(n, m); i++)
		Pow[i] = (s64)Pow[i - 1] * Base % MOD;
	for(re int i = 1; i <= n; i++)
		pre_A[i] = (s64)pre_A[i - 1] * Base % MOD + A[i];
	for(re int i = 1; i <= n; i++)
		suc_A[i] = (s64)suc_A[i - 1] * Base % MOD + A[n - i + 1];
	for(re int i = 1; i <= m; i++)
		pre_B[i] = (s64)pre_B[i - 1] * Base % MOD + B[i];
	for(re int i = 1; i <= m; i++)
		suc_B[i] = (s64)suc_B[i - 1] * Base % MOD + B[m - i + 1];
}
inline int Pre(int PD, int l, int r)
{
	if(PD == 1)
		return (pre_A[r] - (s64)pre_A[l - 1] * Pow[r - l + 1] % MOD + MOD) % MOD;
	if(PD == 2)
		return (pre_B[r] - (s64)pre_B[l - 1] * Pow[r - l + 1] % MOD + MOD) % MOD;
}

inline int Suc(int PD, int L, int R)
{
	int Limit = PD == 1 ? n : m;
	int l = Limit - R + 1, r = Limit - L + 1;
	if(PD == 1)
		return (suc_A[r] - (s64)suc_A[l - 1] * Pow[r - l + 1] % MOD + MOD) % MOD;
	if(PD == 2)
		return (suc_B[r] - (s64)suc_B[l - 1] * Pow[r - l + 1] % MOD + MOD) % MOD;
}

inline int Check(int PD, int l, int r)
{
	int Limit = PD == 1 ? n : m;
	if(l < 1 || r > Limit)
		return 0;
	return Pre(PD, l, r) == Suc(PD, l, r);
}

inline power Find(int PD, int PosA, int PosB)

{
	int l = 1, r = PD == 1 ? n : m;
	while(l < r - 1)
	{
		int mid = l + r >> 1;
		int Left = PosA - mid + 1, Right = PosB + mid - 1;
		if(Check(PD, Left, Right)) l = mid;
		else r = mid;

	}

	int Left, Right;
	Left = PosA - r + 1, Right = PosB + r - 1;
	if(Check(PD, Left, Right)) return (power)
	{
		Left, Right
	};

	Left = PosA - l + 1, Right = PosB + l - 1;
	return (power)
	{
		Left, Right
	};
}
inline void Deal_F()

{
	for(re int i = 1; i <= n; i++)
	{
		power pos;
		pos = Find(1, i, i);
		F[pos.l]++, F[i + 1]--;
		if(A[i] != A[i + 1])
			continue;

		pos = Find(1, i, i + 1);
		F[pos.l]++, F[i + 1]--;
	}
	for(re int i = 1; i <= n + 1; i++)
		F[i] += F[i - 1];
	for(re int i = 1; i <= n + 1; i++)
		Sum_F[i] = Sum_F[i - 1] + F[i];
}
inline void Deal_G()

{
	for(re int i = 1; i <= m; i++)
	{
		power pos;
		pos = Find(2, i, i);
		G[pos.l]++, G[i + 1]--;
		if(B[i] != B[i + 1])
			continue;

		pos = Find(2, i, i + 1);
		G[pos.l]++, G[i + 1]--;
	}
	for(re int i = 1; i <= m + 1; i++)
		G[i] += G[i - 1];
	for(re int i = 1; i <= m + 1; i++)
		Sum_G[i] = Sum_G[i - 1] + G[i];
}
inline int Get_LCP(int L1, int L2)
{
	int l = 0, r = min(n - L1 + 1, m - L2 + 1);

	while(l < r - 1)
	{
		int mid = l + r >> 1;

		if(Pre(1, L1, L1 + mid - 1) == Pre(2, L2, L2 + mid - 1))
			l = mid;
		else r = mid;

	}
	if(Pre(1, L1, L1 + r - 1) == Pre(2, L2, L2 + r - 1))
		return r;
	return l;
}
int main()
{
	scanf("%s", c + 1);
	scanf("%s", A + 1);
	n = strlen(A + 1);
	scanf("%s", B + 1);
	m = strlen(B + 1);
	for(re int i = 1, j = m; i <= j; i++, j--)
		swap(B[i], B[j]);
	Deal_first();
	Deal_F();
	/*for(int i=1; i<=n; i++)
		printf("%d\n",Sum_G[i]);*/
	Deal_G();
	Q = get();
	while(Q--)
	{
		x = get(), y = get();
		int l = Get_LCP(x, y);
		s64 Ans = Sum_F[x + l] - Sum_F[x] + Sum_G[y + l] - Sum_G[y] + l;
		printf("%lld\n", Ans);

	}
}
