#include<cstdio>
#include<cstdlib>
#include<iostream>
#define re register
using namespace std;
#define dipig(x,y) ((a[x].tp=='M'&&(a[y].t==2||a[y].t==3))||(a[x].tp=='Z'&&a[y].t==2)||(a[x].tp=='F'&&a[y].t==1))
#define youpig(x,y) (((a[x].tp=='M'||a[x].tp=='Z')&&a[y].t==1)||(a[x].tp=='F'&&a[y].t==2))
int nxt[15],las[15],top,f,n,m;
char tmp[5],paidui[2010];
struct pig
{
	char tp,pai[2010];
	int xue,s,z,t;
	inline void chess(int &x)
	{
		--s;
		for(re int i=x; i<s; ++i)
			pai[i]=pai[i+1];
		--x;
	}
	inline bool search(char ch)
	{
		for(re int i=0; i<s; ++i)
			if(pai[i]==ch)
			{
				chess(i);
				return true;
			}
		return false;
	}
	inline void mopai(int x)
	{
		for(re int i=1; i<=x; ++i)
		{
			pai[s++]=paidui[top++];
			if(top==m)
				--top;
		}
	}
} a[15];
inline void end()
{
	puts(a[1].xue?"MP":"FP");
	for(int i=1; i<=n; i++)
	{
		if(a[i].xue==0)puts("DEAD");
		else
		{
			for(int j=0; j<a[i].s-1; j++)
				printf("%c ",a[i].pai[j]);
			if(a[i].s)printf("%c",a[i].pai[a[i].s-1]);
			puts("");
		}
	}
	exit(0);
}
inline void killed(int g,int p)
{
	if(a[p].tp=='M')end();
	if(a[p].tp=='F')
	{
		if(!--f)end();
		a[g].mopai(3);
	}
	else if(a[p].tp=='Z'&&a[g].tp=='M')a[g].s=a[g].z=0;
	nxt[las[p]]=nxt[p];
	las[nxt[p]]=las[p];
}
inline void kouxue(int x,int y)
{
	a[y].xue--;
	if(!a[y].xue)a[y].xue+=a[y].search('P');
	if(!a[y].xue)killed(x,y);
}
inline bool wxkj(int s,int x)
{
	for(int i=s,f=0; !f||i!=s; i=nxt[i],f=1)
	{
		if((!x?(dipig(i,s)):(youpig(i,x)))&&a[i].search('J'))
		{
			a[i].t=a[i].tp=='F'?2:1;
			return !wxkj(i,0);
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(re int i=1; i<=n; i++)
	{
		scanf("%s",tmp);
		a[i].tp=tmp[0];
		f+=tmp[0]=='F';
		for(int j=0; j<4; j++)
			cin>>a[i].pai[j];
		nxt[i]=i+1,las[i]=i-1;
		a[i].s=a[i].xue=4;
	}
	for(re int i=0; i<m; i++)
		cin>>paidui[i];
	nxt[n]=1,las[1]=n;
	int now=1;
	a[1].t=1;
	if(!f)end();
	while(1)
	{
		int kill=0;
		a[now].mopai(2);
		for(re int i=0; i<a[now].s&&a[now].xue; i++)
		{
			if(a[now].pai[i]=='Z')
			{
				a[now].z=1,a[now].chess(i);
				i=-1;
			}
			else if(a[now].pai[i]=='P'&&a[now].xue<4)
			{
				a[now].xue++,a[now].chess(i);
			}
			else if(a[now].pai[i]=='K'&&(a[now].z||!kill))
			{
				int nx=nxt[now];
				if(dipig(now,nx))
				{
					a[now].t=a[now].tp=='F'?2:1;
					a[now].chess(i);
					kill=1;
					if(!a[nx].search('D'))kouxue(now,nx);
				}
			}
			else if(a[now].pai[i]=='F')
			{
				for(re int j=a[now].tp=='F'?1:nxt[now]; j!=now; j=nxt[j])
					if(dipig(now,j))
					{
						a[now].chess(i);
						a[now].t=a[now].tp=='F'?2:1;
						if(wxkj(now,j))break;
						if(a[j].tp=='Z'&&a[now].tp=='M')
						{
							kouxue(now,j);
							break;
						}
						int t=1;
						while(1)
						{
							if(t==1)
							{
								if(!a[j].search('K'))
								{
									kouxue(now,j);
									break;
								}
							}
							else if(!a[now].search('K'))
							{
								kouxue(j,now),i=max(-1,i-1);
								break;
							}
							t^=1;
						}
						i=-1;
						break;
					}
			}
			else if(a[now].pai[i]=='N'||a[now].pai[i]=='W')
			{
				char ch=a[now].pai[i];
				a[now].chess(i);
				for(re int j=nxt[now]; j!=now; j=nxt[j])
				{
					if(!wxkj(now,j)&&!a[j].search(ch=='N'?'K':'D'))
					{
						if(a[j].tp=='M'&&!a[now].t)a[now].t=3;
						kouxue(now,j);
					}
				}
				i=-1;
			}
		}
		now=nxt[now];
	}
	return 0;
}
