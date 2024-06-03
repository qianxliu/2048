#include <iostream>  
#include <vector>  
#include <cstdlib>  
#include <ctime>  
#include <iomanip>

const int SIZE = 4;  
const int MAX_VALUE = 2048;  
  
using namespace std;

vector<vector<int>> grid(4, vector<int>(4));

bool addRandomTile() {  
    std::srand(static_cast<unsigned int>(std::time(nullptr)));    
    while (true) {  
        int row = std::rand() % SIZE;  
        int col = std::rand() % SIZE;  
        if (grid[row][col] == 0) {  
            grid[row][col] = 2;
            return true;
        }  
    }  
}  
  
vector<vector<int*>> columns;
vector<vector<int*>> rows;
void initializeGrid() {  
    addRandomTile();  
    addRandomTile();  
}

void mergeUp() {  
    for (int col = 0; col < SIZE; ++col) {  
        std::vector<int*> column; 
        for (int row = 0; row < SIZE; ++row) {  
            if (grid[row][col] != 0)
                column.push_back(&grid[row][col]);  
        }

        // 合并temp中的数字  
        int idx = 0;  
        while (column.size() > 1 && idx < column.size() - 1) {  
            if (*column[idx] == *column[idx + 1]) {  
                *column[idx] *= 2; // 合并相同的数字  
                column.erase(column.begin() + idx + 1); // 移除已合并的数字  
  
                // 如果合并后的数字等于2048，输出消息并结束循环  
                if (*column[idx] == 2048) {  
                    std::cout << "You reached 2048!" << std::endl;  
                    break; // 跳出循环，因为我们只关心2048这个数字是否出现  
                }  
            }  
            ++idx;  
        }  
        
        idx = 0;
        // 将合并后的数字放回newGrid中  
        for (int row = 0; row < SIZE; ++row) {  
            if (idx < column.size())    grid[row][col] = *column[idx++];  
            else grid[row][col] = 0;
        }  
    }
}  

void mergeDown() {  
    for (int col = 0; col < SIZE; ++col) {  
        std::vector<int*> column; 
        for (int row = 0; row < SIZE; ++row) {  
            if (grid[row][col] != 0)
                column.push_back(&grid[row][col]);  
        }

        // 合并temp中的数字  
        int idx = column.size();  
        while (column.size() > 1 && idx > 0) {  
            if (*column[idx] == *column[idx - 1]) {  
                *column[idx-1] *= 2; // 合并相同的数字  
                column.erase(column.begin() + idx); // 移除已合并的数字  
  
                // 如果合并后的数字等于2048，输出消息并结束循环  
                if (*column[idx] == 2048) {  
                    std::cout << "You reached 2048!" << std::endl;  
                    break; // 跳出循环，因为我们只关心2048这个数字是否出现  
                }  
            }  
            --idx;  
        }

        idx = 0;
        // 将合并后的数字放回newGrid中  
        for (int row = 0; row < SIZE; ++row) {  
            if (idx < column.size())    grid[row][col] = *column[idx++];  
            else grid[row][col] = 0;
        }  
    }
}  

void mergeLeft() {  
    for (int row = 0; row < SIZE; ++row) {  
        std::vector<int*> rows; 
        for (int col = 0; col < SIZE; ++col) {  
            if (grid[row][col] != 0)
                rows.push_back(&grid[row][col]);  
        }

        // 合并temp中的数字  
        int idx = 0;  
        while (rows.size() > 1 && idx < rows.size() - 1) {  
            if (*rows[idx] == *rows[idx + 1]) {  
                *rows[idx] *= 2; // 合并相同的数字  
                rows.erase(rows.begin() + idx + 1); // 移除已合并的数字  
  
                // 如果合并后的数字等于2048，输出消息并结束循环  
                if (*rows[idx] == 2048) {  
                    std::cout << "You reached 2048!" << std::endl;  
                    break; // 跳出循环，因为我们只关心2048这个数字是否出现  
                }  
            }  
            ++idx;  
        }  

        idx = 0;
        // 将合并后的数字放回newGrid中  
        for (int col = 0; col < SIZE; ++col) {  
            if (idx < rows.size())    grid[row][col] = *rows[idx++];  
            else grid[row][col] = 0;
        }  
    }
}  

void merge(char direction) {
    switch (direction)
    {
        case 'w':
        case 'W':
            mergeUp();
            break;
        case 'a':
        case 'A':
                    mergeLeft();
                    break;
        case 's':
        case 'S':
                    mergeDown();
                    break;
        case 'd':
        case 'D':
                    //mergeRight();
                    break;
    }
}  
  
void printGrid() {  
    for (int row = 0; row < SIZE; ++row) {  
        for (int col = 0; col < SIZE; ++col) {  
            std::cout << std::setw(3) << grid[row][col] << " ";  
        }  
        std::cout << std::endl;  
    }  
}  
  
int main() {  
    initializeGrid();  
    char direction;  
  
    while (true) {  
        printGrid();  
        std::cout << "Enter move (w/a/s/d or q to quit): ";  
        std::cin >> direction;  
  
        if (direction == 'q') {  
            break;  
        }  
  
        merge(direction);  
        addRandomTile();

        // TODO: 检查游戏是否结束（无法再合并）  
    }  
  
    return 0;  
}