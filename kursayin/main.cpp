#include <QApplication>
#include "Window.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window* window = new Window();
    window->showMaximized();

    return a.exec();
}
