// #include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 400000;

inline int Idx (char x) {
    if (islower(x)) return x-'a';
    if (isupper(x)) return x-'A';
    return -1;
}

struct Node {
    int X; // How Many The Same K-Word
    int Y; // The Y-th K-Word
    int L; // The Length of the K-Word
    Node *Next[26], *Fail;
};

Node *Root;
Node TrieNode[maxn];

queue<Node*> Que;
int k;
char KText[maxn];
char LText[maxn];
int ans[maxn];
int len[maxn];

void insert(char *str, int kk, int len) {
    int i,idx;
    Node *p = Root;
    for(i = 0; str[i]; i++) {
        idx = Idx(str[i]);
        if(p->Next[idx] == 0) //Need A New Node
        {
            TrieNode[k].X = 0;
            TrieNode[k].Fail = 0;
            memset(TrieNode[k].Next, 0, sizeof(TrieNode[k].Next));
            p->Next[idx] = &TrieNode[k++];
        }
        p = p->Next[idx];
    }
    p->X++;
    p->Y=kk;//Mark Down The K-th Key Word
    p->L=len;
}

void ACGetFail() {
    int i;
    Node *p, *tmp;
    Root->Fail = 0;
    Que.push(Root);
    while (!Que.empty()) {
        tmp = Que.front();
        Que.pop();
        for(i = 0; i < 26; i++) {
            if (tmp->Next[i] == 0) continue;
            if (tmp == Root) tmp->Next[i]->Fail = Root;
            else {
                p=tmp->Fail;
                while (p!=0) {
                    if ((p->Next[i])!=0) { tmp->Next[i]->Fail = p->Next[i]; break; }
                    p=p->Fail;
                }
                if(p == 0) tmp->Next[i]->Fail = Root;
            }
            Que.push(tmp->Next[i]);
        }
    }
}

int lll;

void gelen(char *msg) {
    lll = maxn - 1;
    for (int i = lll; i >= 0; i--)
        if (msg[i]) { lll = i; break; }
    lll++;
}

void AhoCorasick(char *msg) { //The Return is the Sum-Number of the times which K-Word appears
    int i, idx;
    Node *p = Root, *tmp;
    for(i = 0; i < lll; i++) {
        idx = Idx(msg[i]);
        if (idx < 0 || idx > 25) continue;
        while(p->Next[idx] == 0 && p != Root) p = p->Fail;
        p = p->Next[idx];
        if (p == 0) p = Root;
        tmp=p;
        while (tmp!=0) {
            if (tmp->X>=1) {
                ans[i + 1 - tmp -> L] = len[tmp -> Y];
                // printf("The x-th String Apears At %d\n",i+2-tmp->L);//Begins At 1
            }
            tmp=tmp->Fail;
        }
    }
}

void Init() {
    k = 0;
    Root = &TrieNode[k++];
    memset(Root->Next, 0, sizeof(Root->Next));
}

bool isuu[maxn];

void print() {
    for (int i = 0; i < lll; i++) {
        if (ans[i]) {
            for (int j = 1; j <= ans[i]; j++) {
                printf("*");
            }
            i += ans[i] - 1;
            continue;
        }
        if (isuu[i]) printf("%c", LText[i] - 'a' + 'A');
        else printf("%c", LText[i]);
    }
}
int main() __attribute__((optimize("-O2")));
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        // memset(TrieNode, 0, sizeof(TrieNode));
        memset(isuu, 0, sizeof(isuu));
        memset(ans, 0, sizeof(ans));
        Init();
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", KText);
            len[i] = strlen(KText);
            insert(KText, i, len[i]);

        }
        char t[10];
        gets(t);

        gets(LText);
        gelen(LText);
        for (int i = 0; i < lll; i++) {
            if (isupper(LText[i])) isuu[i] = 1;
            LText[i] = tolower(LText[i]);
        }
        ACGetFail();
        AhoCorasick(LText);
        print();
        printf("\n");
    }
    return 0;
}
