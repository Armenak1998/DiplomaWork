#include "GraphicsView.h"
#include <QGraphicsScene>
#include <QWheelEvent>
#include <iostream>

GraphicsView::GraphicsView(QGraphicsScene* scene) :
    QGraphicsView(scene)
{
    setBackgroundBrush(QBrush(Qt::black));
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
  if (event->delta() > 0) {
      scale(1.25, 1.25);
  } else {
      scale(0.8, 0.8);
  }
}
