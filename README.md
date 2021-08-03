# Algorítmo Evolutivo IEEEOpen

A IEEEOpen é uma competição de robótica que ocorre anualmente, mudando de desafio a cada dois anos.

Para o ano de 2021, a competição propõe o desenvolvimento de um robô para automatização de uma loja.

Basicamente, o cenário contém um grid dado por uma matrix 6x7 conectado a uma linha 1x7 que é colorida. As cores desta são: verde, azul, amarelo, vermelho, amarelo, azul e verde, respectivamente. Ademais, há uma estante no outro extremo do ambiente.

Segundo o edital, o cenário pode possuir até 32 blocos coloridos dispostos aleatoriamente sobre o grid. A cor destes pode ser preto, branco (nestes casos acompanhada de um número), ou uma das citadas anteriormente.

No dia da competição, os organizadores fornecerão uma disposoição inicial de blocos. A proposta é que o robô desenvolvido pela equipe seja capaz de identificar o posicionamento de cada e bloco, sua respectiva cor e, caso se aplique, seu número. Ademais, este deve ser capaz de coletar os blocos e entregá-los na posição estipulada.

Os blocos pretos e brancos devem ser entregues nas prateleiras, enquanto os coloridos devem ser levados a um quadrante que contenha sua cor.


Contextualizado o molde da competição, a equipe trabalhou para desenvolver um agoritmo capaz de descobrir qual é a melhor sequência de blocos a ser entregue. A estratégia adotada leva em conta todo o conteúdo apresentado durante a disciplina de Algoritmos Evolutivos.

O programa desenvolvido faz uso de dois AGs, um responsável por cuidar da sequência de blocos a serem entregues, enquanto o outro cuida da sequência de ações que serão tomadas (coletas ou entregas).
