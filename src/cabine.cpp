#include "cabine.h"

/* Metodos classe Ilumincao */
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

/* Metodos classe Porta */
Porta::Porta(SensorBloqueio *sensor): _sensor(sensor){
    if(sensor->estado() == true){
        _estado = true;
    }else{
        _estado = false;
    }
}

void Porta::abre(void){
    _estado = true;
}

void Porta::fecha(void){
    if(_sensor->estado() == true){
        return;
    }
    _estado = false;
}

bool Porta::estado(void) const{
    return _estado;
}



/* Metodos classe Cabine */
