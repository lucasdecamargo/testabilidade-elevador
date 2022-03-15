#ifndef ANDAR_H
#define ANDAR_H


/* Classe Andar */
class Andar{
    public:
        Andar(int);
        int get_id();
        bool operator==( const Andar &right ) const;

    private:
        int id;
};

#endif