#include <iostream>
#include <cstring>
using namespace std;
const int N = 101010;
int next[N],extand[N];
void getnext(char *T){// next[i]: 以第i位置开始的子串 与 T的公共前缀
	int i,length = strlen(T);
	next[0] = length;
	for(i = 0;i<length-1 && T[i]==T[i+1]; i++);
	next[1] = i;
	int a = 1;
	for(int k = 2; k < length; k++){
		int p = a+next[a]-1, L = next[k-a];
		if( (k-1)+L >= p ){
			int j = (p-k+1)>0? (p-k+1) : 0;
			while(k+j<length && T[k+j]==T[j]) j++;// 枚举(p+1，length) 与(p-k+1,length) 区间比较
			next[k] = j, a = k;
		}
		else next[k] = L;
	}
}
void getextand(char *S,char *T){
	memset(next,0,sizeof(next));
	getnext(T);
	int Slen = strlen(S), Tlen = strlen(T), a = 0;
	int MinLen = Slen>Tlen?Tlen:Slen;
	while(a<MinLen && S[a]==T[a]) a++;
	extand[0] = a, a = 0;
	for(int k = 1; k < Slen; k++){
		int p = a+extand[a]-1, L = next[k-a];
		if( (k-1)+L >= p ){
			int j = (p-k+1)>0? (p-k+1) : 0;
			while(k+j<Slen && j<Tlen && S[k+j]==T[j] ) j++;
			extand[k] = j;a = k;
		}
		else extand[k] = L;
	}
}

int main(){
	char s[N],t[N];
	while(~scanf("%s %s",s,t)){
		getextand(s,t);
		for(int i = 0; i < strlen(t); i++)
			printf("%d ",next[i]);
		puts("");
		for(int i = 0; i < strlen(s); i++)
			printf("%d ",extand[i]);
		puts("");
	}
}
