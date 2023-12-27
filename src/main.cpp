#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "controller/DirectoryGraph.h"
#include "model/DirectoryNode.h"
#include "view/Dree.h"

using namespace std;
void help() {
    cout << "\tdree: "
         << "dree "
         << "[dep] [-f [dir|file]][-a][-b]"
         << "\n";
    cout << "\tVisualize directories until certain depth"
         << "\n";
    cout << "\n";
    cout << "\trun dree followed by the number of levels you want to visualize"
         << "\n";
    cout << "\n";
    cout << "\tOptions:"
         << "\n";
    cout << "\t   -f   \t"
         << "search for a directory or file upto the specified depth"
         << "\n";
    cout << "\t   -a   \t"
         << "Show hidden files"
         << "\n";
    cout << "\t   -b   \t"
         << "Visualize directories util certian depth in levelorder fashion"
         << "\n";
}
bool isNumber(string line) {
    char *p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}

void search(int argc, char *argv[]) {
    if (argc != 5) {

        cout << "Missing args"
             << "\n";
        return;
    }
    string flag = argv[3];
    if (flag != "-f") {
        cout << "Unknown args: " << argv[3] << "\n";
        return;
    }
    string query = argv[4];
    int depth = stoi(argv[2]);
    if (depth >= 60) {
        cout << "mask overflow!!";
        return;
    }
    DirectoryGraph builder;
    string currentPath = argv[1];
    filesystem::path directoryPath(currentPath);
    builder.SearchDirectory(currentPath, depth, query);
}

void dree(int argc, char *argv[]) {
    if (!(argc == 3 || argc == 4)) {
        cout << "Missing args" << std::endl;
        return;
    }
    string currentPath = argv[1];
    filesystem::path directoryPath(currentPath);
    bool showHidden = false;
    bool sw=true;
    int depth = -1;
    if (argc == 4 || (argc == 3 && isNumber(argv[2]))) {
        depth = stoi(argv[2]);
        // TODO:add check to prevent overflow
        if (depth >= 60) {
            cout << "mask overflow!!";
            return;
        }
        showHidden = false;
        if (argc == 4) {
            string flag = argv[3];
            if (flag == "-a") {
                showHidden = true;
            } 
            else if(flag=="-b"){
                sw=false;
            }
            else {
                cout << "Unknown flags specified.";
                return;
            }
        }
    } else if (argc == 3) {
        string flag = argv[2];
        if (flag == "--help") {
            help();
            return;
        }
    }
    depth = stoi(argv[2]);

    // TODO:add check to prevent overflow
    if (depth >= 60) {
        cout << "mask overflow!!" << endl;
        return;
    }

    showHidden = false;
    if (argc == 4) {
        string flag = argv[3];
        if (flag == "-a") {
            showHidden = true;
        }
        else if(flag== "-b"){
            sw=false;
        } 
        else {
            cout << "Unknown flags specified" << endl;
            return;
        }
    }
    DirectoryGraph builder(showHidden);
    auto root = builder.BuildGraph(currentPath, depth);
    if(sw){
        builder.PrintGraphDFS(root, depth);
    }
    else{
        builder.PrintGraphBFS(root,depth);
    }
    if (!builder.allFilesPermited) cout << builder.permissionErrorString;
}

int main(int argc, char *argv[]) {
    if (argc < 5)
        dree(argc, argv);
    else if (argc == 5)
        search(argc, argv);
    else
        cout << "Dree cannot execute the given command\n";
    return 0;
}