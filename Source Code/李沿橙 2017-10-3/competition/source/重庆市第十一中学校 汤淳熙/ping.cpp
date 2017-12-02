#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <ctime>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

/*

n 个站点，m 条路，k 对点之间不连通


 */

struct Vtx {
	Vtx *Next;
    int To;

	Vtx(void) : Next(NULL) {}
};

struct VtxHead : Vtx {
	Vtx *Head;

	void operator += (int To)
	{
        if (Head == NULL) {
            Next = new Vtx();
            Next->To = To;
            Head = Next;
        } else {
            Next->Next = new Vtx();
            Next = Next->Next;
            Next->To = To;
        }
	}

	VtxHead(void) : Head(NULL);
};

int main(void)
{
#ifndef LOCAL
	freopen("ping.in", "r", stdin);
	freopen("ping.out", "w", stdout);
#endif // LOCAL




    return 0;
}
