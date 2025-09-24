#include "matrix.h"
// default if none is given
Matrix::Matrix(){
    rows = 0; 
    cols = 0; 
    data = vector<float>();
}

// Constructor given filepath 
Matrix::Matrix(const string& file_path){
    read_file(file_path);
}

// Constructor given row and column
Matrix::Matrix(int row, int col) {
    create_matrix(row, col);
}

// Element function which gathers the specific value at a point using math indexing at 1
float Matrix::element(int row, int col) const {
    return data[(row - 1) * cols + (col - 1)];
}

// Set_element function sets values indvidually using math indexing at 1
void Matrix::set_element(int row, int col, float val) {
    data[(row - 1) * cols + (col - 1)] = val;
}

// Calculates if two matrices are identical first checks exakt size returns a boolean value
// Using c++ 20 adds float overridding (fabs function) doesn't exist, therefore abs will be used here instead
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

// Adds to matrixes together
void Matrix::add(const Matrix &other){
    // mismatch in size
    if (rows != other.rows || cols != other.cols) {
        return;
    }
    for (auto i = 0; i < cols*rows; i++){
        data[i] += other.data[i];
    }
}

// Multiply two matrices together
void Matrix::multiply(const Matrix &other) {
    if (cols != other.rows) {
        cerr << "dimension mismatch" << endl;
        return;
    }

    // Create a new matrix
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

    // Overwrite this matrix A with result A*B
    *this = result;
}

// Str function which returns in matlib format
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

// Helper function which read a file and calls read_matrix
void Matrix::read_file(const string& file_path){
    ifstream file(file_path);

    if (!file){
        cerr << "bad filename " << file_path << endl;
        return;
    }
    read_matrix(file);
}

// Reads matrix values first creating a empty matrix then uses populate_matrix() to populate the matrix
void Matrix::read_matrix(istream& valid_file){
    int row, col;

    valid_file >> row >> col;
    create_matrix(row, col);
    populate_matrix(valid_file);
}

// Creates the empty matrix and asigns rows, cols, using a flat 1d matrix using vector
void Matrix::create_matrix(int row, int col){
    rows = row;
    cols = col;
    int matrix_size = row*col;
    data = std::vector<float>(matrix_size, 0.0f);
}

// Populates the matrix given the previously validated file and uses the set_element function for each value
void Matrix::populate_matrix(istream& valid_file){
    for (int row = 1; row <= rows; row++) {
        for (int col = 1; col <= cols; col++) {
            float val;
            valid_file >> val;
            set_element(row, col, val);
        }
    }
}
