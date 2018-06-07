/*************************************************************************
    > File Name: test.cpp
    > Author: BOSON
    > Mail: suda1527403057@163.com 
    > Created Time: 2017年09月30日 星期六 16时07分54秒
 ************************************************************************/
// 树状数组的区间修改区间查询
/*
 a[1]+a[2]+...+a[n]
 = (c[1]) + (c[1]+c[2]) + ... + (c[1]+c[2]+...+c[n]) 
 = n*c[1] + (n-1)*c[2] +... +c[n]
 = n * (c[1]+c[2]+...+c[n]) - (0*c[1]+1*c[2]+...+(n-1)*c[n])    (式子①)
*/
//定义c1[i] = a[i] - a[i-1] , c2[i] = (i - 1)*c1[i]
//查询: n*sigma(c1, n) - sigma(c2, n)
//对于更新操作 update(delta, left, x), update(delta, right + 1, -x), update(deltai, l, x*l), update(deltai, r + 1, -x(r + 1))
//对于查询操作	
//suml = (left-1)*query(c, left-1) - query(c2, left - 1)
//sumr = right*query(c1, right) - query(c2, right)
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define maxn 100005
LL sum[maxn];
int n;
LL c1[maxn], c2[maxn];
int a[maxn];

void update(LL *c, int id, LL x){
	while(id <= n){
		c[id] += x;
		id += id&(-id);
	}
}

LL getsum(LL *c, int id){
	LL res = 0;
	while(id){
		res += c[id];
		id -= id&(-id);
	}
	return res;
}

int work(int cas){
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) update(c1, i,(LL) a[i] - a[i-1]), update(c2, i, (LL)(a[i] - a[i-1])*(i-1));
	int q; scanf("%d", &q);
	for (int i = 1; i <= q; ++i){
		int op, a, b, x; scanf("%d", &op);
		if(1 == op){
			scanf("%d%d%d", &a, &b, &x);
			update(c1, a, x);
			update(c1, b + 1, -x);
			update(c2, a, x*(a - 1));
			update(c2, b + 1, -x*b);
		}else{
			scanf("%d%d", &a, &b);
			LL suml = (a-1)*getsum(c1, a - 1) - getsum(c2, a-1);
			LL sumr = b*getsum(c1, b) - getsum(c2, b);
			printf("%lld\n", sumr - suml);
		}
	}
	return 0;
}

int main(){
	int t; scanf("%d", &t);
	for (int i = 1; i <= t; ++i) work(i);
	return 0;
}
