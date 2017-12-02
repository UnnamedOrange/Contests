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

const int mod=10001;
template <typename T>
struct stack:public std::stack<T>
{
	T popex()
	{
		if(std::stack<T>::empty()) return T(0);
		T ret=std::stack<T>::top();
		std::stack<T>::pop();
		return ret;
	}
};
enum
{
    left_,
    right_,
    add_,
    sub_,
    mul_,
    pow_,
    positive_,
    negative_
};
const int operand[8]= {0,0,2,2,2,2,1,1};
const bool priority[8][8]=
{
	/////	(	)	+	-	*	^	+	-
	/*(*/{	0,	0,	0,	0,	0,	0,	0,	0},
	/*)*/{	0,	0,	1,	1,	1,	1,	1,	1},
	/*+*/{	0,	0,	1,	1,	1,	1,	1,	1},
	/*-*/{	0,	0,	1,	1,	1,	1,	1,	1},
	/***/{	0,	0,	0,	0,	1,	1,	1,	1},
	/*^*/{	0,	0,	0,	0,	0,	1,	1,	1},
	/*+*/{	0,	0,	0,	0,	0,	0,	0,	0},
	/*-*/{	0,	0,	0,	0,	0,	0,	0,	0}
};
std::map<char,int> opMap;

namespace Regular
{
	int Pow(int x,int y)
	{
		if(!y) return 1;
		int temp=Pow(x,y/2);
		temp=(temp*temp)%mod;
		if(y%2) temp=temp*x%mod;
		return temp;
	}

	class analyzer
	{
	public:
		enum
		{
		    NUM,
		    OPERATOR,
		    A,
		    END
		};

	private:
		int base;
		int pos;
		std::string origin;

		int preType;
		int proofOp(int op)
		{
			if(preType==OPERATOR)
			{
				if(op==add_) return positive_;
				if(op==sub_) return negative_;
			}
			return op;
		}
		int chType(char ch)
		{
			if(ch==' ')
			{
				return END;
			}
			if(ch=='a')
			{
				return A;
			}
			if(ch>='0' && ch<='9')
			{
				return NUM;
			}
			return OPERATOR;
		}

	public:
		analyzer(int a, std::string expre) :base(a),origin(expre)
		{
			pos=0;
			preType=OPERATOR;
		}

		int next(int &recieve)
		{
			while(pos<origin.length() && origin[pos]==' ')
			{
				pos++;
			}
			if(pos==origin.length())
			{
				return END;
			}
			std::string str;
			int type=chType(origin[pos]);
			while(pos<origin.length() && chType(origin[pos])==type)
			{
				str.push_back(origin[pos]);
				pos++;
				if(type==OPERATOR) break;
			}

			if(type==A)
			{
				recieve=base;
				preType=NUM;
				return NUM;
			}
			else if(type==NUM)
			{
				sscanf(str.c_str(),"%d",&recieve);
				//printf("read:%d\n",recieve);
				preType=NUM;
				return NUM;
			}
			else if(type==OPERATOR)
			{
				recieve=opMap[str[0]];
				recieve=proofOp(recieve);
				if(recieve==right_) preType=NUM;
				else preType=OPERATOR;
				return OPERATOR;
			}
			return 0;
		}
	};

	class expression
	{
		std::string origin;

		int calc1(int op, int a)
		{
			if(op==positive_) return a%mod;
			if(op==negative_) return (-a+mod)%mod;
			return 0;
		}
		int calc2(int op, int a, int b)
		{
			if(op==add_) return (a+b)%mod;
			if(op==sub_) return (a-b+mod)%mod;
			if(op==mul_) return (a*b)%mod;
			if(op==pow_) return Pow(a,b);
			return 0;
		}

		void deal(int op, stack<int> &ovs, stack<int> &ops)
		{
			while(!ops.empty() && priority[op][ops.top()])
			{
				int opt=ops.popex();
				if(operand[opt]==1)
				{
					int reg=ovs.popex();
					ovs.push(calc1(opt,reg));
				}
				else if(operand[opt]==2)
				{
					int reg2=ovs.popex();
					int reg1=ovs.popex();
					ovs.push(calc2(opt,reg1,reg2));
				}
			}
		}

	public:
		expression(std::string expre): origin(expre)
		{
		}

		double calc(int a)
		{
			analyzer ana(a,origin);
			stack<int> ovs;
			stack<int> ops;
			int recieve;
			int type;

			ops.push(left_);
			while((type=ana.next(recieve)) != analyzer::END)
			{
				//printf("%d %d\n",type,recieve);
				if(type==analyzer::NUM)
				{
					ovs.push(recieve);
				}
				else if(type==analyzer::OPERATOR)
				{
					if(recieve==left_)
					{
						ops.push(recieve);
					}
					else if(recieve==right_)
					{
						deal(recieve,ovs,ops);
						ops.pop();
					}
					else
					{
						deal(recieve,ovs,ops);
						ops.push(recieve);
					}
				}
			}
			deal(right_,ovs,ops);
			//printf("%d\n",ovs.top());
			return ovs.popex();
		}
	};

	void run()
	{
		char buffer[1000]= {0};
		cin.getline(buffer,1000);
		std::string str(buffer);
		expression expre(str);

		cin.getline(buffer,1000);
		int number;
		number=atoi(buffer);

		for(int i=0; i<number; i++)
		{
			cin.getline(buffer,1000);
			std::string temp(buffer);
			expression comp(temp);
			bool bOk=true;
			for(int j=0; j<=5; j++)
			{
				if(expre.calc(j) != comp.calc(j))
				{
					bOk=false;
					break;
				}
			}
			if(bOk)
			{
				printf("%c",'A'+i);
			}
		}
	}
};

void input()
{

}

int main()
{
#ifndef DEBUG
	freopen("equal.in","r",stdin);
	freopen("equal.out","w",stdout);
#endif
	opMap['(']=left_;
	opMap[')']=right_;
	opMap['+']=add_;
	opMap['-']=sub_;
	opMap['*']=mul_;
	opMap['^']=pow_;
	input();
	Regular::run();
	return 0;
}
