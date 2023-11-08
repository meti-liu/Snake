#include<iostream>//刘博瑞 2023302071062
#include<windows.h> //清屏调用     
#include<conio.h>//键盘传感器      
using namespace std;
const int height=20;//地图长宽,不能在中途修改
const int width=40;
bool End;//判断游戏终止，撞墙或头尾相碰
int x,y,score=0;//
int f1x,f1y,f2x,f2y;//食物
int ox,oy;//障碍物
enum Direction{Stop,Left,Right,Down,Up};//四种方向,必须要大写，不然会报错，可能小写是某些默认的功能
Direction dir;
//关卡设置：1、移动速度 2、左右有无墙 3、有无障碍物 4、障碍物是否移动
void setup()
{
    End=false;
    dir=Stop;
    x=width/2;//蛇从地图中央开始
    y=height/2;
    f1x=rand()%width+1;//随机生成食物
    f1y=rand()%height+1;
    f2x=rand()%width+1;//随机生成食物
    f2y=rand()%height+1;
}

void draw()
{
    system("cls");//clean the screen清屏操作
    for(int i=1;i<=width;i++) cout<<"#";//第一行地图
    cout<<endl;
    for(int i=1;i<=height;i++)
    {
        for(int j=1;j<=width;j++)
        {
            if(i==y&&j==x) cout<<"O";//蛇头
            else if(i==f1y&&j==f1x) cout<<"$";//随机生成食物1
            else if(i==f2y&&j==f2x) cout<<"$";//随机生成食物2
            else
            {
                if(j==1||j==width) cout<<"#";//左右墙壁
                else cout<<" ";
            }
        }
        cout<<endl;
    }
    for(int i=1;i<=width;i++) cout<<"#";//最后一行地图
}
    
void print()
{
    if(_kbhit()==1)//如果键盘上按下任何按钮key board hit 从conio中调用
    {
        switch (_getch())//判断具体是哪个键位
        {
        case 'w':
        case 'W':
        case VK_UP: // VK_UP 表示向上箭头键
            dir = Up;
            break;
        case 's':
        case 'S':
        case VK_DOWN: // VK_DOWN 表示向下箭头键
            dir = Down;
            break;
        case 'a':
        case 'A':
        case VK_LEFT: // VK_LEFT 表示向左箭头键
            dir = Left;
            break;
        case 'd':
        case 'D':
        case VK_RIGHT: // VK_RIGHT 表示向右箭头键
            dir = Right;
            break;
        case 'x':
        case 'X':
            End=true;
            break;
        }
    }
}

void logic()
{
    switch(dir)//蛇头移动
    {
        case Left:
        x--;
        break;
        case Right:
        x++;
        break;
        case Up:
        y--;        //因为是从上往下打印map，所以y是反着的
        break;
        case Down:
        y++;
        break;
    }
}

int main()//end为false就持续打印
{
    setup();
    while(End==false)
    {
        draw();
        print();
        logic();
        Sleep(50);//减速
    }
    return 0;
}