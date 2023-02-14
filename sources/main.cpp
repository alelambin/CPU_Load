#include <QApplication>
#include "../headers/mainwidget.h"

int main(int argc, char *argv[]) {
    try {
        QApplication app(argc, argv);

        MainWidget mainWidget;
        mainWidget.resize(800, 600);
        mainWidget.setWindowTitle("CPU Load");
        mainWidget.setWindowIcon(QIcon(":/img/icon.png"));
        mainWidget.show();

        return app.exec();
    } catch (std::exception &exception) {
        qDebug() << exception.what() << '\n';
        return -1;
    }
}
