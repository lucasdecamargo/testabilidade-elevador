#ifndef COMPONENTES_H
#define COMPONENTES_H

#include <list>
#include <functional>
#include <string>

typedef std::string Id;

class Andar {};

template<typename T, typename R = void>
class Notificador
{
public:
    Notificador(){};
    ~Notificador(){};

    void notifica(T obj);
    void registraOuvinte(std::function<R(T)>& func);
    void removeOuvinte(std::function<R(T)>& func);

protected:
    std::list< std::function<R(T)> > ouvintes;
};

template<typename T, typename R = void>
class Sensor : public Notificador<T,R>
{
public:
    Sensor(Id id);

    void ativa();
    void desativa();
    bool estado() { return _estado; }
    const Id id() { return _id; }

private:
    Id _id;
    bool _estado;
};

typedef Sensor<bool> SensorBloqueio;
typedef Sensor<bool> SensorPresenca;

class SensorAndar : public Sensor<Andar>
{
public:
    SensorAndar(Id id) : Sensor(id) {}

    const Andar get() { return andar; }
    void set(Andar a) { andar = a; }

protected:
    Andar andar;
};

template<typename T=void>
class Contador : public Notificador<T>
{
public:
    Contador(unsigned timeout=15);

    void reinicia(T msg);

protected:
    Andar andar;

private:
    T _msg;
};

template<typename T=void>
class Botao : public Notificador<T>
{
public:
    Botao(Id id);

    void dispara(T msg);

private:
    Id _id;
};

typedef Botao<void> BotaoDestino;
typedef Botao<void> BotaoEmergencia;
typedef Botao<void> BotaoChamada;


#endif
