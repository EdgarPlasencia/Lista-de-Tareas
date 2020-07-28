#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include "tarea.h"
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

    void agregarTarea();
    void inicializar();
    void archivar();
    void eliminar();

private slots:
    void on_actionNuevaTarea_triggered();

    void on_actionFinalizarTarea_triggered();

    void on_actionEliminarTarea_triggered();

private:
    Ui::Principal *ui;

    QList<Tarea*>tarea;
};
#endif // PRINCIPAL_H
