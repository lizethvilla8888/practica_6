#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <conio.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    h_limit = 2000;//mi pantalla es 1920 x 1080
    v_limit = 1000;
    dt = 0.1;

    timer = new QTimer(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-h_limit/2,-v_limit/2,h_limit,v_limit);

    ui->graphicsView->setScene(scene);
    ui->centralwidget->adjustSize();

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setWindowTitle("Sistema interplanetario");

    timer->stop();
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

    cantidad = on_boton_cantidad_planetas_2_clicked();
    for (int i = 0 ; i < cantidad ;i++){
        on_ingresar_datos_clicked();
        qDebug ()<< "Agrego "<<i;
    }

    for (int i=0;i<bars.size() ;i++ ) {
        bars.at(i)->actualizar(dt);
        scene->addItem(bars.at(i));
        qDebug ()<< "cuerpo agregado a pantalla";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete scene;
}

void MainWindow::actualizar()
{
    for (int i=0;i<bars.size() ;i++ ) {
        for (int j=0;j<bars.size() ;j++ ) {
            if(i!=j){
                bars.at(i)->getEsf()->acelerar(bars.at(j)->getEsf()->getPX(),bars.at(j)->getEsf()->getPY(),bars.at(j)->getEsf()->getMasa());
                bars.at(i)->actualizar(dt);
            }
        }
    }
}

void MainWindow::on_inicio_clicked()
{
    timer->start(dt);
}

void MainWindow::on_pausa_clicked()
{
    timer->stop();
}

void MainWindow::on_ingresar_datos_clicked()
{
    double x= ui->posi_x->text().toDouble();
    double y= ui->posi_y->text().toDouble();
    double vx = ui->velocidad_x->text().toDouble();
    double vy = ui->velocidad_y->text().toDouble();
    double radio = ui->radio_line->text().toDouble();
    double masa = ui->masa->text().toDouble();

    bars.push_back(new cuerpograf(x,y,vx,vy,masa,radio));
    //scene->addItem(bars.back());

}

int MainWindow::on_boton_cantidad_planetas_2_clicked()
{
    int contador = 0;
    int num = 0;
    if (contador == 0){
        num = ui->can_planetas->text().toInt();
        qDebug() << num;
        contador ++;
        qDebug() << "contador == 0";
    }
    if (contador > 0){
        for (int idx = 0; idx < bars.size(); ) {
            bars.removeAt(idx);
            qDebug() << "contador > 0";
    }
    }
    return num;
}
