#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct alunos {
    char nome[50];
    char endereco[100];
    char telefone[15];
    int idade;
} alunos;

typedef struct curso {
    char codigo [10];
    char nome [50];
    char instrutor [50];
} curso;

typedef struct matricula {
    //*alunos;
    //*curso;
    int numero;
} matricula;

void menu(){
    printf("---MENU---\n");
    printf("1. Cadastrar aluno.\n");
    printf("2. Procurar aluno.\n");
    printf("3. Atualizar aluno.\n");
    printf("4. Descadastrar aluno.\n\n");
    printf("5. Casdastrar curso.\n");
    printf("6. Procurar curso.\n");
    printf("7. Atualizar curso.\n");
    printf("8. Descadastrar curso.\n\n");
    printf("9. Matricular Aluno.\n");
    printf("10. Procurar Matricula.\n");
    printf("11. Cancelar matricula.\n");
    printf("12. Listar todas as matricular feitas.\n\n");
    printf("13. Listar todos os cursos cadastrados.\n");
    printf("14. Listar todos os alunos cadastrados.\n");
    printf("15. Listar todos os alunos de um curso.\n");
    printf("16. Listar todos os alunos de todos os cursos.\n\n");
    printf("17. Listar todos os cursos de um aluno. \n");
    printf("18. Listar todos os cursos de todos os alunos.\n");
    printf("19. Listar todas as matriculas de um aluno. \n");
    printf("20. Listar todas as matriculas de um curso. \n\n");
    printf("21. Listar alunos cadastrados sem curso.\n");
    printf("22. Listar cursos cadastrados sem alunos.\n");
    printf("23. Sair.\n\n");
    printf("Escolha uma opcao: ");
}

void cadastrarAluno(){
    alunos a;
    printf("Digite seu nome: ");
    fgets(a.nome, 50, stdin);
    printf("Digite seu endereço: ");
    fgets(a.endereco, 100, stdin);
    printf("Digite seu telefone: ");
    fgets(a.telefone, 15, stdin);
    printf("Digite sua idade: ");
    scanf("%d", &a.idade);

    
}

int main(){
    int opcao;
    menu();
    scanf("%d", &opcao);
    do
    {
        switch(opcao){
        case 1:
            //cadastrar aluno
            break;
        case 2:
            //procurar aluno
            break;
        case 3:
            //atualizar aluno
            break;
        case 4:
            //descadastrar aluno
            break;
        case 5:
            //cadastrar curso
            break;
        case 6:
            //procurar curso
            break;
        case 7:
            //atualizar curso
            break;
        case 8:
            //descadastrar curso
            break;
        case 9:
            //matricular aluno
            break;
        case 10:
            //procurar matricula
            break;
        case 11:
            //cancelar matricula
            break;
        case 12:
            //listar todas as matriculas feitas
            break;
        case 13:
            //listar todos os cursos cadastrados
            break;
        case 14:
            //listar todos os alunos cadastrados
            break;
        case 15:
            //listar todos os alunos de um curso
            break;
        case 16:
            //listar todos os alunos de todos os cursos
            break;
        case 17:
            //listar todos os cursos de um aluno
            break;
        case 18:
            //listar todos os cursos de todos os alunos
            break;
        case 19:
            //listar todas as matriculas de um aluno
            break;
        case 20:
            //listar todas as matriculas de um curso
            break;
        case 21:
            //listar alunos cadastrados sem curso
            break;
        case 22:
            //listar cursos cadastrados sem alunos
            break;
        case 23:
            //sair
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
    }
    } while (opcao != 23);
    
        return 0;
}
