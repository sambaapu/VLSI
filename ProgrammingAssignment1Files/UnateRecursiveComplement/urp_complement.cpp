#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <unordered_map>
#include <algorithm>

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

int find_most_binate(vector<vector<int>>& cubes){
    std::unordered_map<int, vector<int>> totalCount;
    for(auto cube: cubes){
        for (auto element: cube){
            if (totalCount.find(abs(element)) == totalCount.end()){
                totalCount[abs(element)] = {1,0,0};
                if (element > 0){
                    totalCount[abs(element)][1] = 1;
                }else{
                    totalCount[abs(element)][2] = 1;
                }
            }else{
                totalCount[abs(element)][0] += 1;
                if (element > 0){
                    totalCount[abs(element)][1] += 1;
                }else{
                    totalCount[abs(element)][2] += 1;
                }
            }
        }
    }
    int min = INT32_MAX;
    for (auto key: totalCount){
        if (key.second[0]<= min){
            min  = key.second[0];
        }
    }
    vector<int> min_index;
    for (auto key: totalCount){
        if (key.second[0] == min){
            min_index.push_back(key.first);
        }
    }
    std::sort(min_index.begin(), min_index.end());
    return min_index[0];
}

vector<vector<int>> calc_cofactor(vector<vector<int>> cubes, int x){
    vector<vector<int>> result;
    for (auto cube: cubes){
        vector<int> temp;
        bool keepCube = true;
        for (auto element: cube){
            if (element == x){
                continue;
            }else if (element == -x){
                keepCube = false;
                break;
            }else{
                temp.push_back(element);
            }
        }
        if (keepCube){
            result.push_back(temp);
        }
    }
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
        return result;
    }else if(check_empty_cube(cubes)){
        return result;
    }else{
        int x = find_most_binate(cubes);
        vector<vector<int>> posCubes = complement(calc_cofactor(cubes, x));
        vector<vector<int>> negCubes = complement(calc_cofactor(cubes, -x));
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
    return result;
}

void write_to_file(string outputfile, int num_of_vars, vector<vector<int>> result){
    ofstream file(outputfile);
    file << num_of_vars << endl;
    file << result.size() << endl;
    for (auto cube: result){
        file << cube.size() << " ";
        for (auto element: cube){
            file << element << " ";
        }
        file << endl;
    }
    file.close();
}

int main() {
    string input_file;
    cout << "Enter the file name: "<< endl;
    cin >> input_file;

    int num_of_vars=0, num_of_cubes=0;
    vector<std::vector<int>> cubes;
    vector<std::vector<int>> result;
    
    parse_input_file(input_file+".pcn", num_of_vars, num_of_cubes, cubes);
    result = complement(cubes);
    write_to_file(input_file+".out", num_of_vars, result);

    return 0;
}