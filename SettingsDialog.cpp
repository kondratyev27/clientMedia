#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

void SettingsDialog::setParams(const ServerParams &params)
{
    ui->hostWidget->setText(params.host);
    ui->portWidget->setValue(params.port);
}

ServerParams SettingsDialog::getParams()
{
    return {ui->hostWidget->text(), ui->portWidget->value()};
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
