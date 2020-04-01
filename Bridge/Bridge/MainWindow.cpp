#include "stdafx.h"
#include "MainWindow.h"
#include "MainWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidget = new MainWidget();
    setCentralWidget(mainWidget);

    QMenu* fileMenu = this->menuBar()->addMenu("File");
    QMenu* viewMenu = this->menuBar()->addMenu("View");

    for (auto& fileAction : { "Open Dataset" })
    {
        QAction* action = fileMenu->addAction(QString::fromStdString(fileAction));
        connect(action, &QAction::triggered, this, &MainWindow::fileMenuChanged);
    }

    for (auto& viewAction : {"All", "Schedule", "Other" })
    {
        QAction* action = viewMenu->addAction(QString::fromStdString(viewAction));
        action->setCheckable(true);
        connect(action, &QAction::triggered, this, &MainWindow::viewMenuChanged);

        if (action->text() == QString("All"))
        {
            currViewAction = action;
            currViewAction->setChecked(true);
        }
    }

    resize(700, 500);
    setWindowTitle("Bridge");
}

void MainWindow::fileMenuChanged()
{
    auto action = dynamic_cast<QAction*>(QObject::sender());
    QString actionName = action->text();

    if (actionName == "Open Dataset")
    {
        mainWidget->openDataset();
    }
}

void MainWindow::viewMenuChanged()
{
    auto action = dynamic_cast<QAction*>(QObject::sender());
    QString actionName = action->text();

    currViewAction->setChecked(false);
    currViewAction = action;
    action->setChecked(true);

    mainWidget->setObjectCategory(actionName);
}