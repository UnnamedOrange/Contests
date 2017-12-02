#include <iostream>
#include <cstdio>
#include <cstdlib>
#define N 222222

long long x[N], y[N];

template<typename T>void Sort(T* l, T* r)
{
    --r;
    T x = *(l + (r - l) / 2);
    T *i = l, *j = r;
    while (i < j) {
        while (*i < x) ++i;
        while (x < *j) --j;
        if (i <= j) {
            T tmp = *i;
            *i = *j;
            *j = tmp;
            ++ i, -- j;
        }
    }
    if (l < j) Sort(l, j + 1);
    if (i < r) Sort(i, r + 1);
}

int getint()
{
	char ch;
	do
	{
		ch=getchar();
	}while (ch!='-'&&(ch<'0'||ch>'9'));
	int ans=0,f=0;
	if (ch=='-') f=1; else ans=ch-'0';
	while (isdigit(ch=getchar())) ans=ans*10+ch-'0';
	if (f) ans*=-1;
	return ans;
}

int main() {
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
	int n = getint();
	for (int i = 1; i <= n; i++) x[i] = getint();
	for (int i = 1; i <= n; i++) y[i] = getint();
	Sort(&x[1], &x[n + 1]);
	Sort(&y[1], &y[n + 1]);
	int m = getint();
	for (int i = 1; i <= m; i++) {
		int xx = getint(), yy = getint();
		int l = 1, r = n;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if ((long long)x[mid] * yy + (long long)y[mid] * xx >= (long long)x[mid] * y[mid]) l = mid;
			else r = mid - 1;
		}
		if ((long long)x[l] * yy + (long long)y[l] * xx >= (long long)x[l] * y[l]) printf("%d\n", l);
		else printf("%d\n", 0);
	}
	return 0;
}
