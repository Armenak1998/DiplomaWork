#include "cell.h"
#include "pin.h"
#include "chip.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
//#include <QRandomGenerator>
#include <QtGlobal>
#include <iostream>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////////////////////
// ! initialization static member Cell
///////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Cell> Cell::s_cells;

///////////////////////////////////////////////////////////////////////////////////////////////
// ! constructor Cell
///////////////////////////////////////////////////////////////////////////////////////////////
Cell::Cell(std::string name, int x, int y, LibCell libcell, tee _tee) :
    LibCell(libcell), m_name(name), m_point(x,y), m_tee(_tee)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! Cell isAllowed
///////////////////////////////////////////////////////////////////////////////////////////////
const std::vector<Cell>& Cell::getAllCell()
{
    return s_cells;;

}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! Cell getCell
///////////////////////////////////////////////////////////////////////////////////////////////
bool Cell::getCell(const std::string& name, Cell& cell)
{
    for (const auto& item : s_cells) {
        if (item.getName() == name) {
            cell = item;
            return true;
        }
    }
    return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// ! Cell find
///////////////////////////////////////////////////////////////////////////////////////////////
bool Cell::find(const Cell& cell)
{
    const auto& finde = std::find(s_cells.begin(), s_cells.end(), cell);
    if (finde == s_cells.end()) {
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! Cell addCell
///////////////////////////////////////////////////////////////////////////////////////////////
bool Cell::addCell(const Cell& cell)
{
    if (find(cell)) {
        return false;
    }
    s_cells.push_back(cell);
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! Cell isAllowed
///////////////////////////////////////////////////////////////////////////////////////////////
bool Cell::isAllowed(Cell cell) const
{
    QRect rectcell(cell.m_point.x(), cell.m_point.y(), cell.m_v, cell.m_h);
    QRect rect = layer::getAdmissibility();
    if (rectcell == rect.intersected(rectcell)) {
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! Cell draw
///////////////////////////////////////////////////////////////////////////////////////////////
void Cell::draw(QGraphicsScene* scan) const
{
    QPen pen(Qt::white);
    scan->addRect(m_point.x(), m_point.y(), m_v, m_h, pen);
    for(const auto& item : m_libPins) {
        item.draw(scan, m_point.x(), m_point.y());
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! Cell getName
///////////////////////////////////////////////////////////////////////////////////////////////
const std::string& Cell::getName()const
{
    return m_name;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! Cell getPinsCount
///////////////////////////////////////////////////////////////////////////////////////////////
int Cell::getPinsCount() const
{
    return m_libPins.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! Cell getInPinsCount
///////////////////////////////////////////////////////////////////////////////////////////////
int Cell::getInPinsCount() const
{
    int i = 0;
    for(const auto& item : m_libPins) {
        if(item.getDirection() == EAD::DIRECTION::IN) {
            ++i;
        }
    }
    return i;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! Cell getOutCellsCount
///////////////////////////////////////////////////////////////////////////////////////////////
int Cell::getOutPinsCount() const
{
    int i = 0;
    for(const auto& item : m_libPins) {
        if(item.getDirection() == EAD::DIRECTION::OUT) {
            ++i;
        }
    }
    return i;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! destructor Cell
///////////////////////////////////////////////////////////////////////////////////////////////
void Cell::getPins(std::vector<Pin*>& pins) const
{
    pins.clear();
    for (const auto& item : m_libPins) {
        pins.push_back(new Pin(item.getName(), item.getV() + m_point.x(),
                    item.getH() + m_point.y(), item.getDirection()));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! destructor Cell
///////////////////////////////////////////////////////////////////////////////////////////////
Cell::~Cell()
{
    s_cells.erase(std::remove(s_cells.begin(), s_cells.end(), *this), s_cells.end());
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//// ! initialization static member cell_list
/////////////////////////////////////////////////////////////////////////////////////////////////
//Cell* cell_list::m_default = nullptr;
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//// ! constructor cell_list
/////////////////////////////////////////////////////////////////////////////////////////////////
//cell_list::cell_list(int x, int y, int w, int h):QRectF(x, y, w, h)
//{
//    std::vector<LibPin> pins;
//    pins.push_back(LibPin("lpin1", 0, 5, EAD::DIRECTION::IN));
//    pins.push_back(LibPin("lpin2", 20, 3, EAD::DIRECTION::OUT));
//    pins.push_back(LibPin("lpin3", 20, 7, EAD::DIRECTION::OUT));
//    LibCell libcell("lcell", 20, 10, pins);
//    LibCell::addLibCell(libcell);
//    m_default = new Cell("cell1", 20, 30, libcell);
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//// ! ell_list how
/////////////////////////////////////////////////////////////////////////////////////////////////
//int cell_list::how(int cmoll, int big, int netscount)
//{
//    int count =  big / (cmoll + netscount);
//    return --count;
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//// ! cell_list findevector
/////////////////////////////////////////////////////////////////////////////////////////////////
//bool cell_list::findevector(std::vector<int> vec, int item)
//{
//    for(const auto& el : vec) {
//        if(((el - 6) <= item) && ((el + 6) >= item)) {
//            return true;
//        }
//    }
//    return false;
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//// ! cell_list randomCreatePinW
/////////////////////////////////////////////////////////////////////////////////////////////////
///*pin* cell_list::randomCreatePinW(int x, int begin, int end, std::vector<int> vec, Status status)
//{
//    //int y = QRandomGenerator::global()->generate();
//    int y = qrand();
//    int size = end - begin;
//    y %= size;
//    y += begin;
//
//    while(findevector(vec,y)) {
//        //y = QRandomGenerator::global()->generate();
//        y = qrand();
//        y %= (end - begin);
//        y += begin;
//    }
//    static int pin_name = 1;
//    return new pin("pin_random_w_" + std::to_string(pin_name++), x, y, status);
//}*/
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//// ! cell_list randomCreatePinH
/////////////////////////////////////////////////////////////////////////////////////////////////
//pin* cell_list::randomCreatePin(int x, int begin, int end, std::vector<int> vec, Status status)
//{
//    //int x = QRandomGenerator::global()->generate();
//    int y =qrand();
//    y %= (end - begin + 1);
//    y += begin;
//
//    while(findevector(vec,y)) {
//        //x = QRandomGenerator::global()->generate();
//        y = qrand();
//        y %= (end - begin + 1);
//        y += begin;
//    }
//    static int pin_name = 1;
//    return new pin("pin_random_h_" + std::to_string(pin_name++), x, y, status);
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//// ! ell_list statusInitialize
/////////////////////////////////////////////////////////////////////////////////////////////////
//void cell_list::statusInitialize(Status *arr, int count_in, int count_out)
//{
//        for(int i = 0; i < count_in; ++i) {
//            arr[i] = Status::IN;
//        }
//        for(int i = count_in; i < count_out; ++i) {
//            arr[i] = Status::OUT;
//        }
//}
/////////////////////////////////////////////////////////////////////////////////////////////////
//// ! ell_list randomCreatePins
/////////////////////////////////////////////////////////////////////////////////////////////////
//Cell* cell_list::randomCreatePins(int x_cell, int y_cell,
//        int w_cell, int h_cell, int count_pins, Status status, int& in, int& out)
//{
//    /*pin** arr = new pin *[count_pins];
//    Status * s_arr = new Status[count_pins];
//    //int st_count = QRandomGenerator::global()->generate();
//    int st_count = qrand();
//    st_count %= (count_pins - 2);
//    ++st_count;
//
//    int max = (st_count > (count_pins / 2)) ? 1 + st_count : count_pins - st_count;
//
//    if (status == Status::IN) {
//        for(int i = 0; i < max; ++i) {
//            s_arr[i] = Status::IN;
//        }
//        for(int i = max; i < count_pins; ++i) {
//            s_arr[i] = Status::OUT;
//        }
//        in = max;
//        out = count_pins - max;
//
//    } else {
//        for(int i = 0; i < max; ++i) {
//            s_arr[i] = Status::OUT;
//        }
//        for(int i = max; i < count_pins; ++i) {
//            s_arr[i] = Status::IN;
//        }
//        out = max;
//        in = count_pins - max;
//    }
//
//    int cou = count_pins / 4;
//    std::vector<int> vecint;
//    int g = -1;
//    int gx = -1;
//    for(int i = 0; i < cou; ++i) {
//        arr[i] = randomCreatePinW(x_cell, y_cell, y_cell + h_cell - 5,
//                vecint, s_arr[i]);
//        vecint.push_back(arr[i]->rect().y());
//        if(arr[i]->y() >= (y_cell + h_cell - 6)) {
//            gx = arr[i]->x();
//        }
//
//        if(arr[i]->y() <= (y_cell + 6)){
//            g = arr[i]->x();
//        }
//    }
//    vecint.clear();
//    if(g != -1) {
//        vecint.push_back(g);
//        g = -1;
//    }
//
//    for(int i = cou; i < (2 * cou); ++i) {
//        arr[i] = randomCreatePinH(y_cell, x_cell, x_cell + w_cell - 5,
//                vecint, s_arr[i]);
//        vecint.push_back(arr[i]->rect().x());
//        if(arr[i]->rect().x() <= (x_cell + 6)) {
//            g = arr[i]->rect().y();
//        }
//    }
//    vecint.clear();
//    if(g != -1) {
//        vecint.push_back(g);
//        g = -1;
//    }
//
//    for(int i = (2 * cou); i < (3 * cou); ++i) {
//        arr[i] = randomCreatePinW(x_cell + w_cell - 5, y_cell, y_cell + h_cell - 5,
//                vecint, s_arr[i]);
//        vecint.push_back(arr[i]->rect().y());
//
//        if(arr[i]->rect().y() >= (y_cell + h_cell - 6)) {
//            g = arr[i]->rect().x();
//        }
//    }
//    vecint.clear();
//    if(g != -1) {
//        vecint.push_back(g);
//    }
//    if(gx != -1) {
//        vecint.push_back(gx);
//    }
//
//    for(int i = (3 * cou); i < count_pins; ++i) {
//        arr[i] = randomCreatePinH(y_cell + h_cell - 5, x_cell,
//                x_cell + w_cell - 5, vecint, s_arr[i]);
//        vecint.push_back(arr[i]->rect().x());
//    }
//    static int cell_name = 1;
//    return new Cell("cell_random_" + std::to_string(cell_name++), x_cell,
//            y_cell, w_cell, h_cell, arr, count_pins);
//    */
//
//    if (count_pins > 6) {
//        count_pins = 6;
//    }
//    if (count_pins < 2) {
//        count_pins = 2;
//    }
//
//    pin** arr = new pin *[count_pins];
//    Status * s_arr = new Status[count_pins];
//    int st_count;
//    if (count_pins != 2) {
//        st_count = qrand();
//        st_count %= (count_pins - 2);
//        ++st_count;
//        if (st_count > 3) {
//            st_count = 3;
//        }
//    } else {
//        st_count = 1;
//    }
//    int max = (st_count > (count_pins / 2)) ? 1 + st_count : count_pins - st_count;
//    int cou;
//
//    if (status == Status::IN) {
//        statusInitialize(s_arr, max, count_pins);
//        cou = max;
//        in = max;
//        out = count_pins - max;
//
//    } else {
//        statusInitialize(s_arr, count_pins - max, count_pins);
//        cou = count_pins - max;
//        out = max;
//        in = count_pins - max;
//    }
//
//    std::vector<int> vecint;
//    for(int i = 0; i < cou; ++i) {
//        arr[i] = randomCreatePin(x_cell, y_cell + 2, y_cell + h_cell - 7,
//                vecint, s_arr[i]);
//        vecint.push_back(arr[i]->y());
//    }
//    vecint.clear();
//
//    for(int i = cou; i < count_pins ; ++i) {
//        arr[i] = randomCreatePin(x_cell + w_cell, y_cell + 2, y_cell + h_cell - 7,
//                vecint, s_arr[i]);
//        vecint.push_back(arr[i]->y());
//    }
//    static int cell_name = 1;
//    return new Cell("cell_random_" + std::to_string(cell_name++), x_cell,
//            y_cell, w_cell, h_cell, arr, count_pins);
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//// ! cell_list setlist
/////////////////////////////////////////////////////////////////////////////////////////////////
//void cell_list::setlist(int netscount, Cell* exempl)
//{
//    int in = 0;
//    int out = 0;
//    if(netscount < 2) {
//        netscount = 2;
//    }
//    int coun = 1 + (6 * netscount);
//    int c_x = this->x() + coun;
//    int c_y = this->y() + coun;
//    int c_h = this->height();
//    int c_w = this->width();
//    int w = exempl->width();
//    int h = exempl->height();
//
//    int count_h = how(h, c_h, coun);
//    int count_w = how(w, c_w, coun);
//    int l_in;
//    int l_out;
//    for(int i = 0; i < count_w; ++i) {
//        for(int j = 0; j < count_h; ++j) {
//            if(in > out) {
//                m_list_cells.push_back(randomCreatePins(c_x + (w * i) + (coun * i),
//                            c_y + (h * j) + (coun * j), w, h, exempl->getPinsCount(),
//                            Status::OUT, l_in, l_out));
//                in += l_in;
//                out += l_out;
//                //std::cout << (c_x + (w * i) + (coun * i)) + w << " " << (c_y + (h * j) + (coun * j)) + h <<std::endl;
//            } else {
//                m_list_cells.push_back(randomCreatePins(c_x + (w * i) + (coun * i),
//                            c_y + (h * j) + (coun * j), w, h, exempl->getPinsCount(),
//                            Status::IN, l_in, l_out));
//                in += l_in;
//                out += l_out;
//                //std::cout<< (c_x + (w * i) + (coun * i)) + w << " " << (c_y + (h * j) + (coun * j)) + h<<std::endl;
//            }
//        }
//    }
//    //std::cout<<"count h "<<count_h<<"   count w " <<count_w<<std::endl;
//    //std::cout<< "w = "<<w<<"  cx = "<<c_x<<std::endl;
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////
//// ! cell_list intersect
/////////////////////////////////////////////////////////////////////////////////////////////////
//bool cell_list::intersect(Cell* _cell) const
//{
//    return intersects(*_cell);
//
//}
/////////////////////////////////////////////////////////////////////////////////////////////////
//// ! cell_list intersect
/////////////////////////////////////////////////////////////////////////////////////////////////
//bool cell_list::intersect(cell_list* _cell_list) const
//{
//    return intersects(*_cell_list);
//}
/////////////////////////////////////////////////////////////////////////////////////////////////
//// ! cell_list getList
/////////////////////////////////////////////////////////////////////////////////////////////////
//std::vector<Cell*> cell_list::getList()
//{
//    return m_list_cells;
//}
