#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>

using namespace std;

void parse_input_file(string input_file, int &num_of_vars, int &num_of_cubes, vector<vector<int>> &cubes) {
    ifstream file(input_file);
    
    // read first two lines
    file >> num_of_vars >> num_of_cubes;
    
    string line;
    std::getline(file, line); // Skip the remainder of the current line
    for (int i = 0; i < num_of_cubes; ++i) {
        std::getline(file, line);
        std::istringstream iss(line);
        int temp;
        std::vector<int> cube;

        // Skip the first integer in the line
        iss >> temp;

        // Read the remaining integers
        while (iss >> temp) {
            cube.push_back(temp);
        }

        cubes.push_back(cube);
    }
    file.close();
}

bool check_empty_cube(vector<vector<int>> cubes){
    for (auto cube: cubes){
        if (cube.size() == 0){
            return true;
        }
    }
    return false;
}
int find_most_binate(vector<vector<int>> cubes){
    return 0;
}
vector<vector<int>> cal_pos_cofactor(vector<vector<int>> cubes, int x){
    vector<vector<int>> result;
    
    return result;
}
vector<vector<int>> cal_neg_cofactor(vector<vector<int>> cubes, int x){
    vector<vector<int>> result;
    return result;
}

vector<vector<int>> complement(vector<vector<int>> cubes) {
    vector<vector<int>> result;
    if (cubes.size() == 0) {
        result.push_back({});
        return result;
    }else if (cubes.size() == 1){
        vector<int> cube = cubes[0];
        for (auto element: cube){
            result.push_back({-element});
        }
    }else if(check_empty_cube(cubes)){
        return result;
    }else{
        int x = find_most_binate(cubes);
        vector<vector<int>> posCubes = complement(cal_pos_cofactor(cubes, x));
        vector<vector<int>> negCubes = complement(cal_neg_cofactor(cubes, x));
        for (auto cube: posCubes){
            cube.push_back(x);
            result.push_back(cube);
        }
        for (auto cube: negCubes){
            cube.push_back(-x);
            result.push_back(cube);
        }
        return result;
    }
}

int main() {
    string input_file;
    cout << "Enter the file name: "<< endl;
    cin >> input_file;

    int num_of_vars=0, num_of_cubes=0;
    vector<std::vector<int>> cubes;
    
    parse_input_file(input_file, num_of_vars, num_of_cubes, cubes);
    complement(cubes);

    return 0;
}