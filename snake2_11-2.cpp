#include<iostream>//������ 2023302071062
#include<windows.h> //��������     
#include<conio.h>//���̴�����      
using namespace std;
const int height=20;//��ͼ����,��������;�޸�
const int width=40;
bool End;//�ж���Ϸ��ֹ��ײǽ��ͷβ����
int x,y,score=0;//
int f1x,f1y,f2x,f2y;//ʳ��
int ox,oy;//�ϰ���
bool wall;
enum Direction{Stop,Left,Right,Down,Up};//���ַ���,����Ҫ��д����Ȼ�ᱨ������Сд��ĳЩĬ�ϵĹ���
Direction dir;
//�ؿ����ã�1���ƶ��ٶ� 2����������ǽ 3�������ϰ��� 4���ϰ����Ƿ��ƶ�
void setup()
{
    End=false;
    dir=Stop;
    x=width/2;//�ߴӵ�ͼ���뿪ʼ
    y=height/2;
    f1x=rand()%width+1;//�������ʳ��
    f1y=rand()%height+1;
    f2x=rand()%width+1;//�������ʳ��
    f2y=rand()%height+1;
    ox=rand()%width+1;//��������ϰ���
    oy=rand()%height+2;
}

void draw()
{
    system("cls");//clean the screen��������
    for(int i=1;i<=width;i++) cout<<"#";//��һ�е�ͼ
    cout<<endl;
    for(int i=1;i<=height;i++)
    {
        for(int j=1;j<=width;j++)
        {
            if(i==y&&j==x) cout<<"O";//��ͷ
            else if(i==f1y&&j==f1x) cout<<"$";//�������ʳ��1
            else if(i==f2y&&j==f2x) cout<<"$";//�������ʳ��2
            else
            {
                if(j==1||j==width) cout<<"#";//����ǽ��
                else cout<<" ";
            }
        }
        cout<<endl;
    }
    for(int i=1;i<=width;i++) cout<<"#";//���һ�е�ͼ
}
    
void print()
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
    switch(dir)//��ͷ�ƶ�
    {
        case Left:
        x--;
        break;
        case Right:
        x++;
        break;
        case Up:
        y--;        //��Ϊ�Ǵ������´�ӡmap������y�Ƿ��ŵ�
        break;
        case Down:
        y++;
        break;
    }
    if(wall==true)
    {
        if(x>=width||x<=1||y>=height+1||y<=0) End=true;
    }
}

int main()//endΪfalse�ͳ�����ӡ
{
    cout<<"��ѡ��ģʽ��"<<endl;
    cout<<"ģʽ1����ǽ��"<<endl;
    cout<<"ģʽ2����ǽ��"<<endl;
    int k1;
    cin>>k1;
    if(k1==1) wall=false;
    else wall=true;
    setup();
    while(End==false)
    {
        draw();
        print();
        logic();
        Sleep(400);//����
    }
    return 0;
}