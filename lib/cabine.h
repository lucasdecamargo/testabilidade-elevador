#ifndef CABINE_H
#define CABINE_H

#include <componentes.h>

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

/* Classe Cabine */
class Cabine{
    public:
        Cabine(bool estado_iluminacao, SensorBloqueio *sensor_bloqueio,
                std::chrono::seconds timeout, Id sensor_andar, Id sensor_presenca);
        Cabine();
        void move(Andar destino);
    private:
        Iluminacao _iluminacao;
        Porta _porta;
        Contador<bool> _contador;
        SensorAndar *_sensor_andar;
        SensorPresenca *_sensor_presenca;
};

#endif
