#ifndef ROUTING_H
#define ROUTING_H

#include <vector>
#include <queue>
#include "chip.h"
class cell;
class net;
class layer;
///
///class lee
///
class lee
{
private:
    const int size = 10000;
    short** mat;
    std::vector<net*> m_net;

public:
    lee();
    lee(layer* _leyer);
    bool ifIsCorectINit(int ci, int cj, int val, bool clearLee = false);
    bool find(int ci, int cj, bool clearLee = false);
    bool haveRoad(int ci, int cj, int value);
    void leeFinal(int si, int sj, net* _net);
    void leeAlgorithm(net* net_, bool clearLee = false);
    void upNet(net* net_);
    void startleeAlgorithm();
    void setNet(int& i, int& j, int evi, int evj, Layer& begin, net*& _net);
    void g(std::queue<std::pair<int, int>>& lee_queue, bool clearLee = false);
    void f(int i, int j, int changei, int changej,
            std::pair<int, int>& pr,
            std::queue<std::pair<int, int>>& lee_queue, bool clearLee = false);

    void g(int si,int sj,int ni,int nj);

/*
    void connected(cell* _cell);
    void rout(std::vector<net*> _nets);
    void rout(net* _net);
    */
};
#endif // ROUTING_H
