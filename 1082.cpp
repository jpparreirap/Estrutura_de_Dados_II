#include <bits/stdc++.h>
#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define MAX 30

using namespace std;

int adj[MAX][MAX];
int visitados[MAX];
vector<int> ordem;
int vertices, arestas, j, i;

void dfs(int p){
    visitados[p]=1;
	ordem.push_back(p); // adiciona um elemento ao final do vetor
	for(int i=0;i<vertices;i++){
        if(adj[p][i]){
            if(!visitados[i]){ // se a pos do adj[p][i] ainda não for visitada chama dfs para visita
                dfs(i);
			}
		}
	}
}

int main(void){
    int n_casos;
	scanf("%d", &n_casos);

	for(int k = 0; k < n_casos; k++){
        cout << "Case #" << k+1 << ":" << endl;
        cin >> vertices >> arestas;

        char caract1, caract2;
        int cont = 0;

        ordem.clear(); //limpa o vetor
        memset(adj, 0, sizeof(adj)); //ele ta inicializando os blocos de memoria da matriz adj como 0
        memset(visitados, 0, sizeof(visitados)); //ele ta inicializando os blocos de memoria do vet visitados como 0

        for(int i=0; i<arestas; i++){
            cin >> caract1 >> caract2;
            int u,v;
            u = caract1 - 'a'; //0
            v = caract2 - 'a';//2
            adj[u][v] = adj [v][u] = 1;
            //  0  2         2  0
        }

        for(int i=0; i<vertices; i++){
            if(!visitados[i]){
                cont++;
                dfs(i);
                sort(ordem.begin(),ordem.end());
                for(int j = 0;j < ordem.size();j++){ // enquando for menor que o tam do vetor
                        printf("%c,",ordem[j]+ 'a');
                }
                printf("\n");
			}
			ordem.clear(); // limpa o vetor
		}
		cout << cont << " connected components" << endl;
		cout << endl;
	}
	return 0;
}
