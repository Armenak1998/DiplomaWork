#pragma once

#include<QGraphicsRectItem>
#include<vector>
#include <net.h>

class Cell;
//class cell_list;
//class port;
class net;

enum class Orientation {HORIZONTAL, VERTICAL, NONE};
///
/// class layer
///
class layer : public QGraphicsRectItem
{
private:
    static QRect sm_admissibility;
    static QLine sm_inLine;
    static QLine sm_outLine;
    Orientation m_orientation;
    std::vector<Cell*> m_cells;
    std::vector<Pin*> m_pins;
    std::vector<net*>  m_nets;

private:
    bool isCorect(Cell* _pin) const;
    bool isAllowed(Cell * _cell) const;

public:
    layer(int v, int h, Orientation orientation, const std::vector<Pin*>& pins);
    //bool isCorectPlace(Pin* _pin);
    //bool isRepeating(Pin* pin);
    void draw(QGraphicsScene* scan, Layer* arr, int count) const;
//    void setCells(cell_list* lists);
    void setCell(Cell* cell);
    std::vector<Cell*> getCells() const;
    std::vector<net*> getNets() const;
    void setNets(std::vector<net*> vec);
    void setNet(net* net_);
    bool isCorectStatus() const;
    static QRect getAdmissibility();
    static QLine getInLine();
    static QLine getOutLine();
};

///
/// class chip
///
class chip
{
private:
    layer m_layer;

public:
    chip(int v, int h, const std::vector<Pin*>& pins);
//    void setCells(cell_list* lists);
    void setCell(Cell* cell);
    void draw(QGraphicsScene* scan, Layer* arr, int count) const;
    void rout();
    void setNets(std::vector<net*> vec);

};
