#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<map>
#include<queue>
#include<string>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
typedef long long ll;
using namespace std;
int main()
{	freopen("photo.in","r",stdin);
	freopen("photo.out","w",stdout);
	srand(time(0));
	cout<<((rand()*rand()%rand()+rand()*233)/rand()+rand())%100+1<<endl;
	return 0;
}

