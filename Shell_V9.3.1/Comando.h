#ifndef COMANDO_H
#define COMANDO_H

#include <string>

//Comando
class Comando {
private:
    std::string key;
    std::string valor;
public:
    Comando (){
        key = "";
        valor = "";
    }

    Comando (std::string key, std::string valor){
        this->key = key;
        this->valor = valor;
    }

    void setKey (std::string key){
        this->key = key;
    }
    std::string getKey () const{
        return key;
    }

    void setValor (std::string valor){
        this->valor = valor;
    }
    std::string getValor () const{
        return valor;
    }

};

#endif // COMANDO_H
