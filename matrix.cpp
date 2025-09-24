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
        
        float element(int row, int col){
            return data[(row - 1) * cols + (col - 1)];
        }

        void set_element(int row, int col, float val) {
            data[(row - 1) * cols + (col - 1)] = val;
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
            read_matrix(file);

        }
        void read_matrix(istream& valid_file){
            int row, col;

            valid_file >> row >> col;
            cout << row << " " << col << endl;
            create_matrix(row, col);
        }
        void create_matrix(int row, int col){
            // 1d vector
            rows = row;
            cols = col;
            int matrix_size = row*col;
            data = std::vector<float>(matrix_size, 0.0f);
            }
        
};  

int main(){
    Matrix my_obj("m1.txt");
    my_obj.set_element(2,3, 9.9);
    return 0;
}