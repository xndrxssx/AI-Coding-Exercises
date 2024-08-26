#include <stdio.h>
#include <stdlib.h>
// Defina o número de cidades
#define NUM_CIDADES 20
// Para fins de aprendizado, vou definir essa patifaria abaixo  
#define ARAD 0
#define ZERIND 1
#define ORADEA 2
#define SIBIU 3
#define TIMISOARA 4
#define LUGOJ 5
#define MEHADIA 6
#define DOBRETA 7
#define CRAIOVA 8
#define RIMNICU_VILCEA 9
#define PITESTI 10
#define FAGARAS 11
#define BUCHAREST 12
#define GIURGIU 13
#define URZICENI 14
#define HIRSOVA 15
#define EFORIE 16
#define VASLUI 17
#define IASI 18
#define NEAMT 19
// Fim da bagunça

// Para o print ficar bonitinho:
const char* nomes[NUM_CIDADES] = {
    "Arad",
    "Zerind",
    "Oradea",
    "Sibiu",
    "Timisoara",
    "Lugoj",
    "Mehadia",
    "Dobreta",
    "Craiova",
    "Rimnicu Vilcea",
    "Pitesti",
    "Fagaras",
    "Bucharest",
    "Giurgiu",
    "Urziceni",
    "Hirsova",
    "Eforie",
    "Vaslui",
    "Iasi",
    "Neamt"
};

typedef struct {
    int adj[NUM_CIDADES][NUM_CIDADES];
    // Matriz de adjacência, é 1 quando uma cidade está ligada a outra

    int visitado[NUM_CIDADES];
    // Array para verificar se o nó já foi visitado          
} Grafo;

typedef struct {
    int itens[NUM_CIDADES];
    int frente, tras;
} Fila;

void inicializaFila(Fila* f) {
    f->frente = 0;
    f->tras = -1;
}

int filaVazia(Fila* f) {
    return f->tras < f->frente;
}

void enfileira(Fila* f, int valor) {
    f->itens[++f->tras] = valor;
    // Primeira chamada:
    // f->tras passa de -1 para 0 e a primeira coisa é colocada na posição 0
    // Segunda chamada:
    // f->tras passa de 0 para 1 e a segunda coisa é colocada na posição 1
}

int desenfileira(Fila* f) {
    return f->itens[f->frente++];
    // Retorna o primeiro item da fila
    // Depois de retornar o primeiro item, f->frente passa de 0 para 1
    // Atualizando agora o primeiro da fila
}

void inicializaGrafo(Grafo* g) {
    // Inicializando o babado todo com zeros e tal...
    for (int i = 0; i < NUM_CIDADES; i++) {
        for (int j = 0; j < NUM_CIDADES; j++) {
            g->adj[i][j] = 0;
        }
        g->visitado[i] = 0;
    }
}

void adicionaAresta(Grafo* g, int origem, int destino) {
    g->adj[origem][destino] = 1;
    g->adj[destino][origem] = 1;
    // Se o grafo for não direcionado, comentar essa última linha...  
}

void bfs(Grafo* g, int inicio, int objetivo) {
    Fila f; // Armazena os nós que foram visitados mas não foram expandidos ainda 
    inicializaFila(&f);
    enfileira(&f, inicio); // Coloca Arad no início da fila
    g->visitado[inicio] = 1; // E como estamos saindo dele, ele foi visitado
    // Lembrando que ARAD == 0

    while (!filaVazia(&f)) {
        int atual = desenfileira(&f);
        //Primeira iteração, recebe ARAD
        printf("Visitando: %s (Numero: %d)\n", nomes[atual], atual);

        if (atual == objetivo) {
            printf("Objetivo %s encontrado!\n", nomes[objetivo]);
            return;
        }

        for (int i = 0; i < NUM_CIDADES; i++) {
            if (g->adj[atual][i] == 1 && !g->visitado[i]) {
                // Só entra aqui se:
                // Tiver uma aresta entre o nó atual e o nó i
                // E o nó i não foi visitado ainda
                enfileira(&f, i);
                // Se for um vizinho válido, ele é adicionado a borda
                g->visitado[i] = 1;
                // Marca como visitado para não passar de novo
            }
        }
    }
    printf("Objetivo %d não encontrado.\n", objetivo);
}

int main() {
    Grafo g;
    inicializaGrafo(&g);

    adicionaAresta(&g, ARAD, ZERIND);            // Arad -> Zerind
    adicionaAresta(&g, ARAD, SIBIU);             // Arad -> Sibiu
    adicionaAresta(&g, ARAD, TIMISOARA);         // Arad -> Timisoara
    adicionaAresta(&g, ZERIND, ORADEA);          // Zerind -> Oradea
    adicionaAresta(&g, ORADEA, SIBIU);           // Oradea -> Sibiu
    adicionaAresta(&g, SIBIU, FAGARAS);          // Sibiu -> Fagaras
    adicionaAresta(&g, SIBIU, RIMNICU_VILCEA);   // Sibiu -> Rimnicu Vilcea
    adicionaAresta(&g, TIMISOARA, LUGOJ);        // Timisoara -> Lugoj
    adicionaAresta(&g, LUGOJ, MEHADIA);          // Lugoj -> Mehadia
    adicionaAresta(&g, MEHADIA, DOBRETA);        // Mehadia -> Dobreta
    adicionaAresta(&g, DOBRETA, CRAIOVA);        // Dobreta -> Craiova
    adicionaAresta(&g, CRAIOVA, RIMNICU_VILCEA); // Craiova -> Rimnicu Vilcea
    adicionaAresta(&g, CRAIOVA, PITESTI);        // Craiova -> Pitesti
    adicionaAresta(&g, RIMNICU_VILCEA, PITESTI); // Rimnicu Vilcea -> Pitesti
    adicionaAresta(&g, PITESTI, BUCHAREST);      // Pitesti -> Bucharest
    adicionaAresta(&g, FAGARAS, BUCHAREST);      // Fagaras -> Bucharest
    adicionaAresta(&g, BUCHAREST, GIURGIU);      // Bucharest -> Giurgiu
    adicionaAresta(&g, BUCHAREST, URZICENI);     // Bucharest -> Urziceni
    adicionaAresta(&g, URZICENI, HIRSOVA);       // Urziceni -> Hirsova
    adicionaAresta(&g, HIRSOVA, EFORIE);         // Hirsova -> Eforie
    adicionaAresta(&g, URZICENI, VASLUI);        // Urziceni -> Vaslui
    adicionaAresta(&g, VASLUI, IASI);            // Vaslui -> Iasi
    adicionaAresta(&g, IASI, NEAMT);             // Iasi -> Neamt

    bfs(&g, ARAD, BUCHAREST);

    return 0;
}
