// Bitacora.h
#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <map>
#include <vector>

enum meses_year { Jan, Feb, Mar, Abr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };

class Bitacora {
public:
    Bitacora();
    Bitacora(const std::string& month_str, int day, const std::string& _tiempo, const std::string& IP_origin, const std::string& IP_dest, const std::string& message);
    ~Bitacora();

    void set_mes(const std::string& month_str);
    void set_dia(int day);
    void set_time(const std::string& _tiempo);
    void set_dir_ip_origin(const std::string& IP_origin);
    void set_dir_ip_dest(const std::string& IP_dest);
    void set_msg(const std::string& message);

    meses_year get_mes() const;
    int get_dia() const;
    std::string get_time() const;
    std::string get_dir_ip_origin() const;
    std::string get_dir_ip_dest() const;
    std::string get_msg() const;
    std::string getIPClass() const;

    bool isEarlierThan(const Bitacora& other) const;
    bool isWithinRange(const Bitacora& start, const Bitacora& end) const;

    bool operator<(const Bitacora& other) const;
    bool operator<=(const Bitacora& other) const;
    bool operator>(const Bitacora& other) const;
    bool operator>=(const Bitacora& other) const;

    bool compareIP(const Bitacora& other) const;

private:
    std::string mes_str;
    meses_year mes;
    int dia;
    std::string tiempo;
    std::string dir_ip_origin;
    std::string dir_ip_dest;
    std::string msg;

    static const std::map<std::string, meses_year> month_map;
    static std::vector<int> splitIP(const std::string& ip);
};

#endif // BITACORA_H