#include<cstdio>
#include<cstdlib>
using namespace std;
#define MAXN 1000+5
typedef long long LL;
/*int read()
{
    int x=0; char ch=getchar();
    bool flag=0;
    while (ch<'0'||ch>'9') { if (ch=='-') flag=1; ch=getchar(); }
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    if (flag) return -x; else return x;
}*/
int n,a[MAXN+1];
bool book[MAXN+1];
LL tot;
void dfs(int step)
{
	if(step == n+1){
		tot++;
			for(int i=1;i<= n-1;i++){
				if(a[i] - a[i+1] >= 2){//前后两项之差 
					tot--;
						break;
				}
			}
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		if(book[i] == false)
		{
			book[i] = true;
			a[step] = i;
			//step++;
			dfs(step+1);
			book[i] = false;
			//step--;	
		}	
	}
}
int main()
{
	freopen("stack.in","r",stdin);
    freopen("stack.out","w",stdout);
	scanf("%d",&n);
	//n = read();
	/*for(int now=1;now<=n;now++){
		dfs(1,now);
		//printf("%d ",tot);
	}
	*/
	dfs(1);
	tot++;
	tot = tot %7;
	printf("%lld",tot);//注意是lld 
	return 0;
}
