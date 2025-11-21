#define RESET   "\033[0m" 
#define VERMELHO "\033[31m"
#define VERDE    "\033[32m"
#define AMARELO  "\033[33m"
#define AZUL     "\033[34m"
#define MAGENTA  "\033[35m"
#define CIANO    "\033[36m"
#define BRANCO   "\033[37m"

#ifndef LUTAS_H
#define LUTAS_H

typedef struct {
    int id;
    char nome[50];
    float peso;
    int vitorias;
    float nota;
} Lutador;

extern Lutador lutadores[100];
extern int total_lutadores;

void cadastrar_lutador();
void listar_lutadores();
void lutar();
void alterar_lutador();
int buscar_lutador_por_id(int id);
float calcular_poder(Lutador l);

// Persistência
void salvar_lutadores();
void carregar_lutadores();

#endif
