#include <fstream>
#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <sstream>

using namespace std;


class Matrix {
public:
    Matrix();
    Matrix(std::size_t N);
    Matrix(std::vector<std::vector<int> > nums);

    vector<vector<int> > get_data(){
        return nums;
    }

    static Matrix read_from_file(string filename) {
    vector<vector<int> > data;
    fstream myfile(filename);
    if (myfile.is_open()) {
        string str_size;
        if (getline(myfile, str_size)) {
            int size = stoi(str_size);
            int row_count = 0;
            string line;

            while (row_count < size * 2 && getline(myfile, line)) {
                if (line.empty()) {
                    continue;  // skip blank lines
                }

                stringstream ss(line);
                vector<int> row;
                int value;

                while (ss >> value) {
                    row.push_back(value);
                }

                // Only count and push non-empty rows
                if (!row.empty()) {
                    data.push_back(row);
                    row_count++;
                }
            }
        }
        myfile.close();
    }
    return Matrix(data);
}

   
    Matrix operator+(const Matrix &rhs) const{
        std::vector<std::vector<int> > data;
        for (size_t i = 0; i < nums.size(); ++i) {
           vector<int> row;
           for (size_t j = 0; j < nums[i].size(); ++j) {
                row.push_back(nums[i][j] + rhs.nums[i][j]);
          }
          data.push_back(row);
        }
        return Matrix(data);

    }
    Matrix operator*(const Matrix &rhs) const{
        std::vector<std::vector<int> > data(nums.size(), vector<int>(nums.size(), 0));
        for (int i = 0; i < nums.size(); ++i){
            for (int j = 0; j < nums.size(); ++j){
                int sum = 0;
                for (int k = 0; k < nums.size(); ++k){
                    sum += nums[i][k] * rhs.nums[k][j];
                }
            data[i][j] = sum;
            }
        }
        return Matrix(data);
    }
    void set_value(std::size_t i, std::size_t j, int n);
    int get_value(std::size_t i, std::size_t j) const;
    int get_size() const;
    int sum_diagonal_major() const;
    int sum_diagonal_minor() const;
    void swap_rows(std::size_t r1, std::size_t r2);
    void swap_cols(std::size_t c1, std::size_t c2);
    void print_matrix() const;
private:
    std::vector<std::vector<int> > nums;  // Member variable to store the matrix
};

// Constructor that initializes an empty NxN matrix
Matrix::Matrix(std::size_t N) {
    nums = std::vector<std::vector<int> >(N, std::vector<int>(N, 0));
}

// Constructor that initializes the matrix with provided data
Matrix::Matrix(std::vector<std::vector<int> > nums) {
    this->nums = nums;
}

int Matrix::sum_diagonal_major() const{
    int diagonal_sum = 0;
    int row = 0;
    int col = 0;
    while (row < nums.size() && col < nums.size()){
        diagonal_sum += nums[row][col];
        row++;
        col++;
    }
    return diagonal_sum;
}

int Matrix::sum_diagonal_minor() const{
    int diagonal_sum = 0;
    int row = 0;
    int col = nums.size() - 1;
    while (row < nums.size() && col >= 0){
        diagonal_sum += nums[row][col];
        row++;
        col--;
    }
    return diagonal_sum;
}


void Matrix::swap_rows(std::size_t r1, std::size_t r2){
    if (r1 <= nums.size() - 1 && r2 <= nums.size() - 1 && r1 > 0 && r2 > 0){
    vector<int> temp = nums[r1];
    nums[r1] = nums[r2];
    nums[r2] = temp;
    }
    else{
        cout << "Index Out of Bounds" << endl;
    }
}

void Matrix::swap_cols(std::size_t c1, std::size_t c2){
    if (c1 <= nums.size()-1 && c2 <= nums.size()-1 && c1 > 0 && c2 > 0){
        vector<int> temp_values;
        for (int rows = 0; rows < nums.size(); rows++){
            temp_values.push_back(nums[rows][c1]);
        }
        for (int rows = 0; rows < nums.size(); rows++){
            nums[rows][c1] = nums[rows][c2];
        }
        for (int rows = 0; rows < nums.size(); rows++){
            nums[rows][c2] = temp_values[rows];
        }
    }
    else{
        cout << "Index Out of Bounds" << endl;
    }
} 

// Function to print the matrix
void Matrix::print_matrix() const {
    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = 0; j < nums[i].size(); ++j) {
            cout << nums[i][j] << " ";  
        }
        cout << endl;
    }
}

int Matrix::get_value(std::size_t i, std::size_t j) const{
    return nums[i][j];
}

void Matrix::set_value(std::size_t i, std::size_t j, int n){
    nums[i][j] = n;
}

void update_matrix(std::size_t i, std::size_t j, int new_val, Matrix &rhs){
         if (i <= rhs.get_data().size() - 1 && j <= rhs.get_data().size() - 1 && i > 0 && j > 0){
                rhs.set_value(i, j, new_val);
         }
         else{
            cout << "Index out of range" << endl;
         }
    }






int main() {
    // 1. Read values from a file into the matrix
    string file;
    cout << "What is the name of the file: ";
    cin >> file;
    Matrix m = Matrix::read_from_file(file);

    vector<vector<int> > combined_values = m.get_data();
    int halfway = combined_values.size() / 2;

    // store the two matrices properly
    vector<vector<int> > m1(combined_values.begin(), combined_values.begin() + halfway);
    vector<vector<int> > m2(combined_values.begin() + halfway, combined_values.end());

    Matrix mat1(m1);
    Matrix mat2(m2);

    // print two matrices to ensure proper object creation
    cout << "1. Read values from a file into the matrix" << endl;
    cout << "Matrix 1: " << endl;
    mat1.print_matrix();
    cout<<endl;
    cout << "Matrix 2: " << endl;
    mat2.print_matrix();
    cout<<endl;

    // 2. Add two matrices and display the result
    cout << "2. Add two matrices and display the result. Add matrix 1 and matrix 2" << endl;
    Matrix mat3 = mat1 + mat2;
    mat3.print_matrix();
    cout<<endl;

    // 3. Multiply two matrices and display the result
    cout << "3. Multiply two matrices and display the result. Multiply matrix 1 and matrix 2" << endl;
    Matrix mat4 = mat1 * mat2;
    mat4.print_matrix();
    cout<<endl;

    // 4. Get the sum of matrix diagonal elements
    cout << "4. Get the sum of matrix diagonal elements. Add up the diagonals of matrix 1." << endl;
    cout << mat1.sum_diagonal_major() + mat1.sum_diagonal_minor() << endl;
    cout<<endl;

    // 5. Swap matrix rows and display the result
    cout << "5. Swap matrix rows and display the result. Swap index rows 1 and 2 on matrix 1" << endl;
    mat1.swap_rows(1, 2); // swap row indices 1 and 2
    mat1.print_matrix();
    cout<<endl;

    // 6. Swap matrix columns and display the result
     cout << "6. Swap matrix columns and display the result. Swap index columns 1 and 2 on matrix 1" << endl;
    mat2.swap_cols(1, 2); // swap column indices 1 and 2
    mat2.print_matrix();
    cout<<endl;

    // 7. Update matrix rows and display the result. Update row index 1, column index 2, of matrix 1 to 17
    cout << "7. Update matrix rows and display the result. Update row index 1, column index 2, of matrix 1 to 17" << endl;
    update_matrix(1, 2, 17, mat1); // update row index 1, column index 2, of matrix 1 to 17
    mat1.print_matrix();


    return 0;
};


