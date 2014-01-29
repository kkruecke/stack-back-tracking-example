#include <fstream>
#include <sstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <utility>
#include <exception>
#include "flightmap.h"

using namespace std;

FlightMap::FlightMap(string file_path)
{
	ifstream myfile (file_path.c_str());

        string line;

        //check to see if the file is opened:
        if (myfile.is_open()) {

           //while there are still lines in the
           //file, keep reading:
           for(auto index = 0; ! myfile.eof(); index++) {

             //place the line from myfile into the
             //line string variable:
             getline (myfile,line);
             
             if (line == "") { // last line of text file is empty.
                 
                 break;
             }

             // read in the integers from the string
             istringstream istr(line);

             // the first city is the destination city
             int originCity;

             istr >> originCity;

             // add the destination cities, which follow the origin
             // city, to a temporary vector
             vector<int> destinations;

             copy(istream_iterator<int>(istr), istream_iterator<int>(),
            		 back_inserter(destinations));
             
             // insert the origin city into the map. 
             auto pr = adjacencyList.insert(pair<int, adjacencyStruct>(originCity, adjacencyStruct() ));

             // swap it's value, an empty vector<adjacencyStruct>, with the vector we created.
             (pr.first)->second.destinationCities.swap(destinations);

           }

           //close the stream:
           myfile.close();
        }
         
         for(auto iter = adjacencyList.begin(); iter != adjacencyList.end(); iter++) {

        	 cout << "Origin is: " << iter->first << iter->second << endl;
         }
         

}

// Set the visited flag to false in each adjacencyStruct.
void FlightMap::unvisitAll()
{
     for (map<int, adjacencyStruct>::iterator iter = adjacencyList.begin(); iter != adjacencyList.end(); iter++) {
           
	 iter->second.setVisited(false);
         
         //TODO: reset all iterators for the destination cities.
         vector<int>& vec = iter->second.destinationCities;
         
         vector<int>::const_iterator iter_begin = vec.begin();
         
         iter->second.iter = iter_begin;
      }
}

// This method is called only once, each time a city is visited, immediately
// after it has been pushed onto the stack (of visited cities).
inline void  FlightMap::markVisited(int city)
{
	adjacencyStruct& s = adjacencyList[city];

        // Set the initial value for the vector's iterator.

	s.setVisited(true);
}

// Get the next yet-unvisited destination city.
bool  FlightMap::getNextCity(int TopCity, int& nextCity)
{
	// If an destination city has not yet been visited, return it.
	adjacencyStruct& s = adjacencyList[TopCity];
        
	while (s.iter != s.destinationCities.end()) {
            		
               int index = *(s.iter);
                
               // advance iterator, so next time this method is called we 
               // already point to the next destination city.
               ++s.iter;
	                
	       if (!adjacencyList[index].visited) {

			nextCity = index;
                        
        		return true;
		}
                                
	} 

        return false;
}

bool FlightMap::isPath(int originCity, int destinationCity)
// -----------------------------------------------------
// Determines whether a sequence of flights between two
// cities exists. Nonrecursive stack version.
// Precondition: originCity and destinationCity are the city
// numbers of the origin and destination cities,
// respectively.
// Postcondition: Returns true if a sequence of flights
// exists from originCity to destinationCity; otherwise
// returns false. Cities visited during the search are
// marked as visited in the flight map.
// Implementation notes: Uses a stack for the city
// numbers of a potential path. Calls unvisitAll,
// markVisited, and getNextCity.
// -----------------------------------------------------
{
   stack<int> aStack;
   int   topCity, nextCity;
   bool  success;

   unvisitAll();

   // push origin city onto aStack, mark it visited
   aStack.push(originCity);

   markVisited(originCity);

   topCity = aStack.top();

   while (!aStack.empty() && (topCity != destinationCity)) {  
      // Loop invariant: The stack contains a directed path
      // from the origin city at the bottom of the stack to
      // the city at the top of the stack

      // find an unvisited city adjacent to the city on the
      // top of the stack
      success = getNextCity(topCity, nextCity);

      if (!success) {

         aStack.pop();  // no city found; backtrack
      }
      else   {         // visit city

         aStack.push(nextCity);
         markVisited(nextCity);
      }

      if (!aStack.empty()) {

         topCity = aStack.top();
      }
   }  // end while

   // If stack empty, no path exists.
   return !aStack.empty();
}

