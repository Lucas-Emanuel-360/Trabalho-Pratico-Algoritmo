#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

typedef struct {
char nome[60];
char cpf[12];
char formacao[60];
char contato[15];
}Pesquisador;

typedef struct {
char cpfPesquisador[12];
char dataDeRealizacao[11]; // formato dd-mm-aaaa
int tamAlvo; // tamanho da sequência que está está buscando.
char resultado[100]; // se achou ou não e qual sequência
}Experimento;

typedef struct{
  int base;
  int qtd;
} Resultado;

// FILE *fileAME = fopen("AMESUL.txt", "r"); // Laercio Recomendou
FILE *fileAME;

/*
organiza() -> colocar no vetor(), transformar em decimal(), ordem crescente();
compara vetor(); -> ve quais bases se repetem e salva no vetor de bases repetidas
struct de resultado? base, qtas vezes
id em struct experimento? global pra contar qtd -> gravar o resultado no final -1
*/

// Funções Relacionadas a pesquisador
void cadastrarPesquisador(); //luckckckckckckas
void listarPesquisador(); //wal
void buscarPesquisador(); //fer
void alterarPesquisador(); // wal

//Funções Relacionadas aos experimentos
int verificarCpfExistente(char cpf[]); // luska
int cadastrarExperimento(); //fer
int executarExperimento(); // todos nozes

//Parte Dificil
int * pegaVetor(int posicao, int *tv); //wal linda ;) // agora é fefu >:) peguei
int * converteDecimal(int *vetor, int *tamVet, int tamAlvo); // fefefefefe // agora é wal
void quickSort(int *v, int inicio, int fim); // Lusca // continua Lusca
Resultado * comparaVetor(int *vet1, int tam1, int *vet2, int tam2, Resultado *resultado, int *tamR); //wal
int buscaBinaria(int *vet, int tamVet, int valor);
void converteParaString(Resultado r, int tamAlvo);
void listarExperimentos(); // lucas
void gerarRelatorio();// Lucas


int main()
{
  // fileAME = fopen("AMESUL.txt", "r");
  fileAME = fopen("Teste.txt", "r");
  int op;

  int a, t; //testes

  do{
    printf("Menu Principal\n");
    printf("1. Cadastrar Pesquisador\n");
    printf("2. Listar Pesquisadores\n");
    printf("3. Buscar Pesquisador Pelo nome\n");
    printf("4. Alterar Pesquisador Pelo CPF\n");
    printf("5. Executar Experimento\n");
    printf("6. Listar Experimentos\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &op);
    getchar();  
    switch(op){
      case 1:
      cadastrarPesquisador();
      break;
      case 2:
      listarPesquisador();
      break;
      case 3:
      buscarPesquisador();
      break;
      case 4:
      alterarPesquisador();
      break;
      case 5:
      executarExperimento();
      break;
      case 6:
      gerarRelatorio();
      break;
      case 7:
      system("clear");
      printf("\n-> ");
      scanf("%d", &a);
      pegaVetor(a, &t);
      break;
      default:
      printf("Opcao invalida! Tente novamente.\n");
    }
  }while(op != 8);
}

void cadastrarPesquisador(){
  system("clear");
  FILE *file = fopen("Pesquisadores.bin", "ab");
  if (file == NULL) {
      printf("Erro ao abrir o arquivo de pesquisadores!\n");
      return;
  }
  Pesquisador p;
  int x;

  printf("Nome: ");
  fgets(p.nome, 60, stdin); // Lê o nome do usuário e armazena em 'p.nome'.
  p.nome[strcspn(p.nome, "\n")] = '\0'; // Remove o '\n' no final da string 'p.nome', se presente.

  printf("CPF: ");
  fgets(p.cpf, 12, stdin);
  p.cpf[strcspn(p.cpf, "\n")] = '\0';
  getchar();  // Limpa o '\n' restante no buffer de entrada.

  printf("Formacao: ");
  fgets(p.formacao, 60, stdin);
  p.formacao[strcspn(p.formacao, "\n")] = '\0';

  printf("Contato: ");
  fgets(p.contato, 15, stdin);
  p.contato[strcspn(p.contato, "\n")] = '\0';

  fwrite(&p, sizeof(Pesquisador), 1, file);
  fclose(file);

  printf("Pesquisador cadastrado com sucesso!\n");

  do{
    printf("\nDigite 0 para voltar ao menu.\n");
    scanf("%d", &x);
    if (x == 0){
      fclose(file);
      system("clear");
      return;
    }
  } while (x!= 0);
}

void listarPesquisador(){
  FILE *file = fopen("Pesquisadores.bin", "r+b");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo de pesquisadores!\n");
    return;
  }

  system("clear");

  Pesquisador p;
  int x;

  printf("\nLista de Pesquisadores Cadastrados\n");
  printf("\n%-30s%-12s\n","Nome", "CPF"); //o %-20s significa que a string será impressa com 20 caracteres de largura total, alinhada à esquerda. Espaços serão adicionados à direita para preencher o campo

  while(fread(&p, sizeof(Pesquisador), 1, file) != 0){ 
    printf("%-30s%-12s\n", p.nome, p.cpf);
  } 

  do{
    printf("\nDigite 0 para voltar ao menu.\n");
    scanf("%d", &x);
    if (x == 0){
      fclose(file);
      system("clear");
      return;
    }
  } while (x!= 0);
}

void buscarPesquisador()
{
  FILE *file;
  file = fopen("Pesquisadores.bin", "rb");

  system("clear");

  Pesquisador p;
  int v, achou = 0;
  char nome[60];

  printf("Pesquisar por nome: ");
  scanf(" %[^\n]", nome);



  while(fread(&p, sizeof(Pesquisador), 1, file) != 0)
    {
      if(strcmp(p.nome, nome) == 0)
      {
        achou = 1;
        printf("\nNome: %s", p.nome);
        printf("\nCPF: %s", p.cpf);
        printf("\nFormacao: %s", p.formacao);
        printf("\nContato: %s", p.contato);
        printf("\n");
      }
    }

  if(achou == 0)
    {
      printf("\nNenhum pesquisador com esse nome encontrado :(");
    }

  printf("\n\nDigite 0 para voltar ao menu\n");
  scanf("%d", &v);

  fclose(file);
  system("clear");


}

void alterarPesquisador(){
  FILE *file = fopen("Pesquisadores.bin", "r+b");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo de pesquisadores!\n");
    return;
  }

  system("clear");

  Pesquisador p, newP;
  int existe = 0, count = 0, x = 0;

  printf("\nAlterar Pesquisador\n");
  printf("Digite o CPF do pesquisador: ");
  scanf("%[^\n]s", newP.cpf);

  while(fread(&p, sizeof(Pesquisador), 1, file) != 0){
    if (strcmp (newP.cpf, p.cpf) == 0){
      existe = 1; 
      break;
    } //int strcmp(quero comparar, comparação);
    count++;
  }
  if (existe == 1){
    printf("\nNome: ");
    scanf("\n%[^\n]s", newP.nome);
    printf("Formação: ");
    scanf("\n%[^\n]s", newP.formacao);
    printf("Contato: ");
    scanf("\n%[^\n]s", newP.contato);

    //posiciona no registro int fseek(FILE *fp, long numbytes, int origem)
    // SEEK_SET (a partir do inicio do arquivo), SEEK_CUR (a partir da posição atual), SEEK_END (fim do arquivo)

    fseek(file, (count)*sizeof(Pesquisador), SEEK_SET);
    fwrite(&newP, sizeof(Pesquisador), 1, file); //size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    fclose(file);

    printf("\nPesquisador alterado.\n");
  }
  else printf("\nCPF não encontrado!");

  do{
    printf("\n\nDigite 0 para voltar ao menu.\n");
    scanf("%d", &x);
    if (x == 0){
      fclose(file);
      system("clear");
      return;
    }
  } while (x!= 0);

}

int verificarCpfExistente(char cpf[]) {
    FILE *file = fopen("Pesquisadores.bin", "rb");
    if (file == NULL) {
        return 0;
    }

    Pesquisador p;
    while (fread(&p, sizeof(Pesquisador), 1, file)) {
        if (strcmp(p.cpf, cpf) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int cadastrarExperimento()
{
  FILE *file = fopen("Experimentos.bin", "ab");
  if (file == NULL) {
      printf("Erro ao abrir o arquivo de Experimentps!\n");
      return 0;
  }

  Experimento exp;
  char cpfP[12];
  char res[100] = "naofeito";

  printf("CPF do pesquisador desse experimento: ");
  scanf("%s", cpfP);

  if(verificarCpfExistente(cpfP))
  {
    int form = 0;


    strcpy(exp.cpfPesquisador, cpfP);

    do
      {
        printf("\nData de realização(dd-mm-aaaa): ");
        scanf(" %[^\n]", exp.dataDeRealizacao);

        // 02-03-2024
        form = 1;
        if(exp.dataDeRealizacao[2] != '-' || exp.dataDeRealizacao[5] != '-')
        {
          form = 0;
          printf("\nFormato de data errado! Insira a data novamente.\n");
          sleep(02);
          system("clear");
          printf("Cadastro de experimento\n");
          printf("CPF do pesquisador desse experimento: %s", cpfP);
        }

      }
      while(form == 0);


    printf("Tamanho da sequência alvo: ");
    scanf("%d", &exp.tamAlvo);
    strcpy(exp.resultado, res);



    fwrite(&exp, sizeof(Experimento), 1, file);


    printf("Experimento cadastrado com sucesso!\n");

  }
  else
  {
    printf("\nNenhum pesquisador com esse CPF encontrado!\n");
    system("sleep 03");
    system("clear");  
    return 0;
  }

  fclose(file);
  return 1;
}

int executarExperimento(){
  system("clear");

  int cadastro;
  Experimento e;
  Resultado *resultado = NULL;
  int *vet = NULL, *vet2 = NULL,  tam1, tam2;
  int *vetQlqr = NULL, tamQlqr, tamR = 0; //colocar loop até EOF e ir incrementando
  int posicaoBloco = 3;
  char linha;
  
  printf("\nCadastro de experimento\n\n");

  cadastro = cadastrarExperimento();

  if (cadastro == 1){
    FILE *fileExp = fopen("Experimentos.bin", "r");

    if (fileExp == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return -1; // ou outro valor de erro
    }

    fseek(fileExp, -(sizeof(Experimento)), SEEK_END);
    fread(&e, sizeof(Experimento), 1, fileExp);

    vet = pegaVetor(1, &tam1);
    vet = converteDecimal(vet, &tam1, e.tamAlvo);
    quickSort(vet, 0, tam1-1);
    printf("\nVetor quick sortado\n-> ");
    for(int i = 0; i < tam1; i++)
      {
        printf("%d ", vet[i]);
      }


    vet2 = pegaVetor(2, &tam2);
    vet2 = converteDecimal(vet2, &tam2, e.tamAlvo);
    quickSort(vet2, 0, tam2-1);

    resultado = comparaVetor(vet, tam1, vet2, tam2, resultado, &tamR);
    printf("\nTamR = %d\n", tamR);
    
    for (int i = 0; i < tamR; i++){
      printf("\nBase: %d, Qtd: %d\n", resultado[i].base, resultado[i].qtd);
    }
    
    int bloco = 0;
    posicaoBloco = 1;
    while(fscanf(fileAME, " %[^\n]", &linha) != EOF){
      printf("\n\nestou no while, posicaobloco = %d\n\n", posicaoBloco);
      printf("\n\n");
      if(linha != '>' && bloco == 0){
        vetQlqr = pegaVetor(posicaoBloco, &tamQlqr);
        vetQlqr = converteDecimal(vetQlqr, &tamQlqr, e.tamAlvo);
        quickSort(vetQlqr, 0, tamQlqr-1);

        for (int i = 0; i < tamR; i++) {
          // Para cada elemento do vetor1, faz busca binária no vetor2
          if (buscaBinaria(vetQlqr, tamQlqr, resultado[i].base) != -1) {
            resultado[i].qtd += 1;
          }
        }
        bloco = 1;
        printf("\n\nepassei do for, posicaobloco = %d\n\n", posicaoBloco);
        posicaoBloco++;
      }
      
      if(linha == '>' && bloco == 1)
      {
        bloco = 0;
      }
    }
    //testando
    for (int i = 0; i < tamR; i++){
      printf("\n\nBase: %d, Qtd: %d\n\n", resultado[i].base, resultado[i].qtd);
    }
    // e.resultado = "Achou " + resultado->base;
  }
  else {
    printf("\nNão foi possível realizar o experimento.\n");
    system("sleep 03");
    system("clear");
    return 0;
  }

  return 0;
}



int * pegaVetor(int posicao, int *tv)
{
  char linha[200]; //linha sendo observada
  int atual = 0; //para saber em qual bloco de sequência o código está
  int divisoria = 0; //para diferenciar se a linha faz parte da sequencia ou se é a divisao entre blocos
  int add; //para adicionar bytes necessarios para saltar uma linha
  long int bytes, bytes2; //quantidade de bytes que o ponteiro tem que "pular" para chegar no bloco escolhido
  int acabou = 0; //para controlar o while que passa pelo bloco escolhido e salva em vetor de int
  int cont = 0;
  int tam = 0;

  // char blocoEscolhido[300];
  char * blocoChar; //vetor com o bloco escolhido em char
  blocoChar = (char *)calloc(1, sizeof(char));



  bytes = 0; // coloca os bytes em 0 para o ponteiro ficar no começo
  while(atual < posicao)
    {
      if (fseek(fileAME, bytes, SEEK_SET) != 0) { //verifica se o local para onde o ponteiro está indo não passa do limite do arquivo, e alerta o erro
        printf("\nErro ao mover ponteiro. Alvo não existe no arquivo!");
      }
      else
      {
        fseek(fileAME, bytes, SEEK_SET); //posiciona o ponteiro no começo da proxima linha nao contada
        fscanf(fileAME, " %[^\n]", linha);  //lê a linha inteira


        if(linha[0] != '>') //verifica se a linha faz parte de um bloco de virus
        {
          if(divisoria == 0) //verifica se a linha anterior foi uma divisoria
          {
            divisoria = 1; //avisa q essa linha não é divisoria
            atual++; //adiciona 1 ao contador de em qual bloco estamos
            add = 61; //faz o add ser 61, já que cada linha de virus tem 61 bytes (eu contei)
          }
        }

        else if(linha[0] == '>') //se a linha tual não for linha de virus, verifica se é linha divisoria
        {
          if(divisoria == 1) //verifica se a linha anterior foi linha de virus
          {
            fseek(fileAME, bytes, SEEK_SET); //reposiciona o ponteiro no começo da linha divisoria

            add = 0; //faz o add ser 0 para poder contar quantos bytes vai ser preciso saltar para chegar no começo da próxima linha

            while(fgetc(fileAME) != '\n') //esse bloco de while vai passar por cada caractere da linha de divisão e contar quantos são
              {
                add++;
              }
            add++; //é preciso adicionar mais 1 byte para que o ponteiro vá para o começo da próxima linha, e não para o final dessa ;) 

            divisoria = 0; //avisa que essa linha é divisória
          }
        }

        if(atual != posicao) //verifica se o código ainda não chegou no bloco solicitado para atualizar a quantidade de bytes para chegar na próxima linha. Se a linha atual for a primeira do bloco solicitado, esse if não roda, para que o ponteira permaneça no começo da primeira linha necessária
        {
          bytes += add; //atualiza a quantidade de bytes para chegar na próxima linha
        }
      }
    }

  fseek(fileAME, bytes, SEEK_SET);//garante que o ponteiro vá estar no começo da primeira linha do bloco solicitado (é meio que redundancia, dá pra tirar se quiser o.O)

  while(acabou != 1)
    {
      fscanf(fileAME, "%s\n", linha);//  lê a linha

      if(linha[0] != '>') //verifica se não é linha de divisao
      {
        tam += 60; //aumenta o tamanho contado do vetor
        blocoChar = (char *)realloc(blocoChar, tam*sizeof(char)); //realoca o vetor de char para caber os valores da nova linha

        for(int i = 0; i < 60; i++) //passa por cada char da linha e coloca numa posição do blocoChar
          {
            blocoChar[cont] = linha[i];
            cont += 1; //aumenta a "posição de edição" do blocoChar
          }
      }

      else if(linha[0] == '>') //se a linha for de divisao, encerra o loop
      {
        acabou = 1;
      }
    }

  int * blocoEscolhido; //vetor para armazenar, em ints, o bloco escolhido
  blocoEscolhido = (int *)calloc(tam, sizeof(int)); //aloca o tamanho para o vetor

  for(int i = 0; i < tam; i++)
    {
      blocoEscolhido[i] = blocoChar[i] - '0'; //converte cada char do blocoChar para int e coloca em cada posição do blocoEscolhido
    }


  //imprimindo o vetor para verificar se esta correto
  printf("\nVetor buscado\n-> ");
  for(int i = 0; i < tam; i++)
    {
      printf("%d ", blocoEscolhido[i]);
    }
  
  *tv = tam; //passa o tamanho do vetor pra varivel fora da função passada por referencia
  return blocoEscolhido; //retorna o vetor pronto
}



// tem q pegar de x em x bloquinhos e colocar em base 10
int * converteDecimal(int *vetor, int *tamVet, int tamAlvo)
{
  int * convertendo = NULL, count = 0, valor;

  convertendo = (int *)calloc(*tamVet, sizeof(int));

  for(int i = 0, j = 0; i < *tamVet; i++){
    valor = 0;

    for (int j = 0, k = tamAlvo - 1; j < tamAlvo; j++, k--){
      valor += vetor[i + j] * pow(4, k);
    }

    // a = vetor[i] * pow(4, 3);
    // b = vetor[i + 1] * pow(4, 2);
    // c = vetor[i + 2] * pow(4, 1);
    // d = vetor[i + 3] * pow(4, 0);
    /*
    Ex.: 2 2 3 ->
    2 * 4^2 k -> representa a potência (se alvo = 3, 0 <= k <= alvo -1)
    2 * 4^1 j -> representa posição dos valores no vetor (se alvo = 3, pegamos posição 0
    3 * 4^0      + os próximos 2 valores, entao j, j+1 e j+2)
    */

    convertendo[i] = valor;
    count++;
  }
   *tamVet = count;

  printf("\nVetor convert\n-> ");
  for(int i = 0; i < count; i++)
    {
      printf("%d ", convertendo[i]);
    }

  return convertendo;
}

void quickSort(int *v, int inicio, int fim) {
  // quickSort(vetorConvertido, 0, tamConvertendo - 1); <- chamada de exemplo para a função
  
  // Verifica se a posição inicial é menor que a posição final
  // Caso contrário, a partição já está ordenada
  if (inicio < fim) {
    // Definindo os índices iniciais e finais da partição
    int i = inicio, j = fim;

    // Definindo o pivô como o elemento central da partição atual
    int pivo = v[(inicio + fim) / 2];

    // Variável temporária usada para troca de valores
    int temp;

    // Particionamento: reorganizando os elementos em torno do pivô
    while (i <= j) {
      // Move o índice 'i' para a direita até encontrar um valor maior ou igual ao pivô
      while (v[i] < pivo) {
        i++;
      }

      // Move o índice 'j' para a esquerda até encontrar um valor menor ou igual ao pivô
      while (v[j] > pivo) {
        j--;
      }

      // Se 'i' ainda for menor ou igual a 'j', realiza a troca dos elementos
      if (i <= j) {
        // Troca os elementos nas posições 'i' e 'j'
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;

        // Avança os índices 'i' e 'j'
        i++;
        j--;
      }
    }

    if (inicio < j) {
      quickSort(v, inicio, j);
    }

    // Recursivamente, aplica o QuickSort na partição direita
    if (i < fim) {
      quickSort(v, i, fim);
    }
  }
}

Resultado * comparaVetor(int *vet1, int tam1, int *vet2, int tam2, Resultado *resultado, int *tamR){
  // ela ta ali falando e eu aqui em enteder nada
  int size = 200, achou = 0;
  Resultado *result = (Resultado *)malloc(size * sizeof(Resultado)), r;

  for (int i = 0; i < tam1; i++) {
    // Para cada elemento do vetor1, faz busca binária no vetor2
    if (buscaBinaria(vet2, tam2, vet1[i]) != -1) {
      achou = 0;
      r.base = vet1[i];
      r.qtd = 1;

      for (int j = 0; j < *tamR; j++){
        if (r.base == result[j].base){
          result[j].qtd += 1;
          achou = 1;
          printf("R = %d, %d\n", result[j].base, result[j].qtd); //tirar qtd aqui, deixar só no while
          break;
        }
      }
      if(achou == 0){
        if (*tamR >= size) {
          size *= 2;
          result = (Resultado *)realloc(result, size * sizeof(Resultado));
        }
        result[*tamR] = r;
        printf("R = %d, %d\n", result[*tamR].base, result[*tamR].qtd);
        *tamR += 1;
      }
    }
  }
  
   result = (Resultado *)realloc(result, (*tamR) * sizeof(Resultado)); // Final reallocation
  
  return result;
}


int buscaBinaria(int *vet, int tamVet, int valor){
  
  int inicio = 0;
  int fim = tamVet - 1;

  while (inicio <= fim) {
    int meio = inicio + (fim - inicio) / 2;

    if (vet[meio] == valor) {
      printf("\nBusca binária, achou -> %d", meio);
      return meio;  // Retorna a posição do valor encontrado
    }

    if (vet[meio] < valor) {
      inicio = meio + 1;
    } else {
      fim = meio - 1;
    }
    
  }
  
  return -1;  // Valor não encontrado
}

// void converteParaString(Resultado r, int tamAlvo){
//   char s[tamAlvo + 1], base; 
//   //9
//   int resto = 0, i = tamAlvo - 1; //0 1 2 3
//   int numRestante = r.base;
//   float num;
    
//   while (num/4 != 0){
//     resto = numRestante % 4; //1
//     numRestante = numRestante/4; //2
      
//     switch(resto){
//       case 0:
//         s[i] = 'A';
//       case 1:
//         s[i] = 'T';
//       case 2:
//         s[i] = 'C';
//       case 3:
//         s[i] = 'G';
//     }
//     i--;
//   }
  
//   while()
// }

void listarExperimentos() {
  FILE *file = fopen("Experimentos.bin", "rb");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo de experimentos!\n");
    return;
  }

  system("clear");

  Experimento e;
  int x;

   printf("\nTodos os experimentos:\n");
  printf("\n%-20s%-12s%-15s%-12s", "CPF - Pesquisador", "Data", "Tamanho - Alvo", "Resultado");
  while (fread(&e, sizeof(Experimento), 1, file)) {
    printf(
        "\n%-20s%-12s%-15d%-12s",
        e.cpfPesquisador, e.dataDeRealizacao, e.tamAlvo, e.resultado);
  }
  printf("\n\n");

  fclose(file);

  do{
    printf("\nDigite 0 para voltar ao menu.\n");
    scanf("%d", &x);
    if (x == 0){
      system("clear");
      return;
    }
  } while (x!= 0);

}

void listarExperimentosPorPesquisador(char *cpfPesquisador) {
  FILE *file = fopen("Experimentos.bin", "rb");
  if (file == NULL) {
      printf("Erro ao abrir o arquivo de experimentos.\n");
      return;
  }

  Experimento exp;
  int encontrou = 0;
  while (fread(&exp, sizeof(Experimento), 1, file)) {
      if (strcmp(exp.cpfPesquisador, cpfPesquisador) == 0) {
          printf("Data: %s, Tamanho Alvo: %d, Resultado: %s\n", exp.dataDeRealizacao, exp.tamAlvo, exp.resultado);
          encontrou = 1;
      }
    sleep(02);
  }

  if (!encontrou) {
      printf("Nenhum experimento encontrado para o CPF %s.\n", cpfPesquisador);
  }
  sleep(02);

  fclose(file);
}

void listarExperimentosPorAno(char *ano) {
  FILE *file = fopen("Experimentos.bin", "rb");
  if (file == NULL) {
      printf("Erro ao abrir o arquivo de experimentos.\n");
      return;
  }

  Experimento exp;
  int encontrou = 0;
  while (fread(&exp, sizeof(Experimento), 1, file)) {
      if (strncmp(&exp.dataDeRealizacao[6], ano, 4) == 0) {
          printf("CPF Pesquisador: %s, Data: %s, Tamanho Alvo: %d, Resultado: %s\n", exp.cpfPesquisador, exp.dataDeRealizacao, exp.tamAlvo, exp.resultado);
          encontrou = 1;
      }
    sleep(02);
  }

  if (!encontrou) {
      printf("Nenhum experimento encontrado para o ano %s.\n", ano);
  }

  fclose(file);
}

void gerarRelatorio() {
  int opcao;
  char input[12];

  printf("Escolha o tipo de relatório:\n");
  printf("1) Todos os experimentos de um pesquisador\n");
  printf("2) Todos os experimentos realizados em um determinado ano\n");
  printf("Opção: ");
  scanf("%d", &opcao);

  switch (opcao) {
      case 1:
          printf("Digite o CPF do pesquisador: ");
          scanf("%s", input);
          getchar();
          listarExperimentosPorPesquisador(input);
          sleep(02);
          break;
      case 2:
          printf("Digite o ano (aaaa): ");
          scanf("%s", input);
          listarExperimentosPorAno(input);
          break;
      default:
          printf("Opção inválida.\n");
  }
}