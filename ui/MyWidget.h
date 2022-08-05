#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "scene/scene.h"
//#include "pathtracer.h"

class MyWidget : public QMainWindow
{
    Q_OBJECT
public:

    QGraphicsScene* scene_TO_DRAW;
    QApplication* a;




  MyWidget(QWidget *parent = NULL, QApplication* ain = NULL) : QMainWindow(parent), a(ain)
  {
    this->resize(820, 820);
    this->setWindowTitle("J. Alex Mina's Path Tracer");

    scene_TO_DRAW = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene_TO_DRAW);
    setCentralWidget(view);


  }

public slots:
  void buttonClicked()
  {
      counter++;
      label->setText(QString("Click #%1").arg(counter));
      //this->close();
  }

private:
  void createMenus()
  {
    QMenuBar *bar = menuBar();
    QMenu *fileMenu = bar->addMenu(tr("&File"));
    fileMenu->addAction(new QAction("Open", this));
    fileMenu->addAction(new QAction("Close", this));
  }
private:
  int counter;
  QLabel* label;
};

#endif // MYWIDGET_H
