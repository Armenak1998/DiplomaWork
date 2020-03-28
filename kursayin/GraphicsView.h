#include <QGraphicsView>

class QGraphicsScene;

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QGraphicsScene* scene);
private:
    void wheelEvent(QWheelEvent *event);
};
