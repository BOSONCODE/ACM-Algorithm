#include <bits/stdc++.h>
using namespace std;

#define maxn 250005

namespace SuffixAutomation {
    struct sam {
        int fa, go[26];
        int len, r;
        bool lst;
        void init() {
            fa = len = r = 0; lst = false;
            memset(go, 0, sizeof go);
        }
    }node[maxn];
    int rt, last, tot;
    void init() {
        rt = last = tot = 1;
        node[0].init();
        node[1].init();
    }
    int newnode() {
        node[++tot].init();
        return tot;
    }
    void extend(int c) {
        int p = last, q;
        if((q = node[p].go[c])){
            if(node[q].len == node[p].len + 1) last = q;
            else{
                int nq = newnode(); 
                node[nq].len = node[p].len + 1;
                memcpy(node[nq].go, node[q].go, sizeof(node[q].go));
                node[nq].fa = node[q].fa; node[q].fa = nq;
                while (p && node[p].go[c] == q)
                node[p].go[c] = nq, p = node[p].fa;
                last = nq;
            }
            return ;
        }
        int np = newnode();
        node[np].len = node[p].len + 1; node[np].r = 1;
        while (p && !node[p].go[c]) node[p].go[c] = np, p = node[p].fa;
        if (!p) node[np].fa = rt;
        else {
            q = node[p].go[c];
            if (node[p].len + 1 == node[q].len) node[np].fa = q;
            else {
                int nq = newnode(); 
                node[nq].len = node[p].len + 1;
                memcpy(node[nq].go, node[q].go, sizeof(node[q].go));
                node[nq].fa = node[q].fa; node[np].fa = node[q].fa = nq;
                while (p && node[p].go[c] == q)
                    node[p].go[c] = nq, p = node[p].fa;
            }
        }
        last = np;
    }

    void print(){
        for (int i = 1; i <= tot; ++i){
            for (int j = 0; j < 26; ++j){
                if(node[i].go[j]){
                    cout << i << " " << (char)(j +'a') << " " << node[i].go[j] << " parent: " << node[i].fa << endl;
                }
            }
        }
    }
};
using namespace SuffixAutomation;

struct Trie{
    int nxt[26];
    int v; 
    void init(){
        v = 0;
        memset(nxt, -1, sizeof nxt);
    }
}t[maxn*26];

int cnt = 0;

void add(char a[], int len){
    int now = 0;
    for (int i = 0; i < len; ++i){
        int tmp = a[i] - 'a';
        int nxt = t[now].nxt[tmp];
        if(nxt == -1){
            nxt = ++cnt;
            t[nxt].init();
            t[now].nxt[tmp] = nxt;
        }
        now = nxt;
    }
    t[now].v = 1;
}

int query(char a[], int len){
    int now = 0;
    for (int i = 0; i < len; ++i){
        int id = a[i] - 'a';
        if(~t[now].nxt[id]) now = t[now].nxt[id];
        else return 0;
    }
    return t[now].v;
}

int ll[maxn];

void bfs(int root){
    queue<int>q;
    for (int i = 0; i < 26; ++i){
        if(~t[0].nxt[i]){
            q.push(t[0].nxt[i]);
            //cout << char(i + 'a') << endl;
            ll[t[0].nxt[i]] = last;
            extend(i);
        }
    }
    while(!q.empty()){
        int u = q.front(); q.pop();
        last = ll[u];
        for (int i = 0; i < 26; ++i){
            if(~t[u].nxt[i]){
                //cout << (char)(i + 'a') << endl;
                if(t[t[u].nxt[i]].v) node[tot + 1].lst = true;
                extend(i);  ll[t[u].nxt[i]] = last;
                q.push(t[u].nxt[i]);
            }
        }
    }
}

void dfs(int u){
    int tt = last;
    for (int i = 0; i < 26; ++i){
        if(~t[u].nxt[i]){
            extend(i);
            dfs(t[u].nxt[i]);
            last = tt;
        }
    }
}

char str[maxn];

bool query(){
    int p = rt; int len = strlen(str);
    for (int i = 0; i < len; ++i){
        int id = str[i] - 'a';
        if(node[p].go[id]) p = node[p].go[id];
        else return false;
        if(node[p].lst) return true;
    }
    return true;
}

bool query(char *str, int len, int flag){
    int p = rt; 
    for (int i = 0; i < len; ++i){
        int id = str[i] - 'a';
        if(node[p].go[id]) p = node[p].go[id];
        else return false;
        cout << (char)(id + 'a') << endl;
    }
    return true;
}

int main(){
    init();
    int n; scanf("%d", &n); int root = 0; t[0].init();
    for (int i = 1; i <= n; ++i) {
        scanf("%s", str); add(str, strlen(str)); 
    }bfs(root);
    print();
    while(scanf("%s", str))
    printf("%s\n", query(str, strlen(str), 1)? "YES":"NO");
    return 0;
}

