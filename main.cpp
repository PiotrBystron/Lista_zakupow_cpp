#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

void displayItems(map<string, int> &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    cout << it->first << " (" << it->second << ")" << endl;
  }
}

void addItem(map<string, int> &items) {
  string item;
  int quantity;

  cout << "Podaj nazwę produktu" << endl;
  cin >> item;
  cout << "Podaj ilość" << endl;
  // cin >> quantity;

  while (1) {
    cin >> quantity;
    if (quantity > 0) {
      break;
    } else {
      cout << "Musisz podać liczbę większą od 0!" << endl;
      cin.clear();
      cin.ignore(40, '\n');
    }
  }

  if (items.count(item) > 0) {
    items.at(item) += quantity;
    cout << "Dodano dodatkowe sztuki." << endl;
  } else {
    items.emplace(item, quantity);
    cout << "Dodano " << item << " ilość: " << quantity << endl;
  }
}

void removeItem(map<string, int> &items) {
  cout << "Jaki produkt chcesz usunąć?" << endl;
  string item;
  cin >> item;
  items.erase(item);
  cout << "Produkt: " << item << " został usunięty." << endl;
}

void clearList(map<string, int> &items) {
  items.clear();
  cout << "Lista została wyczyszczona." << endl;
}

void saveListToFile(map<string, int> &items) {
  ofstream itemsList;
  itemsList.open("Lista.txt");

  for (auto it = items.begin(); it != items.end(); ++it) {
    itemsList << it->first << "_" << it->second << endl;
  }
  itemsList.close();
}

void loadListFromFile(map<string, int> &items) {
  items.clear();
  ifstream itemsList("Lista.txt");
  while (itemsList) {
    string key{}, value{};
    {
      getline(itemsList, key, '_') && getline(itemsList, value);
      if (itemsList) {
        items[key] = stoi(value);
      }
    }
  }
  cout << "Lista zakupów została wczytana" << endl;
  itemsList.close();
}

int main() {
  map<string, int> items;
  int option = -1;

  while (option != 0) {
    cout << "0 - wyłącz program" << endl;
    cout << "1 - wyświetl produkty" << endl;
    cout << "2 - dodaj produkty" << endl;
    cout << "3 - usuń produkty" << endl;
    cout << "4 - wyczyść listę" << endl;
    cout << "5 - zapisz listę do pliku" << endl;
    cout << "6 - wczytaj listę z pliku" << endl;
    cout << "7 - wyczyść konsolę" << endl;
    cout << "Wybierz opcję: ";

    while (!(cin >> option)) {
      cout << "Musisz podać liczbę!" << endl;
      cin.clear();
      cout << "Wybierz opcję: ";
      cin.ignore(40, '\n');
    }

    switch (option) {
    case 0:
      cout << "Program został wyłączony" << endl;
      break;
    case 1:
      displayItems(items);
      break;
    case 2:
      addItem(items);
      break;
    case 3:
      removeItem(items);
      break;
    case 4:
      clearList(items);
      break;
    case 5:
      saveListToFile(items);
      break;
    case 6:
      loadListFromFile(items);
      break;
    case 7:
      system("clear");
      break;
    }
  }
}