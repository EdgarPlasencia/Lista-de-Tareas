#ifndef TAREA_H
#define TAREA_H

#include <QObject>
#include <QWidget>
#include <QDate>

class Tarea : public QObject
{
    Q_OBJECT

public:
    explicit Tarea(QObject *parent = nullptr);
    Tarea();
    Tarea(int numero,QString nombre, QString tipo, QDate fecha,int prioridad);
    int getNumero();
    QString getNombre();
    QDate getfecha();
    QString getTipo();

private:
    int numero;
    QString nombre;
    QDate fecha;
    int prioridad;
    QString tipo;


signals:

};

#endif // TAREA_H
