//Indirect sort + BIT
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
    bool minus = false;
    INT a = 0;
    char ch = getchar();
    while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
    if (ch == '-')
    {
        minus = true;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        a *= 10;
        a += ch;
        a -= '0';
        ch = getchar();
    }
    if (minus) a = -a;
    return a;
}

const INT mod = 99999997;
const INT maxn = 100005;
INT n;
INT height1[maxn];
INT index1[maxn];
INT height2[maxn];
INT index2[maxn];
bool comp1(const INT& a, const INT& b)
{
    return height1[a] < height1[b];
}
bool comp2(const INT& a, const INT& b)
{
    return height2[a] < height2[b];
}
INT sequence[maxn];
INT temp[maxn];

inline INT lowbit(INT x)
{
    return x & -x;
}
INT getInv()
{
    INT ans = 0;
    std::vector<INT> BIT(n + 1);
    for(int i = 0; i < n; i++)
    {
        INT x;
        x = sequence[i] + 1; //必须从1开始，所以重编码 
        while(x <= n)
        {
            BIT[x]++;
            x += lowbit(x);
        }

        INT count_ = 0;
        x = sequence[i] + 1;
        while(x > 0)
        {
            count_ += BIT[x];
            x -= lowbit(x);
        }
        ans += i + 1 - count_;
    }
    return ans;
}

void run()
{
    n = readIn();
    for (int i = 0; i < n; i++)
    {
        height1[i] = readIn();
        index1[i] = i;
    }
    for (int i = 0; i < n; i++)
    {
        height2[i] = readIn();
        index2[i] = i;
    }
    std::sort(index1, index1 + n, comp1);
    std::sort(index2, index2 + n, comp2);

    for (int i = 0; i < n; i++)
    {
        sequence[index1[i]] = index2[i];
    }
    cout << getInv() % mod << endl;
}

int main()
{
    run();
    return 0;
}
