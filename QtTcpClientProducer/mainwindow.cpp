#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  //tcpConnect();
    // Desativa botões de ação até que a conexão seja estabelecida
  ui->pushButton_parar->setEnabled(false);
  ui->pushButton_comecar->setEnabled(false);
  ui->pushButton_desconectar->setEnabled(false);
}
// Método para estabelecer uma conexão TCP com o servidor
void MainWindow::tcpConnect(){
  if(ui->textEditIPServer->toPlainText()==""){
    socket->connectToHost("127.0.0.1",1234);
      ui->textEditIPServer->setText("127.0.0.1");
  }
  else{
    socket->connectToHost(ui->textEditIPServer->toPlainText(),1234);
  }
  // Verifica se a conexão foi estabelecida com sucesso
  if(socket->waitForConnected(3000)){
    ui->labelConectado->setText("Conectado com sucesso");
    ui->pushButton_comecar->setEnabled(true);
    ui->pushButton_desconectar->setEnabled(true);
    ui->pushButton_conectar->setEnabled(false);
  }
  else{
    ui->labelConectado->setText("Falha na Conexão");
  }
}

void MainWindow::timerEvent(QTimerEvent *event){
    putData();
}
// Chamado periodicamente pelo temporizador para enviar dados para o servidor

void MainWindow::putData(){
  QDateTime datetime;
  QString str;
  qint64 msecdate;

  if(socket->state()== QAbstractSocket::ConnectedState){
    msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
    str = "set "+ QString::number(msecdate) + " " +
        QString::number(ui->sliderMin->value()+rand()%(ui->sliderMax->value()-ui->sliderMin->value()+1))+"\r\n";
// Envia dados para o servidor
    socket->write(str.toStdString().c_str());
    ui->listWidget->addItem(str);
  }
}

void MainWindow::conectar(){
  tcpConnect();
}

void MainWindow::desconectar(){
  socket->disconnectFromHost();
  ui->labelConectado->setText("Desconectado");
  if(estado == 1){
    parar();
  }
  // Atualiza o estado dos botões
  ui->pushButton_conectar->setEnabled(true);
  ui->pushButton_desconectar->setEnabled(false);
  ui->pushButton_comecar->setEnabled(false);
  ui->pushButton_parar->setEnabled(false);
}
// Chamado quando o valor mínimo do slider é alterado
void MainWindow::setMin(){
  ui->sliderMax->setMinimum(ui->sliderMin->value());
}
// Chamado quando o valor máximo do slider é alterado
void MainWindow::setMax(){
  ui->sliderMin->setMaximum(ui->sliderMax->value());
}
// Chamado quando o botão "Começar" é clicado
void MainWindow::comecar(){
  temporizador = startTimer(ui->sliderTempo->value()*1000);
  estado = 1;
  ui->pushButton_parar->setEnabled(true);
  ui->pushButton_comecar->setEnabled(false);
}

void MainWindow::parar(){
  killTimer(temporizador);
  estado = 0;
  ui->pushButton_parar->setEnabled(false);
  ui->pushButton_comecar->setEnabled(true);
}

void MainWindow::alteratempo()
{
    if(estado == 1){
      killTimer(temporizador);
      temporizador = startTimer(ui->sliderTempo->value()*1000);
    }
}

MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}
