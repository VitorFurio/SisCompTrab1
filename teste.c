// programa.c

#include <stdio.h>
#include "lista.h"

int main() {
    No* lista = criar_lista();
    adicionar_elemento(&lista, 10);
    adicionar_elemento(&lista, 20);
    adicionar_elemento(&lista, 30);
    imprimir_lista(lista);
    remover_elemento(&lista, 20);
    imprimir_lista(lista);
    return 0;
}
