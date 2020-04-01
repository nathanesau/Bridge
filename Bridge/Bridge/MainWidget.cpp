#include "stdafx.h"
#include "MainWidget.h"

#include "QuantLibScheduleWidget.h"
#include "NameDialog.h"

struct QActionWithIndex : public QAction
{
    QPersistentModelIndex index;
    QActionWithIndex(QPersistentModelIndex index) : QAction(), index(index) {}
};

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Bridge.db");
    db.open();

    model = new QSqlTableModel(nullptr);
    model->setTable("Objects");
    model->setFilter("");
    model->select();
    
    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->verticalHeader()->setVisible(false);
    tableView->horizontalHeader()->setStretchLastSection(true);

    connect(tableView, &QTableView::doubleClicked, this, &MainWidget::tableViewDoubleClicked);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tableView);

    setLayout(mainLayout);
}

void MainWidget::openDataset()
{
    QString dbName = QFileDialog::getOpenFileName(this, tr("Open Dataset"), "", tr("Database Files (*.db)"));

    if (!dbName.isEmpty())
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbName);
        db.open();

        model->select();

        tableView->update();
    }
}

void MainWidget::setObjectCategory(QString category)
{
    QString filter = category == QString("All") ? "" : QString("category = \"%1\"").arg(category);
    model->setFilter(filter);
    model->select();

    tableView->update();
}

void MainWidget::tableViewDoubleClicked(const QModelIndex &index)
{
    QuantLibScheduleWidget *widget = new QuantLibScheduleWidget(model->data(index).toString(), this);
    widget->show();
}

void MainWidget::contextMenuEvent(QContextMenuEvent* event)
{
    QPoint pos = QWidget::mapFromParent(event->pos());
    QPersistentModelIndex index = tableView->indexAt(pos);

    if (index.isValid())
    {
        QActionWithIndex editAction(index);
        editAction.setText("Edit Object");
        connect(&editAction, &QAction::triggered, this, &MainWidget::editObject);

        QActionWithIndex renameAction(index);
        renameAction.setText("Rename Object");
        connect(&renameAction, &QAction::triggered, this, &MainWidget::renameObject);

        QMenu menu(this);
        menu.addAction(&editAction);
        menu.addAction(&renameAction);
        menu.exec(event->globalPos());
    }
    else
    {
        QAction createAction;
        createAction.setText("Create Object");
        connect(&createAction, &QAction::triggered, this, &MainWidget::createObject);

        QMenu menu(this);
        menu.addAction(&createAction);
        menu.exec(event->globalPos());
    }
}

void MainWidget::createObject()
{
    NameDialog nameDialog(NameDialogType::CREATE_NEW_OBJECT);
    
    if (nameDialog.exec())
    {
        QString objectName = nameDialog.getName();

        QuantLibScheduleWidget *scheduleWidget = new QuantLibScheduleWidget(objectName, this);
        scheduleWidget->show();
    }
}   

void MainWidget::editObject()
{
    auto action = dynamic_cast<QActionWithIndex*>(QObject::sender());
    QuantLibScheduleWidget* scheduleWidget = new QuantLibScheduleWidget(model->data(action->index).toString(), this);
    scheduleWidget->show();
}

void MainWidget::renameObject()
{
    auto action = dynamic_cast<QActionWithIndex*>(QObject::sender());

    NameDialog nameDialog(NameDialogType::RENAME_EXISTING_OBJECT);

    if (nameDialog.exec())
    {
        QString objectName = nameDialog.getName();

        model->setData(action->index, objectName);
        tableView->update();
    }
}
