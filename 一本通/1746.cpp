#include<cstdio>
#include<cctype>
#include<algorithm>
#define re register
using namespace std;
namespace IO
{
	char buf[1<<15],*fs,*ft;
	inline char getc()
	{
		return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++;
	}
	template<typename T>inline void read(T &x)
	{
		x=0;
		bool f=false;
		char ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=true, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
		if(f)
			x=-x;
		return;
	}

	char Out[1<<28],*fe=Out,ch[20];
	int num;
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
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
		num=0;
		while(x)
		{
			ch[++num]=(x%10)^48;
			x/=10;
		}
		while(num)
			*fe++=ch[num--];
		*fe++='\n';
	}
}

using IO::read;
using IO::write;
const int N=251,logN=9;
int n,m,q,f[N][N][logN][logN],logg[N];
int main()
{
	read(n);
	read(m);
	read(q);
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=m; ++j)
			read(f[i][j][0][0]);
	logg[0]=-1;
	for(re int i=1; i<=max(n,m); ++i)
		logg[i]=logg[i>>1]+1;
	for(re int k=0; k<logg[n]+1; ++k)
		for(re int l=0; l<logg[m]+1; ++l)
		{
			if(!k&&!l)
				continue;
			for(re int i=1; i+(1<<k)-1<=n; ++i)
				for(re int j=1; j+(1<<l)-1<=m; ++j)
				{
					if(l)
						f[i][j][k][l]=max(f[i][j][k][l-1],f[i][j+(1<<l-1)][k][l-1]);
					else
						f[i][j][k][l]=max(f[i][j][k-1][l],f[i+(1<<k-1)][j][k-1][l]);
				}
		}
	re int q1,q2,x1,x2,y1,y2;
	while(q--)
	{
		read(x1);
		read(y1);
		read(x2);
		read(y2);
		q1=logg[x2-x1+1];
		q2=logg[y2-y1+1];
		write(max(max(f[x1][y1][q1][q2],f[x1][y2-(1<<q2)+1][q1][q2]),max(f[x2-(1<<q1)+1][y1][q1][q2],(f[x2-(1<<q1)+1][y2-(1<<q2)+1][q1][q2]))));
	}
	IO::flush();
	return 0;
}
