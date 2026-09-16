#include <QApplication>
#include <QWidget>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Fantasy In Hand - Combat Trace");
    QLabel label("Simple text", &window);
    window.show();

    return app.exec();
}