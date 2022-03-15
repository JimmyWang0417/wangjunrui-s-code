#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e5 + 7;

namespace
{
	long long gcd (long long a, long long b)
	{
		return b ? gcd (b, a % b) : a;
	}
	long long Pow (long long a, long long b, long long c)
	{
		long long base = a, resl = 1;
		while (b)
		{
			if (b & 1)
				resl = resl * base % c;
			base = base * base % c;
			b >>= 1;
		}
		return resl;
	}
	namespace
	{
		int tot;
		bool mar[N];
		long long pri[N];
		void PrimeGenerate ()
		{
			for (int i = 2; i < N; i += 1)
			{
				if (!mar[i])
					pri[++tot] = i;
				for (int j = 1; j <= tot && i * pri[j] < N; j += 1)
				{
					mar[i * pri[j]] = true;
					if (i % pri[j] == 0) break;
				}
			}
		}// Generate Primes in O (n)
	}// Prime Generate
}// Basis Operation
namespace
{
	long long mod;
	struct Matrix
	{
		int r, c;
		long long m[3][3];
		inline Matrix ()
		{
			memset(m, false, sizeof m);
		}
		inline Matrix (int n, int m) :Matrix()
		{
			r = n, c = m;
		}
		inline Matrix (int n) :Matrix()
		{
			r = c = n;
			m[0][0] = m[1][1] = 1ll;
		}
		inline Matrix operator * (const Matrix &o) const
		{
			Matrix res = Matrix (r, o.c);
			for (int i = 0; i < r; i += 1)
				for (int j = 0; j < o.c; j += 1)
					for (int k = 0; k < c; k += 1)
						res.m[i][j] += 1ll * m[i][k] * o.m[k][j] % mod,
						               res.m[i][j] %= mod;
			return res;
		}
		Matrix operator ^ (long long o) const
		{
			Matrix base = *this;
			Matrix resl = Matrix (r);
			while (o)
			{
				if (o & 1ll)
					resl = resl * base;
				base = base * base;
				o >>= 1;
			}
			return resl;
		}
	};
	long long Fib (long long n, long long Mod)
	{
		if (n == 0) return 0ll;
		if (n == 1 || n == 2) return 1ll;
		mod = Mod;
		n -= 1;
		Matrix a = Matrix (2, 1);
		a.m[0][0] = 1;
		Matrix b = Matrix (2, 2);
		b.m[0][0] = b.m[1][0] = b.m[0][1] = 1;
		a = (b ^ n) * a;
		return a.m[0][0];
	}

	namespace
	{
		char ch[N*300];
		void Read()
		{
			scanf("%s", ch);
		}
		long long Int(long long p)
		{
			register long long res = 0;
			register int pos = 0;
			while (!isdigit(ch[pos])) pos += 1;
			while (isdigit(ch[pos]))
				res = res * 10 + ch[pos] - '0', res %= p, pos += 1;
			return res;
		}
	}// Big Integer

	namespace
	{
		long long Fac[N];
		int  cnt;
		long long Judge (long long k, long long p)
		{
			cnt = 0;
			for (register long long i = 1; i * i <= k; i += 1)
			{
				if (k % i) continue;
				Fac[cnt ++] = i;
				if (i * i < k) Fac[cnt ++] = k / i;
			}
			std:: sort (Fac, Fac + cnt);
			for (register int i = 0; i < cnt; i += 1)
				if (Fib(Fac[i] + 5, p) == 5)
					return Fac[i];
		}
		const long long Rest[6] = {0, 1, 3, 8, 6, 20};
		long long g (long long p)
		{
			if (p <= 5) return Rest[p];
			if (Pow(5, (p - 1) >> 1, p) == 1)
				return Judge (p-1, p);
			else return Judge ((p + 1) << 1, p);
		}
		long long Get (long long p)
		{
			PrimeGenerate ();
			long long tmp, pre;
			long long lcm = 1ll;
			for (register int i = 1; i <= tot && pri[i] * pri[i] <= p; i += 1)
			{
				if (p % pri[i]) continue;
				pre = p / pri[i];
				while (p % pri[i] == 0) p /= pri[i];
				tmp = g (pri[i]) * (pre / p), lcm = lcm / gcd (lcm, tmp) * tmp;
			}
			if (p > 1)
			{
				tmp = g(p);
				lcm = lcm * tmp / gcd(lcm, tmp);
			}
			return lcm;
		}
	}
}
int main ()
{
	Read();
	long long Mod, A, M;
	scanf("%lld", &Mod);
	M = Get (Mod);
	A = Int (M);
	printf("%lld\n", Fib(A, Mod));
	return 0;
}
