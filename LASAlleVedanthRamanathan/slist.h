/*
Header file for single linked list class library
*/

#include <string>
#include <cstring>
#include <iostream>
using namespace std;

struct Airport {
    char code[5]{};
    double longitude{};
    double latitude{};

    Airport() = default;

    Airport(const char* cod, double lat, double lon) {
        strcpy(code, cod);

        latitude = lat;
        longitude = lon;
    }

    void dsp() {
        cout << "{" << code << ", (" << latitude << ", " << longitude << ")}" << endl;
    }
};

struct Node {
    Airport* dat;
    Node* next;
};

class slist {
public:
    int length{};
    Node* head{};
    Node* tail{};

    slist();
    slist(slist* s, int i1, int i2);
    ~slist();
    void add(Airport* a);
    void clear();
    bool equals(const slist& s) const;
    Node* get(int idx) const;
    void insert(int idx, Airport* a);
    void exchg(int i1, int i2) const;
    void swap(int i1, int i2);
    bool isEmpty() const;
    Node* remove(int idx);
    void set(int idx, Airport* a) const;
    int size() const;
    slist subList(int s, int e);
    string toString() const;
}; 

