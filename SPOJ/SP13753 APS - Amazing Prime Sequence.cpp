#include <cstdio>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(flag)
		x=(~x)+1;
}
int T,n;
const int N=1e6,mod=1000000003;
int f[N+5];
int main()
{
	for(re int i=1; i<=N; ++i)
		f[i]=(int)((f[i-1]+1ll*i*i%mod*(i+1)%mod*(i+1)%mod*250000001%mod)%mod);//250000001是4关于1000000003的逆元 
	read(T);
	while(T--)
	{
		read(n);
		printf("%d\n",f[n]);
	}
	return 0;
}
