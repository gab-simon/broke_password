#include "biblioteca.h"
#include "quebrador-senha.h"

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
int quebrador_senha_exaustivo(){
    char vargs[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    int senhaIndex = 0;
    char v[7] = "";
    v[6] = '\0';

    int valida = gera_senha_forcabruta(v, vargs, senhaIndex);

    if (valida)
        return 1;
    return 0;
}

int valida_dupla(char senhaPronto[], int senhaIndex, int tamanho)
{
    char vargs[] = "abcdefghijklmnopqrstuvwxyz";
    int soma = 0;

    /* Caso a senha já tenha 5 de tamanho, ele entra na condição*/
    if (senhaIndex == 5)
    {
        /* Percorre a senha pronta e verifica se já tem mais de dois caracteres*/
        for (int i = tamanho; i < 26; i++)
        {
            for (int j = 0; j <= senhaIndex; j++)
            {
                if (senhaPronto[senhaIndex] = vargs[i])
                    soma++;
            }
        }
        if (soma >= 2 && soma <= 4)
            return 1;
    }

    return 0;
}

/* Gera senhas poda */
int gera_senha_poda(char senhaPronto[], char CaracteresRestantes[], int senhaIndex, int tamanho)
{
    int i;
    char guardaCaracter;

    /* Caso base */
    if (senhaIndex == 6)
    {
        if (login(senhaPronto))
            return 1;
    }

    else
    {
        if (!valida_dupla(senhaPronto, senhaIndex, tamanho + 1))
        {
            /* Permutação */
            for (i = tamanho; i < 36; i++)
            {
                /* Marca quando o caracter ja foi utilizado, para que pode a arvore */
                if (CaracteresRestantes[i] != '@')
                {

                    /* Marcação de caracter já utilizado atraves do @ */
                    senhaPronto[senhaIndex] = CaracteresRestantes[i];
                    guardaCaracter = CaracteresRestantes[i];
                    CaracteresRestantes[i] = '@';

                    if (gera_senha_poda(senhaPronto, CaracteresRestantes, senhaIndex + 1, tamanho + 1))
                        return 1;

                    CaracteresRestantes[i] = guardaCaracter;
                }
            }
        }
    }

    return 0;
}

/* Retorna 1 caso tenha encontrado a senha e 0 caso contrario */
int quebrador_senha_poda(){
    char vargs[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    char v[7] = "";
    v[6] = '\0';
    int senhaIndex = 0;
    int tamanho = 0;

    int valida = gera_senha_poda(v, vargs, senhaIndex, tamanho);

    if (valida)
        return 1;
    return 0;
}


