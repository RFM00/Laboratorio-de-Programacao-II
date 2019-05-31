#ifndef BUSCADOR_H
#define BUSCADOR_H

#include <iostream>
#include <string>
#include <time.h>

using namespace std;

void buscar_forca_bruta(const char *texto, const char *padrao, int *saida){
    bool find = false;
	for(int i = 0; texto[i] != '\0'; i++){
        find = true;
		for(int j = 0; padrao[j] != '\0'; j++){
			if(texto[i+j] != padrao[j]){
				find = false;
				break;
			}
		}
		if(find){ 
			*saida = i;
            saida++;
		}
	}
    *saida = -1;
}

int *calcular_pi(const char *padrao){
    const char *aux = padrao;
    int m = 0;
    while (*aux != '\0')
    {
        m++;
        aux++;
    }

    int *pi = new int[m];
    int k, l;

    pi[0] = 0;
    for (int i = 1; i < m; i++)
    {
        k = i - 1;
        while (true)
        {
            l = pi[k];
            if (l == 0)
            {
                if (padrao[0] == padrao[i])
                {
                    pi[i] = 1;
                    break;
                }else
                {
                    pi[i] = 0;
                    break;
                }
            }else
            {
                if (padrao[i] == padrao[l])
                {
                    pi[i] = l + 1;
                    break;
                }else
                {
                    k = l - 1;
                }
            }    
        }
    }

    return pi;
}

void buscar_KMP(const char *texto, const char *padrao, int *saida){
    int *pi = calcular_pi(padrao);
    
    int i = 0, j = 0;
    while (texto[i] != '\0')
    {
        if (texto[i] != padrao[j])
        {
            if (j == 0)
            {
                ++i;
            }else
            {
                j = pi[j - 1];
            }
        }else
        {
            if (padrao[j + 1] == '\0')
            {
                *saida = i - j;
                saida++;
                j = pi[j];
                ++i;
            }else
            {
                ++i;
                ++j;
            }
        }
    }
    *saida = -1;
}

#endif