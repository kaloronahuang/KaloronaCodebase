#include <iostream>
#include <queue>

using namespace std;

struct point
{
    int x, y;
    int depth = -1;
    char type;
};

bool compare(point a, point b)
{
    return (a.x == b.x) && (a.y == b.y) && (a.type == b.type);
}

int BFS(int n, int m)
{
    // declaration & I/O;
    point map[n + 2][m + 2];
    point startP;
    point endP;
    for (int i = 0; i < n + 2; i++)
    {
        for (int j = 0; j < m + 2; j++)
        {
            if (i == 0 || i == n + 1 || j == 0 || j == m + 1)
            {
                map[i][j].x = i;
                map[i][j].y = j;
                map[i][j].type = 'X';
            }
            else
            {
                cin >> map[i][j].type;
                map[i][j].x = i;
                map[i][j].y = j;
                if (map[i][j].type == 'S')
                    startP = map[i][j];
                else if (map[i][j].type == 'T')
                    endP = map[i][j];
            }
        }
    }
    // process;
    int currentDepth = 0;
    queue<point> nextq;
    nextq.push(startP);
    while (!nextq.empty())
    {
        currentDepth++;
        int maxQ = nextq.size();
        if (maxQ == 1 && nextq.front().type == 'T')
            if(nextq.front().depth != -1)
                return nextq.front().depth;
            else
                return currentDepth;
        for (int j = 0; j < maxQ; j++)
        {
            point currentPoint = nextq.front();
            if (nextq.size() == 1 && nextq.front().type == 'T')
                return currentPoint.depth;
            nextq.pop();
            point surrounding[4];
            surrounding[0] = map[currentPoint.x - 1][currentPoint.y]; // up;
            surrounding[1] = map[currentPoint.x][currentPoint.y + 1]; // right;
            surrounding[2] = map[currentPoint.x + 1][currentPoint.y]; // down;
            surrounding[3] = map[currentPoint.x][currentPoint.y - 1]; // left;

            for (int i = 0; i < 4; i++)
            {
                point currentPoint = surrounding[i];
                if (currentPoint.type != 'X' && currentPoint.depth == -1)
                {
                    // opt;
                    currentPoint.depth = currentDepth;
                    map[currentPoint.x][currentPoint.y].depth = currentDepth;
                    nextq.push(currentPoint);
                }
            }
        }
    }
    return -1;
}

int main()
{
    int n, m, t;
    cin >> n >> m >> t;
    int steps = BFS(n, m);
    if (steps > t || steps == -1)
        cout << "NO";
    else if (steps <= t)
        cout << "YES";
    return 0;
}