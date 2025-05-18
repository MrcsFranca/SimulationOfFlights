#include <iostream>
#include <ctime>
#include <unistd.h>
#include <climits>
#define NUMAVIAO 50

using namespace std;

struct no {
    int info;
    int prior;
    no *link;
};

no *insere(no *L, int x, int prior);
no *retira(no *L, int *x, int *prior);
void exibe(no *L, int tempoEstimado);

int main() {
    system("clear||cls");
    srand(time(NULL));

    int x = 0, prior = 0, tempoEstimado = 0, ut = 1, aleat;
    no *FP1, *FP2, *filaGeral, *P;

    FP1 = FP2 = filaGeral = NULL;

    for(int i = 0; i < NUMAVIAO; i++) {
        filaGeral = insere(filaGeral, i, rand()%2);
    }

    do {
        system("clear||cls");
        cout << endl << "UNIDADE DE TEMPO: " << ut << "------------------------------------------------" << endl;
        if(filaGeral != NULL) {
            for(int i = 0; (i < 5) && (i < NUMAVIAO); i++) {
                filaGeral = retira(filaGeral, &x, &prior);
                aleat = rand()%INT_MAX;
                if(aleat % 2 == 0) {
                    cout << "$ O aviao " << x << " de prioridade " << prior << " pediu para pousar!" << endl;
                    FP1 = insere(FP1, x, prior);
                } else {
                    cout << "$ O aviao " << x << " de prioridade " << prior << " pediu para decolar!" << endl;
                    FP2 = insere(FP2, x, prior);
                }

            }
        }

        if((ut % 2 == 0) && (FP1 != NULL)) {
            FP1 = retira(FP1, &x, &prior);
            cout << endl << "*****O aviao " << x << " de prioridade " << prior << " acabou de pousar*****" << endl;
        }
        if((ut % 3 == 0) && (FP2 != NULL)) {
            FP2 = retira(FP2, &x, &prior);
            cout << endl << "*****O aviao " << x << " de prioridade " << prior << " acabou de decolar*****" << endl;
        }

        cout << endl << "=======Aviaoes que desejam pousar=======" << endl;
        exibe(FP1, 2);
        
        cout << endl << endl << "=======Avioes que desejam decolar=======" << endl;
        exibe(FP2, 3);

        if(FP1 != NULL) {
            cout << endl << ">> O aviao " << FP1->info << " de prioridade " << FP1->prior << " esta usando a pista de pouso" << endl;
        }

        if(FP2 != NULL) {
            cout << endl << ">> O aviao " << FP2->info << " de prioridade " << FP2->prior << " esta usando a pista de decolagem" << endl;
        }

        ut++;
        sleep(5);
    } while ((FP1 != NULL) || (FP2 != NULL));

    cout << endl << "A simulação terminou... obrigado por usar" << endl;

    return 0;
}

no *insere(no *L, int x, int prior) {
    no *N, *P, *ANT;

    N = new no;
        N->info = x;
        N->prior = prior;

    if (L == NULL) {
            L = N;
            N->link = NULL;
    }
    else {
        P = L;

        while ((P != NULL) && (prior >= P->prior)) {
            ANT = P;
            P = P->link;
        }
        if (P == L) {
            N->link = L;
            L = N;
         }
         else {
             ANT->link = N;
             N->link = P;
             }
        }
        return L;
}

no *retira(no *L, int *x, int *prior) {
    if(L != NULL) {
        no *N;
        N = L;
        *x = N->info;
        *prior = N->prior;
        L = L->link;
        delete N;
    } else {
        *x = *prior = 0;
    }
    return L;
}

void exibe(no *L, int tempoEstimado) {
    int i = 1;
    no *P = L;
    if(P != NULL) {
        P = P->link;
    }
    while(P != NULL) {
        cout << "A: " << P->info << " | P: " << P->prior << " | T.A. de espera: " << (tempoEstimado * i) << endl;
        P = P->link;
        i++;
    }
}
