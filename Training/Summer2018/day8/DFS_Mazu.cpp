// DFS
#include <iostream>
#include <stack>

using namespace std;

struct PointInfo
{
    char type;
    bool isVisited = false;
    int x;
    int y;
};

// Mazu;
void DFS_Mazu()
{
    // inp;
    int n, m;
    cin >> n >> m;
    PointInfo mazu_map[n + 2][m + 2];
    PointInfo startPoint;
    PointInfo endPoint;
    // put walls;
    for (int i = 0; i < n + 2; i++)
    {
        for (int j = 0; j < m + 2; j++)
        {
            if (i == 0 || i == n + 1)
                mazu_map[i][j].type = 'X';
            else if (j == 0 || j == m + 1)
                mazu_map[i][j].type = 'X';
            else
            {
                cin >> mazu_map[i][j].type;
                mazu_map[i][j].x = i;
                mazu_map[i][j].y = j;
                if (mazu_map[i][j].type == 'S')
                    startPoint = mazu_map[i][j];
                else if (mazu_map[i][j].type == 'T')
                    endPoint = mazu_map[i][j];
            }
        }
    }
    // start to dfs;
    stack<PointInfo> st;
    st.push(startPoint);
    while (!st.empty())
    {
        // Notice:
        // 0 - down;
        // 1 - right;
        // 2 - up;
        // 3 - left;
        PointInfo currentPoint = st.top();
        bool isGone = false;
        PointInfo dst;
        for (int i = 0; i < 4; i++)
        {
#pragma region whereToGo
            PointInfo target;
            if (i == 0)
            {
                target = mazu_map[currentPoint.x + 1][currentPoint.y];
                if (!target.isVisited && (target.type == '.') || (target.type == 'T'))
                {
                    // goto;
                    dst = target;
                    mazu_map[target.x][target.y].isVisited = true;
                    isGone = true;
                }
            }
            else if (i == 1)
            {
                target = mazu_map[currentPoint.x][currentPoint.y + 1];
                if (!target.isVisited && (target.type == '.') || (target.type == 'T'))
                {
                    // goto;
                    dst = target;
                    mazu_map[target.x][target.y].isVisited = true;
                    isGone = true;
                }
            }
            else if (i == 2)
            {
                target = mazu_map[currentPoint.x - 1][currentPoint.y];
                if (!target.isVisited && (target.type == '.') || (target.type == 'T'))
                {
                    // goto;
                    dst = target;
                    mazu_map[target.x][target.y].isVisited = true;
                    isGone = true;
                }
            }
            else if (i == 3)
            {
                target = mazu_map[currentPoint.x][currentPoint.y - 1];
                if (!target.isVisited && (target.type == '.') || (target.type == 'T'))
                {
                    // goto;
                    dst = target;
                    mazu_map[target.x][target.y].isVisited = true;
                    isGone = true;
                }
            }
#pragma endregion
        }
        if (isGone)
        {
            if (dst.x == endPoint.x && dst.y == endPoint.y)
            {
                cout << "Yes" << endl;
                return;
            }
            st.push(dst);
            currentPoint.isVisited = true;
        }
        else
        {
            currentPoint.type = 'X';
            st.pop();
        }
    }
    cout << "No";
    return;
}

int main()
{
    DFS_Mazu();
    return 0;
} // DFS
