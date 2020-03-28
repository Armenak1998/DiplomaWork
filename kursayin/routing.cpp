#include "routing.h"
#include "cell.h"
#include "net.h"
#include <vector>
#include "chip.h"

//void lee::g(int si,int sj,int ni,int nj) {
//    static int k = 0;
//    ++k;
//    std::cout<<k<<std::endl;
//    for(int i = 0; i < 10000; ++i) {
//        for(int j = 0; j < 10000; ++j) {
//            if(mat[i][j] > 0) {
//                std::cout<<"("<<i<<", "<<j<<") | " <<mat[i][j] <<std::endl;
//            }
////            std::cout<<mat[i][j]<< " ";
//        }
////        std::cout<<std::endl;
//    }
//    std::cout<<"#########################################################################"<<std::endl;
//}

lee::lee(){}

lee::lee(layer* _leyer)
{
    mat = new short *[size];
    for(int i = 0; i < size; i++) {
        mat[i] = new short[size];
    }
    for(int i = 0; i <= 10; ++i) {
        for(int j = 0; j < size; ++j) {
            mat[i][j] = -1;
            mat[j][i] = -1;
        }
    }

    for(int i = size - 10; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            mat[i][j] = -1;
            mat[j][i] = -1;
        }
    }
    std::vector<Cell*> vec = _leyer->getCells();
    std::vector<Pin*> pins;
    for(auto item : vec) {
        item->getPins(pins);
        for(auto it : pins) {
            mat[it->x()][it->y()] = -1;
        }
    }
    m_net = _leyer->getNets();
}

bool lee::ifIsCorectINit(int ci, int cj, int val, bool clearLee)
{
	if (ci < 0 || cj < 0) {
		return false;
	}
    if ((ci > size) || (cj > size)) {
		return false;
	}
    if ((!clearLee ) && (0 != mat[ci][cj])) {
        return false;
    }
    if (clearLee && (0 >= mat[ci][cj])) {
        return false;
    }
    mat[ci][cj] = val;
	return true;
}

bool lee::find(int ci, int cj, bool clearLee)
{
    if ((!clearLee) && (mat[ci][cj] > 0)) {
        return true;
    }
    if (clearLee && (mat[ci][cj] == 0)) {
        return true;
    }
	return false;
}

bool lee::haveRoad(int ci, int cj, int value)
{
	if (ci < 0 || cj < 0) {
		return false;
	}
	if (((ci + 5) > size) || ((cj + 5) > size)) {
		return false;
	}
    if (value != mat[ci][cj]) {
        return false;
    }
	return true;
}

void lee::setNet(int& i, int& j, int evi, int evj, Layer& begin, net*& _net)
{
    if (!haveRoad(i + evi, j + evj, mat[i][j] - 1)) {
        return;
    }
    Layer end;
    if (evj != 0) {
        end = Layer::LEYER_3;
    } else {
        end = Layer::LEYER_2;
    }
    _net->setViaWier(new via("via", i, j, begin, end));
    QPoint bpoint(i + evi, j + evj);
    while (haveRoad(i + evi, j + evj, mat[i][j] - 1)) {
        j += evj;
        i += evi;
    }
    QPoint epoint(i + (-1 * evi), j + (-1 * evj));
    _net->setViaWier(new wire("wire", bpoint, epoint, end));
    begin = end;
}

void lee::leeFinal(int si, int sj, net* _net)
{
	int i = si;
	int j = sj;
    Layer leyer = Layer::LEYER_1;
    while (true) {
		if (mat[i][j] == 2) {
            _net->setViaWier(new via("via", i, j, leyer, Layer::LEYER_1));
            return ;
		}
        setNet(i, j, 0,  1, leyer, _net);
        setNet(i, j, 1,  0, leyer, _net);
        setNet(i, j, 0, -1, leyer, _net);
        setNet(i, j, -1, 0, leyer, _net);
    }
}

void lee::f(int i, int j, int changei, int changej,
        std::pair<int, int>& pr,
        std::queue<std::pair<int, int>>& lee_queue, bool clearLee)
{
    int value;
    if (clearLee) {
        value = 0;
    } else {
        value = mat[i][j] + 1;
    }
    if (ifIsCorectINit(i + changei, j + changej, value, clearLee)) {
        pr = {i + changei, j + changej};
        lee_queue.push(pr);
    }
}

void lee::g(std::queue<std::pair<int, int>>& lee_queue, bool clearLee)
{
	std::pair<int, int> pr = lee_queue.front();
	lee_queue.pop();
	int i = pr.first;
	int j = pr.second;

    f(i, j,  1,  0, pr, lee_queue, clearLee);
    f(i, j, -1,  0, pr, lee_queue, clearLee);
    f(i, j,  0,  1, pr, lee_queue, clearLee);
    f(i, j,  0, -1, pr, lee_queue, clearLee);
}

void lee::leeAlgorithm(net* net_, bool clearLee)
{
    int si = net_->getIN()->x();
    int sj = net_->getIN()->y();
    int fi = net_->getOut()->x();
    int fj = net_->getOut()->y();

    if((!clearLee) && (net_->getViaWier().empty())) {
        mat[si][sj] = 0;
        mat[fi][fj] = 0;
    } else if (!clearLee) {
        return;
    }

	std::queue<std::pair<int, int>> lee_queue;
    if (ifIsCorectINit(si, sj, 2, clearLee)) {
		lee_queue.push(std::pair<int, int>{si, sj});
	}

	while (true) {
        if (find(fi, fj, clearLee)) {
            if (!clearLee) {
               leeFinal(fi, fj, net_);
            }
            break;
		}
		if (lee_queue.empty()) {
			break;
		}
        g(lee_queue, clearLee);
	}
    if (!clearLee) {
        leeAlgorithm(net_, true);
        upNet(net_);
    }/* else {
        g(0, 0, 0, 0);
    }*/
}

void lee::startleeAlgorithm()
{
    for(auto item : m_net) {
        leeAlgorithm(item);
    }

}

void lee::upNet(net* net_)
{
    std::vector<baseviawier*> vec = net_->getViaWier();
    for(auto item : vec) {
        QLine line = item->getRect();
        for(int i = line.x1() - 1; i <= line.x2() + 1; ++i) {
            for(int j = line.y1() - 1; j <= line.y2() + 1; ++j) {
                mat[i][j] = -1;
            }
        }
    }
}
