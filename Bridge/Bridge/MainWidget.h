#pragma once

#include "stdafx.h"
//#include "TableView.h"

class MainWidget : public QWidget
{
    Q_OBJECT

    QSqlTableModel* model;

    QTableView* tableView;
    QVBoxLayout* mainLayout;

public:
    MainWidget(QWidget* parent = nullptr);

    void openDataset();
    void setObjectCategory(QString category);

public slots:
    void tableViewDoubleClicked(const QModelIndex &index);
    void contextMenuEvent(QContextMenuEvent* event);
    void createObject();
    void editObject();
    void renameObject();
};