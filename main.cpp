#include <bits/stdc++.h>
using namespace std;

void printMatrix(int ileWierzcholkow, int** matrix) {
    for (int i = 0; i < ileWierzcholkow; i++)
    {
        for(int j = 0; j < ileWierzcholkow; j++){
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    
}

bool czyOneGraph(int n, int** matrix) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] > 1) {
                return false;
            }
        }
    }
    return true;
}

bool czySprzezony(int ileWierzcholkow, int** matrix) {
    for (int i = 0; i < ileWierzcholkow - 1; i++) {
        for (int j = i + 1; j < ileWierzcholkow; j++) {
            bool sharedNeighbor = false;
            for (int k = 0; k < ileWierzcholkow; k++) {
                if (matrix[i][k] != 0 && matrix[j][k] != 0) {
                    sharedNeighbor = true;
                    for (int m = 0; m < ileWierzcholkow; m++) {
                        if ((matrix[i][m] == 0 && matrix[j][m] != 0) ||
                            (matrix[i][m] != 0 && matrix[j][m] == 0)) {
                            return false;
                        }
                    }
                }
            }
            if (sharedNeighbor) {
                continue;
            }
        }
    }
    return true;
}

bool czyLiniowy(int ileWierzcholkow, int** matrix) {
    for (int i = 0; i < ileWierzcholkow - 1; i++) {
        for (int j = i + 1; j < ileWierzcholkow; j++) {
            bool hasCommonEdge = false;
            for (int k = 0; k < ileWierzcholkow; k++) {
                if (matrix[i][k] != 0 && matrix[j][k] != 0) {
                    hasCommonEdge = true;
                    for (int m = 0; m < ileWierzcholkow; m++) {
                        if (matrix[m][i] != 0 && matrix[m][j] != 0) {
                            return false;
                        }
                    }
                }
            }
            if (hasCommonEdge) {
                continue;       
            }
        }
    }
    return true;
}


vector<pair<int, int>> sprzezonyNaOryginalnyMacieja(int ileWierzcholkow, int **matrix) {
    vector<pair<int, int>> edges, edgePairs;

    for (int i = 0; i < ileWierzcholkow; i++) {
        for (int j = i + 1; j < ileWierzcholkow; j++) {
            if (matrix[i][j] > 0) {
                edges.emplace_back(i + 1, j + 1);
            }
        }
    }
    int numEdges = edges.size();
    for (int i = 0; i < numEdges; i++) {
        int start1 = edges[i].first;
        int end1 = edges[i].second;

        for (int j = i + 1; j < numEdges; j++) {
            int start2 = edges[j].first;
            int end2 = edges[j].second;
        if (start1 == start2 || start1 == end2 || end1 == start2 || end1 == end2) {
                edgePairs.emplace_back(i + 1, j + 1);
            }
        }
    }

    return edgePairs;
}

vector<pair<int, int>> sprzezonyNaOryginalny(int ileWierzcholkow, int **adj) {
    vector<pair<int, int>> originalEdges;
    pair<int,int> temp = {0, 0};

    for(int i = 0; i < 100; i++)     {
        originalEdges.emplace_back(temp);
    }

    int indeksKrawedzi = 1;

    for(int i1 = 0; i1 < ileWierzcholkow; i1++) {
        if(originalEdges[i1].first == 0){
            originalEdges[i1].first = indeksKrawedzi;
            indeksKrawedzi++;
        }
        if(originalEdges[i1].second == 0){
            originalEdges[i1].second = indeksKrawedzi;
            indeksKrawedzi++;
        }
        for(int i2 = 0; i2 < ileWierzcholkow; i2++){
            if(adj[i2][i1] == 1) {
                originalEdges[i2].second = originalEdges[i1].first;
            }
        }
        for(int i3 = 0; i3 < ileWierzcholkow; i3++){
            if(adj[i1][i3] == 1) {
                originalEdges[i3].first = originalEdges[i1].second;
        }
    }   
}
   return originalEdges;
}

int countUniques(int* arr, int size) {
    int result = 1;
    
    sort(arr, arr + size);
    for(int i = 1; i < size; i++)
        {
            if (arr[i]!= arr[i-1])
                result++;
        }
    return result;
}

vector<pair<int, int> > reindexEdges(const vector<pair<int, int>>& edges) {
    map<int, int> vertIndexMap;
    vector<pair<int, int>> reinexedEdges; // check if reindexed is a word in dictionary
    int indexIt = 1;

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;

        if(vertIndexMap.find(u) == vertIndexMap.end()){
            vertIndexMap[u] = indexIt++; 
        }
        if(vertIndexMap.find(v) == vertIndexMap.end()){
            vertIndexMap[v] = indexIt++; 
        }
        reinexedEdges.emplace_back(make_pair(vertIndexMap[u], vertIndexMap[v]));
}
return reinexedEdges;
}


int main(int argc, char **argv) {
    fstream in_file;
    int ileWierzcholkow = 0;
    bool czyRobicOryginalny = false;

    in_file.open(argv[1]);
    if (!in_file.is_open()) {
        cerr << "Brakuje pliku na wejsciu.\n";
        exit(1);
    }
    
    in_file >> ileWierzcholkow;
    int** adj = new int*[ileWierzcholkow];
    for (int i = 0; i < ileWierzcholkow; i++) {
        adj[i] = new int[ileWierzcholkow]();
    }

    int u, v;
    while (in_file >> u >> v) {
        adj[u-1][v-1]+=1;
    }

    if(!czyOneGraph(ileWierzcholkow, adj)) 
        {
            cout << "Graf nie jest 1-grafem\n";
            exit(1);
        }

    if(!czySprzezony(ileWierzcholkow, adj))
        {
            cout << "Graf nie jest sprzezony\n";
            exit(1);
        }
        
    string temp = "cowsay -f tux Graf jest sprzezony";
    temp.append(czyLiniowy(ileWierzcholkow, adj) ? " i liniowy" : " i nie jest liniowy");

    system(temp.c_str());

    czyRobicOryginalny = czySprzezony(ileWierzcholkow, adj);

    if(czyRobicOryginalny) {
    vector<pair<int, int>> originalGraphEdges = sprzezonyNaOryginalny(ileWierzcholkow, adj);
    
    ofstream out_file;
    out_file.open(argv[2]);
    int* arr = new int[1024 * 2];
    int it = 0;
     for (const auto &edge : originalGraphEdges) {
        if(edge.first != 0)
            {        
        arr[it] = edge.first;
        arr[it+1] = edge.second;

        it+=2;
     }
     }

    int size = sizeof(arr) / sizeof(arr[0]);
    int uniqueCount = countUniques(arr, it);

    vector<pair<int, int>> reindex = reindexEdges(originalGraphEdges);
    // vector<pair<int, int>> reindex = sprzezonyNaOryginalnyMacieja(ileWierzcholkow, adj);

    sort(reindex.begin(), reindex.end());

    out_file << uniqueCount << endl;
    for (const auto &edge : reindex) {
        if(edge.first != uniqueCount+1)
        out_file << edge.first << " " << edge.second<< endl;
        }

    out_file.close();
    delete[] arr;
    }
    in_file.close();

    for (int i = 0; i < ileWierzcholkow; i++) {
        delete[] adj[i];
        }
    delete[] adj;

    return 0;

}