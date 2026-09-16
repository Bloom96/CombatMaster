#pragma once
#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    QListWidget* sidebar;
    QStackedWidget* content;
};