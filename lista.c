// lista.c

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <pthread.h>

No* criar_lista() {
    return NULL;
}

void adicionar_elemento(No** cabeca, client_data* data) {
    No* novo_no = (No*) malloc(sizeof(No));
    novo_no->data = data;
    novo_no->data->estado=OCIOSO;
    pthread_mutex_init(&novo_no->data->mutex, NULL);
    novo_no->proximo = *cabeca;
    *cabeca = novo_no;
}

void remover_elemento(No** cabeca, client_data* data) {
    No* atual = *cabeca;
    No* anterior = NULL;
    
    while (atual != NULL) {
        if (atual->data == data) {
            if (anterior == NULL) {
                *cabeca = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

void destruir_lista(No** lista) {
    No* atual = *lista;
    No* prox;
    while (atual != NULL) {
        prox = atual->proximo;
        pthread_mutex_destroy(&atual->data->mutex);
        free(atual->data);
        free(atual);
        atual = prox;
    }
    *lista = NULL;
}


void print_lista(No* cabeca) {
    No* atual = cabeca;
    printf("      Lista de workes:\n");
    while (atual != NULL) {
        printf("Worker %s:%d (%d)\n", inet_ntoa(atual->data->client_addr->sin_addr), ntohs(atual->data->client_addr->sin_port),atual->data->estado);
        atual = atual->proximo;
    }
    printf("      -   -   -   -\n\n");
    fflush(stdout);
}

No* busca_worker(No* cabeca){
    if (cabeca == NULL) {
        return NULL;
    }
    No* atual = cabeca;
    while (atual != NULL) {
        if(pthread_mutex_trylock(&atual->data->mutex)==0){
            return atual;
        }else{
            atual = atual->proximo;
        }

        // if (atual->data->estado == OCIOSO){
        //     return atual;
        // } else {
        //     atual = atual->proximo;
        // } 
    }
    return NULL;
}
