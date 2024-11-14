// Bitacora.cpp
#include "Bitacora.h"
#include <sstream>
#include <stdexcept>

using namespace std;

const std::map<std::string, meses_year> Bitacora::month_map = {
    {"Jan", Jan}, {"Feb", Feb}, {"Mar", Mar}, {"Apr", Abr}, {"May", May}, {"Jun", Jun},
    {"Jul", Jul}, {"Aug", Aug}, {"Sep", Sep}, {"Oct", Oct}, {"Nov", Nov}, {"Dec", Dec}
};

Bitacora::Bitacora() {}

Bitacora::Bitacora(const std::string& month_str, int day, const std::string& _tiempo, const std::string& IP_origin, const std::string& IP_dest, const std::string& message)
    : mes_str(month_str), dia(day), tiempo(_tiempo), dir_ip_origin(IP_origin), dir_ip_dest(IP_dest), msg(message) {
    set_mes(month_str);
}

Bitacora::~Bitacora() {}

void Bitacora::set_mes(const std::string& month_str) {
    auto it = month_map.find(month_str);
    if (it != month_map.end()) {
        mes = it->second;
    } else {
        throw std::invalid_argument("Invalid month string");
    }
}

void Bitacora::set_dia(int day) {
    dia = day;
}

void Bitacora::set_time(const std::string& _tiempo) {
    tiempo = _tiempo;
}

void Bitacora::set_dir_ip_origin(const std::string& IP_origin) {
    dir_ip_origin = IP_origin;
}

void Bitacora::set_dir_ip_dest(const std::string& IP_dest) {
    dir_ip_dest = IP_dest;
}

void Bitacora::set_msg(const std::string& message) {
    msg = message;
}

meses_year Bitacora::get_mes() const {
    return mes;
}

int Bitacora::get_dia() const {
    return dia;
}

std::string Bitacora::get_time() const {
    return tiempo;
}

std::string Bitacora::get_dir_ip_origin() const {
    return dir_ip_origin;
}

std::string Bitacora::get_dir_ip_dest() const {
    return dir_ip_dest;
}

std::string Bitacora::get_msg() const {
    return msg;
}

std::string Bitacora::getIPClass() const {
    int first_octet = splitIP(dir_ip_origin)[0];
    if (first_octet >= 1 && first_octet <= 126) {
        return "Class A";
    } else if (first_octet >= 128 && first_octet <= 191) {
        return "Class B";
    } else if (first_octet >= 192 && first_octet <= 223) {
        return "Class C";
    }
    return "Other";
}

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

std::vector<int> Bitacora::splitIP(const string& ip) {
    vector<int> result;
    stringstream ss(ip);
    string segment;
    while (getline(ss, segment, '.')) {
        size_t colon_pos = segment.find(':');
        if (colon_pos != string::npos) {
            result.push_back(stoi(segment.substr(0, colon_pos)));
            result.push_back(stoi(segment.substr(colon_pos + 1)));
        } else {
            result.push_back(stoi(segment));
        }
    }
    return result;
}

bool Bitacora::compareIP(const Bitacora& other) const {
    vector<int> ip1 = splitIP(this->dir_ip_origin);
    vector<int> ip2 = splitIP(other.dir_ip_origin);

    for (size_t i = 0; i < ip1.size(); ++i) {
        if (ip1[i] != ip2[i]) {
            return ip1[i] < ip2[i];
        }
    }
    return false;
}