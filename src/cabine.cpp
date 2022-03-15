#include <cabine.h>

using namespace elevador;

/*-------------  Metodos classe Iluminacao  ------------- */
Iluminacao::Iluminacao(): _estado(false){}

Iluminacao::Iluminacao(bool estado): _estado(estado){}


void Iluminacao::liga(void){
    _estado = true;
}

void Iluminacao::desliga(void){
    _estado = false;
}

bool Iluminacao::estado(void) const{
    return _estado;
}


/*-------------  Metodos classe Porta  ------------- */
Porta::Porta(bool estado): sensor_bloqueio("SB"), _estado(estado) { }

Porta::Porta(): sensor_bloqueio("SB"), _estado(false) { }

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


/*-------------  Metodos classe Cabine  ------------- */
Cabine::Cabine(std::vector<Andar>* lista_andar)
    : iluminacao(true), porta(false), 
        sensor_andar("SA"), sensor_presenca("SP"), _lista_andar(lista_andar),
        _movimento(false)
{

}

void Cabine::mover(Andar *atual, Andar prox)
{
    *atual = prox;
    _movimento = true;
}

bool Cabine::get_movimento(){
    return _movimento;
}   

void Cabine::parar(){
    _movimento = false;
}