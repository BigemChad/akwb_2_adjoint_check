#include <iostream>
#include <vector>

using namespace std;
bool czySprzezony(int ileWierzcholkow, int **matrix) {
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

bool czyLiniowy(int ileWierzcholkow, int **matrix) {
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

int** createMatrix(int n, const vector<vector<int>>& values) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = values[i][j];
        }
    }
    return matrix;
}

void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
int ileWierzcholkow = 4;
vector<vector<int>> values = {
    {0, 1, 1, 1},
    {1, 0, 1, 1},
    {1, 1, 0, 1},
    {1, 1, 1, 0}
};

int** matrix = createMatrix(ileWierzcholkow, values);
bool result = czySprzezony(ileWierzcholkow, matrix);
deleteMatrix(matrix, ileWierzcholkow);

if (result) {
    cout << "Test passed: Expected true, got true" << endl;
    return 0;
} else {
    cout << "Test failed: Expected true, got false" << endl;
    return 1;
}
}