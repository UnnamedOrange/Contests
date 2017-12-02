#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;

const int maxn=40000 + 5;
int n,m;

struct datas
{
	int x;
	int index;
	datas(int x,int index):x(x),index(index)
	{

	}
	bool operator < (const datas &b) const
	{
		return x<b.x;
	}
};
void run_O4()
{
	std::vector<datas> x;
	std::vector<int> ans[4];
	for(int i=0; i<4; i++)
	{
		ans[i].resize(m+1);
	}
	for(int i=1; i<=m; i++)
	{
		int input;
		scanf("%d",&input);
		x.push_back(datas(input,i));
	}
	sort(x.begin(),x.end());

	int object[4];
	for(object[0]=0; object[0]<m; object[0]++)
		for(object[1]=object[0]+1; object[1]<m; object[1]++)
			for(object[2]=object[1]+1; object[2]<m; object[2]++)
				for(object[3]=object[2]+1; object[3]<m; object[3]++)
				{
					if(x[object[1]].x - x[object[0]].x == 2*(x[object[3]].x - x[object[2]].x))
						if(x[object[2]].x > x[object[1]].x * 4 - x[object[0]].x * 3)
						{
							ans[0][x[object[0]].index]++;
							ans[1][x[object[1]].index]++;
							ans[2][x[object[2]].index]++;
							ans[3][x[object[3]].index]++;
						}
				}

	for(int i=1; i<=m; i++)
	{
		printf("%d %d %d %d\n",ans[0][i],ans[1][i],ans[2][i],ans[3][i]);
	}
}

void run_O4O3()
{
	std::vector<datas> x;
	std::vector<int> ans[4];
	for(int i=0; i<4; i++)
	{
		ans[i].resize(m+1);
	}
	for(int i=1; i<=m; i++)
	{
		int input;
		scanf("%d",&input);
		x.push_back(datas(input,i));
	}
	sort(x.begin(),x.end());

#define NUM(arg) x[arg].x
	for(int A=0; A<m; A++)
	{
		for(int B=A+1; B<m; B++)
		{
			for(int C=B+1; C<m ; C++)
			{
				if(NUM(C) <= 4*NUM(B)-3*NUM(A)) continue;
				for(int D=C+1; D<m; D++)
				{
					if(2*(NUM(D)-NUM(C)) > NUM(B) - NUM(A)) break;

					if(2*(NUM(D)-NUM(C)) == NUM(B) - NUM(A))
					{
						ans[0][x[A].index]++;
						ans[1][x[B].index]++;
						ans[2][x[C].index]++;
						ans[3][x[D].index]++;
					}
				}
			}
		}
	}

	for(int i=1; i<=m; i++)
	{
		printf("%d %d %d %d\n",ans[0][i],ans[1][i],ans[2][i],ans[3][i]);
	}
}

void run_Regular()
{

}

void input()
{
	scanf("%d%d",&n,&m);
}

int main()
{
#ifndef DEBUG
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
#endif
	input();
	if(m<=30)
		run_O4();
	else if(m<=40000)
		run_O4O3();
	else
		run_Regular();
	return 0;
}
