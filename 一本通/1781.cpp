#include<cstdio>
#include<cctype>
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
const int N=(1<<10)+10;
int n,m,k,f[N][N];
bool g[N][N];
int ans;
int main()
{
	read(n);
	read(m);
	read(k);
	for(re int i=1,x,y; i<=m; i++)
	{
		read(x);
		read(y);
		--x;
		--y;
		g[x][y]=g[y][x]=true;
		f[(1<<x)|(1<<y)][(1<<x)|(1<<y)]=1;
	}
	for(re int i=1; i<=(1<<n)-1; i++)
		for(re int j=i; j; j=(j-1)&i)
		{
			if(!f[i][j])
				continue;
			for(re int x=0; x<n; x++)
			{
				if(!(i&(1<<x)))
					continue;
				int t=(j&(1<<x))?j^(1<<x):j;
				for(re int y=0; y<n; y++)
				{
					if(!g[x][y]||t>(1<<y)||i&(1<<y))
						continue;
					f[i|(1<<y)][t|(1<<y)]+=f[i][j];
				}
			}
		}
	for(re int i=1,t,tot; i<=(1<<n)-1; i++)
	{
		t=i;
		tot=0;
		while(t)
		{
			tot+=t&1;
			t>>=1;
		}
		if(tot==k)
			ans+=f[(1<<n)-1][i];
	}
	write(ans);
	IO::flush();
	return 0;
}

