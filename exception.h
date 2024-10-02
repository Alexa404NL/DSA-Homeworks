#ifndef EXCEPTION_H
#define EXCEPTION_H

#endif //EXCEPTION_H


#include <iostream>
#include <exception>
#include <string>
using namespace std;

class nuevaException : public exception{
public:
    virtual const char *what() const throw(){
        return mensaje.c_str();
    }

    string mensaje;
    nuevaException(string m){
        mensaje = m;
    }

};