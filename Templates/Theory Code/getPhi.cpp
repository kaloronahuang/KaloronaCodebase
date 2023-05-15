int phi[maxn];

void preprocess()
{
    for (int i = 1; i < maxn; i++)
        phi[i] = i;
    for (int i = 2; i < maxn; i++)
        if (phi[i] == i)
            for (int j = i; j < maxn; j += i)
                phi[j] -= phi[j] / i;
}