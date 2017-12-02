#include <bits/stdc++.h>
using namespace std;
char s[1000005];
int n, k;
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while (~scanf("%d%d%s", &n, &k, s))
	{
		for (int i = 0; i < n && k; i++)
		{
			if (s[i] == '2' && s[i + 1] == '3' && s[i + 2] == '3' && !(i % 2)) k %= 2;
			if (k && s[i] == '2' && s[i + 1] == '3') s[i] = s[i + 1] = (i % 2)? '3' : '2', i -= 2, k--;
		}
		puts(s);
	}
    return 0;
}
