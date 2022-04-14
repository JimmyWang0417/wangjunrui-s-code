#include<stdio.h>
#include<cassert>
#include<cstdlib>
#include"guess.h"

namespace
{
	long long P,seed;
	int n;
	long long y;
	int cnt;
	const int Qmin=100,Qmax=200;
	int gen()
	{
		seed=seed*n%P;
		return seed%n;
	}
	int work()
	{
		assert(scanf("%lld %d %lld %lld",&P,&n,&seed,&y)==4);
		cnt=0;
		long long res=solve(P,n);
		if (res!=y) exit(puts("wrong answer")&0);
		return cnt;
	}
	int __query(long long x){++cnt;if (cnt>Qmax) exit(puts("too many queries")&0);return (x==y?1:(x<y?2:0))^gen();}
}

int query(long long x){if (x<0||x>(long long)(1e18)) exit(puts("invalid query")&0); return __query(x);}

int main()
{
	int sub,T; assert(scanf("%d %d",&sub,&T)==2);
	int mx=0;
	while (T--) { int t=work(); mx=(mx<t?t:mx); }
	printf("correct, maximum query count %d\n",mx);
	return 0;
}
