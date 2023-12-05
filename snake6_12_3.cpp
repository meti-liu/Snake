#include<iostream>//刘博瑞 2023302071062
#include<windows.h> //清屏调用     
#include<conio.h>//键盘传感器 
#include<ctime>//真随机数需要     
using namespace std;
int height;//地图长宽
int width;
char a[50][50];//小心数组越界
int tx[100];//每个蛇尾都有一个坐标（txi,tyi），对应蛇头（x，y）
int ty[100];
int tail=0;
int mo;//障碍物是否移动
bool End;//判断游戏终止，撞墙或头尾相碰
int x,y,score=0;//
int f1x,f1y,f2x,f2y;//食物
int ox[6],oy[6];//障碍物
int obstacle=2;//障碍物数量
bool wall;//有无墙壁
bool wider;//蛇的胖瘦
enum Direction{Stop,Left,Right,Down,Up};//四种方向,必须要大写，不然会报错，可能小写是某些默认的功能
Direction dir;
//关卡设置：1、移动速度 2、左右有无墙 3、有无障碍物 4、障碍物是否移动 5.地图大小6.蛇的宽度
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
    for(int i=1;i<=obstacle;i++)
    {
        ox[i]=rand()%(width-3)+3;//随机生成障碍物
        oy[i]=rand()%(height-3)+3;        
    }
        for(int i=0; i<50; i++)//我们必须在每次restart之后都将数据清零
    {
        for(int j=0; j<50; j++)
        {
            a[i][j] = 0;
        }
    }
    for(int i=0; i<100; i++)
    {
        tx[i] = 0;
        ty[i] = 0;
    }
    tail = 0;
    score = 0;
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
        for(int m=1;m<=obstacle;m++)
        {
            if(i==oy[m]&&j==ox[m])
            {
                a[i][j]='*';
                a[i-1][j-1]='*';
                a[i][j-1]='*';//障碍物面积是2*2的
                a[i-1][j]='*';
            }
        }
        
        if(wider==false)
        {
            for(int k=1;k<=tail;k++)
            {
                if(i==ty[k]&&j==tx[k]) a[i][j]='o';
            }
            if(i==y&&j==x) a[i][j]='O';//！！！！！考虑清楚重叠时的逻辑关系！！！！！！            
        }

        if(wider==true)//对胖蛇的处理
        {
            for (int k = 1; k <= tail; k++) 
            {
                if ((i == ty[k] || i == ty[k] + 1) && (j == tx[k] || j == tx[k] + 1)) 
                {
                    a[i][j] = 'o'; // 绘制蛇身
                }
            }

            if ((i == y || i == y + 1) && (j == x || j == x + 1)) 
            {
                a[i][j] = 'O'; // 绘制蛇头
            }

        }

    }
    cout<<"\t\t\t\t";
    for(int i=1;i<=height;i++)//用tab来使地图在终端里居中，而不是左对齐
    {
        for(int j=1;j<=width;j++)
        {
            cout<<a[i][j];
        }
        cout<<endl<<"\t\t\t\t";
    }
    cout<<"\t\t\t\tSCORE:"<<score;

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
    // 将蛇尾的第一节设置为蛇头的坐标
    tx[0] = x;
    ty[0] = y;

    // 移动蛇尾
    for(int i = tail; i > 0; i--)//顺序非常重要，我们先更新最后一节尾巴的位置，再依次往前
    //直到第一节尾巴
    {
        tx[i] = tx[i-1];
        ty[i] = ty[i-1];
    }

    
    switch(dir)//蛇头移动
    {
        case Left:
        x --;
        break;
        case Right:
        x ++;
        break;
        case Up:
        y--;        
        break;
        case Down://注意我们是从上往下打印的map，所以y是反着的
        y++;
        break;
    }


    if(wider==false)//对瘦蛇的一整套logic处理
    {
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
        for(int i=1;i<=tail;i++)
        {
            if(x==tx[i]&&y==ty[i]) End=true;//蛇头碰蛇尾，游戏结束
        }
        for(int i=1;i<=obstacle;i++)
        {
            if(x==ox[i]&&y==oy[i]) End=true;
            if(x==ox[i]-1&&y==oy[i]-1) End=true;
            if(x==ox[i]-1&&y==oy[i]) End=true;
            if(x==ox[i]&&y==oy[i]-1) End=true;//撞到障碍物，游戏结束
        }


        if(wall==false)//蛇头从一边进从另一边出
        {
            if(x>width) x=1;
            if(x<1) x=width;
            if(y>height) y=1;
            if(y<1) y=height;
        }
        if(wall==true)
        {
            if(x>=width||x<=1||y>=height||y<=1) End=true;//撞墙游戏结束
        }
    }


    if(wider==true)//对胖蛇处理略有不同
    {
        if((x==f1x||x+1==f1x)&&(y==f1y||y+1==f1y))//吃食物加分 ，食物刷新
        {
            tail++;
            score+=10;
            f1x=rand()%(width-2)+2;//食物1刷新位置
            f1y=rand()%(height-2)+2;
        } 
        if((x==f2x||x+1==f2x)&&(y==f2y||y+1==f2y))
        {
            tail++;
            score+=10;
            f2x=rand()%(width-2)+2;//食物2刷新位置
            f2y=rand()%(height-2)+2;
        } 

        // for(int i=1;i<=tail;i++)
        // {
        //     if((x==tx[i]||x+1==tx[i])&&(y==ty[i]||y+1==ty[i])) End=true;//胖蛇头碰蛇尾，游戏结束
        // }
        for(int i=1;i<=obstacle;i++)
        {
            if((x==ox[i]||x+1==ox[i])&&(y==oy[i]||y+1==oy[i])) End=true;//胖蛇撞到障碍物，游戏结束
        }

        if(wall==false)//蛇头从一边进从另一边出
        {
            if(x>width-1) x=1;
            if(x<1) x=width-1;
            if(y>height-1) y=1;
            if(y<1) y=height-1;
        }
        if(wall==true)
        {
            if(x>=width-1||x<=1||y>=height-1||y<=1) End=true;//胖蛇撞墙游戏结束
        }
    }

    
    if(mo==2)//对于困难模式，障碍物会移动
    {
        for(int i=1;i<=obstacle;i++)
        {
            if(ox[i]>width) ox[i]=1;
            if(ox[i]<1) ox[i]=width;//障碍物撞墙也会从另一边出来
            if(oy[i]>height) oy[i]=1;
            if(oy[i]<1) oy[i]=height;
        }

        ox[1]+=3;//障碍物1移动快
        oy[1]+=2;
        ox[2]--;//障碍物2移动慢
        oy[2]--;
    }
}







int main()//end为false就持续打印
{

    bool restart=true;
    while(restart)//这样可以反复进行游戏过程
    {
        srand(time(0));// srand(static_cast<unsigned>(time(0)));//实现真正的随机数处理
        cout<<"\n\n\n\n\n\t\t\t 欢迎进入贪吃蛇游戏!"<<endl;//欢迎界面;
        cout<<"\n\n\n\t\t\t 按任意键马上开始。。。"<<endl;//准备开始;;
        _getch();
        system("cls");//clean the screen清屏操作

        cout<<"\n\n\n\n\n\t\t\t 请选择模式："<<endl;
        cout<<"\n\n\n\n\n\t\t\t1：无墙壁"<<endl;
        cout<<"\n\n\n\n\n\t\t\t2：有墙壁"<<endl;
        int k1;
        cin>>k1;
        if(k1==1) wall=false;  
        if(k1==2) wall=true;
        system("cls");//clean the screen清屏操作

        cout<<"\n\n\n\n\n\t\t\t 请选择蛇的胖瘦："<<endl;//蛇的胖瘦
        cout<<"\n\n\n\n\n\t\t\t1：胖蛇"<<endl;
        cout<<"\n\n\n\n\n\t\t\t2：瘦蛇"<<endl;
        int k2;
        cin>>k2;
        if(k2==1) wider=true;  
        if(k2==2) wider=false;
        system("cls");//clean the screen清屏操作

        cout<<"\n\n\n\n\n\t\t\t 请选择速度"<<endl;//\n与endl效果相同 
        cout<<"\n\n\n\n\n\t\t\t 1：慢速"<<endl;//\t相当于tab缩进，我们以此达到交互页面居中的效果
        cout<<"\n\n\n\n\n\t\t\t 2：中速"<<endl;
        cout<<"\n\n\n\n\n\t\t\t 3：快速"<<endl;
        int sl,sleep;
        cin>>sl;
        switch(sl)
        {
            case 1:sleep=60;
            break;
            case 2:sleep=20;
            break;
            case 3:sleep=0;
            break;
        }
        system("cls");//clean the screen清屏操作  

        cout<<"\n\n\n\n\n\t\t\t 请选择地图大小"<<endl;//\n与endl效果相同 
        cout<<"\n\n\n\n\n\t\t 如果地图跳动，请将终端调整至全屏"<<endl;//\n与endl效果相同 
        cout<<"\n\n\n\n\n\t\t\t 1：小地图25*25"<<endl;//\t相当于tab缩进，我们以此达到交互页面居中的效果
        cout<<"\n\n\n\n\n\t\t\t 2：中地图30*35"<<endl;
        cout<<"\n\n\n\n\n\t\t\t 3：大地图40*40"<<endl;
        int map_size;
        cin>>map_size;
        switch (map_size)
        {
        case 1:
            width=25;
            height=25;
            break;
        case 2:
            width=35;
            height=30;
            break;
        case 3:
            width=50;
            height=35;
            break;
        }
        system("cls");//clean the screen清屏操作  

        cout<<"\n\n\n\n\n\t\t\t 请选择游戏难度"<<endl;//\n与endl效果相同 
        cout<<"\n\n\n\n\n\t\t\t 1：简单25*25"<<endl;//\t相当于tab缩进，我们以此达到交互页面居中的效果
        cout<<"\n\n\n\n\n\t\t\t 2：困难30*35"<<endl;
        cin>>mo;

        setup();
        while(End==false)//主要逻辑在此处调用
        {
            draw();
            input();
            logic();
            Sleep(sleep);//减速
        }
        system("cls");//clean the screen清屏操作  
        cout<<"\n\n\n\n\n\t\t\t GAME OVER"<<endl;//gg
        cout<<"\n\n\n\n\n\t\t\t 是否继续游戏"<<endl;
        cout<<"\n\n\n\n\n\t\t\t 1：是"<<endl;
        cout<<"\n\n\n\n\n\t\t\t 0：否"<<endl;
        cin>>restart;
        if(restart) End=false;//下一轮不结束
        system("cls");//clean the screen清屏操作  
    }
    return 0;
}