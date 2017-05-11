// Project 1a: Solving knapsack using exhaustive search
//

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <time.h>

using namespace std;

#include "d_except.h"
#include "d_random.h"
#include "knapsack.h"
#include <ctime>
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

   fileName = "knapsack32.input";

    //cout << "Enter filename" << endl;
    //cin >> fileName;

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

        exhaustiveKnapsack(k, 1);

        cout << endl << "Best solution" << endl;
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
   clock_t timestart = clock();
   clock_t timenow, timeelapsed = 0;
   int object, value, cost, totalvalue = 0, totalcost = 0, bestcost, bestvalue = 0;
   randomNumber r;
   vector<bool> bestobject;
   bestobject.resize(k.getNumObjects());

   while(timeelapsed < time) {
      do {
         do {
            object = (int) r.random() % k.getNumObjects();
            while (object < 0)
               object += k.getNumObjects();
         } while (k.isSelected(object));

         value = k.getValue(object);
         cost = k.getCost(object);
         k.select(object);

         if (totalcost + cost > k.getCostLimit())
            break;

         totalcost += cost;
         totalvalue += value;
      } while (totalcost <= k.getCostLimit());

      if (bestvalue < value) {
         bestvalue = value;
         bestcost = cost;

         for (int i = 0; i < k.getNumObjects(); i++) {
            bestobject[i] = k.isSelected(i);
            k.unSelect(i);
         }
      }

      //add printing function, and be able to compare to prior sacks
      timenow = clock();
      int x = CLOCKS_PER_SEC;
      timeelapsed = ((timenow - timestart) / CLOCKS_PER_SEC)*1000000;

   }
   for (int j = 0; j < k.getNumObjects(); j++) {
      if (bestobject[j])
         k.select(j);
   }
   k.totalValue = bestvalue;
   k.totalCost = bestcost;
}
