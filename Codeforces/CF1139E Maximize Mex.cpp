#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
using namespace std;
int n,m;
string a[101];
int ch[2000001][27];
int tot;
int p;
bool vis[2000001];
string b;
int main(){
	freopen("paragraph.in","r",stdin);
	freopen("paragraph.out","w",stdout);
	ios::sync_with_stdio(false);
	scanf("%d%d",&n,&m);
	int len;
	int u;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		len=a[i].size();
		p=0;
		for (int j=0;j<len;j++){
			u=a[i][j]-96;
			if (!ch[p][u]){
				tot++;
				ch[p][u]=tot;
			}	
			p=ch[p][u];
			if (j==len-1){
				vis[p]=1;
			}
		}
	}
	int ans=0;
	for (int i=1;i<=m;i++){
		ans=0;
		p=0;
		cin>>b;
		len=b.size();
		for (int j=0;j<len;j++){
			u=b[j]-96;
			if (!ch[p][u] && ans!=j){
				break;
			}
			else if (!ch[p][u]){
				p=0;
			}
			if (!ch[p][u]){
				break;
			}
			p=ch[p][u];
			if (vis[p]){
				ans=j+1;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
} 
