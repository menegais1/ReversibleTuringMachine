Integrantes do grupo: Roberto Menegais, Henrique Rodrigues, Thiago Pavin

Linguagem: C++

Observaçoes:

O arquivo de entrada contém uma transição final que deixa a HEAD da TAPE de INPUT deslocada DUAS casas a direita do último elemento de INPUT.
Isso foi modificado de forma que a HEAD fique UMA casa a direita do último elemento.
Além disso, não é possível utilizar PARENTESES no ALFABETO da PILHA ou do INPUT, devido ao formato do arquivo com parenteses. O ideal seria que os valores fossem separados por espaço
ou vírgula.

No artigo LOGICAL REVERSIBILITY OF COMPUTATION, a HEAD da MT deve ficar posicionada no começo da TAPE de INPUT ao final do estágio de COMPUTE, o exemplo fornecido não garante isso,
portanto, foi tratado no programa para que somente exemplos onde o HEAD esteja posicionado uma casa a DIREITA do último elemento de INPUT sejam aceitos.

Para compilar o programa, é necessário ter o GCC ou MINGW instalado na máquina, é possível compilar com o seguinte comando:

g++ *.cpp -o output

Após isso, basta roda-lo com o seguinte comando:

./output < entrada.txt
