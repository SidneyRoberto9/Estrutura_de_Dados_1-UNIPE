// Mini projeto - Árvore Binária de Busca;
// Alunos: Aurélio Miguel Lima Santos e Sidney Roberto Peixoto da Silva

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Estrutura com os dados rgm e nome do aluno
typedef struct{
	int rgm;
	char nome[50];
} data;

// Definindo a estrutura do nó (arvore) com a estrutura de dados do aluno
struct no{
	struct no *esq;
	data aluno;
	struct no *dir;
};

// Exibe menu
int menu();
// Limpa a tela em Windows e GNU/Linux
void clearScreen();
// Limpa o buffer
void limpaBuffer();
// Trata palavras e capitaliza apenas a primeira letra de cada palavra
void tratarPalavra(char []);
// Cria um nó
struct no *criar(int, char []);
// Exibe em pré ordem
void exibirPreOrdem(struct no *);
// Exibe em ordem
void exibirInOrdem(struct no *);
// Exibe em pós ordem
void exibirPosOrdem(struct no *);
// Insere os dados
struct no *inserir(struct no *, int, char []);
// Realiza busca
struct no *busca(struct no *, int);
// Função que percorre a árvore para retornar o menor valor da árvore buscada
struct no *buscaMenor(struct no *);
// Função que remove um elemento da árvore usando o rgm
struct no *remover(struct no *, int);
// Função que deleta cada elemento da árvore
void deletaArvore(struct no *);
// Função que lê os dados de um arquivo e grava na arvore
struct no *manipulaArquivo(struct no *);

int main(void){

    // Inicialização em NULL da arvore
	struct no *arvore = NULL;

	// Variável para parar a tela
    char pause;
    // Variáveis para controle de dados
    int alternativa = 6;

	arvore = manipulaArquivo(arvore);

    // Loop para a execução do programa até que o usuario escolha sair
    while(alternativa != 0){
        // Variável que guarda a opção selecionada pelo usuário
        alternativa = menu();
        // Condição para garantir que uma das alternativas disponíveis seja escolhida
        if(alternativa > 5 || alternativa < 0){
            printf("\n Alternativa invalida, tente novamente!\n\n");
            // Loop até que a condição certa seja selecionada
            while(alternativa > 5 || alternativa < 0){
                // Limpa o buffer
                limpaBuffer();
                printf(" > ");
                scanf("%d", &alternativa);
            }
        }// Limpa a tela
        clearScreen();
        // Switch para executar a alternativa escolhida
        switch (alternativa){
            case 1:{
                printf("\n\t\t\tINSERINDO - RGM e Nome\n");

				char nomeAluno[50];
				int rgmAluno;

				printf("\n Digite um RGM unico e maior que zero para o aluno: ");
				scanf("%d",&rgmAluno);
				limpaBuffer();

				printf (" Digite o nome do aluno: ");
				// Aqui o nome do aluno é recebido pela variável
				scanf("%[^\n]", nomeAluno);
				// O nome é tratado para possuir apenas a primeira letra maiúscula
				tratarPalavra(nomeAluno);

				// A árvore recebe o retorno da função inserir que criar e armazena os dados na arvore criada
				arvore = inserir(arvore, rgmAluno, nomeAluno);

				limpaBuffer();
                printf("\n Pressione qualquer tecla para voltar ao menu. > ");
                scanf("%c", &pause);
                break;
			}
            case 2:{
                printf("\n\t\t\tREMOVENDO UM NO POR RGM\n");

				if(arvore == NULL){
					printf("\n A arvore esta vazia.\n");

				} else {

					int rgmAluno;

					printf("\n Digite um RGM do aluno que quer remover: ");
					scanf("%d",&rgmAluno);
					// Busca o rgm a ser deletado e caso seja encontrado informe o usuário
					if (busca(arvore, rgmAluno) != NULL){
						printf(" e removido!\n");
					}
					// Nova arvore sem o elemento deletado
					arvore = remover(arvore, rgmAluno);
				}

                printf("\n Pressione qualquer tecla para voltar ao menu. > ");
				limpaBuffer();
                scanf("%c", &pause);
                break;
			}
            case 3:{
                printf("\n\t\t\tPESQUISAR POR RGM\n");

				if(arvore == NULL){
					printf("\n A arvore esta vazia.\n");

				} else {

					int rgmAluno;

					printf("\n Digite um RGM do aluno que quer pesquisar: ");
					scanf("%d",&rgmAluno);
					// Chamada e exibição do resultado da busca
					busca(arvore, rgmAluno);
					printf("\n");
				}

                printf("\n Pressione qualquer tecla para voltar ao menu. > ");
				limpaBuffer();
                scanf("%c", &pause);
                break;
            }
            case 4:{
                printf("\n\t\t\tESVAZIANDO A ARVORE\n");

				if(arvore == NULL){
					printf("\n A arvore ja esta vazia.\n");

				} else {

					// Chada da função de que deleta a arvore nó após nó
					deletaArvore(arvore);
					// Árvore zerada
					arvore = NULL;
					// Memória desalocada
					free(arvore);

					printf("\n\n Arvore esvaziada!\n");

				}

                printf("\n Pressione qualquer tecla para voltar ao menu. > ");
                limpaBuffer();
                scanf("%c", &pause);
                break;
            }
            case 5:{
                printf("\n\t\t\tEXIBINDO A ARVORE - PRE, IN ou POS\n");

				if(arvore == NULL){
					printf("\n Arvore vazia!\n");
				} else {
					printf("\n\n Exibicao em pre-ordem:\n\n RGM\t     Nome\n\n");
					exibirPreOrdem(arvore); printf("\n");
					printf("\n Exibicao em in-ordem:\n\n RGM\t     Nome\n\n");
					exibirInOrdem(arvore); printf("\n");
					printf("\n Exibicao em pos-ordem:\n\n RGM\t     Nome\n\n");
					exibirPosOrdem(arvore); printf("\n");
				}

                printf("\n Pressione qualquer tecla para voltar ao menu. > ");
                limpaBuffer();
                scanf("%c", &pause);
                break;
            }
            default:
                printf("\n Programa encerrado!\n\n");
                break;
        }
    }
	return 0;
}

// Função que exibe o menu e retorna a alternativa escolhida pelo usurario
int menu(){
    int alternativa;

    clearScreen();

	printf("\n ALUNO: AURELIO MIGUEL LIMA SANTOS\n");
	printf(" ALUNO: SIDNEY ROBERTO PEIXOTO DA SILVA\n");
	printf(" DISCIPLINA: ESTRUTURA DE DADOS I\n");
	printf(" PROFESSOR: WALLACE BONFIM\n");
    printf("\n\t\t\tEDITOR DE ARVORE\t\t\n\n");
    printf(" 1 - INSERIR - fornecer RGM e Nome\n"
           " 2 - REMOVER UM NO - fornecer o RGM a remover\n"
           " 3 - PESQUISAR - fornecer o RGM a pesquisar\n"
           " 4 - ESVAZIAR A ARVORE\n"
           " 5 - EXIBIR A ARVORE - tres opcoes: PRE, IN ou POS\n"
		   " 0 - SAIR\n"
		   "\n\n\t\t DIGITE SUA OPCAO: ");

    scanf("%d", &alternativa);

    return alternativa;
}
// Função para limpar a tela em Windows e GNU/Linux
void clearScreen(){
#ifdef _WIN32 // Caso seja windows
    system("cls");
#else // Caso não seja
    system ("clear");
#endif
}
//Função para limpar o buffer
void limpaBuffer(){
    while ((getchar()) != '\n');
}
// Função para tratar palavras e capitalizar apenas a primeira letra de cada palavra
void tratarPalavra(char str[]){
    for(int i = 0; str[i] != '\0'; i++){
        //Checa se o primeiro caractere está minúsculo
        if(i == 0){
            if((str[i] >= 'a' && str[i] <= 'z')){
                str[i] = str[i] - 32;  //Subtrai 32 para tornar maiúscula
            }
            continue; //continua o loop
        }
        if(str[i] == ' '){ //Verifica os espaços
            //Se é encontrado espaço checa o próximo caractere
            ++i;
            //Verifica se o próximo caractere é minusculo
            if(str[i] >= 'a' && str[i] <= 'z'){
                str[i] = str[i]-32; //Subtrai 32 para tornar maiúscula
                continue; //continua o loop
            }
        } else {
            //Todos os outros caracteres maiúsculos ficarão minúsculos
            if(str[i] >= 'A' && str[i] <= 'Z'){
                str[i] = str[i] + 32; //Adiciona 32 para fazer ficar minúsculo
            }
        }
    }
}

// Cria um no
struct no *criar(int rgmAluno, char nomeAluno[]){
    // Alocação de memória no nó criado
	struct no *temp = (struct no *)malloc(sizeof(struct no));
	// Atribuição de dado no nó
	temp->aluno.rgm = rgmAluno;
	memcpy(temp->aluno.nome, nomeAluno, strlen(nomeAluno)+1);
	// Próximos nó vazios
	temp->esq = temp->dir = NULL;
	// Retorna a árvore criada
    return temp;
}
// Função recursiva para exibição em pré ordem
void exibirPreOrdem(struct no *tree){

	if (tree != NULL){

		printf(" %-8d-   %s\n", tree->aluno.rgm, tree->aluno.nome);

		exibirPreOrdem(tree->esq);

		exibirPreOrdem(tree->dir);
    }
}
// Função recursiva para exibição em In ordem
void exibirInOrdem(struct no *tree){

    if (tree != NULL){

        exibirInOrdem(tree->esq);

        printf(" %-8d-   %s\n", tree->aluno.rgm, tree->aluno.nome);

        exibirInOrdem(tree->dir);
    }
}
// Função recursiva para exibição em pós ordem
void exibirPosOrdem(struct no *tree){

    if(tree != NULL){

        exibirPosOrdem(tree->esq);

        exibirPosOrdem(tree->dir);

        printf(" %-8d-   %s\n", tree->aluno.rgm, tree->aluno.nome);
    }
}
// Função que cria, aloca e insere os dados nos seus respectivos nós
struct no *inserir(struct no *tree, int rgmAluno, char nomeAluno[]){

	// Se a raiz for nula, então insere a raiz
    if(tree == NULL){
    	// Retorna a árvore criada com dados
        return criar(rgmAluno, nomeAluno);
	}

	// Compara os dados para alocar à esquerda
	if(rgmAluno < tree->aluno.rgm){
		// Aloca os dados à esquerda
		tree->esq = inserir(tree->esq, rgmAluno, nomeAluno);
	} else {
		// Caso contrário aloca à direita
		tree->dir = inserir(tree->dir, rgmAluno, nomeAluno);
	}
	// Caso contrário retorna a árvore sem modificações
	return tree;
}
// Função que busca o nó pelo rgm e informa o usuário
struct no *busca(struct no *tree, int rgmAluno){
	// Os dois primeiros ifs são condições de parada da função recursiva
	// Caso o elemento não seja encontrado
    if(tree == NULL){

    	printf ("\n Nao encontrado\n");
		// O retorno NULL controla o resultado da função
        return NULL;
	}
	// Se o elemento for encontrado
    if(tree->aluno.rgm == rgmAluno){

    	printf("\n %d foi encontrado", rgmAluno);
		// O retorno é a árvore buscada
        return tree;
	}
	// Busca é executada pela esquerda
    if(rgmAluno < tree->aluno.rgm){

        return busca(tree->esq, rgmAluno);
	// Busca é executada pela direita
	} else {

        return busca(tree->dir, rgmAluno);
	}
}

// Função que percorre a árvore para retornar o menor valor da árvore buscada
// Não precisa percorrer toda a árvore
struct no *buscaMenor(struct no *tree){
	// Criação de ponteiro para a árvore buscada
	struct no *current = tree;

	// Loop para buscar pela esquerda até o menor elemento ser encontrado
	while (current && current->esq != NULL)
		current = current->esq;
	// Retorna o menor elemento
	return current;
}

// Função que recebe a árvore e o rgm e deleta um único elemento caso seja encontrado retornando a árvore resultante
struct no *remover(struct no *tree, int rgmAluno){

	// Caso base, se a árvore for nula, retorne-a
	if (tree == NULL)
		return (struct no *)tree;

	// Percurso realizado pelo elemento menor à esquerda da raiz
	if (rgmAluno < tree->aluno.rgm)
		tree->esq = remover(tree->esq, rgmAluno);

	// Percurso realizado pelo elemento maior à direita da raiz
	else if (rgmAluno > tree->aluno.rgm)
		tree->dir = remover(tree->dir, rgmAluno);

	// Caso o elemento não seja menor e nem maior ele foi encontrado
	else {
		// Caso para o nó com apenas um filho ou nenhum
		if (tree->esq == NULL) {
			struct no *temp = tree->dir;
			free(tree);
			return (struct no *)temp;
		}
		else if (tree->dir == NULL) {
			struct no *temp = tree->esq;
			free(tree);
			return (struct no *)temp;
		}

		// Nó com dois filhos, pega o sucessor in ordem o menor elemento da subárvore à direita
		struct no *temp = buscaMenor(tree->dir);

		// O sucessor em in order é copiado para nó
		tree->aluno = temp->aluno;

		// O sucessor in ordem é deletado
		tree->dir = remover(tree->dir, temp->aluno.rgm);
	}
	// A nova árvore é retornada sem o elemento deletado
	return (struct no *)tree;
}
// Função que esvazia a árvore elemento por elemento
void deletaArvore(struct no* tree){

	// Caso a árvore seja nula não faça nada
	if (tree == NULL){
		return;
	}
    // Recursão para cada subárvore
    deletaArvore(tree->esq);
    deletaArvore(tree->dir);

    // Cada um dos nós deletados
    printf("\n Deletando os nos: %d - %s", tree->aluno.rgm, tree->aluno.nome);
    // Memória desalocada
	free(tree);
}

struct no *manipulaArquivo(struct no *arvore){

//iniciando variavel do arquivo
    FILE *arquivo;

// Variáveis para controle de dados
    int nRGM = 0;

//Variaveis para auxiliar no arquivo
    char texto[100], tRGM[50], tnome[50], *token ,stok[2] = ";";

    //Colocar todo conteudo do arquivo na Arvore
    arquivo = fopen("dados.txt","r");

    while(fgets(texto, 100, arquivo)!= NULL){
        token = strtok(texto, stok);
        strcpy(tRGM,token);
        token = strtok(NULL, stok);
        strcpy(tnome,token);

        // retira o \n
        for(int i = 0; i <strlen(tnome); i++)if(tnome[i] == '\n') tnome[i] = '\0';
        // converte o rgm recebido em string para inteiro
        nRGM = atoi(tRGM);

		tratarPalavra(tnome);

        arvore = inserir(arvore, nRGM, tnome);
    }

    fclose(arquivo);

	return arvore;
}
