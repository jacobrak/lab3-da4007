#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Matrix{
    public:
        //public
        Matrix(const string& file_path);
        Matrix(int row, int col);
        Matrix();

        float element(int row, int col) const;
        void set_element(int row, int col, float val);

        bool same_as(const Matrix& other) const;

        void add(const Matrix &other);
        void multiply(const Matrix &other);

        string str() const;

    private:
        std::vector<float> data;
        int rows;
        int cols;

        void read_file(const string& file_path);
        void read_matrix(istream& valid_file);
        void create_matrix(int row, int col);
        void populate_matrix(istream& valid_file);
};

#endif
