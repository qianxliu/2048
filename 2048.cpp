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

int score = 0;

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
                score += *column[idx];  
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
                                score += *rows[idx];  

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

void mergeDown() {  
    for (int col = 0; col < SIZE; ++col) {  
        std::vector<int*> column; 
        for (int row = SIZE-1; row >= 0; --row) {  
            if (grid[row][col] != 0)
                column.push_back(&grid[row][col]);  
        }

        // 合并temp中的数字  
        int idx = 0;  
        while (column.size() > 1 && idx < column.size() - 1) {  
            if (*column[idx] == *column[idx + 1]) {  
                *column[idx] *= 2; // 合并相同的数字  
                                score += *column[idx];  

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
        for (int row = SIZE-1; row >= 0; --row) {  
            if (idx < column.size())    grid[row][col] = *column[idx++];  
            else grid[row][col] = 0;
        }  
    }
}  

void mergeRight() {  
    for (int row = 0; row < SIZE; ++row) {  
        std::vector<int*> rows; 
        for (int col = SIZE-1; col >=0; ++col) {  
            if (grid[row][col] != 0)
                rows.push_back(&grid[row][col]);  
        }

        // 合并temp中的数字  
        int idx = 0;  
        while (rows.size() > 1 && idx < rows.size() - 1) {  
            if (*rows[idx] == *rows[idx + 1]) {  
                *rows[idx] *= 2; // 合并相同的数字  
                                score += *rows[idx];  

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
        for (int col = SIZE-1; col >= 0; --col) {  
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
                    mergeRight();
                    break;
    }
}  
  
void refresh() {
    cout << '\n'; 
    system("clear");
    for (int row = 0; row < SIZE; ++row) {  
        for (int col = 0; col < SIZE; ++col) {  
            std::cout << std::setw(3) << grid[row][col] << " ";  
        }  
        std::cout << std::endl;  
    }  
    std::cout << "\nscore is " << score << '\n';
}  

#include <termios.h>  
#include <unistd.h>

int main() {  
    std::cout << "Enter move (w/a/s/d or q/enter to quit): ";  
    initializeGrid();  
    refresh();  

    struct termios oldt, newt;  
  
    tcgetattr(STDIN_FILENO, &oldt); // 保存旧的终端设置  
    newt = oldt;  
    newt.c_lflag &= ~(ICANON | ECHO); // 关闭规范模式和回显  
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // 应用新的终端设置  

    char direction;  
    while ((direction = getchar()) != ('\n')) {  
            refresh(); 
            if (direction == 'q') {  
                break;  
            }
            merge(direction);  
            addRandomTile();

        // TODO: 检查游戏是否结束（无法再合并）  
    }  
  
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 恢复旧的终端设置  
    return 0;  
}