#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Player 1(Kita) dan Player 2 (Bot)
// Spade, Wajik, keriting, dan Heart (dihilangkan)

// Rules Menang
// Three of a kind (7,7,7) & 7,8,9

// Kartu = Angka
// Setiap Player akan mendapat 3 kartu pertama.
// Giliran player = wajib membuang salah satu kartu.

// Cek kemenangan
// Kartu ditangan = Rules Menang

// !==
// Berpindah giliran ke player selanjutnya

// === Kelas dasar (Base Class) ===
class Player
{
protected:
    int hand[3]; // Menyimpan 3 kartu pemain
    string name; // Nama pemain (bisa "Kamu" atau "Bot")

public:
    // Constructor kelas Player - akan otomatis dijalankan saat objek dibuat
    Player(string n) : name(n)
    {
        for (int i = 0; i < 3; i++)
            hand[i] = rand() % 9 + 1; // Mengacak kartu awal
        cout << "Constructor Player untuk " << name << " dipanggil.\n";
    }

    // Destructor kelas Player - dipanggil otomatis saat objek dihapus
    virtual ~Player()
    {
        cout << "Destructor Player untuk " << name << " dipanggil.\n";
    }

    // Menampilkan kartu pemain ke layar
    void showHand()
    {
        cout << name << "'s card: ";
        for (int i = 0; i < 3; i++)
            cout << "[" << hand[i] << "] ";
        cout << endl;
    }

    // Mengecek apakah 3 kartu bernilai sama (Three of a Kind)
    bool checkThreeOfAKind()
    {
        return hand[0] == hand[1] && hand[1] == hand[2];
    }

    // Mengecek apakah kartu membentuk urutan berurutan (Run)
    bool checkRun()
    {
        int temp[3] = {hand[0], hand[1], hand[2]};
        sort(temp, temp + 3); // Urutkan kartu
        return temp[1] == temp[0] + 1 && temp[2] == temp[1] + 1;
    }

    // Mengecek apakah pemain menang
    bool checkWin()
    {
        return checkThreeOfAKind() || checkRun();
    }

    // 52 Kartu, 3 player 1, 3 player 2,
    // 52 - 6 = Deck kita

    // Menarik kartu dari deck ke posisi terakhir (setelah membuang)
    void drawCard(int deck[], int &deckSize)
    {
        if (deckSize <= 0)
        {
            cout << "Deck habis!\n";
            return;
        }
        int card = deck[--deckSize];
        hand[2] = card;
        cout << name << " draw: " << card << endl;
    }

    // Fungsi virtual murni (harus di-override di class turunan)
    virtual void discardCard() = 0;
};

// === Kelas turunan HumanPlayer dari Player ===
class HumanPlayer : public Player
{
public:
    // Constructor HumanPlayer memanggil constructor Player terlebih dahulu
    HumanPlayer(string n) : Player(n)
    {
        cout << "Constructor HumanPlayer untuk " << name << " dipanggil.\n";
    }

    ~HumanPlayer()
    {
        cout << "Destructor HumanPlayer untuk " << name << " dipanggil.\n";
    }

    // Implementasi fungsi buang kartu untuk pemain manusia
    void discardCard() override
    {
        int choice;
        cout << "Pilih kartu yang ingin dibuang (1-3): ";
        cin >> choice;
        choice--;
        if (choice < 0 || choice >= 3)
        {
            cout << "Input tidak valid. Otomatis buang kartu pertama.\n";
            choice = 0;
        }
        for (int i = choice; i < 2; i++)
            hand[i] = hand[i + 1];
        hand[2] = 0; // slot kosong, nanti akan diganti oleh drawCard
    }
};

// === Kelas turunan AIPlayer dari Player ===
class AIPlayer : public Player
{
public:
    AIPlayer(string n) : Player(n)
    {
        cout << "Constructor AIPlayer untuk " << name << " dipanggil.\n";
    }

    ~AIPlayer()
    {
        cout << "Destructor AIPlayer untuk " << name << " dipanggil.\n";
    }

    // Implementasi sederhana: AI selalu buang kartu pertama
    void discardCard() override
    {
        cout << name << " buang kartu pertama.\n";
        for (int i = 0; i < 2; i++)
            hand[i] = hand[i + 1];
        hand[2] = 0;
    }
};

// Fungsi untuk mengacak deck menggunakan algoritma shuffle sederhana
void shuffleDeck(int deck[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int j = rand() % size;
        swap(deck[i], deck[j]);
    }
}

// === Fungsi utama ===
int main()
{
    srand(time(0)); // Seed random
    int deck[36];   // Deck dengan 36 kartu
    int deckSize = 36;

    // Isi deck: 4 buah untuk setiap angka dari 1 sampai 9
    for (int i = 0; i < 36; i++)
        deck[i] = (i % 9) + 1;

    shuffleDeck(deck, deckSize);

    // Buat objek pemain
    HumanPlayer human("Kamu");
    AIPlayer ai("Bot");

    int turn = 0; // Penanda giliran

    // Game loop: jalan terus sampai ada yang menang atau deck habis
    while (true)
    {
        cout << "\n========== GILIRAN ";
        cout << (turn % 2 == 0 ? "KAMU" : "AI") << " ==========\n";

        // Pointer ke pemain saat ini (human atau ai)
        Player *current = (turn % 2 == 0) ? (Player *)&human : (Player *)&ai;

        current->showHand();               // Tampilkan kartu
        current->discardCard();            // Buang 1 kartu
        current->drawCard(deck, deckSize); // Ambil 1 kartu
        current->showHand();               // Tampilkan kartu setelah draw

        // Cek apakah menang
        if (current->checkWin())
        {
            cout << "\n"
                 << (turn % 2 == 0 ? "KAMU" : "AI") << " MENANG! \n";
            if (current->checkThreeOfAKind())
                cout << "Dengan kombinasi: Three of a Kind!\n";
            else
                cout << "Dengan kombinasi: Run (berurutan)!\n";
            break;
        }

        // Jika deck habis, permainan berakhir seri
        if (deckSize <= 0)
        {
            cout << "\nDeck habis, permainan berakhir seri.\n";
            break;
        }

        turn++; // Ganti giliran
    }

    return 0;
}
