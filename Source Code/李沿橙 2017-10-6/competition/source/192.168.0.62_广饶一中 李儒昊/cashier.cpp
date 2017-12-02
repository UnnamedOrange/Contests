#include<cstdio>
#include<cstring>
#include<iostream>

#define N 25

using namespace std;
int T, x, y, tag;
int hahahahahahahahahah[N], hahahahahahahahhahahah[N], hahahahaha[N];
int main()
{
    freopen("cashier.in", "r", stdin);
    freopen("cashier.out", "w", stdout);
    scanf("%d", &T);

    while(T--)
    {
        y = tag = 0;

        for(int i = 0; i < 24; i++) scanf("%d", &hahahahahahahahahah[i]);

        for(int i = 0; i < 24; i++) scanf("%d", &hahahahahahahahhahahah[i]);

        memset(hahahahaha, 0, sizeof(hahahahaha));

        for(int i = 0; i < 24; i++)
            if(hahahahahahahahahah[i] > hahahahaha[i])
            {
                for(int j = i; hahahahahahahahahah[i] > hahahahaha[i] && j > max(-1, i - 8); j--)
                    if(hahahahahahahahhahahah[j])
                    {
                        x = min(hahahahahahahahahah[i] - hahahahaha[i], hahahahahahahahhahahah[j]);
                        hahahahahahahahhahahah[j] -= x, y += x;

                        for(int k = min(23, j + 7); k >= i; k--) hahahahaha[k] += x;
                    }

                if(hahahahahahahahahah[i] > hahahahaha[i])
                {
                    tag = 1;
                    break;
                }
            }

        if(tag) puts("-1");
        else printf("%d\n", y);
    }

    return 0;
}
