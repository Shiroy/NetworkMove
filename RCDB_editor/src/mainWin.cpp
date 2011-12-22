#include "mainWin.h"
#include "editDialog.h"

#include <QFileDialog>

mainWin::mainWin() : QMainWindow()
{
    setupUi(this);
    m_lastId = 0;

    QStringList header_label;

    header_label << "ID" << "Type" << "Fichier";
    m_model = new QStandardItemModel(0, 3);
    m_model->setHorizontalHeaderLabels(header_label);
    view->setModel(m_model);

    connect(newRc, SIGNAL(triggered()), this, SLOT(newRessource()));
    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editRessource(QModelIndex)));
}

mainWin::~mainWin()
{

}

void mainWin::newRessource()
{
    EditDialog dialog(this, m_workingDir);
    connect(&dialog, SIGNAL(addRessource(int, QString)), this, SLOT(addRessource(int, QString)));
    dialog.exec();
}

void mainWin::on_changeWorkingDir_triggered()
{
    QString newDir = QFileDialog::getExistingDirectory(this, tr("Sélectionnez un repertoire de travail"));
    m_workingDir.setPath(newDir);
}

void mainWin::addRessource(int type, QString filename)
{
    m_model->appendRow(0);
    QModelIndex index = m_model->index(m_lastId, 0, QModelIndex());
    m_model->setData(index, m_lastId+1); //On commence à l'ID 1
    index = m_model->index(m_lastId, 1, QModelIndex());
    m_model->setData(index, type);
    index = m_model->index(m_lastId, 2, QModelIndex());
    m_model->setData(index, filename);
    m_lastId++;
}

void mainWin::editRessource(QModelIndex index)
{
    int row = index.row();
    QModelIndex rcIndex = m_model->index(row, 1, QModelIndex());
    int type = m_model->data(rcIndex).toInt();
    rcIndex = m_model->index(row, 2, QModelIndex());
    QString filename = m_model->data(rcIndex).toString();

    EditDialog dialog(this, m_workingDir, type, filename);
    dialog.exec();
}
