#include "mainwindow.h"
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    sidebar = new QListWidget(this);
    sidebar->addItem("Combat");
    sidebar->addItem("World");
    sidebar->addItem("Session");
    sidebar->addItem("Character");

    content = new QStackedWidget(this);
    content->addWidget(new QLabel("Combat view goes here"));
    content->addWidget(new QLabel("World view goes here"));
    content->addWidget(new QLabel("Session view goes here"));
    content->addWidget(new QLabel("Character view goes here"));

    connect(sidebar, &QListWidget::currentRowChanged,
            content, &QStackedWidget::setCurrentIndex);

    QWidget* central = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(central);
    layout->addWidget(sidebar);
    layout->addWidget(content);

    setCentralWidget(central);
}