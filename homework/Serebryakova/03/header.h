#pragma

class Matrix{
    int **ptr;
    size_t rows, cols;
    class Row {
        size_t len;
        int* arr;
    public:
        Row(int* arr, size_t);
        int& operator[](const size_t);
        const int& operator[](const size_t) const;
        ~Row();
    };
public:
    Matrix(size_t, size_t);
    size_t getRows() const;
    size_t getColumns() const;
    Row operator[](const size_t);
    const Row operator[](const size_t) const;
    bool operator==(const Matrix&) const;
    bool operator!=(const Matrix&) const;
    Matrix& operator*=(const int);
    ~Matrix();
};
