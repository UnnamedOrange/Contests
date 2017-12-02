#include<cstdio>
#include<cstring>
#define MAXH 1048
#define MAXS 10000000
using namespace std;
const short pows[10]={1,2,4,8,16,32,64,128,256,512};
int h[MAXH];
long long sum[MAXS];
inline void hash(int tar){
	bool tem[10];
	memset(tem,false,sizeof(tem));
	while(tar){
		tem[tar%10]=true;
		tar/=10;
	}
	short ha=0;
	for(int i=0;i<=9;i++) if(tem[i]) ha+=pows[i];
	h[ha]++;
}
int get_sum(int tar){
	if(!tar) return 0;
	if(sum[tar]) return sum[tar];
	return sum[tar]=get_sum(tar-1)+tar;
}
int n;
int main(){
	freopen("number.in","r",stdin),freopen("number.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) hash(i);
	long long ans=0;
	for(int i=1;i<=1024;i++) ans+=(h[i])?(get_sum(h[i]-1)):(0);
	printf("%lld",ans);
	fclose(stdin),fclose(stdout);
	return 0;
}
