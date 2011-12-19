#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include "ui_mainWin.h"

class mainWin : public QMainWindow, private Ui::mainWin
{
    Q_OBJECT
    public:

    mainWin();
    ~mainWin();

};

#endif
