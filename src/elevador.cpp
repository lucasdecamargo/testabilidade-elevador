#include <elevador.h>

/* Classe Gerenciador */
Gerenciador::Gerenciador(){
    requisicoes.clear();
}

void Gerenciador::insere(Andar andar){
    requisicoes.push_back(andar);
}

Andar Gerenciador::proximo(){
    Andar andar_aux = requisicoes.front();
    requisicoes.pop_front();
    return andar_aux;
}

/* Classe Andar */
Andar::Andar(int id_name){
    id = id_name;
    //ver botão
}

/* Classe Elevador */
Elevador::Elevador(Gerenciador * g, Cabine * c){
    l_andar.clear();
    estados = 0;
    ger = g;
    cabine = c;
}

void Elevador::init(Andar * terreo){
    andar = terreo;
}

void Elevador::loop(){

    switch (estados)
    {
    case 0: /* Parado sem requsição
        /* code */
        break;
    case 1: /* Parado com requisição
        /* code */
        break;
    case 2: /* Movimento
        /* code */
        break;

    default:
        break;
    }
}