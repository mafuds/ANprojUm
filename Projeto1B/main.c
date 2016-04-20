#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Programa que calcula uma integral por 1/3 de Simpson. Aceita até 10 valores tabelados como entrada
int main()
{
  float x[10],y[10],soma=0,h,temp;
  int i,dados,j,k=0;
  //float fact(int);

  // Coisas necessárias para medir tempo de execução ******
     clock_t tempo;
     tempo = clock();

  // Pega os valores da tabela pra calcular a integral
      printf("\nQuantos dados serao inseridos? ");
      scanf("%d",&dados);

          for(i = 0; i < dados; i++)
          {
           printf("\nDigite o valor de x%d: ",i);
           scanf("%f",&x[i]);
           printf("\nDigite o valor de f(x%d): ",i);
           scanf("%f",&y[i]);
          }
  //

      h = x[1]-x[0]; // h = b - a (limites de integração)
      dados = dados-1; // corrige o fato de que o PC computa a partir do 0 e o usuário acaba digitando 1 a mais (pensa a partir de 1)
      soma = soma + y[0]; // ja seta o valor da soma da fórmula com f(x0)

          for(i = 1;i < dados;i++)
          {
                // caso ta nos elementos que são multiplicados por 4 na fórmula
                if(k == 0)
                {
                 soma = soma + 4 * y[i];
                 k = 1;
                }

                // caso os de 2
                else
                {
                 soma = soma + 2 * y[i];
                 k = 0;
                }
          }

       soma = soma + y[i]; // soma o f(xn)
       soma = soma * (h/3); // termina a conta multiplicando pelo h/3

    printf("\nResultado da integral:  I = %f  ",soma);

    tempo = clock() - tempo;
    double tempoLevado = ((double) tempo) / CLOCKS_PER_SEC; // pega o tempo em segundos

    printf("\nO calculo levou %f segundos para ser executado \n",tempoLevado);

    return 0;
}
