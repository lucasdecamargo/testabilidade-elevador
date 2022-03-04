#ifndef CABINE_H
#define CABINE_H

#include "componentes.h"


/*-------------------- Iluminacao --------------------*/
/* Classe Iluminacao */
class Iluminacao{
    public:
        Iluminacao();
        Iluminacao(bool estado);
        void liga(void);
        void desliga(void);
        bool estado(void) const;
    private:
        bool _estado;
};

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

/*-------------------- Porta --------------------*/
/* Classe Porta */
class Porta{
    public:
        Porta(SensorBloqueio *sensor);
        void abre(void);
        void fecha(void);
        bool estado(void) const;
    private:
        bool _estado;
        SensorBloqueio *_sensor;
};

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

/*-------------------- Cabine --------------------*/
/* Classe Cabine */
template<typename T>
class Cabine{
    public:
        Cabine(bool estado_iluminacao, SensorBloqueio *sensor_bloqueio,
                std::chrono::seconds timeout, Id sensor_andar, Id sensor_presenca);
        Cabine();
        void move(Andar destino);
    private:
        Iluminacao _iluminacao;
        Porta _porta;
        Contador _contador;
        SensorAndar *_sensor_andar;
        SensorPresenca *_sensor_presenca;
};

/* Metodos classe Cabine */

Cabine::Cabine(){
    
}



#endif