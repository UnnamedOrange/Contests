#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <map>
using std::cin;
using std::cout;
using std::endl;

class REAL
{
	static const int maxn=105;
	signed char ip[maxn];
	signed char fp[maxn];

	int ilength() const
	{
		for(int i=maxn-1; i>=0; i--)
		{
			if(ip[i])
			{
				return i+1;
			}
		}
		return 0;
	}

	int flength() const
	{
		for(int i=maxn-1; i>=0; i--)
		{
			if(fp[i])
			{
				return i+1;
			}
		}
		return 0;
	}

public:
	REAL()
	{
		memset(ip,0,sizeof(ip));
		memset(fp,0,sizeof(fp));
	}

	friend std::istream& operator >> (std::istream &in, REAL &num)
	{
		char buffer[maxn];
		scanf("%s",buffer);
		int length=strlen(buffer);
		int dot=length;
		for(int i=0; i<length; i++)
		{
			if(buffer[i]=='.')
			{
				dot=i;
				break;
			}
		}

		for(int i=dot-1,j=0; i>=0; i--,j++)
		{
			num.ip[j]=buffer[i]-'0';
		}

		for(int i=dot+1,j=0; i<length; i++,j++)
		{
			num.fp[j]=buffer[i]-'0';
		}
		return in;
	}

	friend std::ostream& operator << (std::ostream &out, const REAL &num)
	{
		int ilength=num.ilength();
		int flength=num.flength();
		for(int i=ilength-1; i>=0; i--)
		{
			printf("%d",num.ip[i]);
		}
		if(!ilength) printf("0");
		if(!flength) return out;
		printf(".");
		for(int i=0; i<flength; i++)
		{
			printf("%d",num.fp[i]);
		}
		return out;
	}

	REAL operator + (const REAL &b) const
	{
		REAL ret;
		for(int i=0; i<maxn; i++)
		{
			ret.ip[i]=ip[i]+b.ip[i];
			ret.fp[i]=fp[i]+b.fp[i];
		}

		for(int i=maxn-1; i>=0; i--)
		{
			if(i!=0)
			{
				ret.fp[i-1]+=ret.fp[i]/10;
			}
			else
			{
				ret.ip[0]+=ret.fp[i]/10;
			}
			ret.fp[i]%=10;
		}

		for(int i=0; i<maxn; i++)
		{
			if(i!=maxn-1)
			{
				ret.ip[i+1]+=ret.ip[i]/10;
			}
			ret.ip[i]%=10;
		}
		return ret;
	}
};
char num[2][105];
int length[2];

int main()
{
	REAL real1,real2;
	cin>>real1>>real2;
	cout<<real1+real2;
	return 0;
}
