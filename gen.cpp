#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=9000;
char s[2005];
struct SAM{
	int last,l[MAXN],f[MAXN],go[MAXN][26],L;
	int mn[MAXN];
	int mx[MAXN];
	int x[MAXN];
	int root,tot;
	SAM(){
		root=last=tot=1;
	}
	void add(int w){// add last + char w
		L++;
		int p=last;
		int np=++tot;// xS
		l[np]=l[p]+1;
		while(p&&!go[p][w]){
			go[p][w]=np;
			p=f[p];
		}
		if(!p){
			f[np]=root;
		}else{
			int q=go[p][w];
			if(l[p]+1==l[q]){
				f[np]=q;
			}else{
				int nq=++tot;
				l[nq]=l[p]+1;
				memcpy(go[nq],go[q],sizeof go[q]);
				f[nq]=f[q];
				f[q]=f[np]=nq;
				while(p&&go[p][w]==q) go[p][w]=nq,p=f[p];
			}
		}
		last=np;
	}
	void output(){
		puts("digraph G {");
		for(int i=1;i<=tot;i++){
			printf("%d[label=\"%d(len=%d)\"];\n",i,i,l[i]);
			if(f[i])printf("%d -> %d[color=blue,style=dotted];\n",i,f[i]);
			for(int j=0;j<26;j++){
				if(go[i][j]>0){
					printf("%d -> %d[label=\"%c\"];\n",i,go[i][j],'a'+j);
				}
			}
		}
		puts("}");
	}
}SAM;
int n;
int main(){
	scanf("%s",s);
	for(int i=0;s[i];i++){
		SAM.add(s[i]-'a');
	}
	SAM.output();
	return 0;
}


