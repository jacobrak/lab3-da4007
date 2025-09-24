#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Matrix{
    public:
        // public methods
        Matrix(const string& file_path){
            read_file(file_path);
        }
        Matrix(int row, int col) {
            create_matrix(row, col);
        }

        float element(int row, int col){
            return data[(row - 1) * cols + (col - 1)];
        }

        void set_element(int row, int col, float val) {
            data[(row - 1) * cols + (col - 1)] = val;
        }

        bool same_as(const Matrix& other){
            return true;
        }

        void add(const Matrix &other){
            ;
        }

        void multiply(const Matrix &other){
            ;
        }

        string str() {
            string final_string = "[";
            for (int r = 1; r <= rows; r++) {
                final_string += "[";
                for (int c = 1; c <= cols; c++) {
                    final_string += to_string(element(r, c));
                    
                    if (c < cols) {
                        final_string += ", ";   // comma between elements in a row
                    }
                }
                
                final_string += "]";
                if (r < rows) {
                    final_string += ", ";       // comma between rows
                }
            }
            final_string += "]";
            return final_string;
        }

    private:
        // Private members
        std::vector<float> data;
        int rows;
        int cols;

        void read_file(const string& file_path){
            ifstream file(file_path);

            if (!file){
                cerr << "bad filename " << file_path << endl;
                return;
            }
            // read matrix
            read_matrix(file);
        }

        void read_matrix(istream& valid_file){
            int row, col;

            valid_file >> row >> col;
            cout << row << " " << col << endl;
            create_matrix(row, col);
            // populate
            populate_matrix(valid_file);
        }

        void create_matrix(int row, int col){
            // 1d vector
            rows = row;
            cols = col;
            int matrix_size = row*col;
            data = std::vector<float>(matrix_size, 0.0f);
        }

        void populate_matrix(istream& valid_file){
            for (int r = 1; r <= rows; r++) {
                for (int c = 1; c <= cols; c++) {
                    float val;
                    valid_file >> val;
                    set_element(r, c, val);
                }
            }
        }
        
};  

int main(){
    Matrix my_obj("m1.txt");
    cout <<my_obj.str() << endl;
    return 0;
}