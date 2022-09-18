#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "TRandom3.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <TF1.h>
#include <TH2F.h>
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "cFCgraphics.h"
#include "TLine.h"

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std; 





class cell {
  int a;
  int b;
  int c;
  bool d;
  int e;
  int f;
  bool g;
  int h;
  int i;
  int j;
 
public: 
  cell(int x, int y,int z, bool w, int u,int v, bool j, int k, int l, int m){
    a = x; //x
    b=y; //y 
    c=z; //serial
    d=w; //alive
    e=u; //age
    f=v; //hunger
    g=j;// sex 0=male 1=female
    h=k;//pop serial
    i=l; //generation
    j=m; //time
 
  }
  ~cell() {}
  int xx() {return a;}
  int yy() {return b;}
  int serial(){ return c;}
  bool alive() {return d;}
  int age() {return e;}
  int hunger() {return f;}
  bool sex() {return g;}
  int popserial(){return h;}
  int generation(){return i;}
  int time() {return j;}
  void setx(int z){ a=z;}
  void sety(int v) {b=v;}
  void setlife(bool t) {d=t;}
  void setage(int g) {e=g;}
  void sethunger(int t) {f=t;}
  void setgeneration(int t) {i=t;}
  void settime(int h){j=h;}
};


int main() {
  TRandom3 rand(0);
	     
  //contador de mortes
  int dcount=0;
  //flag t=0
 


  //map generator
  int L=6; //side of square lattice, keep it even for more evenly distributed food sites (keep L>=4 )
  if (L<4) {cout <<"lattice too small" << endl; return 0; }
  int maxx=L-1; int maxy=L-1; //(min is 0 so lattice is (maxx+1) * (maxy+1) squares
 

  cFCgraphics D;
  D.CreatePad("Pad");
  int Pixwidth=1;

  TH2F* cellmat;
  TH2F* fdmat;
  // TH2F* deathmat;
  cellmat=new TH2F("Population","The Matrix",L,0,(L)*Pixwidth,L,0,(L)*Pixwidth);
  fdmat=new TH2F("Population ","The Matrix",L,0,(L)*Pixwidth,L,0,(L)*Pixwidth);
  

  vector<TLine*> lines;
  lines.resize((L)*5);
  //verticais
  for(int i=0; i<L; ++i) {
    lines[i] = new TLine(i,0,i,L);
    lines[i]->SetLineStyle(1);
    lines[i]->SetLineColor(11);
  }
  //horizontais
  for(int i=0; i<L; ++i) {
    lines[L+i] = new TLine(0,i,L,i);
    lines[L+i]->SetLineStyle(1);
    lines[L+i]->SetLineColor(11);
  }

  gStyle->SetOptStat("ne");
  gStyle->SetPalette(1);
  gROOT->SetStyle("Plain");

  

 

  fdmat->SetOption("COL");
  fdmat->GetXaxis()->SetTitle("x");
  fdmat->GetYaxis()->SetTitle("y");
  D.AddObject(fdmat,"Pad");
  D.DumpPad("Pad");

  cellmat->SetMarkerStyle(29);
  cellmat->SetMarkerSize(2);
  cellmat->SetMarkerColor(1);
  cellmat->SetOption("SCAT");
  cellmat->GetXaxis()->SetTitle("x");
  cellmat->GetYaxis()->SetTitle("y");
  D.AddObject(cellmat,"Pad");
   D.DumpPad("Pad");

  for(int i=0; i<(L)*2; ++i) {
    D.AddObject(lines[i],"Pad");
     D.DumpPad("Pad");
  }




  /***POP GENERATOR 1 ***
   //generates pop in a big L with 2 cell in each square and vertex at 0,0.
 
   //pop generator
   int cellnumber=10;
   //pop A
   int currentserial=0;
   vector<cell*> popA;
   int c1=0;
   int c2=0;

   for( int q=0; q<cellnumber; q+=2) {
   if (q%4==0){
   popA.push_back(new cell (0,q%4/2+c1,q,1,0,0,0,0,0,0)); //q%2 means q even sex is 0, q odd sex is 1
   popA.push_back(new cell (0,q%4/2+c1,q+1,1,0,0,1,0,0,0));
   currentserial=q+1;
   ++c1;}
   if (q%4!=0){
   popA.push_back(new cell (q%4/2+c2,0,q,1,0,0,0,0,0,0)); //q%2 means q even sex is 0, q odd sex is 1
   popA.push_back(new cell (q%4/2+c2,0,q+1,1,0,0,1,0,0,0));
   currentserial=q+1; 
   ++c2;}
   }
   //END OF POP GENERATOR 1*/

  /***POP GENERATOR 2 ***/
  //generates pop in a big L with 2 cell in each square and vertex at 0,0. 


  int tries=10;
  //este file e' para escrever dados para histogrma
 ofstream myfile;
  myfile.open ("hist_data.txtt");
   for (int i=1; i<tries; ++i) {
     system("rm *.txt");

  //pop generator
  int cellnumber=20; //has to be even
  //pop A
  int currentserial=cellnumber-1;
  vector<cell*> popA;
 

  for( int q=0; q<cellnumber/2; q+=2) {
    int l=q/2;
    // if (q==0) {l=1;}
    popA.push_back(new cell (0,l,q,1,0,0,q%2,0,0,0)); //q%2 means q even sex is 0, q odd sex is 1
     popA.push_back(new cell (0,l,q+1,1,0,0,q%2+1,0,0,0)); //q%2 means q even sex is 0, q odd sex is 1
  }
  
  for( int q=0; q<cellnumber/2; q+=2) {
    int l=(q+1);
    if (q==0) {l=1;}
    popA.push_back(new cell (L-1,l,q+cellnumber/2,1,0,0,q%2,0,0,0)); //q%2 means q even sex is 0, q odd sex is 1
  popA.push_back(new cell (L-1,l,q+cellnumber/2+1,1,0,0,q%2+1,0,0,0)); //q%2 means q even sex is 0, q odd sex is 1
  } 
  //END OF POP GENERATOR 2
  


  
  /*****Try 1(distribuiçao equitativa) de food e death sites *****
   //tenho de meter mais entries nos death para este ficar vermelho e o food ficar verde, escala dde cor e prop a escala de entries
   int JMAX=50;

   //food
   vector<int> fx;
   vector<int> fy;
   int fperiod=4;// period of food sites
  
   for (int yi=0; yi<maxy; ++yi) {
   if ((yi%2==0 )&& (yi!=0)){
   for (int xi=1; xi<maxx; xi+=fperiod){

   fx.push_back(xi);
   fy.push_back(yi);
   for(int j=0; j<0.5*JMAX; ++j){
   fdmat->Fill(xi,yi); }
   cout <<"food: " << xi <<","<< yi << endl; 
   }
   }
   else if (yi%2==1){
   for (int xi=3; xi<maxx; xi+=fperiod){
   fx.push_back(xi);
   fy.push_back(yi);
   for(int j=0; j<0.5*JMAX; ++j){
   fdmat->Fill(xi,yi); }
   cout <<"food: " << xi <<","<< yi << endl; 
   }
   }
   }
 
   int fnumber=fx.size();// L*L/4 : 1 food site per 4 lattice squares
  
   //death zones
   vector<int> deathx;
   vector<int> deathy;
   int dperiod=2; // period of death zones
   //1st death zone origin
   int dp=2; //(2,2)
   for (int yi=dp; yi<maxy; yi+=dperiod) {
     
   for (int xi=dp; xi<maxx; xi+=dperiod){
   deathx.push_back(xi);
   deathy.push_back(yi);
   for(int j=0; j<JMAX; ++j) {
   fdmat->Fill(xi,yi); }
   cout <<"death zone: " << xi <<","<< yi << endl; 
   }
   }
   int dnumber=deathx.size(); //1 death zone per 16 square lattices (aprox)

   //food limit 
   vector<int> foodc; //foodc[0] contador de fx[0] fy[0] (corresponde a (1,0) )
   foodc.resize(fnumber);
   //FIM DA TRY 1*****/


  /*****Try 2(distribuiçao simetrica) de food e death sites *****/
  //tenho de meter mais entries nos death para este ficar vermelho e o food ficar verde, escala dde cor e prop a escala de entries
  int JMAX=50;

  //food
  vector<int> fx;
  vector<int> fy;
 
  
  fx.push_back(1);
  fy.push_back(1);
  for(int j=0; j<0.5*JMAX; ++j){
    fdmat->Fill(1,1); }

  fx.push_back(4);
  fy.push_back(4);
  for(int j=0; j<0.5*JMAX; ++j){
    fdmat->Fill(4,4); }


 
  int fnumber=fx.size();// L*L/4 : 1 food site per 4 lattice squares
  
  //death zones
  vector<int> deathx;
  vector<int> deathy;

  deathx.push_back(1);
  deathy.push_back(4);
  for(int j=0; j<JMAX; ++j) {
    fdmat->Fill(1,4); }

  deathx.push_back(4);
  deathy.push_back(1);
  for(int j=0; j<JMAX; ++j) {
    fdmat->Fill(4,1); }
  
  
  int dnumber=deathx.size(); //1 death zone per 16 square lattices (aprox)

  //food limit 
  vector<int> foodc; //foodc[0] contador de fx[0] fy[0] (corresponde a (1,0) )
  foodc.resize(fnumber);
  //FIM DA TRY 2*****/		  

  //conditions
 int maxage=25; //after maxage steps cells die
  int maxswof=5; //max steps without food
  int x; int y; //position variables
  int dmax=100; //max steps of simulation
  int minagesexi=0; //geraçao 0 vem pronta a reproduzir
  int minagesex=minagesexi; //min age for reproduction
  int minagesexf=1; // geraçao >0 precisa de crescer para se reproduzir
  int flagserial=-1;//cheat variable to generate 1 child per pair and not two
  int gentrack=0;
  // int dailyflimit=L*L*cellnumberinit;
  int dailyflimit=10;
  int poplim=500;
  int dreg=0;
  int first=1;


  //*********************LIFE CYCLE *************************//
  for (int  d=0; d<dmax; ++d) {
    //limpa matrix apos cada dia
    cellmat->Reset();
    //reset aos contadores de food sites
    foodc.clear();
    foodc.resize(fnumber);
  
    for (int p=0; p<cellnumber; ++p) {
   
    
      //reproduction
  if (popA[p]->generation()>0) { minagesex=minagesexf;}

      if( popA[p]->age()>=minagesex) {
	//mete as de geraçoes mais antigas a acasalar com as de geraçoes mais recentes (preferencia evolutiva)
	for (int r=cellnumber-1; r>=0; --r){
	  if( cellnumber<poplim &&  popA[p]->xx()==popA[r]->xx() && r!=p) {
	    if( flagserial!=popA[p]->serial() &&   popA[p]->yy()==popA[r]->yy() && popA[r]->sex()!=popA[p]->sex() && popA[r]->time()==popA[p]->time()) {

	      //    cout << "REPPPPP: cell " <<popA[p]->serial()<< " + " << popA[r]->serial()<< endl;
	      flagserial=popA[r]->serial(); //only one child per pair
	      bool sex=rand.Integer(2);
	      currentserial=currentserial+1;
	      int gen=0;
	      if (popA[p]->generation()>popA[r]->generation()) {
		gen =popA[p]->generation(); }
	      else { gen=popA[r]->generation();}
	      popA.push_back(new cell (popA[r]->xx(),popA[r]->yy(),currentserial,1,0,0,sex,0,gen+1,d));
	      //    cellmat->Fill(popA[r]->xx(),popA[r]->yy());
	      cellnumber=cellnumber+1;
	    
	      //copy mem_tot to cell mem_g
	      //create or update and/or clear file
	      

	      if (gen+1> gentrack) { 
		gentrack=gen+1 ;
		//memory
	
		std::string s = SSTR( gentrack ); //gen 0 no mem
		string str ="mem_"+s+".txt";
		//	cout << str << endl;
		ifstream f2;
		ofstream f1;
		f1.open(str.c_str(), ios::app);
		f2.open("mem_tot.txt");
		for( std::string line; getline( f2, line ); )
		  {
		    f1 << line << endl;
		  }
		f1.close();
		f2.close();
	      
	      
	      }
	      r=-1; //break for loop - only one reproduction per day
	    }

	  }
	 
	
	}
	flagserial=-1;
      }


      if (first==1){
	//	initial conditions
	//	cout << "born: cell " << popA[p]->serial() << " gen: " <<popA[p]->generation() <<" alive: " << popA[p]->alive() << " hunger: " << popA[p]->hunger() <<" age: " << popA[p]->age() << " sex: " << popA[p]->sex() << " x: " << popA[p]->xx() <<" y: " << popA[p]->yy()<< endl;

      }

      if (first==0) {

	/***GOOD TRY 
	    int Nadj=3; //square root of number of max possible moves (adjacent squares)

	    //saves positions and death counts of every possible move
	    vector<int> px;
	    // px.resize(Nadj*Nadj);
	    vector<int> py;
	    //  py.resize(Nadj*Nadj);
	    vector<int> count;
	    // count.resize(Nadj*Nadj)

	    int county=0; //temporary counter


	    //moving
	    if (popA[p]->generation()==0) {
	    //x
	    if( popA[p]->xx()==maxx) {
	    int xmin=popA[p]->xx()-1;
	    int xmax=popA[p]->xx()+1-xmin; 
	    x=rand.Integer(xmax)+xmin; }
	    else {
	    int xmin=popA[p]->xx()-1;
	    if (xmin<0) {xmin=0;}
	    int xmax=popA[p]->xx() +1+1-xmin; 
	    x=rand.Integer(xmax)+xmin; }
	    //y
	    if( popA[p]->yy()==maxy) {
	    int ymin=popA[p]->yy()-1;
	    int ymax=popA[p]->yy()+1-ymin;
	    y=rand.Integer(ymax)+ymin;
	    }
	    else {
	    int ymin=popA[p]->yy()-1;
	    if (ymin<0) {ymin=0;}
	    int ymax=popA[p]->yy()+1+1-ymin;
	    y=rand.Integer(ymax)+ymin; }

	    popA[p]->setx(x);
	    popA[p]->sety(y);
	    popA[p]->setage(popA[p]->age()+1); //age
	    popA[p]->settime(d); 
	    }

	    else{


	    cout << "entrei no mov" << endl;
	    for (int ii=0;ii<Nadj; ++ii) {
	    x=popA[p]->xx()-1+ii;
	 
	    for(int jj=0; jj<Nadj; ++jj) {
	    y=popA[p]->yy()-1+jj;
	    
	    //only does math if position is possible (in the lattice) - easy way to account for special cases where the cell is in a corner etc
	    if( x>=0 && y>=0 && x<=maxx && y<=maxy ) {
	    //checks memory to ponderate option
	    ifstream file;
	    string name="mem_"+SSTR(popA[p]->generation()) + ".txt";
	    file.open(name.c_str());
	    string rline;
	    string wline;
	    county =0;
	    wline=SSTR(x)+","+SSTR(y);
	    while (getline( file, rline ) )  
	    { 		 
	  
	    if (rline == wline)
	    {
	    ++county;
	    //	cout <<"I AM SMART!!!"<< endl;
		
	    }
	    }
	    count.push_back(county);
	    px.push_back(x);
	    py.push_back(y);
	    cout << x<< " "<<y<<" " << county << endl;
		
	
	    }

	    }
	    }

	 
	    int dtot=0; //total of deaths in every adjacent square
	    for(size_t it=0; it<count.size(); ++it)  {
	    dtot=dtot+count[it];

	    }
	    cout << count.size() << endl;
	    double lolada=count.size();
	    double equiprob=  1/lolada;
	    cout << equiprob << endl;
	    vector<double> prob;
	    for(size_t it = 0; it<count.size(); ++it)  {
	    //avvoid infinity
	    if (dtot==0) {
	    prob.push_back(equiprob)  ;
	    cout <<"ADEEUS " << equiprob<< endl;
	    }
	    else {
	    prob.push_back(equiprob*exp( equiprob-(count[it]/dtot) ))  ;
	    cout <<"ADEEUS 2 " << equiprob*exp( equiprob-(count[it]/dtot) )<< endl;
	    }
    
	    }

	    //gerar aleatorio 
	    double val = rand.Uniform(1);
	    double pro=0;

	    for(size_t it =0; it< prob.size(); ++it)  {
	    pro=pro+prob[it];
	    cout <<"val " << val << "pro " << pro << endl;
	    cout <<"olaaaaa" <<  px[it]<< " " <<py[it] << endl;
	    if (val <= pro)   {  
	    cout << "entrei" << endl;
	    popA[p]->setx(px[it]);
	    popA[p]->sety(py[it]);
	    popA[p]->setage(popA[p]->age()+1); //age
	    popA[p]->settime(d);
	    it=prob.size()+1; //break loop

	    } 


	    }
	    }
	    //END OF GOOD TRY ***/
	//moving

	int Nadj=3; //square root of number of max possible moves (adjacent squares)

	//saves positions and death counts of every possible move
	vector<int> px;
	// px.resize(Nadj*Nadj);
	vector<int> py;
	//  py.resize(Nadj*Nadj);
	vector<int> count;
	// count.resize(Nadj*Nadj)
	vector<double> prob;

	int county=0; //temporary counter


	//moving
   	if (popA[p]->generation()==0) {
	  //x
	  if( popA[p]->xx()==maxx) {
	    int xmin=popA[p]->xx()-1;
	    int xmax=popA[p]->xx()+1-xmin; 
	    x=rand.Integer(xmax)+xmin; }
	  else {
	    int xmin=popA[p]->xx()-1;
	    if (xmin<0) {xmin=0;}
	    int xmax=popA[p]->xx() +1+1-xmin; 
	    x=rand.Integer(xmax)+xmin; }
	  //y
	  if( popA[p]->yy()==maxy) {
	    int ymin=popA[p]->yy()-1;
	    int ymax=popA[p]->yy()+1-ymin;
	    y=rand.Integer(ymax)+ymin;
	  }
	  else {
	    int ymin=popA[p]->yy()-1;
	    if (ymin<0) {ymin=0;}
	    int ymax=popA[p]->yy()+1+1-ymin;
	    y=rand.Integer(ymax)+ymin; }

	  popA[p]->setx(x);
	  popA[p]->sety(y);
	  popA[p]->setage(popA[p]->age()+1); //age
	  popA[p]->settime(d); 
	}

	else{


	  //  cout << "entrei no mov" << endl;
	  for (int ii=0;ii<Nadj; ++ii) {
	    x=popA[p]->xx()-1+ii;
	 
	    for(int jj=0; jj<Nadj; ++jj) {
	      y=popA[p]->yy()-1+jj;
	    
	      //only does math if position is possible (in the lattice) - easy way to account for special cases where the cell is in a corner etc
	      if( x>=0 && y>=0 && x<=maxx && y<=maxy ) {
		//checks memory to ponderate option
		ifstream file;
		string name="mem_"+SSTR(popA[p]->generation()) + ".txt";
		file.open(name.c_str());
		string rline;
		string wline;
		county =0;
		wline=SSTR(x)+","+SSTR(y);
		while (getline( file, rline ) )  
		  { 		 
	  
		    if (rline == wline)
		      {
			++county;
			//	cout <<"I AM SMART!!!"<< endl;
		
		      }
		  }
		count.push_back(county);
		px.push_back(x);
		py.push_back(y);
		//	cout << x<< " "<<y<<" " << county << endl;
		
	
	      }

	    }
	  }

	 
	  int dtot=0; //total of deaths in every adjacent square
	  for(size_t it=0; it<count.size(); ++it)  {
	    dtot=dtot+count[it];

	  }
	  // cout << count.size() << endl;
	  double lolada=count.size();
	  double equiprob=  1/lolada;
	  cout <<"nr cells adj: "<<  lolada << endl;
	 
	  for(size_t it = 0; it<count.size(); ++it)  {
	    //avvoid infinity
	    if (dtot==0) {
	      prob.push_back(equiprob)  ;
	      //  cout <<"ADEEUS " << equiprob<< endl;
	    }
	    else {
	      prob.push_back(equiprob*exp( equiprob-(count[it]/dtot) ))  ;
	      //   cout <<"ADEEUS 2 " << equiprob*exp( equiprob-(count[it]/dtot) )<< endl;
	    }
    
	  }
	      

	  //gerar aleatorio 

	  int j=0;
	  double pro=0;
	  size_t size = count.size();
       
	  while(j!=1) {
	    size_t ind = rand.Integer(size);
	    for (size_t i=0; i<prob.size(); i++) {
	      cout << "coord cell " << i << ": " <<px[i] <<","<<py[i]<< endl;
	      cout << "prob cell " << i << ": " <<prob[i] << endl;
	      if(i==ind){  pro= prob[i];}
	    }
	    double val=rand.Uniform(equiprob);
          cout <<"possible cell coord: "  <<px[ind] <<","<<py[ind]<< endl;
	    if (val <= pro)   {  
	      //	 cout << "entrei" << endl;
	      popA[p]->setx(px[ind]);
	      popA[p]->sety(py[ind]);
	      popA[p]->setage(popA[p]->age()+1); //age
	      popA[p]->settime(d);
	      j=1; //break loop
	      cout <<"chosen cell coord: "  <<px[ind] <<","<<py[ind]<< endl;
	    }
	  }
	}
      
	     


     
	  
	/***
	 //gerar aleatorio 
	 int size = count.size();
	 double val = rand.Uniform(size);
	 double pro=0;

         for(size_t it =0; it< prob.size(); ++it)  {
	 pro=pro+prob[it];
	 cout <<"val " << val << "pro " << pro << endl;
	 cout <<"olaaaaa" <<  px[it]<< " " <<py[it] << endl;
	 if (val <= pro)   {  
	 cout << "entrei" << endl;
	 popA[p]->setx(px[it]);
	 popA[p]->sety(py[it]);
	 popA[p]->setage(popA[p]->age()+1); //age
	 popA[p]->settime(d);
	 it=prob.size()+1; //break loop
	***/		
      

      }
    }
   
    //conta a partir do fim, assim garante que as mais novas comem primeiro
    for(int p=cellnumber-1; p>=0; --p) {
      //food
      bool ate=0;
      for (int o=0; o<fnumber; ++o) {
	if ((popA[p]->xx() == fx[o] && popA[p]->yy() == fy[o]) && (foodc[o]<dailyflimit)) {
	  popA[p]->sethunger(0);
	  ate=1;
	  ++foodc[o];
	  //  cout << "AAAAAAAAAAAA" << foodc[o] << endl;
	}
      }
	
      if(ate==0) {
	popA[p]->sethunger(popA[p]->hunger()+1); }

      //death (nao me apeteceu criar uma funçao pa escrever no mem_tot e lidar com os probs disso, dai o codigo repetido)
      int dflag=0;
      if (popA[p]->hunger()==maxswof){
	dflag=1;
	// cout <<"died of hunger" << endl;
	//add to mem_tot coords where cell has died
	fstream F;
	F.open("mem_tot.txt",ios::in | ios::out | ios::app);
	F <<  popA[p]->xx() << "," << popA[p]->yy() << endl;
      
	F.close();
	++dcount;
      }
      else if( popA[p]->age()==maxage){
	dflag=1;
	//	cout <<"death by natural causes" << endl;
	//add to mem_tot coords where cell has died
	fstream F1;
	F1.open("mem_tot.txt",ios::in | ios::out | ios::app);
	F1 <<  popA[p]->xx() << "," << popA[p]->yy() << endl;
      
	F1.close();
	++dcount;
      }
      else  {
	for(int f=0; f<dnumber; ++f) {
	  if (popA[p]->xx()==deathx[f] && popA[p]->yy()==deathy[f]) {
	    dflag=1;
	    // cout <<"entered DEATH ZONE" << endl;
	    //add to mem_tot coords where cell has died
	    fstream F2;
	    F2.open("mem_tot.txt",ios::in | ios::out | ios::app);
	    F2 <<  popA[p]->xx() << "," << popA[p]->yy() << endl;
      
	    F2.close();
	    ++dcount;
	  }

	}
      }

      if (dflag==1) {
	popA[p]->setlife(0);
      }
   
      //	cout << "day " << d << " report: "<< "cell "<< popA[p]->serial() << " gen: " <<popA[p]->generation() <<" alive: " << popA[p]->alive() << " hunger: " << popA[p]->hunger() <<" age: " << popA[p]->age() << " sex: " << popA[p]->sex() << " x: " << popA[p]->xx() <<" y: " << popA[p]->yy()<< endl;
    
      dflag=0;
      //go to graveyard
      if(popA[p]->alive()==0) {   
	popA[p]->setx(-1);
	popA[p]->sety(-1);
	//	cout << "died: cell "<< popA[p]->serial() << " gen: " <<popA[p]->generation() <<" alive: " << popA[p]->alive() << " hunger: " << popA[p]->hunger() <<" age: " << popA[p]->age() << " sex: " << popA[p]->sex() << " x: " << popA[p]->xx() <<" y: " << popA[p]->yy()<< endl;
	
	if(cellnumber==1) {
	  dreg=d;
d=dmax+1 ;
}//cheat to break life loop
	
	popA.erase(popA.begin()+p);
	cellnumber=cellnumber-1; 
	dflag=1; 
      }
      if(dflag==0){
	cellmat->Fill(popA[p]->xx(),popA[p]->yy()); }
    
    }
  
      cout <<"day " << d << endl;
    if (d==dmax-1) {dreg=d+1; }
     cout <<"CELLNUMBER: " << cellnumber << endl;
    // cout << "dcount: " <<dcount << endl;
    fdmat->SetEntries(cellmat->GetEntries()); //shows entries of cell histogram (I am printing the fdmat histogram)
  

  

      D.DumpPad("Pad");
      D.DrawPad("Pad");
        string namepic ="day_"+SSTR(d)+".pdf";
      D.Print(namepic.c_str());
    first=0;
 
  }
  if(dreg==-1) {dreg=0;} //doesnt last one day
  cout << "dias pop viveu: " << dreg << endl;
  double maxage2=maxage;
  myfile << dreg/maxage2 << endl;

   }

   myfile.close();
}


