TRABALHO 1 - Inteligência Computacional e Artificial
Prof. Igor Machado Coelho - IME/UERJ

Formem grupos da seguinte forma:
- Graduação: até 3 membros
- Mestrado: até 2 membros
- Doutorado: somente 1 membro

Podem escolher QUALQUER linguagem de programação, e a entrega será um relatório explicativo dos desafios e resultados encontrados, bem como o código-fonte da proposta. Enfatizem bem:
- descrição do problema abordado (expliquem com suas palavras o problema)
- descrição da representação adotada
- número de soluções representadas no espaço amostral
- criem 10 instâncias de teste com tamanhos variados, de acordo com a especificação passada no exemplo (use isso no relatório, qual o melhor valor encontrado para cada instância, e qual tempo computacional)
- algoritmo para versão de minimização (se for metaheurística, explicar parâmetros adotados)
- algoritmo para versão de maximização se for metaheurística, explicar parâmetros adotados)
- 30 experimentos com essa matriz de testes, apresentando os seguintes valores encontrados: menor, maior, média, desvio padrão, mediana.
- apresentar também média de tempo computacional das 30 execuções (é esperado que o algoritmo execute por alguns segundos ou minutos, em cada execução... não faça instâncias muito menores ou muito maiores do que isso, para não dificultar as comparações)


P2) Point Subset
Dada uma matriz inteira NxN, representando a “distância” entre elementos, faça um algoritmo que encontre a distância Mínima e a Máxima (Minimização e Maximização), entre o primeiro e o último elemento da matriz (elemento 0 e elemento N-1).

Exemplo:
3
0 8 7
0 0 -6
0 0 0
Solução: 
Minimização -> S: 0 1 2 -> f(S) = 8 - 6 = 2
Maximização: -> S: 0 2 -> f(S) = 7

Veja o exemplo em anexo: berlin52.mtx
