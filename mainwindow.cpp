#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int i,j;
    for(i=0;i<6;i++){
        for(j=0;j<6;j++){
        QTableWidgetItem *newItem = new QTableWidgetItem;
        ui->board->setItem(i, j, newItem);
        }
        ui->board->item(i,0)->setBackground(Qt::red);
    }        
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTableWidgetItem *MainWindow::find(int i)//returns the "i" row's red item
{
    int j;

    for(j=0;j<6;j++){
        if(ui->board->item(i,j)->background()==Qt::red){
            return ui->board->item(i,j);
        }
    }
    return nullptr;
}

bool MainWindow::attack(QTableWidgetItem *queen)//verifys if it's attacking other queens
{
    //vertical
    int i;
    for(i=0;i<6;i++){
        if(queen->row()==i)continue;
        if(ui->board->item(i,queen->column())->background()==queen->background())
            return true;
    }
    //diagonal
    while(ui->board->item(queen->row()-1,queen->column()-1)){//up left
        if(ui->board->item(queen->row()-1,queen->column()-1)->background()==queen->background())
            return true;
    }
    while(ui->board->item(queen->row()-1,queen->column()+1)){//up right
        if(ui->board->item(queen->row()-1,queen->column()+1)->background()==queen->background())
            return true;
    }
    while(ui->board->item(queen->row()+1,queen->column()-1)){//down left
        if(ui->board->item(queen->row()+1,queen->column()-1)->background()==queen->background())
            return true;        
    }
    while(ui->board->item(queen->row()+1,queen->column()+1)){//down right
        if(ui->board->item(queen->row()+1,queen->column()+1)->background()==queen->background())
            return true;
    }
    return false;
}

bool MainWindow::move(QTableWidgetItem *queen)//moves the item
{
    if(queen->column()==5){
        ui->board->item(queen->row(),0)->setBackground(queen->background());
        ui->board->item(queen->row(),queen->column())->setBackground(Qt::white);
        return true;}//returns true if it's the last column
    ui->board->item(queen->row(),queen->column()+1)->setBackground(queen->background());
    ui->board->item(queen->row(),queen->column())->setBackground(Qt::white);
    return false;
}


void MainWindow::on_start_released()
{
    bool f1=0,f2=0,f3=0,f4=0,f5=0;
    int cont=0;

    while(attack(find(0))&&attack(find(1))&&attack(find(2))&&attack(find(3))&&attack(find(4))&&attack(find(5))){
                cont++;f1=f2=f3=f4=f5=0;
            f1=move(find(0));ui->board->show();
                if(f1){                
                //moves the next queen
                f2=move(find(1));
                    if(f2){
                    //moves the next queen
                    f3=move(find(2));
                        if(f3){
                            //moves the next queen
                            f4=move(find(3));
                            if(f4){
                                //moves the next queen
                                f5=move(find(4));
                                if(f5){
                                    //moves the next queen
                                    move(find(5));
                                }
                            }
                        }
                    }
            }
    }
}
