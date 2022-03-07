#include <elevador.h>

/* Classe Gerenciador */
Gerenciador::Gerenciador(){
    requisicoes.clear();
}

void Gerenciador::insere(Andar andar){
    requisicoes.push_back(andar);
    requisicoes.unique();
}

Andar Gerenciador::proximo(){
    proximo_destino = &requisicoes.front();
    requisicoes.pop_front();
    return *proximo_destino;
}

Andar Gerenciador::destino(){
    return *proximo_destino;
}

bool Gerenciador::nenhuma_requisicao(){
    return requisicoes.empty();
}

/* Classe Andar */
Andar::Andar(int id_name){
    id = id_name;    
}

int Andar::get_id(){
    return id;
}

/* Classe Elevador */
Elevador::Elevador(int numero_andares): bCham("B1"), bDest("B2"), cabine(&l_andar){
    l_andar.clear();
    estado = ESPERANDO;
    n_andares = numero_andares;
    contador.registraOuvinte(std::bind(&Elevador::contador_timeout, this, std::placeholders::_1));
    andar_atual = &l_andar.front();
}

void Elevador::loop(){

    switch (estado)
    {
    case PARADO: // Parado com a porta aberta

        

        break;
    case ESPERANDO: //Porta fechada

        if(ger.nenhuma_requisicao()==false){

            Andar * andar_destino =  &ger.proximo();
            if(ger.proximo().get_id() == andar_atual->get_id()){
                cabine.iluminacao.liga();
                cabine.porta.abre();
                contador.reinicia();
                estado = PARADO;
            }else{
                cabine.move(andar_atual, *andar_destino);
                estado = MOVIMENTO;
            }
        }

        break;
    case MOVIMENTO:

        if(cabine.sensor_andar.estado().get_id() == ger.destino().get_id()){

            if(cabine.iluminacao.estado()==false){
                cabine.iluminacao.liga();
            }

            cabine.porta.abre();
            contador.reinicia();
            andar_atual = &ger.destino();
            cabine.parar();
            estado = PARADO;
        }

        break;
    case EMERGENCIA:
        
        if(cabine.sensor_andar.estado().get_id() == ger.destino().get_id()){
            cabine.parar();
        }

        if(cabine.iluminacao.estado()==false){
            cabine.iluminacao.liga();
        }

        break;
    default:
        break;
    }
}

void Elevador::contador_timeout(bool time_out){
    try
    {
        cabine.porta.fecha();
        cabine.iluminacao.desliga();
    }
    catch(const std::exception& e)
    {
       contador.reinicia();
    }
}