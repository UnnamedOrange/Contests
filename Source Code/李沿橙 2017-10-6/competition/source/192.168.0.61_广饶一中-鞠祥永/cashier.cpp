#include<cstdio>
#include<cstring>
inline int min_(int x,int y){return x<y?x:y;}
inline int max_(int x,int y){return x>y?x:y;}
int test;
int a[24],b[24],c[24];
int main(){
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	scanf("%d",&test);
	int x,y;
	bool no;
	while(test--){
		y=no=0;
		for(int i=0;i<24;i++) scanf("%d",&a[i]);
		for(int i=0;i<24;i++) scanf("%d",&b[i]);
		memset(c,0,sizeof(c));
		for(int i=0;i<24;i++)
		if(a[i]>c[i]){
			for(int j=i;a[i]>c[i]&&j>max_(-1,i-8);j--)
			if(b[j]){
				x=min_(a[i]-c[i],b[j]);
				b[j]-=x,y+=x;
				for(int k=min_(23,j+7);k>=i;k--) c[k]+=x;
			}
			if(a[i]>c[i]){
				no=1;
				break;
			}
		}
		if(no) puts("-1");
		else printf("%d\n",y);
	}
	return 0;
}
