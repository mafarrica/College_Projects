# # # # # # # # # # # # # # # # # #
# Mafalda Fernandes  LEIC-T 21/22 #
# ist1102702                      #
# # # # # # # # # # # # # # # # # #


#BUGGY DATA BASE#

#1.2.1
def corrigir_palavra(palavra):
    '''
    Retirar pares maiuscula-minuscula da mesma letra (e vice-versa) de uma palavra
    corrigir_palavra: cad. carateres -> cad. carateres
    '''
    maiusculas = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                  'U', 'V', 'W', 'X', 'Y', 'Z']
    minusculas = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                  'u', 'v', 'w', 'x', 'y', 'z']

    lista_palavra = list(palavra)
    index_letra = 0
    while index_letra < len(lista_palavra) - 1:         #percorrer a palavra letra a letra
        if lista_palavra[index_letra] in maiusculas and lista_palavra[index_letra + 1] in minusculas:           #verificar se sao um par maiuscula-minuscula
            if maiusculas.index(lista_palavra[index_letra]) == minusculas.index(lista_palavra[index_letra+1]):     #verificar se se trata da mesma letra
                del lista_palavra[index_letra + 1]
                del lista_palavra[index_letra]
                index_letra = 0
            else:
                index_letra += 1
        elif lista_palavra[index_letra] in minusculas and lista_palavra[index_letra + 1] in maiusculas:          #verificar se sao um par minuscula-maiuscula
            if minusculas.index(lista_palavra[index_letra]) == maiusculas.index(lista_palavra[index_letra+1]):      #verificar se se trata da mesma letra
                del lista_palavra[index_letra + 1]
                del lista_palavra[index_letra]
                index_letra = 0
            else:
                index_letra += 1
        else:
            index_letra += 1

    palavra = ''
    for e in lista_palavra:            #tranformar a lista que contem as letras ja revistas numa unica string final
        palavra += e

    return palavra

#1.2.2
def eh_anagrama(palavra1, palavra2):
    '''
    Verifica se as duas palavras dadas sao anagramas
    eh_anagrama: cad. carateres × cad. carateres -> booleano
    '''
    lista1 = list(palavra1.upper())        #transformar todas as letras em maiusculas para ignorar diferencas entre maiusculas e minusculas
    lista2 = list(palavra2.upper())

    if len(lista1) == len(lista2):          #se sao anagramas tem o mesmo tamanho
        index_letra_verificacao = 0
        while index_letra_verificacao < len(lista1) and lista1[index_letra_verificacao] in lista2:      #apagar da segunda palavra todas as letras iguais as da primeira palavra
            del lista2[lista2.index(lista1[index_letra_verificacao])]
            index_letra_verificacao += 1

        return len(lista2) == 0                  #se no final a segunda palavra for vazia, trata-se de uma anagrama

    else:
        return False

#1.2.3
def corrigir_doc(texto):
    '''
    Corrige todas as palavras de um texto e retira os anagramas de palavras diferentes
    corrigir_doc: cad. carateres -> cad. carateres
    '''
    if not type(texto) == str:
        raise ValueError('corrigir_doc: argumento invalido')

    lista_texto = [texto]
    for letra in texto:
        if texto == '' or (not letra.isalpha() and not letra.isspace()):
            raise ValueError('corrigir_doc: argumento invalido')

    for index_letra in range(len(texto)):
        if texto[index_letra] == ' ' and texto[index_letra + 1] == ' ':
            raise ValueError('corrigir_doc: argumento invalido')


    lista_palavras = lista_texto[0].split()             #separar o texto por palavras

    correcao = []
    for palavra in lista_palavras:             #corrigir cada palavra do texto e coloca-la numa nova lista
        correcao += [corrigir_palavra(palavra)]


    index_palavra = 0
    while index_palavra < len(correcao) - 1:           #verificar se existem anagramas e se existirem e forem palavras diferentes, apagar a segunda palavra
        index_palavra_seguinte = index_palavra + 1
        while index_palavra_seguinte < len(correcao):
            if eh_anagrama(correcao[index_palavra], correcao[index_palavra_seguinte]) and correcao[index_palavra].upper() != correcao[index_palavra_seguinte].upper():
                del correcao[index_palavra_seguinte]
            index_palavra_seguinte += 1
        index_palavra += 1


    index_palavra = 0
    texto_final_lista = []
    while index_palavra < len(correcao):          #acrescentar os espaços entre palavras
        if index_palavra < len(correcao) - 1:
            texto_final_lista += [correcao[index_palavra]] + [' ']
            index_palavra += 1
        else:
            texto_final_lista += [correcao[index_palavra]]
            index_palavra += 1

    texto_final = ''
    for e in texto_final_lista:            #transformar a lista das palavras todas corrigidas numa string final
        texto_final += e

    return texto_final


#2.2.1
def obter_posicao(caracter, inteiro):
    '''
    Devolve a posicao final apos um dos digitos(posicao inicial) sofrer um dos movimentos
    obter_posicao: cad. carateres × inteiro -> inteiro
    '''
    lista_hor = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    lista_ver = [[1, 4, 7], [2, 5, 8], [3, 6, 9]]

    if caracter == 'C':               #moviemento apos pressionar 'C'
        if inteiro in lista_hor[0]:      #se se tratar do 1, 2, ou 3, retornar o proprio numero
            return inteiro
        elif inteiro in lista_ver[0]:
            return lista_ver[0][lista_ver[0].index(inteiro) - 1]
        elif inteiro in lista_ver[1]:
            return lista_ver[1][lista_ver[1].index(inteiro) - 1]
        else:
            return lista_ver[2][lista_ver[2].index(inteiro) - 1]

    if caracter == 'B':               #movimento apos pressionar 'B'
        if inteiro in lista_hor[2]:           #se se tratar do 7, 8 ou 9, retornar o proprio numero
            return inteiro
        elif inteiro in lista_ver[0]:
            return lista_ver[0][lista_ver[0].index(inteiro) + 1]
        elif inteiro in lista_ver[1]:
            return lista_ver[1][lista_ver[1].index(inteiro) + 1]
        else:
            return lista_ver[2][lista_ver[2].index(inteiro) + 1]

    if caracter == 'D':              #movimento apos pressionar 'D'
        if inteiro in lista_ver[2]:         #se se tratar do 3, 6 ou 9, retornar o proprio numero
            return inteiro
        elif inteiro in lista_hor[0]:
            return lista_hor[0][lista_hor[0].index(inteiro) + 1]
        elif inteiro in lista_hor[1]:
            return lista_hor[1][lista_hor[1].index(inteiro) + 1]
        else:
            return lista_hor[2][lista_hor[2].index(inteiro) + 1]

    if caracter == 'E':              #movimento apos pressionar 'E'
        if inteiro in lista_ver[0]:        #se se tratar do 1, 4 ou 7, retornar o proprio numero
            return inteiro
        elif inteiro in lista_hor[0]:
            return lista_hor[0][lista_hor[0].index(inteiro) - 1]
        elif inteiro in lista_hor[1]:
            return lista_hor[1][lista_hor[1].index(inteiro) - 1]
        else:
            return lista_hor[2][lista_hor[2].index(inteiro) - 1]

#2.2.2
def obter_digito(cad, inteiro):
    '''
    Devolve a posicao final apos um dos digitos(posicao inicial) sofrer varios movimentos
    obter_digito: cad. carateres × inteiro -> inteiro
    '''
    lista_cad = list(cad)

    for movimento in lista_cad:          #aplicar cada movimento ao inteiro resultante do movimento anterior
        inteiro = obter_posicao(movimento, inteiro)

    return inteiro

#2.2.3
def obter_pin(tuplo):
    '''
    Devolve o pin resultante da sequencia de movimentos fornecida
    obter_pin: tuplo -> tuplo
    '''
    if type(tuplo) != tuple or len(tuplo) < 4 or len(tuplo) > 10:
        raise ValueError('obter_pin: argumento invalido')

    for string in tuplo:
        if type(string) != str or string == '':
            raise ValueError('obter_pin: argumento invalido')
        for letra in string:
            if letra != 'C' and letra != 'B' and letra != 'E' and letra != 'D':
                raise ValueError('obter_pin: argumento invalido')
    num = 5
    final = ()
    for movimento in tuplo:        #aplicar cada um dos movimentos ao inteiro resultante do movimento anterior, comecando pelo 5
        num = obter_digito(movimento, num)
        final += (num,)          #inserir o resultado num tuplo final

    return final


#3.2.1
def eh_entrada(elemento):
    '''
    Verifica se o argumento dado corresponde a uma entrada valida da BDB, segundo os criterios dados
    eh_entrada: universal -> booleano
    '''
    if type(elemento) != tuple or len(elemento) != 3:       #verificar se é tuplo e se tem 3 elementos
        return False

    cifra = elemento[0]
    checksum = elemento[1]
    tuplo = elemento[2]

    #verificar o tipo da cifra, do checksum e do tuplo dos numeros de seguranca
    if type(cifra) != str or\
    type(checksum) != str or\
    type(tuplo) != tuple:
        return False

    if cifra == '':
        return False

    controlo = 0
    for char in cifra:
        if char.islower() or char == '-':       #cada elemento da cifra apenas pode ser uma letra minuscula ou um hifen
            controlo += 1
    if controlo != len(cifra):
        return False

    #o checksum deve ter 7 elementos, dois parenteses retos e 5 letras
    if len(checksum) != 7 or\
    checksum[0] != '[' or\
    checksum[-1] != ']':
        return False

    num_parenteses = 0
    for elemento in checksum:
        if elemento == '[' or elemento == ']':
            num_parenteses += 1
    if num_parenteses != 2:       #o checksum apenas pode ter dois parenteses retos
        return False

    controlo = 0
    for elemento in checksum:
        if elemento.islower() or elemento == '[' or elemento == ']':    #verificar se os elementos do checksum apenas sao letras minusculas e parenteses retos
            controlo += 1
    if controlo != len(checksum):
        return False

    if len(tuplo) < 2:          #verificar se o tuplo dos numeros de seguranca tem mais de dois argumentos
        return False

    for num in tuplo:           #verificar que o tuplo dos numeros de seguranca apenas é composto por inteiros positivos
        if type(num) != int or num <= 0:
            return False

    return True

#3.2.2
def validar_cifra(cifra, checksum):
    '''
    Verifica se o segundo argumento é composto pelas cinco letras da cifra com mais ocorrencias
    validar_cifra: cad. carateres × cad. carateres -> booleano
    '''
    num_ocorrencias_letra = []
    guardar_letra = []
    for letra in cifra:     #gurdaar em duas listas cada letra o seu numero de ocorrencias de forma a terem o mesmo indice
        if letra.isalpha():
            if letra in guardar_letra:
                num_ocorrencias_letra[guardar_letra.index(letra)] += 1
            else:
                guardar_letra += [letra]
                num_ocorrencias_letra += [1]


    organizado = []
    while len(guardar_letra) > 0:
        maior_valor = 0
        lista_temp = []
        for valor in num_ocorrencias_letra:        #verificar qual o maior numero de ocorrencias na lista de ocorrencias
            if valor > maior_valor:
                maior_valor = valor

        index_num = 0
        while index_num < len(num_ocorrencias_letra):
            #procurar a letra com maior ocorrencia
            if num_ocorrencias_letra[index_num] == maior_valor:
                #guardar a letra com maior ocorrencia numa lista temporaria e apaga-la da lista de letras e da lista de ocorrencias
                lista_temp += [guardar_letra[num_ocorrencias_letra.index(num_ocorrencias_letra[index_num])]]
                del guardar_letra[num_ocorrencias_letra.index(maior_valor)]
                del num_ocorrencias_letra[num_ocorrencias_letra.index(maior_valor)]
                index_num = 0       #voltar ao inicio da lista para nova verificacao
            else:
                index_num += 1
            if len(num_ocorrencias_letra) == 0:
                break
        #por cada bloco de letras com igual numero de ocorrencia, organizar o bloco por ordem alfabetica
        organizado += sorted(lista_temp)

    #criar um checksum com os resultados
    checksum_criado = '[' + organizado[0] + organizado[1] + organizado[2] + organizado[3] + organizado[4] + ']'

    #verificar se o checksum criado corresponde ao recebido
    return checksum == checksum_criado

#3.2.3
def filtrar_bdb(lista):
    '''
    Recebe uma ou mais entradas da BDB e devolve apenas aquelas em que o checksum nao e coerente com a cifra
    filtrar_bdb: lista -> lista
    '''
    if type(lista) != list or lista == []:
        raise ValueError('filtrar_bdb: argumento invalido')

    lista_final = []
    for entrada in lista:
        if not eh_entrada(entrada):     #verificar que cada entrada fornecida e valida
            raise ValueError('filtrar_bdb: argumento invalido')
        else:
            if not validar_cifra(entrada[0], entrada[1]):
                lista_final += [entrada]        #criar uma lista com todas as entradas nao coerentes


    return lista_final


#4.2.2
def obter_num_seguranca(tuplo):
    '''
    Recebe numeros inteiros positivos e devolve a menor diferenca positiva entre qualquer par desses numeros
    obter_num_seguranca: tuplo -> inteiro
    '''
    diferenca = 0
    num_controlo = 0
    while num_controlo < len(tuplo) - 1:
        num_seguinte = 1
        while num_seguinte < len(tuplo):
            if diferenca == 0:      #situacao inicial em que ainda nenhuma diferenca foi identificada
                #guardar apenas a diferenca que for positiva
                if tuplo[num_controlo] - tuplo[num_seguinte] > 0:
                    diferenca = tuplo[num_controlo] - tuplo[num_seguinte]
                elif tuplo[num_seguinte] - tuplo[num_controlo] > 0:
                    diferenca = tuplo[num_seguinte] - tuplo[num_controlo]
            #verificar se a diferenca entre os numeros que estao a ser avaliados e menor do que a diferenca obtida anteriormente
            if 0 < tuplo[num_controlo] - tuplo[num_seguinte] < diferenca:
                diferenca = tuplo[num_controlo] - tuplo[num_seguinte]       #guarda-la se for menor
            if 0 < tuplo[num_seguinte] - tuplo[num_controlo] < diferenca:
                diferenca = tuplo[num_seguinte] - tuplo[num_controlo]
            num_seguinte += 1
        num_controlo += 1


    return diferenca

#4.2.3
def decifrar_texto(cifra, num_seg):
    '''
    Troca cada letra da cifra avançando no alfabeto o numero de vezes do numero de seguranca, mais 1 se o indice da letra for par ou menos 1 se for impar. No final substitui os tracos por espacos
    decifrar_texto: cad. carateres × inteiro -> cad. carateres
    '''
    alfabeto = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
    string_final = ''
    num_seg_perm = num_seg

    for letra_index in range(len(cifra)):
        letra = cifra[letra_index]

        if letra.isalpha():     #se o elemento da cifra for uma letra
            #verificar se e par ou impar e alterar o numero de seguranca dependendo do que for
            if letra_index % 2 == 0:
                num_seg += 1
            else:
                num_seg -= 1
            index = alfabeto.index(letra)
            while num_seg > 0:
                if index == 25:     #se ao avancar no alfabeto chegar ao final, voltar ao inicio e continuar a avancar caso necessario
                    index = 0
                    num_seg -= 1
                else:
                    index += 1
                    num_seg -= 1
            string_final += alfabeto[index]         #adicionar ao resultado final a letra obtida

        else:           #se o elemento da cifra for uma letra substituir por um espaco
            string_final += ' '
        num_seg = num_seg_perm

    return string_final

#4.2.4
def decifrar_bdb(lista):
    '''
    Recebe uma ou mais entradas da BDB e devolve as entradas decifradas
    decifrar_bdb: lista -> lista
    '''
    if type(lista) != list:
        raise ValueError('decifrar_bdb: argumento invalido')

    for entrada in lista:       #verificar que cada entrada e valida
        if not eh_entrada(entrada):
            raise ValueError('decifrar_bdb: argumento invalido')

    lista_final = []
    #adicionar a uma lista final cada uma das entradas depois de decifradas
    for entrada in lista:
        lista_final += [decifrar_texto(entrada[0], obter_num_seguranca(entrada[2]))]

    return lista_final


#5.2.1
def eh_utilizador(arg):
    '''
    Verifica se o dicionario recebido com as informacoes do utilizador (nome, senha e regra individual) e valido
    eh_utilizador: universal -> booleano
    '''
    if type(arg) != dict or len(arg) != 3:      #verificar se e um dicionario e tem 3 argumentos
        return False

    if 'name' not in arg or 'pass' not in arg or 'rule' not in arg:     #verificar se os argumentos se tratam do nome, senha e regra individual
        return False

    if type(arg['name']) != str or type(arg['pass']) != str or type(arg['rule']) != dict:       #verificar se o nome e a senha sao strings e que a regra e um dicionario
        return False

    if len(arg['name']) < 1 or len(arg['pass']) < 1:        #verificar se o nome e a senha tem apenas 1 argumento
        return False

    if len(arg['rule']) != 2:       #verificar se a regra individual tem 2 pares chave-valor
        return False

    if 'vals' not in arg['rule'] or 'char' not in arg['rule']:      #verificar se as chaves da regra individual sao 'vals' e 'char'
        return False

    if type(arg['rule']['vals']) != tuple or type(arg['rule']['char']) != str:  #verificar se 'vals' e um tuplo e que 'char' e uma string
        return False

    for numero in arg['rule']['vals']:      #verificar se os elementos dentro do tuplo de 'vals' sao inteiros positivos
        if type(numero) != int or numero < 0:
            return False

    for letra in arg['rule']['char']:       #verificar se os elementos dentro da string 'char' sao letras minusculas
        if not letra.isalpha() and not letra.islower():
            return False

    if len(arg['rule']['vals']) != 2 or len(arg['rule']['char']) != 1:      #verificar se o tuplo de 'vals' apenas tem 2 elementos e se a string de 'char' apenas tem 1 elemento
        return False

    if arg['rule']['vals'][0] > arg['rule']['vals'][1]:     #verificar se o primeiro elemento do tuplo de 'vals' e menor que o segundo
        return False

    return True

#5.2.2
def eh_senha_valida(senha, dicionario):
    '''
    Recebe uma senha e uma regra individual (em dicionario) e verifica se a senha cumpre as regras gerais e individuais
    eh_senha_valida: cad. carateres × dicionario -> booleano
    '''
    vogais = ['a', 'e', 'i', 'o', 'u']

    #verificar se todas as letras da senha sao vogais minusculas
    num_vogais = 0
    for letra in senha:
        if letra in vogais:
            num_vogais += 1
    if num_vogais < 3:
        return False

    #verificar se pelo menos uma das letras da senha aparece duas vezes consecutivas
    char_consec = 0
    for index_letra in range(len(senha)):
        if index_letra < len(senha) - 1 and senha[index_letra] == senha[index_letra + 1]:
            char_consec += 1
    if char_consec == 0:
        return False

    #contar quantas vezes a letra que esta no elemento 'char' do dicionario aparece na senha
    char_regra_indiv = 0
    for letra in senha:
        if letra == dicionario['char']:
            char_regra_indiv += 1

    #verificar se esse numero de vezes esta entre o primeiro numero do tuplo do elemento 'vals' do dicionario e o segundo numero desse tuplo
    if not dicionario['vals'][0] <= char_regra_indiv <= dicionario['vals'][1]:
        return False

    return True

#5.2.3
def filtrar_senhas(lista):
    '''
    Recebe uma lista com um ou mais dicionarios correspondentes a entradas da BDB e devolve os nomes dos utilizadores com senhas invalidas por ordem alfabetica
    filtrar_senhas: lista -> lista
    '''
    if type(lista) != list or lista == []:
        raise ValueError('filtrar_senhas: argumento invalido')

    for entrada in lista:       #verificar se cada entrada e valida
        if entrada == {} or type(entrada) != dict:
            raise ValueError('filtrar_senhas: argumento invalido')
        if not eh_utilizador(entrada):
            raise ValueError('filtrar_senhas: argumento invalido')

    #verificar quais os utilizadores com senha errada e aadicionar os seus nomes a uma lista
    user_senha_errada = []
    for elemento in lista:
        if not eh_senha_valida(elemento['pass'], elemento['rule']):
            user_senha_errada += [elemento['name']]

    lista_final = sorted(user_senha_errada)     #ordenar a lista dos nomes alfabeticamente

    return lista_final