#include "tarea.h"

Tarea::Tarea(QObject *parent) : QObject(parent)
{

}

Tarea::Tarea()
{
    numero=0;
    nombre="SinNombre";
    fecha= QDate(01,01,01);
    prioridad=1;
    tipo="SinDefinir";
}

Tarea::Tarea(int numero, QString nombre, QString tipo, QDate fecha,int prioridad)
{
    this->numero=numero;
    this->nombre=nombre;
    this->fecha=fecha;
    this->prioridad=prioridad;
    this->tipo=tipo;
}

int Tarea::getNumero()
{
    return numero;
}

QString Tarea::getNombre()
{
    return nombre;
}

QDate Tarea::getfecha()
{
    return fecha;
}

QString Tarea::getTipo()
{
    return tipo;
}
