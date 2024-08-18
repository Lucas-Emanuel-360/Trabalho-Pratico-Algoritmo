// int * pegaVetor(int posicao)
// {

//   char linha[200]; //linha sendo observada
//   int atual = 0; //para saber em qual bloco de sequência o código está
//   int divisoria = 1; //para diferenciar se a linha faz parte da sequencia ou se é a divisao entre blocos
//   int add; //para adicionar bytes necessarios para saltar uma linha
//   long int bytes; //quantidade de bytes que o ponteiro tem que "pular" para chegar no bloco escolhido
//   int acabou = 0; //para controlar o while que passa pelo bloco escolhido e salva em vetor de int
//   int qnt = 0; //quantidade de numeros singulares no vetor

//   int *blocoEscolhido; //vetor com o bloco escolhido




//   bytes = 0; // coloca os bytes em 0 para o ponteiro ficar no começo
//   while(atual < posicao)
//     {
//       if (fseek(fileTeste, 10, SEEK_SET) != 0) { //verifica se o local para onde o ponteiro está indo não passa do limite do arquivo, e alerta o erro
//         printf("\nErro ao mover ponteiro. Alvo não existe no arquivo!");
//         return 0;
//       }
//       else
//       {
//         fseek(fileTeste, bytes, SEEK_SET); //posiciona o ponteiro no começo da proxima linha nao contada
//         fscanf(fileTeste, " %[^\n]", linha); //lê a linha inteira


//         if(linha[0] != '>') //verifica se a linha faz parte de um bloco de virus
//         {
//           if(divisoria == 0) //verifica se a linha anterior foi uma divisoria
//           {
//             divisoria = 1; //avisa q essa linha não é divisoria
//             atual++; //adiciona 1 ao contador de em qual bloco estamos
//             add = 61; //faz o add ser 61, já que cada linha de virus tem 61 bytes (eu contei)
//           }
//         }

//         else if(linha[0] == '>') //se a linha tual não for linha de virus, verifica se é linha divisoria
//         {
//           if(divisoria == 1) //verifica se a linha anterior foi linha de virus
//           {
//             fseek(fileTeste, bytes, SEEK_SET); //reposiciona o ponteiro no começo da linha divisoria

//             add = 0; //faz o add ser 0 para poder contar quantos bytes vai ser preciso saltar para chegar no começo da próxima linha
//             while(fgetc(fileTeste) != '\n') //esse bloco de while vai passar por cada caractere da linha de divisão e contar quantos são 
//               {
//                 add++;
//               }
//             add++; //é preciso adicionar mais 1 byte para que o ponteiro vá para o começo da próxima linha, e não para o final dessa ;) 

//             divisoria = 0; //avisa que essa linha é divisória
//           }
//         }

//         if(atual != posicao) //verifica se o código ainda não chegou no bloco solicitado para atualizar a quantidade de bytes para chegar na próxima linha. Se a linha atual for a primeira do bloco solicitado, esse if não roda, para que o ponteira permaneça no começo da primeira linha necessária
//         {
//           bytes += add; //atualiza a quantidade de bytes para chegar na próxima linha
//         }
//       }
//     }

//   fseek(fileTeste, bytes, SEEK_SET); //garante que o ponteiro vá estar no começo da primeira linha do bloco solicitado (é meio que redundancia, dá pra tirar se quiser o.O)

//   fscanf(fileTeste, "%s\n", linha);
//   printf("\nAqui->\n%s", linha);

//   while(acabou != 1)
//     {
//       fscanf(fileTeste, "%s\n", linha);

//       if(linha[0] != '>')
//       {
//         for(int i = 0; i < 60; i++)
//           {
//             blocoEscolhido[qnt] = linha[i];
//             qnt++;
//           }
//       }

//       else if(linha[0] == '>')
//       {
//         acabou = 1;
//       }

//     }

//   printf("\n\n");

//   for(int i = 0; i < qnt; i++)
//     {
//       for(int j = 0; j < 60; j++)
//         {
//           printf("%d ", blocoEscolhido[i]);
//         }
//       printf("\n");
//     }






//   return 0;
// }