#ifndef ELEVADOR_H
#define ELEVADOR_H

#include <componentes.h>
#include <cabine.h>
#include <list>

/* Classe Gerenciador */
class Gerenciador{
    public:
        Gerenciador();
        void insere(Andar);
        Andar proximo();
        Andar destino();
        bool nenhuma_requisicao();

    private:
        std::list<Andar> requisicoes;
        Andar *proximo_destino;
};

/* Classe Andar */
class Andar{
    public:
        Andar(int);
        int get_id();

    private:
        int id;
};

/* Classe Elevador */
class Elevador{

    enum Estado{
        ESPERANDO,
        PARADO,
        MOVIMENTO,
        EMERGENCIA
    };

    public:
        Elevador(int);
        void init(Andar *);
        void loop();
        
        BotaoDestino bDest;
        BotaoChamada bCham;
        Cabine cabine;

    private:
        void contador_timeout(bool);

        std::list<Andar> l_andar;
        Estado estado;
        Gerenciador ger;
        Andar * andar_atual;
        int n_andares;
        Contador<bool> contador;
};

#endif
