#include <iostream>
#include <algorithm>
#include <sstream>
const int maxn = 10020;
using namespace std;

class Integer
{
  public:
    /**
   *  The basic part of Integer.
   */
    Integer(string orig) { m_data = orig; }
    friend ostream &operator<<(ostream &out, Integer orig)
    {
        out << orig.m_data;
        return out;
    }

  public:
    /**
   *  Implement Addition
   *  The basic thought is to transfer the string to array
   *  and operate array so that we can get the answer string.
   *
   *  @param Int_a Integer a
   *  @param Int_b Integer b
   *
   *  @return answer string
   */
    friend string operator+(Integer Int_a, Integer Int_b)
    {
        size_t a_len = Int_a.m_data.length();
        size_t b_len = Int_b.m_data.length();
        int a_vec[maxn] = {0}, b_vec[maxn] = {0}, c_vec[maxn] = {0};
        /**
     *  Transfer the string to Array
     *  Pay attention to the position of corresponding element in string.
     *  We wanna operate the Integer from the beginning.
     */
        reverse(Int_a.m_data.begin(), Int_a.m_data.end());
        for (int i = 0; i < a_len; i++)
        {
            a_vec[i] = Int_a.m_data[i] - '0';
        }
        reverse(Int_b.m_data.begin(), Int_b.m_data.end());
        for (int i = 0; i < b_len; i++)
        {
            b_vec[i] = Int_b.m_data[i] - '0';
        }

        size_t c_len = a_len > b_len ? a_len : b_len;
        for (int i = 0; i < c_len; i++)
        {
            c_vec[i] = a_vec[i] + b_vec[i] + c_vec[i];
            if (c_vec[i] >= 10)
            {
                c_vec[i + 1] = 1;
                c_vec[i] -= 10;
            }
        }
        if (c_vec[c_len] > 0)
        {
            c_len++;
        }
        string ans;
        for (int i = int(c_len - 1); i >= 0; i--)
        {
            ans.push_back('0' + c_vec[i]);
            if (i % 3 == 0 && i != 0)
            {
                ans.push_back(',');
            }
        }
        return ans;
    }

  public:
    /**
   *  Implement substraction
   *
   *  @param Int_a Integer a
   *  @param Int_b Integer b
   *
   *  @return answer string
   */
    friend string operator-(Integer Int_a, Integer Int_b)
    {
        size_t a_len = Int_a.m_data.length();
        size_t b_len = Int_b.m_data.length();
        int a_vec[maxn] = {0}, b_vec[maxn] = {0};
        reverse(Int_a.m_data.begin(), Int_a.m_data.end());
        for (int i = 0; i < a_len; i++)
        {
            a_vec[i] = Int_a.m_data[i] - '0';
        }
        reverse(Int_b.m_data.begin(), Int_b.m_data.end());
        for (int i = 0; i < b_len; i++)
        {
            b_vec[i] = Int_b.m_data[i] - '0';
        }

        size_t c_len = a_len > b_len ? a_len : b_len;
        if (judge(a_vec, b_vec, c_len))
        {
            string ans = divd(a_vec, b_vec, c_len);
            return ans;
        }
        else
        {
            string ans = "-";
            ans += divd(b_vec, a_vec, c_len);
            return ans;
        }
    }
    /**
   *  The detail part of substraction
   *
   *  @param num_a array of Integer a
   *  @param num_b array of Integer b
   *  @param lc    length of maxn array
   *
   *  @return answer string
   */
    static string divd(int *num_a, int *num_b, long lc)
    {
        int result[maxn] = {0};
        for (long i = 0; i < lc; i++)
        {
            result[i] = num_a[i] - num_b[i];
            if (result[i] < 0)
            {
                result[i] += 10;
                num_a[i + 1]--;
            }
        }
        lc--;
        while (lc > 0)
        {
            if (result[lc] > 0)
            {
                break;
            }
            lc--;
        }
        string ans;
        while (lc >= 0)
        {
            ans.push_back('0' + result[lc]);
            lc--;
            if (lc % 3 == 0 && lc != -1)
            {
                ans.push_back(',');
            }
        }
        return ans;
    }
    /**
   *  judge which Integer is greater
   *
   *  @param num_a array of Integer a
   *  @param num_b array of Integer b
   *  @param lc    length of maxn array
   *
   *  @return bool
   */
    static bool judge(int *num_a, int *num_b, long lc)
    {
        for (long i = lc - 1; i >= 0; i--)
        {
            if (num_a[i] > num_b[i])
            {
                return true;
            }
            else if (num_a[i] < num_b[i])
            {
                return false;
            }
        }
        return true;
    }

  public:
    /**
   *  Implement Multiple operation
   *
   *  @param Int_a Integer a
   *  @param Int_b Integer b
   *
   *  @return answer string
   */
    friend string operator*(Integer Int_a, Integer Int_b)
    {
        int array_a[maxn] = {0}, array_b[maxn] = {0};
        int array_sum[maxn * 2] = {0};
        int a_len = int(Int_a.m_data.length()), b_len = int(Int_b.m_data.length()),
            sum_len = 0;
        int i, j;
        reverse(Int_a.m_data.begin(), Int_a.m_data.end());
        for (i = 0; i < a_len; i++)
        {
            array_a[i] = Int_a.m_data[i] - '0';
        }
        reverse(Int_b.m_data.begin(), Int_b.m_data.end());
        for (i = 0; i < b_len; i++)
        {
            array_b[i] = Int_b.m_data[i] - '0';
        }

        for (i = 0; i < a_len; i++)
        {
            for (j = 0, sum_len = i - 1; j < b_len; j++)
            {
                array_sum[++sum_len] += array_b[j] * array_a[i];
            }
        }
        for (i = 0; i < sum_len; i++)
        {
            if (array_sum[i] >= 10)
            {
                if (array_sum[sum_len] >= 10)
                {
                    sum_len++;
                }
                array_sum[i + 1] += array_sum[i] / 10;
                array_sum[i] %= 10;
            }
        }
        string answer;
        for (i = sum_len; i >= 0; i--)
        {
            answer.push_back('0' + array_sum[i]);
            if (i % 3 == 0 && i != 0)
            {
                answer.push_back(',');
            }
        }
        return answer;
    }

  private:
    string m_data;
} ans, tot;

struct minister
{
    long long l, r;

    bool operator<(const minister &mst) const
    {
        return l * r < mst.l * mst.r;
    }
} ministres[maxn];
int n;

string toString(int num)
{
    stringstream ss;
    ss << num;
    return ss.str();
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> ministres[i].l >> ministres[i].r;
    sort(ministres + 1, ministres + n + 1);
    ans = Integer("0");
    for (int i = 2; i <= n; i++)
    {
        tot = tot * Integer(toString(ministres[i - 1].l));
        ans = max(tot./Integer(toString(ministres[i].r));
    }
}