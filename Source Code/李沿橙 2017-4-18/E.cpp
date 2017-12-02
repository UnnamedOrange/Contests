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

char S[305];
int length;
char S1[30];
int length1;
char S2[15];
int length2;

int main()
{
#define END {\
		printf("-1");\
		return 0;}
	scanf("%s",S);
	strcpy(S1,strchr(S,',')+1);
	*strchr(S,',')='\0';
	strcpy(S2,strchr(S1,',')+1);
	*strchr(S1,',')='\0';

	length=strlen(S);
	length1=strlen(S1);
	length2=strlen(S2);

	char *found1=strstr(S,S1);
	if(!found1)
		END;
	char *found2=strstr(S,S2);
	if(!found2)
		END;
	while(char *temp = strstr(found2+length2,S2))
	{
		found2=temp;
	}

	if(found1+length1>found2) END;
	printf("%d",(int)(found2-found1-length1));
	return 0;
}
