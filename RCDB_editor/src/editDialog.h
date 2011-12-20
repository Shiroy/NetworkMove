#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include <QDir>
#include "ui_editDialog.h"

class EditDialog : public QDialog, private Ui::editDialog
{
    Q_OBJECT

    public:

    EditDialog(QWidget *parent = 0, QDir workingDir = QDir::rootPath(), int type = 0, QString filename = QString());

    signals:

    void addRessource(int type, QString relativePath);

    private slots:

    void acceptClicked();
    void on_browse_clicked();

    private:

    QDir m_workingDir;
};

#endif
