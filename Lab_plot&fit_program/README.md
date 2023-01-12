Work done in Laboratory classes. Contains a program (done in C++ with CERN's ROOT libraries) that performs plots, histograms or fits of the experimental data. The development of this program was essential since we needed a high degree of personalisation in our plots. My group had the best grade in the class.




HOWTO



Hardware eventually fails. Software eventually works. And fail, we shall.

1. Introdução

Este programa faz ajustes de funções de 1 variável (até agora) a conjuntos de dados e os gráficos correspondentes. Deve ser fornecido um ficheiro com os detalhes do ajuste organizados da forma descrita adiante e um outro com o conjunto de dados.


2. Funcionamento

fitter.C:
para compilar basta escrever make
para executar escrever ./fitter.exe detalhes.txt dados.txt

main.C:
para compilar basta escrever make
para executar escrever ./main.exe param.txt dados.txt


2.1. fitter

2.2. detalhes do ajuste

Opções possíveis: fit, grafico, histograma

Ordem do ficheiro:

opcao:<acção que se quer executar>
titulo:<Título;nome das abcissas;nome das ordenadas>
func:<função a ajustar(parâmetros devem estar na forma [0],[1],etc)>
xmin:<valor mínimo das abcissas>
xmax:<valor máximo das abcissas>
ymin:<valor mínimo das ordenadas>
ymax:<valor máximo das ordenadas>

2.3. dados


3. Outros


