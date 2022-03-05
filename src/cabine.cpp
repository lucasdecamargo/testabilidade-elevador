#include <cabine.h>

using namespace elevador;

/* Metodos classe Ilumincao */
Iluminacao::Iluminacao(): _estado(false){}

Iluminacao::Iluminacao(bool estado): _estado(estado){}

int Iluminacao::soma(int a, int b){
    return a+b;
}

void Iluminacao::liga(void){
    _estado = true;
}

void Iluminacao::desliga(void){
    _estado = false;
}

bool Iluminacao::estado(void) const{
    return _estado;
}

/* Metodos classe Porta */
Porta::Porta(bool estado): sensor_bloqueio("SB"), _estado(estado) { }

void Porta::abre(void){
    _estado = true;
}

void Porta::fecha(void){
    if(sensor_bloqueio.estado()){
        throw exc::porta_bloqueada();
    }
    _estado = false;
}

bool Porta::estado(void) const{
    return _estado;
}



/* Metodos classe Cabine */
Cabine::Cabine(std::list<Andar>* lista_andar)
    : iluminacao(true), porta(false), contador(std::chrono::seconds(0)), 
        sensor_andar("SA"), sensor_presenca("SP"), _lista_andar(lista_andar)
{

}

void Cabine::move(Andar& destino)
{

}