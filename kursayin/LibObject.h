#pragma once

#include <vector>
#include <string>

#include "EnumAndDecl.h"

class Pin;
class QGraphicsScene;

/*************************************/
class DBObject
{
public:
    DBObject(std::string name) :
        m_name(name){}

public:
    inline const std::string& getName() const
    {
        return m_name;
    }

protected:
    std::string m_name;
};


/*************************************/
class LibPin : public DBObject
{
public:
    LibPin(std::string name, int v, int h, EAD::DIRECTION direction) :
        DBObject(name), m_v(v), m_h(h), m_direction(direction) {}

public:
    bool operator==(const LibPin& libpin);
    void draw(QGraphicsScene* scan, int x, int y) const;
    inline EAD::DIRECTION getDirection() const
    {
        return m_direction;
    }
    inline int getV() const
    {
        return m_v;
    }
    inline int getH() const
    {
        return m_h;
    }

protected:
    int m_v;
    int m_h;
    EAD::DIRECTION m_direction;
};

/*************************************/
class LibCell : public DBObject
{
public:
    LibCell(std::string name, int v, int h, const std::vector<LibPin>& libPins);
    virtual ~LibCell();

public:
    bool operator==(const LibCell& libcell);

    //static
    static const std::vector<LibCell>& getAllLibCell();
    static bool getLibCell(const std::string& name, LibCell& libcell);
    static bool find(const LibCell& libcell);
    static bool addLibCell(const LibCell& libcell);

protected:
    int m_v;
    int m_h;
    std::vector<LibPin> m_libPins;
    static std::vector<LibCell> s_libcells;
};
