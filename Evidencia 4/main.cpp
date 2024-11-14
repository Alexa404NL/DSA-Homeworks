#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "Bitacora.h"
#include <sstream>
#include <algorithm>
#include "AVLTree.h"

using namespace std;
namespace fs = std::filesystem;

vector<Bitacora*> leerArchivo(const string& file) {
    vector<Bitacora*> log_file;
    ifstream f(file);
    if (!f.is_open()) {
        cerr << "Error opening file: " << file << endl;
        return log_file;
    }

    int n, m;
    f >> n >> m;
    f.ignore(); // Ignore the newline after m

    vector<string> ips(n);
    for (int i = 0; i < n; ++i) {
        getline(f, ips[i]);
    }

    string l, mes, hora, ip_origin, ip_dest, msg;
    int dia;
    while (getline(f, l)) {
        istringstream iss(l);
        iss >> mes >> dia >> hora >> ip_origin >> ip_dest;
        getline(iss, msg);
        try {
            Bitacora* log = new Bitacora(mes, dia, hora, ip_origin, ip_dest, msg);
            log_file.push_back(log);
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << " in line: " << l << endl;
        }
    }
    return log_file;
}

void freeLogs(vector<Bitacora*>& logs) {
    for (auto& entry : logs) {
        delete entry;
    }
    logs.clear();
}

AVLTree<string, vector<string>> buildAdjacencyList(const vector<Bitacora*>& logs) {
    AVLTree<string, vector<string>> adj_list;
    for (const auto& log : logs) {
        auto& dest_vector = adj_list[log->get_dir_ip_origin()];
        if (find(dest_vector.begin(), dest_vector.end(), log->get_dir_ip_dest()) == dest_vector.end()) {
            dest_vector.push_back(log->get_dir_ip_dest());
        }
    }
    return adj_list;
}

vector<pair<string, int>> calculateFanOut(const AVLTree<string, vector<string>>& adj_list) {
    vector<pair<string, int>> fan_out;
    for (const auto& entry : adj_list) {
        fan_out.push_back(make_pair(entry.first, entry.second.size()));
    }
    return fan_out;
}

vector<string> findNodesWithHighestFanOut(const vector<pair<string, int>>& fan_out) {
    vector<string> highest_fan_out_nodes;
    int max_fan_out = 0;
    for (const auto& entry : fan_out) {
        if (entry.second > max_fan_out) {
            max_fan_out = entry.second;
            highest_fan_out_nodes.clear();
            highest_fan_out_nodes.push_back(entry.first);
        } else if (entry.second == max_fan_out) {
            highest_fan_out_nodes.push_back(entry.first);
        }
    }
    return highest_fan_out_nodes;
}

string findBotMaster(const vector<pair<string, int>>& fan_out) {
    string bot_master;
    int max_fan_out = 0;
    for (const auto& entry : fan_out) {
        if (entry.second > max_fan_out) {
            max_fan_out = entry.second;
            bot_master = entry.first;
        }
    }
    return bot_master;
}

int getFanOut(const vector<pair<string, int>>& fan_out, const string& ip) {
    for (const auto& entry : fan_out) {
        if (entry.first == ip) {
            return entry.second;
        }
    }
    return 0;
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

    // Build adjacency list and calculate fan-out
    auto adj_list = buildAdjacencyList(log);
    auto fan_out = calculateFanOut(adj_list);

    // Find nodes with the highest fan-out
    auto highest_fan_out_nodes = findNodesWithHighestFanOut(fan_out);
    cout << "Nodes with the highest fan-out:" << endl;
    for (const auto& node : highest_fan_out_nodes) {
        cout << node << " with fan-out " << getFanOut(fan_out, node) << endl;
    }

    // Determine the bot master
    string bot_master = findBotMaster(fan_out);
    cout << "Presumed bot master IP: " << bot_master << " with fan-out " << getFanOut(fan_out, bot_master) << endl;

    // Free logs
    freeLogs(log);

    return 0;
}