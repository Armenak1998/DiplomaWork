#include "pin.h"
#include "net.h"
#include <QGraphicsScene>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////
// ! constructor baseviawier
///////////////////////////////////////////////////////////////////////////////////////////////
baseviawier::baseviawier(std::string name):m_name(name)
{}

////    ///////////////////////////////////////////////////////////////////////////////////////////
// ! baseviawier getName
///////////////////////////////////////////////////////////////////////////////////////////////
const std::string& baseviawier::getName() const
{
    return m_name;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! constructor via
    ///////////////////////////////////////////////////////////////////////////////////////////////
via::via(std::string name, int x, int y, Layer bagin, Layer end) : baseviawier( name ),
    QPoint(x, y), m_layer_bagin(bagin), m_layer_end(end)
{}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! via getRect
///////////////////////////////////////////////////////////////////////////////////////////////
QLine via::getRect()
{
   return QLine(rx(), ry(), rx(), ry());
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! via draw
///////////////////////////////////////////////////////////////////////////////////////////////
void via::draw(QGraphicsScene* scan, Layer _layer) const
{
    if ((_layer == m_layer_bagin) || (_layer == m_layer_end)) {
        QPen pen(Qt::cyan);
        scan->addRect(x(), y(), 0.5, 0.5, pen);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
// ! constructor wire
///////////////////////////////////////////////////////////////////////////////////////////////
wire::wire(std::string name, QPoint start, QPoint end, Layer layer) : baseviawier( name ),
    QLine(start, end), m_layer(layer)
{}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! wire getRect
///////////////////////////////////////////////////////////////////////////////////////////////
QLine wire::getRect()
{
    return QLine(p1(), p2());
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! wire draw
///////////////////////////////////////////////////////////////////////////////////////////////
void wire::draw(QGraphicsScene* scan ,Layer _layer) const
{
    if (m_layer == _layer) {
        QPen pen(Qt::red);
        if(_layer == Layer::LEYER_2) {
            pen.setColor(Qt::magenta);
        }
        if((x1() == x2()) && (y1() == y2())) {
            //scan->addRect(x1(), y1(), 1, 1, pen);
        } else {
            scan->addLine(*this, pen);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! constructor net
///////////////////////////////////////////////////////////////////////////////////////////////
net::net(std::string name, Pin* in, Pin* out) :
    m_name(name), m_in(in), m_out(out)
{}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! constructor Pin
///////////////////////////////////////////////////////////////////////////////////////////////
Pin* net::getIN() const
{
    return m_in;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! constructor Pin
///////////////////////////////////////////////////////////////////////////////////////////////
Pin* net::getOut() const
{
    return m_out;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! net getName
///////////////////////////////////////////////////////////////////////////////////////////////
const std::string& net::getName()const
{
    return m_name;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! net setAngle
///////////////////////////////////////////////////////////////////////////////////////////////
void net::setViaWier(baseviawier* _viawier)
{
    m_viawier.push_back(_viawier);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! net getViaWier
///////////////////////////////////////////////////////////////////////////////////////////////
std::vector<baseviawier*> net::getViaWier() const
{
    return m_viawier;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! net draw
///////////////////////////////////////////////////////////////////////////////////////////////
void net::draw(QGraphicsScene* scan, Layer _layer) const
{
    for(const auto item : m_viawier) {
        item->draw(scan, _layer);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
// ! randomnets createNets
///////////////////////////////////////////////////////////////////////////////////////////////
void randomnets::createNets()
{
    const std::vector<Pin>& vec = Pin::getAllPin();
    std::vector<Pin> vec_in;
    std::vector<Pin> vec_out;

    for(const auto& item : vec) {
        if(item.getDirection() == EAD::DIRECTION::IN) {
            vec_in.push_back(item);
        } else {
            vec_out.push_back(item);
        }
    }

    int size_in = vec_in.size();
    int size_out = vec_out.size();
    int i;
    int j;
    while((size_in > 0) && (size_out > 0)) {
        i = qrand();
        j = qrand();
        i %= size_in;
        j %= size_out;
        m_nets.push_back(new net("net_rand_1",&vec_in.at(i), &vec_out.at(j)));
        std::swap(vec_in.at(i),vec_in.at(--size_in));
        std::swap(vec_out.at(j),vec_out.at(--size_out));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! randomnets getNets
///////////////////////////////////////////////////////////////////////////////////////////////
std::vector<net*> randomnets::getNets()const
{
    return m_nets;
}