#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define DOISPI (2 * M_PI)
#define CONST 1 / DOISPI
#define MENOSPI -M_PI
/// ( 1 / sqrt(2.01 - 2 * cos x) - cos x)
/// com h variavel de = 2 * pi / 2^k * 3

int main()
{
    int i, j, numParticoes, contPos, contNeg, opcao, loop;
    double *a, primDerivadax0, primDerivadaxn, *vetB, *vetDeX, passoH, *vetL, *vetMi, *vetZ, *b, *c, *d;

    printf("\t\t\tEX 01 - PROJETO 1\n\n\t\t\t  SPLINE FIXADO\n\n");
    printf("1. Derivadas em +-pi\n2. Aproximacoes das derivadas com formula de 3 pontos em +-pi\n\n\t");
    printf("Opcao: ");
    scanf("%d", &opcao);
    printf("\n\nQuantas iteracoes (1 | 2 | 3 | 4 | 5): ");
    scanf("%d", &loop);

    for (i = 1; i <= loop; i++)
    {
        numParticoes = pow(2, i) * 3;
        passoH = DOISPI / numParticoes;

        a = (double *) malloc ((numParticoes + 1) * sizeof(double));
        vetDeX = (double *) malloc ((numParticoes + 1) * sizeof(double));
        vetDeX[0] = MENOSPI;

        /// Obtendo os y's e x's da função
        for (j = 0; j <= numParticoes; j++)
        {
            a[j] = 1 / sqrt(2.01 - (2 * cos(vetDeX[j]))) - cos(vetDeX[j]);
            if (j != numParticoes)
                vetDeX[j+1] = vetDeX[j] + passoH;
            if (j > 0) {
            	if (vetDeX[j] >= acos(1.01/2) && vetDeX[j-1] <= acos(1.01/2))
        			contPos = j - 1;
        		if (vetDeX[j] >= -acos(1.01/2) && vetDeX[j-1] <= -acos(1.01/2))
        			contNeg = j - 1;
            }
        }

        // melhor essa formula por causa das extremidades, pois as info sobre f fora do intervalo não estão dispo
        // o erro é maior do que da outra equação mas tem esse lance aí de cima
        if (opcao == 1) {
            primDerivadax0 = 0;
            primDerivadaxn = 0;
        }
        else {
            primDerivadax0 = 1 / (2 * passoH) * (-3 * a[0] + 4 * a[1] - a[2]);
            primDerivadaxn = 1 / (2 * passoH) * (a[numParticoes - 2] - 4 * a[numParticoes - 1] + 3 * a[numParticoes]);
        }

        /// Criação do vetor b (Ac = b)
        vetB = (double *) malloc ((numParticoes + 1) * sizeof(double));
        vetB[0] = 3 * (a[1] - a[0]) / passoH - 3 * primDerivadax0;
        vetB[numParticoes] = 3 * primDerivadaxn - 3 * (a[numParticoes] - a[numParticoes - 1]) / passoH;

        for (j = 1; j <= numParticoes - 1; j++)
            vetB[j] = (3 / passoH) * (a[j+1] - a[j]) - (3 / passoH) * (a[j] - a[j-1]);

        /// Solução para o sistema linear
        vetL = (double *) malloc ((numParticoes + 1) * sizeof(double));
        vetMi = (double *) malloc ((numParticoes) * sizeof(double));
        vetZ = (double *) malloc ((numParticoes + 1) * sizeof(double));

        vetL[0] = 2 * passoH;
        vetMi[0] = 0.5;
        vetZ[0] = vetB[0] / vetL[0];

        for (j = 1; j <= numParticoes - 1; j++)
        {
            vetL[j] = 2 * (vetDeX[j+1] - vetDeX[j-1]) - passoH * vetMi[j-1];
            vetMi[j] = passoH / vetL[j];
            vetZ[j] = (vetB[j] - passoH * vetZ[j-1]) / vetL[j];
        }

        vetL[numParticoes] = passoH * (2 - vetMi[numParticoes-1]);
        vetZ[numParticoes] = (vetB[numParticoes] - passoH * vetZ[numParticoes-1]) / vetL[numParticoes];
        c = (double *) malloc ((numParticoes + 1) * sizeof(double));
        c[numParticoes] = vetZ[numParticoes];
        b = (double *) malloc ((numParticoes + 1) * sizeof(double));
        d = (double *) malloc ((numParticoes + 1) * sizeof(double));

        for (j = numParticoes - 1; j >= 0; j--)
        {
        	c[j] = vetZ[j] - vetMi[j] * c[j+1];
        	b[j] = 	(a[j+1] - a[j]) / passoH - passoH * (c[j+1] + 2 * c[j]) / 3;
        	d[j] = (c[j+1] - c[j]) / (3 * passoH);
        }

        printf("\n\nK = %d | Num de Pontos: %d\n", i, numParticoes + 1);
        for (j = 0; j < numParticoes; j++)
            printf("\nS%d(x): %.3f + %.3f(x - %.3f) + %.3f(x - %.3f)² + %.3ff(x - %.3f)³", j, a[j], b[j], vetDeX[j], c[j], vetDeX[j], d[j], vetDeX[j]);

        printf("\n\nYmin da funcao em +-arccos(1.01/2) -> +-1.04141... = 0.495");
       	double r = a[contPos] + b[contPos] * (acos(1.01/2) - vetDeX[contPos]) + c[contPos] * pow((acos(1.01/2) - vetDeX[contPos]), 2) + d[contPos] * pow((acos(1.01/2) - vetDeX[contPos]), 3);
		printf("\n\nS%d(1.04141): %.5f", contPos, r);
		r = a[contNeg] + b[contNeg] * (-acos(1.01/2) - vetDeX[contNeg]) + c[contNeg] * pow((-acos(1.01/2) - vetDeX[contNeg]), 2) + d[contNeg] * pow((-acos(1.01/2) - vetDeX[contNeg]), 3);
		printf("\nS%d(-1.04141): %.5f", contNeg, r);	

    }

    return 0;
}
