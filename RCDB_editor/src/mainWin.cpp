#include "mainWin.h"
#include "editDialog.h"

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
    EditDialog dialog(this, QDir::rootPath(), 1, "Essai");
    dialog.exec();
}
