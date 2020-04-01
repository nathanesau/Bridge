#pragma once

#include "stdafx.h"

enum NameDialogType
{
    RENAME_EXISTING_OBJECT,
    CREATE_NEW_OBJECT
};

class NameDialog : public QDialog
{
    QLineEdit* name;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* mainLayout;

    void setWindowTitle(NameDialogType dialogType);

public:
    NameDialog(NameDialogType dialogType, QWidget *parent = nullptr);

    QString getName() const;
};