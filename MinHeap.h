//********************************************************
// Assignment: ASU CSE310 HW#7
// Your Name: Conner Erickson
// ASU ID: 1214908565
// ASU Email address: cserick3@asu.edu
// Description: MinHeap class heavily based on my own assignment3 code. Added build_min_heap method as well and modified extractHeapMin function.
//********************************************************
#include "LinkedList.h"

using namespace std;

//represent each node of the graph which is a departure City
struct City
{
    string cityName;
    int d;
    struct City* pi;
    LinkedList* arrCityList;
};

//class Heap represents a Min-heap that contains City objects. Underline data structure is
//a one dimensional array of City objects.
class MinHeap
{
    private:
        struct City* cityArr;	//an array of City
        int capacity, size;

	public:
        MinHeap(int capacity);
        ~MinHeap();

        City* getCityArr();
        int getSize();
        int getCapacity();
        int isFound(string cityName);
        bool decreaseKey(int index, City oneCitywithNewD);
        bool insert(City newCity);
        void heapify(int index);
        City getHeapMin();
        void extractHeapMin();
        int leftChild(int parentIndex);
        int rightChild(int parentIndex);
        int parent(int childIndex);
        void printHeap();

        void build_min_heap();      //***newly added function
 };

//Constructor to dynamically allocate memory for a heap with the specified capacity
MinHeap::MinHeap(int capacity)
{
 	cityArr = new City[capacity];
	this->capacity = capacity;
	size = 0;
}

//Define all remaining functions according to above function declaration
//----
//----
MinHeap::~MinHeap()
{
    int count = size;
    delete[] cityArr;
    
    capacity = 5;
    size = 0;
    cityArr = new City[capacity];
}

City* MinHeap::getCityArr()
{
    return cityArr;
}

int MinHeap::getSize()
{
    return size;
}

int MinHeap::getCapacity()
{
    return capacity;
}

int MinHeap::isFound(string cityName)
{
    if(size == 0)
    {
        return -1;
    }

    for(int i = 0; i < size; i++)
    {
        if(cityArr[i].cityName == cityName)
        {
            return i;
        }
    }
    return -1;
}

bool MinHeap::decreaseKey(int index, City oneCitywithNewD)
{
    int newKey = oneCitywithNewD.d;

    if(newKey > cityArr[index].d)
    {
        return false;
    }
    cityArr[index].d = newKey;
    while(index > 0 && cityArr[parent(index)].d > cityArr[index].d)
    {
        City temp = cityArr[parent(index)];
        cityArr[parent(index)] = cityArr[index];
        cityArr[index] = temp;
        index = parent(index);
    }
    return true;
}

bool MinHeap::insert(City newCity)
{

    if(size == capacity)
    {
        capacity = capacity * 2;
        City* temp = new City[capacity];
        for(int i = 0; i < size; i++)
        {
            temp[i] = cityArr[i];
        }
        delete[] cityArr;
        cityArr = temp;

        cout << "\nReach the capacity limit. Double the capacity\n\nThe new capacity now is " << capacity << endl;
    }

    City dummy;
    dummy.d = 30000;
    dummy.cityName = newCity.cityName;
    dummy.arrCityList = newCity.arrCityList;
    dummy.pi = newCity.pi;

    cityArr[size] = dummy;
    decreaseKey(size, newCity);
    size += 1;
    return true;
}

void MinHeap::heapify(int index)
{
    int l = leftChild(index);
    int r = rightChild(index);
    int smallest = index;

    if(l < size && cityArr[l].d < cityArr[smallest].d)
        smallest = l;

    if(r < size && cityArr[r].d < cityArr[smallest].d)
        smallest = r;

    if(smallest != index)
    {
        City temp = cityArr[smallest];
        cityArr[smallest] = cityArr[index];
        cityArr[index] = temp;
        heapify(smallest);
    }
}

City MinHeap::getHeapMin()
{
    return cityArr[0];
}

//****************************************************************
//**Changed a little bit. Once extractedHeapMin, the procedure will
//put the last element at index 0 and re-heapify the array. We will
//keep the extracted City object
void MinHeap::extractHeapMin()
{
	if (getSize() < 1)
	{
		cout << "\nError: empty heap, cannot extract min" << endl;
        return;
	}
	//----
    if(size > 0)
    {
        cityArr[0] = cityArr[size - 1];
        size -= 1;
        //heapify(0);
    }

    build_min_heap();
	//----

}

int MinHeap::leftChild(int parentIndex)
{
    return (2*(parentIndex + 1)) - 1;
}

int MinHeap::rightChild(int parentIndex)
{
    return 2*(parentIndex + 1);
}

int MinHeap::parent(int childIndex)
{
    return ((childIndex + 1)/2) - 1;
}

//*********************************************************
void MinHeap::printHeap()
{
	if (cityArr == NULL || size == 0)
		cout << "\nEmpty heap, no elements" << endl;
	else
	{
		cout << "\nHeap size = " << getSize() << "\n" << endl;

		cout << left;
		cout << setw(15) << "City Name"
             << setw(12) << "d Value"
             << setw(15) << "PI"
             << "Arrival City List" << endl;

		for (int i = 0; i < getSize(); i++)
		{
		    cout << left;
			cout << setw(15) << cityArr[i].cityName
                 << setw(12) << cityArr[i].d;
            if(cityArr[i].pi != NULL)
                    cout << setw(15) << cityArr[i].pi->cityName;
            else
                    cout << setw(15) << "No Parent";
    		 cityArr[i].arrCityList->printArrCityList();
		}
	}
}

void MinHeap::build_min_heap()
{
    for(int i = size/2 - 1; i >= 0; i--)
    {
        heapify(i);
    }
}