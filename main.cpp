#include "flightmap.h"
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
   string directory = "/home/kurt/NetBeansProjects/stack2/";
   string file_name = "cities2.txt";
     
   FlightMap m(directory + file_name);

   vector<pair<int, int>> a { make_pair(4, 8), make_pair(4, 2), make_pair(5, 9), make_pair(4, 9), make_pair(5, 3) };

   for (auto iter = a.begin(); iter != a.end(); ++iter) {

	   int origin = iter->first;
	   int dest =  iter->second;
           
       try {
           
	   bool b = m.isPath(origin, dest);

	   string msg = b ? "is a path " : "is no path ";

	   cout << "There " << msg << " from " << "city " << origin << " to " << " city " << dest << endl;
           
       }  catch (exception& e) {
           
           cout << e.what() << endl;
           
       }
   }

   return 0;
}
