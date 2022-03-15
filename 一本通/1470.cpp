#include<cstdio>
#include<cstring>
using namespace std;
#define r register
inline int read()
{
    char s=getchar();
    bool f=false;
    int x=0;
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
    return f?-x:x;
}
const int N=1e6+1;
char a[N],b[N],c[N];
int p[N],n,m,father[N],tot;
inline void pre()
{
    p[1]=0;
    for(r int i=1,j=0; i<m; i++)
    {
        while(j>0&&b[j+1]!=b[i+1])
            j=p[j];
        if(b[j+1]==b[i+1])
            j++;
        p[i+1]=j;
    }
}
inline void kmp()
{
    r int i=0,j=0;
    for(i=1; i<=n; i++)
    {
    	c[++tot]=a[i];
        while(j>0&&b[j+1]!=c[tot])
            j=p[j];
        if(b[j+1]==c[tot])
            j++;
        father[tot]=j;
        if(j==m)
        {
        	tot-=m;
        	j=father[tot];
		}
    }
}
int main()
{
    scanf("%s%s",a+1,b+1);
    n=strlen(a+1);
    m=strlen(b+1);
    pre();
    kmp();
    for(r int i=1;i<=tot;i++)
    printf("%c",c[i]);
    return 0;
}

