#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "Bitacora.h"
#include <sstream>
#include <algorithm>
#include <unordered_map>

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
        try {
            Bitacora *log = new Bitacora(mes, dia, hora, dir_ip, msg);
            log_file.push_back(log);
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << " in line: " << l << endl;
        }
    } while (getline(f, l));
    return log_file;
}

void freeLogs(vector<Bitacora*>& logs) {
    for (auto& entry : logs) {
        delete entry;
    }
    logs.clear();
}

int partition(vector<Bitacora*>& logs, int low, int high) {
    Bitacora* pivot = logs[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (logs[j]->compareIP(*pivot)) {
            i++;
            swap(logs[i], logs[j]);
        }
    }
    swap(logs[i + 1], logs[high]);
    return i + 1;
}

void quickSortLogsByIP(vector<Bitacora*>& logs, int low, int high) {
    if (low < high) {
        int pi = partition(logs, low, high);
        quickSortLogsByIP(logs, low, pi - 1);
        quickSortLogsByIP(logs, pi + 1, high);
    }
}

std::vector<int> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    int token;
    std::vector<int> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = stoi(s.substr (pos_start, pos_end - pos_start));
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (stoi (s.substr (pos_start)));
    return res;
}

int binary_search(const vector<Bitacora*>& arr, const string& ip) {
    string delimiter = ".";
    vector<int> v1 = split (ip, delimiter);

    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        vector<int> v2 = split (arr[mid]->get_dir_ip(), delimiter);
        if (v2[0] == v1[0] && v2[1] == v1[1] && v2[2] == v1[2] ) {
            return mid;
        }
        if (v2[0] <= v1[0]) {
            if(v2[1] < v1[1]){
                low = mid + 1;
            }
        } else {
            high = mid - 1;
        }
        if (low==high){
            return high;
        }
    }
    return -1;
}

vector<Bitacora*> searchLogs(const vector<Bitacora*>& logs, const string& start_ip, const string& end_ip) {
    vector<Bitacora*> result;
    int inicio = binary_search(logs, start_ip);
    int fin = binary_search(logs, end_ip);
    if (inicio == -1 || fin == -1 || inicio > fin) {
        return result; // Return empty result if indices are invalid
    }
    for (int i = inicio; i <= fin; i++) {
        result.push_back(logs[i]);
    }
    return result;
}

string monthNumberToName(int month) {
    static const string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
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

void countIPOccurrences(const vector<Bitacora*>& logs) {
    unordered_map<string, int> ip_count;

    for (const auto& log : logs) {
        string ip = log->get_dir_ip();
        ip_count[ip]++;
    }

    vector<pair<string, int>> ip_vector(ip_count.begin(), ip_count.end());
    sort(ip_vector.begin(), ip_vector.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return b.second < a.second; // Sort in descending order
    });

    bool has_repeats = false;
    cout << endl << "Repeated IP addresses:" << endl;
    for (const auto& entry : ip_vector) {
        if (entry.second > 1) {
            cout << entry.first << " repeats " << entry.second << " times" << endl;
            has_repeats = true;
        }
    }

    if (!has_repeats) {
        cout << "No repeated IP addresses found." << endl;
    }
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

    // Ordenar los logs por dirección IP usando Quick Sort
    quickSortLogsByIP(log, 0, log.size() - 1);

    // Guardar los logs ordenados en un archivo
    writeLogsToFile(log, "sorted_bitacora2.txt");

    // Pedir al usuario las direcciones IP de inicio y fin para la búsqueda
    string start_ip, end_ip;
    cout << "Ingresa la dirección IP de inicio para la búsqueda: ";
    getline(cin, start_ip);
    cout << "Ingresa la dirección IP de fin para la búsqueda: ";
    getline(cin, end_ip);

    // Buscar los logs en el rango de direcciones IP usando Binary Search
    vector<Bitacora*> search_results = searchLogs(log, start_ip, end_ip);

    // Desplegar resultados de la búsqueda
    if (!search_results.empty()) {
        displayLogs(search_results);
        // Almacenar en un archivo el resultado del ordenamiento.
        writeLogsToFile(search_results, "resultados_búsqueda.txt");
    } else {
        cout << "No logs found in the specified IP range." << endl;
    }

    // Contar y mostrar las IPs repetidas
    countIPOccurrences(log);

    // Liberar memoria de los logs
    freeLogs(log);

    return 0;
}