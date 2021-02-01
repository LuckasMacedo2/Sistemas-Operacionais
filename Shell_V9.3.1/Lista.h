#ifndef LISTA_H
#define LISTA_H

#include<iostream>
#include "No.h"
#include "Comando.h"
class Lista
{
private:
    No *inicio, * final;
public:

    Lista()
    {
        inicio = NULL;
        final = NULL;
    }

    Comando * getInicio () const{
        return inicio->getDados();
    }

    bool eVazia () const{
        return (inicio==NULL);
    }
    
    void inserirFinal (Comando * aux){
        if (aux==NULL){
            throw std::string ("\nImpossivel realizar a operacao\n");
        }
        No * novo = new No;
        novo->MontarNo(aux);
        if (eVazia())
        {
            inicio = final = novo;
        }else{
            final->setProximo(novo);
            final = novo;
        }
    }

    void inserirInicio (Comando * aux){
        try {
            if (aux == NULL)
            {
                throw std::string ("\nImpossivel realizar a operação\n");
            }
            No * novo = new No;
            novo->MontarNo(aux);
            if (eVazia()){
                inicio = final = novo;
            }
            novo->setProximo(inicio);
            inicio = novo;

        } catch (std::string &erro) {
            throw std::string ("\nErro, impossivel inserir Comando no inicio da lista");
        }
    }

    Comando * retirar(std::string key){
          if(eVazia()) return NULL;
          No *aux=inicio,*ant=inicio;
          while(aux!=NULL && aux->getDados()->getKey() !=key){
              ant=aux;
              aux=aux->getProximo();

          }
          if(aux==NULL) return NULL;
          if(aux==inicio){
              inicio=inicio->getProximo();
              aux->setProximo(NULL);
              if(inicio==NULL) final =NULL;
          }
          else{
              ant->setProximo(aux->getProximo());//1
              aux->setProximo(NULL); //2
              if(aux==final) final=ant;
          }
          Comando * ret=aux->getDados();
          aux->setDados(NULL);
          delete aux;
          return ret;
    }

    Comando * retirarInicio (){
        if (eVazia())
        {
            throw std::string ("\nImpossivel realizar a operacao de remocao da lista\n");
        }
        No * aux = inicio;
        inicio = inicio->getProximo();
        aux->setProximo(NULL);
        if (inicio==NULL) final=NULL;
        Comando * retorno = aux->getDados();
        aux->setDados(NULL);
        delete aux;
        return retorno;
    }

    Comando * buscar (std::string key)const{
        No * aux = inicio;

        for (; aux !=NULL && aux->getDados()->getKey()!=key;)
        {
            aux = aux->getProximo();
        }
        

        if (aux==NULL) return NULL;


        Comando * retorno = new Comando;
        *retorno = *(aux->getDados());//copiando somente o conteudo não o ponteiro
        return retorno;

    }
};

#endif // LISTA_H
