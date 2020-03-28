#pragma once

#include <QPoint>
#include <QRect>
#include <vector>
#include <string>

#include "LibObject.h"
#include "EnumAndDecl.h"

class QGraphicsScene;
class cell;

enum class Status {IN,OUT};

///
/// class Pin
///
class Pin : public DBObject
{
private:
    QPoint m_point;
    EAD::DIRECTION m_direction;
    static std::vector<Pin> s_pins;

public:
    Pin(std::string name, int x, int y, EAD::DIRECTION direction);
    ~Pin();

public:
    void draw(QGraphicsScene* scan) const;
    inline EAD::DIRECTION getDirection() const
    {
        return m_direction;
    }
    inline int x() const
    {
        return m_point.x();
    }
    inline int y() const
    {
        return m_point.y();
    }
    bool operator==(const Pin&);

    //static
    static const std::vector<Pin>& getAllPin();
    static bool getPin(const std::string& name, Pin& pin);
    static bool find(const Pin& pin);
    static bool addPin(const Pin& pin);
public:
};

/////
///// class port
/////
//class port : public QPoint
//{
//private:
//    Status m_status;
//    std::string m_name;
//    static std::vector<port*> ports_list;
//    static std::string default_name;
//    static int INDEX;
//    Pin * m_pin;
//
//public:
//    port(std::string name, int x, int y, Status status1);
//    void draw(QGraphicsScene* scan) const;
//    std::string getName() const;
//    static bool repetitiveName(std::string name);
//    static port* getPortByName(std::string name);
//    Status getStatus()const;
//    pin* getPin() const;
//    ~port();
//};
