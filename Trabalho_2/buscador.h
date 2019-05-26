#ifndef BUSCADOR_H
#define BUSCADOR_H

int *buscar_forca_bruta(char *T, char *P, int n, int m){
	int *ocorrencia = new int[n];
	bool find = false;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(T[i+j] != P[j]){
				find = false;
				break;
			}else{ 
				find = true; 
			}
		}

		if(find){ 
			ocorrencia[i] = 1; 
		}
		else {
			ocorrencia[i] = 0; 
		}
	}
	return ocorrencia;
}

int *calcular_pi(char *P){
    char *aux = P;
    int m = 0;
    while (*aux != '\0')
    {
        m++;
        aux++;
    }
    delete aux;

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
                if (P[0] == P[i])
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
                if (P[i] == P[l])
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

void buscar_KMP(char *texto, char *padrao, int *saida){
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
        *saida = -1;
    }
}

#endif