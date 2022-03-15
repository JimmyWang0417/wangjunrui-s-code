#include<cstdio>
#include<cstring>
#define re register
using namespace std;
struct Matrix
{
    int n,m,g[110][110];
} res,a,c;
int maxn,n,s[20][20],t;
const int mod=2009;
inline Matrix operator * (const Matrix&a,const Matrix&b)
{
    c.n=a.n;
    c.m=b.m;
    for(re int i=1; i<=c.n; i++)
        for(re int j=1; j<=c.m; j++)
            c.g[i][j]=0;
    for(re int i=1; i<=c.n; i++)
        for(re int j=1; j<=c.m; j++)
            for(re int k=1; k<=a.m; k++)
                c.g[i][j]=(c.g[i][j]+a.g[i][k]*b.g[k][j])%mod;
    return c;
}
inline int calc(int a,int b)
{
    return a+n*b;
}
inline Matrix operator ^ (Matrix a,long long b)
{
    res.n=res.m=maxn*n;
    for(re int i=1; i<=res.n; i++)
        for(re int j=1; j<=res.m; j++)
            res.g[i][j]=(i==j);
    while(b)
    {
        if(b&1)
            res=res*a;
        a=a*a;
        b>>=1;
    }
    return res;
}
inline void print(Matrix a)
{
    for(re int i=1; i<=a.n; i++)
    {
        for(re int j=1; j<=a.m; j++)
            printf("%d ",a.g[i][j]);
        putchar('\n');
    }
}
int main()
{
    //memset(a.g,0x7fffffff,sizeof(a.g));
    scanf("%d%d",&n,&t);
    for(re int i=1; i<=n; i++)
        for(re int j=1; j<=n; j++)
        {
            scanf("%1d",&s[i][j]);
            if(s[i][j]>maxn)

                maxn=s[i][j];
        }
    for(re int i=1; i<=n; i++)
        for(re int j=1; j<maxn; j++)
            a.g[calc(i,j)][calc(i,j-1)]=1;
    for(re int i=1; i<=n; i++)
        for(re int j=1; j<=n; j++)
            if(s[i][j]!=0)
                a.g[i][calc(j,s[i][j]-1)]=1;
    a.n=a.m=maxn*n;
    //printf("%d\n",calc(n,maxn-1));
    //print(a);
    a=a^t;
    //print(a);
    printf("%d\n",a.g[1][n]);
    return 0;
}
