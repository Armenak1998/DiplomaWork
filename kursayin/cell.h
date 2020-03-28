#pragma once

#include<QGraphicsRectItem>
#include <QRect>
#include<vector>
#include<string>

#include "LibObject.h"
#include "pin.h"

class QGraphicsRectItem;
class QGraphicsScene;
class Pin;

enum class tee {IS_TEE, ISNOT_TEE};

///
///class Cell
///
class Cell : public LibCell
{
public:
    Cell(std::string name, int x, int y, LibCell libcell, tee _tee = tee::ISNOT_TEE);
    virtual ~Cell();

public:
    void draw(QGraphicsScene* scan) const;
    bool isAllowed(Cell cell) const;
    const std::string& getName()const;

    void getPins(std::vector<Pin*>& pins) const;
    int getPinsCount() const;
    int getInPinsCount() const;
    int getOutPinsCount() const;

    //static
    static const std::vector<Cell>& getAllCell();
    static bool getCell(const std::string& name, Cell& cell);
    static bool find(const Cell& libcell);
    static bool addCell(const Cell& cell);

    //
    const std::vector<Pin>& getPins() const;
    inline int x() const { return m_point.x();}
    inline int y() const { return m_point.y();}
    inline int width() const { return m_v;}
    inline int height() const { return m_h;}

private:
    std::string m_name;
    QPoint m_point;
    tee m_tee;
    static std::vector<Cell> s_cells;
};

///
///class cell_list
///
//class cell_list : public QRectF
//{
//private:
//    std::vector<Cell*> m_list_cells;
//    static Cell* m_default;
//
//private:
//    int how(int cmoll, int big, int netscount);
//    Cell* randomCreatePins(int x_cell, int y_cell, int w_cell, int h_cell, int count_pins, Status status, int& in, int& out);
//    //pin* randomCreatePinW(int x, int begin, int end, std::vector<int> vec, Status status);
//    pin* randomCreatePin(int y, int begin, int end, std::vector<int> vec, Status status);
//    bool findevector(std::vector<int> vec, int item);
//    void statusInitialize(Status *arr, int count_in, int count_out);
//
//public:
//    cell_list(int x, int y, int w, int h);
//    void setlist(int netscount = 2, Cell* exempl = m_default);
//    bool intersect(Cell* _cell) const;
//    bool intersect(cell_list* _cell_list) const;
//    std::vector<Cell*> getList();
//
//};
