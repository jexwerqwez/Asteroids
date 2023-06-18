#include "../includes/settings.h"
#define ELEMENTS 5

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
      if (str == "fuzzy_coef") {
        getline(file, str);
        istringstream iss(str);
        string number;
        int i = 0;
        while (getline(iss, number, ',')) {
          set.fuzzy_coef[i] = stof(number);
          i++;
        }
      }
      if (str == "fuzzy_dist") {
        getline(file, str);
        istringstream iss(str);
        string number;
        int i = 0;
        while (getline(iss, number, ',')) {
          set.fuzzy_dist[i] = stoi(number);
          i++;
        }
      }
      if (str == "fuzzy_prio") {
        getline(file, str);
        istringstream iss(str);
        string number;
        int i = 0;
        while (getline(iss, number, ',')) {
          set.fuzzy_prio[i] = stoi(number);
          i++;
        }
      }
    }
  }
  return 0;
}

// void Settings::outputZoneSettings(std::string filename) {
//   std::ofstream file(filename);
//   if (file.is_open()) {
//     file << "fuzzy_coef=";
//     for (int i = 0; i < ELEMENTS; i++) {
//       file << fuzzy_coef[i] << " ";
//     }
//     file << endl;
//     file << "fuzzy_dist=";
//     for (int i = 0; i < ELEMENTS; i++) {
//       file << fuzzy_dist[i] << " ";
//     }
//     file << endl;
//     file << "fuzzy_prio=";
//     for (int i = 0; i < ELEMENTS; i++) {
//       file << fuzzy_prio[i] << " ";
//     }
//     file.close();
//   } else {
//     std::cout << "Ошибка открытия файла!" << std::endl;
//   }
// }
