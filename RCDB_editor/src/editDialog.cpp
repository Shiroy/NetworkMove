#include "editDialog.h"
#include <QFileDialog>

EditDialog::EditDialog(QWidget *parent, QDir workingDir, int rc_type, QString filename) : QDialog(parent), m_workingDir(workingDir)
{
    setupUi(this);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptClicked()));
    type->setCurrentIndex(rc_type);
    file->setText(filename);
}

void EditDialog::acceptClicked()
{
    emit addRessource(type->currentIndex(), file->text());
}

void EditDialog::on_browse_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Sélectionner un fichier"), file->text());

    QString relativePath = m_workingDir.relativeFilePath(filename);
    file->setText(relativePath);
}


