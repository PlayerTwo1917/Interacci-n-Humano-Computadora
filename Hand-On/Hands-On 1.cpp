//Martha Mariana Angulo González
//220588284

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

class LeastSquaredRegressor {
private:
    vector<vector<double>> X;
    vector<double> Y;
    vector<double> B;

public:

    // Constructor con dataset predefinido
    LeastSquaredRegressor() {

        /*
            Dataset:
            x1 = dureza
            x2 = flexibilidad
            y  = yield
        */

        X = {
            {1, 1, 3},
            {1, 2, 1},
            {1, 3, 4},
            {1, 4, 2},
            {1, 5, 5},
            {1, 6, 3},
            {1, 7, 6},
            {1, 8, 4},
            {1, 9, 7},
            {1,10, 5},
            {1,11, 8},
            {1,12, 6},
            {1,13, 9},
            {1,14, 7},
            {1,15,10},
            {1,16, 8},
            {1,17,11}
        };

        Y = {
            15, 18, 21, 24, 27, 30, 33, 36, 39,
            42, 45, 48, 51, 54, 57, 60, 63
        };

        B.resize(3, 0);
    }

    // Transpuesta
    vector<vector<double>> transpose(vector<vector<double>> A) {

        vector<vector<double>> T(A[0].size(),
                                 vector<double>(A.size()));

        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A[0].size(); j++) {
                T[j][i] = A[i][j];
            }
        }

        return T;
    }

    // Multiplicación de matrices
    vector<vector<double>> multiply(vector<vector<double>> A,
                                    vector<vector<double>> B) {

        vector<vector<double>> C(A.size(),
                                 vector<double>(B[0].size(), 0));

        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < B[0].size(); j++) {
                for (int k = 0; k < B.size(); k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        return C;
    }

    // Multiplicación matriz-vector
    vector<double> multiplyMatrixVector(vector<vector<double>> A,
                                        vector<double> B) {

        vector<double> C(A.size(), 0);

        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < B.size(); j++) {
                C[i] += A[i][j] * B[j];
            }
        }

        return C;
    }

    // Inversa de matriz 3x3
    vector<vector<double>> inverse3x3(vector<vector<double>> A) {

        vector<vector<double>> inv(3, vector<double>(3));

        double det =
            A[0][0]*(A[1][1]*A[2][2] - A[1][2]*A[2][1]) -
            A[0][1]*(A[1][0]*A[2][2] - A[1][2]*A[2][0]) +
            A[0][2]*(A[1][0]*A[2][1] - A[1][1]*A[2][0]);

        inv[0][0] = (A[1][1]*A[2][2] - A[1][2]*A[2][1]) / det;
        inv[0][1] = (A[0][2]*A[2][1] - A[0][1]*A[2][2]) / det;
        inv[0][2] = (A[0][1]*A[1][2] - A[0][2]*A[1][1]) / det;

        inv[1][0] = (A[1][2]*A[2][0] - A[1][0]*A[2][2]) / det;
        inv[1][1] = (A[0][0]*A[2][2] - A[0][2]*A[2][0]) / det;
        inv[1][2] = (A[0][2]*A[1][0] - A[0][0]*A[1][2]) / det;

        inv[2][0] = (A[1][0]*A[2][1] - A[1][1]*A[2][0]) / det;
        inv[2][1] = (A[0][1]*A[2][0] - A[0][0]*A[2][1]) / det;
        inv[2][2] = (A[0][0]*A[1][1] - A[0][1]*A[1][0]) / det;

        return inv;
    }

    // Calcular parámetros óptimos
    void calculateParameters() {

        vector<vector<double>> XT = transpose(X);

        vector<vector<double>> XTX = multiply(XT, X);

        vector<vector<double>> XTX_inv = inverse3x3(XTX);

        vector<double> XTY = multiplyMatrixVector(XT, Y);

        B = multiplyMatrixVector(XTX_inv, XTY);
    }

    // Imprimir ecuación
    void printEquation() {

        cout << "\n===== ECUACION DE REGRESION =====\n";

        cout << fixed << setprecision(4);

        cout << "Yield = "
             << B[0]
             << " + (" << B[1] << " * x1)"
             << " + (" << B[2] << " * x2)"
             << endl;
    }

    // Predicción
    double predict(double x1, double x2) {

        return B[0] + B[1]*x1 + B[2]*x2;
    }

    // Simular experimentos
    void simulateExperiments() {

        cout << "\n===== SIMULACION DE EXPERIMENTOS =====\n";

        double experiments[5][2] = {
            {5, 7},
            {8, 2},
            {10, 9},
            {12, 4},
            {15, 6}
        };

        for (int i = 0; i < 5; i++) {

            double x1 = experiments[i][0];
            double x2 = experiments[i][1];

            double y = predict(x1, x2);

            cout << "\nExperimento " << i + 1 << endl;

            cout << "x1 (Dureza): " << x1 << endl;
            cout << "x2 (Flexibilidad): " << x2 << endl;

            cout << "Yield predicho: "
                 << fixed << setprecision(4)
                 << y << endl;
        }
    }

    // Imprimir parámetros
    void printParameters() {

        cout << "\n===== PARAMETROS OPTIMOS =====\n";

        cout << "B0 = " << B[0] << endl;
        cout << "B1 = " << B[1] << endl;
        cout << "B2 = " << B[2] << endl;
    }
};

int main() {

    LeastSquaredRegressor model;

    model.calculateParameters();

    model.printParameters();

    model.printEquation();

    model.simulateExperiments();

    return 0;
}