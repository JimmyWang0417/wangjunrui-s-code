#include<cstdio>
#include<cctype>
#include<algorithm>
#include<cstring>
#define re register
using namespace std;
namespace IO
{
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=getchar();
		while(!isdigit(ch)&&ch^'-')
			ch=getchar();
		if(ch=='-')
		{
			b=true;
			ch=getchar();
		}
		while(isdigit(ch))
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=getchar();
		}
		if(b)
			x=~x+1;
		return;
	}
	char Out[1000*7+10],*fe=Out,ch[25];
	int num=0;
	template<typename T>
	inline void write(T x)
	{
		if(!x)
			*fe++='0';
		if(x<0)
		{
			*fe++='-';
			x=-x;
		}
		while(x)
		{
			ch[++num]=x%10+'0';
			x/=10;
		}
		while(num)
			*fe++=ch[num--];
		*fe++='\n';
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
using IO::read;
using IO::write;
const int N=1e5+10,SIZE=(1<<21)+10;
int T,n,a[N],tot,type,b[N],t,top;
bool f[SIZE];
struct point
{
	int l,r;//rÖ¸1£¬lÖ¸0
	inline void init()
	{
		return (void)(l=r=0);
	}
} tree[SIZE];
inline void insert(int x)
{
	re int u=1;
	for(re int i=20; i>=0; i--)
		if((x>>i)&1)
		{
			if(!tree[u].r)
			{
				tree[u].r=++tot;
				tree[tot].init();
			}
			u=tree[u].r;
		}
		else
		{
			if(!tree[u].l)
			{
				tree[u].l=++tot;
				tree[tot].init();
			}
			u=tree[u].l;
		}
	return;
}
inline int find(int x)
{
	re int u=1,ans=0;
	for(re int i=20; i>=0; i--)
		if((x>>i)&1)
		{
			if(tree[u].l)
			{
				u=tree[u].l;
				ans|=(1<<i);
			}
			else
				u=tree[u].r;
		}
		else
		{
			if(tree[u].r)
			{
				u=tree[u].r;
				ans|=(1<<i);
			}
			else
				u=tree[u].l;
		}
	return ans;
}
int main()
{
	re int ans=0;
	read(T);
	while(T--)
	{
		read(n);
		read(type);
		for(re int i=1; i<=n; i++)
			read(a[i]);
		ans=0;
		if(type==2)
		{
			tree[tot=1].init();
			insert(a[1]);
			for(re int i=2; i<=n; i++)
			{
				ans=max(ans,find(a[i]));
				insert(a[i]);
			}
		}
		else if(type==1)
		{
			t=n;
			for(re int i=1; i<=n; i++)
				b[i]=a[i];
			for(re int j=20; j>=0; j--)
			{
				top=0;
				for(re int i=1; i<=t; i++)
					if((b[i]>>j)&1)
						top++;
				if(top>1)
				{
					top=0;
					ans|=1<<j;
					for(re int i=1; i<=t; i++)
						if((b[i]>>j)&1)
							b[++top]=b[i];
					t=top;
				}
			}
		}
		else
		{
			memset(f,false,sizeof(f));
			for(re int i=1; i<=n; i++)
				f[a[i]]=true;
			for(re int i=(1<<20)-1; i>=0; i--)
				for(re int j=0; j<=19&&!f[i]; j++)
					if(!((i>>j)&1))
						f[i]|=f[i|(1<<j)];
			for(re int i=1,val; i<=n; i++)
			{
				val=0;
				for(re int j=19; j>=0; j--)
					if((!((a[i]>>j)&1))&&f[val|(1<<j)])
						val|=1<<j;
				ans=max(ans,a[i]|val);
			}
		}
		write(ans);
	}
	IO::flush();
	return 0;
}
