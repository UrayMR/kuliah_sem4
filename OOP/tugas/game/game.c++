#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class RandomNumber
{
private:
  int number;

public:
  RandomNumber()
  {
    srand(time(0));
    number = rand() % 21;
  }

  int getNumber()
  {
    return number;
  }
};

class Player
{
private:
  string name;
  int guess;

public:
  Player(string n)
  {
    name = n;
    guess = 0;
  }

  void makeGuess()
  {
    cout << "Hello, " << name << "! Masukkan tebakan (0-20): ";
    cin >> guess;
  }

  int getGuess()
  {
    return guess;
  }

  string getName()
  {
    return name;
  }
};

class Life
{
private:
  int life;

public:
  Life(int lifeCount) : life(lifeCount) {}

  void decreaseLife()
  {
    life--;
  }

  int getLife()
  {
    return life;
  }

  bool isAlive()
  {
    return life > 0;
  }
};

class Game
{
private:
  RandomNumber randomNumber;
  Player player;
  Life life;

public:
  Game(string playerName, int lifeCount) : player(playerName), life(lifeCount) {}

  void play()
  {
    int target = randomNumber.getNumber();
    cout << "Selamat datang di permainan Tebak Angka! Anda memiliki " << life.getLife() << " nyawa." << endl;

    while (life.isAlive())
    {
      player.makeGuess();
      if (player.getGuess() > target)
      {
        cout << "Terlalu tinggi! Nyawa berkurang 1." << endl;
      }
      else if (player.getGuess() < target)
      {
        cout << "Terlalu rendah! Nyawa berkurang 1." << endl;
      }
      else
      {
        cout << "Selamat, " << player.getName() << "! Anda menebak dengan benar." << endl;
        return;
      }
      life.decreaseLife();
      cout << "Sisa nyawa: " << life.getLife() << endl;
    }
    cout << "Game Over! Angka yang benar adalah " << target << "." << endl;
  }
};

int main()
{
  string name;
  cout << "Masukkan nama Anda: ";
  cin >> name;
  Game game(name, 5); // Pemain diberikan 5 nyawa
  game.play();
  return 0;
}
