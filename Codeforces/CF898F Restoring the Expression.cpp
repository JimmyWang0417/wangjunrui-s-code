#include <cstdio>
#include <cstring>
#define re register
#define int long long
using namespace std;
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
const int mod1=100663319,mod2=201326611,N=1e6+5;
int power1[N],power2[N],hash1[N],hash2[N];
char str[N];
int a[N],n;
inline int Hash1(int l,int r)
{
	return (hash1[r]-hash1[l-1]*power1[r-l+1]%mod1+mod1)%mod1;
}
inline int Hash2(int l,int r)
{
	return (hash2[r]-hash2[l-1]*power2[r-l+1]%mod2+mod2)%mod2;
}
inline bool check(int l,int r)
{
	if(l==r)
		return true;
	return a[l]!=0;
}
inline bool check(int pos1,int pos2,int pos3,int pos4=n)
{
	return check(pos1,pos2)&&check(pos2+1,pos3)&&check(pos3+1,pos4)&&
	       (Hash1(pos1,pos2)+Hash1(pos2+1,pos3))%mod1==Hash1(pos3+1,pos4)&&
	       (Hash2(pos1,pos2)+Hash2(pos2+1,pos3))%mod2==Hash2(pos3+1,pos4);
}
inline int solve(int pos)
{
	int len=n-pos;
	if(len<pos&&check(1,len,pos))
		return len;
	if(len<=pos&&len>1&&check(1,len-1,pos))
		return len-1;
	if(pos>len&&check(1,pos-len,pos))
		return pos-len;
	if(pos>len-1&&len>1&&check(1,pos-len+1,pos))
		return pos-len+1;
	return 0;
}
inline void print(int pos1,int pos2)
{
	for(re int i=1; i<=n; ++i)
	{
		putchar(str[i]);
		if(i==pos1)
			putchar('+');
		if(i==pos2)
			putchar('=');
	}
}
signed main()
{
	power1[0]=power2[0]=1;
	scanf("%s",str+1);
	n=strlen(str+1);
	for(re int i=1; i<=n; ++i)
	{
		a[i]=str[i]-'0';
		power1[i]=power1[i-1]*10%mod1;
		power2[i]=power2[i-1]*10%mod2;
		hash1[i]=(hash1[i-1]*10+a[i])%mod1;
		hash2[i]=(hash2[i-1]*10+a[i])%mod2;
	}
	for(re int i=(n+1)>>1; i<n; ++i)
	{
		int ans=solve(i);
		if(!ans)
			continue;
		print(ans,i);
		break;
	}
	return 0;
}
