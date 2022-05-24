%-------------------------------------------%
%                                           %
%            MAFALDA FERNANDES              %
%                 102702                    %
%             LEIC-T   21/22                %
%                                           %
%-------------------------------------------%


:- [codigo_comum].


/*----------------------------------------------------------------------------------------------------------------
    2.1 Predicado extrai_ilhas_linha/3

    extrai_ilhas_linha(N_L, Linha, Ilhas)
        N_L -> inteiro positivo correspondente ao numero de uma linha
        Linha -> lista correspondente a uma linha de um puzzle
        Ilhas -> lista ordenada (da esquerda para a direita) cujos elementos sao as ilhas de uma linha

    Extrai as ilhas que se encontram na linha dada
*/

extrai_ilhas_linha(N_L, Linha, Ilhas) :- 
    extrai_ilhas_linha(N_L, Linha, 0, [], Ilhas).

extrai_ilhas_linha(_, [], _, Ilhas, Ilhas).

% se existir uma ilha no lugar em estudo
extrai_ilhas_linha(N_L, [ Cab | Res ], Control, Aux, Ilhas) :-
    Cab =\= 0,
    Coluna is Control + 1,
    append(Aux, [ilha(Cab, (N_L, Coluna))], NovoAux),
    extrai_ilhas_linha(N_L, Res, Coluna, NovoAux, Ilhas).

% se nao existir uma ilha no lugar em estudo
extrai_ilhas_linha(N_L, [ _ | Res ], Control, Aux, Ilhas) :-
    Coluna is Control + 1,
    extrai_ilhas_linha(N_L, Res, Coluna, Aux, Ilhas). 






/*-----------------------------------------------------------------------------------------------------------------------
    2.2 Predicado ilhas/2

    ilhas(Puz, Ilhas)
        Puz -> um puzzle
        Ilhas -> lista ordenada (da esquerda para a direita e de cima para baixo) cujos elementos sao as ilhas do puzzle

    Extrai as ilhas de forma ordenada que se encontram no puzzle dado
*/

ilhas(Puz, Ilhas) :- ilhas(Puz, 0, [], Ilhas).

ilhas([], _, Ilhas, Ilhas).

ilhas([Linha | Resto], X, Aux, Ilhas) :-
    NumLinha is X + 1,
    extrai_ilhas_linha(NumLinha, Linha, IlhasLista),
    append(Aux, IlhasLista, NovoAux),
    ilhas(Resto, NumLinha, NovoAux, Ilhas).




/*------------------------------------------------------------------------------------------------------------------------------
    2.3 Predicado vizinhas/3

    vizinhas(Ilhas, Ilha, Vizinhas)
        Ilhas -> lista de ilhas de um puzzle
        Ilha -> uma ilha do puzzle
        Vizinhas -> lista ordenada das ilhas vizinhas de Ilha

    Devolve uma lista com as ilhas que se encontram em volta da ilha dada
*/

vizinhas(Ilhas, Ilha, Vizinhas) :- vizinhas(Ilhas, Ilha, Vizinhas, [], [], [], [], [], 0).

vizinhas(_, _, Vizinhas, Vizinhas, _, _, _, _, 4).


% ser a ilha em estudo ou estar numa linha e coluna diferentes da ilha em estudo
vizinhas([ilha(_, (XVer, YVer)) | Resto], ilha(_, (XObj, YObj)), Vizinhas, Aux, C, E, D, B, 0) :-
    ((XVer == XObj, YVer == YObj); (XVer =\= XObj, YVer =\= YObj)),
    vizinhas(Resto, ilha(_, (XObj, YObj)), Vizinhas, Aux, C, E, D, B, 0).


% estar na mesma coluna que a ilha em estudo
vizinhas([ilha(PVer, (XVer, YVer)) | Resto], ilha(_, (XObj, YObj)), Vizinhas, Aux, C, E, D, B, 0) :-
    YVer == YObj,
    XVer < XObj, 
    append(C, [ilha(PVer, (XVer, YVer))], NC), 
    vizinhas(Resto, ilha(_, (XObj, YObj)), Vizinhas, Aux, NC, E, D, B, 0).

vizinhas([ilha(PVer, (XVer, YVer)) | Resto], ilha(_, (XObj, YObj)), Vizinhas, Aux, C, E, D, B, 0) :-
    YVer == YObj,
    XVer > XObj, 
    append(B, [ilha(PVer, (XVer, YVer))], NB), 
    vizinhas(Resto, ilha(_, (XObj, YObj)), Vizinhas, Aux, C, E, D, NB, 0).



% estar na mesma linha que a ilha em estudo
vizinhas([ilha(PVer, (XVer, YVer)) | Resto], ilha(_, (XObj, YObj)), Vizinhas, Aux, C, E, D, B, 0) :-
    XVer == XObj,
    YVer < YObj, 
    append(E, [ilha(PVer, (XVer, YVer))], NE),
    vizinhas(Resto, ilha(_, (XObj, YObj)), Vizinhas, Aux, C, NE, D, B, 0).

vizinhas([ilha(PVer, (XVer, YVer)) | Resto], ilha(_, (XObj, YObj)), Vizinhas, Aux, C, E, D, B, 0) :-
    XVer == XObj,
    YVer > YObj, 
    append(D, [ilha(PVer, (XVer, YVer))], ND),
    vizinhas(Resto, ilha(_, (XObj, YObj)), Vizinhas, Aux, C, E, ND, B, 0).



% ir buscar o ultimo elemento da lista C (lista com as ilhas que estao acima da ilha em estudo), que corresponde a ilha mais proxima da ilha em estudo
vizinhas([], _, Vizinhas, Aux, C, E, D, B, 0) :-
    length(C, LenC), 
    LenC > 0, 
    last(C, LastC),
    append(Aux, [LastC], Aux2),
    vizinhas([], _, Vizinhas, Aux2, C, E, D, B, 1).

vizinhas([], _, Vizinhas, Aux, C, E, D, B, 0) :-
    vizinhas([], _, Vizinhas, Aux, C, E, D, B, 1).


% ir buscar o ultimo elemento da lista E (lista com as ilhas que estao a esquerda da ilha em estudo), que corresponde a ilha mais proxima da ilha em estudo
vizinhas([], _, Vizinhas, Aux, C, E, D, B, 1) :-
    length(E, LenE), 
    LenE > 0, 
    last(E, LastE),
    append(Aux, [LastE], Aux2),
    vizinhas([], _, Vizinhas, Aux2, C, E, D, B, 2).

vizinhas([], _, Vizinhas, Aux, C, E, D, B, 1) :-
    vizinhas([], _, Vizinhas, Aux, C, E, D, B, 2).


% ir buscar o primeiro elemento da lista D (lista com as ilhas que estao a direita da ilha em estudo), que corresponde a ilha mais proxima da ilha em estudo
vizinhas([], _, Vizinhas, Aux, C, E, D, B, 2) :-
    length(D, LenD), 
    LenD > 0,
    vizinhas([], _, Vizinhas, Aux, C, E, D, B, 21).

vizinhas([], _, Vizinhas, Aux, C, E, [CabD | _], B, 21) :-
    append(Aux, [CabD], Aux2),
vizinhas([], _, Vizinhas, Aux2, C, E, _, B, 3).

vizinhas([], _, Vizinhas, Aux, C, E, D, B, 2) :-
    vizinhas([], _, Vizinhas, Aux, C, E, D, B, 3).


% ir buscar o primeiro elemento da lista B (lista com as ilhas que estao abaixo da ilha em estudo), que corresponde a ilha mais proxima da ilha em estudo
vizinhas([], _, Vizinhas, Aux, C, E, D, B, 3) :-
    length(B, LenB), 
    LenB > 0,
    vizinhas([], _, Vizinhas, Aux, C, E, D, B, 31).

vizinhas([], _, Vizinhas, Aux, C, E, D, [CabB | _], 31) :-
    append(Aux, [CabB], Aux2),
    vizinhas([], _, Vizinhas, Aux2, C, E, D, _, 4).

vizinhas([], _, Vizinhas, Aux, C, E, D, B, 3) :-
    vizinhas([], _, Vizinhas, Aux, C, E, D, B, 4).







/*----------------------------------------------------------------------------------------------------------------------------------------------------------
    2.4 Predicado estado/2

    estado(Ilhas, Estado)
        Ilhas -> lista de ilhas de um puzzle
        Estado -> lista ordenada das entradas referentes a cada uma das ilhas
        (entrada -> lista cujos elementos sao uma ilha, uma lista com as vizinhas dessa ilha, uma lista com as pontes dessa ilha (inicialmente vazia))

    Devolve uma lista correspondente ao estado de um puzzle
*/

estado(Ilhas, Estado) :- 
    estado(Ilhas, Ilhas, [], Estado, []).

estado([], _, _, Estado, Estado).

estado([ X | Res ], Ilhas, EstIlha, Estado, Aux) :-
    append(EstIlha, [X], EstIlha2),
    vizinhas(Ilhas, X, Vizinhas),
    append(EstIlha2, [Vizinhas], EstIlha3),
    append(EstIlha3, [[]], EstIlha4),
    append(Aux, [EstIlha4], Aux2),
    estado(Res, Ilhas, [], Estado, Aux2).









/*---------------------------------------------------------------------------------------------------------------------------------------
    2.5 Predicado posicoes_entre/3

    posicoes_entre(Pos1, Pos2, Posicoes)
        Pos1 -> posicao
        Pos2 -> posicao
        Posicoes -> lista ordenada das posicoes entre Pos1 e Pos2, excluindo estas
        

    Devolve as posicoes que estao entre duas posicoes dadas
*/

posicoes_entre(Pos1, Pos2, Posicoes) :- posicoes_entre(Pos1, Pos2, 1, 0, [], Posicoes).

posicoes_entre(_, _, 0, _, Posicoes, Posicoes).

% se posicoes dadas nao estarem na ordem certa, trocar as posicoes
posicoes_entre((X1, Y1), (X2, Y2), _, C, Aux, Posicoes) :-
    ((X1 == X2, Y1 > Y2); (Y1 == Y2, X1 > X2)),
    posicoes_entre((X2, Y2), (X1, Y1), 1, C, Aux, Posicoes).

% as posicoes estarem na mesma linha e o contador tiver ultrapassado o limite estabelecido pela segunda posicao
posicoes_entre((X1, Y1), (X2, Y2), _, C, Aux, Posicoes) :-
    X1 == X2,
    NC is C + 1,
    Control is Y1 + NC,
    Control >= Y2,
    posicoes_entre((X1, Y1), (X2, Y2), 0, NC, Aux, Posicoes).

% as posicoes estarem na mesma coluna e o contador tiver ultrapassado o limite estabelecido pela segunda posicao
posicoes_entre((X1, Y1), (X2, Y2), _, C, Aux, Posicoes) :-
    Y1 == Y2,
    NC is C + 1,
    Control is X1 + NC,
    Control >= X2,
    posicoes_entre((X1, Y1), (X2, Y2), 0, NC, Aux, Posicoes).

% as posicoes estarem na mesma linha e o contador nao tiver ultrapassado o limite estabelecido pela segunda posicao
posicoes_entre((X1, Y1), (X2, Y2), _, C, Aux, Posicoes) :-
    X1 == X2,
    NC is C + 1,
    Control is Y1 + NC,
    Control < Y2,
    append(Aux, [(X1, Control)], NovoAux),
    posicoes_entre((X1, Y1), (X2, Y2), 1, NC, NovoAux, Posicoes).

% as posicoes estarem na mesma coluna e o contador nao tiver ultrapassado o limite estabelecido pela segunda posicao
posicoes_entre((X1, Y1), (X2, Y2), _, C, Aux, Posicoes) :-
    Y1 == Y2,
    NC is C + 1,
    Control is X1 + NC,
    Control < X2,
    append(Aux, [(Control, Y1)], NovoAux),
    posicoes_entre((X1, Y1), (X2, Y2), 1, NC, NovoAux, Posicoes).





/*---------------------------------------------------------------------------------------------------------------------------------------
    2.6 Predicado cria_ponte/3

    cria_ponte(Pos1, Pos2, Ponte)
        Pos1 -> posicao
        Pos2 -> posicao
        Ponte -> ponte entre Pos1 e Pos2
        

    Devolve uma ponte entre as duas posicoes dadas
*/

cria_ponte(Pos1, Pos2, Ponte) :- cria_ponte(Pos1, Pos2, 0, _, Ponte).

cria_ponte(_, _, 1, Ponte, Ponte).

% se posicoes dadas nao estarem na ordem certa, trocar as posicoes
cria_ponte((X1, Y1), (X2, Y2), Control, _, Ponte) :-
    ((X1 == X2, Y1 > Y2); (Y1 == Y2, X1 > X2)),
    cria_ponte((X2, Y2), (X1, Y1), Control, _, Ponte).

cria_ponte(Pos1, Pos2, Control, _, Ponte) :-
    Final is Control + 1,
    cria_ponte(Pos1, Pos2, Final, ponte(Pos1, Pos2), Ponte).






/*---------------------------------------------------------------------------------------------------------------------------------------
    2.7 Predicado caminho_livre/5

    caminho_livre(Pos1, Pos2, Posicoes, I, Vz)
        Pos1 -> posicao
        Pos2 -> posicao
        Posicoes -> lista ordenada das posicoes entre Pos1 e Pos2
        I -> ilha
        Vz -> uma das vizinhas da ilha I
        

    Verifica se a adicao da ponte entre as duas posicoes dadas nao faz com que as ilhas deixem de ser vizinhas
*/

caminho_livre(Pos1, Pos2, Posicoes, I, Vz) :- caminho_livre(Pos1, Pos2, Posicoes, I, Vz, 0, _).

caminho_livre(_, _, _, _, _, 1, []).

% se as posicoes dadas corresponderem as posicoes da ilha e da sua vizinha
caminho_livre(Pos1, Pos2, _, ilha(_, PosI), ilha(_, PosVz), 0, _) :-
    (Pos1 == PosI, Pos2 == PosVz);
    (Pos1 == PosVz, Pos2 == PosI).

% cria uma lista com as posicoes que estao entre a ilha e a sua vizinha
caminho_livre(Pos1, Pos2, Posicoes, ilha(_, PosI), ilha(_, PosVz), 0, _) :-
    posicoes_entre(PosI, PosVz, Posicoes2), !,
    caminho_livre(Pos1, Pos2, Posicoes, ilha(_, PosI), ilha(_, PosVz), 1, Posicoes2).

% se uma dessas posicoes corresponder a uma posicao onde se encontra a ponte, o caminho deixa imediatamente de estar livre
caminho_livre(_, _, Posicoes, _, _, 1, [X | _]) :-
    member(X, Posicoes), !, fail.

caminho_livre(Pos1, Pos2, Posicoes, I, Vz, 1, [_ | Res]) :-
    caminho_livre(Pos1, Pos2, Posicoes, I, Vz, 1, Res).




/*----------------------------------------------------------------------------------------------------------------------------------------------------
    2.8 Predicado actualiza_vizinhas_entrada/5

    actualiza_vizinhas_entrada(Pos1, Pos2, Posicoes, Entrada, Nova_Entrada)
        Pos1 -> posicao
        Pos2 -> posicao
        Posicoes -> lista ordenada das posicoes entre Pos1 e Pos2
        Entrada -> entrada do puzzle
        Nova_Entrada -> atualizacao de Entrada depois de serem removidas as ilhas da lista de vizinhas, que deixaram de o ser apos a adicao de pontes
        

    Devolve uma entrada do puzzle atualizada apos a adicao de pontes
*/

actualiza_vizinhas_entrada(Pos1, Pos2, Posicoes, Entrada, Nova_Entrada) :-
    actualiza_vizinhas_entrada(Pos1, Pos2, Posicoes, Entrada, Nova_Entrada, [_, [], _]).

actualiza_vizinhas_entrada(_, _, _, [_, [], _], Nova_Entrada, Nova_Entrada).

% se o caminho estiver livre, as ilhas em estudo continuam a ser vizinhas
actualiza_vizinhas_entrada(Pos1, Pos2, Posicoes, [Ilha, [Vz | Resto], Pontes], Nova_Entrada, [Ilha, Vizinhas, Pontes]) :-
    caminho_livre(Pos1, Pos2, Posicoes, Ilha, Vz),
    append(Vizinhas, [Vz], Vizinhas2),
    actualiza_vizinhas_entrada(Pos1, Pos2, Posicoes, [Ilha, Resto, Pontes], Nova_Entrada, [Ilha, Vizinhas2, Pontes]).


actualiza_vizinhas_entrada(Pos1, Pos2, Posicoes, [Ilha, [_ | Resto], Pontes], Nova_Entrada, [Ilha, Vizinhas, Pontes]) :-
    actualiza_vizinhas_entrada(Pos1, Pos2, Posicoes, [Ilha, Resto, Pontes], Nova_Entrada, [Ilha, Vizinhas, Pontes]).






/*----------------------------------------------------------------------------------------------------------------------------------------------------
    2.9 Predicado actualiza_vizinhas_apos_pontes/4

    actualiza_vizinhas_apos_pontes(Estado, Pos1, Pos2, Novo_estado)
        Estado -> estado do puzzle
        Pos1 -> posicao
        Pos2 -> posicao
        Novo_estado -> estado que se obtem de Estado apos a atualizacao das ilhas vizinhas em cada uma das suas entradas
        

    Devolve um estado do puzzle atualizada apos a adicao de pontes
*/

actualiza_vizinhas_apos_pontes(Estado, Pos1, Pos2, Novo_estado) :- 
    actualiza_vizinhas_apos_pontes(Estado, Pos1, Pos2, Novo_estado, []).

actualiza_vizinhas_apos_pontes([], _, _, Novo_estado, Novo_estado).

actualiza_vizinhas_apos_pontes([Entrada | Resto], Pos1, Pos2, Novo_estado, Aux) :-
    posicoes_entre(Pos1, Pos2, Posicoes),
    actualiza_vizinhas_entrada(Pos1, Pos2, Posicoes, Entrada, Nova_Entrada),
    append(Aux, [Nova_Entrada], Aux2),
    actualiza_vizinhas_apos_pontes(Resto, Pos1, Pos2, Novo_estado, Aux2).




/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    2.10 Predicado ilhas_terminadas/2

    ilhas_terminadas(Estado, Ilhas_term)
        Estado -> estado do puzzle
        Ilhas_term -> lista das pontes que ja tem todas as pontes associadas
        (uma ilha de entrada   [ilha(N_pontes, Pos), Vizinhas, Pontes]   esta terminada se N_pontes for diferente de 'X' e o comprimento da lista Pontes for N_pontes)
        

    Devolve as ilhas de uma entrada que estao terminadas
*/

ilhas_terminadas(Estado, Ilhas_term) :-
    ilhas_terminadas(Estado, Ilhas_term, []).

ilhas_terminadas([], Ilhas_term, Ilhas_term).

% se as condicoes acima descritas se verificarem, a ilha esta terminada
ilhas_terminadas([[ilha(NumPontes, Pos), _, ListaPontes] | Resto], Ilhas_term, Aux) :-
    NumPontes \== 'X',
    length(ListaPontes, LenLP),
    LenLP == NumPontes,
    append(Aux, [ilha(NumPontes, Pos)], Aux2),
    ilhas_terminadas(Resto, Ilhas_term, Aux2).

ilhas_terminadas([_ | Resto], Ilhas_term, Aux) :-
    ilhas_terminadas(Resto, Ilhas_term, Aux).




/*--------------------------------------------------------------------------------------------------------------------------------------
    2.11 Predicado tira_ilhas_terminadas_entrada/3

    tira_ilhas_terminadas_entrada(Ilhas_term, Entrada, Nova_entrada)
        Ilhas_term -> lista das pontes que ja tem todas as pontes associadas
        Entrada -> entrada do puzzle
        Nova_entrada -> entrada resultante de remover as ilhas terminadas da lista de ilhas vizinhas de Entrada
        
        
    Devolve uma entrada atualizada depois de remover as ilhas terminadas das vizinhas da entrada dada
*/

tira_ilhas_terminadas_entrada(Ilhas_term, Entrada, Nova_entrada) :-
    tira_ilhas_terminadas_entrada(Ilhas_term, Entrada, Nova_entrada, [], [], 1).

tira_ilhas_terminadas_entrada(_, _, Nova_entrada, Nova_entrada, _, 0).

% apos ter verificado as vizinhas todas, devolver a entrada final
tira_ilhas_terminadas_entrada(_, [Ilha, [], Pontes], Nova_entrada, Aux, LVizinhas, 1) :-
    append(Aux, [Ilha, LVizinhas, Pontes], Aux2),
    tira_ilhas_terminadas_entrada(_, _, Nova_entrada, Aux2, _, 0).

% se a vizinha em estudo estiver terminada, ir verificar o resto das vizinhas
tira_ilhas_terminadas_entrada(Ilhas_term, [Ilha, [Vizinha | Resto], Pontes], Nova_entrada, Aux, LVizinhas, 1) :-
    member(Vizinha, Ilhas_term),
    tira_ilhas_terminadas_entrada(Ilhas_term, [Ilha, Resto, Pontes], Nova_entrada, Aux, LVizinhas, 1).

% se a vizinha em estudo nao estiver terminada, guarda-la e ir verificar as outras
tira_ilhas_terminadas_entrada(Ilhas_term, [Ilha, [Vizinha | Resto], Pontes], Nova_entrada, Aux, LVizinhas, 1) :-
    append(LVizinhas, [Vizinha], LVizinhas2),
    tira_ilhas_terminadas_entrada(Ilhas_term, [Ilha, Resto, Pontes], Nova_entrada, Aux, LVizinhas2, 1).





/*--------------------------------------------------------------------------------------------------------------------------------------
    2.12 Predicado tira_ilhas_terminadas/3

    tira_ilhas_terminadas(Estado, Ilhas_term, Novo_estado)
        Estado -> estado de um puzzle
        Ilhas_term -> lista das pontes que ja tem todas as pontes associadas
        Novo_estado -> estado resultante da atualizacao de todas as entradas de Estado
        
        
    Devolve um estado atualizado depois de atualizar todas as entradas do estado inicial dado
*/

tira_ilhas_terminadas(Estado, Ilhas_term, Novo_estado) :-
    tira_ilhas_terminadas(Estado, Ilhas_term, Novo_estado, []).

tira_ilhas_terminadas([], _, Novo_estado, Novo_estado).

tira_ilhas_terminadas([Entrada | Resto], Ilhas_term, Novo_estado, Aux) :-
    tira_ilhas_terminadas_entrada(Ilhas_term, Entrada, Nova_entrada),
    append(Aux, [Nova_entrada], Aux2),
    tira_ilhas_terminadas(Resto, Ilhas_term, Novo_estado, Aux2).




/*--------------------------------------------------------------------------------------------------------------------------------------
    2.13 Predicado marca_ilhas_terminadas_entrada/3

    marca_ilhas_terminadas_entrada(Ilhas_term, Entrada, Nova_entrada)
        Ilhas_term -> lista das pontes que ja tem todas as pontes associadas
        Entrada -> entrada de um puzzle
        Nova_entrada -> atualizacao de Entrada apos substituir o numero de pontes de uma ilha por 'X' se esta pertencer a Ilhas_term
        
        
    Devolve uma entrada atualizada apos marcar as ilhas da entrada inicial dada que estao terminadas
*/

marca_ilhas_terminadas_entrada(Ilhas_term, Entrada, Nova_entrada) :-
    marca_ilhas_terminadas_entrada(Ilhas_term, Entrada, Nova_entrada, _, 1).

marca_ilhas_terminadas_entrada(_, _, Nova_entrada, Nova_entrada, 0).

% se a ilha da entrada estiver na lista de ilhas terminadas, marca-la com um 'X'
marca_ilhas_terminadas_entrada(Ilhas_term, [ilha(Ponte, Pos), Vizinhas, Pontes], Nova_entrada, _, 1) :-
    member(ilha(Ponte, Pos), Ilhas_term),
    marca_ilhas_terminadas_entrada(_, _, Nova_entrada, [ilha('X', Pos), Vizinhas, Pontes], 0).

marca_ilhas_terminadas_entrada(_, Entrada, Nova_entrada, _, 1) :-
    marca_ilhas_terminadas_entrada(_, Entrada, Nova_entrada, Entrada, 0).




/*--------------------------------------------------------------------------------------------------------------------------------------
    2.14 Predicado marca_ilhas_terminadas/3

    marca_ilhas_terminadas(Estado, Ilhas_term, Novo_estado)
        Estado -> estado de um puzzle
        Ilhas_term -> lista das pontes que ja tem todas as pontes associadas
        Novo_estado -> estado resultante da atualizacao de todas as entradas de Estado, apos marcar todas as ilhas terminadas
        
        
    Devolve um estado atualizado com todas as ilhas terminadas marcadas com um 'X'
*/

marca_ilhas_terminadas(Estado, Ilhas_term, Novo_estado) :-
    marca_ilhas_terminadas(Estado, Ilhas_term, Novo_estado, []).

marca_ilhas_terminadas([], _, Novo_estado, Novo_estado).

marca_ilhas_terminadas([Entrada | Resto], Ilhas_term, Novo_estado, Aux) :-
    marca_ilhas_terminadas_entrada(Ilhas_term, Entrada, Nova_entrada),
    append(Aux, [Nova_entrada], Aux2),
    marca_ilhas_terminadas(Resto, Ilhas_term, Novo_estado, Aux2).



/*--------------------------------------------------------------------------------------------------------------------------------------
    2.15 Predicado trata_ilhas_terminadas/2

    trata_ilhas_terminadas(Estado, Novo_estado)
        Estado -> estado de um puzzle
        Novo_estado -> estado resultante de aplicar os predicados  tira_ilhas_terminadas  e  marca_ilhas_terminadas  a Estado
        
        
    Devolve um estado atualizado sem ilhas terminadas na lista de vizinhas de cada entrada e com todas as ilhas terminadas marcadas com um 'X'
*/

trata_ilhas_terminadas(Estado, Novo_estado) :-
    trata_ilhas_terminadas(Estado, Novo_estado, _, 1).

trata_ilhas_terminadas(_, Novo_estado, Novo_estado, 0).

trata_ilhas_terminadas(Estado, Novo_estado, _, 1) :-
    ilhas_terminadas(Estado, Ilhas_term),
    tira_ilhas_terminadas(Estado, Ilhas_term, EstadoSemIlhasTerm),
    marca_ilhas_terminadas(EstadoSemIlhasTerm, Ilhas_term, EstadoFinal),
    trata_ilhas_terminadas(Estado, Novo_estado, EstadoFinal, 0).





/*------------------------------------------------------------------------------------------------------------------------------------------------------------
    2.16 Predicado junta_pontes/5

    junta_pontes(Estado, Num_pontes, Ilha1, Ilha2, Novo_estado)
        Estado -> estado de um puzzle
        Ilha1 -> ilha
        Ilha2 -> ilha
        Novo_estado -> estado resultante de adicionar as devidas pontes entre Ilha1 e Ilha2 e tudo o que adicao implica
        (criacao das pontes, adicao das pontes as respetivas entradas, atualizacao das vizinhas de todas as ilhas do estado e marcacao das ilhas terminadas)
        
        
    Devolve um estado atualizado apos a adicao das pontes entres duas ilhas e de tudo o que isso implica
*/

junta_pontes(Estado, Num_pontes, Ilha1, Ilha2, Novo_estado) :-
    junta_pontes(Estado, Num_pontes, 0, Ilha1, Ilha2, Novo_estado, [], _, 1).

junta_pontes(_, _, _, _, _, Novo_estado, Novo_estado, _, 5).

% criacao da ponte entre as ilhas
junta_pontes(Estado, Num_pontes, 0, ilha(P1, Pos1), ilha(P2, Pos2), Novo_estado, Aux, _, 1) :-
    cria_ponte(Pos1, Pos2, PonteEntreIlhas),
    junta_pontes(Estado, Num_pontes, 0, ilha(P1, Pos1), ilha(P2, Pos2), Novo_estado, Aux, PonteEntreIlhas, 2).

% iterar pelo estado ate encontrar a primeria ilha dada para a modificar
junta_pontes([[Ilha, Vizinhas, Pontes] | Resto], Num_pontes, 0, Ilha1, Ilha2, Novo_estado, Aux, PonteEntreIlhas, 2) :-
    Ilha \== Ilha1,
    append(Aux, [[Ilha, Vizinhas, Pontes]], Aux2),
    junta_pontes(Resto, Num_pontes, 0, Ilha1, Ilha2, Novo_estado, Aux2, PonteEntreIlhas, 2).

    
/* quando encontrada, verificar se o numero de pontes adicionadas a lista de pontes dessa ilha corresponde 
ao numero de pontes que a ilha deve ter e, se nao, continuar a adicionar as pontes ate atingir esse numero*/
junta_pontes([[Ilha, Vizinhas, Pontes] | Resto], Num_pontes, X, Ilha1, Ilha2, Novo_estado, Aux, PonteEntreIlhas, 2) :-
    Ilha == Ilha1, !,
    NX is X + 1,
    ((NX == Num_pontes, 
    append(Pontes, [PonteEntreIlhas], Pontes2),
    append(Aux, [[Ilha, Vizinhas, Pontes2]], Aux2),
    junta_pontes(Resto, Num_pontes, 0, Ilha1, Ilha2, Novo_estado, Aux2, PonteEntreIlhas, 3));
    (NX =\= Num_pontes,
    append(Pontes, [PonteEntreIlhas], Pontes2),
    junta_pontes([[Ilha, Vizinhas, Pontes2] | Resto], Num_pontes, NX, Ilha1, Ilha2, Novo_estado, Aux, PonteEntreIlhas, 2))).


% iterar pelo estado ate encontrar a segunda ilha dada para a modificar
junta_pontes([[Ilha, Vizinhas, Pontes] | Resto], Num_pontes, X, Ilha1, Ilha2, Novo_estado, Aux, PonteEntreIlhas, 3) :-
    Ilha \== Ilha2,
    append(Aux, [[Ilha, Vizinhas, Pontes]], Aux2),
    junta_pontes(Resto, Num_pontes, X, Ilha1, Ilha2, Novo_estado, Aux2, PonteEntreIlhas, 3).


/* quando encontrada, verificar se o numero de pontes adicionadas a lista de pontes dessa ilha corresponde 
ao numero de pontes que a ilha deve ter e, se nao, continuar a adicionar as pontes ate atingir esse numero*/
junta_pontes([[Ilha, Vizinhas, Pontes] | Resto], Num_pontes, X, Ilha1, Ilha2, Novo_estado, Aux, PonteEntreIlhas, 3) :-
    Ilha == Ilha2,
    NX is X + 1,
    ((NX == Num_pontes, 
    append(Pontes, [PonteEntreIlhas], Pontes2),
    append(Aux, [[Ilha, Vizinhas, Pontes2]], Aux2),
    append(Aux2, Resto, Aux3),
    junta_pontes(_, Num_pontes, X, Ilha1, Ilha2, Novo_estado, Aux3, PonteEntreIlhas, 4));
    (NX =\= Num_pontes,
    append(Pontes, [PonteEntreIlhas], Pontes2),
    junta_pontes([[Ilha, Vizinhas, Pontes2] | Resto], Num_pontes, NX, Ilha1, Ilha2, Novo_estado, Aux, PonteEntreIlhas, 3))).


% marcar todas as ilhas do estado que sejam ilhas terminadas
junta_pontes(_, _, _, ilha(_, Pos1), ilha(_, Pos2), Novo_estado, Aux, _, 4) :-
    actualiza_vizinhas_apos_pontes(Aux, Pos1, Pos2, Novo_estado_aux),
    trata_ilhas_terminadas(Novo_estado_aux, Novo_estado_aux2),
    junta_pontes(_, _, _, _, _, Novo_estado, Novo_estado_aux2, _, 5).





% FIM :)