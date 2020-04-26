#include <bits/stdc++.h>
using namespace std;
#define ll long long
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline ll read(){
    char ch=nc();ll sum=0;
    while(!(ch>='0'&&ch<='9'))ch=nc();
    while(ch>='0'&&ch<='9')sum=sum*10+ch-48,ch=nc();
    return sum;
}
const long long mod = 1e9 + 7;
int a [1000005];
map <int,int> rl;	//某个数字最左边的 
ll ans [1000005];
int n;
struct node {
	ll sum1;	//一维和 
	ll sum2;	//二维和
	int l,r,tag; 
} t1 [4000005],t2 [4000005];
void build1 (int i,int l,int r) {
	t1 [i].l = l;t1 [i].r = r;
	if (l == r) {
		return ;
	}
	int mid = (l + r) >> 1;
	build1(i << 1,l,mid);build1 (i << 1|1,mid+1,r);
}
inline void push_down (int x) {
	int t = t1 [x].tag;
	t1 [x].tag = 0;
	t1 [x << 1].tag += t;t1 [x << 1 | 1].tag += t;
	t1 [x].sum2 += ((t * t % mod) * (t1 [x].r - t1 [x].l + 1) + 2 * t1 [x].sum1 * t) % mod;
	t1 [x].sum1 += (t * (t1 [x].r - t1 [x].l + 1)) % mod;
	t1 [x].sum1 %= mod;
	t1 [x].sum2 %= mod;
}
ll sum1 (int i,int l,int r) {
	push_down (i);
	if (l <= t1 [i].l && t1 [i].r <= r) {
		return t1 [i].sum1;
	}
	int mid = (t1 [i].l + t1 [i].r) >> 1;
	ll ret = 0;
	if (l <= mid) {
		ret += sum1 (i << 1,l,r);
	}
	if (r > mid) {
		ret += sum1 (i << 1 | 1,l,r);
	}
	ret %= mod;
	return ret;
}
ll sum2 (int i,int l,int r) {
	push_down (i);
	if (l <= t1 [i].l && t1 [i].r <= r) {
		return t1 [i].sum2;
	}
	int mid = (t1 [i].l + t1 [i].r) >> 1;
	ll ret = 0;
	if (l <= mid) {
		ret += sum2 (i << 1,l,r);
	}
	if (r > mid) {
		ret += sum2 (i << 1 | 1,l,r);
	}
	ret %= mod;
	return ret;
}
void add (int i,int l,int r,int v) {
	push_down (i);
	if (l <= t1 [i].l && t1 [i].r <= r) {	//都加上v 
		t1 [i].sum2 += v * v * (t1 [i].r - t1 [i].l + 1) + 2 * t1 [i].sum1;
		t1 [i].sum1 += v * (t1 [i].r - t1 [i].l + 1);
		t1 [i].sum1 %= mod;
		t1 [i].sum2 %= mod;
		//告诉孩子需要加一 
		t1 [i<<1].tag += v;
		t1 [i<<1|1].tag += v;
		return ;
	}
	int mid = (t1 [i].l + t1 [i].r) >> 1;
	if (l <= mid) {
		add (i<<1,l,r,v);
	}
	if (r > mid) {
		add (i<<1|1,l,r,v);
	}
	t1 [i].sum1 = (t1 [i<<1].sum1 + t1 [i<<1|1].sum1) % mod;
	t1 [i].sum2 = (t1 [i<<1].sum2 + t1 [i<<1|1].sum2) % mod;
}
int main () {
	n = read ();
	for (int i = 1;i <= n;++ i) a [i] = read ();
	build1 (1,1,n);
	ll ans = 0;
	for (int i = n;i >= 1;-- i) {
		int d = n + 1;
		if (rl.find (a [i]) != rl.end ()) d = rl [a [i]];
		int k = i + 1;
		ans += d - i;
		ans %= mod;
		ans += (sum1 (1,k,d - 1)) << 1;
		ans %= mod;
		ans += (sum2 (1,k,d - 1));
		ans %= mod;
		ans = (ans + sum2 (1,d,n)) % mod;
		add (1,i,d - 1,1);
		rl [a [i]] = i;
	}
	printf ("%lld\n",ans);
	return 0;
}