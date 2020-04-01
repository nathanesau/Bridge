#pragma once

#include "stdafx.h"

class MainWidget;

class MainWindow : public QMainWindow
{
    MainWidget* mainWidget;

    QAction* currViewAction;

public:
    MainWindow(QWidget* parent = nullptr);

    void fileMenuChanged();
    void viewMenuChanged();
};