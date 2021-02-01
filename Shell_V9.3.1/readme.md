# SHELL

## Português
------- Considerações iniciais -----------

-> Para setar o valor para uma variavel é necessário 
o comando set e o operador =, como por exemplo
	set a = 5 //a <- 5

-> Para concatenar uma string não é necessário nenhum
operador especial, bastando escrever a variavel ou palavra 
seguida do valor que se quer concatenar, por exemplo:
	set a = 5
	set b = $a$aVariavelb // b <- 55Variavelb

-> Para inserir espaços ou caracteres especiais, utilizar
o operador especial < palavra com espaço ou caracter especial>
, o operador é <>, por exemplo
	set a = /home/<"Área de Trabalho">
	a <- /home/"Área de Trabalho"

-> Para vizualizar uma especie de help basta digitar h ou H.


------- Funções --------------------------

-> Tratar string: Recebi uma string como parametro e a percorri
procurando por separadores, definidos, como espaços, $, <>, =, e retorna
uma lista que contém as substrings, por exemplo:
	comando = "set a = 5"
	tratarString(comando)
	set -> a -> = -> 5
Por essa função retirar os espaços e caracteres especiais foi definido
o operador especial <>.



-> Operador$(listaComando, listaObjs): Recebi como parametros a lista de comandos
já separados pela função tratarString(comando), e a lista de variaveis, basicamente
percorri a string que até então está no inicio da lista procurando por ela na lista 
de variaveis até encontrar um valor que ali exista e o resto da string é então concatenado
com a anterior, se não existir nenhuma variavel com aquele nome, é retornado um erro, exemplo:
	set a = 5
	echo $avarA
	Na saída teremos
	>> 5varA


-> set (listaComando, listaObjs): Recebi como parametros a lista de comandos já separada
e a lista de variaveis, onde tem como objetivo atualizar o valor de uma variavel ou criar uma
nova variavel que será colocada na lista, retornando um objeto do tipo comando, o set é divido 
em variavel comando de atribuição valor da variavel, por exemplo
	set a = 5
	Na saída teremos
	>> key: a | valor: 5


-> path(listaObjs): Recebi como parametro a lista e realiza a busca da variavel path já que
a mesma contém o endereço do que será executado, tenta criar um filho se o filho for criado
na saída são impressos o id do mesmo e o caminho é executado se possivel, se não for possivel criar
o filho é impresso um erro na tela.


-> echo (listaObjs, listaComandos): Recebi como parametro a lista de variaveis e a lista de 
comandos, tem como retorno uma string contendo o que deseja-se imprimir na tela, como conteudo
de variaveis mensagens, etc. Se for o conteudo de uma variavel a mesma é buscada na lista
de variaveis se ela não existir é retornado um erro, se não for para imprimir o valor de uma
variavel é impresso o conteudo presente na lista naquela posição, por exemplo.
	set a = 5
	echo $aValorDeA$a
	>>5ValorDeA5
  
  ## English
  ------- Initial considerations -----------

-> To define the value for a variable it is necessary
the command set and the = operator, such as
set a = 5 // a <- 5

-> To concatenate a string, no
special operator, just write the variable or word
followed by the value to be concatenated, for example:
set a = 5
set b = $ a $ aVariavelb // b <- 55Variavelb

-> To insert spaces or special characters, use
the special operator <word with space or special character>
, the operator is <>, for example
set a = / home / <"Desktop">
a <- / home / "Desktop"

-> To view a help type just type h or H.


------- Functions --------------------------

-> Treat string: I received a string as a parameter and traversed it
looking for defined separators, such as spaces, $, <>, =, and returns
a list that contains as substrings, for example:
command = "set to = 5"
treatingString (command)
set -> a -> = -> 5
This function removes spaces and special characters.
the special operator <>.



-> Operator $ (commandList, listObjs): I received the list of commands as parameters
already separated by the treatmentString function (command), and a list of variables, basically
scrolled through a string that was at the beginning of the list looking for it in the list
of variables until you find a value that exists there and the rest of the string is then concatenated
with the previous one, if there is no variable with that name, an error is returned, example:
set a = 5
echo $ avarA
At the exit we will have
>> 5varA


-> set (commandList, listObjs): I received the list of commands already separated as parameters
and the list of variables, where it aims to update the value of a variable or create a
new variable that will be placed in the list, returning a command type object, the set is divided
in variable exercise command variable value, for example
set a = 5
At the exit we will have
>> key: a | value: 5


-> path (listaObjs): I received the list as a parameter and performs a search of the path variable since
the same address as the one to be obtained, try to raise a child if the child is created
at the output, its id is printed and the path is taken if possible, if not possible to create
the child is printed an error on the screen.


-> echo (ListObjs, listCommands): I received as parameter the list of variables and list of
commands, returns a string containing what you want to print on the screen, as content
of variable messages, etc. See for the contents of a variable the same searched for in the list
of variables if it does not exist an error is returned, if not to print the value of a
variable is printed the content present in the list in that position, for example.
set a = 5
echo $ aValueFrom $ a
>> 5AAValue
