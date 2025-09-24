#include "matrix.h"

Matrix::Matrix(const string& file_path){
    read_file(file_path);
}

Matrix::Matrix(int row, int col) {
    create_matrix(row, col);
}

// default if none is given
Matrix::Matrix(){
    rows = 0; 
    cols = 0; 
    data = vector<float>();
}

// element
float Matrix::element(int row, int col) const {
    return data[(row - 1) * cols + (col - 1)];
}

// set_element
void Matrix::set_element(int row, int col, float val) {
    data[(row - 1) * cols + (col - 1)] = val;
}

// using c++ 20 adds float overridding (fabs function) doesn't exist, therefore abs will be used here instead
bool Matrix::same_as(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false;
    }

    for (int i = 0; i < rows * cols; i++) {
        float value = std::abs(data[i] - other.data[i]);
        if (value > 1e-10) {
            return false;
        }
    }

    return true;
}

// adds to matrixes together
void Matrix::add(const Matrix &other){
    // mismatch in size
    if (rows != other.rows || cols != other.cols) {
        return;
    }
    for (auto i = 0; i < cols*rows; i++){
        data[i] += other.data[i];
    }
}

// multiply two matrices together
void Matrix::multiply(const Matrix &other) {
    if (cols != other.rows) {
        cerr << "dimension mismatch" << endl;
        return;
    }

    // create a new matrix
    Matrix result(rows, other.cols);

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= other.cols; j++) {
            float sum = 0;
            for (int k = 1; k <= cols; k++) {
                sum += element(i, k) * other.element(k, j);
            }
            result.set_element(i, j, sum);
        }
    }

    // overwrite this matrix A with result A*B
    *this = result;
}


string Matrix::str() const {
    string final_string = "[";
    for (int r = 1; r <= rows; r++) {
        final_string += "[";
        for (int c = 1; c <= cols; c++) {
            final_string += to_string(element(r, c));
            
            if (c < cols) { 
                final_string += ", "; // comma between elements in a row
            }
        }
        
        final_string += "]";
        if (r < rows) {
            final_string += ", "; // comma between rows
        }
    }
    final_string += "]";
    return final_string;
}

void Matrix::read_file(const string& file_path){
    ifstream file(file_path);

    if (!file){
        cerr << "bad filename " << file_path << endl;
        return;
    }
    read_matrix(file);
}

void Matrix::read_matrix(istream& valid_file){
    int row, col;

    valid_file >> row >> col;
    cout << row << " " << col << endl;
    create_matrix(row, col);
    populate_matrix(valid_file);
}

void Matrix::create_matrix(int row, int col){
    rows = row;
    cols = col;
    int matrix_size = row*col;
    data = std::vector<float>(matrix_size, 0.0f);
}

void Matrix::populate_matrix(istream& valid_file){
    for (int row = 1; row <= rows; row++) {
        for (int col = 1; col <= cols; col++) {
            float val;
            valid_file >> val;
            set_element(row, col, val);
        }
    }
}
