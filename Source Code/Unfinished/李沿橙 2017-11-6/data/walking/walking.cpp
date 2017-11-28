#include <iostream>
#include <vector>
using namespace std;
vector<long long> adj[1000010];
double down[1000010];
double up[1000010];
long long childcnt[1000010];
long long n,x,y;
vector<long long> tim;
double dfs(long long pos, long long par){
	long long cnt=0;
	double tot = 0;
	for(long long i : adj[pos]){
		if(i==par)	continue;
		cnt++;
		tot+=dfs(i,pos);
	}
	double val = 0;
	if(cnt>0)	tot/=cnt;
	down[pos]=val+tot;
	childcnt[pos]=cnt;
	return down[pos]+tim[pos];
}
 
void dfs1(long long pos, long long par){
	up[pos]=tim[par];
	double val = down[par];
	val*=childcnt[par];
	val-=tim[pos];
	val-=down[pos];
	val+=up[par];
	if(par==1){
		if(childcnt[par]>1)
			val/=(childcnt[par]-1);
	}
	else{
		if(childcnt[par]>0)
			val/=(childcnt[par]);
	}
	up[pos]+=val;
	for(long long i : adj[pos]){
		if(i==par)	continue;
		dfs1(i,pos);
	}
}
int main() {
	cin>>n;
	tim.resize(n+1);
	for(long long i = 1 ; i<=n ; i++)	cin>>tim[i];
	for(long long i = 1; i<n ; i++){
		cin>>x>>y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs(1,1);
	up[1]=0;
	for(long long i : adj[1])
		dfs1(i,1);
	double minval = 1e200;
	double minpos = -1;
	for(long long i = 1; i<=n; i++){
		double val = 0.0;
		if(childcnt[i]==0) val = up[i]+tim[i];
		else if(i==1)	val=down[i]+tim[i];
		else{
			val = down[i]*childcnt[i];
			val+=up[i];
			val/=(childcnt[i]+1);
			val+=tim[i];
		}
		if(val<minval){
			minval = val;
			minpos = i;
		}
	}
	cout<<minpos;
	return 0;
}
