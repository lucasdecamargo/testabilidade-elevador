#include <gtest/gtest.h>
#include <elevador.h>
#include <cabine.h>
#include <iostream>
#include <exception>
#include <thread>


//O elevador só se desloca se a porta estiver fechada.


//A porta não fecha se estiver bloqueada.
TEST(Porta, Porta_bloqueada){
    Porta porta(true);

    SensorBloqueio sensor_bloqueio(true);

    porta.fecha();

    EXPECT_TRUE(porta.estado);
}

// O contador é reiniciado quando houver presença no habitáculo.
TEST(){
    SensorPresenca sensor_presenca(true);


}

// O elevador entra em estado de espera após o disparo do contador.

// A iluminação é desligada quando o elevador está em estado de espera.
TEST(){

    Gerenciador g;
    Andar andar_1(1);
    Andar andar_2(2);
    Andar andar_3(3);
    std::list<Andar> list_andar;
    list_andar.push_back(andar_1);
    list_andar.push_back(andar_2);
    list_andar.push_back(andar_3);

    Elevador elevador(3, &list_andar);

    EXPECT_EQ(elevador.estado, Elevador::ESPERANDO);
    EXPECT_EQ(elevador.cabine.iluminacao.estado, false);
}

// A iluminação é ligada quando o o sensor de presenca está ativo ou o estado do elevador é parado.
TEST(){

    Gerenciador g;
    Andar andar_1(1);
    Andar andar_2(2);
    Andar andar_3(3);
    std::list<Andar> list_andar;
    list_andar.push_back(andar_1);
    list_andar.push_back(andar_2);
    list_andar.push_back(andar_3);
    SensorPresenca sensor(false);

    Elevador elevador(3, &list_andar);
    g.insere(andar_1);

    EXPECT_EQ(elevador.estado, Elevador::PARADO);
    EXPECT_EQ(elevador.cabine.iluminacao.estado, true);

    sensor.set(true);

    EXPECT_EQ(elevador.cabine.iluminacao.estado, true);

    g.insere(andar_2);

    EXPECT_EQ(elevador.estado, Elevador::MOVIMENTO);
    EXPECT_EQ(elevador.cabine.iluminacao.estado, true);

}

// Se o elevador está em estado de espera e a porta não estiver bloqueada a porta é fechada.
TEST(){

    Gerenciador g;
    Andar andar_1(1);
    Andar andar_2(2);
    Andar andar_3(3);
    std::list<Andar> list_andar;
    list_andar.push_back(andar_1);
    list_andar.push_back(andar_2);
    list_andar.push_back(andar_3);
    SensorPresenca sensor_presenca(false);
    SensorBloqueio sensor_bloqueio(false);

    Elevador elevador(3, &list_andar);
    g.insere(andar_1);

    EXPECT_EQ(elevador.estado, Elevador::ESPERANDO);
    EXPECT_TRUE(elevador.cabine.porta.estado);
}

// A porta só abre se o elevador estiver parado em um andar.

// Quando o elevador está em estado de emergência, o elevador deve permanecer parado e o contador em reinício.