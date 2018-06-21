#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int x, int y){
    if (x < y)
        return x;
    else
        return y;
}

int maxx(int x, int y){
    if (x > y)
        return x;
    else
        return y;
}

void segTreeMin(int segTree[], int vet[], int low, int high, int pos){

    if(low == high){
        segTree[pos] = vet[low];
    }
    else{
        int mid = (low + high) / 2;
        segTreeMin(segTree, vet, low, mid, 4 * pos + 1);
        segTreeMin(segTree, vet, mid + 1 , high, 4 * pos + 2);
        segTree[pos] = min(segTree[4 * pos + 1], segTree[4 * pos + 2]);
    }
}

void segTreeMax(int segTree[], int vet[], int low, int high, int pos){

    if(low == high){
        segTree[pos] = vet[low];
    }
    else{
        int mid = (low + high) / 2;
        segTreeMax(segTree, vet, low, mid, 4 * pos + 1);
        segTreeMax(segTree, vet, mid + 1 , high, 4 * pos + 2);
        segTree[pos] = maxx(segTree[4 * pos + 1], segTree[4 * pos + 2]);
    }
}

int segTreeSoma(int segTree[], int vet[], int low, int high, int pos){

    if(low == high){

        segTree[pos] = vet[low];

        return vet[low];
    }
    else {
        int mid = (low + high) / 2;
        int somaEsq = segTreeSoma(segTree, vet, low, mid, 4 * pos + 1);
        int somaDir = segTreeSoma(segTree, vet, mid + 1 , high, 4 * pos + 2);
        segTree[pos] = somaEsq + somaDir;
        return segTree[pos];
    }
}

int buscaMin(int segTree[], int low, int high, int qlow, int qhigh, int pos){

    if(qlow <= low && qhigh >= high){
        return segTree[pos];
    }

    if(qlow > high || qhigh < low){
        return INT_MAX;
    }

    int mid = (low + high) / 2;

    return min(buscaMin(segTree, low, mid, qlow, qhigh, 4 * pos + 1),
               buscaMin(segTree, mid + 1, high, qlow, qhigh, 4 * pos + 2));
}

int buscaMax(int segTree[], int low, int high, int qlow, int qhigh, int pos){

    if(qlow <= low && qhigh >= high){
        return segTree[pos];
    }

    if(qlow > high || qhigh < low){
        return INT_MIN;
    }

    int mid = (low + high) / 2;

    return maxx(buscaMax(segTree, low, mid, qlow, qhigh, 4 * pos + 1),
               buscaMax(segTree, mid + 1, high, qlow, qhigh, 4 * pos + 2));
}

int buscaSoma(int segTree[], int low, int high, int qlow, int qhigh, int pos){

    if(qlow <= low && qhigh >= high){
        return segTree[pos];
    }

    if(qlow > high || qhigh < low){
        return 0;
    }

    int mid = (low + high) / 2;
    int somaEsq = buscaSoma(segTree, low, mid, qlow, qhigh, 4 * pos + 1);
    int somaDir = buscaSoma(segTree, mid + 1, high, qlow, qhigh, 4 * pos + 2);

    return somaEsq + somaDir;
}

int main() {
    long long int segTreeMinn[4*400000];
    long long int segTreeMaxx[4*400000];
    long long int segTreeSomaa[4*400000];
    long long int vet[4*400000];
    long long int i, v;
    long long int TAM, b;

    long long int somaTotal;
    long long int somaMin;
    long long int somaMax;
    long long int score;

    while(scanf("%d %d", &TAM, &b) != EOF){

        somaTotal = 0;
        somaMin = 0;
        somaMax = 0;
        score = 0;

        for(i = 0; i < TAM; i++){
            scanf("%d", &v);
            vet[i] = v;
        }

        segTreeMin(segTreeMinn, vet, 0, TAM - 1, 0);
        segTreeMax(segTreeMaxx, vet, 0, TAM - 1, 0);
        segTreeSoma(segTreeSomaa, vet, 0, TAM - 1, 0);

        for(i=0; i<=TAM-b; i++){
            int qhigh = b-1+i;

            somaTotal += buscaSoma(segTreeSomaa, 0, TAM - 1, i, qhigh, 0);
            somaMin += buscaMin(segTreeMinn, 0, TAM - 1, i, qhigh, 0);
            somaMax += buscaMax(segTreeMaxx, 0, TAM - 1, i, qhigh, 0);
        }

        score = somaTotal - (somaMin + somaMax);

        printf("%d\n", score);
    }
    return 0;
}
