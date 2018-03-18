#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pb push_back
#define percent(x) if(rand()%100<x)


using namespace std;

ll Rand(ll mod){return (unsigned long long)rand()*rand()*rand()*rand()%mod;}
const int base=2;
int Rand_log(int ub){return pow(base,1.0*rand()/RAND_MAX*(log(ub)/log(base)));}

#define N 55
int a[N][N];
int r,c;
void gen_rand(int _r,int _c){
	r=_r;
	c=_c;
	r-=rand()%2*rand()%int(sqrt(r));
	c-=rand()%2*rand()%int(sqrt(c));
	for (int i=1;i<=r;++i)
		for (int j=1;j<=c;++j)
			a[i][j]=rand()%3?1:0;
}

void genRand(int _r,int _c){
	r=_r;
	c=_c;
	assert(int(sqrt(r))>0);
	assert(int(sqrt(c))>0);
	r-=rand()%2*rand()%int(sqrt(r));
	c-=rand()%2*rand()%int(sqrt(c));
	for (int i=1;i<=r;++i)
		for (int j=1;j<=c;++j)
			a[i][j]=1;
	int rm=Rand_log(r*c),x,y;
	if ((rm&1)!=((r*c)&1)) ++rm;
//	printf("[debug] %d %d\n",r*c,rm);return;
	for (int i=rm-rm/2;i;--i){
		do x=rand()%r+1,y=rand()%c+1;while (((x^y)&1)==1||a[x][y]==0);
		a[x][y]=0;
	}
	for (int i=rm/2;i;--i){
		do x=rand()%r+1,y=rand()%c+1;while (((x^y)&1)==0||a[x][y]==0);
		a[x][y]=0;
	}
}

void genGood(int _r,int _c){
	r=_r;
	c=_c;
	assert(int(sqrt(r))>0);
	assert(int(sqrt(c))>0);
	r-=rand()%2*rand()%int(sqrt(r));
	c-=rand()%2*rand()%int(sqrt(c));
	for (int i=1;i<=r;++i)
		for (int j=1;j<=c;++j)
			a[i][j]=0;
	if (r==1||c==1) return;
	int nows=0;
	for (;;){
		if (nows*2>r*c){
			double p=pow(nows-r*c/2,2.1)/pow(r*c,3.5);
			percent(p*100) break;
		}
		percent(50){
			int x=rand()%(r-1)+1;
			int y=rand()%c+1,d=rand()&1?1:-1;
			bool flag=1;
			while (1<=y&&y<=c){
				if (a[x][y]+a[x+1][y]>0) break;
				y+=d;
				if (flag&&(y<1||y>c||a[x][y]+a[x+1][y]>0)) break;
				a[x][y-d]=a[x+1][y-d]=1;
				nows+=2;
//				percent(90/c) break;
				flag=0;
			}
		}
		else{
			int y=rand()%(c-1)+1;
			int x=rand()%r+1,d=rand()&1?1:-1;
			bool flag=1;
			while (1<=x&&x<=r){
				if (a[x][y]+a[x][y+1]>0) break;
				x+=d;
				if (flag&&(x<1||x>r||a[x][y]+a[x][y+1]>0)) break;
				a[x-d][y]=a[x-d][y+1]=1;
				nows+=2;
//				percent(90/r) break;
				flag=0;
			}
		}
	}
	int cnt[2]={0,0};
	for (int i=1;i<=r;++i)for (int j=1;j<=c;++j)
		if (a[i][j]) ++cnt[(i+j)&1];
	assert(cnt[0]==cnt[1]);
}

void gen(int T,int _r,int _c,int type){
	printf("%d\n",T);
	for (int t=1;t<=T;++t){
		if (t==1){
			r=_r;
			c=_c;
			for (int i=1;i<=r;++i)
				for (int j=1;j<=c;++j)
					a[i][j]=1;
		}
		else if (t==2){
			r=_r;
			c=1;
			for (int i=1;i<=r;++i)
				a[i][1]=rand()&1;
		}
		else if (t==3){
			r=_r;
			c=1;
			for (int i=1;i<=r;++i)
				a[i][1]=0;
		}
		else{
			percent(5) gen_rand(_r,_c);
			else percent(40) genRand(_r,_c);
			else genGood(_r,_c);
		}
		
		printf("%d %d\n",r,c);
		for (int i=1;i<=r;++i)
			for (int j=1;j<=c;++j){
				if (type==0){
					percent(75) a[i][j]*=2;
				}
				printf("%d",a[i][j]);
				if (j==c) puts("");
				else putchar(' ');
			}
	}
}

int main(int argc,char **argv){
	unsigned int seed=argc>1?atoi(argv[1]):time(0);
	srand(seed);
	freopen("seed.txt","w",stdout);
	printf("%u\n",seed);
	fclose(stdout);
	const int start=1;
	const int cas=20;
/*	const int T[cas]={200,200,200,200,200,200,200,200,10,10,10,10,200,200,200,200,200,200,200,200};
	const int n[cas]={30,30,30,30,30,30,30,30,20,20,30,30,30,30,30,30,30,30,30,30};
	const int m[cas]={2,2,7,7,7,7,7,7,20,20,30,30,30,30,30,30,30,30,30,30};*/
	for (int t=0;t<cas;++t){
		char fname[23];
		int index=t+start;
		sprintf(fname,"%d.in",index);
		freopen(fname,"w",stdout);
		int T,n,m,type;
		T=9<=index&&index<=12?5:100;
		n=9<=index&&index<=10?20:25;
		m=index<=2?2:(index<=8?7:n);
		type=13<=index&&index<=19?1:0;
		gen(T,n,m,type);
		fclose(stdout);
	}
	return 0;
}
