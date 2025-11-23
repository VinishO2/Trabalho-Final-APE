#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------------
// ESTRUTURAS
//---------------------------------------------------------------
// Representa um aluno na lista encadeada
typedef struct Aluno {
    char nome[50];
    char endereco[100];
    char telefone[15];
    int idade;
    struct Aluno *prox; // ponteiro para o próximo aluno da lista
} Aluno;

// Representa um curso na lista encadeada
typedef struct Curso {
    char codigo[10];
    char nome[50];
    char instrutor[50];
    struct Curso *prox; // ponteiro para o próximo curso da lista
} Curso;

// Representa uma matrícula (ligando aluno e curso)
typedef struct Matricula {
    Aluno *aluno;     // referência ao aluno matriculado
    Curso *curso;     // referência ao curso matriculado
    int numero;       // número sequencial da matrícula
    struct Matricula *prox; // ponteiro para próxima matrícula
} Matricula;

//---------------------------------------------------------------
// VARIÁVEIS GLOBAIS
//---------------------------------------------------------------
Aluno *listaAlunos = NULL;
Curso *listaCursos = NULL;
Matricula *listaMatriculas = NULL;
int geradorMatriculas = 1; // número de matrícula vai aumentando automaticamente

//---------------------------------------------------------------
// FUNÇÃO DE ERRO
//---------------------------------------------------------------
static void reportar_erro(char *mensagem) {
    printf("[ERRO]: %s
", mensagem);
}

//---------------------------------------------------------------
// FERRAMENTAS PARA ALUNOS
//---------------------------------------------------------------
Aluno *buscarAluno(char *nome) {
    // Percorre a lista de alunos procurando pelo nome
    Aluno *aux = listaAlunos;
    while (aux != NULL) {
        if (strcmp(aux->nome, nome) == 0) return aux;
        aux = aux->prox;
    }
    return NULL;
}

void cadastrarAluno() {
    Aluno *novo = (Aluno*)malloc(sizeof(Aluno));

    printf("Nome: "); fflush(stdin); fgets(novo->nome, 50, stdin);
    novo->nome[strcspn(novo->nome, "
")] = 0;

    if (buscarAluno(novo->nome) != NULL) {
        reportar_erro("Aluno já cadastrado.");
        free(novo);
        return;
    }

    printf("Endereço: "); fgets(novo->endereco, 100, stdin);
    novo->endereco[strcspn(novo->endereco, "
")] = 0;

    printf("Telefone: "); fgets(novo->telefone, 15, stdin);
    novo->telefone[strcspn(novo->telefone, "
")] = 0;

    printf("Idade: "); scanf("%d", &novo->idade);

    // Insere no início da lista
    novo->prox = listaAlunos;
    listaAlunos = novo;

    printf("Aluno cadastrado com sucesso!
");
}

void procurarAluno() {
    char nome[50];
    printf("Digite o nome do aluno para procurar: "); fflush(stdin); fgets(nome, 50, stdin);
    nome[strcspn(nome, "
")] = 0;

    Aluno *a = buscarAluno(nome);
    if (a == NULL) {
        reportar_erro("Aluno não encontrado.");
        return;
    }

    printf("Aluno encontrado: %s | Endereço: %s | Telefone: %s | Idade: %d
", a->nome, a->endereco, a->telefone, a->idade);
}

void atualizarAluno() {
    char nome[50];
    printf("Nome do aluno a atualizar: "); fflush(stdin); fgets(nome, 50, stdin);
    nome[strcspn(nome, "
")] = 0;

    Aluno *a = buscarAluno(nome);
    if (!a) {
        reportar_erro("Aluno não encontrado.");
        return;
    }

    printf("Novo endereço: "); fgets(a->endereco, 100, stdin);
    a->endereco[strcspn(a->endereco, "
")] = 0;
    printf("Novo telefone: "); fgets(a->telefone, 15, stdin);
    a->telefone[strcspn(a->telefone, "
")] = 0;
    printf("Nova idade: "); scanf("%d", &a->idade);

    printf("Aluno atualizado!
");
}

void descadastrarAluno() {
    char nome[50];
    printf("Nome do aluno para remover: "); fflush(stdin); fgets(nome, 50, stdin);
    nome[strcspn(nome, "
")] = 0;

    Aluno *atual = listaAlunos;
    Aluno *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (!atual) {
        reportar_erro("Aluno não encontrado.");
        return;
    }

    if (anterior == NULL) listaAlunos = atual->prox;
    else anterior->prox = atual->prox;

    free(atual);
    printf("Aluno removido com sucesso.
");
}

//---------------------------------------------------------------
// FERRAMENTAS PARA CURSOS
//---------------------------------------------------------------
Curso *buscarCurso(char *codigo) {
    Curso *aux = listaCursos;
    while (aux != NULL) {
        if (strcmp(aux->codigo, codigo) == 0) return aux;
        aux = aux->prox;
    }
    return NULL;
}

void cadastrarCurso() {
    Curso *novo = (Curso*)malloc(sizeof(Curso));

    printf("Código do curso: "); fflush(stdin); fgets(novo->codigo, 10, stdin);
    novo->codigo[strcspn(novo->codigo, "
")] = 0;

    if (buscarCurso(novo->codigo) != NULL) {
        reportar_erro("Curso já cadastrado.");
        free(novo);
        return;
    }

    printf("Nome do curso: "); fgets(novo->nome, 50, stdin);
    novo->nome[strcspn(novo->nome, "
")] = 0;

    printf("Instrutor: "); fgets(novo->instrutor, 50, stdin);
    novo->instrutor[strcspn(novo->instrutor, "
")] = 0;

    novo->prox = listaCursos;
    listaCursos = novo;

    printf("Curso cadastrado com sucesso!
");
}

void procurarCurso() {
    char codigo[10];
    printf("Código do curso: "); fflush(stdin); fgets(codigo, 10, stdin);
    codigo[strcspn(codigo, "
")] = 0;

    Curso *c = buscarCurso(codigo);
    if (!c) {
        reportar_erro("Curso não encontrado.");
        return;
    }

    printf("Curso encontrado: %s | Nome: %s | Instrutor: %s
", c->codigo, c->nome, c->instrutor);
}

void atualizarCurso() {
    char codigo[10];
    printf("Código do curso a atualizar: "); fflush(stdin); fgets(codigo, 10, stdin);
    codigo[strcspn(codigo, "
")] = 0;

    Curso *c = buscarCurso(codigo);
    if (!c) {
        reportar_erro("Curso não encontrado.");
        return;
    }

    printf("Novo nome: "); fgets(c->nome, 50, stdin);
    c->nome[strcspn(c->nome, "
")] = 0;

    printf("Novo instrutor: "); fgets(c->instrutor, 50, stdin);
    c->instrutor[strcspn(c->instrutor, "
")] = 0;

    printf("Curso atualizado com sucesso!
");
}

void descadastrarCurso() {
    char codigo[10];
    printf("Código do curso para remover: "); fflush(stdin); fgets(codigo, 10, stdin);
    codigo[strcspn(codigo, "
")] = 0;

    Curso *atual = listaCursos;
    Curso *anterior = NULL;

    while (atual != NULL && strcmp(atual->codigo, codigo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (!atual) {
        reportar_erro("Curso não encontrado.");
        return;
    }

    if (!anterior) listaCursos = atual->prox;
    else anterior->prox = atual->prox;

    free(atual);
    printf("Curso removido com sucesso.
");
}

//---------------------------------------------------------------
// MATRÍCULAS
//---------------------------------------------------------------
Matricula *buscarMatricula(int numero) {
    Matricula *aux = listaMatriculas;
    while (aux != NULL) {
        if (aux->numero == numero) return aux;
        aux = aux->prox;
    }
    return NULL;
}

void matricularAluno() {
    char nome[50], codigo[10];

    printf("Nome do aluno: "); fflush(stdin); fgets(nome, 50, stdin);
    nome[strcspn(nome, "
")] = 0;

    printf("Código do curso: "); fgets(codigo, 10, stdin);
    codigo[strcspn(codigo, "
")] = 0;

    Aluno *a = buscarAluno(nome);
    if (!a) {
        reportar_erro("Aluno não encontrado.");
        return;
    }

    Curso *c = buscarCurso(codigo);
    if (!c) {
        reportar_erro("Curso não encontrado.");
        return;
    }

    Matricula *nova = (Matricula*)malloc(sizeof(Matricula));
    nova->aluno = a;
    nova->curso = c;
    nova->numero = geradorMatriculas++;

    nova->prox = listaMatriculas;
    listaMatriculas = nova;

    printf("Matrícula realizada! Número: %d
", nova->numero);
}

void procurarMatricula() {
    int n;
    printf("Número da matrícula: "); scanf("%d", &n);

    Matricula *m = buscarMatricula(n);
    if (!m) {
        reportar_erro("Matrícula não encontrada.");
        return;
    }

    printf("Matrícula %d | Aluno: %s | Curso: %s
", m->numero, m->aluno->nome, m->curso->nome);
}

void cancelarMatricula() {
    int n;
    printf("Número da matrícula para cancelar: "); scanf("%d", &n);

    Matricula *atual = listaMatriculas;
    Matricula *anterior = NULL;

    while (atual != NULL && atual->numero != n) {
        anterior = atual;
        atual = atual->prox;
    }

    if (!atual) {
        reportar_erro("Matrícula não encontrada.");
        return;
    }

    if (!anterior) listaMatriculas = atual->prox;
    else anterior->prox = atual->prox;

    free(atual);
    printf("Matrícula cancelada com sucesso.
");
}

//---------------------------------------------------------------
// MENU PRINCIPAL
//---------------------------------------------------------------
void menu() {
    printf("
--- MENU ---
");
    printf("1. Cadastrar aluno
");
    printf("2. Procurar aluno
");
    printf("3. Atualizar aluno
");
    printf("4. Descadastrar aluno
");
    printf("5. Cadastrar curso
");
    printf("6. Procurar curso
");
    printf("7. Atualizar curso
");
    printf("8. Descadastrar curso
");
    printf("9. Matricular aluno
");
    printf("10. Procurar matrícula
");
    printf("11. Cancelar matrícula
");
    printf("23. Sair
");
    printf("Escolha: ");
}

int main() {
    int opcao;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarAluno(); break;
            case 2: procurarAluno(); break;
            case 3: atualizarAluno(); break;
            case 4: descadastrarAluno(); break;
