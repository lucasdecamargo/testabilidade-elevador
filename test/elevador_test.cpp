#include <gtest/gtest.h>
#include <elevador.h>
#include <iostream>
#include <exception>
#include <thread>

using namespace elevador;


TEST(Gerenciador, Construtor)
{
    Gerenciador g;
    
    EXPECT_TRUE(g.nenhuma_requisicao());
}

TEST(Gerenciador, Requisicoes)
{
    Andar andar(1);
    Gerenciador g;

    g.insere(andar);

    EXPECT_EQ(g.destino(), nullptr);
    // EXPECT_EQ(g.proximo()->get_id(), andar.get_id());
    // EXPECT_EQ(g.destino()->get_id(), andar.get_id());
    EXPECT_EQ(g.proximo(), nullptr);

    Andar andar0(0);
    Andar andar1(1);

    g.insere(andar0);
    g.insere(andar1);

    // EXPECT_EQ(g.proximo()->get_id(), andar0.get_id());
    // EXPECT_EQ(g.proximo()->get_id(), andar1.get_id());
}

TEST(Elevador, Movimento)
{
    Andar andar_1(1);
    Andar andar_2(2);
    Andar andar_3(3);
    std::vector<Andar> list_andar;
    list_andar.push_back(andar_1);
    list_andar.push_back(andar_2);
    list_andar.push_back(andar_3);

    std::cout << "@@ CHECK 1" << std::endl;
    Elevador elevador(&list_andar);
    std::cout << "@@ CHECK 2" << std::endl;

    EXPECT_EQ(elevador.estado, Elevador::ESPERANDO);
    std::cout << "@@ CHECK 3" << std::endl; 
    
    elevador.bCham.dispara(andar_2);
    std::cout << "@@ CHECK 4" << std::endl;
    elevador.loop();
    std::cout << "@@ CHECK 5" << std::endl;

    EXPECT_EQ(elevador.estado,Elevador::MOVIMENTO);
    std::cout << "@@ CHECK 6" << std::endl;
}

TEST(Elevador, Emergencia)
{
    Andar andar_1(1);
    Andar andar_2(2);
    Andar andar_3(3);
    std::vector<Andar> list_andar;
    list_andar.push_back(andar_1);
    list_andar.push_back(andar_2);
    list_andar.push_back(andar_3);

    Elevador elevador(&list_andar);

    EXPECT_EQ(elevador.estado, Elevador::ESPERANDO);
    
    elevador.bEmerg.dispara(true);
    elevador.loop();

    EXPECT_EQ(elevador.estado, Elevador::EMERGENCIA);
}

TEST(Elevador, Parado){
    Andar andar_1(1);
    Andar andar_2(2);
    Andar andar_3(3);
    std::vector<Andar> list_andar;
    list_andar.push_back(andar_1);
    list_andar.push_back(andar_2);
    list_andar.push_back(andar_3);

    Elevador elevador(&list_andar);
    Gerenciador g;

    EXPECT_EQ(elevador.estado, Elevador::ESPERANDO);
    
    g.insere(andar_1);

    EXPECT_EQ(elevador.estado, Elevador::PARADO);
}