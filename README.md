Player é triangulo arco-íris.
Tecla R -> inverte a sua direção.
Seta esquerda diminui -> a sua velocidade.
Seta direita aumenta -> a sua velocidade.
Seta de cima e baixo muda -> a seleção da próxima curva do player, apenas após está ser randomizada quando o player completar metade da curva.
Espaço -> pausa o movimento para todos os triangulos.
'G' -> Remove todos os triangulos e se pressionado novamente Randomiza novos triangulos.
Quantidade de triangulos determinada pela var enemyNumber.

Caso não haja um arquivo de txt descrevendo a pista a ser construida o programa inicia no modo editor.
'G' também coloca programa no modo editor.

Comandos do modo editor
Clique botão esquerdo do mouse -> Cria um ponto na coordenada do mouse e o adiciona a o buffer de pontos (Array de 3 posições) na próxima posição livre.
'B' -> Constroi uma curva Bezier apartir dos pontos no Buffer de pontos, a ordem em que os pontos foram adicionados ao buffer influência no desenho da curva. Ultimo ponto do buffer será automaticamente posicionado como buffer primeiro ponto do buffer 
da proxima curva.
'Z' -> Destroi ultima Bezier criada.
'R' -> Remove ultimo ponto posicionado.
'S' -> Posiciona um ponto que proporcione continuidade de derivada para a proxima curva. Só pode ser feito logo após a criação de uma curva.
'C' -> Limpa o buffer de pontos.

Seleção de pontos
    Ao pressionar a seta de cima durante o modo editor entra-se no modo seleção de pontos.
    Selecione um ponto ja posicionado para adicionar novamente ao buffer.
    O ponto a ser selecionado será roxo, pressione teclas esquerda/direita para alterar a seleção.
    Pressione espaço para adicionar o ponto selecionado ao buffer.
    Pressione a seta de cima para sair do modo de seleção de pontos.

Binding de Bezier
    Para conectar quaisquer duas Curvas Bezier pressione a seta de baixo para entrar no modo de Binding
    Durante o modo binding a curva a ser selecionada se tornará roxa, pressione teclas esquerda/direita para alterar a seleção.
    Pressionando espaço irá tornar a curva amarela, indicando que está foi selecionada como curva de saida.
    Pressionando espaço novamente sobre qualquer curva a tornara a curva de entrada.
    Agora estas duas curvas estarão conectadas, de maneira que um triangulo pode transicionar de uma para outra, em qualquer sentido. 
    Detalhe, as curvas não precisam ser adjacentes.

Criação de um arquivo modelo.
Os arquivos modelos de pistas seguem a seguinte estrutura

Número inteiro -> indica a quantidade de pontos
-- Pontos listados no formato (float x) (float y). Um por linha.
Número inteiro -> indica a quantidade de curvas
-- Curvas listadas no formato (int ponto 1) (int ponto 2) (int ponto 3). Uma por linha.
Número inteiro -> indica a quantidade de binds
-- Binds listadas no formato (int bzSaida) (int bzEntrada). Uma por linha.