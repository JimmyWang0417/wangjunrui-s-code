#include<cstdio>
#include<map>
#define re register
#define ll long long
using namespace std;
const ll mod2=402653189,mod1=1e7+9;
const int N=1000010;
int n,m,p,q;
char s[30010][510],ans[510];
map<long long,int>c;
struct node
{
	long long former,opposite;
} a[N];
inline void heap(char *s,node&a)
{
	ll x,y,x1,y1;
	x=y=x1=y1=0ll;
	for(re int i=1; i<=m; i++)
	{
		x=(x<<1ll|(long long)(s[i]=='Y'))%mod1;
		y=(y<<1ll|(long long)(s[i]=='Y'))%mod2;
		x1=(x1<<1ll|(long long)(s[i]=='N'))%mod1;
		y1=(y1<<1ll|(long long)(s[i]=='N'))%mod2;
	}
	a.former=x*mod2+y;
	a.opposite=x1*mod2+y1;
	return;
}
inline bool check(int t)
{
	ll x,y,x1,y1;
	x=y=x1=y1=0ll;
	for(re int i=m-1; i>=0; i--)
	{
		if(t&(1<<i))
		{
			x=(x<<1ll|1ll)%mod1;
			y=(y<<1ll|1ll)%mod2;
			x1=(x1<<1ll)%mod1;
			y1=(y1<<1ll)%mod2;
		}
		else
		{
			x=(x<<1ll)%mod1;
			y=(y<<1ll)%mod2;
			x1=(x1<<1ll|1ll)%mod1;
			y1=(y1<<1ll|1ll)%mod2;
		}
	}
	return !(c[x*mod2+y]||c[x1*mod2+y1]);
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&p,&q);
	for(re int i=1; i<=n; i++)
	{
		scanf("%s",s[i]+1);
		heap(s[i],a[i]);
		c[a[i].former]++;
	}
	if(!(p||q))
	{
		int ans=n+1;
		for(re int i=0; i<=n; i++)
			if(check(i))
			{
				ans=i;
				break;
			}
		if(ans<=n)
		{
			for(re int i=m-1; i>=0; i--)
				printf("%c",(ans&(1<<i))?'Y':'N');
			putchar('\n');
		}
		else
			puts("-1");
	}
	else if(p)
	{
		bool flag=false;
		for(re int i=1; i<=n; i++)
		{
			if(c[a[i].former]==p&&c[a[i].opposite]==q)
			{
				if(!flag)
				{
					flag=true;
					for(re int j=1; j<=m; j++)
						ans[j]=s[i][j];
				}
				else
				{
					int x=1;
					while(x<=m&&s[i][x]==ans[x])
						x++;
					if(s[i][x]<ans[x]&&x<=m)
					{
						for(re int j=x; j<=m; j++)
							ans[j]=s[i][j];
					}
				}
			}
		}
		if(!flag)
		{
			putchar('-');
			putchar('1');
			putchar('\n');
			return 0;
		}
		for(re int i=1; i<=m; i++)
			putchar(ans[i]);
		putchar('\n');
	}
	else
	{
		bool flag=false;
		for(re int i=1; i<=n; i++)
		{
			if(c[a[i].former]==q&&c[a[i].opposite]==p)
			{
				if(!flag)
				{
					flag=true;
					for(re int j=1; j<=m; j++)
						ans[j]=s[i][j];
				}
				else
				{
					int x=1;
					while(x<=m&&s[i][x]==ans[x])
						x++;
					if(s[i][x]<ans[x]&&x<=m)
					{
						for(re int j=x; j<=m; j++)
							ans[j]=s[i][j];
					}
				}
			}
		}
		if(!flag)
		{
			putchar('-');
			putchar('1');
			putchar('\n');
			return 0;
		}
		for(re int i=1; i<=m; i++)
			putchar(ans[i]=='Y'?'N':'Y');
		putchar('\n');
	}
	return 0;
}
