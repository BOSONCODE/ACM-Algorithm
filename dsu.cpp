/*************************************************************************
    > File Name: dsu.cpp
    > Author: BOSON
    > Mail: suda1527403057@163.com 
    > Created Time: 2017年09月30日 星期六 22时03分08秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;
#define maxn 200005

int fa[maxn];
int n;

void init(){
	for (int i = 0; i < maxn-4; ++i)
		fa[i] = i;
}

int find(int x){
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void unite(int x, int y){	
	int fx = find(x);
	int fy = find(y);
	if(fx == fy) return ;
	fa[fx] = fy;
}

int tot = 0;
map<string, int>g;

int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	init();
	for (int i = 1; i <= n; ++i){
		int op; string s, str; cin >> op >> s >> str;
		int l = g[s], r = g[str];
		if(!l) l = g[s] = ++tot;
		if(!r) r = g[str] = ++tot;
		if(!op){
			unite(l, r);
		}else{	
			int fal = find(g[s]), far = find(g[str]);
			if(fal == far) cout << "yes" << endl; 
			else cout << "no" << endl;
		}
	}
	return 0;
}
