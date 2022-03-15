#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=5e5+5;
struct PAM
{
	int fa,len;
	int ans;
	int ch[26];
} point[N];
int cnt=1,las=0;
char str[N];
int n,len;
inline int getfa(int x)
{
//	printf("%d\n",x);
	while(str[n]!=str[n-point[x].len-1])
		x=point[x].fa;
//	printf("%d\n",x);
	return x;
}
inline void insert(int c)
{
//	printf("%d\n",n);
	int cur=getfa(las);
	int now=point[cur].ch[c];
//	printf("%d\n",cur);
//	printf("nmsl\n");
//	printf("las=%d p=%d\n",las,cur);
//	printf("c=%d\n",c);
	if(!now)
	{
		now=++cnt;
		point[now].len=point[cur].len+2;
		point[now].fa=point[getfa(point[cur].fa)].ch[c];
		point[now].ans=point[point[now].fa].ans+1;
		point[cur].ch[c]=now;
	}
	las=now;
//	printf("fa=%d len=%d\n",point[now].fa,point[now].len);
}
signed main()
{
	point[1].len=-1;
	point[0].fa=1;
	point[1].fa=0;
	scanf("%s",str+1);
	len=(int)strlen(str+1);
	int lastans=0;
	for(n=1; n<=len; ++n)
	{
		str[n]=(str[n]-'a'+lastans)%26+'a';
		insert(str[n]-'a');
//		lastans=point[las].ans;
		printf("%d ",lastans=point[las].ans);
	}
	putchar('\n');
	return 0;
}


