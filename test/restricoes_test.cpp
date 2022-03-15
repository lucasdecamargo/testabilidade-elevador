#include <gtest/gtest.h>

#include <elevador.h>
#include <cabine.h>

#include <iostream>
#include <exception>
#include <thread>

TEST(R1, MovimentoElevador)
{
    // O elevador só se desloca se a porta estiver fechada.
    // ELEVADOR.movimento -> PORTA.fechada

    std::vector<Andar> lista_andar;

    for(int i = 0; i < 5; i++)
        lista_andar.push_back(Andar(i));

    Elevador elevador(&lista_andar);

    elevador.loop();
    elevador.bCham.dispara(lista_andar[2]);
    while(elevador.cabine.porta.estado() != true)
        elevador.loop();
    
    elevador.bCham.dispara(lista_andar[0]);
    elevador.bCham.dispara(lista_andar[1]);

    while(elevador.cabine.sensor_andar.estado()->get_id() != lista_andar[1].get_id())
    {
        EXPECT_TRUE(elevador.estado == Elevador::MOVIMENTO ? !elevador.cabine.porta.estado() : true);
        elevador.loop();
    }
}

TEST(R2, Porta_bloqueada)
{
    // A porta não fecha se estiver bloqueada.
    // S_BLOQ.verdadeiro -> PORTA.aberto
    
    std::vector<Andar> lista_andar;

    for(int i = 0; i < 5; i++)
        lista_andar.push_back(Andar(i));

    Elevador elevador(&lista_andar);

    elevador.loop();
    elevador.bCham.dispara(lista_andar[2]);
    elevador.loop();
    EXPECT_FALSE(elevador.cabine.porta.estado());

    elevador.bCham.dispara(lista_andar[0]);

    while(elevador.estado != Elevador::PARADO)
        elevador.loop();
    
    elevador.cabine.sensor_presenca.set(true);
    
    elevador.bCham.dispara(lista_andar[3]);

    elevador.loop();

    EXPECT_EQ(elevador.estado, Elevador::PARADO);
}

// // O contador é reiniciado quando houver presença no habitáculo.
// TEST(){
//     SensorPresenca sensor_presenca(true);


// }

// // O elevador entra em estado de espera após o disparo do contador.

// // A iluminação é desligada quando o elevador está em estado de espera.
// TEST(){

//     Gerenciador g;
//     Andar andar_1(1);
//     Andar andar_2(2);
//     Andar andar_3(3);
//     std::vector<Andar> list_andar;
//     list_andar.push_back(andar_1);
//     list_andar.push_back(andar_2);
//     list_andar.push_back(andar_3);

//     Elevador elevador(3, &list_andar);

//     EXPECT_EQ(elevador.estado, Elevador::ESPERANDO);
//     EXPECT_EQ(elevador.cabine.iluminacao.estado, false);
// }

// // A iluminação é ligada quando o o sensor de presenca está ativo ou o estado do elevador é parado.
// TEST(){

//     Gerenciador g;
//     Andar andar_1(1);
//     Andar andar_2(2);
//     Andar andar_3(3);
//     std::vector<Andar> list_andar;
//     list_andar.push_back(andar_1);
//     list_andar.push_back(andar_2);
//     list_andar.push_back(andar_3);
//     SensorPresenca sensor(false);

//     Elevador elevador(3, &list_andar);
//     g.insere(andar_1);

//     EXPECT_EQ(elevador.estado, Elevador::PARADO);
//     EXPECT_EQ(elevador.cabine.iluminacao.estado, true);

//     sensor.set(true);

//     EXPECT_EQ(elevador.cabine.iluminacao.estado, true);

//     g.insere(andar_2);

//     EXPECT_EQ(elevador.estado, Elevador::MOVIMENTO);
//     EXPECT_EQ(elevador.cabine.iluminacao.estado, true);

// }

// // Se o elevador está em estado de espera e a porta não estiver bloqueada a porta é fechada.
// TEST(){

//     Gerenciador g;
//     Andar andar_1(1);
//     Andar andar_2(2);
//     Andar andar_3(3);
//     std::vector<Andar> list_andar;
//     list_andar.push_back(andar_1);
//     list_andar.push_back(andar_2);
//     list_andar.push_back(andar_3);
//     SensorPresenca sensor_presenca(false);
//     SensorBloqueio sensor_bloqueio(false);

//     Elevador elevador(3, &list_andar);
//     g.insere(andar_1);

//     EXPECT_EQ(elevador.estado, Elevador::ESPERANDO);
//     EXPECT_TRUE(elevador.cabine.porta.estado);
// }

// // A porta só abre se o elevador estiver parado em um andar.

// // Quando o elevador está em estado de emergência, o elevador deve permanecer parado e o contador em reinício.