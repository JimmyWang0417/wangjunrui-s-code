#include<cstdio>
#define re register
#define min(x,y) ((x)>(y)?(y):(x))
#define max(x,y) ((x)>(y)?(x):(y))
inline void readstring(char *str,int &cnt)
{
	char s=getchar();
	str[0]='~';
	str[cnt=1]='|';
	while(s<'a'||s>'z')
		s=getchar();
	while(s>='a'&&s<='z')
	{
		str[++cnt]=s;
		str[++cnt]='|';
		s=getchar();
	}
}
const int N=11000000+5<<1;
char s[N];
int cnt,p[N];
int main()
{
	int ans=-1;
	readstring(s,cnt);
	for(re int i=1,r=0,mid=0; i<=cnt; ++i)
	{
		if(i<=r)
			p[i]=min(p[(mid<<1)-i],r-i+1);
		while(s[i-p[i]]==s[i+p[i]])
			++p[i];
		if(i+p[i]>r)
		{
			r=i+p[i]-1;
			mid=i;
		}
		ans=max(ans,p[i]);
	}
	printf("%d\n",ans-1);
	return 0;
}
