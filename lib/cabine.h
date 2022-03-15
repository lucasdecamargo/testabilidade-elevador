#ifndef CABINE_H
#define CABINE_H

#include <chrono>

#include <componentes.h>
#include <excecoes.h>
#include <andar.h>

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
        Porta(bool estado);
        Porta();
        void abre(void);
        void fecha(void);
        bool estado(void) const;

    /* protected: */
        SensorBloqueio sensor_bloqueio;

    private:
        bool _estado;
};

/* Classe Cabine */
class Cabine{
    friend class Elevador;

    public:
        Cabine(std::list<Andar>* lista_andar);
        void mover(Andar *atual, Andar destino);
        void parar();
        bool get_movimento();

    protected:
        Iluminacao iluminacao;
        Porta porta;
        SensorAndar sensor_andar;
        SensorPresenca sensor_presenca;

    private:
        std::list<Andar>* _lista_andar;
        bool _movimento;
};

#endif
