#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <set>
using namespace std;
inline int read() {
	int X=0,w=1;
	char ch=0;
	while(ch<'0' || ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
	return X*w;
}
int n,k,t;
char c[1000001];
int main() {
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while(~scanf("%d %d",&n,&k)) {
		scanf("%s",&c);
		for(int i=0; i<n; i++) {
			if(k==0) break;
			if(c[i]=='2' && c[i+1]=='3' &&k>0) {
				k--;
				if((i+1+2)%2==1	) 	c[i+1]='2';
				else {
					c[i]='3';
					if(c[i-1]=='2' && i-2>=-1) {
						i=i-2;
					}
				}
			}
		}
		puts(c);
	}
	return 0;
}
