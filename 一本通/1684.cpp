#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=25;
int ans,a[N],t,n;
bool flag;
inline void dfs(int k,int pre)
{
	if(flag)
		return;
	int res=0;
	for(re int i=2; i<=n; i++)
		if(abs(a[i]-a[i-1])>1)
			res++;
	if(res+k>ans)
		return;
	bool check=true;
	for(re int i=2; i<=n; i++)
		if(a[i]!=a[i-1]+1)
		{
			check=false;
			break;
		}
	if(check)
	{
		printf("%d\n",ans);
		flag=true;
		return;
	}
	for(re int i=2; i<=n; i++)
	{
		if(i==pre)
			continue;
		reverse(a+1,a+i+1);
		dfs(k+1,i);
		reverse(a+1,a+i+1);
	}
}
int main()
{
	read(t);
	while(t--)
	{
		read(n);
		for(re int i=1; i<=n; i++)
			read(a[i]);
		for(ans=0;; ans++)
		{
			flag=false;
			dfs(0,0);
			if(flag)
				break;
		}
	}
	return 0;
}
