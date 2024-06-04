#include <iostream>  
#include <vector>  
#include <cstdlib>  
#include <ctime>  
#include <iomanip>


#include <ctime>
#include <string>
using namespace std;
struct Data {
    int score;
    int size;
    long time;
};
  
Data dat = {0, 4, 0};

vector<vector<int>> grid(4, vector<int>(4));

bool addRandom() {  
    std::srand(static_cast<unsigned int>(std::time(nullptr)));    
    vector<pair<int, int>>  avaliable;
    for (int i = 0; i < dat.size; ++i)
    {
        for (int j = 0; j < dat.size; ++j)
            if (grid[i][j] == 0)    avaliable.push_back({i, j});
    }
    if (avaliable.size() == 0)  return false;
    int rand = std::rand() % avaliable.size();  
    grid[avaliable[rand].first][avaliable[rand].second] = 2;
    return true;
}  

void initialize() {  
    addRandom();  
    addRandom();  
}

void msg(int &i)
{
    if (i == 2048)
        std::cout << "You reached 2048!" << '\n';  
}

void mergeUp() {  
    std::vector<int*> column;   
    for (int col = 0; col < dat.size; ++col) {    
        column.clear(); // 清除上一列的指针  
        for (int row = 0; row < dat.size; ++row) {    
            if (grid[row][col] != 0)  
                column.push_back(&grid[row][col]);    
        }  
    
        // 如果列中没有数字，则跳过  
        if (column.empty()) continue;  

        int idx = 0;    
        while (idx < column.size() - 1) {    
            if (*column[idx] == *column[idx + 1]) {    
                *column[idx] *= 2; // 合并相同的数字  
                dat.score += *column[idx];    
                // 注意：删除下一个元素后，不需要再次增加idx，因为下一个元素会移动到当前位置  
                column.erase(column.begin() + idx + 1); // 移除已合并的数字    

                // 如果合并后的数字等于2048，输出消息  
                msg(*column[idx]);  
            } else ++idx;  
        }  
    
        // 将合并后的数字放回grid中  
        idx = 0;  
        for (int row = 0; row < dat.size; ++row) {    
            if (idx < column.size()) {  
                grid[row][col] = *column[idx++]; // 只在column中有值时赋值，否则为0  
            } else {  
                grid[row][col] = 0; // 如果column中的值都用完了，则剩余的行都为0  
            }  
        }  
    }

}  

void mergeLeft() {  
    std::vector<int*> rows; 
    for (int row = 0; row < dat.size; ++row) {  
        rows.clear();
        for (int col = 0; col < dat.size; ++col) {  
            if (grid[row][col] != 0)
                rows.push_back(&grid[row][col]);  
        }

    // 如果列中没有数字，则跳过  
    if (rows.empty()) continue;  
        // 合并temp中的数字  
        int idx = 0;  
        while (idx < rows.size() - 1) {  
            if (*rows[idx] == *rows[idx + 1]) {  
                *rows[idx] *= 2; // 合并相同的数字  
                dat.score += *rows[idx];  
                rows.erase(rows.begin() + idx + 1); // 移除已合并的数字  
  
                // 如果合并后的数字等于2048，输出消息并结束循环  
                msg(*rows[idx]);
            }  else ++idx;  
        }  

        idx = 0;
        // 将合并后的数字放回newGrid中  
        for (int col = 0; col < dat.size; ++col) {  
            if (idx < rows.size())    grid[row][col] = *rows[idx++];
            else grid[row][col] = 0;
        }  
    }
}  

void mergeDown() {
    vector<int*> column;
    for (int col = 0; col < dat.size; ++col) {  
        column.clear();
        for (int row = dat.size-1; row >= 0; --row) {  
            if (grid[row][col] != 0)
                column.push_back(&grid[row][col]);  
        }

    if (column.empty()) continue;  

        // 合并temp中的数字  
        int idx = 0;  
        while (idx < column.size() - 1) {  
            if (*column[idx] == *column[idx + 1]) {  
                *column[idx] *= 2; // 合并相同的数字  
                dat.score += *column[idx];  
                column.erase(column.begin() + idx + 1); // 移除已合并的数字  
  
                // 如果合并后的数字等于2048，输出消息并结束循环  
                msg(*column[idx]);

            }  else ++idx;  
        }

        idx = 0;
        // 将合并后的数字放回newGrid中  
        for (int row = dat.size-1; row >= 0; --row) {  
            if (idx < column.size())    grid[row][col] = *column[idx++];              
            else grid[row][col] = 0;
        }  
    }
}  

void mergeRight() {  
    vector<int*> rows;
    for (int row = 0; row < dat.size; ++row) {  
        rows.clear();
        for (int col = dat.size-1; col >=0; --col) {  
            if (grid[row][col] != 0)
                rows.push_back(&grid[row][col]);  
        }

    if (rows.empty()) continue;  
        // 合并temp中的数字  
        int idx = 0;  
        while (idx < rows.size() - 1) {  
            if (*rows[idx] == *rows[idx + 1]) {  
                *rows[idx] *= 2; // 合并相同的数字  
                dat.score += *rows[idx];  

                rows.erase(rows.begin() + idx + 1); // 移除已合并的数字  
  
                // 如果合并后的数字等于2048，输出消息并结束循环  
                msg(*rows[idx]);

            }  else ++idx;  
        }  

        idx = 0;
        // 将合并后的数字放回newGrid中  
        for (int col = dat.size-1; col >= 0; --col) {  
            if (idx < rows.size())    grid[row][col] = *rows[idx++]; // 只在column中有值时赋值，否则为0  
            else grid[row][col] = 0;
        }  
    }
}  


bool check(char direction) {
    switch (direction)
    {
		case 119: // 'w' key
		case 107: // 'k' key
		case 65:  // up arrow
            mergeUp();
            break;
		case 97:  // 'a' key
		case 104: // 'h' key
		case 68:  // left arrow
            mergeLeft();
                    break;
		case 115: // 's' key
		case 106: // 'j' key
		case 66:  // down arrow
                mergeDown();
                    break;
		case 100: // 'd' key
		case 108: // 'l' key
		case 67:  // right arrow
                mergeRight();
                    break;
        default:
            return false;
    }
    return true;
}  
  
void refresh() {
    cout << '\n'; 
    printf("\033[H"); // move cursor to 0,0
    for (int row = 0; row < dat.size; ++row) {  
        for (int col = 0; col < dat.size; ++col) {  
            std::cout << std::setw(3) << grid[row][col] << " ";  
        }  
        std::cout << std::endl;  
    }  
    std::cout << "\nscore is " << dat.score << '\n';
}  

#include <termios.h>  
#include <unistd.h>
#include <fstream>
#include <algorithm>

int main() {  
    initialize();
    std::cout << "Enter move (w/a/s/d or q/enter to quit): \n";  

	// make cursor invisible, erase entire screen
    printf("\033[?25l\033[2J");
    struct termios oldt, newt;  
    tcgetattr(STDIN_FILENO, &oldt); // 保存旧的终端设置  
    newt = oldt;  
    newt.c_lflag &= (~ICANON & ~ECHO); // 关闭规范模式和回显, disable canonical mode (buffered i/o) and local echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // 应用新的终端设置  


    std::vector<Data> dats;
    Data tmp;
    std::ifstream input("scores.dat"); // 使用二进制模式  
    if (!input.is_open()) {  
        std::cerr << "无法打开文件以进行读取" << std::endl;  
        return 1;  
    }
    while (input.read(reinterpret_cast<char*>(&tmp), sizeof(tmp)))  
    {
        dats.push_back(tmp);
    }
    input.close();

    refresh();
    for (Data dat : dats)
    {
        time_t now = dat.time;
        cout << dat.score << "\t" << dat.size << "\t" << asctime(localtime(&now));
    }

    char direction;  
    while ((direction = getchar()) != '\n' && direction != 'q') {  
            refresh();
            if (check(direction))
            {  
                refresh(); 
                if (addRandom())
                    refresh();
                else 
                {
                    continue;
                };
            } 
        // TODO: 检查游戏是否结束（无法再合并）  
    }  
    cout << "game over\n";
    dat.time = std::time(nullptr);
    dats.push_back(dat);
    sort(dats.begin(), dats.end(), [](Data &a, Data &b){
        return a.score > b.score;   // can not if (a.score>b.score) return true;
    });  
    for (int i = dats.size()-1; i > 0; --i)
    {
        if (i > 9 || dats[i].score == dats[i-1].score)   dats.erase(dats.begin() + i);
    }

    std::ofstream output("scores.dat", std::ios::out | std::ios::trunc); // 使用二进制模式  
    if (!output.is_open()) {  
        std::cerr << "无法打开文件！" << std::endl;  
        return 1;  
    }
    for (Data dat : dats)
    {
        output.write(reinterpret_cast<char*>(&dat), sizeof(dat));
    }
    output.close();


    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 恢复旧的终端设置  
    // make cursor visible, reset all modes
	printf("\033[?25h\033[m");

    return 0;  
}