#include <iostream>
#include <fstream>
using namespace std;

class Matrix{
    public:
        Matrix(const string& file_path){
            read_file(file_path);
        }
        void read_file(const string& file_path){
            ifstream file(file_path);

            if (!file){
                cerr << "bad filename " << file_path << endl;
                return;
            }

        }
};  

int main(){
    Matrix my_obj("m4.txt");
    return 0;
}