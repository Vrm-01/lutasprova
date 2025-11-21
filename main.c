#include <stdio.h>
#include <stdlib.h>
#include "lutas.h"

int main() {

    carregar_lutadores(); 

    int opcao;

    do {
        printf(CIANO "1 - Cadastrar lutador\n" RESET);
        printf(CIANO "2 - Listar lutadores\n" RESET);
        printf(CIANO "3 - Luta entre lutadores\n" RESET);
        printf(CIANO "4 - Alterar lutador\n" RESET);
        printf(VERMELHO "0 - Sair\n" RESET);

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrar_lutador(); break;
            case 2: listar_lutadores(); break;
            case 3: lutar(); break;
            case 4: alterar_lutador(); break;
            case 0: printf(AMARELO "\nSaindo...\n" RESET); break;
            default: printf(VERMELHO "Opcao invalida!\n" RESET);
        }

    } while (opcao != 0);

    return 0;
}
