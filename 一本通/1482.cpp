#include<cstdio>
#include<cstring>
using namespace std;
#define r register
int p[1000001],ans,len[200],n;
char a[200][1000001];
inline void pre(char*b,int m)
{
	p[1]=0;
	for(r int i=1,j=0; i<m; i++)
	{
		while(j>0&&b[i+1]!=b[j+1])j=p[j];
		if(b[i+1]==b[j+1])
			j++;
		p[i+1]=j;
	}
}
inline int kmp(char*a,char*b,int n,int m)
{
	int answer=0;
	for(r int i=0,j=0; i<n; i++)
	{
		while(j>0&&b[j+1]!=a[i+1])
			j=p[j];
		if(b[j+1]==a[i+1])
			j++;
		if(j==m)
		{
			answer++;
			j=p[j];
		}
	}
	return answer;
}
int main()
{
	scanf("%d",&n);
	for(r int i=0; i<n; i++)
	{
		scanf("%s",a[i]+1);
		len[i]=strlen(a[i]+1);
	}
	for(r int i=0; i<n; i++)
	{
		pre(a[i],len[i]);
        ans=0;
        for(int j=0; j<n; j++)
            ans+=kmp(a[j],a[i],len[j],len[i]);
        printf("%d\n",ans);
	}
}
