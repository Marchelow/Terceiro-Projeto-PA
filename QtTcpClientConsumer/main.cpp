#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show(); // Exibe a janela principal.

  return a.exec(); // Inicia o loop de eventos da aplicacao. 
}
