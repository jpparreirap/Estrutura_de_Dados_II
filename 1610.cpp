#include <bits/stdc++.h>

using namespace std;

enum {WHITE, GRAY, BLACK};

#define INIFITO 9999999

int G[20001][20001], vertice[20001];

bool loop;

int dfs(int Ndoc, int doc){

    vertice[doc] = GRAY;

    int i;
    for(i = 1; i <= Ndoc; i++){
        if (G[doc][i] == 1) {
            if(vertice[i] == WHITE){
                dfs(Ndoc,doc);
            }
            else if(vertice[i] == GRAY){
                loop = true;
                return 0;
            }
        }
    }

    vertice[doc] = BLACK;

    return 1;
}

void inicializa(int Ndoc){
    int i, j;
    for (i = 1; i <= Ndoc; i++)
        vertice[i] = 0;

    for (i = 1; i <= Ndoc; i++)
        for (j = 1; j <= Ndoc; j++)
            G[i][j] = INIFITO;
}

int main (){
    int Tcasos, Ndoc, Mdep, Doc_A, Doc_B;

    cin >> Tcasos;

    while (Tcasos--){
        cin >> Ndoc >> Mdep; // numero de docs e dependencias

        inicializa(Ndoc);

        loop = false;

        while(Mdep--){
            cin >> Doc_A >> Doc_B;

            G[Doc_A][Doc_B] = 1;

        }

//        for(int i = 0; i < G.size(); i++){ //percorre até tam max de vert adj
//            if(vertice[i] == WHITE) { // se o vert adj for branco chama dfs para conhece-lo
//                dfs(Ndoc,i);
//                if(loop) // se ele ja for conhecido (se ja for cinza), quebra o laço
//                    break;
//            }
//        }

        if (loop)
            printf("SIM\n");

        else
            printf("NAO\n");
    }
  return 0;
}
