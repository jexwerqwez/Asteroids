#include "../includes/settings.h"

int Settings::parser(Settings &set, string &filename) {
  ifstream file(filename);
  string str;
  if (!file.is_open()) {
    cout << "Ошибка открытия файла!" << endl;
    return -1;
  } else {
    while (!file.eof()) {
      getline(file, str, '=');
      if (str == "height") {
        getline(file, str);
        set.height = stoi(str);
      }
      if (str == "width") {
        getline(file, str);
        set.width = stoi(str);
      }
      if (str == "score") {
        getline(file, str);
        set.score = stoi(str);
      }
      if (str == "hp") {
        getline(file, str);
        set.hithpoint = stoi(str);
      }
    }
  }
  return 0;
}
