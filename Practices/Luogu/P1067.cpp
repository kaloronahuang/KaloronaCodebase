// P1067
#include <iostream>
#include <sstream>
#include <cmath>

#define abs std::abs

std::string toString(int n)
{
    std::ostringstream ss;
    ss << n;
    return ss.str();
}

int main()
{
    int N;
    std::cin >> N;
    std::string str = "";

    for (int i = 0; i < N + 1; i++)
    {
        int num;
        std::cin >> num;
        if (num)
        {
            if (num < 0)
                str += "-";
            else if (str.length() != 0)
                str += "+";

            if (N - i != 0)
            {
                if (abs(num) != 1)
                    str += toString(abs(num));
                str += "x";
                if (N - i != 1)
                    str += ("^" + toString(abs(N - i)));
            }
            else
            {
                std::string nowChar = toString(abs(num));
                str += nowChar;
            }
        }
    }

    std::cout << str;
    return 0;
}