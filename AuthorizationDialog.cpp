#include "AuthorizationDialog.h"
#include "ui_AuthorizationDialog.h"

AuthorizationDialog::AuthorizationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationDialog)
{
    ui->setupUi(this);
}

AuthorizationDialog::~AuthorizationDialog()
{
    delete ui;
}

QString AuthorizationDialog::userName()
{
    return ui->loginWidget->text();
}

QString AuthorizationDialog::password()
{
    return ui->passwordWidget->text();
}
