#ifndef ELEVADOR_H
#define ELEVADOR_H

#include <componentes.h>
#include <cabine.h>
#include <list>
#include <andar.h>

/* Classe Gerenciador */
class Gerenciador{
    public:
        Gerenciador();
        void insere(Andar);
        Andar * proximo();
        Andar * destino();
        bool nenhuma_requisicao();

    private:
        std::list<Andar> requisicoes;
        Andar *proximo_destino;
};

/* Classe Elevador */
class Elevador{

    public:
        enum Estado{
            ESPERANDO,
            PARADO,
            MOVIMENTO,
            EMERGENCIA
        };

        Elevador(int, std::list<Andar>*);
        void loop();
        
        BotaoDestino bDest;
        BotaoChamada bCham;
        Cabine cabine;
        Estado estado;

    private:
        void contador_timeout(bool);

        std::list<Andar> l_andar;
        Gerenciador ger;
        Andar * andar_atual;
        int n_andares;
        Contador<bool> contador;
};

#endif
