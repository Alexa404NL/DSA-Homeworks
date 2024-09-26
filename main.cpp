#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "Bitacora.h"
#include <sstream>
using namespace std;

namespace fs = std::filesystem;

vector<Bitacora*> leerArchivo(string& file) {
    vector<Bitacora*> log_file;
    string l, mes, hora, dir_ip, msg;
    int dia;
    ifstream f(file);
    getline(f, l);
    do {
        istringstream leer(l);
        leer >> mes >> dia >> hora >> dir_ip;
        getline(leer, msg);
        Bitacora *log = new Bitacora(mes, dia, hora, dir_ip, msg);
        log_file.push_back(log);
    } while (getline(f, l));
    return log_file;
}

string monthNumberToName(int month) {
    string months[] = {"Jan", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    if (month >= 1 && month <= 12) {
        return months[month - 1];
    }
    return "Invalid";
}

void displayLogs(const vector<Bitacora*>& logs) {
    for (auto& line : logs) {
        cout << monthNumberToName(line->get_mes()) << " " << line->get_dia() << " " << line->get_time() << " " << line->get_dir_ip() << " " << line->get_msg() << endl;
    }
}

void freeLogs(vector<Bitacora*>& logs) {
    for (auto& line : logs) {
        delete line;
    }
    logs.clear();
}

void merge(vector<Bitacora*>& logs, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Bitacora*> L(n1);
    vector<Bitacora*> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = logs[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = logs[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i]->isEarlierThan(*R[j])) {
            logs[k] = L[i];
            i++;
        } else {
            logs[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        logs[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        logs[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Bitacora*>& logs, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(logs, left, mid);
        mergeSort(logs, mid + 1, right);

        merge(logs, left, mid, right);
    }
}

Bitacora* parseDate(const string& date_str) {
    istringstream iss(date_str);
    string mes, tiempo;
    int dia;
    iss >> mes >> dia >> tiempo;
    return new Bitacora(mes, dia, tiempo, "", "");
}


//busqueda binaria (funciona para buscar en los rangos para el día y mes pero no para horas)
int busqueda_bin(vector<Bitacora*> arr, Bitacora* n){
    int lim_inferior=0, lim_superior=arr.size()-1, mitad;
    Bitacora* valor_mitad;
    while (lim_inferior<lim_superior){
        mitad=(lim_inferior+lim_superior)/2;
        valor_mitad=arr[mitad];
        if (valor_mitad->get_mes()==n->get_mes() && valor_mitad->get_dia()==n->get_dia() && valor_mitad->get_time()<=n->get_time()){ //error al momento de separar por horas
            return mitad;
        } else if (valor_mitad->get_mes()<n->get_mes() || valor_mitad->get_dia()<n->get_dia() || valor_mitad->get_time()<n->get_time()){
            lim_inferior=mitad+1;
        } else if (valor_mitad->get_mes()>n->get_mes() || valor_mitad->get_dia()>n->get_dia() || valor_mitad->get_time()>n->get_time()){
            lim_superior=mitad-1;
        }
    }

    if (lim_inferior==lim_superior){
        return lim_superior;
    }
    return -1;
}

vector<Bitacora*> searchLogs(const vector<Bitacora*>& logs, Bitacora* start, Bitacora* end) {
    vector<Bitacora*> result;
    int inicio, fin;
    inicio= busqueda_bin(logs, start);
    fin= busqueda_bin(logs, end);
    for (inicio; inicio<=fin; inicio++) {
            result.push_back(logs[inicio]);
    }
    return result;
}

/*
 //busqueda iterativa
vector<Bitacora*> searchLogs(const vector<Bitacora*>& logs, Bitacora* start, Bitacora* end) {
    vector<Bitacora*> result;
    for (const auto& log : logs) {
        if (log->isWithinRange(*start, *end)) {
            result.push_back(log);
        }
    }
    return result;
}*/


void writeLogsToFile(const vector<Bitacora*>& logs, const string& filename) {
    ofstream outFile(filename);
    for (const auto& entry : logs) {
        outFile << monthNumberToName(entry->get_mes()) << " " << entry->get_dia() << " " << entry->get_time() << " " << entry->get_dir_ip() << " " << entry->get_msg() << endl;
    }
    outFile.close();
}

int main() {
    vector<Bitacora*> log;
    string filename = "bitacora.txt";

    try {
        if (fs::exists(filename))
            log = leerArchivo(filename);
        else {
            cout << "El archivo " << filename << " no existe" << endl;
            return 1;
        }
    } catch (const exception& exp) {
        cerr << exp.what() << endl;
        return 1;
    }

    //cout << log.size() << endl;

    // Sortear con base a tiempo y fecha
    mergeSort(log, 0, log.size() - 1);

    // Escribir la lista sorteada a un archivo
    writeLogsToFile(log, "sorted_bitacora.txt");

    // Preguntar por fechas
    string start_date_str, end_date_str;
    cout << "Ingresa la fecha de inicio para la busqueda (e.g., Jan 1 00:00:00): ";
    getline(cin, start_date_str);
    cout << "Ingresa la fecha de fin para la busqueda (e.g., Jan 31 23:59:59): ";
    getline(cin, end_date_str);

    // Tomar las fechas
    Bitacora* start_date = parseDate(start_date_str);
    Bitacora* end_date = parseDate(end_date_str);

    // Buscar dentro del rango
    vector<Bitacora*> search_results = searchLogs(log, start_date, end_date);

    // Muestra logs, sorteados dentro del rango
    displayLogs(search_results);

    // Liberar memoria
    freeLogs(log);
    delete start_date;
    delete end_date;

    return 0;
}