#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/* — Versão vetor */
#define MAX_ITENS 100
typedef struct {
    Item itens[MAX_ITENS];
    int tamanho;
} MochilaVetor;

/* — Versão lista encadeada */
typedef struct No {
    Item dados;
    struct No *proximo;
} No;
typedef struct {
    No *inicio;
    int tamanho;
} MochilaLista;

/* — Vetor: inicializar */
void initVetor(MochilaVetor *m) {
    m->tamanho = 0;
}

/* — Lista: inicializar */
void initLista(MochilaLista *m) {
    m->inicio = NULL;
    m->tamanho = 0;
}

/* — Vetor: inserir */
int inserirVetor(MochilaVetor *m, Item item) {
    if (m->tamanho >= MAX_ITENS) return 0;
    m->itens[m->tamanho++] = item;
    return 1;
}

/* — Lista: inserir no início */
int inserirLista(MochilaLista *m, Item item) {
    No *novo = malloc(sizeof(No));
    if (!novo) return 0;
    novo->dados = item;
    novo->proximo = m->inicio;
    m->inicio = novo;
    m->tamanho++;
    return 1;
}

/* — Vetor: listar */
void listarVetor(const MochilaVetor *m) {
    printf("Itens (vetor):\n");
    for (int i = 0; i < m->tamanho; i++) {
        printf("  %s | %s | %d\n",
               m->itens[i].nome,
               m->itens[i].tipo,
               m->itens[i].quantidade);
    }
}

/* — Lista: listar */
void listarLista(const MochilaLista *m) {
    printf("Itens (lista):\n");
    No *p = m->inicio;
    while (p) {
        printf("  %s | %s | %d\n",
               p->dados.nome,
               p->dados.tipo,
               p->dados.quantidade);
        p = p->proximo;
    }
}

/* — Vetor: busca sequencial */
int buscarVetor(const MochilaVetor *m, const char *nome) {
    for (int i = 0; i < m->tamanho; i++) {
        if (strcmp(m->itens[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

/* — Lista: busca sequencial */
int buscarLista(const MochilaLista *m, const char *nome) {
    No *p = m->inicio;
    int pos = 0;
    while (p) {
        if (strcmp(p->dados.nome, nome) == 0) {
            return pos;
        }
        p = p->proximo;
        pos++;
    }
    return -1;
}

/* — Vetor: ordenação simples (bubble sort) por nome */
void ordenarVetor(MochilaVetor *m) {
    for (int i = 0; i < m->tamanho - 1; i++) {
        for (int j = 0; j < m->tamanho - i - 1; j++) {
            if (strcmp(m->itens[j].nome, m->itens[j+1].nome) > 0) {
                Item tmp = m->itens[j];
                m->itens[j] = m->itens[j+1];
                m->itens[j+1] = tmp;
            }
        }
    }
}

/* — Vetor: busca binária (precisa estar ordenado) */
int buscarBinariaVetor(const MochilaVetor *m, const char *nome) {
    int esq = 0, dir = m->tamanho - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int cmp = strcmp(m->itens[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;
}

int main() {
    MochilaVetor mv;
    MochilaLista ml;
    initVetor(&mv);
    initLista(&ml);

    int escolha = 0;
    Item item;
    char nomeBusca[30];

    do {
        printf("\nEscolha estrutura: 1=Vetor, 2=Lista, 0=Sair: ");
        scanf("%d", &escolha);
        getchar();

        if (escolha == 1) {
            printf("Inserir item no vetor:\n");
            printf("Nome: ");
            fgets(item.nome, sizeof(item.nome), stdin);
            item.nome[strcspn(item.nome, "\n")] = '\0';
            printf("Tipo: ");
            fgets(item.tipo, sizeof(item.tipo), stdin);
            item.tipo[strcspn(item.tipo, "\n")] = '\0';
            printf("Quantidade: ");
            scanf("%d", &item.quantidade);
            getchar();
            inserirVetor(&mv, item);

            printf("Listando vetor:\n");
            listarVetor(&mv);

            printf("Ordenando vetor...\n");
            ordenarVetor(&mv);

            printf("Buscar (binária) item no vetor, digite nome: ");
            fgets(nomeBusca, sizeof(nomeBusca), stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
            int posB = buscarBinariaVetor(&mv, nomeBusca);
            printf("Resultado busca binária no vetor: %d\n", posB);
        }
        else if (escolha == 2) {
            printf("Inserir item na lista:\n");
            printf("Nome: ");
            fgets(item.nome, sizeof(item.nome), stdin);
            item.nome[strcspn(item.nome, "\n")] = '\0';
            printf("Tipo: ");
            fgets(item.tipo, sizeof(item.tipo), stdin);
            item.tipo[strcspn(item.tipo, "\n")] = '\0';
            printf("Quantidade: ");
            scanf("%d", &item.quantidade);
            getchar();
            inserirLista(&ml, item);

            printf("Listando lista:\n");
            listarLista(&ml);

            printf("Buscar (sequencial) item na lista, digite nome: ");
            fgets(nomeBusca, sizeof(nomeBusca), stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
            int posL = buscarLista(&ml, nomeBusca);
            printf("Resultado busca sequencial na lista: %d\n", posL);
        }

    } while (escolha != 0);

    // liberar lista
    No *p = ml.inicio;
    while (p) {
        No *tmp = p->proximo;
        free(p);
        p = tmp;
    }

    printf("Encerrando.\n");
    return 0;
}
