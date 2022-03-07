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

    private:
        std::list<Andar> requisicoes;
};

/* Classe Andar */
class Andar{
    public:
        Andar(int);
        Gerenciador *ger;

    private:
        int id;
        BotaoDestino *bCham;
        BotaoChamada *bDest;
};

/* Classe Elevador */
class Elevador{

    public:
        Elevador(Gerenciador *, Cabine *);
        void init(Andar *);
        void loop();
    private:
        std::list<Andar> l_andar;
        int estados;
        Gerenciador *ger;
        Cabine *cabine;
        Andar * andar;
};

#endif
