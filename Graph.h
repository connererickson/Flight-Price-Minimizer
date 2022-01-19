//********************************************************************
// ASU CSE310 Assignment #7
// Name of Author: Conner Erickson
// ASU ID: 1214908565
// Description: This is the header file that defines a directed graph
//********************************************************************

#include "MinHeap.h"

using namespace std;

class Graph
{
   private:
   int numOfNode;        //number of nodes in the graph
   MinHeap* cityHeap;    //a min-heap of departure City objects

   //feel free to add other necessary functions
   public:
   Graph(int numOfNode, MinHeap* cityHeap);
   void destructor();
   void printGraph();
   void initialize_single_source(string sourceCityName);
   void relax(City* u, City* v);
   int findOneCity(string aCityName);

   void dijkstra(string sourceCityName);
   void printDijkstraPath(string sourceCityName);
   void printPath(City s, City v);
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfNode, MinHeap* cityHeap)
{
   this->numOfNode = numOfNode;
   this->cityHeap = cityHeap;
}

//*******************************************************************
//Destructor Graph::~Graph()
void Graph::destructor()
{
   delete [] cityHeap;
   cityHeap = NULL;
   numOfNode = 0;
}

//Define all remaining functions according to above function declaration
//----
//----
void Graph::printGraph()
{
   cityHeap->printHeap();
}

void Graph::initialize_single_source(string sourceCityName)
{
   for(int i = 0; i < cityHeap->getSize(); i++)
   {
      cityHeap->getCityArr()[i].d = 99999;
      cityHeap->getCityArr()[i].pi = NULL;
   }
   cityHeap->getCityArr()[cityHeap->isFound(sourceCityName)].d = 0;
}

void Graph::relax(City* u, City* v)
{
   string uname = u->cityName;
   string vname = v->cityName;

   int weight = u->arrCityList->findArrCity(vname)->price;

   if(v->d > u->d + weight)
   {
      //v.d = u.d + weight
      cityHeap->getCityArr()[cityHeap->isFound(vname)].d = u->d + weight;
      
      //v.pi = u
      cityHeap->getCityArr()[cityHeap->isFound(vname)].pi = u;

      //maintain min heap properties
      cityHeap->build_min_heap();

   }
}

int Graph::findOneCity(string aCityName)
{
   cityHeap->isFound(aCityName);
}

//*******************************************************************
//This function performs the dijkstra's shortest path algorithm
void Graph::dijkstra(string sourceCityName)
{
   //----
   initialize_single_source(sourceCityName);

   cityHeap->build_min_heap();
   
   MinHeap* finalArray = new MinHeap(cityHeap->getSize());

   ArrCity* adjacent;
   City u, v;

   while(cityHeap->getSize() != NULL)
   {
      City u = cityHeap->getHeapMin();

      cityHeap->extractHeapMin();

      finalArray->insert(u);

      //adjacent cities are located inside of the linkedlist of the departure city
      adjacent = u.arrCityList->getHead();
      
      //while not all arrival cities have been checked yet
      while(adjacent != NULL)
      {

         //if the arrival city is in S, set V equal to its reference in S, otherwise set V equal to its reference in CityHeap
         if(finalArray->isFound(adjacent->arrCityName) == -1)
         {
            v = cityHeap->getCityArr()[cityHeap->isFound(adjacent->arrCityName)];
         }
         else
         {
            v = finalArray->getCityArr()[finalArray->isFound(adjacent->arrCityName)];
         }
         
         relax(&finalArray->getCityArr()[finalArray->isFound(u.cityName)], &v);

         //iterate through linked list
         adjacent = adjacent->next;
      }
   }

   //lock in final array
   cityHeap = finalArray;
}

//*********************************************************************************
//This function prints the cheapest price and path after the Dijkstra's algorithm
void Graph::printDijkstraPath(string sourceCityName)
{
   cout << "\nSource City: " << sourceCityName << endl;
   cout << left;
   cout << setw(15) << "\nArrival City" << setw(15) << "Lowest Price"   << setw(15) << "Shortest Path" << endl;
   //----
   //----
   cityHeap->build_min_heap();

   //for each index in the cityheap, print its name and price, call recursive function to print path
   for(int i = 0; i < cityHeap->getSize(); i++)
   {
      cout << setw(15) << cityHeap->getCityArr()[i].cityName << setw(15) << cityHeap->getCityArr()[i].d;
      
      printPath(cityHeap->getCityArr()[0], cityHeap->getCityArr()[i]);
      cout << endl;
   }
}

//printPath function as described in textbook pseudocode
void Graph::printPath(City s, City v)
{
   if(v.cityName == s.cityName)
   {
      cout << s.cityName;
   }
   else if (v.pi == NULL)
   {
      cout << "no path from " << s.cityName << " to " << v.cityName << " exists.";
      return;
   }
   else
   {
      printPath(s, *v.pi);
      cout << "->" << v.cityName;
   }
   
}