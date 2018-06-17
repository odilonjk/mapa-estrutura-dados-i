#include <stdio.h>
#include <stdlib.h>

/**
 * Aluno: Odilon Jonathan Kröger
 * RA: 17150705
 * Professor: Marcelo Lessa
 * 
 * O código fonte desta atividade também se encontra em meu github:
 * https://github.com/odilonjk/mapa-estrutura-senhas-i
 */ 

//  Constantes
#define DESLIGAR 0
#define PEGAR_SENHA 1
#define CHAMAR_SENHA 2 

//  Definindo tipo fila
typedef struct {
    int senhas[10];
    int fim;
} tipo_fila;

//  Variáveis globais
tipo_fila fila;
// fila.fim = 0;
int acao = 1;
int senha = 0;
int senhaEmAtendimento = 0;

void imprimeFila()
{
    if(fila.senhas[0] == 0)
    {
        printf("Não há ninguém na fila aguardando atendimento.\n");
    }
    else
    {
        printf("Senhas: ");
        int i;
        for(i = 0; i < fila.fim; i++)
        {
            printf("%d ", fila.senhas[i]);
        }
        printf("\n");
    }
};

void chamaSenhaDaFila()
{
    if(fila.fim != 0)
    {
        senhaEmAtendimento = fila.senhas[0];
        int i;
        for(i = 0; i < fila.fim; i++)
        {
            fila.senhas[i] = fila.senhas[i+1];
        }
        fila.senhas[fila.fim-1] = 0;
        fila.fim--;
    }
};

void enfileiraNovaSenha()
{
    if(fila.fim == 10)
    {
        printf("A fila já está completa, tente novamente mais tarde.\n");
    }
    else
    {
        senha++;
        fila.senhas[fila.fim] = senha;
        if(fila.fim < 10)
        fila.fim++;
    }
};

void encerrarSistema()
{
    if(fila.senhas[0] == 0)
    {
        printf("Encerrando sistema...\n\n");
    }
    else
    {
        printf("ERRO: Não é possível encerrar o sistema enquanto houver clientes aguardando atendimento.\n");
        acao = 1;
    }
};

void mostraAtendimento()
{
    printf(" Atendimento: \n\n");
    if(senhaEmAtendimento == 0)
    {
        printf(" Senha anterior: -\n");
        printf(" Senha atual: -\n");
    }
    else
    {
        if(senhaEmAtendimento == 1)
        {
            printf(" Senha anterior: -\n");
        }
        else
        {
            printf(" Senha anterior: %d\n", senhaEmAtendimento-1);
        }
        printf(" Senha atual: %d\n", senhaEmAtendimento);
    }
    printf(" Próxima senha: %d\n", senhaEmAtendimento+1);
};

//  Função que exibe o menu
void mostraMenu()
{
    printf("_____________________\n\n");
    printf("-> Açougue do José <-\n");
    printf("_____________________\n");
    printf("                    \n");
    mostraAtendimento();
    printf("_____________________\n");
    printf("\n Opções:\n");
    printf("                    \n");
    printf(" (1) Pegar senha.   \n");
    printf(" (2) Chamar senha.  \n");
    printf(" (0) Desligar.      \n");
    
    printf("\n");
    printf("____________________\n\n");
};

//  Limpa a tela considerando o sistema operacional para executar o comando correto
void limpaTela()
{
    #ifdef _WIN32
    printf("cls");
    #endif
    #ifdef linux
    printf("\033c");
    #endif
};

//  Função que captura a ação escolhida pelo usuário e retorna esta ação
void obtemAcao()
{
    printf("\nEscolha uma opção: ");
    scanf("%d", &acao);
    while(acao < 0 || acao > 2)
    {   
        limpaTela();
        mostraMenu();
        imprimeFila();
        printf("\nDesculpe, esta opção não existe! Tente novamente: ");
        scanf("%d", &acao);
    }
};

//  Trata a ação selecionada pelo usuário
void executarAcao()
{
    switch(acao)
    {
        case PEGAR_SENHA:
            enfileiraNovaSenha();
            break;
        case CHAMAR_SENHA:
            chamaSenhaDaFila();
            break;
        case DESLIGAR:
            encerrarSistema();
            break;
        default:
            break;
    }
};

int main()
{
    
    limpaTela();
    //  Loop de execução do sistema
    while(acao > 0)
    {
        mostraMenu();
        imprimeFila();
        obtemAcao();
        limpaTela();
        executarAcao();
    }
    
    return 0;
}
