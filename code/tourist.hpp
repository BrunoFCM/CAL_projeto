#include <vector>
#include <string>
using namespace std;

class Tourist {
    int id;
    string name;
    vector<int> points_of_interest;

    public:
     Tourist(int id, string name);

     int getId();
     string getName();
     vector<int> getPOI();

     void addPOI(int poi_id);
};