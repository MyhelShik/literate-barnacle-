
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char titulo[100], autor[100];
    int ano;
    int disponivel; //1 para disponivel e 0 se emprestado
}livro;

typedef struct 
{ 
    int id; 
    char nome[50]; 
    int cc;
}leitor;

typedef struct 
{ 
    int idLivro; 
    int idLeitor; 
    char dataEmprestimo[11]; 
    char dataDevolucao[11]; 
} emprestimo;

#define max_livros 2
#define max_leitor 2
#define max_emprestimo 50



leitor *leitores[max_leitor];

void GerirLeitores()
{
    int temp_leitor = 0; // to move to structure public VAR
    int opcao;
    int removeID = 0;
    do
    {
        printf("\n Menu Leitores:\n"); 
        printf("1. Adicionar leitores\n"); 
        printf("2. Listar leitores\n"); 
        printf("3. Remover leitores\n");
        printf("6. Sair ao menu principal\n"); 
        printf("Escolha uma opção: "); 
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
            if(temp_leitor >= max_leitor)
            {
                printf("Fora do numero leitores accessiveis,(%d > valor maximo de leitores) tenta noutra vez ou remove leitores para adiccionar.",temp_leitor);
                break;
            }
            else
            {
                printf("Adicionar leitores:\n");
                for (int i = 0; i < max_leitor; i++)
                {
                    if (leitores[i] == NULL) 
                        {
                            leitores[i] = malloc(sizeof(leitor)); // Allocação da memória do apontador do leitor AKA. objeto -> leitor *leitores[max_leitor];
                            if (!leitores[i]) 
                            {
                                printf("Erro ao alocar memória para leitores[%d]\n", i);
                                exit(1);
                            }
                        }

                    printf("Insira o nome do leitor %d:", i+1);
                    scanf(" %[^\n]", &leitores[i]->nome);
                    printf("Insira o numero do cartão de cidadão:");
                    scanf("%d", &leitores[i]->cc);

                    leitores[i]->id = i +1; // unique id assign
                    temp_leitor++; // count of max leitor if statement check   
                    
                    char continuar;
                    printf("Deseja adicionar outro leitor? (s/n): ");
                    scanf(" %[^\n]", &continuar);
                    
                    if(temp_leitor >= max_leitor)
                    {
                        printf("Fora do numero leitores accessiveis,(%d > valor maximo de leitores) tenta noutra vez ou remove leitores para adiccionar.",temp_leitor);
                        break;
                    }
                    else
                    {
                        if (continuar != 's' || continuar != 'S') 
                            continue;
                        else if(continuar != 'n' || continuar != 'N')
                            break;
                    }
                }
            }
            break;
            
            case 2:
            printf("Listar leitores:\n");
            for (int i = 0; i < max_leitor; i++)
            {
                if(leitores[i]->id != 0)
                    printf("leitor: %d \n nome:%s - CC:%d\n",i+1,leitores[i]->nome,leitores[i]->cc);
            }    
            break;

            case 3:
                printf("Remover leitores:\n");
                scanf("%d",&removeID);
                for (int i = 0; i < max_leitor; i++)
                {
                    if (leitores[i]->id == removeID)
                    {
                        printf("Leitor com id %d, nome %s e cc %d, foi removido com successo!",leitores[i]->id,leitores[i]->nome,leitores[i]->cc);

                        leitores[i]->id = 0;
                        strcpy(leitores[i]->nome, "");
                        leitores[i]->cc = 0;
                        temp_leitor--;
                    }
                }
                break;
            
            default:
                printf("Opção inválida. Tente novamente...\n");
                break;
        }
    } while (opcao !=6);
    
}

void menu_principal() 
{
    int opcao;
    do
    {
        printf("\nMenu Principal:\n"); 
        printf("1. Gerir Livros\n"); 
        printf("2. Gerir Leitores\n"); 
        printf("3. Registar Emprestimo\n"); 
        printf("4. Registar Devolução\n"); 
        printf("5. Exibir Relatorios\n"); 
        printf("6. Sair\n"); 
        printf("Escolha uma opção: "); 
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                GerirLivros();
                break;
            case 2:
                //GerirLeitores();
                GerirLeitores();
                break;
            case 3:
                //RegistarEmprestimo();
                break;
            case 4:
                //RegistarDevolucao();
                break;
            case 5:
                //ExibirRelatorio();
                break;
            case 6:
                //printf("A sair...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente...\n");
        }
    } while (opcao !=6);

return 0;
}
void GerirLivros()
{
    int opcao2;
    printf("\nMenu Principal:\n"); 
        printf("1. Adicionar Livro\n"); 
        printf("2. Listar Livros\n"); 
        printf("3. Pesquisar Livro\n"); 
        printf("4. Remover livro\n");  
        printf("5. Sair\n"); 
        printf("Escolha uma opção: "); 
        scanf("%d", &opcao2);

        switch(opcao2)
        {
            case 1:
                AdicionarLivro();
                break;
            case 2:
                ListarLivros();
                break;
            case 3:
                PesquisarLivro();
                break;
            case 4:
                RemoverLivro();
                break;
            case 5:
                printf("A sair...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente...\n");
                return GerirLivros();
        }
     while (opcao2 !=5);
     return menu_principal();
}

livro *livros[max_livros];  // Array de ponteiros para armazenar os livros
int num_livros_adicionados = 0;  // Contador de livros adicionados 

void AdicionarLivro()
{
    livro *novolivro;  // Ponteiro para um livro
    static int contador_id = 0;  // Variável estática para manter o contador de IDs
    int opcao;
    // bloco para adicionar múltiplos livros
    for (int i = 0; i < max_livros; i++) 
    {
        printf("A adicionar livro %d de %d\n", i + 1, max_livros);

        novolivro = (livro *)malloc(sizeof(livro));  // Aloca memória para um livro
        if (novolivro == NULL) 
        {
            printf("Falha na alocação de memória\n");
            return;
        }

        novolivro->id = ++contador_id;  // Aumenta o ID para o próximo livro

        fflush(stdin);
        // Leitura do título com fgets
        printf("Titulo do livro: \n");
        fgets(novolivro->titulo, sizeof(novolivro->titulo), stdin);
        novolivro->titulo[strcspn(novolivro->titulo, "\n")] = '\0';  // Remove o caractere de nova linha

        
        // Leitura do autor com fgets
        printf("Autor do livro: \n");
        fgets(novolivro->autor, sizeof(novolivro->autor), stdin);
        novolivro->autor[strcspn(novolivro->autor, "\n")] = '\0';  // Remove o caractere de nova linha

        fflush(stdin);
        // Leitura do ano com fgets e conversão para inteiro
        printf("Ano do livro: \n");
        char ano_input[10];
        fgets(ano_input, sizeof(ano_input), stdin);
        sscanf(ano_input, "%d", &novolivro->ano);  // Converte a string para um inteiro

        fflush(stdin);    
        // Exibe os dados do livro adicionado
        printf("Livro adicionado: ID %d - Titulo: %s, Autor: %s, Ano: %d\n", novolivro->id, novolivro->titulo, novolivro->autor, novolivro->ano);

        // Armazena o livro no array
        livros[num_livros_adicionados++] = novolivro;

        // Pergunta ao utilizador se deseja adicionar mais livros
        char continuar;
        printf("Deseja adicionar outro livro? (s/n): ");
        scanf(" %c", &continuar);  // Lê a resposta
        getchar();  // Limpa o buffer de entrada

        if (continuar != 's' && continuar != 'S') 
        {
            break;  // Sai do bloco caso o utilizador não quiser adicionar mais livros
            
        }
        
    }
    printf("--------------------\n");
    opcao=1;
    if(opcao==1)
    {
        return GerirLivros();
    }
    
}
void ListarLivros() 
{
    
    char opcao[40];
    // Exibe os livros cadastrados
    do
    {
        for (int i = 0; i < num_livros_adicionados; i++) 
        {
            printf("ID: %d\n", livros[i]->id);
            printf("Titulo: %s\n", livros[i]->titulo);
            printf("Autor: %s\n", livros[i]->autor);
            printf("Ano: %d\n", livros[i]->ano);
            printf("--------------------\n");
        }
    if (num_livros_adicionados == 0) 
    {
        printf("Nenhum livro no sistema.\n");
        return GerirLivros();
    }
    fflush(stdin);
    printf("Para sair escreva (s/n)");
    scanf("%c", &opcao);
    break;
    } while (opcao != 's' && opcao !='S');
    
    return GerirLivros();
    
    }    


void PesquisarLivro() 
{
    int opcao;
    do{
    getchar();
    char titulo_busca[100];
    printf("Digite o titulo do livro que deseja pesquisar: ");
    fgets(titulo_busca, sizeof(titulo_busca), stdin);
    titulo_busca[strcspn(titulo_busca, "\n")] = '\0';  // Remove o caractere de nova linha

    int encontrado = 0;
    for (int i = 0; i < num_livros_adicionados; i++) 
    {
        if (strstr(livros[i]->titulo, titulo_busca) != NULL) 
        {  // Verifica se o título contém o texto de busca
            printf("Livro encontrado: ID: %d\n", livros[i]->id);
            printf("Titulo: %s\n", livros[i]->titulo);
            printf("Autor: %s\n", livros[i]->autor);
            printf("Ano: %d\n", livros[i]->ano);
            printf("--------------------\n");
            encontrado = 1;
        }
    }

    if (!encontrado) 
    {
        printf("Nenhum livro encontrado com o título '%s'.\n", titulo_busca);
    }
    fflush(stdin);
    printf("Deseja procurar outro livro? (s/n) ");
    scanf("%c", &opcao);
    
    }while(opcao == 'n' || opcao =='N');
    printf("--------------------\n");

     opcao=1;
    if(opcao==1)
    {
        return GerirLivros();
    }
}
// Função para remover um livro por ID
void RemoverLivro() 
{
    int id; int id_remover;
    int i, j;
    int encontrado = 0;
    printf("Digite o ID do livro que deseja remover: ");
    scanf("%d", &id_remover);
    // Procura pelo livro com o ID fornecido
    for (i = 0; i < num_livros_adicionados; i++) 
        {
            if (livros[i]->id == id) 
            {
                // Livro encontrado
                printf("Livro encontrado: ID %d - Titulo: %s, Autor: %s, Ano: %d\n", livros[i]->id, livros[i]->titulo, livros[i]->autor, livros[i]->ano);

            }
                // Desloca os livros seguintes para preencher a posição
            for (j = i; j < num_livros_adicionados - 1; j++) 
            {
                livros[j] = livros[j + 1];
            }

            // Decrementa o contador de livros
            num_livros_adicionados--;

            printf("Livro com ID %d removido com sucesso!\n", id);
            encontrado = 1;
            break;
        }
        return;

 if (!encontrado) 
    {
        printf("Livro com ID %d não encontrado.\n", id);
    }

    return GerirLivros();
}


void exibirRelatorioLivrosDisponiveis() 
{
    printf("Relat�rio de Livros Dispon�veis\n");
    for (int i = 0; i < num_livros_adicionados; i++) 
    {
        printf("%d Livro ID: %d\n",i, livros[i]->id);        
    }
 
}

void exibirRelatorioLivrosEmprestados() 
{
    printf("Relat�rio de Livros Emprestados\n");
    // C�digo para listar livros emprestados
}

void exibirRelatorioLeitoresAtivos() 
{
    printf("Relatório de Leitores Ativos:\n");
    for (int i = 0; i < max_leitor; i++) 
    {
        printf("Leitor Ativo: ID: %d, Nome: %s, CC: %d\n", leitores[i]->id, leitores[i]->nome, leitores[i]->cc);
        printf("Leitor Ativo: ID: %d, Nome: %s, CC: %d\n", leitores[i]->id, leitores[i]->nome, leitores[i]->cc);
        
    }
}


void exibirRelatorioLivrosMaisEmprestados() 
{
    printf("Relat�rio de Livros Mais Emprestados\n");
    // C�digo para listar livros mais emprestados
}


void main1()
{
                printf("menu \"Exibir Relat�rios\":\n");
                printf("1. Relat�rio de Livros Dispon�veis\n");
                printf("2. Relat�rio de Livros Emprestados\n");
                printf("3. Relat�rio de Leitores Ativos\n");
                printf("4. Voltar ao Menu Principal\n");
                printf("Escolha uma op��o: ");
                
                int subOpcao;
                scanf("%d", &subOpcao);

                switch (subOpcao) 
                {
                    case 1:
                        exibirRelatorioLivrosDisponiveis();
                        break;
                    case 2:
                        exibirRelatorioLivrosEmprestados();
                        break;
                    case 3:
                        exibirRelatorioLeitoresAtivos();
                        break;
                    case 4:
                        printf("Voltando ao Menu Principal\n");
                        break;
                    default:
                        printf("Op��o inv�lida! Tente novamente.\n");
                        break;
                }
               

}

int main()
{
    menu_principal();
    // GerirLeitores();
    // exibirRelatorioLeitoresAtivos();
    return 0;
}
