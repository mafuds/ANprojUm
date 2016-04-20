#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// pi = M_PI ; pi/2 = M_PI_2 ; pi/4 = M_PI_4 Constantes do Pi para se saber
// Programa que calcula uma integral por 1/3 de Simpson. Aceita até 10 valores tabelados como entrada
int main()
{
  float x[10],y[10],soma=0,h,valorAnterior,integralFinal;
  int i,dados,k=1,identificaFx=0;

  // Coisas necessárias para medir tempo de execução ******
     clock_t tempo;
     tempo = clock();

  // Pega os valores da tabela pra calcular a integral
      printf("\nQuantos dados serao inseridos? ");
      scanf("%d",&dados);

          for(i = 0; i < dados; i++)
          {
           printf("\nDigite o valor de fi%d: ",i);
           scanf("%f",&x[i]);
           printf("\nDigite o valor de f(fi%d): ",i);
           scanf("%f",&y[i]);
          }
  //

      /* Aqui é o local no código original  h = x[1]-x[0]; // h = b - a (limites de integração)
      dados = dados - 1; // corrige o fato de que o PC computa a partir do 0 e o usuário acaba digitando 1 a mais (pensa a partir de 1)
      soma = soma + y[0]; // ja seta o valor da soma da fórmula com f(x0)*/

      do
      {
          h = (2 * M_PI) / ((pow(2,k)) * 3);
          dados = dados - 1; // corrige o fato de que o PC computa a partir do 0 e o usuário acaba digitando 1 a mais (pensa a partir de 1)
          soma = soma + y[0]; // ja seta o valor da soma da fórmula com f(x0)

          for(i = 1;i < dados;i++)
              {
                    // caso ta nos elementos que são multiplicados por 4 na fórmula
                    if(identificaFx == 0)
                    {
                     soma = soma + 4 * y[i];
                     identificaFx = 1;
                    }

                    // caso os de 2
                    else
                    {
                     soma = soma + 2 * y[i];
                     identificaFx = 0;
                    }
              }

           soma = soma + y[i]; // soma o f(xn)
           soma = soma * (h/3); // termina a conta multiplicando pelo h/3

        integralFinal = (1 / (2 * M_PI)) * soma;
        printf("\nResultado da integral: %f  ",integralFinal);

            if (k > 1)
            {
                printf("\nDiferenca I%d - I%d : %f",k,k-1,integralFinal - valorAnterior);
            }

        valorAnterior = integralFinal;
        soma = 0;
        k++;

      }while(k <= 10);

    tempo = clock() - tempo;
    double tempoLevado = ((double) tempo) / CLOCKS_PER_SEC; // pega o tempo em segundos

    printf("\n\nO calculo levou %f segundos para ser executado \n",tempoLevado);

    return 0;
}
