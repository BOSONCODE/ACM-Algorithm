/*************************************************************************
    > File Name: sam.cpp
    > Author: BOSON
    > Mail: suda1527403057@163.com 
    > Created Time: 2017年09月30日 星期六 07时03分00秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;

#define maxn 10005

struct sam{
	int go[26], fa, len;
	void init(){
		fa = len = 0;
		memset(go, 0, sizeof go);
	}
}node[maxn];

int last, tot, root;

void init(){
	last = tot = root = 1;
	node[0].init();
	node[1].init();
}

int newnode(){
	node[++tot].init();
	return tot;
}

void extend(int c){
	int p = last, np = newnode();
	node[np].len = node[p].len + 1;
	while(p && !node[p].go[c]) node[p].go[c] = np, p = node[p].fa;
	if(!p) node[np].fa = root;
	else{
		int q = node[p].go[c];
		if(node[q].len == node[p].len + 1) node[np].fa = q;
		else{
			int nq = newnode();
			node[nq].len = node[p].len + 1;
			memcpy(node[nq].go, node[q].go, sizeof node[q].go);
			node[nq].fa = node[q].fa; node[np].fa = node[q].fa = nq;
			while(p && node[p].go[c] == q) node[p].go[c] = nq, p = node[p].fa;
		}
	}
	last = np;
}

char str[maxn], s[maxn];

int lcs(){
	int p = root; int cnt = 0, res = 0;
	for (int i = 0; s[i]; ++i){
		int c = s[i] - 'a';
		if(node[p].go[c]) p = node[p].go[c], ++cnt;
		else{
			while(p && !node[p].go[c]) p = node[p].fa;
			if(!p) p = root, cnt = 0;
			else {
				cnt = node[p].len + 1;
				p = node[p].go[c];
			}
		}
		res = max(res, cnt);
	}
	return res;
}

int main(){
	init();
	scanf("%s", str);
	for (int i = 0; str[i]; ++i) extend(str[i]-'a');
	scanf("%s", s);
	cout << lcs() << endl;
	return 0;
}
