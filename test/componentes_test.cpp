#include <gtest/gtest.h>
#include <componentes.h>
#include <iostream>
#include <exception>
#include <thread>

struct FunctionCalled : public std::exception
{
	const char * what () const throw ()
    {
    	return "Function called";
    }
};


void func_int(int i)
{
    throw FunctionCalled();
}

void func_void(void)
{
    throw FunctionCalled();
}

void func_bool(bool b)
{
    throw FunctionCalled();
}

TEST(ComponentesTest, Notificador)
{
    Notificador<int> n_int;
    n_int.registraOuvinte(func_int);
    EXPECT_THROW(n_int.notifica(10),FunctionCalled);

    Notificador<int> n_bool;
    n_int.registraOuvinte(func_bool);
    EXPECT_THROW(n_int.notifica(false),FunctionCalled);

    Notificador<> n_void;
    n_void.registraOuvinte(func_void);
    EXPECT_THROW(n_void.notifica(),FunctionCalled);
}

TEST(ComponentesTest, Sensor)
{
    SensorBloqueio s_bloq("SB1");
    SensorPresenca s_pres("SP1");
    SensorAndar s_andar("SA1");

    s_bloq.registraOuvinte(func_bool);
    EXPECT_THROW(s_bloq.set(true),FunctionCalled);
    EXPECT_THROW(s_bloq.set(false),FunctionCalled);

    s_pres.registraOuvinte(func_bool);
    EXPECT_THROW(s_pres.set(true),FunctionCalled);
    EXPECT_THROW(s_pres.set(false),FunctionCalled);

    s_andar.set(Andar());
}

TEST(ComponentesTest, Contador)
{
    Contador<> cont(std::chrono::seconds(2));

    cont.registraOuvinte(func_bool);

    cont.reinicia();
    cont.reinicia(true);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_FALSE(cont.loop());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_THROW(cont.loop(),FunctionCalled);
}

TEST(ComponentesTest, Botao)
{
    BotaoDestino b_dest("BD1");
    BotaoEmergencia b_emerg("BE1");
    BotaoChamada b_chamada("BC1");

    b_dest.registraOuvinte(func_void);
    EXPECT_THROW(b_dest.dispara(),FunctionCalled);
    EXPECT_THROW(b_dest.dispara(),FunctionCalled);

    b_emerg.registraOuvinte(func_void);
    EXPECT_THROW(b_dest.dispara(),FunctionCalled);
    EXPECT_THROW(b_dest.dispara(),FunctionCalled);

    b_chamada.registraOuvinte(func_void);
    EXPECT_THROW(b_dest.dispara(),FunctionCalled);
    EXPECT_THROW(b_dest.dispara(),FunctionCalled);
}