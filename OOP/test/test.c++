#include "iostream"
using namespace std;

class Segitiga
{
private:
  float alas, tinggi;

public:
  // Construct
  Segitiga()
  {
    this->alas = 0;
    this->tinggi = 0;
  }

  Segitiga(float _alas, float _tinggi)
  {
    this->alas = _alas;
    this->tinggi = _tinggi;
  }

  float luas()
  {
    return 0.5 * alas * tinggi;
  }

  // Destructor
  ~Segitiga()
  {
    cout << "Destructor Called" << endl;
  }
};

int main()
{
  Segitiga ss[0];
  ss[0] = Segitiga(20, 5);
  Segitiga s(10, 5);

  cout << "Luas Segitiga: " << s.luas() << endl;
  cout << "Luas Segitiga array: " << ss[0].luas() << endl;

  return 0;
}