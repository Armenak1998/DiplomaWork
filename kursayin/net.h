#ifndef NET_H
#define NET_H
#include <string>
#include <vector>
#include <QRect>
#include <QLine>
class Pin;
enum class Layer {LEYER_1, LEYER_2, LEYER_3};

///
///class baseviawier
///
class baseviawier
{
private:
    std::string m_name;

public:
    baseviawier(std::string name);
    const std::string& getName() const;
    virtual QLine getRect() = 0;
    virtual void draw(QGraphicsScene* scan, Layer _layer) const = 0;
};

///
/// class via
///
class via : public baseviawier , public QPoint
{
private:
    Layer m_layer_bagin;
    Layer m_layer_end;
public:
    via(std::string name,int x, int y, Layer bagin, Layer end);
    QLine getRect();
    void draw(QGraphicsScene* scan, Layer _layer) const;
};

///
/// wier
///
class wire : public baseviawier, public QLine
{
private:
    Layer m_layer;

public:
    wire(std::string name, QPoint start, QPoint end, Layer layer);
    QLine getRect();
    void draw(QGraphicsScene* scan, Layer _layer) const;
};

///
/// class net
///
class net
{
private:
    std::string m_name;
    Pin* m_in;
    Pin* m_out;
    std::vector<baseviawier*> m_viawier;
public:
    net(std::string name, Pin* in, Pin* out);
    Pin* getIN() const;
    Pin* getOut() const;
    const std::string& getName()const;
    void setViaWier(baseviawier* _viawier);
    std::vector<baseviawier*> getViaWier() const;
    void draw(QGraphicsScene* scan, Layer _layer) const;
};

///
///class randomnets
///

class randomnets{
private:
    std::vector<net*> m_nets;

public:
    void createNets();
    std::vector<net*> getNets()const;
};

#endif // NET_H
