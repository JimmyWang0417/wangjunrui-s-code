#include<cstdio>
#define MAXN 100007
using namespace std;
int n,m,x,y;
struct SegTree
{
	int l;//左端点
	int r;//右端点
	long long w;//区间和（表示区间内树的总数）
	int lt;//lazytag(懒惰标记)
	int add;
	int mul;
	SegTree()
	{
		lt=1;   //将lazytag初始化为一
	}
} tree[MAXN<<2]; //注意tree数组的长度至少为maxn*4
inline int read()
{
	register char s=getchar();
	int x=0;
	while(s<'0'||s>'9')
		s=getchar();
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return x;
}
inline void build(int l,int r,int u)//建树
{
	tree[u].l=l,tree[u].r=r;
	if(l==r)
	{
		tree[u].w=1;    //一旦找到叶节点，直接将值赋为1(因为没个点上只有一棵树)
		return;
	}
	int m=(l+r)/2;//二分
	build(l,m,u+u);
	build(m+1,r,u+u+1);
	tree[u].w=tree[u+u].w+tree[u+u+1].w;//区间和即为两子树的区间和之和（绕口但不难理解）
}
inline void down(int u)//下推lazytag
{
	tree[u+u].lt=tree[u].lt;  //直接将lazytag赋给子节点
	tree[u+u+1].lt=tree[u].lt;
	tree[u+u].w=tree[u].lt;   //由于lazytag被标记后值为0，修改区间内的树也要变为0，所以直接将lazytag赋给子节点的w
	tree[u+u+1].w=tree[u].lt;
	tree[u].lt=1;            //将标记去掉
}
inline void change(int u)//区间修改
{
	if(tree[u].l>=x&&tree[u].r<=y) //若该区间被待修改区间覆盖，直接将区间和清0（树要全部去掉），并打上标记
	{
		tree[u].w=0;
		tree[u].lt=0;
		return;
	}
	if(tree[u].lt!=1) down(u);//若有标记则下推
	int m=(tree[u].l+tree[u].r)/2;
	if(x<=m) change(u+u);//判断中点左右是否有待修改的点
	if(y>m) change(u+u+1);
	tree[u].w=tree[u+u+1].w+tree[u+u].w;//更新当前点的区间和
}
int main()
{
	n=read();
	m=read();
	++n;//树的位置由0~n->1~n+1
	build(1,n,1);
	while(m--)
	{
		x=read();
		y=read();
		++x,++y;
		change(1);
	}
	printf("%lld",tree[1].w);//直接输出修改后整个区间之和
	return 0;
}
