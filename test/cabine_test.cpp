#include <gtest/gtest.h>
#include <cabine.h>
#include <iostream>
#include <exception>
#include <thread>

using namespace elevador;


TEST(Iluminacao, Construtor)
{
    Iluminacao ilum_default;
    Iluminacao ilum_true(true);
    Iluminacao ilum_false(false);
    
    EXPECT_EQ(ilum_default.estado(), false);
    EXPECT_EQ(ilum_true.estado(), true);
    EXPECT_EQ(ilum_false.estado(), false);
}

TEST(Iluminacao, Metodos)
{
    Iluminacao ilum; 

    ilum.liga();
    EXPECT_EQ(ilum.estado(), true);
    ilum.desliga();
    EXPECT_EQ(ilum.estado(), false);
}


TEST(Porta, Construtor)
{
    Porta porta_default;
    Porta porta_true(true);
    Porta porta_false(false);
    
    EXPECT_EQ(porta_default.estado(), false);
    EXPECT_EQ(porta_true.estado(), true);
    EXPECT_EQ(porta_false.estado(), false);
}


TEST(Porta, abre)
{
    Porta porta; 
    porta.abre();
    EXPECT_EQ(porta.estado(), true);
} 

TEST(Porta, fecha_porta_livre){
    Porta porta;

    porta.abre();
    porta.sensor_bloqueio.set(false);
    porta.fecha();
    EXPECT_EQ(porta.estado(), false);
}

TEST(Porta, fecha_porta_bloqueada){
    Porta porta;

    porta.abre();
    porta.sensor_bloqueio.set(true);
    EXPECT_THROW(porta.fecha(), exc::porta_bloqueada);

}

TEST(Porta, redundancia_livre){
    Porta porta;
    // Livre
    porta.sensor_bloqueio.set(false);

    porta.abre();
    EXPECT_EQ(porta.estado(), true);
    porta.abre();
    EXPECT_EQ(porta.estado(), true);
    
    porta.fecha(); 
    EXPECT_EQ(porta.estado(), false);
    porta.fecha(); 
    EXPECT_EQ(porta.estado(), false);
}

TEST(Porta, redundancia_bloqueada){
    Porta porta;
    porta.sensor_bloqueio.set(true);

    porta.abre();
    EXPECT_EQ(porta.estado(), true);
    porta.abre();
    EXPECT_EQ(porta.estado(), true);

    EXPECT_THROW(porta.fecha(), exc::porta_bloqueada);
    EXPECT_THROW(porta.fecha(), exc::porta_bloqueada);
}

// Duvida aqui: Como testar atributos protegidos? tenho que criar 
// classe amiga so pra testar? Mas isso vai alterar a cabine.h
TEST(Cabine, Construtor){
    std::list<Andar> *andar;
    Cabine cab(andar);
    
    EXPECT_EQ(cab.get_movimento(), false);

}


TEST(Cabine, move_e_parar){
    std::list<Andar> *andar;
    Andar *atual;
    Andar *prox;
    Cabine cab(andar);

    cab.mover(atual, *prox);
    EXPECT_EQ(cab.get_movimento(), true);
    cab.parar();
    EXPECT_EQ(cab.get_movimento(), false);
}