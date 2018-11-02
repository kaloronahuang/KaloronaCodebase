// T3
#include <iostream>
#include <cstring>
using namespace std;

int n, m, k, c = 0;
string *map;
string *cmd;

struct Vector
{
    int x, y;
    char type;
    Vector *next;

    Vector()
    {
        type = '.';
        x = 0;
        y = 0;
        next = NULL;
    }

    Vector(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Vector operator+(const Vector &v) const
    {
        Vector ret;
        ret.x = x + v.x;
        ret.y = y + v.y;
        return ret;
    }
};

struct snake
{
    Vector *head;
    Vector *tail;
    int length;

    snake()
    {
        length = 0;
        head = NULL;
        tail = NULL;
    }
};

void init()
{
    cin >> n >> m >> k;
    map = new string[n];
    for (int i = 0; i < n; i++)
        cin >> map[i];
    for (int x = 0; x < n; x++)
        for (int y = 0; y < m; y++)
            if (map[x][y] == '@')
                c++;
    cmd = new string[c];
    for (int i = 0; i < c; i++)
        cin >> cmd[i];
}

Vector parse(char c)
{
    switch (c)
    {
    case 'W':
        return Vector(-1, 0);
        break;
    case 'A':
        return Vector(0, -1);
        break;
    case 'S':
        return Vector(1, 0);
        break;
    case 'D':
        return Vector(0, 1);
        break;
    }
}

snake *getSnake(Vector head)
{
    snake *ret = new snake();
    bool vis[n][m];
    memset(vis, false, sizeof(vis));
    int x = head.x;
    int y = head.y;
    while (map[x][y] != '&' || map[x][y] != '.')
    {
        Vector *v = new Vector();
        v->x = x;
        v->y = y;
        v->type = map[x][y];
        if (ret->head == NULL)
            ret->head = v;
        if (ret->tail != NULL)
            ret->tail->next = v;
        ret->tail = v;
        ret->length++;
        if (x < n - 1 && map[x + 1][y] == '#' && !vis[x + 1][y])
            x++;
        else if (x > 0 && map[x - 1][y] == '#' && !vis[x - 1][y])
            x--;
        else if (y < m - 1 && map[x][y + 1] == '#' && !vis[x][y + 1])
            y++;
        else if (y > 0 && map[x][y - 1] == '#' && !vis[x][y - 1])
            y--;
        else
            break;
    }
    return ret;
}

void sol1()
{
    snake *s;
    for (int x = 0; x < n; x++)
        for (int y = 0; y < m; y++)
            if (map[x][y] == '@')
            {
                Vector v;
                v.x = x;
                v.y = y;
                s = getSnake(v);
            }
    for (int i = 0; i < cmd[0].length(); i++)
    {
    }
}

int main()
{
    init();
    if (c == 1)
        sol1();
}
