#include<stdlib.h>
#include<string>
#include<iostream>
#include<ctime>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include <sstream>
#include<stdio.h>
using namespace std;
static int I = 0;//��Ȧ���
static int i = 0;//������
static string a = "����";
static string b = "С����";
static string c = "�󻨰���";
static string d = "��";
char price[500];
static int soldpignum=0;

ofstream OutFile1("SoldPig.txt",ios::app);//���������ı�
ofstream OutFile2("CurrentPig.txt",ios::app);//�˳�ʱ��Ȧ��������
ofstream OutFile3("Input-Littlepig.txt",ios::app);//�������������
ifstream InFile1("CurrentPig.txt",ios::in);

static char fileName[500];
void DouStr(double freq1)//double��char
{
    ostringstream oss1;
    oss1<<freq1;
    memset(fileName,0,500);
//��ת��Ϊ������ת��Ϊstring,Ȼ����ת��Ϊchar
    strcat(fileName,(oss1.str()).c_str());
}

void HugeNumber(char aaa[500],char bbb[500])//��Ǯ�ļ���������
{
    int i,tb,ta;
    ta = strlen(aaa);
    int tr1 = strlen(aaa);
    for (i = 0; i < tr1; i++) //�ҳ�С�����λ��
        if (aaa[i] == '.')
        {
            ta = i;
            break;
        }
    tb=strlen(bbb);
    int tr2=strlen(bbb);
    for(i=0;i<tr2;i++)
    if(bbb[i]=='.')
    {
        tb=i;
        break;
    }
    int ia=ta+1,ib=tb+1,zhs[500],xs[500],c,j,e;
    memset(xs,0,sizeof(xs));//��ʾС����������
    memset(zhs,0,sizeof(zhs));//��ʾ����
    ta--;tb--;
    i=j=0;
    while(1)//���������ĺ�
    {
        if(ta>=0)
        {zhs[i]+=aaa[ta]-'0';ta--;}
        if(tb>=0)
        {zhs[i]+=bbb[tb]-'0';tb--;}
        i++;         //i��ʾ����λ�ĳ���
        if(ta<0&&tb<0)
        break;
    }
    while(1)//�����С�������֮��
    {
        if(ia<tr1)
        {xs[j]+=aaa[ia]-'0';ia++;}
        if(ib<tr2)
        {xs[j]+=bbb[ib]-'0';ib++;}
        j++;         //j��ʾС��������ĳ���

        if(ia>=tr1&&ib>=tr2)
        break;
    }
    c=0;
    for(e=j-1;e>=0;e--)//��ʼ��λ
    {
        xs[e]+=c;
        c=xs[e]/10;
        xs[e]%=10;
    }
    for(e=0;e<i;e++)
    {
        zhs[e]+=c;
        c=zhs[e]/10;
        zhs[e]%=10;
    }
    if(c)
    {
        zhs[e]+=c;i++;
    }
    for(e=j-1;e>=0;e--)//ȥ�����������
    if(xs[e])
    break;
    else
    j--;
    for(e=i-1;e>=0;e--)
    if(zhs[e])
    break;
    else
    i--;
    int jj = 0;
    for(e=i-1;e>=0;e--)//��������ֵĺ�
    {
        price[jj] = zhs[e]+'0';
        jj++;
    }
    if(j>0)//���С����������������С����
    { 
        price[jj] = '.';
        jj++;
    }
    for(e=0;e<j;e++){
        price[jj] = xs[e]+'0';
        jj++;
    }
    if(j<=0&&i<=0){//����������Ϊ��ʱ����Ĳ���������������
        price[jj] = '0';
        jj++;
    }
}

typedef struct Pig{//��
    int pigstynum;
    int num;
    char *type;
    double weight;
    double time;
    double pri;
    bool ill;
}pig;
static Pig soldpig[10000];

typedef struct Pigsty{//��Ȧ
    int no;
    int pignum;
    int black;
    struct node *a;
    int illpignum;
}pigsty;

typedef struct Node//��Ȧָ��
{
    pigsty Data;
    struct Node *next;
}Lnode;

typedef struct node//��ָ��
{
    pig data;
    struct node *next;
}lnode;

void Clean(Lnode *p){//����Ȧ���
    Lnode *r = p;
    r->Data.black = 0;
    r->Data.no = 0;
    r->Data.pignum = 0;
    r->Data.illpignum = 0;
}

void clean(lnode *p){//��������
    lnode *r = p;
    r->data.num = 0;
    r->data.pigstynum = 0;
    r->data.time = 0;
    r->data.type = &d[0];
    r->data.weight = 0;
    r->data.ill = false;
}

void creat(lnode *hh,int n)//�������
{
    lnode *p,*r;
    int j;
    r=hh;
    for(j=0;j<n;j++)
    {
        p=(lnode *)malloc(sizeof(lnode));
        r->next=p;
        clean(r);
        r->data.pigstynum = I;
        r->data.num = i;
        i++;
        if(i==10) i = i - 10;
        r=p;
    }
    I++;
    r->next=NULL;
}

void Creat(Lnode *b,int n)//������Ȧ
{
    Lnode *p,*r;
    int j;
    r=b;
    for(j=0;j<n;j++)
    {
        p=(Lnode *)malloc(sizeof(Lnode));
        r->next=p;
        Clean(r);
        r->Data.no = I;
        lnode *hh;
        hh=(lnode *)malloc(sizeof(lnode));
        hh->next=NULL;
        r->Data.a = hh;
        creat(hh,10);
        r=p;
    }
    r->next=NULL;
}

void Input(Lnode *p,pig u)//��1�����Ȧ
{
    for (int j = 0; j < 10;j++){
        Lnode *r = p;
        for (; r->next != NULL; r = r->next)
        {
            if (r->Data.pignum <= j){
                if (r->Data.pignum==0){
                    if (u.type==&a[0]) r->Data.black = 1;
                    lnode *h = r->Data.a;
                    for (; h->next != NULL; h = h->next)
                    {
                        if(h->data.weight == 0&&r->Data.illpignum==0)
                        {
                        h->data.weight = u.weight;
                        h->data.type = u.type;
                        h->data.pigstynum = r->Data.no;
                        h->data.time = u.time;
                        h->data.ill = u.ill;
                        r->Data.pignum++;
                        return;
                        }
                    }
                }
                if(((r->Data.pignum!=0&&r->Data.black==0)&&(u.type==&b[0]||u.type==&c[0]))||(r->Data.black==1&&u.type==&a[0])){
                    lnode *h = r->Data.a;
                    for (; h->next != NULL; h = h->next)
                    {
                        if(h->data.weight == 0&&r->Data.illpignum==0)
                        {
                        h->data.weight = u.weight;
                        h->data.type = u.type;
                        h->data.pigstynum = r->Data.no;
                        h->data.time = u.time;
                        h->data.ill = u.ill;
                        r->Data.pignum++;
                        return;
                        }
                    }
                }      
            }
        }
    }
}

void output(Lnode *h)//���������Ȧ
{
    Lnode *p;
    p = h;
    while(p->next!=NULL)
    {
        if(p->Data.pignum!=0){
            cout<<p->Data.no<<endl;
            lnode *r = p->Data.a;
            while(r->next!=NULL){
                if(r->data.weight!=0){
                cout << r->data.num << r->data.type << r->data.weight <<"kg"<<r->data.time<< "��";
                if(r->data.ill==false) cout << "���� ";
                else if(r->data.ill==true) cout << "���� ";}
                r=r->next;
            }
            cout << endl;
        }
        p=p->next;
    }
}

void File(Lnode *h,int y)//�浵
{
    Lnode *p;
    p = h;
    while(p->next!=NULL)
    {
		//OutFile2<<p->Data.no<<endl;
        lnode *r = p->Data.a;
        int h=0;
        while(r->next!=NULL){
            if(r->data.weight!=0){
                h++;
            }
            r = r->next;
        }
        OutFile2 << h << endl;
        r = p->Data.a;
        while(r->next!=NULL){
            if(r->data.weight!=0){
                OutFile2 << r->data.num << " ";
                if (r->data.type == &a[0])
                    OutFile2 << 0 <<" ";
                if (r->data.type == &b[0])
                    OutFile2 << 1 <<" ";
                if (r->data.type == &c[0])
                    OutFile2 << 2 <<" ";
                OutFile2 << r->data.weight << " " << r->data.time<< " ";
                if (r->data.ill == false)
                    OutFile2 << 0<<" ";
                else if (r->data.ill == true)
                    OutFile2 << 1<<" ";
            }
            r=r->next;
        }
        OutFile2 << endl;
        p=p->next;
    }
    OutFile2 << y;
    OutFile2.close();
}

void ReadingFiles(Lnode *h)//����
{
    Lnode *p;
    p = h;
    while(p->next!=NULL)
    {
        int N,j;
        double s;
        InFile1 >> N;
        p->Data.pignum = N;
        lnode *r = p->Data.a;
        for (int i = 0; i < N;i++){
            InFile1 >> j;
            //cout << j;
            r->data.num = j;
            
            InFile1 >> j;
            //cout << j;
            if(j==0) r->data.type = &a[0];
            if(j==1) r->data.type = &b[0];
            if(j==2) r->data.type = &c[0];

            InFile1 >> s;
            //cout << s;
            r->data.weight = s;
            //cout << r->data.weight;

            InFile1 >> j;
            //cout << j;
            r->data.time = j;
            //cout << r->data.time;

            InFile1 >> j;
            //cout << j;
            if(j==0) r->data.ill = false;
            if(j==1) {r->data.ill = true; p->Data.illpignum = 10;}
            //cout << r->data.ill;
            r = r->next;
        }
        p=p->next;
    }
    //InFile1 >> n;
    //InFile1.close();
    //return n;
    //output(h);
}

void ergoPW(Lnode *h){//����������ÿͷ��1�������
    Lnode *p;
    p = h;
    while (p->next != NULL)
    {
        lnode *r = p->Data.a;
        for (;r->next != NULL ; r = r->next)
        {
            if(r->data.weight!=0){
                double x;
                x = double((rand() % 12) / 10.00);
                r->data.weight = r->data.weight + x;
                r->data.time++;
            }  
        }
        p = p->next;
    }
    Sleep(100);     
}

void onlyergo(Lnode *h,int n){//�ҵ���Ӧ��Ȧ����������Ȧ�������
    Lnode *p = h;
    while (p->Data.no!=n){
        p = p->next;
    }
    lnode *r = p->Data.a;
    if(p->Data.pignum==0)
        cout << "�����Ȧ��ʱû������Ŷ" << endl;
    else{
        cout << "===============================" << endl;
        while(r->next!=NULL){
            if(r->data.weight!=0){
                cout << r->data.num << r->data.type << " ";  
            }
            r = r->next;
        }
        cout << endl;
        cout << "         �鿴�ڼ�ͷ��" << endl;
        cout << "===============================" << endl;
        int y;
        cin >> y;
        r = p->Data.a;
        while(r->next!=NULL){
            if(r->data.num==y) {
                if(r->data.weight!=0)
                    cout << r->data.num << r->data.type << r->data.weight << "kg" << r->data.time << "�� ";
                else
                    cout << "��������������Ŷ" << endl;
                break;
            }
            r = r->next;
        }
        cout << endl;
    }
    //system("cls");
}

void raceergo(Lnode *h,char *g){//����ֲ�
    Lnode *p;
    p = h;
    int racenum=0;
    int rr;
    while(p->next!=NULL)
    {   
        lnode *r = p->Data.a;
        rr = 0;
        if(p->Data.pignum!=0){
            while(r->next!=NULL){
                if(r->data.weight!=0&&r->data.type==g){
                    racenum++;
                    rr++;
                }
                r=r->next;
            }
        }
        if(rr!=0){
            cout<<p->Data.no<<endl;
            r = p->Data.a;
            while(r->next!=NULL){
                if(r->data.weight!=0&&r->data.type==g){
                    cout << r->data.num << r->data.type << r->data.weight <<"kg"<<r->data.time<< "�� ";
                }
                r=r->next;
            }
            cout << endl;
        }
        p=p->next;
    }
    cout << "һ����" << racenum << "ͷ" << *g << endl;
}

void pricesum(Lnode *h){//�������г�Ȧ��ļ۸���ճ�Ȧ���
    Lnode *p;
    p = h;
    while (p->next != NULL)
    {
        lnode *r = p->Data.a;
        int j = 0;
        for (;r->next != NULL; r = r->next)
        {
            if((r->data.time>=365||r->data.weight>75.00)&&r->data.ill==false){
                soldpig[soldpignum].time = r->data.time;
                soldpig[soldpignum].type = r->data.type;
                soldpig[soldpignum].weight = r->data.weight;
                soldpig[soldpignum].pigstynum = r->data.pigstynum;
                soldpig[soldpignum].num = r->data.num;
                if (r->data.type == &a[0]){
                    DouStr(r->data.weight * 30);
                    HugeNumber(fileName, price);
                    soldpig[soldpignum].pri = r->data.weight * 30;
                }
                if (r->data.type == &b[0]){
                    DouStr(r->data.weight * 14);
                    HugeNumber(fileName, price);
                    soldpig[soldpignum].pri = r->data.weight * 14;
                }   
                if (r->data.type == &c[0]){
                    DouStr(r->data.weight * 12);
                    HugeNumber(fileName, price);
                    soldpig[soldpignum].pri = r->data.weight * 12;
                }
				OutFile1 << soldpig[soldpignum].pigstynum << "����Ȧ" << soldpig[soldpignum].num << "��" << soldpig[soldpignum].type << soldpig[soldpignum].weight << "kg" << soldpig[soldpignum].time << "�� ����" << soldpig[soldpignum].pri << "Ԫ" << endl;
				soldpignum++;    
                r->data.time = 0;
                r->data.type = &d[0];
                r->data.weight = 0;
                j++;
            }
        }
        p->Data.pignum = p->Data.pignum - j;
        if(p->Data.pignum==0) p->Data.black = 0;
        p = p->next;
    }
}

bool Full(Lnode *h){//������Ȧ����û��
    Lnode *p;
    p = h;
    while(p->next!=NULL)
    {
        lnode *r = p->Data.a;
        while(r->next!=NULL){
            if(r->data.weight==0) return false;
            r=r->next;
        }
        p=p->next;
    }
    return true;
}

void random(pig *u){//���һ����
    double wei;
    wei=rand() % 30+20.00;
    u->weight = wei;
    int tpnum;
    tpnum = rand() % 3;
    switch(tpnum){
        case 0:
            u->type = &a[0];
            break;
        case 1:
            u->type = &b[0];
            break;
        case 2:
            u->type = &c[0];
            break;
    };
    u->time = 0;
    u->ill = false;
}


int main()
{
    int xx = 1;
    int button;
    char smallbutton='0';
    while(xx){  
        cout << "               ����ģ��" << endl;
        cout << "======================================" << endl;
        cout << "             1.��ʼ����" << endl;
        cout << "             2.�������" << endl;
        cout << "             3.�˳���Ϸ" << endl;
        cout << "======================================" << endl;
        cin >> button;
        system("cls");
        while(button!=1&&button!=2&&button!=3){
            cout << "����������ֲ���ȷŶ������������" << endl;
            cin >> button;
        }
        if(button==1){
            xx = 0;
            cout << "=================================" << endl;
            cout << "            1.�µ���Ϸ" << endl;
            cout << "            2.������Ϸ" << endl;
            cout << "=================================" << endl;
            cin >> smallbutton;
            system("cls");
        }
        if(button==2){
            cout << "================================================================" << endl;
            cout << "����һ��ũ��������һ����100����Ȧ������0-99��ţ���ÿ����Ȧ���" << endl;
            cout << "��10ͷ������0��9��ţ�����һ��������Ʒ�֣�����С����ʹ󻨰�" << endl;
            cout << "�����ں���ö�����Ϊ֮����������Ȧ��ÿ3���£��������Ȧһ����" << endl;
            cout << "�����������س���150��ĺ���������1��ģ�ͬʱ����һ�����̶������" << endl;
            cout << "Ʒ�֡�����¼�����ѡ��������ɣ�����ĳ�ʼ������20-50kg,��ÿһͷ" << endl;
            cout << "���ÿ����������0.0-1.2kg֮�䣨��Ϸ��1s����һ�죩��������ȷ֣�" << endl;
            cout << "����100����Ȧ����ǻ�Ϊ��ͳ�������������ۼۡ�������15Ԫһ�С" << endl;
            cout << "����7Ԫһ��󻨰���6Ԫһ���" << endl;
            cout << "                     �������������Ϸ" << endl;
            cout << "=================================================================" << endl;
            getch();
            system("cls");
        }
        if(button==3) return 0;
    }
    Lnode *p;
    p=(Lnode *)malloc(sizeof(Lnode));
    p->next = NULL;
    Creat(p,100);
    srand((int)time(0));
    pig u;
    if(smallbutton=='1'){
        int n = rand() % 500;
        while(n==0){
            n = rand() % 500;
        }
        for (int j = 0; j < n;j++){
            random(&u);
            Input(p, u);
        }
    }
    int days = 1;
    if(smallbutton=='2'){
        if(!InFile1){
            cout << "û�д洢�ϴ���Ϸ��¼\n";
            return 0;
        }
        //cout << 1;
       
    }
    cout << "==============================" << endl;
    //cout << "          ��ʼ����" << endl;
    cout << "           �����С�����"<<endl;
    cout << "  �����������ͣ��ѯ��Ȧ���" << endl;
    cout << "==============================" << endl;
    while (1)
    {   ergoPW(p);
        if (days % 90 == 0)
        {
            pricesum(p);
           
            int littlepig = rand() % 100;
            for (int jj = 0; jj < littlepig; jj++)
            {
                if(Full(p)) break;
                random(&u);
				OutFile3 << u.type << u.weight <<"kg ";
				if(u.ill==false) OutFile3 << "����"<<endl;
                else if(u.ill==true) OutFile3 << "����"<<endl;
				Input(p, u);
            }
        }
        cout <<"��"<< days <<"�� ";
        if(days%5==0) {
            cout<<endl;
            system("cls");
            cout << "==============================" << endl;
            //cout << "          ��ʼ����" << endl;
            cout << "           �����С�����"<<endl;
            cout << "  �����������ͣ��ѯ��Ȧ���" << endl;
            cout << "==============================" << endl;
        }
        if (_kbhit()){//����а������£���_kbhit()���������棬ͷ�ļ�conio.h
            getch();//�������룬������ʾ
            system("cls");
            int ff;
            while(ff){
                cout << endl;
                cout << "====================================" << endl;
                cout << "               ѡ�" << endl;
                cout << "           1.��Ȧ����" << endl;
                cout << "           2.�鿴��Ȧ" << endl;
                cout << "           3.����ֲ�" << endl;
                cout << "           4.���۵���" << endl;
                cout << "           5.��������" << endl;
                cout << "           6.����ģ��" << endl;
                cout << "           7.�˳���Ϸ" << endl;
                cout << "====================================" << endl;
                cin >> button;
                system("cls");
                if (button == 1){
                    cout << "���ǵ�"<<days<<"���������Ȧ�����" << endl;
                    output(p);
                }
                else if (button == 2){
                    cout << "ѡ����Ȧ��ţ�0-99" << endl;
                    cin >> button;
                    while(button>99||button<0){
                        cout << "�������ѡ���ȷ������������" << endl;
                        cin >> button;
                    }
                    cout << "���ǵ�" << days << "��ĵ�" << button << "����Ȧ�������" << endl;
                    onlyergo(p, button);
                }
                else if(button==3){
                    while(1){
                        cout << "==================================" << endl;
                        cout << "      ����鿴��һ����ֲ����" << endl;
                        cout << "             1.����" << endl;
                        cout << "             2.С����" << endl;
                        cout << "             3.�󻨰���" << endl;
                        cout << "             4.����" << endl;
                        cout << "==================================" << endl;
                        int sr;
                        cin >> sr;
                        system("cls");
                        if(sr==4) {system("cls");break;}
                        switch(sr){
                            case 1:raceergo(p, &a[0]);
                                break;
                            case 2:raceergo(p, &b[0]);
                                break;
                            case 3:raceergo(p, &c[0]);
                                break;
                        }
                        if(sr!=1&&sr!=2&&sr!=3&&sr!=4) cout << "�������ѡ���ȷŶ" << endl;
                        cout << "�������������һ����" << endl;
                        //system("cls");
                        getch();
                        system("cls");
                    }
                }
                else if (button == 4){
                    cout << "���������" << endl;
                    int kk;
                    for (int jj = 0; jj < 100;jj++){
                        kk = 0;
                        for (int rr = 0; soldpig[rr].weight != 0;rr++){
                            if (soldpig[rr].pigstynum == jj){
                                if(kk==0){
                                    cout << jj << endl;
                                    kk = 1;
                                }
                                cout<< soldpig[rr].num <<"��"<< soldpig[rr].type << soldpig[rr].weight <<"kg"<< soldpig[rr].time << "�� ����"<<soldpig[rr].pri<<"Ԫ"<<endl;
                            }
                        }  
                    }
                    if(price[0]==0)
                        cout << "����δ�кϸ��������Ŷ" << endl;
                    else{
                        cout << endl;
                        cout << "һ��������" << price << "Ԫ" << endl;
                    }
                }
                else if(button==5) break;
                else if(button==6){
                }
                else if(button==7) {
                    File(p,days);
                    OutFile2.close();
                    OutFile3.close();
                    return 0;
                }
                else{
                    cout << "�������ѡ���ȷŶ" << endl;
                }
                if(button!=3){
                    cout << "�������������һ����" << endl;
                    getch();
                    system("cls");
                }
                ff = 1;
            }
            cout << "��������ɼ�������" << endl;
            getch();
            cout << "==============================" << endl;
            cout << "            �����С�����" << endl;
            cout << "   �����������ͣ��ѯ��Ȧ���" << endl;
            cout << "==============================" << endl;
        }
        days++; 
    }
    OutFile1.close();
    OutFile2.close();
    OutFile3.close();
    return 0;
}
