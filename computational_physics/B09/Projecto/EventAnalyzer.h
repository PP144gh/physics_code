#include "EventGenerator.h"

class EventAnalyzer : public EventGenerator {
 public:

  EventAnalyzer(int, int);
 void InfoDraw(int); //event drawer
void CleanData(); //cleans file
  void HistP(); //position histogram
  void HistR(); //radius histogram
  void HistB();//beta histogram
  void HistT();//time histogram
  void HistL(); //piece of circunferene histogram
  void Hist();//creates all histograms
  void HistA(); //angle histogram
  void HistN();//noise histogram


};
