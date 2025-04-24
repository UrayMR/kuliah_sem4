#include "iostream"

using namespace std;

class User
{
private:
  string password;

protected:
  string fullName;

public:
  static int jumlahUser;
  string username;

  User()
  {
    jumlahUser++;
  }

  void registerUser(string _username, string _password)
  {
    username = _username;
    password = _password;
  }
};

class Member : public User
{
public:
  string getMember(string _username)
  {
    cout << username << endl;
    if (_username == username)
      return username;

    return "Not the same";
  }
};

int User::jumlahUser = 0;

int main()
{
  User u1;
  u1.registerUser("Uray", "Rosi");

  cout << "Nama user 1: " << u1.username << endl;
  cout << "Jumlah user 1: " << u1.jumlahUser << endl;

  Member m1;
  cout << "Get member m1: " << m1.getMember("Uray");

  return 0;
}
