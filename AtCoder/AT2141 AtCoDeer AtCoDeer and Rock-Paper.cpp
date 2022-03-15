#include<cstdio>
#include<cstring>
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
char s[1000010],len;
long long ans,sum_1,sum_2;
bool col[1000010];
int main()
{
	scanf("%s",s+1);
	len=strlen(s+1);
	for(int i=1; i<=len; ++i)
	{
		if(s[i]=='p')
		{
			if(sum_1<sum_2)
				sum_1++;
			else
			{
				sum_2++;
				ans--;
			}
		}
		else
		{
			if(sum_1<sum_2)
			{
				sum_1++;
				ans++;
			}
			else
				sum_2++;
		}
	}
	printf("%lld\n",ans);
}
