#ifndef ELEVADOR_H
#define ELEVADOR_H

#include <componentes.h>
#include <cabine.h>
#include <vector>
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
        std::vector<Andar> requisicoes;
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

        Elevador(std::vector<Andar>*);
        void loop();
        
        BotaoDestino bDest;
        BotaoChamada bCham;
        BotaoEmergencia bEmerg;
        Cabine cabine;
        Estado estado;

    private:
        void contador_timeout(bool);
        void emergencia_callback(bool);
        void botao_andar_callback(Andar andar);

        std::vector<Andar> l_andar;
        Gerenciador ger;
        Andar * andar_atual;
        int n_andares;
        Contador<bool> contador;
};

#endif
