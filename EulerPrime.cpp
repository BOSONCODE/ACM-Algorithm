/*************************************************************************
    > File Name: 1.cpp
    > Author: BOSON
    > Mail: suda1527403057@163.com 
    > Created Time: 2017年09月30日 星期六 06时12分39秒
 ************************************************************************/

#include<bits/stdc++.h>
using namespace std;

#define maxn 1000
int prime[maxn], primecnt;
bool isprime[maxn];

void getTable(){	
	memset(isprime, true, sizeof isprime);
	isprime[1] = false;
	for (int i = 2; i < maxn; ++i){
		if(isprime[i]) prime[primecnt++] = i;
		for (int j = 0; j < primecnt && i*prime[j] < maxn; ++j){
			isprime[prime[j]*i] = false;
			if(i % prime[j] == 0) break;
		}
	}
}

int main(){
	getTable();
	for (int i = 0; i < primecnt; ++i) cout << prime[i] << endl;
	return 0;
}
