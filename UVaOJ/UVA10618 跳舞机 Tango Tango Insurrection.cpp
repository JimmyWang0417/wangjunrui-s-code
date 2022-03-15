#include<cstdio>
#include<cstring>
#define re register
using namespace std;
const int up=0,left=1,right=2,down=3,N=70+5;
int dp[N][4][4][3];
int action[N][4][4][3];
char seq[N],pos[256],footch[]= {".LR"};
inline int calc(int a,int ta)
{
	if(a==ta)
		return 3;
	else if(a+ta==3)
		return 7;
	return 5;
}
inline int energy(int i,int a,int b,int s,int f,int t,int &ta,int &tb)
{
	ta=a,tb=b;
	if(f==1)
		ta=t;
	else if(f==2)
		tb=t;
	if(ta==tb)
		return -1;
	if(ta==right&&tb==left)
		return -1;
	if(a==right&&tb!=b)
		return -1;
	if(b==left&&ta!=a)
		return -1;
	int e;
	if(f==0)
		e=0;
	else if(f!=s)
		e=1;
	else
	{
		if(f==1)
			e=calc(a,ta);
		else
			e=calc(b,tb);
	}
	return e;
}
inline void update(int i,int a,int b,int s,int f,int t)
{
	int ta,tb;
	int e=energy(i,a,b,s,f,t,ta,tb);
	if(e<0)
		return;
	int cost=dp[i+1][ta][tb][f]+e,&ans=dp[i][a][b][s];
	if(cost<ans)
	{
		ans=cost;
		action[i][a][b][s]=f*4+t;
	}
}
int main()
{
	freopen("ans.in","r",stdin);
	freopen("ans.out","w",stdout);
	pos['U']=up;
	pos['L']=left;
	pos['R']=right;
	pos['D']=down;
	while(scanf("%s",seq)!=EOF)
	{
		if(seq[0]=='#')
			break;
		int n=strlen(seq);
		memset(dp,0,sizeof(dp));
		for(re int i=n-1; i>=0; --i)
			for(re int a=0; a<4; ++a)
				for(re int b=0; b<4; ++b)
					if(a!=b)
						for(re int s=0; s<3; ++s)
						{
							dp[i][a][b][s]=10*n;
							if(seq[i]=='.')
							{
								update(i,a,b,s,0,0);
								for(re int t=0; t<4; ++t)
								{
									update(i,a,b,s,1,t);
									update(i,a,b,s,2,t);
								}
							}
							else
							{
								update(i,a,b,s,1,pos[seq[i]]);
								update(i,a,b,s,2,pos[seq[i]]);
							}
						}
		int a=left,b=right,s=0;
		for(re int i=0; i<n; ++i)
		{
			int f=action[i][a][b][s]/4,t=action[i][a][b][s]%4;
			putchar(footch[f]);
			s=f;
			if(f==1)
				a=t;
			else if(f==2)
				b=t;
		}
		putchar('\n');
	}
	return 0;
}
