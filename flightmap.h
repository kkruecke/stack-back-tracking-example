#ifndef FLIGHTMAP_H
#define	FLIGHTMAP_H

#include <iosfwd>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <iterator>

using namespace std;

class FlightMap {

      void markVisited(int city);
      bool getNextCity(int topCity, int& nextCity);
      void unvisitAll();

      struct adjacencyStruct {

    	 vector<int> destinationCities;
    	 bool visited;
    	 vector<int>::const_iterator iter;

         adjacencyStruct() : visited(false) {}
         
    	 void setVisited(bool b) { visited = b; }
         
    	 bool getVisited() { return visited; }

    	 friend ostream& operator<<(ostream& o, const adjacencyStruct& a)
    	 {
    		 o << " The vector of destinations cities: ";
    		 copy(a.destinationCities.begin(), a.destinationCities.end(), ostream_iterator<int>(o, " "));
    		 return o;
      	 }
      };
            
      map<int, adjacencyStruct>  adjacencyList;

  public:
     FlightMap(string file_path);
     bool isPath(int origin, int dest);
};

class BadStuffexception: public exception
{
  virtual const char* what() const throw()
  {
    return "The unexpected did happen!";
  }
}; 

#endif	/* FLIGHTMAP_H */

