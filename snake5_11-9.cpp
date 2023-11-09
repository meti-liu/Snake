#include<iostream>//������ 2023302071062
#include<windows.h> //��������     
#include<conio.h>//���̴����� 
#include<ctime>//���������Ҫ     
using namespace std;
int height;//��ͼ����
int width;
char a[50][50];//С������Խ��
int tx[100];//ÿ����β����һ�����꣨txi,tyi������Ӧ��ͷ��x��y��
int ty[100];
int tail=0;
bool End;//�ж���Ϸ��ֹ��ײǽ��ͷβ����
int x,y,score=0;//
int f1x,f1y,f2x,f2y;//ʳ��
int ox[6],oy[6];//�ϰ���
int obstacle=2;//�ϰ�������
bool wall;
enum Direction{Stop,Left,Right,Down,Up};//���ַ���,����Ҫ��д����Ȼ�ᱨ������Сд��ĳЩĬ�ϵĹ���
Direction dir;
//�ؿ����ã�1���ƶ��ٶ� 2����������ǽ 3�������ϰ��� 4���ϰ����Ƿ��ƶ� 5.��ͼ��С
void setup()
{
    End=false;
    dir=Stop;
    x=width/2;//�ߴӵ�ͼ���뿪ʼ
    y=height/2;
    f1x=rand()%(width-2)+2;//�������ʳ��1
    f1y=rand()%(height-2)+2;
    f2x=rand()%(width-2)+2;//�������ʳ��2
    f2y=rand()%(height-2)+2;
    for(int i=1;i<=obstacle;i++)
    {
        ox[i]=rand()%(width-3)+3;//��������ϰ���
        oy[i]=rand()%(height-3)+3;        
    }

}

void draw()
{
    system("cls");//clean the screen��������

    for(int i=1;i<=height;i++)
    for(int j=1;j<=width;j++)
    {
        if(i==1||j==1||i==height||j==width) a[i][j]='#';
        else a[i][j]=' ';//��ͼ��ʼ��
        if(i==f1y&&j==f1x) a[i][j]='$';
        if(i==f2y&&j==f2x) a[i][j]='$';
        for(int m=1;m<=obstacle;m++)
        {
            if(i==oy[m]&&j==ox[m])
            {
                a[i][j]='*';
                a[i-1][j-1]='*';
                a[i][j-1]='*';//�ϰ��������2*2��
                a[i-1][j]='*';
            }
        }
        for(int k=1;k<=tail;k++)
        {
            if(i==ty[k]&&j==tx[k]) a[i][j]='o';
        }
        if(i==y&&j==x) a[i][j]='O';//������������������ص�ʱ���߼���ϵ������������
    }


    cout<<"\t\t\t\t";
    for(int i=1;i<=height;i++)//��tab��ʹ��ͼ���ն�����У������������
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
    if(_kbhit()==1)//��������ϰ����κΰ�ťkey board hit ��conio�е���
    {
        switch (_getch())//�жϾ������ĸ���λ
        {
        case 'w':
        case 'W':
        case 72: // 72 ��ʾ���ϼ�ͷ��
            dir = Up;
            break;
        case 's':
        case 'S':
        case 80: // 80 ��ʾ���¼�ͷ��
            dir = Down;
            break;
        case 'a':
        case 'A':
        case 75: // 75 ��ʾ�����ͷ��
            dir = Left;
            break;
        case 'd':
        case 'D':
        case 77: // 77 ��ʾ���Ҽ�ͷ��
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
    // ����β�ĵ�һ������Ϊ��ͷ������
    tx[0] = x;
    ty[0] = y;

    // �ƶ���β
    for(int i = tail; i > 0; i--)//˳��ǳ���Ҫ�������ȸ������һ��β�͵�λ�ã���������ǰ
    //ֱ����һ��β��
    {
        tx[i] = tx[i-1];
        ty[i] = ty[i-1];
    }

    
    switch(dir)//��ͷ�ƶ�
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
        case Down://ע�������Ǵ������´�ӡ��map������y�Ƿ��ŵ�
        y++;
        break;
    }

    if(x==f1x&&y==f1y)//��ʳ��ӷ� ��ʳ��ˢ��
    {
        tail++;
        score+=10;
        f1x=rand()%(width-2)+2;//ʳ��1ˢ��λ��
        f1y=rand()%(height-2)+2;
    } 
    if(x==f2x&&y==f2y)
    {
        tail++;
        score+=10;
        f2x=rand()%(width-2)+2;//ʳ��2ˢ��λ��
        f2y=rand()%(height-2)+2;
    } 
    for(int i=1;i<=tail;i++)
    {
        if(x==tx[i]&&y==ty[i]) End=true;//��ͷ����β����Ϸ����
    }
    for(int i=1;i<=obstacle;i++)
    {
        if(x==ox[i]&&y==oy[i]) End=true;
        if(x==ox[i]-1&&y==oy[i]-1) End=true;
        if(x==ox[i]-1&&y==oy[i]) End=true;
        if(x==ox[i]&&y==oy[i]-1) End=true;//ײ���ϰ����Ϸ����
    }


    if(wall==false)//��ͷ��һ�߽�����һ�߳�
    {
        if(x>width) x=1;
        if(x<1) x=width;
        if(y>height) y=1;
        if(y<1) y=height;
    }
    if(wall==true)
    {
        if(x>=width||x<=1||y>=height||y<=1) End=true;//ײǽ��Ϸ����
    }

}

int main()//endΪfalse�ͳ�����ӡ
{
    srand(time(0));// srand(static_cast<unsigned>(time(0)));//ʵ�����������������

    bool restart=true;
    while(restart)//�������Է���������Ϸ����
    {
        cout<<"\n\n\n\n\n\t\t\t ��ӭ����̰������Ϸ!"<<endl;//��ӭ����;
        cout<<"\n\n\n\t\t\t ����������Ͽ�ʼ������"<<endl;//׼����ʼ;;
        _getch();
        system("cls");//clean the screen��������

        cout<<"\n\n\n\n\n\t\t\t ��ѡ��ģʽ��"<<endl;
        cout<<"\n\n\n\n\n\t\t\t1����ǽ��"<<endl;
        cout<<"\n\n\n\n\n\t\t\t2����ǽ��"<<endl;
        int k1;
        cin>>k1;
        if(k1==1) wall=false;  
        if(k1==2) wall=true;
        system("cls");//clean the screen��������

        cout<<"\n\n\n\n\n\t\t\t ��ѡ���ٶ�"<<endl;//\n��endlЧ����ͬ 
        cout<<"\n\n\n\n\n\t\t\t 1������"<<endl;//\t�൱��tab�����������Դ˴ﵽ����ҳ����е�Ч��
        cout<<"\n\n\n\n\n\t\t\t 2������"<<endl;
        cout<<"\n\n\n\n\n\t\t\t 3������"<<endl;
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
        system("cls");//clean the screen��������  

        cout<<"\n\n\n\n\n\t\t\t ��ѡ���ͼ��С"<<endl;//\n��endlЧ����ͬ 
        cout<<"\n\n\n\n\n\t\t �����ͼ�������뽫�ն˵�����ȫ��"<<endl;//\n��endlЧ����ͬ 
        cout<<"\n\n\n\n\n\t\t\t 1��С��ͼ25*25"<<endl;//\t�൱��tab�����������Դ˴ﵽ����ҳ����е�Ч��
        cout<<"\n\n\n\n\n\t\t\t 2���е�ͼ30*35"<<endl;
        cout<<"\n\n\n\n\n\t\t\t 3�����ͼ40*40"<<endl;
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
        system("cls");//clean the screen��������  

        setup();
        while(End==false)
        {
            draw();
            input();
            logic();
            Sleep(sleep);//����
        }
        system("cls");//clean the screen��������  
        cout<<"\n\n\n\n\n\t\t\t GAME OVER"<<endl;//gg
        cout<<"\n\n\n\n\n\t\t\t �Ƿ������Ϸ"<<endl;
        cout<<"\n\n\n\n\n\t\t\t 1����"<<endl;
        cout<<"\n\n\n\n\n\t\t\t 0����"<<endl;
        cin>>restart;
        if(restart) End=false;//��һ�ֲ�����
        system("cls");//clean the screen��������  
    }
    return 0;
}