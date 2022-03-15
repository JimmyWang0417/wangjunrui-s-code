/*https://www.luogu.org/problemnew/show/P1464*/
#include<cstdio>
using namespace std;
long long f[21][21][21];
long long w(long long a,long long b,long long c)
{
	if(a<=0||b<=0||c<=0)
		return 1;
	if(a>20||b>20||c>20)
		return w(20,20,20);
	if(a<b&&b<c)
		return f[a][b][c]!=0?f[a][b][c]:f[a][b][c]=w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c);
	return f[a][b][c]!=0?f[a][b][c]:f[a][b][c]=w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1);
}
long long a,b,c;
int main()
{
	while(true)
	{
		scanf("%lld%lld%lld",&a,&b,&c);
		if(a==-1&&b==-1&&c==-1)
			return 0;
		printf("w(%lld, %lld, %lld) = %lld\n",a,b,c,w(a,b,c));
	}
}
