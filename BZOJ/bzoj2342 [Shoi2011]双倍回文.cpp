#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
const int N=500000+5<<1;
int n,p[N],ans;
char str[N];
int main()
{
	scanf("%d%s",&n,str+1);
	for(re int i=n; i>=1; --i)
	{
		str[i<<1]=str[i];
		str[i<<1|1]='|';
	}
	str[0]='~';
	str[1]='|';
	str[(n=n<<1|1)+1]='$';
	for(re int i=1,maxx=0,mid=0; i<=n; ++i)
	{
		p[i]=maxx>i?min(maxx-i,p[(mid<<1)-i]):1;
		while(str[i-p[i]]==str[i+p[i]])
			++p[i];
		if(i+p[i]>maxx)
		{
			if(i&1)
				for(re int j=max(i+4,maxx); j<i+p[i]; ++j)
					if(!((j-i)&3)&&p[i-(j-i)/2]>(j-i)/2)
						ans=max(ans,j-i);
			maxx=i+p[i];
			mid=i;
		}
	}
	printf("%d\n",ans);
	return 0;
}
