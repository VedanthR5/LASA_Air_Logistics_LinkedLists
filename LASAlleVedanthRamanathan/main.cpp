#include "slist.h"
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

double deg2rad(double deg) { return (deg * 3.14159265358979323846 / 180); }

double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  return 2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

double distToAUS(Airport *a) {
  return distanceEarth(a->latitude, a->longitude, 30.1944, 97.67);
}

int partition(slist *s, int low, int high) {
  double pivot = distToAUS(s->get(high)->dat);
  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (distToAUS(s->get(j)->dat) <= pivot) {
      i++;
      s->exchg(i, j);
    }
  }
  s->exchg(i + 1, high);
  return i + 1;
}

void quickSort(slist *s, int low, int high) {
  if (low < high) {
    int pi = partition(s, low, high);

    quickSort(s, low, pi - 1);
    quickSort(s, pi + 1, high);
  }
}

void simpleSortTotal(slist *s) { quickSort(s, 0, s->size() - 1); }

int main() {
  auto *airportArr = new slist();

  ifstream infile("USAirportCodes.csv");
  auto maxApt = new Airport("TST", 30, 98);

  if (infile) {
    while (infile.good()) {
      auto a = new Airport();
      infile.getline(a->code, 256, ',');
      char cNum[10];
      infile.getline(cNum, 256, ',');
      a->latitude = atof(cNum);
      infile.getline(cNum, 256, '\n');
      a->longitude = atof(cNum);

      if (distToAUS(a) > distToAUS(maxApt) && a->longitude != 0 &&
          a->latitude != 0)
        maxApt = a;

      if (distToAUS(a) <= 100.0 * 1.609)
        airportArr->add(a);
    }
    infile.close();
  } else {
    cout << "Error opening file";
    return 1;
  }

  simpleSortTotal(airportArr);

  cout << "Farthest airport from KAUS: " << maxApt->code << " at "
       << distToAUS(maxApt) << " km" << endl;
  cout << "Airports within 100 miles of KAUS: " << endl
       << airportArr->toString();

  delete airportArr;
  delete maxApt;

  return 0;
}

double deg2rad(double deg) { return (deg * 3.14159265358979323846 / 180); }

double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  return 2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

double distToAUS(Airport *a) {
  return distanceEarth(a->latitude, a->longitude, 30.1944, 97.67);
}

int partition(slist* s, int low, int high) {
  double pivot = distToAUS(s->get(high)->dat);
  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (distToAUS(s->get(j)->dat) <= pivot) {
      i++;
      s->exchg(i, j);
    }
  }
  s->exchg(i + 1, high);
  return i + 1;
}

void quickSort(slist* s, int low, int high) {
  if (low < high) {
    int pi = partition(s, low, high);

    quickSort(s, low, pi - 1);
    quickSort(s, pi + 1, high);
  }
}

void simpleSortTotal(slist* s) {
  quickSort(s, 0, s->size() - 1);
}

int main() {
  ifstream infile;
  char cNum[10];
  auto *airportArr = new slist();

  infile.open("USAirportCodes.csv", ifstream::in);
  auto maxApt = new Airport("TST", 30, 98);
  if (infile.is_open()) {
    while (infile.good()) {
      auto a = new Airport();
      infile.getline(a->code, 256, ',');
      infile.getline(cNum, 256, ',');
      a->latitude = atof(cNum); 
      infile.getline(cNum, 256, '\n');
      a->longitude = atof(cNum); 

      if (distToAUS(a) > distToAUS(maxApt) && a->longitude != 0 &&
          a->latitude != 0)
        maxApt = a;

      if (distToAUS(a) <= 100.0 * 1.609)
        airportArr->add(a);
    }
    infile.close();
  } else
    cout << "Error opening file";

  simpleSortTotal(airportArr);

  cout << "Farthest airport from KAUS: " << maxApt->code << " at "
       << distToAUS(maxApt) << " km" << endl;
  cout << "Airports within 100 miles of KAUS: " << endl
       << airportArr->toString();
}
