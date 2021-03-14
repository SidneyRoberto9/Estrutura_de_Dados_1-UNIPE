#define TOTAL 100

#include <stdio.h>
#include <string.h>

typedef struct elementos{
    char nome[50];
    char telefone[20];
    //tipo basico para cada elementos da lista
} Contato;

typedef struct lista{
    Contato vetor[TOTAL];
    int num;
    //tipo lista com um contato e numero de elementos
} S_lista;

S_lista criar(){
    S_lista lista;
    lista.num = -1;

    return lista;
    // Cria uma lista vazia do tipo lista que eu havia criado, colocando o -1 no indice "num",retorna a propria lista
}

int l_vazia(S_lista *lista){
    return (lista->num == -1);
    //Verifica se a lista esta vazia, se contem o -1 no "NUM"
}

int l_cheia(S_lista *lista){
    return (lista->num == TOTAL-1);
    //Verifica se a lista esta cheia, se contem o TOTAL-1 == 99 no "NUM"
}

int tam_lista(S_lista *lista){
    return lista->num + 1;
    //retorna o tamanho da lista
}

int deslocar_d(S_lista * lista, int pos){
    int i;
    for(i = lista->num + 1; i > pos; i--){
        lista->vetor[i] = lista->vetor[i - 1];
    }
    // move os elemetos da lista 1 para direita, para adicionar um novo elemento em algum local
    return 1;
}

int deslocar_e(S_lista * lista, int pos){
    int i;
    for(i = pos; i < (lista->num); i++){
        lista->vetor[i] = lista->vetor[i + 1];
    }
    // move os elemetos da lista 1 para esquerda, para remover um elemento
    return 1;
}

int inserir(S_lista *lista, int pos, Contato dado){
    if(l_cheia(lista)||(pos > lista->num + 1)||(pos < 0)){
        return 0;
        //verificando tudo que pode dizer que a posição ou  a lista esta invalida
    }

    deslocar_d(lista, pos);
    lista->vetor[pos] = dado;
    (lista->num)++;
    // andou pro lado na posição "pos" e adicionou na mesma
    return 1;
}

int remover(S_lista *lista, int pos){
    if((pos > lista->num)||(pos < 0)){
        return 0;
        //verificando tudo que pode dizer que a posição ou  a lista esta invalida
    }

    deslocar_e(lista, pos);
    (lista->num)--;
    // andou pro lado na posição "pos" e removeu na mesma
    return 1;
}

int mostrar(S_lista *lista){
    int i;

    for(i = 0; i <= lista->num; i++){
        printf("Contato: %d\n",i+1);
        printf("Nome: %s\n", lista->vetor[i].nome);
        printf("Telefone: %s\n\n", lista->vetor[i].telefone);
    }
    //simplismente printar na tela tudo
}

void ordem_crescente(S_lista *lista, int n){
    int i,j;
    Contato aux;
    for(i = 1; i < n; i++){
        aux = lista->vetor[i];
        for(j = i; (j > 0) && (strcmp(aux.nome,lista->vetor[j-1].nome)<0); j--){
            lista->vetor[j] = lista->vetor[j - 1];
        }
        lista->vetor[j] = aux;
    }
}

int buscaBinInt(S_lista *lista, int fim, Contato chave){
    int inicio = 0;
    int meio = (inicio + fim )/2;

    while (inicio <= fim){
        if (strcmp(lista->vetor[meio].nome,chave.nome) == 0){
            return meio;
        } else if (strcmp(lista->vetor[meio].nome,chave.nome) > 0){
            fim = meio - 1;
        }else{
            inicio = meio + 1;
        }
    }
    return -1;
}

int buscaBinRec(S_lista *lista, int inicio, int fim, Contato chave) {
    int meio = (inicio + fim)/2;

    if (inicio > fim){
        return -1;
    }
    if (strcmp(lista->vetor[meio].nome,chave.nome) == 0) {
        return meio;
    } else{
        if (strcmp(lista->vetor[meio].nome,chave.nome) > 0){
            return buscaBinRec(lista, inicio, meio - 1, chave);
        }else{
            return buscaBinRec(lista, meio + 1, fim, chave);
        }
    }
}

Contato * Busca(S_lista *lista, int pos){
    if((pos > lista->num)||(pos < 0)){
        return 0;
    }
    return &(lista->vetor[pos]);
    // informo a lista e um ponto do elemento, é verifica se ele é maior ou menor que zero para saber se a posição existe, e retorna a posição correto
}

int compara(Contato dado1, Contato dado2){
    return strcmp(dado1.nome, dado2.nome);
    // comparação basica entre duas strings
}

int retornar_posicao(S_lista *lista, Contato dado){
    int i;
    for(i = 0; i <= lista->num; i++){
        if(compara(lista->vetor[i], dado) == 0){
            return i;
        }
    }
    // retornar o contato igual ao informado
    return -1;
}

int main(){
    Contato c;
    int esc = 0, numero = 0, key = 0, esc2 = 0, pos = 0;

    S_lista Lista = criar();

    if(l_vazia(&Lista)){
        printf("Sua Lista esta Vazia!!");
    }

    if(l_cheia(&Lista)){
        printf("Sua Lista esta Cheia!!");
    }

    while(1){
        ordem_crescente(&Lista, tam_lista(&Lista));
        system("cls");
        setbuf(stdin, NULL);

        printf("-X-X-X-X-X-X- Menu -X-X-X-X-X-X-\n\n");
        printf("1 - Guardar Nome na Lista\n");
        printf("2 - Mostar Nomes da Lista\n");
        printf("3 - Buscar Nome da Lista\n");
        printf("4 - Apagar Nome da Lista\n");
        printf("5 - Sair\n\n\n-->");

        scanf("%d", &esc);
        setbuf(stdin, NULL);
        system("cls");

        if (esc == 1){
            printf("Contato \nNome: ");
            scanf("%[^\n]", &c.nome);
            setbuf(stdin,NULL);
            printf("Telefone: ");
            scanf("%[^\n]", &c.telefone);

            inserir(&Lista, tam_lista(&Lista),c);
            getchar();

        } else if (esc == 2){
            mostrar(&Lista);
            getchar();

        } else if (esc == 3){
            printf("Contato \nNome: ");
            scanf("%[^\n]", &c.nome);

            printf("\n\nQual metodo desaja usar?\n");
            printf("1 - Busca Binaria Recursiva\n");
            printf("2 - Busca Binaria Iterativa\n");
            printf("\n--> ");
            scanf("%d", &esc2);

            if(esc2 == 1){
               pos = buscaBinRec(&Lista, 0, tam_lista(&Lista), c);
            }else if(esc2 == 2){
               pos = buscaBinInt(&Lista, tam_lista(&Lista), c);
            }

            printf("\nResultado da busca:\n");
            if (Busca(&Lista, pos) != NULL){
                printf("O Contato %s Esta na lista!\n", Busca(&Lista, pos));
            } else {
                printf("O Contato nao Esta na lista!\n");
            }
            setbuf(stdin,NULL);
            getchar();

        } else if (esc == 4){
            printf("Infome o Numero do elemento para ser removido da lista: ");
            scanf("%d", &numero);
            remover(&Lista, numero - 1);
            getchar();

        } else if (esc == 5){
             break;
        }
    }
    return 0;
}
