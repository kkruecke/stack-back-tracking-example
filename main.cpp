#include "flightmap.h"
using namespace std;

int main(int argc, char *argv[])
{
   //TODO: cities.txt works but cities2.txt fails
   string directory = "/home/kurt/NetBeansProjects/stack2/";
   string file_name = "cities2.txt";
     
   //string file_name = "cities2.txt";
   
   FlightMap m(directory + file_name);

   //pair<int, int> a[] = { make_pair(4, 8), make_pair(4, 2), make_pair(5, 9), make_pair(4, 9), make_pair(5, 3) };
   pair<int, int> a[] = { make_pair(4, 2) };

   for (int i = 0; i < sizeof(a) / sizeof(pair<int, int>); i++) {

	   int origin = a[i].first;
	   int dest = a[i].second;
           
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
