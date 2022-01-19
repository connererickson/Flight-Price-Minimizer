#include "Graph.h"

int main()
{
    MinHeap* heap = new MinHeap(5);

    City phoenix;
    phoenix.cityName = "Phoenix";
    phoenix.arrCityList = new LinkedList();
    phoenix.arrCityList->addArrCity("Atlanta", 50);
    phoenix.arrCityList->printArrCityList();

    City atlanta;
    atlanta.cityName = "Atlanta";
    atlanta.arrCityList = new LinkedList();

    heap->insert(phoenix);
    heap->insert(atlanta);
    heap->printHeap();
}