#include <andar.h>

/* Classe Andar */
Andar::Andar(int id_name){
    id = id_name;    
}

int Andar::get_id(){
    return id;
}

bool Andar::operator==( const Andar &right ) const
 {
    return ( *this == right );
}