#ifndef EXCECOES_H
#define EXCECOES_H

#include <exception>
#include <stdexcept>

namespace elevador{
namespace exc{

typedef std::invalid_argument argumento_invalido;

struct porta_bloqueada : public std::exception
{
	const char * what () const throw ()
    {
    	return "A porta não pode ser fechada enquanto estiver bloqueada.";
    }
};

}
}

#endif