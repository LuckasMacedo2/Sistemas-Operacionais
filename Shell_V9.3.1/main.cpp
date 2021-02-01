#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "Comando.h" //Objetos maniplados.
#include "Lista.h"   //Estrutura para armazenar os objetos

using namespace std;

//Versões anteriores no drive


//---------------------Controle de Versões ----------------
//|                        Versão 9.3                     |
//|                  Lucas Macedo da Silva                |
//---------------------------------------------------------

//Bug fixed
//
//
//
//
//Terminio
//ECHO - OK
//SET - OK
//EXIT - OK
//PATH - OK



// ' '  -> Separador.
// $ 	-> Pegar o valor da variavel.
// SET  -> Setar um valor para a variavel
// < >	-> Colocar Espaços e caracteres especiais



//------------------------ Funções da shell ------------------------
Lista * tratarString (string str); //Retorna os comando separados.

string operador$ (Lista * listaCMD, Lista *lista); //Retorna o valor da váriavel, e a concatenacao das subsequentes.

Comando * set(Lista * listaDeComandos, Lista *lista); //Atribui o valor depois do operador = na variavel.

void path (Lista *lista); //Executa o caminho definido na variavel PATH a mesma deve ser setada de antemão.

string echo (Lista *lista, Lista *listaCMD); //Imprime o que foi requerido.



//------------------------ Funções extras ---------------------------
string convertiMaiuscula (string str); //Apenas convertendo os primeiros comandos para maiusculo exemplo SET, PATH, ...

void printHelp(); //Imprime uma mensagem com informações sobre o código.



//----------------------- Programa principal ------------------------
int main(int argc, char *argv[])
{
    Lista * lista = new Lista;

    string comando = "";

    cout<<"\n\n\t\t\t\t[-----SHELL-----]\n\t\tPressione h para ajuda\n\t\tPID do programa: "<<getpid()<<"\n\n";

    while(comando != "EXIT"){

        cout<<"-> ";
        getline(cin, comando);

        if(comando == "h" || comando == "H")
        {

            printHelp();

        }else{
            try {

                Lista * listaComandos = new Lista;
                listaComandos = tratarString(comando);

                while(!listaComandos->eVazia()) {
                    string aux = convertiMaiuscula( listaComandos->retirarInicio()->getKey());


                    if (aux == "SET"){
                        Comando * obj = new Comando;

                        obj = set(listaComandos, lista);
                        lista->inserirFinal(obj);

                        cout<<"\n>> "<<"key: "<<obj->getKey()<<" |Valor: "
                           <<obj->getValor()<<endl;
                    }
                    else{
                        if(aux == "PATH")
                        {
                            path(lista);
                        }
                        else
                        {
                            if(aux == "ECHO"){
                                cout<<"\n>> "<<echo(lista, listaComandos)<<endl;
                            }
                            else{
                                if(aux == "EXIT")
                                    exit(1);
                                else
                                    throw string("\n=>>Erro, comando invalido");
                            }
                        }
                    }
                }
            } catch (string &erro) {
                cout<<erro<<endl;
            }
            cout<<endl;
        }
    }
}

//------------------------ Funções da Shell -------------------------
//Retorna uma lista com todas as string's devidamente separadas
Lista * tratarString(string str){

    try{

        int len = int(str.length());
        Lista * stringList = new Lista;

        string subComando = "";
        int j = 0;
        for (; j < len; ++j) {
            Comando * subComandoObj = new Comando;

            if(str[j] == '<'){ //Realizando a operação que permite a inclusao de espacos e caracteres especiais
                int index = str.find('>');

                if(index<0)
                    throw string("\n=>>Erro, comando invalido");

                str[index] = ' '; //Retirando o operador >, pois podem haver mais operações em uma
                int k = j+1;    //mesma string
                string a = "";
                for (;  k < index; k++) {
                    a += str[k];
                }
                subComandoObj = new Comando;
                subComandoObj->setKey(subComando);
                subComandoObj->setValor("");
                stringList->inserirFinal(subComandoObj);
                subComando = "";

                subComandoObj = new Comando;
                subComandoObj->setKey(a);
                subComandoObj->setValor("");
                stringList->inserirFinal(subComandoObj);

                j = k;
            }else{
                //Verificando se é um caracter especial e válido a partir da tabela ASCII
                if(int(str[j]) == 36 || (int(str[j])>=42 && int(str[j])<=47)
                        || int(str[j]) == 61 || int(str[j] == 92) || int(str[j] == 58))

                {
                    if(subComando!=""){
                        subComandoObj = new Comando;
                        subComandoObj->setKey(subComando);
                        subComandoObj->setValor("");
                        stringList->inserirFinal(subComandoObj);

                    }
                    subComando = "";
                    string a = "";
                    a += str[j];

                    subComandoObj = new Comando;
                    subComandoObj->setKey(a);
                    subComandoObj->setValor("");
                    stringList->inserirFinal(subComandoObj);
                }
                else
                {
                    //Verificando se é um caracter válido, segundo a tabela ASCII
                    if((int(toupper(str[j]))>=65 && int(toupper(str[j])<=90)) ||
                            (int(str[j]>=48) && int(str[j]<=57))){
                        subComando += str[j];
                    }else{
                        if(str[j] == ' ')
                        {
                            if(subComando!=""){

                                subComandoObj = new Comando;

                                subComandoObj->setKey(subComando);
                                subComandoObj->setValor("");
                                stringList->inserirFinal(subComandoObj);
                                subComando = "";

                            }
                        }
                    }
                }
            }
        }

        Comando * subComandoObj = new Comando;

        subComandoObj->setKey(subComando);
        subComandoObj->setValor("");
        stringList->inserirFinal(subComandoObj);

        return stringList;
    }catch (string erro){
        throw erro;
    }

}

//Seta o valor para a devida variavel
Comando * set (Lista * listaCMD, Lista * lista){
    try {

        bool ok = false;
        Comando * objOp1 = new Comando;

        //Caso o primeiro elemento faça parte da atribuição
        Comando * op1Aux = new Comando;
        op1Aux = lista->buscar(listaCMD->getInicio()->getKey());

        //Primeiro operando
        Comando * op1 = new Comando;
        op1 = listaCMD->retirarInicio();


        //Criando uma nova variavel
        Comando * objBusca = lista->buscar(op1->getKey());
        if(objBusca == NULL) {//Criando um novo objeto
            objOp1->setKey(op1->getKey());
        }
        else{//O objeto foi encontrado
            ok = true; //Futuras atualizações da variavel
            objOp1 = new Comando;
            objOp1->setKey(op1->getKey());
        }

        //Operador '='
        Comando * op = new Comando;
        op = listaCMD->retirarInicio();

        string var = "";

        if(op->getKey().operator [](0) == '='){
            //Cuidando da segunda variavel
            while(!listaCMD->eVazia()){
                //Segundo operando
                Comando * op2 =  new Comando;
                op2 = listaCMD->retirarInicio();
                //Verificando se é um comando de get do valor
                if(op2->getKey().operator [](0) == '$'){
                    //Caso o primeiro operando exista.
                    if(op1Aux!=NULL && listaCMD->getInicio()->getKey() == op1Aux->getKey()){
                        var += op1Aux->getValor();
                        listaCMD->retirarInicio();

                    }
                    else
                        var += operador$(listaCMD, lista);
                }else{
                    var += op2->getKey();
                }
            }
        }else{
            throw string("\n=>>Erro, formato de operacao invalida, insira = apos a variavel");
        }

        if(ok)
            lista->retirar(op1->getKey()); //Atualizando a variavel caso ela já esteja na lista

        objOp1->setValor(var);

        return objOp1;
    } catch (string &erro) {
        throw erro;
    }
}


//Operador que pega o valor da variavel
string operador$ (Lista * listaCMD, Lista * lista){


    Comando * objOp2 = NULL;

    Comando * obj = new Comando;

    obj = listaCMD->retirarInicio(); //Recebendo o "$"

    string var = obj->getKey();

    if(var=="$"){
        obj = listaCMD->retirarInicio(); //Recebendo a variavel
        var = obj->getKey();
    }

    objOp2 = lista->buscar(var); //Buscando a string total

    string a = "";

    if(objOp2 == NULL){

        string var1 = "";
        int len = int(var.length());
        int i;

        for (i = 0; i < len && objOp2 == NULL; ++i) { //Buscando nas substring's, as demais depois de encontrado o valor são concatenadas
            var1 += var[i];
            objOp2 = lista->buscar(var1);

        }

        if(objOp2 == NULL){
            throw string("\n=>>Operacao invalida, a variavel nao existe");
        }else{
            for (; i < len; ++i) {//Concatenando as demais substring's
                a += var[i];
            }
        }
    }
    return objOp2->getValor()+a;
}

//fork(): Cria uma copia do processo pai, pai e filho sao executados em
//espaços de memória diferentes
//Retornos: 0


void path (Lista * lista){

    try{
        Comando * objBusca = new Comando;

        objBusca = lista->buscar("path");
        if (objBusca == NULL)
            throw string ("\n>>Erro, variavel path, sem um valor atribuido");

        pid_t PID, pid;
        int status;

        PID = fork(); //Criando o filho


        if(PID<0){ //Filho nao foi criado
            cout<<"\n>>Filho não criado impossivel criar o processo.\nTente novamente ...";
            exit(EXIT_FAILURE);
        }else{
            if (PID == 0){ //Filho foi criado

                cout<<"\n>>Filho: "<<(int(PID))<<endl;

                string path = objBusca->getValor(); //Pegando o endereço da path

                //Se estiverem no mesmo diretorio colocar apenas o nome
                //do arquivo ex: hello, que exexcuta.
                
                if (path.find('/') < 0)
                    path = "./" + path;


                execl(path.c_str(), NULL);
                
                _exit(EXIT_SUCCESS);
            }else{
                cout<<"\n>>Pai: "<<(int(PID))<<endl;

                //Bloqueia o pai e espera que ocorra algo com o filho
                //bem como permite que o sistema libere os recursos associados aos
                //processos filhos
                cout<<"\n\t\tPID do programa: "<<getpid();
                while (pid = wait(&status)>0)
                    if(WIFEXITED (status))
                        cout<<"\n>>Filho em espera: "<<int(pid)<<endl;
                    else
                        cout<<"\n=>>Houve um erro com o processo filho: "<<int(pid);


            }

        }
    }catch (string &erro){
        throw erro;
    }
}

string echo (Lista * lista, Lista * listaCMD){
    string saida = "";

    while (!listaCMD->eVazia()) {

        string str = listaCMD->getInicio()->getKey();

        //Verificando se é um comando de get
        if(str == "$"){

            listaCMD->retirarInicio();
            Comando * aux = new Comando;
            aux = listaCMD->retirarInicio();


            Comando * obj = NULL;
            obj = lista->buscar(aux->getKey()); //Buscando o valor na lista de valores

            //O valor não foi encontrado, verificando a concatenção da string
            if(obj == NULL){
                string objStr = aux->getKey();

                int len = int(objStr.length());
                string var = "";

                int i = 0;
                for (; i < len && obj == NULL; ++i) {
                    var += objStr[i];
                    obj = lista->buscar(var);
                }

                //O objeto foi encontrado, verificando o resto da string que
                //está sendo considereada concatenada com a anterior
                if(obj != NULL){
                    var = "";
                    saida += obj->getValor();
                    for (int j = i; j < len; ++j) {
                        var += objStr[j];
                    }
                    saida += var;
                }

                else{
                    throw string ("\n=>>Variavel sem valor atribuido");
                }

            }else{ //O valor foi encontrado na primeira string
                saida += obj->getValor();
            }
        }else{
            Comando * aux = new Comando;
            aux = listaCMD->retirarInicio();
            saida += aux->getKey();
        }


    }

    return saida;
}

//-------------------------- Funções adicionais -----------------------------------------
string convertiMaiuscula (string str){
    int len = str.length();
    string strMaiuscula = "";
    for (int i = 0; i < len; ++i) {
        strMaiuscula += toupper(str[i]);
    }
    return strMaiuscula;
}

void printHelp(){
    cout<<"\n--------------------------------------------------------------------------------"
          "// Criado por Lucas Macedo da Silva.\n"
          "// Matricula: 2016100330547-0.\n"
          "//\n"
          "//Funcoes.\n"
          "//SET A = Valor, seta a variavel A com o valor especificado.\n"
          "//$A Operador de get pega o valor da variavel A.\n"
          "//ECHO Mensagem, Exibi uma mensagem na tela.\n"
          "//PATH, Executa o que esta no caminho definido, o valor deve ser setado antes.\n"
          "//EXIT, sair do programa.\n"
          "//<>, Utilizados para setar um valor com espaços e caracteres especiais.\n"
          "//\n//OBS: Pré compilar o programa a ser executado, ao digitar path\n"
          "--------------------------------------------------------------------------------\n\n";
}






