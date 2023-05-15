#include <queue>
#include <iostream>

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

void BFS_Mazu()
{
    // I/O part;
    int n, m;
    cin >> n >> m;
    point mazu_map[n + 2][m + 2];
    point startP;
    point endP;
#pragma region MapIO
    for (int i = 0; i < n + 2; i++)
    {
        for (int j = 0; j < m + 2; j++)
        {
            if (i == 0 || i == n + 1 || j == 0 || j == m + 1)
            {
                mazu_map[i][j].x = i;
                mazu_map[i][j].y = j;
                mazu_map[i][j].type = 'X';
            }
            else
            {
                cin >> mazu_map[i][j].type;
                mazu_map[i][j].x = i;
                mazu_map[i][j].y = j;
                if (mazu_map[i][j].type == 'S')
                    startP = mazu_map[i][j];
                else if (mazu_map[i][j].type == 'T')
                    endP = mazu_map[i][j];
            }
        }
    }
#pragma endregion

    queue<point> nextQ;
    nextQ.push(startP);

    int currentDepth = 0;
    while (!nextQ.empty())
    {
        currentDepth++;
        int limit = nextQ.size();
        if (limit == 1)
            if (compare(nextQ.front(), endP))
            {
                cout << "Yes;Distance is:" << nextQ.front().depth;
                return;
            }
        for (int i = 0; i < limit; i++)
        {
            point currentPivot = nextQ.front();
            nextQ.pop();
            point surrounding[4];
            surrounding[0] = mazu_map[currentPivot.x - 1][currentPivot.y];
            surrounding[1] = mazu_map[currentPivot.x + 1][currentPivot.y];
            surrounding[2] = mazu_map[currentPivot.x][currentPivot.y + 1];
            surrounding[3] = mazu_map[currentPivot.x][currentPivot.y - 1];
            // judge to add;
            for (int k = 0; k < 4; k++)
            {
                if (surrounding[k].depth == -1 && surrounding[k].type != 'X')
                {
                    point currentPros = surrounding[k];
                    mazu_map[currentPros.x][currentPros.y].depth = currentDepth;
                    surrounding[k].depth = currentDepth;
                    //cout << "I pushed:(" << surrounding[k].x << "," << surrounding[k].y << ")" << endl;
                    nextQ.push(surrounding[k]);
                }
            }
        }
    }
    cout << "No";
    return;
}

int main()
{
    BFS_Mazu();
    return 0;
}