#include <bits/stdc++.h>
using namespace std;

#define maxn 250005

namespace SuffixAutomation {
    struct sam {
        int fa, go[26];
        int len, r;
        int cnt;
        int endpos;
        int pos;
        void init() {
            fa = len = r = 0;
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
        int p = last, np = newnode();
        node[np].len = node[p].len + 1; node[np].r = 1;
        while (p && !node[p].go[c]) node[p].go[c] = np, p = node[p].fa;
        if (!p) node[np].fa = rt;
        else {
            int q = node[p].go[c];
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

    int v[maxn], q[maxn];

    void topsort() {
        memset(v, 0, sizeof v);
        for (int i = 1; i <= tot; ++i) ++v[node[i].len];
        for (int i = 1; i <= tot; ++i) v[i] += v[i - 1];
        for (int i = tot; i; --i) q[v[node[i].len]--] = i;
        for (int i = 1; i <= tot; ++i) node[i].cnt = 1;
    }

    void print(){
        for (int i = 1; i <= tot; ++i){
            for (int j = 0; j < 256; ++j){
                if(node[i].go[j]){
                    cout << i << " " << (char)j << endl; 
                }
            }
        }
    }

    const int Len = 2000;
    vector<int>g[Len*2];
    int sa[maxn], rk[maxn];
    int ti = 0;

    void bianli(int u){
        for (int i = 0; i < 26; ++i){
            if(node[u].go[i]){
                printf("%c", (i + 'a'));
                bianli(node[u].go[i]);
            }
        }
    }


    void dfs(int u){
        if(g[u].size() == 0) {
            bianli(u);
            printf("\n");
            return ;
        }
        for (auto it : g[u]) dfs(it);
    }

    void pre(){
        ti = 0;
        for (int i = 1; i <= tot; ++i) g[i].clear();
        for (int i = 0; i <= tot; ++i){
            g[node[i].fa].push_back(i);
        }
        //dfs(1);
    }

    void clear(){
        for (int i = 1; i <= tot; ++i)
            node[i].init();
    }

    void print_sa(char *s, int len){
        printf("sa:\n");
        for (int i = 0; i < len*2; ++i) printf("%d%c", sa[i], " \n"[i == len - 1]);
        printf("rank:\n");
        for (int i = 0; i < len*2; ++i) printf("%d%c", rk[i], " \n"[i == len - 1]);
    }
    
    //输出所有的后缀
    char buf[maxn];
    int top;
    void tranverse(int u){
        if(top && node[u].endpos)puts(buf);
        sam &cur = node[u];
        for(int i = 0; i < 26; i++){
            if(cur.go[i]){
                buf[top++] = (char)(i + 'a');
                buf[top] = 0;
                tranverse(cur.go[i]);
                top--;
            }
        }
    }
    void suffix_sort(){
        top = 0;
        for(int p = tot; p; p = node[p].fa)
            node[p].endpos = true;
        tranverse(1);
    }
};
using namespace SuffixAutomation;

int main(){
    init();
    char s[1000]; scanf("%s", s); int len = strlen(s);
    for (int i = 0; i < len; ++i) extend(s[i] - 'a');
   // build_sa();
   // print_sa(s, strlen(s));
    return 0;
}
