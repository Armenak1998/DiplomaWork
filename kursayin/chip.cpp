#include "cell.h"
#include "chip.h"
#include "net.h"
#include <QGraphicsRectItem>
#include <QRect>
#include <QGraphicsScene>
#include <QPen>
#include <iostream>
#include "routing.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////
// !
///////////////////////////////////////////////////////////////////////////////////////////////
QRect layer::sm_admissibility(20, 20, 9960, 9960);
QLine layer::sm_inLine(10, 4000, 10, 6000);
QLine layer::sm_outLine(9990, 4000, 9990, 6000);
///////////////////////////////////////////////////////////////////////////////////////////////
// ! constructor layer
///////////////////////////////////////////////////////////////////////////////////////////////
layer::layer(int v, int h, Orientation orientation, const std::vector<Pin*>& pins) :
    QGraphicsRectItem (0, 0, v, h), m_orientation(orientation)
{
    for (const auto& item : pins) {
        m_pins.push_back(item);
    }
//
//    for(int i = 0;i < ports_size; ++i) {
//        if (isCorectPlace(ports_list[i])) {
//            if (isRepeating(ports_list[i])) {
//                m_ports.push_back(ports_list[i]);
//            }
//        }
//    }
//    /*    if (!isCorectStatus()) {
//          throw();
//          }*/
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! layer isCorect
///////////////////////////////////////////////////////////////////////////////////////////////
bool layer::isCorect(Cell* _cell) const
{
    static int c_x = this->rect().x();
    static int c_y = this->rect().y();
    static int c_xw = this->rect().x() + this->rect().width();
    static int c_yh = this->rect().y() + this->rect().height();

    int x = _cell->x();
    int y = _cell->y();
    int xw = _cell->x() + _cell->width();
    int yh = _cell->y() + _cell->height();

    if ((c_x + 19) > x) {
        return false;
    }
    if ((c_y + 19) > y) {
        return false;
    }
    if ((c_xw - 19) < xw) {
        return false;
    }
    if ((c_yh - 19) < yh) {
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! layer isAllowed
///////////////////////////////////////////////////////////////////////////////////////////////
bool layer::isAllowed(Cell * _cell) const
{
    for(const auto& item : m_cells) {
        if (!item->isAllowed(*_cell)) {
            return false;
        }
    }
        return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! layer draw
///////////////////////////////////////////////////////////////////////////////////////////////
void layer::draw(QGraphicsScene* scan, Layer* arr, int count) const
{
    if (count != 0) {
    QPen pen1(Qt::white);
    pen1.setWidth(3);
    scan->addRect(this->rect(),pen1);
    //QPen pen(scan->foregroundBrush().color());
    scan->addRect(this->rect().x() + 10 , this->rect().y() + 10, this->rect().width() - 20, this->rect().height() - 20, pen1);
    //scan->addRect(this->rect().x() - 100 , this->rect().y() - 100, this->rect().x() + this->rect().width() + 200, this->rect().y() + this->rect().height() + 200, pen);
    //std::cout<<"x="<<this->rect().width() - 20<<"y="<<this->rect().height() - 20<<std::endl;
    for(int i = 0; i < count; ++i) {
        if (arr[i] == Layer::LEYER_1) {
            for(const auto& item : m_cells) {
                item->draw(scan);
            }
            //for(const auto& item : m_ports) {
            //    item->draw(scan);
            //}
        }
        for(const auto& item : m_nets) {
            item->draw(scan, arr[i]);
        }
    }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! layer setCells
///////////////////////////////////////////////////////////////////////////////////////////////
//void layer::setCells(cell_list* lists)
//{
//    for(const auto& item : m_cells) {
//            if(lists->intersect(item)) {
//                return ;
//            }
//    }
//    std::vector<Cell*> vec = lists->getList();
//    for(auto item : vec) {
//        m_cells.push_back(item);
//    }
//
    //std::cout<<m_cells.at(m_cells.size() - 1)->rect().x()<<" "<<m_cells.at(m_cells.size() - 1)->rect().y();

//QTextStream out(stdout);
//foreach(QString x, strings)
    //out <<m_cells.at(m_cells.size() - 1)->rect().x()<<" "<<m_cells.at(m_cells.size() - 1)->rect().y() << endl;
    //int size = m_cells.size() + lists->getList().size();
    //m_cells.resize(size + 1);
    //m_cells.insert(end(m_cells), begin(lists->getList()), end(lists->getList()));
    //m_cells.insert(m_cells.end(), lists->getList().begin(), lists->getList().end());
//}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! layer isCorectPlace
///////////////////////////////////////////////////////////////////////////////////////////////
//bool layer::isCorectPlace(port* _port)
//{
//    QLine line = layer::getInLine();
//    int gx1 = line.x1();
//    int gx2 = line.x2();
//    int gy1 = line.y1();
//    int gy2 = line.y2();
//    int x = _port->x();
//    int y = _port->y();
//    Status stat =_port->getStatus();
//
//    if (stat == Status::IN) {
//        if ((gx1 == x) && (gx2 == x) && (gy1 < y) && (gy2 > y)) {
//            return true;
//        }
//    } else {
//        line = layer::getOutLine();
//        gx1 = line.x1();
//        gx2 = line.x2();
//        gy1 = line.y1();
//        gy2 = line.y2();
//
//        if ((gx1 == x) && (gx2 == x) && (gy1 < y) && (gy2 > y)) {
//            return true;
//        }
//    }
//    return false;
//}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! layer isRepeating
///////////////////////////////////////////////////////////////////////////////////////////////
//bool layer::isRepeating(port* _port)
//{
//    for(const auto& item : m_ports) {
//        if ((item->x() == _port->x()) && (item->y() == _port->y())) {
//            return false;
//        }
//        if (item->getName() ==_port->getName()) {
//            return false;
//        }
//    }
//    return true;
//}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! layer isCorectStatus
///////////////////////////////////////////////////////////////////////////////////////////////
bool layer::isCorectStatus() const
{
    int in = 0;
    int out = 0;
    for(const auto& item : m_pins) {
        if (item->getDirection() == EAD::DIRECTION::IN) {
           ++in;
        }
        if (item->getDirection() == EAD::DIRECTION::OUT) {
           ++out;
        }
    }
    if ((in == 0) || (out == 0)) {
       return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! layer setNets
///////////////////////////////////////////////////////////////////////////////////////////////
void layer::setNets(std::vector<net*> vec)
{
    for(auto item : vec) {
        m_nets.push_back(item);
    }
}

void layer::setNet(net* net_)
{
    if (net_ != nullptr) {
        m_nets.push_back(net_);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
// ! layer setCell
///////////////////////////////////////////////////////////////////////////////////////////////
void layer::setCell(Cell* cell)
{
   if (isAllowed(cell)) {
       m_cells.push_back(cell);
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! layer getCells
///////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Cell*> layer::getCells() const
{
    return m_cells;
}


std::vector<net*> layer::getNets() const
{
    return m_nets;
}

QRect layer::getAdmissibility()
{
    return sm_admissibility;
}

QLine layer::getInLine()
{
    return sm_inLine;
}

QLine layer::getOutLine()
{
    return sm_outLine;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! constructor chip
///////////////////////////////////////////////////////////////////////////////////////////////
chip::chip(int v, int h, const std::vector<Pin*>& pins) :
    m_layer(v, h, Orientation::NONE, pins)
{}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! chip setCells
///////////////////////////////////////////////////////////////////////////////////////////////
//void chip::setCells(cell_list* lists)
//{
//    m_layer1.setCells(lists);
//}
//
///////////////////////////////////////////////////////////////////////////////////////////////
// ! chip setcell
///////////////////////////////////////////////////////////////////////////////////////////////
void chip::setCell(Cell* cell)
{
    m_layer.setCell(cell);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! chip draw
///////////////////////////////////////////////////////////////////////////////////////////////
void chip::draw(QGraphicsScene* scan, Layer* arr, int count) const
{
    m_layer.draw(scan, arr, count);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! chip rout
///////////////////////////////////////////////////////////////////////////////////////////////
void chip::rout()
{
    lee alg(&m_layer);
    alg.startleeAlgorithm();
}

void chip::setNets(std::vector<net*> vec)
{
    for(auto item : vec) {
        m_layer.setNet(item);
    }
 //   m_layer1.setNets(vec);
}


