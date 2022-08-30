#include "biblioteca.h"
#include "quebrador-senha.h"
#include <stdio.h>

/* Gera senhas força bruta*/
int gera_senha_forcabruta(char senhaPronto[], char CaracteresRestantes[], int senhaIndex)
{
    int i;

    /* Caso base, quando o tamanho da senha estiver 6, ou seja, completo, da entrada no login */
    if (senhaIndex == 6)
    {
        if (login(senhaPronto))
            return 1;
    }

    else
    {
        /* Percorre arvore de possibilidades e caso encontre senha o retorno será 1 */
        for (i = 0; i < 36; i++)
        {
            senhaPronto[senhaIndex] = CaracteresRestantes[i];
            if (gera_senha_forcabruta(senhaPronto, CaracteresRestantes, senhaIndex + 1))
                return 1;
        }
    }

    return 0;
}

/* Retorna 1 caso tenha encontrado a senha e 0 caso contrario */
int quebrador_senha_exaustivo()
{
    char vargs[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    int senhaIndex = 0;
    char v[7] = "";
    v[6] = '\0';

    int valida = gera_senha_forcabruta(v, vargs, senhaIndex);

    if (valida)
        return 1;
    return 0;
}

/* Gera senhas poda */
int gera_senha_poda(char senhaPronto[], char CaracteresRestantes[], int senhaIndex, int cont_letras, int cont_numeros)
{
    int i;
    char guardaCaracter;

    /* Caso base */
    if (senhaIndex == 6)
    {
        if (cont_letras == 1)
        {
            printf("letras - %d numeros - %d \n", cont_letras, cont_numeros);
        }
        if (login(senhaPronto))
            return 1;
    }

    else
    {
        /* Permutação */
        for (i = 0; i < 36; i++)
        {
            // printf("senhaPronto: %s\n", senhaPronto);
            /* Marca quando o caracter ja foi utilizado, para que pode a arvore */
            if (senhaIndex >= 4)
            {
                if (CaracteresRestantes[i] != '@' && i <= 26)
                {
                    /* Marcação de caracter já utilizado atraves do @ */
                    senhaPronto[senhaIndex] = CaracteresRestantes[i];
                    guardaCaracter = CaracteresRestantes[i];
                    CaracteresRestantes[i] = '@';

                    if (cont_letras >= 2 && cont_numeros >= 2)
                    {
                        if (gera_senha_poda(senhaPronto, CaracteresRestantes, senhaIndex + 1, cont_letras + 1, cont_numeros))
                            return 1;
                    }
                    // printf("letras - %d numeros - %d \n", cont_letras, cont_numeros);
                    // printf("senhaPronto: %s\n", senhaPronto);

                    CaracteresRestantes[i] = guardaCaracter;
                }
                else if (CaracteresRestantes[i] != '@' && i > 26)
                {
                    senhaPronto[senhaIndex] = CaracteresRestantes[i];
                    guardaCaracter = CaracteresRestantes[i];
                    CaracteresRestantes[i] = '@';

                    if (cont_letras >= 2 && cont_numeros >= 2)
                    {
                        if (gera_senha_poda(senhaPronto, CaracteresRestantes, senhaIndex + 1, cont_letras, cont_numeros + 1))
                            return 1;
                    }

                    CaracteresRestantes[i] = guardaCaracter;
                }
            }
            else
            {
                if (CaracteresRestantes[i] != '@' && i <= 26)
                {
                    /* Marcação de caracter já utilizado atraves do @ */
                    senhaPronto[senhaIndex] = CaracteresRestantes[i];
                    guardaCaracter = CaracteresRestantes[i];
                    CaracteresRestantes[i] = '@';

                    if (gera_senha_poda(senhaPronto, CaracteresRestantes, senhaIndex + 1, cont_letras + 1, cont_numeros))
                        return 1;

                    CaracteresRestantes[i] = guardaCaracter;
                }
                else if (CaracteresRestantes[i] != '@' && i > 26)
                {
                    senhaPronto[senhaIndex] = CaracteresRestantes[i];
                    guardaCaracter = CaracteresRestantes[i];
                    CaracteresRestantes[i] = '@';

                    if (gera_senha_poda(senhaPronto, CaracteresRestantes, senhaIndex + 1, cont_letras, cont_numeros + 1))
                        return 1;

                    CaracteresRestantes[i] = guardaCaracter;
                }
            }
        }
    }

    return 0;
}

/* Retorna 1 caso tenha encontrado a senha e 0 caso contrario */
int quebrador_senha_poda()
{
    char vargs[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    char v[7] = "";
    v[6] = '\0';
    int senhaIndex = 0;
    int tamanho = 0;

    int valida = gera_senha_poda(v, vargs, senhaIndex, 0, 0);

    if (valida)
        return 1;
    return 0;
}
