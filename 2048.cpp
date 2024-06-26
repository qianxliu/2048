#include <iostream>  
#include <vector>  
#include <cstdlib>  
#include <ctime>  
#include <iomanip>
#include <fstream>
#include <algorithm>
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

void msg(int &i)
{
    if (i == 2048)  std::cout << "You reached 2048!" << '\n';  
}

#ifdef _WIN32  
    #define byte WindowsByte // 或者其他不会与 std::byte 冲突的名字  
    #include <windows.h> // x86_64-w64-mingw32-g++ ./2048.cpp -static on ubuntu and the terminal should support ANSI(Windows Terminal, ConEmu, Cygwin)
    #define SLEEP(ms) Sleep(ms)  
#elif __linux__
    #include <termios.h>
    #include <unistd.h>
    #define SLEEP(ms) usleep(ms * 1000)
#endif

vector<int> v;
void mergeUp(bool& sliped) {  
    std::vector<int*> column;   
    for (int col = 0; col < dat.size; ++col) {   
        v.clear();
        for (int i = 0; i < dat.size; ++i)  v.push_back(grid[i][col]);

        column.clear(); // 清除上一列的指针
        for (int row = 0; row < dat.size; ++row) {    
            if (grid[row][col] != 0)  
                column.push_back(&grid[row][col]);
        }  
    
        // 如果列中没有数字，则跳过  in loops(for, while)
        if (column.empty()) continue;  

        size_t idx = 0;    
        while (idx < column.size() - 1) {    
            if (*column[idx] == *column[idx + 1]) {   
                                sliped = true; 
 
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
        for (int i = 0; i < dat.size; ++i)  if (grid[i][col] != v[i])   {
            sliped = true;
            break;
        }
    }

}  

void mergeLeft(bool& sliped) {  
    std::vector<int*> rows; 
    for (int row = 0; row < dat.size; ++row) {  
        v.clear();
        for (int i = 0; i < dat.size; ++i)  v.push_back(grid[row][i]);

        rows.clear();
        for (int col = 0; col < dat.size; ++col) {  
            if (grid[row][col] != 0)
                rows.push_back(&grid[row][col]);  
        }

        // 如果列中没有数字，则跳过  
        if (rows.empty()) continue;  
        // 合并temp中的数字  
        size_t idx = 0;  
        while (idx < rows.size() - 1) {  
            if (*rows[idx] == *rows[idx + 1]) {  
                sliped = true; 

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
            if (idx < rows.size())    
            {
                grid[row][col] = *rows[idx++];
            }
            else grid[row][col] = 0;
        }  
        for (int i = 0; i < dat.size; ++i)  if (grid[row][i] != v[i])   {sliped = true; break;}
    }
}  

void mergeDown(bool& sliped) {
    vector<int*> column;
    for (int col = 0; col < dat.size; ++col) {
        v.clear();
        for (int i = 0; i < dat.size; ++i)  v.push_back(grid[i][col]);

        column.clear();
        for (int row = dat.size-1; row >= 0; --row) {  
            if (grid[row][col] != 0)
                column.push_back(&grid[row][col]);  
        }

        if (column.empty()) continue;  

        // 合并temp中的数字  
        size_t idx = 0;  
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
            if (idx < column.size())    
            {
                grid[row][col] = *column[idx++];              
            }
            else grid[row][col] = 0;
        }  
        for (int i = 0; i < dat.size; ++i)  if (grid[i][col] != v[i])   {sliped = true; break;}
    }
}  

void mergeRight(bool& sliped) {  
    vector<int*> rows;
    for (int row = 0; row < dat.size; ++row) {  
        v.clear();
        for (int i = 0; i < dat.size; ++i)  v.push_back(grid[row][i]);

        rows.clear();
        for (int col = dat.size-1; col >=0; --col) {  
            if (grid[row][col] != 0)
                rows.push_back(&grid[row][col]);  
        }

        if (rows.empty()) continue;  
        // 合并temp中的数字  
        size_t idx = 0;  
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
            if (idx < rows.size())    
            {
                grid[row][col] = *rows[idx++]; // 只在column中有值时赋值，否则为0  
            }
            else grid[row][col] = 0;
        }
        for (int i = 0; i < dat.size; ++i)  if (grid[row][i] != v[i])   {sliped = true; break;}
    }
}  


bool check(char direction) {
    bool sliped = false;
    switch (direction)
    {
		case 119: // 'w' key
		case 107: // 'k' key
		case 65:  // up arrow, only works on Linux
            mergeUp(sliped);
            break;
		case 97:  // 'a' key
		case 104: // 'h' key
		case 68:  // left arrow
            mergeLeft(sliped);
            break;
		case 115: // 's' key
		case 106: // 'j' key
		case 66:  // down arrow
            mergeDown(sliped);
            break;
		case 100: // 'd' key
		case 108: // 'l' key
		case 67:  // right arrow
            mergeRight(sliped);
            break;
        default:
            break;
    }
    return sliped;
}  

#include <cmath>

// this function receives 2 pointers (indicated by *) so it can set their values, idea comes from https://github.com/mevdschee/2048.c
void getColors(int value, uint8_t scheme, uint8_t *foreground, uint8_t *background)
{
    
	uint8_t original[] = {8, 255, 1, 255, 2, 255, 3, 255, 4, 255, 5, 255, 6, 255, 7, 255, 9, 0, 10, 0, 11, 0, 12, 0, 13, 0, 14, 0, 255, 0, 255, 0};
	uint8_t blackwhite[] = {232, 255, 234, 255, 236, 255, 238, 255, 240, 255, 242, 255, 244, 255, 246, 0, 248, 0, 249, 0, 250, 0, 251, 0, 252, 0, 253, 0, 254, 0, 255, 0};
	uint8_t bluered[] = {235, 255, 63, 255, 57, 255, 93, 255, 129, 255, 165, 255, 201, 255, 200, 255, 199, 255, 198, 255, 197, 255, 196, 255, 196, 255, 196, 255, 196, 255, 196, 255};
	uint8_t *schemes[] = {original, blackwhite, bluered};
	// modify the 'pointed to' variables (using a * on the left hand of the assignment)
    uint8_t exponent = log2(value);
	*foreground = *(schemes[scheme] + (exponent*2+1) % sizeof(original));
	*background = *(schemes[scheme] + (exponent*2) % sizeof(original));
	// alternatively we could have returned a struct with two variables
}

void printColor(uint8_t &x, uint8_t &y, uint8_t &fg, uint8_t &bg)
{
	for (y = 0; y < dat.size; y++)
	{
		// send the addresses of the foreground and background variables,
		// so that they can be modified by the getColors function
		getColors(grid[x][y], 0, &fg, &bg);
		printf("\033[38;5;%d;48;5;%dm", fg, bg); // set color
		printf("       ");
		printf("\033[m"); // reset all modes
	}
    printf("\n");
}

void refresh() {
    printf("\033[H"); // move cursor to 0,0
    std::cout << "Enter move (w/a/s/d or q to quit): \n";  
    printf("2048.cpp %17d points\n", dat.score);

	uint8_t x, y, fg, bg;    
    for (x = 0; x < dat.size; x++)
	{
		printColor(x, y, fg, bg);
		for (y = 0; y < dat.size; y++)
		{
			getColors(grid[x][y], 0, &fg, &bg);
			printf("\033[38;5;%d;48;5;%dm", fg, bg); // set color
			if (grid[x][y] != 0)
			{
                int number = grid[x][y];            
				uint8_t t = 7 - log10(number);
				printf("%*s%u%*s", t - t / 2, "", grid[x][y], t / 2, "");
			}
			else
			{
				printf("   -   ");
			}
			printf("\033[m"); // reset all modes
		}
        printf("\n");
		printColor(x, y, fg, bg);
	}
	printf("\n");
	printf("\033[A"); // one line up
}

bool addRandom() {
    SLEEP(3e2);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));    
    vector<pair<int, int>>  avaliable;
    for (int i = 0; i < dat.size; ++i)
    {
        for (int j = 0; j < dat.size; ++j)
            if (grid[i][j] == 0)    avaliable.push_back({i, j});
    }
    if (avaliable.size() == 0)  return false;
    int rand = std::rand() % avaliable.size();  
    return (grid[avaliable[rand].first][avaliable[rand].second] = 2);
}  

void initialize() {  
    addRandom();  
    addRandom();  
}

int main(int argc, char* argv[]) {  
    // accept the size argument
    if (argc == 2 && atoi(argv[1]) > 1) dat.size = atoi(argv[1]);
    grid.clear();
    grid.resize(dat.size, vector<int>(dat.size));

	// make cursor invisible, erase entire screen
    printf("\033[?25l\033[2J");

    #ifdef _WIN32  
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hStdin, &mode);
        mode &= (~ENABLE_LINE_INPUT & ~ENABLE_ECHO_INPUT);  
        SetConsoleMode(hStdin, mode);
    #elif __linux__
        struct termios oldt, newt;  
        tcgetattr(STDIN_FILENO, &oldt); // 保存旧的终端设置  
        newt = oldt;  
        newt.c_lflag &= (~ICANON & ~ECHO); // 关闭规范模式和回显, disable canonical mode (buffered i/o) and local echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); // 应用新的终端设置  
    #endif

    std::vector<Data> dats;
    Data tmp;
    string filename = "scores.dat";
    std::ifstream input(filename); // 使用二进制模式  
    if (!input.is_open()) {  
        std::ofstream outfile(filename);
    }
    while (input.read(reinterpret_cast<char*>(&tmp), sizeof(tmp)))  
    {
        dats.push_back(tmp);
    }
    input.close();

    initialize();
    refresh();
    cout << "\n";
    for (Data d : dats)
    {
        time_t now = d.time;
        if (d.size == dat.size)   cout << d.score << "\t" << d.size << "\t" << asctime(localtime(&now));
    }

    char direction;  
    while ((direction = getchar()) != 'q' && direction != 'Q') {
            refresh();
            if (check(direction))
            {  
                refresh();
                if (addRandom())
                {
                    refresh();
                }
            } 
        // TODO: 检查游戏是否结束（无法再合并）  
    }  
    cout << "game over\n";
    dat.time = std::time(nullptr);
    dats.push_back(dat);
    sort(dats.begin(), dats.end(), [](Data &a, Data &b){
        if (a.size > b.size)    return true;
        else if (a.size == b.size && a.score > b.score) return true;
        else return false;
    });
    int d = 0;
    for (size_t i = 0; i+1 < dats.size();)
    {
        if (dat.size == dats[i].size && (dats[i].score == dats[i+1].score || d++ > 9))
        {
            dats.erase(dats.begin() + i);
        }
        else ++i;
    }

    std::ofstream output(filename, std::ios::out | std::ios::trunc); // 使用二进制模式  
    if (!output.is_open()) {  
        std::cerr << "can not open file!" << std::endl;  
        return 1;  
    }
    for (Data dat : dats)
    {
        output.write(reinterpret_cast<char*>(&dat), sizeof(dat));
    }
    output.close();

    #ifdef _WIN32  
        mode |= (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
        SetConsoleMode(hStdin, mode);
    #elif __linux__
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 恢复旧的终端设置  
    #endif
    // make cursor visible, reset all modes
	printf("\033[?25h\033[m");

    return 0;  
}