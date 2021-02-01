#ifndef NO_H
#define NO_H

#include "Comando.h"

class No{
private:
    Comando * dados;
    No * proximo;
public:
    bool setDados(Comando * aux){
        if (aux){
            dados = aux;
            return true;
        }
        return false;
    }

    void setProximo (No * aux){
        proximo = aux;
    }

    Comando * getDados () const{
        return dados;
    }
    No * getProximo () const{
        return proximo;
    }
    void MontarNo(Comando * aux)
    {
        try{
            this->setDados(aux);
            this->setProximo(NULL);
        }
        catch(std::bad_alloc&){
            throw std::string ("Erro na memoria");
        }
    }

    void DesmontarNo()
    {
        this->setProximo(NULL);
        delete this;
    }
};

#endif // NO_H
