#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#define re register
#define dist(i,j) (sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])))
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
struct node
{
	int u,v;
	double w;
	inline bool operator < (node a)
	{
		return w<a.w;
	}
};
vector<node>edge;
int x[2010],y[2010],point[2010],n,father[2010],tot;
double q1[2010],*q2[2010],sum;
double ans;
inline int find(const int &x)
{
	if(!father[x])
		return x;
	return father[x]=find(father[x]);
}
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
	{
		read(x[i]);
		read(y[i]);
		read(point[i]);
	}
	for(re int i=1; i<=n; i++)
		for(re int j=i+1; j<=n; j++)
			edge.push_back(node {i,j,dist(i,j)});
	sort(edge.begin(),edge.end());
	for(re int i=0,fx,fy; i<edge.size(); i++)
	{
		fx=find(edge[i].u);
		fy=find(edge[i].v);
		if(fx!=fy)
		{
			tot++;
			q1[tot]=point[fx]+point[fy];
			q2[tot]=&edge[i].w;
			sum+=edge[i].w;
			point[fx]=max(point[fx],point[fy]);
			father[fy]=fx;
		}
	}
	for(re int i=1; i<=tot; i++)
		ans=max(ans,q1[i]/(sum-(*q2[i])));
	printf("%.2lf\n",ans);
	return 0;
}
