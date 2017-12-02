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
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;
inline int readIn()
{
	int a=0;
	scanf("%d",&a);
	return a;
}

const int maxn=85;
int n,m;
int rect[maxn][maxn];

namespace Regular
{
	struct BigInt
	{
		static const int digit=1e8;
		static const int size=5;
		long long num[size];

		BigInt(int b=0)
		{
			*this=b;
		}
		int length()
		{
			for(int i=size; i>0; i--)
			{
				if(num[i-1]) return i;
			}
			return 0;
		}
		void carry()
		{
			for(int i=0; i<size-1; i++)
			{
				if(num[i]>digit)
				{
					num[i+1]+=num[i]/digit;
					num[i]%=digit;
				}
			}
		}

		BigInt operator= (int b)
		{
			memset(num,0,sizeof(num));
			num[0]=b;
			carry();
		}
		bool operator< (const BigInt &b) const
		{
			for(int i=size-1; i>=0; i--)
			{
				if(num[i]<b.num[i]) return true;
				else if(num[i]>b.num[i]) return false;
			}
			return false;
		}

		void operator*= (int b)
		{
			for(int i=0; i<size; i++)
			{
				num[i]*=b;
			}
			carry();
		}
		void operator*= (BigInt &b)
		{
			BigInt ret;
			int lengthA=length();
			int lengthB=b.length();
			for(int i=0; i<lengthA; i++)
			{
				for(int j=0; j<lengthB; j++)
				{
					ret.num[i+j]+=num[i]*b.num[j];
				}
				ret.carry();
			}
			*this=ret;
		}
		void operator+= (BigInt &b)
		{
			for(int i=0; i<size-1; i++)
			{
				num[i]+=b.num[i];
			}
			carry();
		}

		void print()
		{
			int len=length();
			if(!len)
			{
				printf("0\n");
				return;
			}
			printf("%lld",num[len-1]);
			for(int i=len-2; i>=0; i--)
			{
				printf("%08lld",num[i]);
			}
			puts("");
		}
	};

	void run()
	{
		BigInt ans;
		std::vector<BigInt> Power2(m+1);
		Power2[0]=1;
		for(int i=1; i<=m; i++)
		{
			Power2[i]=Power2[i-1];
			Power2[i]*=2;
		}

		for(int row=1; row<=n; row++)
		{
			std::vector<std::vector<BigInt> > F(m+1);
			for(int i=0; i<=m; i++) F[i].resize(m-i+2);

			for(int len=1; len<=m; len++)
			{
				int maxBegin=m-len+1;
				for(int i=1; i<=maxBegin; i++)
				{
					BigInt F1,F2;
					F1=rect[row][i+len-1];
					F1*=Power2[m-len+1];
					F1+=F[len-1][i];
					F2=rect[row][i];
					F2*=Power2[m-len+1];
					F2+=F[len-1][i+1];
					F[len][i]=std::max(F1,F2);
				}
			}
			ans+=F[m][1]; //从1开始取一个m长的线段
		}
		ans.print();
	}

	void input()
	{
		n=readIn();
		m=readIn();
		for(int i=1; i<=n; i++)
		{
			for(int j=1; j<=m; j++)
			{
				rect[i][j]=readIn();
			}
		}
	}
}


int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
