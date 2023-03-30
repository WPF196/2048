/*
 * 1. 窗口大小：4*4，宽度100，间隔15
 */

#include <iostream>
#include <conio.h>
#include <graphics.h>   //easyx的图形库头文件

#define MAX_GRID 4  //每行的格子数量
#define GRID_WIDTH 100  //格子宽度
#define INTERVAL 15 //间隔

int map[MAX_GRID][MAX_GRID];    //存储每个方格的数字
int num[12] = {0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
POINT pos[MAX_GRID][MAX_GRID];  //PONIT是easyx中的结构体，包含(x,y)，此处用来存储每个方格的左上和右下坐标
bool flag = false;              //是否成功移动的标志

//枚举格子的颜色
enum Color{
    zero = RGB(205, 193, 180),   //0的颜色
    twoTo1 = RGB(238, 228, 218),   //2的颜色
    twoTo2 = RGB(237, 224, 200),   //4的颜色
    twoTo3 = RGB(242, 177, 121),   //8的颜色
    twoTo4 = RGB(245, 149, 99),   //16的颜色
    twoTo5 = RGB(246, 124, 95),   //32的颜色
    twoTo6 = RGB(246, 94, 59),   //64的颜色
    twoTo7 = RGB(242, 177, 121),   //128的颜色
    twoTo8 = RGB(237, 204, 97),   //256的颜色
    twoTo9 = RGB(255, 0, 128),   //512的颜色
    twoTo10 = RGB(145, 0, 72),   //1024的颜色
    twoTo11 = RGB(242, 17, 158),   //2048的颜色
    back = RGB(187, 173, 160)   //背景色
};
Color arr[13] = {zero, twoTo1, twoTo2, twoTo3, twoTo4, twoTo5, twoTo6, twoTo7, twoTo8, twoTo9, twoTo10, twoTo11};

//随机返回2或者4，用以游戏初始使用
int TwoOrFour(){
    if(rand() % 10 == 1) return 4;     //产生4的概率是十分之一
    else return 2;
}

//在随机位置产生数字
void CreateNumber(){
    while(1){
        int x = rand() % MAX_GRID;
        int y = rand() % MAX_GRID;
        if(map[x][y] == 0) {    //在空白位置产生
            map[x][y] = TwoOrFour();
            break;
        }
    }
}

//预处理游戏相关参数
void GameInit(){
    //预处理格子坐标
    for (int i = 0; i < MAX_GRID; ++i)
        for (int j = 0; j < MAX_GRID; ++j) {
            pos[i][j].x = j * GRID_WIDTH + (j + 1) * INTERVAL;
            pos[i][j].y = i * GRID_WIDTH + (i + 1) * INTERVAL;
        }

    //游戏开始随机生成两个数
    srand(GetTickCount());  //设置随机数种子
    CreateNumber();
    CreateNumber();
}

//绘制相应格子的颜色和数字
void GameDraw() {
    cleardevice();    //刷新窗口
    for (int i = 0; i < MAX_GRID; ++i)  //枚举行
        for (int j = 0; j < MAX_GRID; ++j)  //枚举列
            for(int k = 0; k < 12; ++k){        //枚举当前格子可能的12种状态
                if(map[i][j] == num[k]) {
                    //设置举行填充色
                    setfillcolor(arr[k]);
                    //根据矩形的左上和由下坐标进行填充，fill存在白边，solid可以去除白边
                    solidrectangle(pos[i][j].x, pos[i][j].y,
                                   pos[i][j].x + GRID_WIDTH, pos[i][j].y + GRID_WIDTH);
                    if(map[i][j] != 0){
                        char number[5] = " ";   //outtextxy只能输出字符串形式
                        sprintf(number, "%d", map[i][j]);

                        settextstyle(50, 0, "楷体");   //设置字体
                        setbkmode(TRANSPARENT);        //设置背景模式透明
                        int tempx = GRID_WIDTH / 2 - textwidth(number) / 2; //字符串宽度
                        int tempy = GRID_WIDTH / 2 - textheight(number) / 2;//字符串高度
                        //在所需要的位置绘制相关的数字
                        outtextxy(pos[i][j].x + tempx, pos[i][j].y + tempy, number);
                    }
                }
            }
}

void GameJude(){
    if(flag){
        CreateNumber();
        flag = false;
    }
}

//上移
void moveup(){
    printf("up\n");
    for(int i = 0; i < MAX_GRID; ++i) {
        int temp = 0;
        for (int begin = 1; begin < MAX_GRID; ++begin)
            if (map[begin][i] != 0) {       //如果当前数不为空
                if(map[temp][i] == 0){                      //如果上方为空
                    map[temp][i] = map[begin][i];
                    map[begin][i] = 0;
                }else if(map[temp][i] == map[begin][i]){     //如果上方不为空，且与当前数相等
                    map[temp][i] += map[begin][i];
                    map[begin][i] = 0;
                }else{                                       //如果上方不为空，且不等于当前数
                    map[temp + 1][i] = map[begin][i];
                    if(temp + 1 != begin)   map[begin][i] = 0;
                }
                temp++;
                flag = true;        //表示已经移动了
            }
    }
}

//下移
void movedown(){
    printf("down\n");
    for(int i = 0; i < MAX_GRID; ++i) {
        int temp = MAX_GRID - 1;
        for (int begin = MAX_GRID - 2; begin >= 0; --begin)
            if (map[begin][i] != 0) {
                if(map[temp][i] == 0){
                    map[temp][i] = map[begin][i];
                    map[begin][i] = 0;
                }else if(map[temp][i] == map[begin][i]){
                    map[temp][i] += map[begin][i];
                    map[begin][i] = 0;
                }else{
                    map[temp - 1][i] = map[begin][i];
                    if(temp - 1 != begin)   map[begin][i] = 0;
                }
                temp--;
                flag = true;
            }
    }
}

//左移
void moveleft(){
    printf("left\n");
    for(int i = 0; i < MAX_GRID; ++i) {
        int temp = 0;
        for (int begin = 1; begin < MAX_GRID; ++begin)
            if (map[i][begin] != 0) {
                if(map[i][temp] == 0){
                    map[i][temp] = map[i][begin];
                    map[i][begin] = 0;
                }else if(map[i][temp] == map[i][begin]){
                    map[i][temp] += map[i][begin];
                    map[i][begin] = 0;
                }else{
                    map[i][temp + 1] = map[i][begin];
                    if(temp + 1 != begin)   map[i][begin] = 0;
                }
                temp++;
                flag = true;
            }
    }
}

//右移
void moveright(){
    printf("right\n");
    for(int i = 0; i < MAX_GRID; ++i) {
        int temp = MAX_GRID - 1;
        for (int begin = MAX_GRID - 2; begin >= 0; --begin)
            if (map[i][begin] != 0) {
                if(map[i][temp] == 0){
                    map[i][temp] = map[i][begin];
                    map[i][begin] = 0;
                }else if(map[i][temp] == map[i][begin]){
                    map[i][temp] += map[i][begin];
                    map[i][begin] = 0;
                }else{
                    map[i][temp - 1] = map[i][begin];
                    if(temp - 1 != begin)   map[i][begin] = 0;
                }
                temp--;
                flag = true;
            }
    }
}

//键盘控制数字移动
void GameControl(){
    //获取键盘输入
    char key = _getch();
    switch(key){
        case 'w':
        case 'W':
        case 72:
            moveup();
            break;
        case 's':
        case 'S':
        case 80:
            movedown();
            break;
        case 'a':
        case 'A':
        case 75:
            moveleft();
            break;
        case 'd':
        case 'D':
        case 77:
            moveright();
            break;
    }
}

int main() {
    //创建窗口      高度=宽度=格子数*格子宽度+5个间隔 （一下函数均来自easyx图形库）
    initgraph(MAX_GRID * GRID_WIDTH + 5 * INTERVAL, MAX_GRID * GRID_WIDTH + 5 * INTERVAL, 1);
    setbkcolor(back); //设置窗口背景色

    GameInit();

    while(1) {
        GameDraw();
        GameControl();
        GameJude();
    }

    getchar();
    return 0;
}
