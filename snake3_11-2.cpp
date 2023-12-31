#include<iostream>//刘博瑞 2023302071062
#include<windows.h> //清屏调用     
#include<conio.h>//键盘传感器 
#include<ctime>//真随机数需要     
using namespace std;
const int height=20;//地图长宽,不能在中途修改
const int width=40;
char a[height+5][width+5];//小心数组越界
int tx[100];//每个蛇尾都有一个坐标（txi,tyi），对应蛇头（x，y）
int ty[100];
int tail=0;
bool End;//判断游戏终止，撞墙或头尾相碰
int x,y,score=0;//
int f1x,f1y,f2x,f2y;//食物
int ox,oy;//障碍物
bool wall;
enum Direction{Stop,Left,Right,Down,Up};//四种方向,必须要大写，不然会报错，可能小写是某些默认的功能
Direction dir;
//关卡设置：1、移动速度 2、左右有无墙 3、有无障碍物 4、障碍物是否移动
void setup()
{
    End=false;
    dir=Stop;
    x=width/2;//蛇从地图中央开始
    y=height/2;
    f1x=rand()%(width-2)+2;//随机生成食物1
    f1y=rand()%(height-2)+2;
    f2x=rand()%(width-2)+2;//随机生成食物2
    f2y=rand()%(height-2)+2;
    ox=rand()%(width-3)+3;//随机生成障碍物
    oy=rand()%(height-3)+3;
}

void draw()
{
    system("cls");//clean the screen清屏操作

    for(int i=1;i<=height;i++)
    for(int j=1;j<=width;j++)
    {
        if(i==1||j==1||i==height||j==width) a[i][j]='#';
        else a[i][j]=' ';//地图初始化
        if(i==f1y&&j==f1x) a[i][j]='$';
        if(i==f2y&&j==f2x) a[i][j]='$';
        for(int k=1;k<=tail;k++)
        {
            if(i==ty[k]&&j==tx[k]) a[i][j]='o';
        }
        if(i==y&&j==x) a[i][j]='O';//！！！！！考虑清楚重叠时的逻辑关系！！！！！！
    }



    for(int i=1;i<=height;i++)
    {
        for(int j=1;j<=width;j++)
        {
            cout<<a[i][j];
        }
        cout<<endl;
    }
    cout<<"SCORE:"<<score;
}
    
void input()
{
    if(_kbhit()==1)//如果键盘上按下任何按钮key board hit 从conio中调用
    {
        switch (_getch())//判断具体是哪个键位
        {
        case 'w':
        case 'W':
        case 72: // 72 表示向上箭头键
            dir = Up;
            break;
        case 's':
        case 'S':
        case 80: // 80 表示向下箭头键
            dir = Down;
            break;
        case 'a':
        case 'A':
        case 75: // 75 表示向左箭头键
            dir = Left;
            break;
        case 'd':
        case 'D':
        case 77: // 77 表示向右箭头键
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
    // 移动蛇尾
    for(int i = tail; i > 0; i--)
    {
        tx[i] = tx[i-1];
        ty[i] = ty[i-1];
    }
    // 将蛇尾的第一节设置为蛇头的坐标
    tx[0] = x;
    ty[0] = y;
    
    switch(dir)//蛇头移动
    {
        case Left:
        x--;
        break;
        case Right:
        x++;
        break;
        case Up:
        y--;        
        break;
        case Down://注意我们是从上往下打印的map，所以y是反着的
        y++;
        break;
    }

    if(x==f1x&&y==f1y)//吃食物加分 ，食物刷新
    {
        tail++;
        score+=10;
        f1x=rand()%(width-2)+2;//食物1刷新位置
        f1y=rand()%(height-2)+2;
    } 
    if(x==f2x&&y==f2y)
    {
        tail++;
        score+=10;
        f2x=rand()%(width-2)+2;//食物2刷新位置
        f2y=rand()%(height-2)+2;
    } 
    if(wall==true)
    {
        if(x>=width||x<=1||y>=height||y<=1) End=true;//撞墙游戏结束
    }
}

int main()//end为false就持续打印
{
    srand(time(0));// srand(static_cast<unsigned>(time(0)));//实现真正的随机数处理
    cout<<"请选择模式："<<endl;
    cout<<"模式1：无墙壁"<<endl;
    cout<<"模式2：有墙壁"<<endl;
    int k1;
    cin>>k1;
    if(k1==1) wall=false;
    else wall=true;
    setup();
    while(End==false)
    {
        draw();
        input();
        logic();
        Sleep(50);//减速
    }
    return 0;
}