#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define re register
const int N=60*100*26+10;
int ch[N][30],fail[N],tn;
bool bo[N];
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
inline void insert(char *s)
{
	int x=0;
	for(re int i=0; s[i]; ++i)
	{
		int y=s[i]-'A';
		if(ch[x][y]==0) ch[x][y]=++tn;
		x=ch[x][y];
	}
	bo[x]=1;
}
inline void init()
{
	memset(fail,0,sizeof(fail));
	queue<int> que;
	for(re int i=0; i<27; ++i)
	{
		if(ch[0][i]) que.push(ch[0][i]);
	}
	while(!que.empty())
	{
		int now=que.front();
		que.pop();
		for(int i=0; i<27; ++i)
		{
			if(ch[now][i]) que.push(ch[now][i]),fail[ch[now][i]]=ch[fail[now]][i];
			else ch[now][i]=ch[fail[now]][i];
			bo[ch[now][i]]|=bo[ch[fail[now]][i]];
		}
	}
}
struct Mat
{
	long long mat[111][111];
	Mat()
	{
		memset(mat,0,sizeof(mat));
	}
};
inline Mat operator*(const Mat &m1,const Mat &m2)
{
	Mat m;
	for(re int i=0; i<=tn; ++i)
	{
		for(re int j=0; j<=tn; ++j)
		{
			for(re int k=0; k<=tn; ++k)
			{
				m.mat[i][j]+=m1.mat[i][k]*m2.mat[k][j];
				m.mat[i][j]%=10007;
			}
		}
	}
	return m;
}
char str[11];
int m,n;
int main()
{
	read(m);
	read(n);
	tn=0;
	memset(bo,0,sizeof(bo));
	memset(ch,0,sizeof(ch));
	while(m--)
	{
		scanf("%s",str);
		insert(str);
	}
	init();
	Mat e,x;
	for(re int i=0; i<=tn; ++i) e.mat[i][i]=1;
	for(re int i=0; i<=tn; ++i)
	{
		if(bo[i]) continue;
		for(re int j=0; j<27; ++j)
		{
			if(bo[ch[i][j]]) continue;
			++x.mat[i][ch[i][j]];
		}
	}
	while(n)
	{
		if(n&1) e=e*x;
		x=x*x;
		n>>=1;
	}
	long long res=0;
	for(re int i=0; i<=tn; ++i)
	{
		res+=e.mat[0][i];
		res%=10007;
	}
	printf("%lld\n",res);
	return 0;
}
