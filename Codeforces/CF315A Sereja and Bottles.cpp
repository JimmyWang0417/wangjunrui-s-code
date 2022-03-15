#include<cstdio>
#define re register
const int N=105,M=1005;
int where[M],f[M],n,a[N];
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
	{
		int b;
		scanf("%d%d",&a[i],&b);
		++f[b];
		where[b]=i;
	}
	int ans=n;
	for(re int i=1; i<=n; ++i)
		if(f[a[i]]>1||f[a[i]]==1&&where[a[i]]!=i)
			--ans;
	printf("%d\n",ans);
	return 0;
}
