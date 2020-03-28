#include "Window.h"
#include <QGridLayout>
#include <QGraphicsScene>
#include "GraphicsView.h"
#include <QPushButton>

#include "chip.h"
#include "pin.h"
#include "cell.h"
#include "net.h"
#include "routing.h"


Window::Window() : QMainWindow()
{
    setWindowTitle("optimus");
    QWidget* widget = new QWidget(this);
    m_gridLayout = new QGridLayout(widget);
    widget->setLayout(m_gridLayout);
    setCentralWidget(widget);

    m_scene = new QGraphicsScene(this);
    m_graphicsView = new GraphicsView(m_scene);
    //m_scene->setForegroundBrush(Qt::black);
    m_gridLayout->addWidget(m_graphicsView, 0, 2, 20, 20);

    //QPen pen(Qt::red);
    //pen.setWidth(5);
    //m_scene->addRect(0,0,100,50,pen);

    m_check_layer1 = false;
    m_check_layer2 = false;
    m_check_layer3 = false;

    m_layer1 = new QPushButton(widget);
    m_layer1->setText("Layer1");
    m_layer1->setStyleSheet("background-color:red;");
    m_gridLayout->addWidget(m_layer1, 0, 0, 1, 1);
    QObject::connect(m_layer1, SIGNAL(clicked()), this, SLOT(clickLayer1()));

    m_layer2 = new QPushButton(widget);
    m_layer2->setText("Layer2");
    m_layer2->setStyleSheet("background-color:red;");
    m_gridLayout->addWidget(m_layer2, 1, 0, 1, 1);
    QObject::connect(m_layer2, SIGNAL(clicked()), this, SLOT(clickLayer2()));

    m_layer3 = new QPushButton(widget);
    m_layer3->setText("Layer3");
    m_layer3->setStyleSheet("background-color:red;");
    m_gridLayout->addWidget(m_layer3, 2, 0, 1, 1);
    QObject::connect(m_layer3, SIGNAL(clicked()), this, SLOT(clickLayer3()));

    m_lee = new QPushButton(widget);
    m_lee->setText("Lee");
    m_gridLayout->addWidget(m_lee, 3, 0, 1, 1);
    QObject::connect(m_lee, SIGNAL(clicked()), this, SLOT(clickLee()));
    creatDesignet();
}


void Window::creatDesignet()
{
    //m_chip = new chip();
    //std::vector<Pin*> pins = {
    //    new Pin(),
}

void Window::updateGui() {
    m_scene->clear();
    Layer* _layer = new Layer[3];
    int n = 0;

    if (m_check_layer1) {
        _layer[n++] = Layer::LEYER_1;
    }
    if (m_check_layer2) {
        _layer[n++] = Layer::LEYER_2;
    }
    if (m_check_layer3) {
        _layer[n++] = Layer::LEYER_3;
    }

    m_chip->draw(m_scene, _layer, n);
    delete[] _layer;
}

void Window::clickLayer1()
{
    m_layer1->setAutoFillBackground(true);
    if (!m_check_layer1) {
        m_check_layer1 = true;
        m_layer1->setStyleSheet("background-color:green;");
    } else {
        m_check_layer1 = false;
        m_layer1->setStyleSheet("background-color:red;");
    }
    m_layer1->show();
    updateGui();
}

void Window::clickLayer2()
{
    m_layer3->setAutoFillBackground(true);
    if (!m_check_layer2) {
        m_check_layer2 = true;
        m_layer2->setStyleSheet("background-color:green;");
    } else {
        m_check_layer2 = false;
        m_layer2->setStyleSheet("background-color:red;");
    }
    m_layer2->show();
    updateGui();
}

void Window::clickLayer3()
{
    m_layer3->setAutoFillBackground(true);
    if (!m_check_layer3) {
        m_check_layer3 = true;
        m_layer3->setStyleSheet("background-color:green;");
    } else {
        m_check_layer3 = false;
        m_layer3->setStyleSheet("background-color:red;");
    }
    m_layer3->show();
    updateGui();
}

void Window::clickLee()
{
    this->setCursor(Qt::WaitCursor);
    m_chip->rout();
    updateGui();
    this->setCursor(Qt::ArrowCursor);
}
