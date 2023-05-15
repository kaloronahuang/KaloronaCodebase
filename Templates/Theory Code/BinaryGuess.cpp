while (l <= r)
    if (check(mid))
        res = mid, l = mid + 1;
    else
        r = mid - 1;
return res;