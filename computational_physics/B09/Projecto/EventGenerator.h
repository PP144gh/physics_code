#include "TH1F.h"
#include "TH2F.h"
#include <string>
#include <vector>

using namespace std;
class EventGenerator {
 
 public:
  EventGenerator(int,int);
  EventGenerator( const EventGenerator& );
  ~EventGenerator();
  vector <int> EventNoise(float);
  vector <int> RingSignal(float); 
  vector <int> EventSignal(float*);
  void MakeEvent(float*,float,double, EventGenerator); //event creator
  void RecEvent(); //event reconstructor
  vector <int> GetHPID();
  vector <int> GetHNoisy();
  vector <int> GetHPringID();
  vector <double> GetPringL();
  vector <double> GetAziAng();

 protected:
  //variables
  int N0;
  double R; 
  float beta;
  TH2F* Pixmat; //detector
  int Npix; //number of detector pixels
  int Pixwidth;
  double x; //x real
  double y;//y real
  double tempo; //time reconstructing
  double betaR; //Reconstructed beta
  double errob; //Reconstructed beta error
  double RR; //Reconstructed Radius
  double eRR; //Reconstructed Radius error
  double maxx; //maximum value of x possible for reconstructed x
  double minx;//minimum value of x possible for reconstructed x
  double maxy;//maximum value of y possible for reconstructed y
  double miny;//minimum value of y possible for reconstructed y
  double xR;//Reconstructed x
  double yR;//Reconstructed y
  double epos; //xR and yR error
  double ppx; //x of circunference's point used in reconstruction
  double ppy;//y of circunference's point used in reconstruction

  // Arrays/Vectors
  int* PixID; //array with identifiers from ALL pixels, index is their number
  //Vectors used by the computer
  vector <int> PID; //ID Signal Pixels
  vector <int> Noisy; //ID Noise Pixels
  vector <int> PringID; //ID photon ring activated pixels
  vector <double> PringL; //Pieces of circunference per Pixel
  vector <double> AziAng;//azimutal angle
  //Output Vectors
  vector <int> HPID; //array with signal pixels number
  vector <int> HPringID; //array with ID from photon ring pixels
  vector <int> HNoisy;// array with noisy pixels number
  
};


