// 7221
// NOIp: Search

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct point
{
    int x, y;
    char type = '#';
    vector<int> diax;
    vector<int> diay;
    int depth = -1;
};

vector<point *> portals;
int R, C, K;
point mat[200][200];

void search()
{
    queue<point> ps;
    ps.push(mat[1][1]);
    int currentDepth = 0;
    while (!ps.empty())
    {
        point currentPoint = ps.front();
        currentPoint.depth++;
        point surrounding[4] = {
            mat[currentPoint.x - 1][currentPoint.y],
            mat[currentPoint.x + 1][currentPoint.y],
            mat[currentPoint.x][currentPoint.y - 1],
            mat[currentPoint.x][currentPoint.y + 1],
        };
        for (int i = 0; i < 4; i++)
        {
            if(surrounding[i].type!='#')
            {
                if(surrounding[i].type == '.')
                    ps.push(surrounding[i]);
                else if(surrounding.type == 'E')
                    return;
            }
        }
    }
}

int main()
{
    int T;
    cin >> T;
    for (int testBatch = 0; testBatch < T; testBatch++)
    {
        // do the real I/O;
        cin >> R >> C >> K;
        for (int i = 0; i <= R + 1; i++)
            for (int j = 0; j <= C + 1; j++)
            {

                point p;
                p.x = i;
                p.y = j;
                if (i != 0 && i != R + 1 && j != 0 && j != C + 1)
                    cin >> p.type;
                if (p.type == '$')
                    portals.push_back(p);
                mat[i][j] = p;
            }
        // calculate;
    }
    return 0;
}