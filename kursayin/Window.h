#include <QMainWindow>

class QGridLayout;
class QGraphicsScene;
class GraphicsView;
class QPushButton;
class chip;

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window();

public:
    void updateGui();

private slots:
    void clickLayer1();
    void clickLayer2();
    void clickLayer3();
    void clickLee();

private:
    void creatDesignet();

private:
    QGridLayout*    m_gridLayout;
    GraphicsView*  m_graphicsView;
    QGraphicsScene* m_scene;

    //check for layer
    bool m_check_layer1 : 1;
    bool m_check_layer2 : 1;
    bool m_check_layer3 : 1;

    //button
    QPushButton* m_layer1;
    QPushButton* m_layer2;
    QPushButton* m_layer3;
    QPushButton* m_lee;

    //membrs
    chip* m_chip;
};
