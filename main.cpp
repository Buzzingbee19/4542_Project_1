// Project 1a: Solving knapsack using exhaustive search
//

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#include "d_except.h"
#include "d_random.h"
#include "knapsack.h"
#include <cmath>
#include <stack>

void exhaustiveKnapsack(knapsack& k, int time);

int main()
{
    char x;
    ifstream fin;
    stack <int> moves;
    string fileName;

    // Read the name of the graph from the keyboard or
    // hard code it here for testing.

    //fileName = "knapsack8.input";

    cout << "Enter filename" << endl;
    cin >> fileName;

    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try
    {
        cout << "Reading knapsack instance" << endl;
        knapsack k(fin);

        exhaustiveKnapsack(k, 600);

        cout << endl << "Best solution found" << endl;
        k.printSolution();

    }

    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl; exit(1);
    }
    catch (rangeError &ex)
    {
        cout << ex.what() << endl; exit(1);
    }
}

void exhaustiveKnapsack(knapsack& k, int time)
{

   //initialize all variables
   clock_t timestart = clock();
   clock_t timenow;
   int size, bestcost, bestvalue = 0, tempcost, tempvalue, x, z;
   randomNumber r;
   size = k.getNumObjects();
   vector<bool> tempstring, bestobject;
   tempstring.resize(size);
   bestobject.resize(size);
   float timeelapsed;
   int temp = size-1;
 //  k.sortWeighted();

   //loops through each possible combination of objects, checking their legality
   for (int i = 0; i < pow(2,size); i++) {

      //re-initializes variables for each attempted combo of objects
      tempcost = 0;
      tempvalue = 0;
      z = temp;
      x = i;

      //converts the loop iteration ino a unique binary string, and selects
      // those items.
      while (x > 0)
      {
         if (x % 2)
            k.select(z);
         else
            k.unSelect(z);
         z--;
         x=x/2;
      }

      //chooses the objects to be placed in the bag
      for (int j = 0; j < size; j++) {
         if (k.isSelected(j)) {
            tempcost += k.getCost(j);
            tempvalue += k.getValue(j);
            tempstring[j] = true;
         }
         else
            tempstring[j] = false;
      }

      // checks to determine if the set of objects is a legal set, and if it
      // is the most valuable set to this point
      if (tempcost <= k.getCostLimit() & tempvalue > bestvalue) {
         bestvalue = tempvalue;
         bestobject = tempstring;
         bestcost = tempcost;
      }

      //updates the amount of time the function has taken
      timenow = clock();
      timeelapsed = (float)(timenow - timestart) / CLOCKS_PER_SEC;

      //checks to see if the function has exceeded it's time limit or has
      // checked every object pairing
      if (timeelapsed >= time || i == pow(2,size)-1)
      {
         for (int l = 0; l < size; l++)
         {
            k.unSelect(l);
            if (bestobject[l])
               k.select(l);
         }
         //updates the knapsack's cost and value for the best case
         k.totalValue = bestvalue;
         k.totalCost = bestcost;
  //       k.sortOrder();
         return;
      }
   }
}
