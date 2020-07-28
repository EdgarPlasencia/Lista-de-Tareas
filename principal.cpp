#include "principal.h"
#include "ui_principal.h"

#include <QStringList>
#include <QString>
#include <QDebug>
#include <QInputDialog>
#include <QStringList>
#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QDateEdit>
#include <QDate>
#include <QColor>
#include <QStyle>
#include <QBrush>
#include <QFileInfo>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);

    inicializar();

}

Principal::~Principal()
{
    delete ui;
}

void Principal::agregarTarea()
{
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);


    // Add some text above the fields

    form.addRow(new QLabel(tr("Datos de la tarea")));


    QString fields;




    QLineEdit *lineEdit = new QLineEdit(&dialog);
    QString label = QString(tr("Nombre:"));
    form.addRow(label, lineEdit);


    QComboBox *comboB=new QComboBox(&dialog);
    QString labelTipo=QString("Tipo");

    comboB->addItem(tr("Universidad"));
    comboB->addItem(tr("Trabajo"));
    comboB->addItem(tr("Varios"));
    form.addRow(labelTipo,comboB);
    //form.addRow(new QComboBox());

    QComboBox *comboBPrio=new QComboBox(&dialog);
    QString labelPrio=QString(tr("Prioridad"));

    comboBPrio->addItem(tr("Baja"));
    comboBPrio->addItem(tr("Media"));
    comboBPrio->addItem(tr("Alta"));
    form.addRow(labelPrio,comboBPrio);

    form.addRow(new QLabel(tr("Ingrese la Fecha")));
    QDateEdit *date=new QDateEdit(&dialog);
    QString labelDate=QString(tr("Fecha"));
    form.addRow(labelDate,date);

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    QString dialogNombre;
    QString dialogTipo;
    int dialogPrio;
    int prioridad=1;
    QDate dialogDate;

    if (dialog.exec() == QDialog::Accepted) {

    dialogNombre=lineEdit->text();
    dialogTipo=comboB->currentText();
    dialogPrio=comboBPrio->currentIndex();

    dialogDate=date->date();

    if(dialogPrio==0){
        prioridad=1;
    }else if(dialogPrio==1){
        prioridad=2;
    }else if(dialogPrio==2){
        prioridad=3;
    }

    }



   QDate fecha=dialogDate;


    int index=ui->outTareas->rowCount()+1;

    tarea.append(new Tarea(index,dialogNombre,dialogTipo,fecha,prioridad));



    int numero = tarea.at(index-1)->getNumero();
    QString numTarea= QString::number(numero);
    QString nombre = tarea.at(index-1)->getNombre();
    QString tipo=tarea.at(index-1)->getTipo();
    QString fechaTarea=tarea.at(index-1)->getfecha().toString("dd,MM,yyyy");




    int posicion = ui->outTareas->rowCount();
    ui->outTareas->insertRow(posicion);



    QBrush brochaVerde;
    QColor const verde(Qt::green);
    brochaVerde.setColor(verde);



    //QTableWidget::item{selection-background-color: red};


    ui->outTareas->setItem(posicion,0,new QTableWidgetItem(numTarea));
    ui->outTareas->setItem(posicion,1,new QTableWidgetItem(nombre));
    ui->outTareas->setItem(posicion,2,new QTableWidgetItem(tipo));
    ui->outTareas->setItem(posicion,3,new QTableWidgetItem(fechaTarea));

    if(dialogPrio==1){

    //ui->outTareas->setStyleSheet("background-color: green");

    }


    //LINEA PARA INGRESAR
    QString ingresarP;
    ingresarP=numTarea+";"+nombre+";"+tipo+";"+fechaTarea;
    //qDebug()<<ingresarP;



    QFile fileIn("ListaTareas.csv"), fileOut("textOut.csv");

    fileIn.open(QFile::ReadOnly); // check result
    fileOut.open(QFile::WriteOnly); // check result

    QTextStream streamIn(&fileIn), streamOut(&fileOut);
    const QChar delimeter = ';';

    while (!streamIn.atEnd())
    {
        QStringList list = streamIn.readLine().split(delimeter);

        streamOut<< list.join(delimeter)<< "\r\n";

        if (streamIn.atEnd()){

            streamOut <<ingresarP << "\r\n"; // or endl
        }
    }

    fileIn.close();
    fileOut.close();

    fileIn.remove(); // check result
    fileOut.rename(QFileInfo(fileIn).absoluteFilePath()); // check result



}

void Principal::inicializar()
{
    QStringList cabecera={tr("Numero"),tr("Nombre"),tr("Tipo"),tr("Fecha")};

    ui->outTareas->setColumnCount(4);

    ui->outTareas->setHorizontalHeaderLabels(cabecera);

    //SE OMITIO POR UN ERROR QList al cargar la informacion
    /*
    QFile archivo("ListaTareas.csv");

    if(archivo.open(QFile::ReadOnly)){

        QTextStream in(&archivo);
        while(!in.atEnd()){

            QStringList datos = in.readLine().split(";");
            //QStringList datos=linea.split(";");
            int codigo = datos[0].toInt();
            QString numero=QString::number(codigo);
            QString nombre=datos[1];
            QString tipo = datos[2];
            QDate fecha = QDate::fromString(datos[3],"dd/MM/yyyy");
            int prioridad = datos[4].toInt();
            //Crear productos
            tarea.append(new Tarea(codigo,nombre,tipo,fecha,prioridad));

            int posicion = ui->outTareas->rowCount();
            ui->outTareas->insertRow(posicion);

            ui->outTareas->setItem(posicion,0,new QTableWidgetItem(numero));
            ui->outTareas->setItem(posicion,1,new QTableWidgetItem(datos[1]));
            ui->outTareas->setItem(posicion,2,new QTableWidgetItem(datos[2]));
            ui->outTareas->setItem(posicion,3,new QTableWidgetItem(datos[3]));

        }


    }else{
        qDebug()<<"Error al abrir";

    }
    archivo.close();
    */

}

void Principal::archivar()
{

    QString numTarea;
    QString nombre;
    QString tipo;
    QString fechaTarea;

    //LINEA PARA INGRESAR
    QString ingresarP;
    ingresarP=numTarea+";"+nombre+";"+tipo+";"+fechaTarea;
    //qDebug()<<ingresarP;



    QFile fileIn("ListaTareas.csv"), fileOut("textOut.csv");

    fileIn.open(QFile::ReadOnly); // check result
    fileOut.open(QFile::WriteOnly); // check result

    QTextStream streamIn(&fileIn), streamOut(&fileOut);
    const QChar delimeter = ';';

    while (!streamIn.atEnd())
    {
        QStringList list = streamIn.readLine().split(delimeter);

        streamOut<< list.join(delimeter)<< "\r\n";

        if (streamIn.atEnd()){

            streamOut <<ingresarP << "\r\n"; // or endl
        }
    }

    fileIn.close();
    fileOut.close();

    fileIn.remove(); // check result
    fileOut.rename(QFileInfo(fileIn).absoluteFilePath()); // check result

}

void Principal::eliminar()
{

    QWidget *w = qobject_cast<QWidget *>(sender()->parent());
      if(w){
          int row = ui->outTareas->indexAt(w->pos()).row();
          ui->outTareas->removeRow(row);
          ui->outTareas->setCurrentCell(0, 0);
      }

    update();
}


void Principal::on_actionNuevaTarea_triggered()
{
    agregarTarea();
}

void Principal::on_actionFinalizarTarea_triggered()
{
    eliminar();
}

void Principal::on_actionEliminarTarea_triggered()
{
    eliminar();
}
