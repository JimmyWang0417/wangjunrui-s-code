#include<cstdio>
#include<algorithm>
using namespace std;
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}
const int N=1e6+5;
class heap
{
	private:
		int heap[N],heap_size;
		int n;
	public:
		inline void push(int val)
		{
			heap[++heap_size]=val;
			int nxt,now=heap_size;
			while(now>1)
			{
				nxt=now>>1;
				if(heap[nxt]<=heap[now])
					break;
				swap(heap[nxt],heap[now]);
				now=nxt;
			}
		}
		inline void pop()
		{
			heap[1]=heap[heap_size--];
			int nxt,now=1;
			while((now<<1)<=heap_size)
			{
				nxt=now<<1;
				if(nxt<heap_size&&heap[nxt+1]<heap[nxt])
					++nxt;
				if(heap[now]<=heap[nxt])
					break;
				swap(heap[nxt],heap[now]);
				now=nxt;
			}
		}
		inline void work()
		{
			read(n);
			while(n--)
			{
				int opt;
				read(opt);
				if(opt==1)
				{
					int x;
					read(x);
					push(x);
				}
				else if(opt==2)
					printf("%d\n",heap[1]);
				else if(opt==3)
					pop();
			}
		}
} h;
int main()
{
	h.work();
	return 0;
}
