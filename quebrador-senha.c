#include "biblioteca.h"
#include "quebrador-senha.h"
#include <stdio.h>

/* Gera senhas força bruta*/
int gera_senha_forcabruta(char senhaPronto[], char caracteresRestantes[], int senhaIndex)
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
            senhaPronto[senhaIndex] = caracteresRestantes[i];
            if (gera_senha_forcabruta(senhaPronto, caracteresRestantes, senhaIndex + 1))
                return 1;
        }
    }

    return 0;
}

/* Retorna 1 caso tenha encontrado a senha e 0 caso contrario */
int quebrador_senha_exaustivo()
{
    char vargs[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    char v[7] = "";
    v[6] = '\0';

    int valida = gera_senha_forcabruta(v, vargs, 0);

    if (valida)
        return 1;
    return 0;
}

/* Gera senhas poda */
int gera_senha_poda(char senhaPronto[], char caracteresRestantes[], int senhaIndex, int contLetras, int contNumeros)
{
    char guardaCaracter;

    /* Caso base */
    if (senhaIndex == 6)
    {
        if (login(senhaPronto))
            return 1;
        return 0;
    }

    else
    {
        /* Permutação */
        for (int i = 0; i < 36; i++)
        {
            /* Marca quando o caracter ja foi utilizado, para que pode a arvore */
            if (caracteresRestantes[i] != '@')
            {
                /* Marcação de caracter já utilizado atraves do @ */
                senhaPronto[senhaIndex] = caracteresRestantes[i];
                guardaCaracter = caracteresRestantes[i];
                caracteresRestantes[i] = '@';

                if (senhaPronto[senhaIndex] > 57)
                {
                    if (contLetras < 4)
                        if (gera_senha_poda(senhaPronto, caracteresRestantes, senhaIndex + 1, contLetras + 1, contNumeros))
                            return 1;
                }

                else
                {
                    if (contNumeros < 4)
                        if (gera_senha_poda(senhaPronto, caracteresRestantes, senhaIndex + 1, contLetras, contNumeros + 1))
                            return 1;
                }

                caracteresRestantes[i] = guardaCaracter;
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

    int valida = gera_senha_poda(v, vargs, 0, 0, 0);

    if (valida)
        return 1;
    return 0;
}
