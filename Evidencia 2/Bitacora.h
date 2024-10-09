#ifndef BITACORA_H
#define BITACORA_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

enum meses_year {
    Jan = 1, Feb = 2, Mar = 3, Abr = 4, May = 5, Jun = 6, Jul = 7, Aug = 8, Sep = 9, Oct = 10, Nov = 11, Dec = 12,
};

class Bitacora {
private:
    string mes_str;
    meses_year mes;
    string tiempo, dir_ip, msg;
    int dia;
    static const map<string, meses_year> month_map;

public:
    Bitacora();
    ~Bitacora();
    Bitacora(const string&, int, const string&, const string&, const string&);

    void set_mes(const string&);
    void set_dia(int);
    void set_time(const string&);
    void set_dir_ip(const string&);
    void set_msg(const string&);

    meses_year get_mes() const;
    int get_dia() const;
    string get_time() const;
    string get_dir_ip() const;
    string get_msg() const;

    bool isEarlierThan(const Bitacora& other) const;
    bool isWithinRange(const Bitacora& start, const Bitacora& end) const;

    bool operator<(const Bitacora& other) const;
    bool operator<=(const Bitacora& other) const;
    bool operator>(const Bitacora& other) const;
    bool operator>=(const Bitacora& other) const;

    bool compareIP(const Bitacora& other) const;
};

#endif // BITACORA_H