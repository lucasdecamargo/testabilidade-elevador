#include <elevador.h>
#include <algorithm>

/* Classe Gerenciador */
Gerenciador::Gerenciador(){
    requisicoes.clear();
    proximo_destino=nullptr;
}

void Gerenciador::insere(Andar andar){
    requisicoes.push_back(andar);
    // requisicoes.erase(std::unique(requisicoes.begin(), requisicoes.end()));
}

Andar* Gerenciador::proximo(){
    if(requisicoes.size()>0){
        proximo_destino = &requisicoes.front();
        requisicoes.erase(requisicoes.begin());
        return proximo_destino;
    }
    return nullptr;
}

Andar* Gerenciador::destino(){
    return proximo_destino;
}

bool Gerenciador::nenhuma_requisicao(){
    return requisicoes.empty();
}


/* Classe Elevador */
Elevador::Elevador(std::vector<Andar> *andar): bCham("B1"), bDest("B2"), bEmerg("BE"), cabine(&l_andar){
    l_andar = *andar;
    estado = ESPERANDO;
    n_andares = andar->size();
    contador.registraOuvinte(std::bind(&Elevador::contador_timeout, this, std::placeholders::_1));
    bEmerg.registraOuvinte(std::bind(&Elevador::emergencia_callback, this, std::placeholders::_1));
    bDest.registraOuvinte(std::bind(&Elevador::botao_andar_callback, this, std::placeholders::_1));
    bCham.registraOuvinte(std::bind(&Elevador::botao_andar_callback, this, std::placeholders::_1));
    andar_atual = &l_andar.front();
}

void Elevador::emergencia_callback(bool)
{
    estado = Elevador::EMERGENCIA;
}

void Elevador::botao_andar_callback(Andar andar)
{
    ger.insere(andar);
}

void Elevador::loop(){

    switch (estado)
    {
    case PARADO: // Parado com a porta aberta
        if(!ger.nenhuma_requisicao() && !cabine.sensor_presenca.estado())
            estado = Elevador::MOVIMENTO;
        break;
    case ESPERANDO: //Porta fechada

        if(ger.nenhuma_requisicao()==false){

            Andar * andar_destino =  ger.proximo();
            if(ger.proximo()->get_id() == cabine.sensor_andar.estado()->get_id()){
                cabine.iluminacao.liga();
                cabine.porta.abre();
                contador.reinicia();
                estado = PARADO;
            }else{
                cabine.mover(cabine.sensor_andar.estado(), *andar_destino);
                estado = MOVIMENTO;
            }
        }

        break;
    case MOVIMENTO:

        if(cabine.sensor_andar.estado()->get_id() == ger.destino()->get_id()){

            if(cabine.iluminacao.estado()==false){
                cabine.iluminacao.liga();
            }

            cabine.porta.abre();
            contador.reinicia();
            andar_atual = ger.destino();
            cabine.parar();
            estado = PARADO;
        }

        break;
    case EMERGENCIA:
        
        cabine.parar();

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
        estado = Elevador::ESPERANDO;
    }
    catch(const std::exception& e)
    {
       contador.reinicia();
    }
}