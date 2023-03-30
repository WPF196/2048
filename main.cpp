/*
 * 1. ���ڴ�С��4*4�����100�����15
 */

#include <iostream>
#include <conio.h>
#include <graphics.h>   //easyx��ͼ�ο�ͷ�ļ�

#define MAX_GRID 4  //ÿ�еĸ�������
#define GRID_WIDTH 100  //���ӿ��
#define INTERVAL 15 //���

int map[MAX_GRID][MAX_GRID];    //�洢ÿ�����������
int num[12] = {0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
POINT pos[MAX_GRID][MAX_GRID];  //PONIT��easyx�еĽṹ�壬����(x,y)���˴������洢ÿ����������Ϻ���������
bool flag = false;              //�Ƿ�ɹ��ƶ��ı�־

//ö�ٸ��ӵ���ɫ
enum Color{
    zero = RGB(205, 193, 180),   //0����ɫ
    twoTo1 = RGB(238, 228, 218),   //2����ɫ
    twoTo2 = RGB(237, 224, 200),   //4����ɫ
    twoTo3 = RGB(242, 177, 121),   //8����ɫ
    twoTo4 = RGB(245, 149, 99),   //16����ɫ
    twoTo5 = RGB(246, 124, 95),   //32����ɫ
    twoTo6 = RGB(246, 94, 59),   //64����ɫ
    twoTo7 = RGB(242, 177, 121),   //128����ɫ
    twoTo8 = RGB(237, 204, 97),   //256����ɫ
    twoTo9 = RGB(255, 0, 128),   //512����ɫ
    twoTo10 = RGB(145, 0, 72),   //1024����ɫ
    twoTo11 = RGB(242, 17, 158),   //2048����ɫ
    back = RGB(187, 173, 160)   //����ɫ
};
Color arr[13] = {zero, twoTo1, twoTo2, twoTo3, twoTo4, twoTo5, twoTo6, twoTo7, twoTo8, twoTo9, twoTo10, twoTo11};

//�������2����4��������Ϸ��ʼʹ��
int TwoOrFour(){
    if(rand() % 10 == 1) return 4;     //����4�ĸ�����ʮ��֮һ
    else return 2;
}

//�����λ�ò�������
void CreateNumber(){
    while(1){
        int x = rand() % MAX_GRID;
        int y = rand() % MAX_GRID;
        if(map[x][y] == 0) {    //�ڿհ�λ�ò���
            map[x][y] = TwoOrFour();
            break;
        }
    }
}

//Ԥ������Ϸ��ز���
void GameInit(){
    //Ԥ�����������
    for (int i = 0; i < MAX_GRID; ++i)
        for (int j = 0; j < MAX_GRID; ++j) {
            pos[i][j].x = j * GRID_WIDTH + (j + 1) * INTERVAL;
            pos[i][j].y = i * GRID_WIDTH + (i + 1) * INTERVAL;
        }

    //��Ϸ��ʼ�������������
    srand(GetTickCount());  //�������������
    CreateNumber();
    CreateNumber();
}

//������Ӧ���ӵ���ɫ������
void GameDraw() {
    cleardevice();    //ˢ�´���
    for (int i = 0; i < MAX_GRID; ++i)  //ö����
        for (int j = 0; j < MAX_GRID; ++j)  //ö����
            for(int k = 0; k < 12; ++k){        //ö�ٵ�ǰ���ӿ��ܵ�12��״̬
                if(map[i][j] == num[k]) {
                    //���þ������ɫ
                    setfillcolor(arr[k]);
                    //���ݾ��ε����Ϻ��������������䣬fill���ڰױߣ�solid����ȥ���ױ�
                    solidrectangle(pos[i][j].x, pos[i][j].y,
                                   pos[i][j].x + GRID_WIDTH, pos[i][j].y + GRID_WIDTH);
                    if(map[i][j] != 0){
                        char number[5] = " ";   //outtextxyֻ������ַ�����ʽ
                        sprintf(number, "%d", map[i][j]);

                        settextstyle(50, 0, "����");   //��������
                        setbkmode(TRANSPARENT);        //���ñ���ģʽ͸��
                        int tempx = GRID_WIDTH / 2 - textwidth(number) / 2; //�ַ������
                        int tempy = GRID_WIDTH / 2 - textheight(number) / 2;//�ַ����߶�
                        //������Ҫ��λ�û�����ص�����
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

//����
void moveup(){
    printf("up\n");
    for(int i = 0; i < MAX_GRID; ++i) {
        int temp = 0;
        for (int begin = 1; begin < MAX_GRID; ++begin)
            if (map[begin][i] != 0) {       //�����ǰ����Ϊ��
                if(map[temp][i] == 0){                      //����Ϸ�Ϊ��
                    map[temp][i] = map[begin][i];
                    map[begin][i] = 0;
                }else if(map[temp][i] == map[begin][i]){     //����Ϸ���Ϊ�գ����뵱ǰ�����
                    map[temp][i] += map[begin][i];
                    map[begin][i] = 0;
                }else{                                       //����Ϸ���Ϊ�գ��Ҳ����ڵ�ǰ��
                    map[temp + 1][i] = map[begin][i];
                    if(temp + 1 != begin)   map[begin][i] = 0;
                }
                temp++;
                flag = true;        //��ʾ�Ѿ��ƶ���
            }
    }
}

//����
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

//����
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

//����
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

//���̿��������ƶ�
void GameControl(){
    //��ȡ��������
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
    //��������      �߶�=���=������*���ӿ��+5����� ��һ�º���������easyxͼ�ο⣩
    initgraph(MAX_GRID * GRID_WIDTH + 5 * INTERVAL, MAX_GRID * GRID_WIDTH + 5 * INTERVAL, 1);
    setbkcolor(back); //���ô��ڱ���ɫ

    GameInit();

    while(1) {
        GameDraw();
        GameControl();
        GameJude();
    }

    getchar();
    return 0;
}
