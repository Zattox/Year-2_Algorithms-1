#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

class Matrix {
 public:
  int size = 0;
  ll **data;

  Matrix(int size_) {
    size = size_;
    data = {new ll *[size_]{}};
    for (unsigned i{}; i < size_; ++i) {
      data[i] = new ll[size_]{};
    }
  }

  friend const Matrix operator+(Matrix left, const Matrix &right) {
    int n = left.size;
    Matrix result(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        result.data[i][j] = left.data[i][j] + right.data[i][j];
      }
    }
    return result;
  }

  friend const Matrix operator-(Matrix left, const Matrix &right) {
    int n = left.size;
    Matrix result(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        result.data[i][j] = left.data[i][j] - right.data[i][j];
      }
    }
    return result;
  }

  friend const Matrix operator*(Matrix left, const Matrix &right) {
    int n = left.size;
    Matrix result(n);
    if (n <= 128) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          for (int k = 0; k < n; ++k) {
            result.data[i][j] += left.data[i][k] * right.data[k][j];
          }
        }
      }
    } else {
      int m = n / 2;
      Matrix a11(m), a12(m), a21(m), a22(m);
      Matrix b11(m), b12(m), b21(m), b22(m);
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
          a11.data[i][j] = left.data[i][j];
          a12.data[i][j] = left.data[i][j + m];
          a21.data[i][j] = left.data[m + i][j];
          a22.data[i][j] = left.data[i + m][j + m];
          b11.data[i][j] = right.data[i][j];
          b12.data[i][j] = right.data[i][j + m];
          b21.data[i][j] = right.data[m + i][j];
          b22.data[i][j] = right.data[i + m][j + m];
        }
      }

      Matrix p1 = a11 * (b12 - b22);
      Matrix p2 = (a11 + a12) * b22;
      Matrix p3 = (a21 + a22) * b11;
      Matrix p4 = a22 * (b21 - b11);
      Matrix p5 = (a11 + a22) * (b11 + b22);
      Matrix p6 = (a12 - a22) * (b21 + b22);
      Matrix p7 = (a11 - a21) * (b11 + b12);

      Matrix c11 = p5 + p4 + p6 - p2;
      Matrix c12 = p1 + p2;
      Matrix c21 = p3 + p4;
      Matrix c22 = p5 + p1 - p3 - p7;

      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
          result.data[i][j] = c11.data[i][j];
          result.data[i][j + m] = c12.data[i][j];
          result.data[m + i][j] = c21.data[i][j];
          result.data[i + m][j + m] = c22.data[i][j];
        }
      }
    }
    return result;
  }
};

void solve() {
  int n;
  cin >> n;

  Matrix A(n), B(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> A.data[i][j];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> B.data[i][j];
    }
  }

  Matrix c = A * B;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << c.data[i][j] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  while (t > 0) {
    solve();
    --t;
  }
}
