// 156;
// NOIP: Search algorithm;
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

struct point
{
    int x, y;
    char type;
};

point mat[20][20];
int R, S;
stack<point> st;
vector<point> path;
int ans = 0;

bool validiate(point type)
{
    for (int i = 0; i < path.size(); i++)
        if (path[i].type == type.type)
            return false;
    return true;
}

void search()
{
    point currentPoint = st.top();
    int i = currentPoint.x;
    int j = currentPoint.y;
    // up;
    if (currentPoint.x > 0)
    {
        point up = mat[i - 1][j];
        if (validiate(up))
        {
            st.push(up);
            path.push_back(up);
            search();
        }
    }
    // left;
    if (currentPoint.y > 0)
    {
        point left = mat[i][j - 1];
        if (validiate(left))
        {
            st.push(left);
            path.push_back(left);
            search();
        }
    }
    // right;
    if (currentPoint.y < S-1)
    {
        point right = mat[i][j + 1];
        if (validiate(right))
        {
            st.push(right);
            path.push_back(right);
            search();
        }
    }
    // down;
    if (currentPoint.x < R-1)
    {
        point left = mat[i + 1][j];
        if (validiate(left))
        {
            st.push(left);
            path.push_back(left);
            search();
        }
    }
    ans = max(ans,(int)st.size());
    st.pop();
    path.pop_back();
}

int main()
{
    cin >> R >> S;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < S; j++)
        {
            point p;
            cin >> p.type;
            p.x = i;
            p.y = j;
            mat[i][j] = p;
        }
    st.push(mat[0][0]);
    path.push_back(mat[0][0]);
    search();
    cout<<ans;
    return 0;
}