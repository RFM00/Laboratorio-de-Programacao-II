'''Essa função utiliza o ultimo elemento como pivô,
particiona de modo que os menores ficarão a esquerda e
os maiores a direita, e retorna o indice do pivô
'''
def particionamento(A, inicio, fim):
    # Pivo foi escolhido como o ultimo elemento do vetor
    pivo = A[fim]
    # Vamos iterar a partir do primeiro elemento até o fim
    i = inicio - 1
    for j in range(inicio, fim):
        if A[j] < pivo:
            i += 1
            A[i], A[j] = A[j], A[i]
    # Devolve o pivo para o lugar correto
    A[fim], A[i + 1] = A[i + 1], A[fim]
    # Retorna o indice do pivo
    return i + 1

'''Quick Sort
A = lista de valores
inicio = primeiro elemento da lista
fim = ultimo elemento da lista
'''
def quickSort(A, inicio, fim):
    if inicio < fim:
        pivo = particionamento(A, inicio, fim)
        quickSort(A, inicio, pivo - 1)
        quickSort(A, pivo + 1, fim)


def quickSortMemoria(A, inicio, fim):
    while inicio < fim:
        pivo = particionamento(A, inicio, fim)
        if pivo - inicio < fim - pivo:
            quickSortMemoria(A, inicio, pivo - 1)
            inicio = pivo + 1
        else:
            quickSortMemoria(A, pivo + 1, fim)
            fim = pivo - 1


if __name__ == "__main__":
    A = [6, 7, 8, 9, 1, 5]
    B = [6, 7, 8, 9, 1, 5]

    quickSort(A, 0, len(A) - 1)
    print(A)

    quickSortMemoria(B, 0, len(B) - 1)
    print(B)