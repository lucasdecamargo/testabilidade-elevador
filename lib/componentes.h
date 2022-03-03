#ifndef COMPONENTES_H
#define COMPONENTES_H

#include <list>
#include <functional>
#include <string>
#include <chrono>
#include <memory>

typedef std::string Id;

class Andar {};

template<typename ...T>
class Notificador
{
public:
    Notificador(){}
    ~Notificador(){}

    void notifica(T...);
    void registraOuvinte(std::function<void(T...)> func);

protected:
    std::list< std::function<void(T...)> > ouvintes;
};

template<typename T>
class Sensor : public Notificador<T>
{
public:
    Sensor(Id id) : _id(id){}

    void set(T estado);
    const T estado() { return _estado; }
    const Id id() { return _id; }

private:
    Id _id;
    T _estado;
};

typedef Sensor<bool> SensorBloqueio;
typedef Sensor<bool> SensorPresenca;
typedef Sensor<Andar> SensorAndar;

template<typename T=bool>
class Contador : public Notificador<T>
{
public:
    Contador(std::chrono::seconds timeout=std::chrono::seconds(15)) 
        : timeout(timeout),_ativado(false){}

    bool loop();
    void desativa() { _ativado=false; }    
    void reinicia(const T msg);
    void reinicia(void);

protected:
    std::chrono::seconds timeout;

private:
    std::chrono::seconds _sinc;
    std::unique_ptr<T> _msg;
    bool _ativado;
};


template<typename ...T>
class Botao : public Notificador<T...>
{
public:
    Botao(Id id) : _id(id){}

    void dispara(T... msg) {this->notifica(msg...);}

private:
    Id _id;
};

typedef Botao<> BotaoDestino;
typedef Botao<> BotaoEmergencia;
typedef Botao<> BotaoChamada;


template<typename ...T>
void Notificador<T...>::notifica(T... args)
{
    for(auto &f : ouvintes) f(args...);
}


template<typename... T>
void Notificador<T...>::registraOuvinte(std::function<void(T...)> func)
{
    ouvintes.push_back(func);
}



template<typename T>
void Sensor<T>::set(T estado)
{
    _estado = estado;
    this->notifica(estado);
}


template<typename T>
bool Contador<T>::loop()
{
    auto now = std::chrono::steady_clock::now();
    if(_ativado && (std::chrono::time_point_cast<std::chrono::seconds>(now).time_since_epoch() - _sinc) >= timeout)
    {
        this->notifica(_msg.get());
        return true;
    }

    return false;
}


template<typename T>
void Contador<T>::reinicia(const T msg)
{
    auto now = std::chrono::steady_clock::now();
    _msg = std::make_unique<T>(msg);
    _sinc = std::chrono::time_point_cast<std::chrono::seconds>(now).time_since_epoch();
    _ativado = true;
}

template<>
void Contador<bool>::reinicia(void)
{
    auto now = std::chrono::steady_clock::now();
    _msg = std::make_unique<bool>(true);
    _sinc = std::chrono::time_point_cast<std::chrono::seconds>(now).time_since_epoch();
    _ativado = true;
}



#endif
