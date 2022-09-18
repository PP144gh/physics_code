<<<<<<< HEAD
eufito
oi

Hardware eventually fails. Software eventually works. And fail, we shall.
Pilada na testa

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


Créditos a Pedro Pereira por versão base (plotmaker)
=======
Instrucoes

adicionar files:
git add x.filetype
git commit -m "message"
git push
 
adicionar folder:
cd folder
git init
git remote add origin https://gitlab.com/pedro14p/LFEA.git
git add .
git commit -am "message"
git push -u origin master


editar um file:
git commit -am "message"
git push

fazer up:
git pull
>>>>>>> 1f6503373f533fa6d28e07aa83c7c9f3b3363de2
