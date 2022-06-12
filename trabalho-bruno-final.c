#include <stdio.h>

struct produto {
    int codigo;
    char descricao[61];
    char fornecedor[61];
    int quantidadeEstoque;
    double preco;
};

void inicializar(struct produto *produtos, int tam);
void listar(struct produto *produtos, int pos);
void cadastrar(struct produto *produtos, int tam, int *pos);
void encontrar(struct produto *produtos, int pos, int codigo);
void comprar(struct produto *produtos, int pos, int codigo, int quantidade);
void vender(struct produto *produtos, int pos, int codigo, int quantidade);

int main() {
    const int tam = 50; // Numero de produtos diferentes no vetor
    struct produto produtos[tam]; // Vetor de produtos
    int pos = 0; // Posição onde o próximo produto será cadastrado
    int opt; // Variável de opção de menu

    // Variaveis com valores inseridos pelo usuário necessárias
    // em algumas opções do menu.
    int codigo;
    int quantidade; 

    inicializar(produtos, tam);
    
    do {
        printf("MENU\n");
        printf("1. Cadastrar novo produto\n");
        printf("2. Listar todos os produtos\n");
        printf("3. Encontrar um produto\n");
        printf("4. Comprar um produto\n");
        printf("5. Vender um produto\n");
        printf("0. Sair\n");
        printf("> ");
        scanf("%d", &opt);

        switch(opt) {
        case 1: cadastrar(produtos, tam, &pos); break;
        case 2: listar(produtos, pos); break;
        case 3:
            printf("Codigo: ");
            scanf("%d", &codigo);
            encontrar(produtos, pos, codigo);
            break;
        case 4:
            printf("Codigo: ");
            scanf("%d", &codigo);
            printf("Quantidade: ");
            scanf("%d", &quantidade);
            comprar(produtos, pos, codigo, quantidade);
            break;
        case 5:
            printf("Codigo: ");
            scanf("%d", &codigo);
            printf("Quantidade: ");
            scanf("%d", &quantidade);
            vender(produtos, pos, codigo, quantidade);
            break;
        case 0: printf("Encerrando o programa\n"); break;
        default: printf("Opcao invalida\n"); break;
        }
            
    } while(opt != 0);

    return 0;
}

void inicializar(struct produto *produtos, int tam) {
    /* Inicializa todos os elementos do vetor de produtos com valores padrão */
    for(int i = 0; i < tam; i++) {
        produtos[i].codigo = -1;
        produtos[i].descricao[0] = '\0';  // string vazia
        produtos[i].fornecedor[0] = '\0'; // string vazia
        produtos[i].quantidadeEstoque = 0;
        produtos[i].preco = 0;
    }
}

void listar(struct produto *produtos, int pos) {
    /* Lista todos os produtos no vetor */
    for(int i = 0; i < pos; i++) {
        printf("Codigo: %d\n", produtos[i].codigo);
        printf("Descricao: %s\n", produtos[i].descricao);
        printf("Fornecedor: %s\n", produtos[i].fornecedor);
        printf("Quantidade em estoque: %d\n", produtos[i].quantidadeEstoque);
        printf("Preco: %lf\n\n", produtos[i].preco);
    }
}

void cadastrar(struct produto *produtos, int tam, int *pos) {
    /* Cadastra um novo produto no vetor de produtos. O novo produto
       não pode possuir código igual ao de nenhum outro produto já existente
       no vetor e o nem pode ter valor negativo ou zero. */
    int codigo;

    // Verifica se há espaço no vetor para novos cadastros
    if(*pos == tam) {
        printf("Vetor de produtos cheio. Impossivel cadastrar novo item\n");
        return;
    }
    
    printf("Codigo: ");
	scanf(" %d", &codigo);

    // Verifica se o código inserido é valido
    if(codigo <= 0) {
        printf("Codigo deve ser um valor maior ou igual a 1\n");
        return;
    }

    // Verifica se o código não pertence a outro produto do vetor
    for(int i = 0; i < *pos; i++) {
        if(produtos[i].codigo == codigo) {
            printf("Codigo inserido ja pertence a outro produto\n");
            return;
        }
    }

    // Caso passe em todos os testes, continua o cadastro
    produtos[*pos].codigo = codigo;
	printf("Descricao: ");
	scanf(" %[^\n]", produtos[*pos].descricao);
	printf("Fornecedor: ");
	scanf(" %[^\n]", produtos[*pos].fornecedor);
	printf("Quantidade: ");
    scanf(" %d", &produtos[*pos].quantidadeEstoque);
	printf("Preco: ");
    scanf(" %lf", &produtos[*pos].preco);
    (*pos)++; // Atualiza a variável que armazena em que posição o próximo item será inserido.
}

void encontrar(struct produto *produtos, int pos, int codigo) {
    /* Encontra um produto no vetor com o mesmo código passado pelo usuário e mostra
       esse produto. Caso o produto não exista, uma mensagem é exibida */
    for(int i = 0; i < pos; i++) {
        if(produtos[i].codigo == codigo) {
            printf("Produto encontrado na posicao %d do vetor\n", i);
            printf("Codigo: %d\n", produtos[i].codigo);
            printf("Descricao: %s\n", produtos[i].descricao);
            printf("Fornecedor: %s\n", produtos[i].fornecedor);
            printf("Quantidade em estoque: %d\n", produtos[i].quantidadeEstoque);
            printf("Preco: %lf\n\n", produtos[i].preco);
            return; 
        }
    }
    // Se o laço acabar (ou seja, o return dentro do if não foi chamado) isso significa
    // que o produto com o código passado pelo usuário não existe e então, uma mensagem
    // é mostrada na tela, avisando-o
    printf("Produto com codigo %d nao encontrado\n", codigo);
}

void comprar(struct produto *produtos, int pos, int codigo, int quantidade) {
    /* Aumenta a quantidade em estoque do produto que tiver o código passado pelo usuário.
       Caso o produto com o código passado não exista, uma mensagem é exibida */
    for(int i = 0; i < pos; i++) {
        if(produtos[i].codigo == codigo) {
            produtos[i].quantidadeEstoque += quantidade;
            printf("Compra realizada com sucesso\n");
            return; // Sem necessidade de continuar o laço uma vez que o produto foi encontrado
        }
    }
    printf("Produto com codigo %d nao encontrado\n", codigo);
}

void vender(struct produto *produtos, int pos, int codigo, int quantidade) {
    /* Diminui a quantidade em estoque do produto que tiver o código passado pelo usuário.
       Caso o produto com o código passado não exista, uma mensagem é exibida.
       Caso a quantidade de venda seja maior que a quantidade em estoque, a venda não
       é feita e uma mensagem é exibida */
    for(int i = 0; i < pos; i++) {
        if(produtos[i].codigo == codigo) {
            if(produtos[i].quantidadeEstoque - quantidade < 0) {
                printf("Quantidade de venda maior que quantidade do produto em estoque\n");
                return;
            }
            produtos[i].quantidadeEstoque -= quantidade;
            printf("Venda realizada com sucesso\n");
            return; // Sem necessidade de continuar o laço uma vez que o produto foi encontrado
        }
    }
    printf("Produto com codigo %d nao encontrado\n", codigo);
}
