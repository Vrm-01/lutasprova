#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lutas.h"

Lutador lutadores[100];
int total_lutadores = 0;


void salvar_lutadores() {
    FILE *f = fopen("lutadores.csv", "w");

    if (!f) {
        printf("Erro ao abrir arquivo para salvar.\n");
        return;
    }

    for (int i = 0; i < total_lutadores; i++) {
        fprintf(f, "%d;%s;%.1f;%d;%.1f\n",
            lutadores[i].id,
            lutadores[i].nome,
            lutadores[i].peso,
            lutadores[i].vitorias,
            lutadores[i].nota
        );
    }

    fclose(f);
}


void carregar_lutadores() {
    FILE *f = fopen("lutadores.csv", "r");

    if (!f) {
        return; 
    }

    total_lutadores = 0;

    while (fscanf(f,
        "%d;%49[^;];%f;%d;%f\n",
        &lutadores[total_lutadores].id,
        lutadores[total_lutadores].nome,
        &lutadores[total_lutadores].peso,
        &lutadores[total_lutadores].vitorias,
        &lutadores[total_lutadores].nota) == 5)
    {
        total_lutadores++;
    }

    fclose(f);
}


void cadastrar_lutador() {
    Lutador l;
    l.id = total_lutadores + 1;

    printf(CIANO "\n--- CADASTRAR LUTADOR ---\n" RESET);

    printf(AMARELO "Nome: " RESET);
    scanf(" %49[^\n]", l.nome);

    printf(AMARELO "Peso: " RESET);
    scanf("%f", &l.peso);

    printf(AMARELO "Vitorias: " RESET);
    scanf("%d", &l.vitorias);

    printf(AMARELO "Nota geral (0 a 10): " RESET);
    scanf("%f", &l.nota);

    lutadores[total_lutadores] = l;
    total_lutadores++;

    salvar_lutadores(); 

    printf(VERDE "\nLutador cadastrado com sucesso!\n" RESET);
}


void listar_lutadores() {
    printf(CIANO "\n--- LISTA DE LUTADORES ---\n" RESET);

    for (int i = 0; i < total_lutadores; i++) {
        printf("%s%d%s - %s | Peso: %.1f | Vitorias: %d | Nota: %.1f\n",
            AMARELO, lutadores[i].id, RESET,
            lutadores[i].nome,
            lutadores[i].peso,
            lutadores[i].vitorias,
            lutadores[i].nota
        );
    }
}


int buscar_lutador_por_id(int id) {
    for (int i = 0; i < total_lutadores; i++) {
        if (lutadores[i].id == id)
            return i;
    }
    return -1;
}


float calcular_poder(Lutador l) {
    return l.nota * 2 + l.vitorias + (l.peso / 10);
}


void lutar() {
    listar_lutadores();

    int id1, id2;

    printf(AZUL "\nID do primeiro lutador: " RESET);
    scanf("%d", &id1);

    printf(AZUL "ID do segundo lutador: " RESET);
    scanf("%d", &id2);

    int idx1 = buscar_lutador_por_id(id1);
    int idx2 = buscar_lutador_por_id(id2);

    if (idx1 == -1 || idx2 == -1 || idx1 == idx2) {
        printf(VERMELHO "IDs invalidos!\n" RESET);
        return;
    }

    Lutador l1 = lutadores[idx1];
    Lutador l2 = lutadores[idx2];

    float poder1 = calcular_poder(l1);
    float poder2 = calcular_poder(l2);

    printf("\nPoder de %s%s%s: %.2f\n", AMARELO, l1.nome, RESET, poder1);
    printf("Poder de %s%s%s: %.2f\n", AMARELO, l2.nome, RESET, poder2);

    printf(MAGENTA "\n=== RESULTADO DA LUTA ===\n" RESET);

    if (poder1 > poder2) {
        printf(VERDE "%s VENCEU!\n" RESET, l1.nome);
        lutadores[idx1].vitorias++;
    }
    else if (poder2 > poder1) {
        printf(VERDE "%s VENCEU!\n" RESET, l2.nome);
        lutadores[idx2].vitorias++;
    }
    else {
        printf(AMARELO "EMPATE!\n" RESET);
    }

    salvar_lutadores(); 
}


void alterar_lutador() {
    listar_lutadores();

    int id;
    printf(AZUL "\nDigite o ID do lutador que deseja alterar: " RESET);
    scanf("%d", &id);

    int idx = buscar_lutador_por_id(id);

    if (idx == -1) {
        printf(VERMELHO "Lutador nao encontrado!\n" RESET);
        return;
    }

    Lutador *l = &lutadores[idx];

    printf(CIANO "\n--- ALTERAR LUTADOR ---\n" RESET);

    printf(AMARELO "Nome atual (%s): " RESET, l->nome);
    getchar(); 
    fgets(l->nome, sizeof(l->nome), stdin);
    l->nome[strcspn(l->nome, "\n")] = 0;

    printf(AMARELO "Peso atual (%.1f): " RESET, l->peso);
    scanf("%f", &l->peso);

    printf(AMARELO "Vitorias atuais (%d): " RESET, l->vitorias);
    scanf("%d", &l->vitorias);

    printf(AMARELO "Nota atual (%.1f): " RESET, l->nota);
    scanf("%f", &l->nota);

    salvar_lutadores(); 

    printf(VERDE "\nLutador alterado com sucesso!\n" RESET);
}
