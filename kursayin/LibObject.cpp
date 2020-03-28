#include <algorithm>
#include <QGraphicsScene>
#include <QPen>

#include "LibObject.h"

///////////////////////////////////////////////////////////////////////////////////////////////
// ! LibPin operator==
///////////////////////////////////////////////////////////////////////////////////////////////
bool LibPin::operator==(const LibPin& libpin)
{
    bool isequal = true;
    isequal &= (m_name == libpin.m_name);
    isequal &= (m_v == libpin.m_v);
    isequal &= (m_h == libpin.m_h);
    isequal &= (m_direction == libpin.m_direction);
    return isequal;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! LibPin operator==
///////////////////////////////////////////////////////////////////////////////////////////////
void LibPin::draw(QGraphicsScene* scan, int x, int y) const
{
    QPen pen;
    if (m_direction == EAD::DIRECTION::IN) {
        pen.setColor(Qt::darkGreen);
    } else {
        pen.setColor(Qt::darkBlue);
    }
    scan->addRect(x + m_v, y + m_h, 1, 1, pen);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! init LibCell vector
///////////////////////////////////////////////////////////////////////////////////////////////
std::vector<LibCell> LibCell::s_libcells;

///////////////////////////////////////////////////////////////////////////////////////////////
// ! LibCell LibCell
///////////////////////////////////////////////////////////////////////////////////////////////
LibCell::LibCell(std::string name, int v, int h, const std::vector<LibPin>& libPins) :
    DBObject(name), m_v(v), m_h(h)
{
    for (const auto& item : libPins) {
        m_libPins.push_back(item);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! LibCell operator==
///////////////////////////////////////////////////////////////////////////////////////////////
bool LibCell::operator==(const LibCell& libcell)
{
    bool isequal = true;
    isequal &= (m_name == libcell.m_name);
    isequal &= (m_v == libcell.m_v);
    isequal &= (m_h == libcell.m_h);
    isequal &= (m_libPins.size() == libcell.m_libPins.size());
    if (!isequal) {
        return false;
    }
    int size = m_libPins.size();
    for(int i = 0; i < size; ++i)
    {
        isequal &= (m_libPins[i] == libcell.m_libPins[i]);
    }
    return isequal;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! LibCell getAllLibCell
///////////////////////////////////////////////////////////////////////////////////////////////
const std::vector<LibCell>& LibCell::getAllLibCell()
{
    return s_libcells;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! LibCell getLibCell
///////////////////////////////////////////////////////////////////////////////////////////////
bool LibCell::getLibCell(const std::string& name, LibCell& libcell)
{
    for (const auto& item : s_libcells) {
        if (item.getName() == name) {
            libcell = item;
            return true;
        }
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! LibCell find
///////////////////////////////////////////////////////////////////////////////////////////////
bool LibCell::find(const LibCell& libcell)
{
    const auto& finde = std::find(s_libcells.begin(), s_libcells.end(), libcell);
    if (finde == s_libcells.end()) {
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! LibCell addLibCell
///////////////////////////////////////////////////////////////////////////////////////////////
bool LibCell::addLibCell(const LibCell& libcell)
{
    if (find(libcell)) {
        return false;
    }
    s_libcells.push_back(libcell);
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ! LibCell ~LibCell
///////////////////////////////////////////////////////////////////////////////////////////////
LibCell::~LibCell()
{
    s_libcells.erase(std::remove(s_libcells.begin(), s_libcells.end(), *this), s_libcells.end());
}


