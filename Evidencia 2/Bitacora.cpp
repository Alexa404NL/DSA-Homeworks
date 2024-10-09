#include "Bitacora.h"
#include <sstream>
#include <iomanip>

using namespace std;

const map<string, meses_year> Bitacora::month_map = {
    {"Jan", Jan}, {"Feb", Feb}, {"Mar", Mar}, {"Abr", Abr},
    {"May", May}, {"Jun", Jun}, {"Jul", Jul}, {"Aug", Aug},
    {"Sep", Sep}, {"Oct", Oct}, {"Nov", Nov}, {"Dec", Dec}
};

Bitacora::Bitacora() {
    set_mes("Jan");
    dia = 1;
    tiempo = "00:00:00";
    dir_ip = "###.##.###.###:####";
    msg = "no comment";
}

Bitacora::Bitacora(const string& month_str, int day, const string& _tiempo, const string& IP, const string& message) {
    set_mes(month_str);
    dia = day;
    tiempo = _tiempo;
    dir_ip = IP;
    msg = message;
}

Bitacora::~Bitacora() {
}

void Bitacora::set_mes(const string& month_str) {
    mes_str = month_str;
    auto it = month_map.find(month_str);
    if (it != month_map.end()) {
        mes = it->second;
    } else {
        throw invalid_argument("Invalid month string");
    }
}

void Bitacora::set_dia(int day) {
    dia = day;
}

void Bitacora::set_time(const string& _tiempo) {
    tiempo = _tiempo;
}

void Bitacora::set_dir_ip(const string& IP) {
    dir_ip = IP;
}

void Bitacora::set_msg(const string& message) {
    msg = message;
}

meses_year Bitacora::get_mes() const {
    return mes;
}

int Bitacora::get_dia() const {
    return dia;
}

string Bitacora::get_time() const {
    return tiempo;
}

string Bitacora::get_dir_ip() const {
    return dir_ip;
}

string Bitacora::get_msg() const {
    return msg;
}

//🦆 

bool Bitacora::isEarlierThan(const Bitacora& other) const {
    if (mes != other.mes) return mes < other.mes;
    if (dia != other.dia) return dia < other.dia;
    return tiempo < other.tiempo;
}

bool Bitacora::isWithinRange(const Bitacora& start, const Bitacora& end) const {
    return !isEarlierThan(start) && !end.isEarlierThan(*this);
}

bool Bitacora::operator<(const Bitacora& other) const {
    if (mes != other.mes) return mes < other.mes;
    if (dia != other.dia) return dia < other.dia;
    return tiempo < other.tiempo;
}

bool Bitacora::operator<=(const Bitacora& other) const {
    if (mes != other.mes) return mes < other.mes;
    if (dia != other.dia) return dia < other.dia;
    return tiempo <= other.tiempo;
}

bool Bitacora::operator>(const Bitacora& other) const {
    return !(*this <= other);
}

bool Bitacora::operator>=(const Bitacora& other) const {
    return !(*this < other);
}

bool Bitacora::compareIP(const Bitacora& other) const {
    return dir_ip < other.dir_ip;
}