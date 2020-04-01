#include "stdafx.h"
#include "NameDialog.h"

NameDialog::NameDialog(NameDialogType dialogType, QWidget* parent) :
    QDialog(parent)
{
    name = new QLineEdit();
 
    okButton = new QPushButton();
    okButton->setText("OK");
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

    cancelButton = new QPushButton();
    cancelButton->setText("Cancel");
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(name);
    mainLayout->addLayout(buttonLayout);

    setWindowTitle(dialogType);
    setLayout(mainLayout);
    resize(350, 100);
}

void NameDialog::setWindowTitle(NameDialogType dialogType)
{
    switch (dialogType)
    {
    case NameDialogType::CREATE_NEW_OBJECT:
        QDialog::setWindowTitle("Create new object");
        break;
    case NameDialogType::RENAME_EXISTING_OBJECT:
        QDialog::setWindowTitle("Rename existing object");
        break;
    }
}

QString NameDialog::getName() const
{
    return name->text();
}