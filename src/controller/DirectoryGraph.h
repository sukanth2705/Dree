#ifndef DIRECTORYGRAPH_H
#define DIRECTORYGRAPH_H

#include <filesystem>
#include <set>
#include <string>
#include <vector>
#include "../controller/DirectorySearch.h"
#include "../model/DirectoryNode.h"

using namespace std;

class DirectoryGraph {
   public:
    DirectoryGraph(bool showHidden = false);
    DirectoryNode *BuildGraph(const string &directoryName, long long depth);

    void SearchDirectory(const string &directoryName, int searchDepth, const string &query);

    void PrintGraphDFS(DirectoryNode *node, long long depth);
    bool allFilesPermited;
    string permissionErrorString;

   private:
    bool isDirectory(const string &pathStr);
    void TraverseDirectoriesDFS(DirectoryNode *node, long long depth, long long currentDepth = 0);
    void PrintGraphDFS(DirectoryNode *node, long long depth, long long currentDepth, bool isLastChild, long long mask);
    void TraverseDirectoriesToSearch(DirectoryNode *node, long long depth, long long currentDepth, const string &query,
                                     vector<pair<int, DirectoryNode *>> &results);
    bool isExcluded(const string &dirStr);

    set<string> excludedDirectories;
    string icon(const string &pathStr,long long depth, long long currentDepth);
    bool showHidden;
};

#endif
