#include <iostream>
#include <queue>

using namespace std;

struct point
{
    int x, y;
    char type;
    int depth = -1;
};

bool compare(point a, point b)
{
    return (a.x == b.x) && (a.y == b.y) && (a.type == b.type);
}

int maze()
{
    // I/O & preprocessing;
    int n, m;
    cin >> n >> m;
    point map[n + 2][m + 2];
    point startP, endP;
    for (int i = 0; i < n + 2; i++)
    {
        for (int j = 0; j < m + 2; j++)
        {
            map[i][j].x = i;
            map[i][j].y = j;
            if (i == 0 || i == n + 1 || j == 0 || j == m + 1)
            {
                map[i][j].type = 'X';
            }
            else
            {
                cin >> map[i][j].type;
                if (map[i][j].type == 'S')
                    startP = map[i][j];
                else if (map[i][j].type == 'T')
                    endP = map[i][j];
            }
        }
    }

    queue<point> nextq;
    nextq.push(startP);
    int currentDepth = 0;
    while (!nextq.empty())
    {
        currentDepth++;
        int limit = nextq.size();
        if (limit == 1 && nextq.front().type == 'T')
            if (nextq.front().depth == -1)
                return currentDepth;
            else
                return nextq.front().depth;
        for (int i = 0; i < limit; i++)
        {
            point pivot = nextq.front();
            nextq.pop();
            point surrounding[4];
            surrounding[0] = map[pivot.x - 1][pivot.y]; // up;
            surrounding[1] = map[pivot.x][pivot.y + 1]; // right;
            surrounding[2] = map[pivot.x + 1][pivot.y]; // down;
            surrounding[3] = map[pivot.x][pivot.y - 1]; // left;
            for(int j = 0;j<4;j++)
            {
                if(surrounding[j].depth == -1 && surrounding[j].type != 'X')
                {
                    point currentPoint = surrounding[j];
                    currentPoint.depth = currentDepth;
                    nextq.push(currentPoint);
                    map[currentPoint.x][currentPoint.y] = currentPoint;
                }
            }
        }
    }
    return -1;
}

int main()
{
    cout << maze() + 1;
    return 0;
}