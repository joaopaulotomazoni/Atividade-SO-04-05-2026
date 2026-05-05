#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define NUM_FRAMES 10
#define NUM_PAGINAS 20
#define NUM_ACESSOS 5

typedef struct{
    int numero_frame;
    char bit_validade;
} Pagina;

typedef struct{
    int num_pagina;
} Frame;

void inicializar(Frame *frames, Pagina *tabela){
    for(int i = 0; i < NUM_FRAMES; i++){
        frames[i].num_pagina = -1;
    }
    for(int i = 0; i < NUM_PAGINAS; i++){
        tabela[i].bit_validade = 'i';
        tabela[i].numero_frame = -1;
    }
}

void preencherFrames(Frame *frames, Pagina *tabela){
    int i = 0;
    while(i < NUM_FRAMES / 2){
        int r_frame = rand() % NUM_FRAMES;
        int r_pag = rand() % NUM_PAGINAS;

        if(frames[r_frame].num_pagina == -1 && tabela[r_pag].bit_validade == 'i'){
            frames[r_frame].num_pagina = r_pag;
            tabela[r_pag].bit_validade = 'v';
            tabela[r_pag].numero_frame = r_frame;
            i++;
        }
    }
}

void acessarPaginas(Frame *frames, Pagina *tabela, int *acessos){
    for(int i = 0; i < NUM_ACESSOS; i++){
        int pag = acessos[i];

        cout << "=====================================" << endl;

        if(tabela[pag].bit_validade == 'v'){
            cout << "[HIT] Pagina " << pag << " encontrada no frame " << tabela[pag].numero_frame << endl;
        } else {
            cout << "[PAGE FAULT] Pagina " << pag << " nao esta na RAM" << endl;

            bool carregada = false;

            for(int j = 0; j < NUM_FRAMES; j++){
                if(frames[j].num_pagina == -1){
                    frames[j].num_pagina = pag;
                    tabela[pag].bit_validade = 'v';
                    tabela[pag].numero_frame = j;

                    cout << "Pagina " << pag << " carregada no frame " << j << endl;

                    carregada = true;
                    break;
                }
            }

            if(!carregada){
                cout << "Memoria cheia! Necessario algoritmo de substituicao." << endl;
            }
        }
    }
}

int main(){
    srand(time(NULL));

    Frame frames[NUM_FRAMES];
    Pagina tabela[NUM_PAGINAS];

    inicializar(frames, tabela);
    preencherFrames(frames, tabela);

    int acessos[NUM_ACESSOS] = {1,5,2,6,3};


    cout << "\n--- ESTADO INICIAL ---\n";

    cout << "RAM: [";
    for(int i = 0; i < NUM_FRAMES; i++){
        if(frames[i].num_pagina == -1)
            cout << " Livre ";
        else
            cout << " P" << frames[i].num_pagina << " ";
    }
    cout << "]\n";

    acessarPaginas(frames, tabela, acessos);

    cout << "\n--- ESTADO FINAL ---\n";

    cout << "RAM: [";
    for(int i = 0; i < NUM_FRAMES; i++){
        if(frames[i].num_pagina == -1)
            cout << " Livre ";
        else
            cout << " P" << frames[i].num_pagina << " ";
    }
    cout << "]\n";

    return 0;
}