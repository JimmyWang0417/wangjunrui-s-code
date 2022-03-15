#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define ll long long
#define re register
#define int long long
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
const int N=15,mod=299987;
int n,m,ex,ey;
char str[N][N];
bool a[N][N];
int head[300000];
int cnt[2];
struct Edge
{
	int next,key[2];
	ll ans[2];
} e[1<<24];

int now,las;
inline void insert(int bits,int val)
{
	int u=bits%mod;
	for(int i=head[u]; i; i=e[i].next)
		if(e[i].key[now]==bits)
		{
			e[i].ans[now]+=val;
			return;
		}
	e[++cnt[now]].next=head[u];
	e[cnt[now]].key[now]=bits;
	e[cnt[now]].ans[now]=val;
	head[u]=cnt[now];
}
int inc[15];
signed main()
{
	read(n,m);
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",str[i]+1);
		for(int j=1; j<=m; ++j)
			if(str[i][j]=='.')
			{
				a[i][j]=1;
				ex=i,ey=j;
			}
	}
	cnt[now]=1;
	e[cnt[now]].ans[now]=1;
	e[cnt[now]].key[now]=0;
	inc[0]=1;
	for(int i=1; i<=12; ++i)
		inc[i]=inc[i-1]<<2;
	ll ans=0;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=cnt[now]; ++j)
			e[j].key[now]<<=2;
//		for(int j=1; j<=cnt[now]; ++j)
//			printf("%d %d\n",e[j].key[now],e[j].ans[now]);
//		putchar('\n');
		for(int j=1; j<=m; ++j)
		{
			memset(head,0,sizeof(head));
			las=now;
			now^=1;
			cnt[now]=0;
			for(int k=1; k<=cnt[las]; ++k)
			{
				int bit=e[k].key[las];
				ll val=e[k].ans[las];
				int b1=(bit>>((j-1)*2))%4,b2=(bit>>(j*2))%4;
//				printf("%d %d\n",bit,val);
				if(!a[i][j])
				{
					if(!b1&&!b2)
						insert(bit,val);
				}
				else if(!b1&&!b2)
				{
					if(a[i+1][j]&&a[i][j+1])
						insert(bit+inc[j-1]+inc[j]*2,val);
				}
				else if(!b1&&b2)
				{
					if(a[i][j+1])
						insert(bit,val);
					if(a[i+1][j])
						insert(bit-inc[j]*b2+inc[j-1]*b2,val);
				}
				else if(b1&&!b2)
				{
					if(a[i+1][j])
						insert(bit,val);
					if(a[i][j+1])
						insert(bit-inc[j-1]*b1+inc[j]*b1,val);
				}
				else if(b1==1&&b2==1)
				{
					int k1=1;
					for(int l=j+1; l<=m; ++l)
					{
						if((bit>>(l*2))%4==1)
							++k1;
						if((bit>>(l*2))%4==2)
							--k1;
						if(!k1)
						{
							insert(bit-inc[j]-inc[j-1]-inc[l],val);
							break;
						}
					}
				}
				else if(b1==2&&b2==2)
				{
					int k1=1;
					for(int l=j-2; l>=0; --l)
					{
						if((bit>>(l*2))%4==1)
							--k1;
						if((bit>>(l*2))%4==2)
							++k1;
						if(!k1)
						{
							insert(bit-inc[j]*2-inc[j-1]*2+inc[l],val);
							break;
						}
					}
				}
				else if(b1==2&&b2==1)
					insert(bit-inc[j-1]*2-inc[j],val);
				else if(i==ex&&j==ey)
					ans+=val;
			}
//			putchar('\n');
		}
	}
	printf("%lld\n",ans);
	return 0;
}


