#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemDelegate>
#include <QComboBox>
#include <QDir>
#include "ui_mainWin.h"

class mainWin : public QMainWindow, private Ui::mainWin
{
    Q_OBJECT

    public:

    mainWin();
    ~mainWin();

    public slots:

    void newRessource();
    void on_changeWorkingDir_triggered();

    private:

    QStandardItemModel *m_model;
    QDir m_workingDir;
};

#endif
