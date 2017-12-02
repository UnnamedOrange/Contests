#include<cstdio>
#include<cstring>
const int maxn=1e6+10;
int n,k;
char ch[maxn];
int main(){
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while(scanf("%d%d",&n,&k)!=EOF){
		scanf("%s",1+ch);
		int a=1;
		while(k--){
			while((ch[a]!='2'||ch[a+1]!='3')&&a<=n) a++;
			if(a>n) break;
			if(a&1){
				if(ch[a+2]=='3') k&=1;
				ch[a+1]='2';
			}
			else{
				ch[a]='3';
				a--;
			}
		}
		printf("%s\n",1+ch);
	}
	return 0;
} 
