#include "mainWin.h"
#include "editDialog.h"

#include <QFileDialog>

mainWin::mainWin() : QMainWindow()
{
    setupUi(this);

    QStringList header_label;

    header_label << "ID" << "Type de ressource" << "Chemin de la ressource";
    m_model = new QStandardItemModel(0, 3);
    m_model->setHorizontalHeaderLabels(header_label);
    view->setModel(m_model);

    connect(newRc, SIGNAL(triggered()), this, SLOT(newRessource()));
}

mainWin::~mainWin()
{

}

void mainWin::newRessource()
{
    EditDialog dialog(this, m_workingDir);
    dialog.exec();
}

void mainWin::on_changeWorkingDir_triggered()
{
    QString newDir = QFileDialog::getExistingDirectory(this, tr("Sélectionnez un repertoire de travail"));
    m_workingDir.setPath(newDir);
}
