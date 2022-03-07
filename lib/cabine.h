#ifndef CABINE_H
#define CABINE_H

#include <chrono>

#include <componentes.h>
#include <excecoes.h>

/* Classe Iluminacao */
class Iluminacao{
    public:
        Iluminacao();
        Iluminacao(bool estado);
        void liga(void);
        void desliga(void);
        bool estado(void) const;
        int soma(int a, int b);

    private:
        bool _estado;
};

/* Classe Porta */
class Porta{
    public:
        Porta(bool estado);

        void abre(void);
        void fecha(void);
        bool estado(void) const;

    protected:
        SensorBloqueio sensor_bloqueio;

    private:
        bool _estado;
};

/* Classe Cabine */
class Cabine{
    // friend class Elevador;

    public:
        Cabine(std::list<Andar>* lista_andar);

        void move(Andar& destino);

    protected:
        Iluminacao iluminacao;
        Porta porta;
        SensorAndar sensor_andar;
        SensorPresenca sensor_presenca;

    private:
        std::list<Andar>* _lista_andar;
};

#endif
