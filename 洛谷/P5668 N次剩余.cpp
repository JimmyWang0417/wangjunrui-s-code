#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LL long long
#define nmax 1000010
typedef struct num
{
	int ii;
	LL value;
} num;
num Num[nmax];
int flag[nmax], prime[nmax], cpfactor[100];
LL pfactor[100];
int plen, len_pfactor;
LL k, n, p, proot, x, y;
void mkprime()
{
	int i, j;
	memset(flag, -1, sizeof(flag));
	for (i = 2, plen = 0; i < nmax; i++)
	{
		if (flag[i])
		{
			prime[plen++] = i;
		}
		for (j = 0; (j < plen) && (i * prime[j] < nmax); j++)
		{
			flag[i * prime[j]] = 0;
			if (i % prime[j] == 0)
			{
				break;
			}
		}
	}
}
void findpFactor(LL n)
{
	int i, te, cnt;
	te = (int) sqrt(n * 1.0);
	for (i = 0, len_pfactor = 0; (i < plen) && (prime[i] <= te); i++)
	{
		if (n % prime[i] == 0)
		{
			cnt = 0;
			while (n % prime[i] == 0)
			{
				cnt++;
				n /= prime[i];
			}
			pfactor[len_pfactor] = (LL) prime[i];
			cpfactor[len_pfactor++] = cnt;
		}
	}
	if (n > 1)
	{
		pfactor[len_pfactor] = n;
		cpfactor[len_pfactor++] = 1;
	}
}

LL modular_multi(LL a, LL b, LL c)
{
	LL res, temp;
	res = 0, temp = a % c;
	while (b)
	{
		if (b & 1)
		{
			res += temp;
			if (res >= c)
			{
				res -= c;
			}
		}
		temp <<= 1;
		if (temp >= c)
		{
			temp -= c;
		}
		b >>= 1;
	}
	return res;
}
/*¿ìËÙÃÝÈ¡Óàa^b%c*/LL modular_exp(LL a, LL b, LL c)
{
	LL res, temp;
	res = 1 % c, temp = a % c;
	while (b)
	{
		if (b & 1)
		{
			res = modular_multi(res, temp, c);
		}
		temp = modular_multi(temp, temp, c);
		b >>= 1;
	}
	return res;
}
int dfs(int depth, LL now)
{
	int i;
	LL res, temp;
	if (depth == len_pfactor)
	{
		res = modular_exp(proot, now, p);
		if ((res == 1) && (now != (p - 1)))
		{
			return 0;
		}
		return 1;
	}
	for (i = 0, temp = 1; i <= cpfactor[depth]; i++)
	{
		if (!dfs(depth + 1, now * temp))
		{
			return 0;
		}
		temp = temp * pfactor[depth];
	}
	return 1;
}
void primitive()
{
	findpFactor(p - 1);
	for (proot = 2;; proot++)
	{
		if (dfs(0, 1))
		{
			return;
		}
	}
}
LL extend_gcd(LL a, LL b)
{
	LL d, xx;
	if (b == 0)
	{
		x = 1, y = 0;
		return a;
	}
	d = extend_gcd(b, a % b);
	xx = x;
	x = y, y = xx - a / b * y;
	return d;
}

int bfindNum(LL key, int n)
{
	int left, right, mid;
	left = 0, right = n;
	while (left <= right)
	{
		mid = (left + right) >> 1;
		if (Num[mid].value == key)
		{
			return Num[mid].ii;
		}
		else if (Num[mid].value > key)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	return -1;
}
int cmp(const void *a, const void *b)
{
	num n = *(num *) a;
	num m = *(num *) b;
	LL temp = n.value - m.value;
	if (temp > 0)
	{
		return 1;
	}
	else if (temp < 0)
	{
		return -1;
	}
	return 0;
}
/* a^x = b (mod c)*/LL baby_step_giant_step(LL a, LL b, LL c)
{
	int i, j, te;
	LL temp, xx, aa;
	te = (int) (sqrt(c * 1.0) + 0.5);
	for (i = 0, temp = 1 % c; i <= te; i++)
	{
		Num[i].ii = i;
		Num[i].value = temp;
		temp = temp * a % c;
	}
	aa = Num[te].value;
	qsort(Num, te + 1, sizeof(Num[0]), cmp);
	for (i = 0, temp = 1; i <= te; i++)
	{
		extend_gcd((int) (temp), c);
		xx = x;
		xx = xx * b;
		xx = xx % c + c;
		x = xx % c;
		j = bfindNum(x, te + 1);
		if (j != -1)
		{
			return (LL) (i) * te + j;
		}
		temp = temp * aa % c;
	}
	return -1;
}
int rcmp(const void *a, const void *b)
{
	LL temp = *(LL *) a - *(LL *) b;
	if (temp > 0)
	{
		return 1;
	}
	else if (temp < 0)
	{
		return -1;
	}
	return 0;

}
/* ax = b (mod c)*/LL result[1001];
void solve(LL a, LL b, LL c)
{
	int i;
	LL d;
	d = extend_gcd(a, c);
	if (b % d)
	{
		puts("-1");
		return;
	}
	b /= d, c /= d;
	result[0] = ((LL) x * b % c + c) % c;
	for (i = 1; i < d; i++)
	{
		result[i] = result[i - 1] + c;
	}
	for (i = 0; i < d; i++)
	{
		result[i] = modular_exp(proot, result[i], p);
	}
	qsort(result, d, sizeof(result[0]), rcmp);
	for (i = 0; i < d; i++)
	{
		printf("%I64d\n", result[i]);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	//freopen("data.in", "r", stdin);
#endif
	int cas;
	LL a, b, c;
	mkprime();
	cas = 0;
	/*x^k = n (mod p) */
	while (~scanf("%I64d %I64d %I64d", &k, &p, &n))
	{
		primitive();
		b = baby_step_giant_step(proot, n, p);
		a = k, c = p - 1;
		printf("case%d:\n", ++cas);
		solve(a, b, c);
	}
	return 0;
}
