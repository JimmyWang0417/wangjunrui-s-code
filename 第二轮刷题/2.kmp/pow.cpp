#include<cstdio>
#include<cstring>
#define re register
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))

const int N=2005,INF=0x3f3f3f3f;
int n,len[N],mini,p[N];
char s[N][N],T[N];
inline void pre(int lena)
{
	for(re int i=2,j=0; i<=lena; ++i)
	{
		while(j&&T[i]!=T[j+1])
			j=p[j];
		if(T[i]==T[j+1])
			++j;
		p[i]=j;
	}
}
inline int kmp(int where,int lenb)
{
	int ans=-INF;
	const int &lena=len[where];
	for(re int i=1,j=0; i<=lena; ++i)
	{
		while(j&&s[where][i]!=T[j+1])
		{
			ans=max(ans,j);
			j=p[j];
		}
		if(T[j+1]==s[where][i])
		{
			++j;
			ans=max(ans,j);
		}
		if(j==lenb)
			return lenb;
	}
	return ans;
}
int main()
{
	scanf("%d",&n);
	mini=1;
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",s[i]+1);
		len[i]=strlen(s[i]+1);
		if(len[i]<len[mini])
			mini=i;
	}
	int answer=0;
	for(re int I=1,ans; I<=len[mini]; ++I)
	{
		int lenT=len[mini]-I+1;
		for(re int i=I,j=1; i<=len[mini]; ++i,++j)
			T[j]=s[mini][i];
		pre(lenT);
		ans=INF;
		for(re int i=1; i<=n; ++i)
			ans=min(ans,kmp(i,lenT));
		answer=max(answer,ans);
	}
	printf("%d\n",answer);
	return 0;
}
