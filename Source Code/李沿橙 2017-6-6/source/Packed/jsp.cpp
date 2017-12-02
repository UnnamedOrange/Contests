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

int nMachine, nJob, nTotalSteps;

struct Step
{
	int job;
	int time;
	int machine;

	Step(int job=0,int time=0,int machine=0):job(job),time(time),machine(machine)
	{

	}
};

std::vector<Step> steps(1);
int order[25][25];
int countOfSteps[25];

struct Status
{
	int from;
	int to;
	int job;

	Status(int from=0,int to=0,int job=0):from(from), to(to), job(job)
	{

	}

	bool operator< (const Status &b) const
	{
		return from<b.from;
	}
};

std::vector<Status> machines[25];
int queueStatus[25];
//int lastStep[25];
int lastTime[25];

namespace Regular
{
	void run()
	{
		for(int i=1; i<=nTotalSteps; i++)
		{
			int minStartTime=lastTime[steps[i].job];

			int specificMachine=steps[i].machine;
			int length=steps[i].time;
			int tempLast=0;
			for(int j=0; j<machines[specificMachine].size(); j++)
			{
				if(machines[specificMachine][j].from - tempLast >= length &&
				        minStartTime+length<=machines[specificMachine][j].from)
				{
					break;
				}
				tempLast=machines[specificMachine][j].to;
			}
			minStartTime=std::max(minStartTime, tempLast);

			int minFinishTime=minStartTime+length;

			machines[specificMachine].push_back(Status(minStartTime,minFinishTime,steps[i].job));
			std::sort(machines[specificMachine].begin(),machines[specificMachine].end());
			lastTime[steps[i].job]=minFinishTime;
			queueStatus[specificMachine]=std::max(queueStatus[specificMachine],minFinishTime);
		}
		printf("%d\n",*std::max_element(queueStatus+1,queueStatus+1+nMachine));

//		for(int i=1; i<=nMachine; i++)
//		{
//			for(int j=0; j<machines[i].size(); j++)
//			{
//				printf("(%d: %d, %d) ",machines[i][j].job,machines[i][j].from,machines[i][j].to);
//			}
//			puts("");
//		}
	}
	void input()
	{
		scanf("%d%d",&nMachine,&nJob);
		nTotalSteps = nMachine*nJob;
		for(int i=1; i<=nTotalSteps; i++)
		{
			int input;
			scanf("%d",&input);
			order[input][++countOfSteps[input]] = i;
			steps.push_back(Step(input));
		}

		for(int i=1; i<=nJob; i++)
		{
			for(int j=1; j<=nMachine; j++)
			{
				scanf("%d", &steps[order[i][j]].machine);
			}
		}

		for(int i=1; i<=nJob; i++)
		{
			for(int j=1; j<=nMachine; j++)
			{
				scanf("%d", &steps[order[i][j]].time);
			}
		}

//		for(int i=1;i<=nTotalSteps;i++)
//		{
//			printf("Step %d: M:%d T:%d j:%d\n",i,steps[i].machine,steps[i].time,steps[i].job);
//		}
	}
}

int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
