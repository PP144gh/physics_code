class PixelDet {
 public:
  PixelDet();
  ~PixelDet();
  int* EventNoise(float);
  void SetRows(int x){a=x;};
  void SetCols(int x){b=x;};
  void SetSize(double x){c=x;};
  int GetRows(){return a;};
  int GetCols(){return b;};
  double GetSize(){return c;};
 private:
  int a;
  int b;
  double c;
  bool **p;
};
