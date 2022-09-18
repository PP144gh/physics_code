void mRoot1(){
  TObjectTable A;
  A.Print("all");
  cout<<endl<<endl;
  TCanvas *c = new TCanvas;
  TF1 *f = new TF1 ("f","2*x*x",-10,10);
  TH1F **h = new TH1F*[3];
  h[0]=new TH1F ("h0h","h0h",100,-10.,10.);
  h[1]=new TH1F ("h1h","h1h",100,-10.,10.);
  h[2]=new TH1F ("h2h","h2h",100,-10.,10.);
  srand(time(NULL));
  for(Double_t i=0;i<5000;++i){
    h[0]->Fill( ((double) rand()/2147483648.0)*10-5);
  }
  h[0]->DrawCopy();
  for (Double_t i=0;i<5000;++i){
    h[1]->Fill(f->GetRandom());
  }
  h[1]->DrawCopy("same");
  for (Double_t i=0;i<5000;++i){
    h[2]->Fill(gRandom->Gaus(-0.5));
  }
  h[2]->DrawCopy("same");
  A.Add(f);
  for (int j=0;j<3;++j)
    A.Add(h[j]);
  A.Print("all");
  cout<<endl<<endl;
  TF1 **g = new TF1*[2];
  g[0]=new TF1("g0","4*x*x*x*x-2*x*x-2",-4,4);
  g[1]=new TF1("g1","sqrt(x*x+2*9*9.1*exp(-15)*x)*sqrt(1.1612-x)*(x+9*9.1*exp(-15))",0,1.1612);
  g[0]->Draw();
  g[1]->Draw();
  for (int j=0;j<2;++j)
    A.Add(g[j]);
  A.Print("all");
}
