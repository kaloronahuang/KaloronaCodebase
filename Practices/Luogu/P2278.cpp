// P2278.cpp
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

struct taskInfo
{
    int pid, arrTime, lastTime, priority;

    taskInfo() {}
    taskInfo(int p, int a, int l, int pri) : pid(p), arrTime(a), lastTime(l), priority(pri){};

    bool operator<(const taskInfo &b) const
    {
        if (arrTime == b.arrTime)
            return priority > b.priority;
        return arrTime < b.arrTime;
    }
};

struct interval
{
    int st, ed, pri, pid;

    interval() {}
    interval(int sttime, int edtime, int pr, int pid_) : st(sttime), ed(edtime), pri(pr), pid(pid_X) {}
};

int n = 0;
priority_queue<taskInfo> ts;

void init()
{
    int a, b, c, d;
    vector<interval> ints;
    while (scanf("%d%d%d%d", &a, &b, &c, &d) != EOF)
    {
        taskInfo curt = taskInfo(a, b, c, d);
    }
}

void solve()
{
    vector<interval> intervals;
    while (!ts.empty())
    {
        taskInfo curt = ts.top();
        interval last = intervals.front();
        if (intervals.empty())
        {
            intervals.push_back(interval(curt.arrTime, curt.arrTime + curt.lastTime, curt.priority, curt.pid));
            ts.pop();
            continue;
        }
        else
        {
            // if the start time is behind the end time;
            if (last.ed <= curt.arrTime)
                // push into the queue;
                intervals.push_back(interval(curt.arrTime, curt.arrTime + curt.lastTime, curt.priority, curt.pid)),
                    ts.pop();
            else if (last.pri < curt.priority)
            {
                // force to insert it;
                int i = intervals.size() - 1;
                for (; i > -1; i--)
                    if (intervals[i].pri > curt.priority || intervals[i].ed <= curt.arrTime)
                    {
                        i++;
                        break;
                    }
                if (i == intervals.size())
                    intervals.push_back(interval(last.ed, last.ed + curt.lastTime, curt.priority, curt.pid));
                else
                {
                    queue<interval> subseq;
                    subseq.push(interval(intervals[i].st, intervals[i].st + curt.lastTime, intervals[i].pri, intervals[i].pid));
                    subseq.push(interval(curt.arrTime, curt.arrTime + curt.lastTime, curt.priority, curt.pid));
                    subseq.push(interval(curt.arrTime + curt.lastTime+1,))
                    int siz = intervals.size();
                    int lastTimePost = curt.arrTime + curt.lastTime;
                    for (int j = i+1; j < siz; j++)
                
                }
            }
        }
    }
}