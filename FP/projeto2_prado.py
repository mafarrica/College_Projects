#########################################
#      O Prado  -  projeto 2 FP 21/22   #
#  Mafalda Fernandes                    #
#  aluno: 102702                        #
#  LEIC-T 1Ano                          #
#########################################


#Funcoes das posicoes
def cria_posicao(x, y):
    '''
    cria_posicao: int × int -> posicao
    Recebe duas coordenadas e devolve uma posicao
    '''
    if type(x) != int or type(y) != int or x < 0 or y < 0:
        raise ValueError('cria_posicao: argumentos invalidos')
    return [x, y]

def cria_copia_posicao(p):
    '''
    cria_copia posicao: posicao -> posicao
    Recebe uma posicao e devolve uma copia
    '''
    return p.copy()

def obter_pos_x(p):
    '''
    obter_pos_x : posicao -> int
    Recebe uma posicao e devolve a sua abcissa
    '''
    return p[0]

def obter_pos_y(p):
    '''
    obter_pos_y : posicao -> int
    Recebe uma posicao e devolve a sua ordenada
    '''
    return p[1]

def eh_posicao(arg):
    '''
    eh_posicao: universal -> booleano
    Recebe um argumento e verifica se corresponde a uma posicao
    '''
    return type(arg) == list and\
            len(arg) == 2 and\
            type(arg[0]) == int and\
            type(arg[1]) == int and\
            arg[0] >= 0 and\
            arg[1] >= 0

def posicoes_iguais(p1, p2):
    '''
    posicoes_iguais: posicao × posicao -> booleano
    Recebe duas posicoes e verifica se sao iguais
    '''
    return eh_posicao(p1) and\
            eh_posicao(p2) and\
            p1[0] == p2[0] and\
            p1[1] == p2[1]

def posicao_para_str(pos):
    '''
    posicao_para_str : posicao -> str
    Recebe uma posicao e devolve a posicao no tipo string
    '''
    return '(' + str(pos[0]) + ',' + ' ' +  str(pos[1]) + ')'

def obter_posicoes_adjacentes(pos):
    '''
    obter_posicoes adjacentes: posicao -> tuplo
    Recebe uma posicao e devolve um tuplo com as posicoes que estao em cima, a direita, em baixo e a esquerda dessa posicao
    '''
    tuplo_final = ()
    #posicao acima
    if obter_pos_y(pos) - 1 >= 0:
        tuplo_final += (cria_posicao(obter_pos_x(pos), obter_pos_y(pos) - 1),)
    #posicao a direita
    tuplo_final += (cria_posicao(obter_pos_x(pos) + 1, obter_pos_y(pos)),)
    #posicao em baixo
    tuplo_final += (cria_posicao(obter_pos_x(pos), obter_pos_y(pos) + 1),)
    #posicao a esquerda
    if obter_pos_x(pos) - 1 >= 0:
        tuplo_final += (cria_posicao(obter_pos_x(pos) - 1, obter_pos_y(pos)),)
    return tuplo_final

def ordenar_posicoes(tuplo):
    '''
    ordenar_posicoes: tuplo -> tuplo
    Recebe um tuplo com varias posicoes e devolve um tuplo com essas posicoes ordenadas primeiro pelo eixo dos y e depois pelo eixo do x
    '''
    lista = []
    for posicao in tuplo:
        lista += [(obter_pos_x(posicao), obter_pos_y(posicao))]
    lista_copia = lista.copy()
    lista.sort(key=lambda x: x[1])   #lista organizada pelos y de cada posicao
    #dentro das posicoes com y iguais organizam-se pelos x
    lista_sorted = []
    while len(lista) > 0:
        lista_aux = []
        for index in range(len(lista)):
            if lista[index][1] == lista[0][1]:
                lista_aux += [lista[index]]
        lista_aux.sort(key=lambda x: x[0])
        lista_sorted += lista_aux
        for elemento in lista_aux:
            lista.remove(elemento)
    #ir buscar as posicoes ja organizadas ao tuplo original
    tuplo_final = ()
    for elemento in lista_sorted:
        tuplo_final += (tuplo[lista_copia.index(elemento)],)
    return tuplo_final




#Funcoes dos animais
def cria_animal(s, r, a):
    '''
    cria_animal: str × int × int -> animal
    Recebe tres argumentos (especie, frequecia de reproducao e frequencia de alimentacao) e devolve o animal correspondente
    O tipo de animal depende da frequencia de alimentacao, se for 0 e uma presa, se nao e um predador
    '''
    if type(s) != str or type(r) != int or type(a) != int or s == '' or r <= 0 or a < 0:
        raise ValueError('cria_animal: argumentos invalidos')
    if a > 0:
        return [s, 0, r, 0, a]
    else:
        return [s, 0, r]

def cria_copia_animal(animal):
    '''
    cria_copia_animal: animal -> animal
    Recebe um animal e devolve uma copia desse animal
    '''
    return animal.copy()

def obter_especie(animal):
    '''
    obter_especie: animal -> str
    Recebe um animal e devolve a especie desse animal
    '''
    return animal[0]

def obter_freq_reproducao(animal):
    '''
    obter_freq_reproducao: animal -> int
    Recebe um animal e devolve a frequencia de reproducao desse animal
    '''
    return animal[2]

def obter_freq_alimentacao(animal):
    '''
    obter_freq_alimentacao: animal -> int
    Recebe um animal e devolve a frequencia de alimentacao desse animal
    '''
    if len(animal) == 5:
        return animal[4]
    else:
        return 0

def obter_idade(animal):
    '''
    obter_idade: animal -> int
    Recebe um animal e devolve a idade desse animal
    '''
    return animal[1]

def obter_fome(animal):
    '''
    obter_fome: animal -> int
    Recebe um animal e devolve a fome desse animal
    '''
    if len(animal) == 5:
        return animal[3]
    else:
        return 0

def aumenta_idade(animal):
    '''
    aumenta_idade: animal -> animal
    Recebe um animal e adiciona 1 a idade desse animal
    '''
    animal[1] += 1
    return animal

def reset_idade(animal):
    '''
    reset_idade: animal -> animal
    Recebe um animal e altera a idade desse animal para 0
    '''
    animal[1] = 0
    return animal

def aumenta_fome(animal):
    '''
    aumenta_fome: animal -> animal
    Recebe um animal e adiciona 1 a fome desse animal
    '''
    if len(animal) == 5:
        animal[3] += 1
    return animal

def reset_fome(animal):
    '''
    reset_fome: animal -> animal
    Recebe um animal e altera a fome desse animal para 0
    '''
    if len(animal) == 5:
        animal[3] = 0
    return animal

def eh_animal(arg):
    '''
    eh_animal: universal -> booleano
    Recebe um argumento e verifica se corresponde a um animal
    '''
    return type(arg) == list and \
           ((len(arg) == 5 and          #se for predador
            type(arg[0]) == str and arg[0] != '' and
            type(arg[1]) == int and arg[1] >= 0 and
            type(arg[2]) == int and arg[2] > 0 and
            type(arg[3]) == int and arg[3] >= 0 and
            type(arg[4]) == int and arg[4] > 0) or
           (len(arg) == 3 and           #se for presa
            type(arg[0]) == str and arg[0] != '' and
            type(arg[1]) == int and arg[1] >= 0 and
            type(arg[2]) == int and arg[2] > 0
            ))

def eh_predador(arg):
    '''
    eh_predador : universal -> booleano
    Recebe um argumento e verifica se corresponde a um animal predador
    '''
    return eh_animal(arg) and \
           len(arg) == 5 and \
           type(arg[0]) == str and arg[0] != '' and \
           type(arg[1]) == int and arg[1] >= 0 and \
           type(arg[2]) == int and arg[2] > 0 and \
           type(arg[3]) == int and arg[3] >= 0 and \
           type(arg[4]) == int and arg[4] > 0

def eh_presa(arg):
    '''
    eh_presa: universal -> booleano
    Recebe um argumento e verifica se corresponde a um animal presa
    '''
    return eh_animal(arg) and \
           len(arg) == 3 and \
           type(arg[0]) == str and arg[0] != '' and \
           type(arg[1]) == int and arg[1] >= 0 and \
           type(arg[2]) == int and arg[2] > 0

def animais_iguais(a1, a2):
    '''
    animais_iguais: animal × animal -> booleano
    Recebe dois animais e verifica se sao iguais
    '''
    return eh_animal(a1) and eh_animal(a2) and a1 == a2

def animal_para_char(animal):
    '''
    animal_para_char : animal -> str
    Recebe um animal e devolve a primeira letra do nome da sua especie
    A letra e maiuscula se for um predador e minuscula se for uma presa
    '''
    if eh_predador(animal):
        return animal[0][0].upper()
    else:
        return animal[0][0].lower()

def animal_para_str(animal):
    '''
    animal_para_str : animal -> str
    Recebe um animal e devolve esse animal no tipo string na forma
    se for predador -> 'especie [idade/freq rep; fome/freq alim]'
    se for presa -> 'especie [idade/freq rep]'
    '''
    if eh_predador(animal):
        return str(obter_especie(animal)) + ' ' + '[' + str(obter_idade(animal)) + '/' + str(obter_freq_reproducao(animal)) +\
               ';' + str(obter_fome(animal)) + '/' + str(obter_freq_alimentacao(animal)) + ']'
    else:
        return str(obter_especie(animal)) + ' ' + '[' + str(obter_idade(animal)) + '/' + str(obter_freq_reproducao(animal)) + ']'

def eh_animal_fertil(animal):
    '''
    eh_animal_fertil: animal -> booleano
    Recebe um animal e verifica se a sua idade e maior ou igual a frequecia de reproducao
    '''
    return obter_idade(animal) >= obter_freq_reproducao(animal)

def eh_animal_faminto(animal):
    '''
    eh_animal_faminto: animal -> booleano
    Recebe um animal e verifica se a sua foma e maior ou igual a frequecia de alimentacao
    '''
    if eh_predador(animal):
        return obter_fome(animal) >= obter_freq_alimentacao(animal)
    else:
        return False

def reproduz_animal(animal):
    '''
    reproduz_animal: animal -> animal
    Recebe um animal e devolve um novo animal da mesma especie, com igual freq de rep e freq de alimentacao
    Altera a idade do animal fornecido para 0
    '''
    if eh_predador(animal):
        novo_animal = cria_animal(obter_especie(animal), obter_freq_reproducao(animal), obter_freq_alimentacao(animal))
    else:
        novo_animal = cria_animal(obter_especie(animal), obter_freq_reproducao(animal), 0)

    reset_idade(animal)
    return novo_animal




#Funcoes do prado
def cria_prado(d, r, a, p):
    '''
    cria_prado: posicao × tuplo × tuplo × tuplo -> prado
    Recebe argumentos correspondentes ao limite do prado, posicoes dos rochedos, animais do prado e posicoes desses animais
    e devolve um prado com essas informacoes organizadas
    '''
    if not eh_posicao(d) or (type(r) != tuple and type(r) != list) or \
            (type(a) != tuple and type(a) != list) or \
            (type(p) != tuple and type(p) != list) \
            or len(a) == 0 or len(p) != len(a):
        raise ValueError('cria_prado: argumentos invalidos')

    for elemento in r:
        if not eh_posicao(elemento):
            raise ValueError('cria_prado: argumentos invalidos')
        if 0 >= obter_pos_x(elemento) or obter_pos_x(elemento) >= obter_pos_x(d) or \
            0 >= obter_pos_y(elemento) or obter_pos_y(elemento) >= obter_pos_y(d):
            raise ValueError('cria_prado: argumentos invalidos')

    for elemento in a:
        if not eh_animal(elemento):
            raise ValueError('cria_prado: argumentos invalidos')

    for elemento in p:
        if not eh_posicao(elemento):
            raise ValueError('cria_prado: argumentos invalidos')
        if obter_pos_x(elemento) >= obter_pos_x(d) or obter_pos_y(elemento) >= obter_pos_y(d):
            raise ValueError('cria_prado: argumentos invalidos')

    return [d, list(r), list(a), list(p)]

def cria_copia_prado(prado):
    '''
    cria_copia_prado: prado -> prado
    Recebe um prado e devolve uma copia desse prado
    '''
    copia = []
    for arg in prado:
        copia += [arg.copy()]
    return copia

def obter_tamanho_x(prado):
    '''
    obter_tamanho_x: prado -> int
    Recebe um prado e devolve o tamanho horizontal desse prado
    '''
    return obter_pos_x(prado[0]) + 1

def obter_tamanho_y(prado):
    '''
    obter_tamanho_y: prado -> int
    Recebe um prado e devolve o tamanho vertical desse prado
    '''
    return obter_pos_y(prado[0]) + 1

def obter_numero_predadores(prado):
    '''
    obter_numero_predadores: prado -> int
    Recebe um prado e devolve o numero de predadores existentes nesse prado
    '''
    num_pred = 0
    for animal in prado[2]:
        if eh_predador(animal):
            num_pred += 1
    return num_pred

def obter_numero_presas(prado):
    '''
    obter_numero_presas: prado -> int
    Recebe um prado e devolve o numero de presas existentes nesse prado
    '''
    num_pres = 0
    for animal in prado[2]:
        if eh_presa(animal):
            num_pres += 1
    return num_pres

def obter_posicao_animais(prado):
    '''
    obter_posicao_animais: prado -> tuplo posicoes
    Recebe um prado e devolve as posicoes dos animais desse prado organizadas seguindo as linhas
    '''
    return ordenar_posicoes(tuple(prado[3]))

def obter_animal(prado, pos):
    '''
    obter_animal: prado × posicao -> animal
    Recebe um prado e uma posicao e devolve o animal desse prado que se encontra na posicao fornecida
    '''
    for index_posicao in range(len(prado[3])):
        if cria_posicao(obter_pos_x(pos), obter_pos_y(pos)) == prado[3][index_posicao]:
            return prado[2][index_posicao]

def eliminar_animal(prado, pos):
    '''
    eliminar_animal: prado × posicao -> prado
    Recebe um prado e uma posicao e devolve o proprio prado sem o animal que se encontrava na posicao fornecida
    '''
    prado[2].remove(obter_animal(prado, pos))
    prado[3].remove(pos)
    return prado

def mover_animal(prado, pos1, pos2):
    '''
    mover_animal: prado × posicao × posicao -> prado
    Recebe um prado e duas posicoes e move o animal que se encontra na primeira posicao para a segunda posicao
    '''
    prado[3].insert(prado[3].index(pos1), pos2)
    prado[3].remove(pos1)
    return prado

def inserir_animal(prado, animal, pos):
    '''
    inserir_animal: prado × animal × posicao -> prado
    Recebe um prado, um animal e uma posicao e adiciona ao prado esse animal na posicao fornecida
    '''
    prado[2].append(animal)
    prado[3].append(pos)
    return prado

def eh_prado(arg):
    '''
    eh_prado: universal -> booleano
    Recebe um argumento e verifica se corresponde a um prado
    '''
    if type(arg) != list or len(arg) != 4 or not eh_posicao(arg[0]):
        return False
    for elemento in arg[1]:
        if not eh_posicao(elemento):
            return False
    for elemento in arg[2]:
        if not eh_animal(elemento):
            return False
    for elemento in arg[3]:
        if not eh_posicao(elemento):
            return False
    return True

def eh_posicao_animal(prado, pos):
    '''
    eh_posicao_animal: prado × posicao -> booleano
    Recebe um prado e uma posicao e verifica se no prado existe um animal na posicao fornecida
    '''
    return cria_posicao(obter_pos_x(pos), obter_pos_y(pos)) in prado[3]

def eh_posicao_obstaculo(prado, pos):
    '''
    eh_posicao_obstaculo: prado × posicao -> booleano
    Recebe um prado e uma posicao e verifica se no prado existe uma montanha ou um rochedo na posicao fornecida
    '''
    if obter_pos_x(pos) == 0 or\
        obter_pos_y(pos) == 0 or\
        obter_pos_x(pos) == obter_tamanho_x(prado) - 1 or\
        obter_pos_y(pos) == obter_tamanho_y(prado) - 1:
        return True
    for posicao in prado[1]:
        if posicao == cria_posicao(obter_pos_x(pos), obter_pos_y(pos)):
            return True
    return False

def eh_posicao_livre(prado, pos):
    '''
    eh_posicao_livre: prado × posicao -> booleano
    Recebe um prado e uma posicao e verifica se no prado a posicao fornecida nao esta ocupada
    '''
    return not eh_posicao_obstaculo(prado, pos) and not eh_posicao_animal(prado, pos)

def prados_iguais(p1, p2):
    '''
    prados_iguais: prado × prado -> booleano
    Recebe dois prados e verifica se correspondem a prados iguais
    '''
    return eh_prado(p1) and eh_prado(p2) and p1 == p2

def prado_para_str(prado):
    '''
    prado_para_str : prado -> str
    Recebe um prado e devolve o prado em forma de string onde se veem os limites do prado, os animais e os rochedos
    '''
    string = '+' + '-' * (obter_tamanho_x(prado) - 2) + '+' + '\n'
    posicoes_animais = []
    for posicao in obter_posicao_animais(prado):
        posicoes_animais += [cria_posicao(obter_pos_x(posicao), obter_pos_y(posicao))]
    posicoes_rochedos = []
    for posicao in prado[1]:
        posicoes_rochedos += [cria_posicao(obter_pos_x(posicao), obter_pos_y(posicao))]
    linha = 1
    while linha < obter_tamanho_y(prado) - 1:
        string += '|'
        espaco = 1
        while espaco < obter_tamanho_x(prado) - 1:
            posicao_control = cria_posicao(espaco, linha)
            if posicao_control in posicoes_rochedos:
                string += '@'
            elif posicao_control in posicoes_animais:
                string += animal_para_char(obter_animal(prado, posicao_control))
            else:
                string += '.'
            espaco += 1
        string += '|' + '\n'
        linha += 1
    string += '+' + '-' * (obter_tamanho_x(prado) - 2) + '+'

    return string

def obter_valor_numerico(prado, pos):
    '''
    obter_valor_numerico: prado × posicao -> int
    Recebe um prado e uma posicao e devolve o numero ao qual corresponde essa posicao
    (os numeros sao lidos por linhas)
    '''
    return obter_tamanho_x(prado) * obter_pos_y(pos) + obter_pos_x(pos)

def obter_movimento(prado, pos):
    '''
    obter_movimento: prado × posicao -> posicao
    Recebe um prado e uma posicao e devolve a posicao seguinte do animal que se encontra na posicao fornecida, segundo as regras de movimento
    '''
    posicoes_sem_obstaculos = []
    for posicao in obter_posicoes_adjacentes(pos):
        if not eh_posicao_obstaculo(prado, posicao):
            posicoes_sem_obstaculos += [posicao]      #lista das posicoes adjacentes sem montanhas ou rochedos
    cima = cria_posicao(obter_pos_x(pos), obter_pos_y(pos) - 1)
    direita = cria_posicao(obter_pos_x(pos) + 1, obter_pos_y(pos))
    baixo = cria_posicao(obter_pos_x(pos), obter_pos_y(pos) + 1)
    esquerda = cria_posicao(obter_pos_x(pos) - 1, obter_pos_y(pos))
    posicoes_possivies = [cima, direita, baixo, esquerda]
    if eh_predador(obter_animal(prado, cria_posicao(obter_pos_x(pos), obter_pos_y(pos)))):  #se o animal for predador
        livres = 0
        presas = 0
        posicao_presas = []
        for posicao in posicoes_sem_obstaculos:
            if eh_posicao_livre(prado, posicao):
                livres += 1
            elif eh_presa(obter_animal(prado, cria_posicao(obter_pos_x(posicao), obter_pos_y(posicao)))):
                presas += 1
                posicao_presas += [posicao]   #lista com as posicoes das presas em volta do predador
        if presas == 0 and livres == 0:
            return pos
        elif presas == 0:    #se nao existirem presas a sua volta o predador segue a regra geral
            if livres == 0:
                return pos
            posicao_escolhida = obter_valor_numerico(prado, pos) % livres
            posicoes_livres = []
            for posicao in posicoes_possivies:
                if eh_posicao_livre(prado, posicao):
                    posicoes_livres += [posicao]
            if posicao_escolhida == 0:
                return posicoes_livres[0]
            elif posicao_escolhida == 1:
                return posicoes_livres[1]
            elif posicao_escolhida == 2:
                return posicoes_livres[2]
            elif posicao_escolhida == 3:
                return posicoes_livres[3]
        elif presas == 1:   #se existir apenas uma presa a sua volta o predador tem preferencia por ela
            return cria_posicao(obter_pos_x(posicao_presas[0]), obter_pos_y(posicao_presas[0]))
        else:   #se existirem varias presas a sua volta o predador segue a regra geral para essas posicoes
            posicao_escolhida = obter_valor_numerico(prado, pos) % presas
            posicoes_presas = []
            for posicao in posicoes_possivies:
                if eh_posicao_livre(prado, posicao):
                    posicoes_presas += [posicao]
            if posicao_escolhida == 0:
                return posicoes_presas[0]
            elif posicao_escolhida == 1:
                return posicoes_presas[1]
            elif posicao_escolhida == 2:
                return posicoes_presas[2]
            elif posicao_escolhida == 3:
                return posicoes_presas[3]
    else:    #se o animal for presa
        p = 0
        for posicao in posicoes_sem_obstaculos:
            if eh_posicao_livre(prado, posicao):
                p += 1
        if p == 0:
            return pos
        posicao_escolhida = obter_valor_numerico(prado, pos) % p
        posicoes_livres = []
        for posicao in posicoes_possivies:
            if eh_posicao_livre(prado, posicao):
                posicoes_livres += [posicao]
        if posicao_escolhida == 0:
            return posicoes_livres[0]
        elif posicao_escolhida == 1:
            return posicoes_livres[1]
        elif posicao_escolhida == 2:
            return posicoes_livres[2]
        elif posicao_escolhida == 3:
            return posicoes_livres[3]




#Funcoes adicionais
def geracao(prado):
    '''
    geracao: prado -> prado
    Recebe um prado e devolve esse prado modificado de acordo com a evolucao correspondente a uma geracao completa
    Cada animal realiza a sua açao seguindo a ordem de leitura do prado
    '''
    posicoes_ordenadas = ordenar_posicoes(obter_posicao_animais(prado))
    animais_mortos = []
    for posicao in posicoes_ordenadas:
        animal = obter_animal(prado, posicao)
        if posicao not in animais_mortos:
            # se for predador
            if eh_predador(animal):
                aumenta_idade(animal)
                aumenta_fome(animal)
                if obter_movimento(prado, posicao) != posicao:   #se o animal se mover
                    if eh_animal_fertil(animal):
                        if eh_animal_faminto(animal):    #se for fertil e faminto
                            if eh_presa(obter_animal(prado, obter_movimento(prado, posicao))):   #se comer uma presa
                                animais_mortos += obter_movimento(prado, posicao)
                                eliminar_animal(prado, obter_movimento(prado, posicao))  #eliminar a presa
                                reset_fome(animal)
                                mover_animal(prado, posicao, obter_movimento(prado, posicao))
                                inserir_animal(prado, reproduz_animal(animal), posicao)   #reproduz
                            else:                                              #se nao comer uma presa
                                mover_animal(prado, posicao, obter_movimento(prado, posicao))
                                inserir_animal(prado, reproduz_animal(animal), posicao)  # reproduz
                                eliminar_animal(prado, obter_movimento(prado, posicao))   #morre
                        elif not eh_animal_faminto(animal):              #se for fertil mas nao for faminto
                            if eh_presa(obter_animal(prado, obter_movimento(prado, posicao))):   #se comer uma presa
                                animais_mortos += obter_movimento(prado, posicao)
                                eliminar_animal(prado, obter_movimento(prado, posicao))     #eliminar a presa
                                reset_fome(animal)
                                mover_animal(prado, posicao, obter_movimento(prado, posicao))
                                inserir_animal(prado, reproduz_animal(animal), posicao)      #reproduz
                            else:                                            #se nao comer uma presa
                                mover_animal(prado, posicao, obter_movimento(prado, posicao))
                                inserir_animal(prado, reproduz_animal(animal), posicao)  # reproduz
                    elif not eh_animal_fertil(animal):
                        if eh_animal_faminto(animal):                    #se nao for fertil mas for faminto
                            if eh_presa(obter_animal(prado, obter_movimento(prado, posicao))):   #se comer uma presa
                                animais_mortos += obter_movimento(prado, posicao)
                                eliminar_animal(prado, obter_movimento(prado, posicao))  #eliminar a presa
                                reset_fome(animal)
                                mover_animal(prado, posicao, obter_movimento(prado, posicao))
                            else:                                            #se nao comer uma presa
                                eliminar_animal(prado, posicao)                      #morre
                        elif not eh_animal_faminto(animal):           #se nao for fertil nem for faminto
                            if eh_presa(obter_animal(prado, obter_movimento(prado, posicao))):   #se comer uma presa
                                animais_mortos += obter_movimento(prado, posicao)
                                eliminar_animal(prado, obter_movimento(prado, posicao))      #eliminar a presa
                                reset_fome(animal)
                                mover_animal(prado, posicao, obter_movimento(prado, posicao))
                            else:
                                mover_animal(prado, posicao, obter_movimento(prado, posicao))
                else:           #se o animal nao se mover
                    if eh_animal_faminto(animal):
                        eliminar_animal(prado, posicao)
            # se for presa
            elif eh_presa(animal):
                aumenta_idade(animal)
                if obter_movimento(prado, posicao) != posicao:      # se o animal se mover
                    if eh_animal_fertil(animal):                 #se for fertil
                        mover_animal(prado, posicao, obter_movimento(prado, posicao))
                        inserir_animal(prado, reproduz_animal(animal), posicao)     #reproduz
                    else:
                        mover_animal(prado, posicao, obter_movimento(prado, posicao))
    return prado

def simula_ecossistema(f, g, v):
    '''
    simula_ecossistema: str × int × booleano -> tuplo
    Recebe uma cadeia de caracteres correspondente a um ficheiro, um valor inteiro (numero de geracoes) e um valor booleano (modo de apresentacao)
    Mostra a evolucao do prado durante o numero de geracoes e devolve um tuplo com o numero de predadores e presas apos esse numero de geracoes
    Dependendo no modo de apresentacao, pode mostrar o prado inicial e o final ou o prado inicial seguido de esse prado apos cada geracao (desde
    que o numero de predadores e presas nao seja igual ao do prado anterior)
    Por cima de cada representacao do prado mostra o numero de predadores e presas dessa geracao e o numero da geracao
    '''
    with open(f, 'r') as file:
        linhas = file.readlines()
    dim = cria_posicao(eval(linhas[0])[0], eval(linhas[0])[1])     #posicao do limite do prado
    obs = []                                                       #posicoes dos rochedos
    for posicao in eval(linhas[1]):
        obs += [cria_posicao(posicao[0], posicao[1])]
    animais = []                                                    #animais do prado
    pos = []                                                       #posicoes dos animais
    for animal in linhas[2:]:
        a = eval(animal)
        animais += [cria_animal(a[0], a[1], a[2])]
        pos += [cria_posicao(a[3][0], a[3][1])]
    prado = cria_prado(dim, obs, animais, pos)     #prado criado com as informacoes do ficheiro
    # modo verboso
    if v:
        print('Predadores:', obter_numero_predadores(prado), 'vs Presas:', obter_numero_presas(prado), '(Gen. 0)')
        print(prado_para_str(prado))
        for gen in range(g):
            predadores = obter_numero_predadores(prado)
            presas = obter_numero_presas(prado)
            geracao(prado)
            #mostrar o prado desde que o numero de predadores e presas se tenha alterado
            if not predadores == obter_numero_predadores(prado) or not presas == obter_numero_presas(prado):
                print('Predadores:', obter_numero_predadores(prado), 'vs Presas:', obter_numero_presas(prado), '(Gen.', str(gen + 1) + ')')
                print(prado_para_str(prado))
    # modo quiet
    else:
        print('Predadores:', obter_numero_predadores(prado), 'vs Presas:', obter_numero_presas(prado), '(Gen. 0)')
        print(prado_para_str(prado))
        for gen in range(g):
            geracao(prado)
        #mostrar o prado apos todas as geracoes
        print('Predadores:', obter_numero_predadores(prado), 'vs Presas:', obter_numero_presas(prado), '(Gen.', str(g) + ')')
        print(prado_para_str(prado))
    return (obter_numero_predadores(prado), obter_numero_presas(prado))