// Knapsack class
// Version f08.1
#include <iomanip>
#include <vector>
using namespace std;
class knapsack
{
public:
    knapsack(ifstream &fin);
    knapsack(const knapsack &);
    int getCost(int) const;
    int getValue(int) const;
    int getCost() const;
    int getValue() const;
    int getNumObjects() const;
    int getCostLimit() const;
    void printSolution();
    void select(int);
    void unSelect(int);
    bool isSelected(int) const;
    void sortWeighted();
    void sortOrder();
    int totalValue;
    int totalCost;



private:
    int numObjects;
    int costLimit;
    vector<int> index;
    vector<int> value;
    vector<int> cost;
    vector<bool> selected;
    vector<double> costdensity;
};

knapsack::knapsack(ifstream &fin)
// Construct a new knapsack instance using the data in fin.
{
   int n, b, j, v, c;

   fin >> n;  // read the number of objects
   fin >> b;  // read the cost limit

   numObjects = n;
   costLimit = b;

   value.resize(n);
   cost.resize(n);
   selected.resize(n);
   costdensity.resize(n);
   index.resize(n);

   for (int i = 0; i < n; i++)
   {
      fin >> j >> v >> c;
      value[j] = v;
      cost[j] = c;
      costdensity[j] = (double)v/c;
      index[i] = j;
      unSelect(j);
   }

   totalValue = 0;
   totalCost = 0;
}

knapsack::knapsack(const knapsack &k)
// Knapsack copy constructor.
{
   int n = k.getNumObjects();

   value.resize(n);
   cost.resize(n);
   selected.resize(n);
   numObjects = k.getNumObjects();
   costLimit = k.getCostLimit();

   totalCost = 0;
   totalValue = 0;

   for (int i = 0; i < n; i++)
   {
      value[i] = k.getValue(i);
      cost[i] = k.getCost(i);
      if (k.isSelected(i))
	 select(i);
      else
	 unSelect(i);
   }
}

int knapsack::getNumObjects() const
{
   return numObjects;
}

int knapsack::getCostLimit() const
{
   return costLimit;
}

int knapsack::getValue(int i) const
// Return the value of the ith object.
{
   if (i < 0 || i >= getNumObjects())
      throw rangeError("Bad value in knapsack::getValue");

   return value[i];
}

int knapsack::getCost(int i) const
// Return the cost of the ith object.
{
   if (i < 0 || i >= getNumObjects())
      throw rangeError("Bad value in knapsack::getCost");

   return cost[i];
}

int knapsack::getCost() const
// Return the cost of the selected objects.
{
   return totalCost;
}

int knapsack::getValue() const
// Return the value of the selected objects.
{
   return totalValue;
}

ostream &operator<<(ostream &ostr, const knapsack &k)
// Print all information about the knapsack.
{
   cout << "------------------------------------------------" << endl;
   cout << "Num objects: " << k.getNumObjects() << " Cost Limit: " << k.getCostLimit() << endl;

   int totalValue = 0;
   int totalCost = 0;

   for (int i = 0; i < k.getNumObjects(); i++)
   {
      totalValue += k.getValue(i);
      totalCost += k.getCost(i);
   }

   cout << "Total value: " << totalValue << endl;
   cout << "Total cost: " << totalCost << endl << endl;

   for (int i = 0; i < k.getNumObjects(); i++)
      cout << i << "  " << k.getValue(i) << " " << k.getCost(i) << endl;

   cout << endl;

   return ostr;
}

void knapsack::printSolution()
// Prints out the solution.
{
   ofstream myfile;
   myfile.open("output1024.txt");
   cout << "------------------------------------------------" << endl;

   cout << "Total value: " << getValue() << endl;
   cout << "Total cost: " << getCost() << endl << endl;

   myfile << "------------------------------------------------" << endl;

   myfile << "Total value: " << getValue() << endl;
   myfile << "Total cost: " << getCost() << endl << endl;

   // Print out objects in the solution
   for (int i = 0; i < getNumObjects(); i++){

      if (isSelected(i)){

         cout << index[i] << "  " << getValue(i) << " " << getCost(i) << endl;
         myfile << index[i] << "  " << getValue(i) << " " << getCost(i) << endl;

      }

   }

   cout << endl;
}

ostream &operator<<(ostream &ostr, vector<bool> v)
// Overloaded output operator for vectors.
{
   for (int i = 0; i < v.size(); i++)
      cout << v[i] << endl;

   return ostr;
}

void knapsack::select(int i)
// Select object i.
{
   if (i < 0 || i >= getNumObjects())
      throw rangeError("Bad value in knapsack::Select");

   if (selected[i] == false)
   {
      selected[i] = true;
      totalCost = totalCost + getCost(i);
      totalValue = totalValue + getValue(i);
   }
}

void knapsack::unSelect(int i)
// unSelect object i.
{
   if (i < 0 || i >= getNumObjects())
      throw rangeError("Bad value in knapsack::unSelect");

   if (selected[i] == true)
   {
      selected[i] = false;
      totalCost = totalCost - getCost(i);
      totalValue = totalValue - getValue(i);
   }
}

bool knapsack::isSelected(int i) const
// Return true if object i is currently selected, and false otherwise.
{
   if (i < 0 || i >= getNumObjects())
      throw rangeError("Bad value in knapsack::getValue");

   return selected[i];
}

void knapsack::sortWeighted()
//function to sort the knapsack contents by their weighted value
{
   for (int i = (numObjects - 1); i >= 0; i--) {
      for (int j = (numObjects - 1); j >= 0; j--) {
         if (costdensity[i] > costdensity[j]) {
            swap(costdensity[i], costdensity[j]);
            swap(cost[i], cost[j]);
            swap(value[i], value[j]);
            swap(index[i], index[j]);
            swap(selected[i], selected[j]);
         }
      }
   }
}

void knapsack::sortOrder()
//sorts knapsack objecs back to originally passed order
{
   for (int i = (numObjects - 1); i >= 0; i--) {
      for (int j = (numObjects - 1); j >= 0; j--) {
         if (index[i] > index[j]) {
            swap(costdensity[i], costdensity[j]);
            swap(cost[i], cost[j]);
            swap(value[i], value[j]);
            swap(index[i], index[j]);
            swap(selected[i],selected[j]);
         }
      }
   }
}