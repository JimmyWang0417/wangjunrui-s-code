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
const int N=8e5+5;
struct Tree
{
	int fa,len,ch[26];
} point[N];
int cnt=1,las=1;
int len,n;
char str[N];
inline int getfa(int now)
{
	while(str[n]!=str[n-point[now].len-1])
		now=point[now].fa;
	return now;
}
inline void insert(int c)
{
	int cur=getfa(las);
	int now=point[cur].ch[c];
	if(!now)
	{
		now=++cnt;
		point[now].fa=point[getfa(point[cur].fa)].ch[c];
		point[now].len=point[cur].len+2;
		point[cur].ch[c]=now;
	}
	las=now;
}
inline void init()
{
	point[0].fa=1,point[0].len=0;
	point[1].fa=0,point[1].len=-1;
}
signed main()
{
	scanf("%s",str+1);
	len=(int)(strlen(str+1));
	init();
	for(n=1; n<=len; ++n)
		insert(str[n]-'a');
	printf("%d\n",cnt-1);
	return 0;
}


