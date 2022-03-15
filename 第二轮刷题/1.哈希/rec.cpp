#include<cstdio>
#define ll ull
#define ull long long
#define re register
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
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
const int N=2010,p1=29,p2=31,mod=1e9+7;
int n,m,a[N][N],b[N][N],c[N][N];
ull pow_x[N],pow_y[N];
inline void pow_init()
{
	pow_x[0]=pow_y[0]=1;
	for(re int i=1; i<=n; ++i)
		pow_x[i]=1ull*pow_x[i-1]*p1%mod;
	for(re int i=1; i<=m; ++i)
		pow_y[i]=1ull*pow_y[i-1]*p2%mod;
	return;
}
class hash
{
	private:
		ull s[N][N];
	public:
		inline void init(int (*x)[N])
		{
			for(re int i=1; i<=n; ++i)
				for(re int j=1; j<=m; ++j)
				{
					ull tmp=1ull*pow_x[i]*pow_y[j]%mod*x[i][j]%mod;
					s[i][j]=((s[i][j-1]+s[i-1][j])%mod-s[i-1][j-1]+mod+tmp)%mod;
				}
		}
		inline ull sum(int bx,int by,int ex,int ey)
		{
			return ((s[ex][ey]+s[bx-1][by-1])%mod-(s[ex][by-1]+s[bx-1][ey])%mod+mod)%mod;
		}
		/*inline void print(int n,int m)
		{
			for(re int i=1; i<=n; ++i)
			{
				for(re int j=1; j<=m; ++j)
					printf("%lld ",s[i][j]);
				putchar('\n');
			}
		}*/
} hash1,hash2,hash3;
inline bool check1(int len,int i,int j)
{
	int bx1=i-len,by1=j-len,ex1=i+len,ey1=j+len;
	ull res1=hash1.sum(bx1,by1,ex1,ey1);
	int bx2=bx1,by2=m-ey1+1,ex2=ex1,ey2=m-by1+1;
	ull res2=hash2.sum(bx2,by2,ex2,ey2);
	int bx3=n-ex1+1,by3=by1,ex3=n-bx1+1,ey3=ey1;
	ull res3=hash3.sum(bx3,by3,ex3,ey3);
	ull res4=res1;
	if(by1<by2)
		res1=(res1*pow_y[by2-by1])%mod;
	else if(by1>by2)
		res2=(res2*pow_y[by1-by2])%mod;
	if(bx3<bx1)
		res3=(res3*pow_x[bx1-bx3])%mod;
	else if(bx3>bx1)
		res4=(res4*pow_x[bx3-bx1])%mod;
	return res1==res2&&res3==res4;
}
inline bool check2(int len,int i,int j)
{
	int bx1=i-len,by1=j-len,ex1=i+len+1,ey1=j+len+1;
	ull res1=hash1.sum(bx1,by1,ex1,ey1);
	int bx2=bx1,by2=m-ey1+1,ex2=ex1,ey2=m-by1+1;
	ull res2=hash2.sum(bx2,by2,ex2,ey2);
	int bx3=n-ex1+1,by3=by1,ex3=n-bx1+1,ey3=ey1;
	ull res3=hash3.sum(bx3,by3,ex3,ey3);
	ull res4=res1;
	if(by1<by2)
		res1=(res1*pow_y[by2-by1])%mod;
	else if(by1>by2)
		res2=(res2*pow_y[by1-by2])%mod;
	if(bx3<bx1)
		res3=(res3*pow_x[bx1-bx3])%mod;
	else if(bx3>bx1)
		res4=(res4*pow_x[bx3-bx1])%mod;
	return res1==res2&&res3==res4;
}
int main()
{
	re ull answer=0;
	read(n),read(m);
	pow_init();
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=m; ++j)
		{
			read(a[i][j]);
			b[i][m-j+1]=c[n-i+1][j]=a[i][j];
		}
//	for(re int i=1; i<=n; ++i)
//		printf("%d ",pow_x[i]);
//	putchar('\n');
//	for(re int i=1; i<=m; ++i)
//		printf("%d ",pow_y[i]);
//	putchar('\n');
	hash1.init(a),hash2.init(b),hash3.init(c);
	//hash3.print(n,m);
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=m; ++j)
		{
			re int l=0,r=min((i-1,n-i),min(j-1,m-j)),mid;
			while(l<r)
			{
				mid=(l+r+1)>>1;
				//printf("%d %d %d\n",l,r,check1(mid,l,r));
				if(check1(mid,i,j))
					l=mid;
				else
					r=mid-1;
			}
			answer+=l+1;
		}
	for(re int i=1; i<n; ++i)
		for(re int j=1; j<m; ++j)
		{
			re int l=0,r=min(min(i-1,n-i-1),min(j-1,m-j-1)),mid,res=-1;
			while(l<=r)
			{
				mid=(l+r)>>1;
				//printf("%d %d %d\n",l,r,check2(mid,l,r));
				if(check2(mid,i,j))
				{
					res=mid;
					//printf("%d\n",res);
					l=mid+1;
				}
				else
					r=mid-1;
			}
			answer+=res+1;
		}
	printf("%lld\n",answer);
	return 0;
}

