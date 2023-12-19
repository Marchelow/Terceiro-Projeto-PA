#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
// Cria uma instância da classe QApplication, que é necessária para a execução de aplicativos Qt.
  QApplication a(argc, argv);
  MainWindow w;
  w.show();   // Exibe a janela principal.

  return a.exec();
}
