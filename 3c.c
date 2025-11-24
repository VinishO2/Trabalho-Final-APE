#include <stdio.h> // Biblioteca padrão de entrada e saída
#include <stdlib.h> // Biblioteca padrão para alocação de memória
#include <string.h> // Biblioteca para manipulação de strings
#include <locale.h>

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
    printf("[ERRO]: %s", mensagem);
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

//---------------------------------------------------------------
// FUNÇÕES DE CADASTRO, BUSCA, ATUALIZAÇÃO E REMOÇÃO DE ALUNOS
//---------------------------------------------------------------

void cadastrarAluno() {
    Aluno *novo = (Aluno*)malloc(sizeof(Aluno));
    // Coleta os dados do aluno
    printf("Nome: "); fflush(stdin); fgets(novo->nome, 50, stdin);
    novo->nome[strcspn(novo->nome, "")] = 0;

    if (buscarAluno(novo->nome) != NULL) {
        reportar_erro("Aluno já cadastrado.");
        free(novo);
        return;
    }

    printf("Endereço: "); fgets(novo->endereco, 100, stdin);
    novo->endereco[strcspn(novo->endereco, "")] = 0;

    printf("Telefone: "); fgets(novo->telefone, 15, stdin);
    novo->telefone[strcspn(novo->telefone, "")] = 0;

    printf("Idade: "); scanf("%d", &novo->idade);

    // Insere no início da lista
    novo->prox = listaAlunos;
    listaAlunos = novo;

    printf("Aluno cadastrado com sucesso!");
}

void procurarAluno() {
    // Solicita o nome do aluno a ser procurado
    char nome[50];
    printf("Digite o nome do aluno para procurar: "); fflush(stdin); fgets(nome, 50, stdin);
    nome[strcspn(nome, "")] = 0;

    Aluno *a = buscarAluno(nome); // busca o aluno na lista
    if (a == NULL) {
        reportar_erro("Aluno não encontrado.");
        return;
    }

    printf("Aluno encontrado: %s | Endereço: %s | Telefone: %s | Idade: %d", a->nome, a->endereco, a->telefone, a->idade); // mostra os detalhes do aluno
}

void atualizarAluno() {
    char nome[50];
    // Solicita o nome do aluno a ser atualizado
    printf("Nome do aluno a atualizar: "); fflush(stdin); fgets(nome, 50, stdin);
    nome[strcspn(nome, "")] = 0;

    Aluno *a = buscarAluno(nome); // busca o aluno na lista
    if (!a) {
        reportar_erro("Aluno não encontrado.");
        return;
    }

    printf("Novo endereço: "); fgets(a->endereco, 100, stdin); // atualiza o endereço
    a->endereco[strcspn(a->endereco, "")] = 0; // remove o newline
    printf("Novo telefone: "); fgets(a->telefone, 15, stdin); // atualiza o telefone
    a->telefone[strcspn(a->telefone, "")] = 0; // remove o newline
    printf("Nova idade: "); scanf("%d", &a->idade); // atualiza a idade
    printf("Aluno atualizado!");
}

void descadastrarAluno() {
    char nome[50];
    // Solicita o nome do aluno a ser removido
    printf("Nome do aluno para remover: "); fflush(stdin); fgets(nome, 50, stdin);
    nome[strcspn(nome, "")] = 0;

    Aluno *atual = listaAlunos; // ponteiro para percorrer a lista
    Aluno *anterior = NULL; // ponteiro para o aluno anterior

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    } // procura o aluno na lista

    if (!atual) {
        reportar_erro("Aluno não encontrado.");
        return;
    } // remove o aluno da lista

    if (anterior == NULL) listaAlunos = atual->prox; // se for o primeiro da lista
    else anterior->prox = atual->prox; // se for no meio ou fim da lista

    free(atual); // libera a memória
    printf("Aluno removido com sucesso.");
}

//---------------------------------------------------------------
// FERRAMENTAS PARA CURSOS
//---------------------------------------------------------------

Curso *buscarCurso(char *codigo) {
    Curso *aux = listaCursos;
    // Percorre a lista de cursos procurando pelo código
    while (aux != NULL) {
        if (strcmp(aux->codigo, codigo) == 0) return aux;
        aux = aux->prox;
    }
    return NULL;
}

void cadastrarCurso() {
    Curso *novo = (Curso*)malloc(sizeof(Curso));
    // Coleta os dados do curso
    printf("Código do curso: "); fflush(stdin); fgets(novo->codigo, 10, stdin);
    novo->codigo[strcspn(novo->codigo, "")] = 0;

    if (buscarCurso(novo->codigo) != NULL) {
        reportar_erro("Curso já cadastrado.");
        free(novo);
        return;
    } // Verifica se o curso já existe

    printf("Nome do curso: "); fgets(novo->nome, 50, stdin); // Coleta o nome do curso
    novo->nome[strcspn(novo->nome, "")] = 0; // Remove o newline

    printf("Instrutor: "); fgets(novo->instrutor, 50, stdin); // Coleta o nome do instrutor
    novo->instrutor[strcspn(novo->instrutor, "")] = 0; // Remove o newline

    novo->prox = listaCursos; // Insere no início da lista
    listaCursos = novo; // Atualiza a cabeça da lista

    printf("Curso cadastrado com sucesso!");
}

void procurarCurso() {
    // Solicita o código do curso a ser procurado
    char codigo[10];
    printf("Código do curso: "); fflush(stdin); fgets(codigo, 10, stdin); // Coleta o código do curso
    codigo[strcspn(codigo, "")] = 0; // Remove o newline

    Curso *c = buscarCurso(codigo); // Busca o curso na lista
    if (!c) {
        reportar_erro("Curso não encontrado."); // Se não encontrado, reporta erro
        return;
    }

    printf("Curso encontrado: %s | Nome: %s | Instrutor: %s", c->codigo, c->nome, c->instrutor); // Mostra os detalhes do curso
}

void atualizarCurso() {
    // Solicita o código do curso a ser atualizado
    char codigo[10];
    printf("Código do curso a atualizar: "); fflush(stdin); fgets(codigo, 10, stdin); // Coleta o código do curso
    codigo[strcspn(codigo, "")] = 0; // Remove o newline

    Curso *c = buscarCurso(codigo); // Busca o curso na lista
    if (!c) {
        reportar_erro("Curso não encontrado."); // Se não encontrado, reporta erro
        return;
    }

    printf("Novo nome: "); fgets(c->nome, 50, stdin); // Atualiza o nome do curso
    c->nome[strcspn(c->nome, "")] = 0; // Remove o newline

    printf("Novo instrutor: "); fgets(c->instrutor, 50, stdin); // Atualiza o nome do instrutor
    c->instrutor[strcspn(c->instrutor, "")] = 0; // Remove o newline

    printf("Curso atualizado com sucesso!");
}

void descadastrarCurso() {
    // Solicita o código do curso a ser removido
    char codigo[10];
    printf("Código do curso para remover: "); fflush(stdin); fgets(codigo, 10, stdin); // Coleta o código do curso
    codigo[strcspn(codigo, "")] = 0; // Remove o newline

    Curso *atual = listaCursos; // ponteiro para percorrer a lista
    Curso *anterior = NULL; // ponteiro para o curso anterior

    while (atual != NULL && strcmp(atual->codigo, codigo) != 0) {
        anterior = atual;
        atual = atual->prox;
    } // procura o curso na lista

    if (!atual) {
        reportar_erro("Curso não encontrado.");
        return;
    } // remove o curso da lista

    if (!anterior) listaCursos = atual->prox; // se for o primeiro da lista
    else anterior->prox = atual->prox; // se for no meio ou fim da lista

    free(atual); // libera a memória
    printf("Curso removido com sucesso.");
}

//---------------------------------------------------------------
// MATRÍCULAS
//---------------------------------------------------------------

Matricula *buscarMatricula(int numero) {
    // Percorre a lista de matrículas procurando pelo número
    Matricula *aux = listaMatriculas;
    while (aux != NULL) {
        if (aux->numero == numero) return aux;
        aux = aux->prox;
    } // Se encontrar, retorna a matrícula
    return NULL;
}

void matricularAluno() {
    // Coleta os dados para matrícula
    char nome[50], codigo[10];

    printf("Nome do aluno: "); fflush(stdin); fgets(nome, 50, stdin); // Coleta o nome do aluno
    nome[strcspn(nome, "")] = 0; // Remove o newline

    printf("Código do curso: "); fgets(codigo, 10, stdin); // Coleta o código do curso
    codigo[strcspn(codigo, "")] = 0; // Remove o newline

    Aluno *a = buscarAluno(nome);
    if (!a) {
        reportar_erro("Aluno não encontrado.");
        return;
    } // Busca o aluno na lista

    Curso *c = buscarCurso(codigo);
    if (!c) {
        reportar_erro("Curso não encontrado.");
        return;
    } // Busca o curso na lista

    Matricula *nova = (Matricula*)malloc(sizeof(Matricula)); // cria nova matrícula
    nova->aluno = a; // atribui aluno
    nova->curso = c; // atribui aluno e curso
    nova->numero = geradorMatriculas++; // atribui número e incrementa o gerador

    nova->prox = listaMatriculas; // insere no início da lista
    listaMatriculas = nova; // atualiza a cabeça da lista

    printf("Matrícula realizada! Número: %d", nova->numero);
}

void procurarMatricula() {
    int n;
    printf("Número da matrícula: "); scanf("%d", &n);

    Matricula *m = buscarMatricula(n);
    if (!m) {
        reportar_erro("Matrícula não encontrada.");
        return;
    }

    printf("Matrícula %d | Aluno: %s | Curso: %s", m->numero, m->aluno->nome, m->curso->nome); // mostra detalhes da matrícula
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
    printf("Matrícula cancelada com sucesso.");
}

void listarTodasMatriculas() {
    Matricula *aux = listaMatriculas;
    if (!aux) {
        printf("Nenhuma matrícula encontrada.");
        return;
    }
    while (aux != NULL) {
        printf("Matrícula %d | Aluno: %s | Curso: %s\n", aux->numero, aux->aluno->nome, aux->curso->nome);
        aux = aux->prox;
} 
}
void listarTodosCursos() {
    Curso *aux = listaCursos;
    if (!aux) {
        printf("Nenhum curso cadastrado.");
        return;
    }
    while (aux != NULL) {
        printf("Código: %s | Nome: %s | Instrutor: %s\n", aux->codigo, aux->nome, aux->instrutor);
        aux = aux->prox;
    }
}

void listarTodosAlunos() {
    Aluno *aux = listaAlunos;
    if (!aux) {
        printf("Nenhum aluno cadastrado.");
        return;
    }
    while (aux != NULL) {
        printf("Nome: %s | Endereço: %s | Telefone: %s | Idade: %d\n", aux->nome, aux->endereco, aux->telefone, aux->idade);
        aux = aux->prox;
    }
}
void listarAlunosDeUmCurso() {
    char codigo[10];
    printf("Código do curso: "); fflush(stdin); fgets(codigo, 10, stdin);
    codigo[strcspn(codigo, "")] = 0;

    Curso *c = buscarCurso(codigo);
    if (!c) {
        reportar_erro("Curso não encontrado.");
        return;
    }

    Matricula *aux = listaMatriculas;
    int encontrou = 0;
    while (aux != NULL) {
        if (strcmp(aux->curso->codigo, codigo) == 0) {
            printf("Aluno: %s\n", aux->aluno->nome);
            encontrou = 1;
        }
        aux = aux->prox;
    }
    if (!encontrou) {
        printf("Nenhum aluno matriculado neste curso.");
    }
}

void listarAlunosDeTodosCursos() {
    Curso *cursoAux = listaCursos;
    if (!cursoAux) {
        printf("Nenhum curso cadastrado.");
        return;
    }
    while (cursoAux != NULL) {
        printf("Curso: %s\n", cursoAux->nome);
        Matricula *matAux = listaMatriculas;
        int encontrou = 0;
        while (matAux != NULL) {
            if (strcmp(matAux->curso->codigo, cursoAux->codigo) == 0) {
                printf("  Aluno: %s\n", matAux->aluno->nome);
                encontrou = 1;
            }
            matAux = matAux->prox;
        }
        if (!encontrou) {
            printf("  Nenhum aluno matriculado neste curso.\n");
        }
        cursoAux = cursoAux->prox;
    }
}
void listarCursosDeUmAluno() {
    char nome[50];
    printf("Nome do aluno: "); fflush(stdin); fgets(nome, 50, stdin);
    nome[strcspn(nome, "")] = 0;

    Aluno *a = buscarAluno(nome);
    if (!a) {
        reportar_erro("Aluno não encontrado.");
        return;
    }

    Matricula *aux = listaMatriculas;
    int encontrou = 0;
    while (aux != NULL) {
        if (strcmp(aux->aluno->nome, nome) == 0) {
            printf("Curso: %s\n", aux->curso->nome);
            encontrou = 1;
        }
        aux = aux->prox;
    }
    if (!encontrou) {
        printf("Nenhum curso encontrado para este aluno.");
    }
}
void listarCursosDeTodosAlunos() {
    Aluno *alunoAux = listaAlunos;
    if (!alunoAux) {
        printf("Nenhum aluno cadastrado.");
        return;
    }
    while (alunoAux != NULL) {
        printf("Aluno: %s\n", alunoAux->nome);
        Matricula *matAux = listaMatriculas;
        int encontrou = 0;
        while (matAux != NULL) {
            if (strcmp(matAux->aluno->nome, alunoAux->nome) == 0) {
                printf("  Curso: %s\n", matAux->curso->nome);
                encontrou = 1;
            }
            matAux = matAux->prox;
        }
        if (!encontrou) {
            printf("  Nenhum curso encontrado para este aluno.\n");
        }
        alunoAux = alunoAux->prox;
    }
}
void listarMatriculasDeUmAluno() {
    char nome[50];
    printf("Nome do aluno: "); fflush(stdin); fgets(nome, 50, stdin);
    nome[strcspn(nome, "")] = 0;

    Aluno *a = buscarAluno(nome);
    if (!a) {
        reportar_erro("Aluno não encontrado.");
        return;
    }

    Matricula *aux = listaMatriculas;
    int encontrou = 0;
    while (aux != NULL) {
        if (strcmp(aux->aluno->nome, nome) == 0) {
            printf("Matrícula %d | Curso: %s\n", aux->numero, aux->curso->nome);
            encontrou = 1;
        }
        aux = aux->prox;
    }
    if (!encontrou) {
        printf("Nenhuma matrícula encontrada para este aluno.");
    }
}

void listarMatriculasDeUmCurso() {
    char codigo[10];
    printf("Código do curso: "); fflush(stdin); fgets(codigo, 10, stdin);
    codigo[strcspn(codigo, "")] = 0;

    Curso *c = buscarCurso(codigo);
    if (!c) {
        reportar_erro("Curso não encontrado.");
        return;
    }

    Matricula *aux = listaMatriculas;
    int encontrou = 0;
    while (aux != NULL) {
        if (strcmp(aux->curso->codigo, codigo) == 0) {
            printf("Matrícula %d | Aluno: %s\n", aux->numero, aux->aluno->nome);
            encontrou = 1;
        }
        aux = aux->prox;
    }
    if (!encontrou) {
        printf("Nenhuma matrícula encontrada para este curso.");
    }
}

void listarAlunosSemCursos() {
    Aluno *alunoAux = listaAlunos;
    int encontrou = 0;
    while (alunoAux != NULL) {
        Matricula *matAux = listaMatriculas;
        int matriculado = 0;
        while (matAux != NULL) {
            if (strcmp(matAux->aluno->nome, alunoAux->nome) == 0) {
                matriculado = 1;
                break;
            }
            matAux = matAux->prox;
        }
        if (!matriculado) {
            printf("Aluno sem curso: %s\n", alunoAux->nome);
            encontrou = 1;
        }
        alunoAux = alunoAux->prox;
    }
    if (!encontrou) {
        printf("Todos os alunos estão matriculados em cursos.");
    }
}

void listarCursosSemAlunos() {
    Curso *cursoAux = listaCursos;
    int encontrou = 0;
    while (cursoAux != NULL) {
        Matricula *matAux = listaMatriculas;
        int temAlunos = 0;
        while (matAux != NULL) {
            if (strcmp(matAux->curso->codigo, cursoAux->codigo) == 0) {
                temAlunos = 1;
                break;
            }
            matAux = matAux->prox;
        }
        if (!temAlunos) {
            printf("Curso sem alunos: %s\n", cursoAux->nome);
            encontrou = 1;
        }
        cursoAux = cursoAux->prox;
    }
    if (!encontrou) {
        printf("Todos os cursos têm alunos matriculados.");
    }
}

//---------------------------------------------------------------
// SALVAR OS DADOS EM ARQUIVOS
//---------------------------------------------------------------
void salvarDados(){
    FILE *arquivo;

    // Salvar alunos
    arquivo = fopen("alunos.txt", "wb");
    if (arquivo){
        Aluno *atual = listaAlunos;
        while(atual != NULL){
            // Salva cada aluno no arquivo
            fwrite(atual, sizeof(Aluno), 1, arquivo);
            atual = atual->prox;
        }
        fclose(arquivo);
    } else {
        printf("Erro ao salvar alunos. \n");
    }

    //Salvar cursos
    arquivo = fopen("cursos.txt", "wb");
    if (arquivo){
        Curso *atual = listaCursos;
        while(atual != NULL){
            // Salva cada curso no arquivo
            fwrite(atual, sizeof(Curso), 1, arquivo);
            atual = atual->prox;
        }
        fclose(arquivo);
    } else {
        printf("Erro ao salvar cursos. \n");
    }

    //Salvar matrículas
    //Não salvar os ponteiros
    //Salva os identificadores
    arquivo = fopen("matriculas.txt", "wb");
    if(arquivo){
        Matricula *atual = listaMatriculas;
        struct DadosMatricula
        {
            int numero;
            char nomeAluno[50];
            char codigoCurso[10];
        }temp; // Estrutura temporária para salvar os dados sem ponteiros

        while (atual != NULL)
        {
            temp.numero = atual->numero;
            strcpy(temp.nomeAluno, atual->aluno->nome); // Copia o nome do aluno
            strcpy(temp.codigoCurso, atual->curso->codigo); // Copia o código do curso

            fwrite(&temp, sizeof(struct DadosMatricula), 1, arquivo); // Salva a estrutura temporária
            atual = atual->prox;
        }
        fclose(arquivo);
    } else {
        printf("Erro ao salvar matrículas. \n");
    }

    printf("Dados salvos com sucesso!\n");
}

void carregarTudo(){
    FILE *arquivo;

    // Carregar alunos
    arquivo = fopen("alunos.txt", "rb");
    if (arquivo){
        Aluno temp;
        while(fread(&temp, sizeof(Aluno), 1, arquivo)){
            // Cria um novo nó para o aluno
            Aluno *novo = (Aluno*)malloc(sizeof(Aluno));
            // Copia os dados lidos para o novo nó
            *novo = temp;
            // Refaz o encadeamento (insere no início da lista)
            // Aqui inserindo no iniciio para simplificar
            novo->prox = listaAlunos;
            listaAlunos = novo;
        }
        fclose(arquivo);
    }

    // Carregar cursos
    arquivo = fopen("cursos.txt", "rb");
    if (arquivo){
        Curso temp;
        while(fread(&temp, sizeof(Curso), 1, arquivo)){
            // Cria um novo nó para o curso
            Curso *novo = (Curso*)malloc(sizeof(Curso));
            // Copia os dados lidos para o novo nó
            *novo = temp;
            // Refaz o encadeamento (insere no início da lista)
            // Aqui inserindo no iniciio para simplificar
            novo->prox = listaCursos;
            listaCursos = novo;
        }
        fclose(arquivo);
    }

    // Carregar matrículas
    arquivo = fopen("matriculas.txt", "rb");
    if (arquivo){
        struct DadosMatricula
        {
            int numero;
            char nomeAluno[50];
            char codigoCurso[10];
        }temp; // Estrutura temporária para ler os dados sem ponteiros

        int maiorMatricula = 0;

        while (fread(&temp, sizeof(struct DadosMatricula), 1, arquivo)){
            // Cria um novo nó para a matrícula
            Aluno *a = buscarAluno(temp.nomeAluno);
            Curso *c = buscarCurso(temp.codigoCurso);
            if (a && c) {
                Matricula *nova = (Matricula*)malloc(sizeof(Matricula) );
                nova->numero = temp.numero;
                nova->aluno = a;
                nova->curso = c;
                nova->prox = listaMatriculas;
                listaMatriculas = nova;

                // Atualiza o maior número de matrícula
                if (temp.numero >= maiorMatricula)
                {
                    maiorMatricula = temp.numero;
                }
            }
        }
        if(maiorMatricula > 0) geradorMatriculas = maiorMatricula + 1; // Atualiza o gerador de matrículas
        
        fclose(arquivo);
    }
}


//---------------------------------------------------------------
// MENU PRINCIPAL
//---------------------------------------------------------------
void menu() {
    printf("\n\n--- MENU ---\n");
    printf("1. Cadastrar aluno\n");
    printf("2. Procurar aluno\n");
    printf("3. Atualizar aluno\n");
    printf("4. Descadastrar aluno\n");
    printf("5. Cadastrar curso\n");
    printf("6. Procurar curso\n");
    printf("7. Atualizar curso\n");
    printf("8. Descadastrar curso\n");
    printf("9. Matricular aluno\n");
    printf("10. Procurar matrícula\n");
    printf("11. Cancelar matrícula\n");
    printf("12. Listar todas as matrículas feitas\n");
    printf("13. Listar todos os cursos cadastrados\n");
    printf("14. Listar todos os alunos cadastrados\n");
    printf("15. Listar todos os alunos de um curso\n");
    printf("16. Listar todos os alunos de todos os cursos\n");
    printf("17. Listar todos os cursos de um aluno\n");
    printf("18. Listar todos os cursos de todos os alunos\n");
    printf("19. Listar todas as matrículas de um aluno\n");
    printf("20. Listar todas as matrículas de um curso\n");
    printf("21. Listar alunos cadastrados sem cursos\n");
    printf("22. Listar cursos cadastrados sem alunos\n");
    printf("23. Sair\n\n");
    printf("Escolha: ");
}

int main() {
    system ("chcp 65001 > nul");
    setlocale(LC_ALL, "pt_BR.UTF-8");

    carregarTudo();

    int opcao;

do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarAluno(); break;
            case 2: procurarAluno(); break;
            case 3: atualizarAluno(); break;
            case 4: descadastrarAluno(); break;
            case 5: cadastrarCurso(); break;
            case 6: procurarCurso(); break;
            case 7: atualizarCurso(); break;
            case 8: descadastrarCurso(); break;
            case 9: matricularAluno(); break;
            case 10: procurarMatricula(); break;
            case 11: cancelarMatricula(); break;
            case 12: listarTodasMatriculas(); break;
            case 13: listarTodosCursos(); break;
            case 14: listarTodosAlunos(); break;
            case 15: listarAlunosDeUmCurso(); break;
            case 16: listarAlunosDeTodosCursos(); break;
            case 17: listarCursosDeUmAluno(); break;
            case 18: listarCursosDeTodosAlunos(); break;
            case 19: listarMatriculasDeUmAluno(); break;
            case 20: listarMatriculasDeUmCurso(); break;
            case 21: listarAlunosSemCursos(); break;
            case 22: listarCursosSemAlunos(); break;
            case 23: 
                    salvarDados();
                    printf("Saindo...\n"); break;
            default: reportar_erro("Opção inválida."); break;
        }
    } while (opcao != 23);


    return 0;
}