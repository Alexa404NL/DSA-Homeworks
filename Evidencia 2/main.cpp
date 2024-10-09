#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "Bitacora.h"
#include <sstream>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

vector<Bitacora*> leerArchivo(string& file) {
    vector<Bitacora*> log_file;
    string l, mes, hora, dir_ip, msg;
    int dia;
    ifstream f(file);
    getline(f, l);
    do {
        istringstream iss(l);
        iss >> mes >> dia >> hora >> dir_ip;
        getline(iss, msg);
        Bitacora *log = new Bitacora(mes, dia, hora, dir_ip, msg);
        log_file.push_back(log);
    } while (getline(f, l));
    return log_file;
}

void freeLogs(vector<Bitacora*>& logs) {
    for (auto& entry : logs) {
        delete entry;
    }
    logs.clear();
}

void merge(vector<Bitacora*>& logs, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Bitacora*> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = logs[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = logs[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i]->compareIP(*R[j])) {
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

void mergeSortLogsByIP(vector<Bitacora*>& logs, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortLogsByIP(logs, left, mid);
        mergeSortLogsByIP(logs, mid + 1, right);

        merge(logs, left, mid, right);
    }
}

int busqueda_bin(vector<Bitacora*> arr, const string& ip) {
    int lim_inferior = 0, lim_superior = arr.size() - 1, mitad;
    while (lim_inferior <= lim_superior) {
        mitad = (lim_inferior + lim_superior) / 2;
        string valor_mitad = arr[mitad]->get_dir_ip();
        if (valor_mitad == ip) {
            return mitad;
        } else if (valor_mitad < ip) {
            lim_inferior = mitad + 1;
        } else {
            lim_superior = mitad - 1;
        }
    }

    if (lim_inferior == lim_superior) {
        return lim_superior;
    }
    return -1;
}

vector<Bitacora*> searchLogs(const vector<Bitacora*>& logs, const string& start_ip, const string& end_ip) {
    vector<Bitacora*> result;
    int inicio = busqueda_bin(logs, start_ip);
    int fin = busqueda_bin(logs, end_ip);
    for (int i = inicio; i <= fin; i++) {
        result.push_back(logs[i]);
    }
    return result;
}

//🦆

string monthNumberToName(int month) {
    static const string months[] = {"Jan", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    if (month >= 1 && month <= 12) {
        return months[month - 1];
    }
    return "Mes Invalido";
}

void displayLogs(const vector<Bitacora*>& logs) {
    for (const auto& entry : logs) {
        cout << monthNumberToName(entry->get_mes()) << " " << entry->get_dia() << " " << entry->get_time() << " " << entry->get_dir_ip() << " " << entry->get_msg() << endl;
    }
}

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

    // Ordenar los logs por dirección IP usando Merge Sort
    mergeSortLogsByIP(log, 0, log.size() - 1);

    // Guardar los logs ordenados en un archivo
    writeLogsToFile(log, "sorted_bitacora.txt");

    // Pedir al usuario las direcciones IP de inicio y fin para la búsqueda
    string start_ip, end_ip;
    cout << "Ingresa la dirección IP de inicio para la búsqueda: ";
    getline(cin, start_ip);
    cout << "Ingresa la dirección IP de fin para la búsqueda: ";
    getline(cin, end_ip);

    // Buscar los logs en el rango de direcciones IP usando Binary Search
    vector<Bitacora*> search_results = searchLogs(log, start_ip, end_ip);

    // Desplegar resultados de la búsqueda
    displayLogs(search_results);

    // Liberar memoria de los logs
    freeLogs(log);

    return 0;
}