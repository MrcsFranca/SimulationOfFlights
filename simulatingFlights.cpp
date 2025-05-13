#include <iostream>
#include <ctime>
#include <unistd.h>
#define numAviao 50

using namespace std;

struct no {
    int info;
    int prior;
    no *link;
};

no *insere(no *L, int x, int prior);
no *retira(no *L, int *x, int *prior);
int vazia(no *L);
void exibe(no *L);

int main() {
    system("clear");
    srand(time(NULL));
    int x = 0, prior = 0, tempoEstimado = 0;
    no *FP1, *FP2, *P1, *P2;

    FP1 = FP2 = NULL;

    for(int i = 1; i <= numAviao; i++) {
        FP1 = insere(FP1, i, (rand()%2)+1);
        FP2 = insere(FP2, i, (rand()%2)+1);
    }

    cout << "Avioes que desejam pousar: " << endl;
    exibe(FP1);

    cout << endl;

    cout << endl << "Avioes que desejam decolar: " << endl;
    exibe(FP2);

    cout << endl;

    sleep(10);
    system("clear");

    for(int ut = 1, numImpresso = 5; (vazia(FP1) == 0) || (vazia(FP2) == 0); ut++, numImpresso+=5) {
        cout << endl << "Unidade de tempo: " << ut  << endl;
        cout << endl << "------------------------------------------------------------------" << endl;

        if(vazia(FP1) == 0) {
            P1 = FP1;
            cout << "Pista de pouso atendendo o aviao: " << P1->info << " | P: " << P1->prior << endl;
            cout << endl << endl << "=====Avioes que desejam pousar=====" << endl;
            P1 = P1->link;
            for(int i = 1;(i < numImpresso) && (P1 != NULL); i++) {
                tempoEstimado = i * 2;
                cout << "A: " << P1->info << " | P: " << P1->prior << " | T.A. de espera: " << tempoEstimado << endl;
                P1 = P1->link;
            }
            if(P1 == NULL) {
                cout << "Mais nenhum aviao solicitou pouso" << endl;
            }
            cout << endl;
            if(((ut % 2) == 0)) {
                FP1 = retira(FP1, &x, &prior);
                cout << "> Aviao " << x << " de prioridade " << prior << " terminou de pousar" << endl;
                if(FP1 != NULL) {
                    cout << endl << "*****Novo aviao usando a pista de pouso*****" << endl << "A: " << FP1->info << " | P: " << FP1->prior << endl << endl;
                }
            }
        }

        cout << endl << "------------------------------------------------------------------" << endl << endl;

        if(vazia(FP2) == 0) {
            P2 = FP2;
            cout << "Pista de decolagem atendendo o aviao: " << P2->info << " | P: " << P2->prior << endl;
            cout << endl << endl << "=====Avioes que desejam decolar=====" << endl;
            P2 = P2->link;
            for(int i = 1; (i < numImpresso) && P2 != NULL; i++) {
                tempoEstimado = i * 2;
                cout << "A: " << P2->info << " | P: " << P2->prior << " | T.A. de espera: " << tempoEstimado << endl;
                P2 = P2->link;
            }
            if(P2 == NULL) {
                cout << "Nenhum outro aviao solicitou decolagem" << endl;
            }
            cout << endl;
            if(((ut % 3) == 0)) {
                FP2 = retira(FP2, &x, &prior);
                cout << "> Aviao " << x << " de prioridade " << prior << " acabou de decolar" << endl;
                if(FP2 != NULL) {
                    cout << endl << "*****Proximo aviao a decolar*****" << endl << "A: " << FP2->info << " | P: " << FP2->prior << endl;
                }
            }
        }
        cout << endl << endl;
        sleep(5);
        system("clear");
    }

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

int vazia(no *L) {
    if(L == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void exibe(no *L) {
    no *P = L;
    cout << " ";
    while(P != NULL) {
        cout << "A: " << P->info << " P: " << P->prior << " | ";
        P = P->link;
    }
}
