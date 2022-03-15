
// Problem : SP688 SAM - Toy Cars
// Contest : Luogu
// URL : https://www.luogu.com.cn/problem/SP688
// Memory Limit : 0 MB
// Time Limit : 1070 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
using std::priority_queue;
using std::pair;
using std::make_pair;
using std::swap;
typedef pair<int,int> node;
const int N=5e5+5;
struct Heap
{
	node heap[N];
	int heapsize;
	int pos[N];
	inline void push(node x)
	{
		heap[++heapsize]=x;
		pos[x.second]=heapsize;
		int now=heapsize,nxt;
		while(now>1)
		{
			nxt=now>>1;
			if(heap[nxt]>=heap[now])
				break;
			swap(pos[heap[nxt].second],pos[heap[now].second]);
			swap(heap[nxt],heap[now]);
			now=nxt;
		}
	}
	inline void pop()
	{
		pos[heap[1].second]=0;
		heap[1]=heap[heapsize];
		pos[heap[heapsize--].second]=1;
		int now=1,nxt;
		while((nxt=now<<1)<=heapsize)
		{
			if(nxt<heapsize&&heap[nxt]<heap[nxt+1])
				++nxt;
			if(heap[now]>=heap[nxt])
				break;
			swap(pos[heap[nxt].second],pos[heap[now].second]);
			swap(heap[now],heap[nxt]);
			now=nxt;
		}
	}
	inline void update(node x)
	{
		if(!pos[x.second])
			return;
		int now=pos[x.second],nxt;
		heap[now]=x;
		while(now>1)
		{
			nxt=now>>1;
			if(heap[nxt]>=heap[now])
				break;
			swap(pos[heap[nxt].second],pos[heap[now].second]);
			swap(heap[nxt],heap[now]);
			now=nxt;
		}
	}
	inline void clear()
	{
		memset(pos,0,sizeof(pos));
		heapsize=0;
	}
} heap;
int a[N],head[N],nxt[N];
inline void work()
{
	int n,k,p;
	read(n,k,p);
	for(re int i=1; i<=p; ++i)
	{
		read(a[i]);
		nxt[head[a[i]]]=i;
		head[a[i]]=i;
	}
	for(re int i=1; i<=p; ++i)
		if(!nxt[i])
			nxt[i]=p+1;
	int ans=0;
	for(re int i=1; i<=p; ++i)
	{
		if(heap.pos[a[i]])
			heap.update(make_pair(nxt[i],a[i]));
		else
		{
			if(heap.heapsize==k)
				heap.pop();
			heap.push(make_pair(nxt[i],a[i]));
			++ans;
		}
	}
	printf("%d\n",ans);
	heap.clear();
	memset(nxt,0,sizeof(nxt));
	memset(head,0,sizeof(head));
}
signed main()
{
//	freopen("toy.in","r",stdin),freopen("toy.out","w",stdout);
	work();
	return 0;
}


