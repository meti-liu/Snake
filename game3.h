#include<iostream>//������ 2023302071062
#include<windows.h> //��������     
#include<conio.h>//���̴����� 
#include<ctime>//���������Ҫ     
using namespace std;
class game3
{
    public:
    static const int height=40;//��ͼ����,��������;�޸�
    static const int width=40;
    char a[height+5][width+5];//С������Խ��
    int tx[100];//ÿ����β����һ�����꣨txi,tyi������Ӧ��ͷ��x��y��
    int ty[100];
    int tail=0;
    bool End;//�ж���Ϸ��ֹ��ײǽ��ͷβ����
    int x,y,score=0;//
    int f1x,f1y,f2x,f2y;//ʳ��
    int ox,oy;//�ϰ���
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
        ox=rand()%(width-3)+3;//��������ϰ���
        oy=rand()%(height-3)+3;
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
            for(int k=1;k<=tail;k++)
            {
                if(i==ty[k]&&j==tx[k]) a[i][j]='o';
            }
            if(i==y&&j==x) a[i][j]='O';//������������������ص�ʱ���߼���ϵ������������
        }



        for(int i=1;i<=height;i++)
        {
            for(int j=1;j<=width;j++)
            {
                cout<<a[i][j];
            }
            cout<<endl;
        }
        cout<<"\t\t\tSCORE:"<<score;
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
        if(wall==true)
        {
            if(x>=width||x<=1||y>=height||y<=1) End=true;//ײǽ��Ϸ����
        }

    }

    void play()//endΪfalse�ͳ�����ӡ
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
            else wall=true;
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
        
    }


};

