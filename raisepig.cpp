#include<stdlib.h>
#include<string>
#include<iostream>
#include<ctime>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include <sstream>    //���������ת�� 
#include<stdio.h>
using namespace std;
static int pigjuanNum = 0;//��Ȧ���
static int pigNum = 0;//������
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
void DouStr(double freq1)//double��char(�۸�price����char���ʹ���ģ� 
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
    int ia=ta+1,ib=tb+1,zhengshu[500],xiaoshu[500],c,j,e;
    memset(xiaoshu,0,sizeof(xiaoshu));//��ʾС����������
    memset(zhengshu,0,sizeof(zhengshu));//��ʾ����
    ta--;tb--;
    i=j=0;
    while(1)//���������ĺ�
    {
        if(ta>=0)
        {zhengshu[i]+=aaa[ta]-'0';ta--;}
        if(tb>=0)
        {zhengshu[i]+=bbb[tb]-'0';tb--;}
        i++;         //i��ʾ����λ�ĳ���
        if(ta<0&&tb<0)
        break;
    }
    while(1)//�����С�������֮��
    {
        if(ia<tr1)
        {xiaoshu[j]+=aaa[ia]-'0';ia++;}
        if(ib<tr2)
        {xiaoshu[j]+=bbb[ib]-'0';ib++;}
        j++;         //j��ʾС��������ĳ���

        if(ia>=tr1&&ib>=tr2)
        break;
    }
    c=0;
    for(e=j-1;e>=0;e--)//��ʼ��λ
    {
        xiaoshu[e]+=c;
        c=xiaoshu[e]/10;
        xiaoshu[e]%=10;
    }
    for(e=0;e<i;e++)
    {
        zhengshu[e]+=c;
        c=zhengshu[e]/10;
        zhengshu[e]%=10;
    }
    if(c)
    {
        zhengshu[e]+=c;i++;
    }
    for(e=j-1;e>=0;e--)//ȥ�����������
    if(xiaoshu[e])
    break;
    else
    j--;
    for(e=i-1;e>=0;e--)
    if(zhengshu[e])
    break;
    else
    i--;
    int jj = 0;
    for(e=i-1;e>=0;e--)//��������ֵĺ�
    {
        price[jj] = zhengshu[e]+'0';
        jj++;
    }
    if(j>0)//���С����������������С����
    { 
        price[jj] = '.';
        jj++;
    }
    for(e=0;e<j;e++){
        price[jj] = xiaoshu[e]+'0';
        jj++;
    }
    if(j<=0&&i<=0){//����������Ϊ��ʱ����Ĳ���������������
        price[jj] = '0';
        jj++;
    }
}

typedef struct Pig{//��
    int pigstynum;     //��Ȧ��� 
    int num;           //��ı�� 
    char *type;        //������� 
    double weight;     //������� 
    double time;       //ʱ�� 
    double pri;        //�۸� 
    bool ill;          //����״�� 
}pig;
static Pig soldpig[10000];//Pig���͵��������    �۳����� 

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
        r->data.pigstynum = pigjuanNum;
        r->data.num = pigNum;
        pigNum++;
        if(pigNum==10) pigNum = pigNum - 10;
        r=p;
    }
    pigjuanNum++;
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
        r->Data.no = pigjuanNum;
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
            
            r->data.weight = s;
            InFile1 >> j;
            r->data.time = j;
            InFile1 >> j;
            if(j==0) r->data.ill = false;
            if(j==1) r->data.ill = true;
            r = r->next;
        }
        p=p->next;
    }
}

void pigweightgrow(Lnode *h){//����������ÿͷ��1�������
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

void outputonepig(Lnode *h,int n){//�ҵ���Ӧ��Ȧ����������Ȧ�������
    Lnode *p = h;
    while (p->Data.no!=n){
        p = p->next;
    }
    lnode *r = p->Data.a;
    if(p->Data.pignum==0)
        cout << "                                               ���������Ȧ��ʱ��û��������" << endl;
    else{
        cout << "                                       *********************************************" << endl;
        while(r->next!=NULL){
            if(r->data.weight!=0){
                cout << r->data.num << r->data.type << " ";  
            }
            r = r->next;
        }
        cout << endl;
        cout << "                                              ����鿴�ڼ�ͷ���ۣ��������ı��" << endl;
        cout << "                                       ********************************************" << endl;
        int y;
        cin >> y;
        r = p->Data.a;
        while(r->next!=NULL){
            if(r->data.num==y) {
                if(r->data.weight!=0)
                    cout << r->data.num << r->data.type << r->data.weight << "kg" << r->data.time << "�� ";
                else
                    cout << "                             �ɴ��۾���������������Ҫ����ֻ��^(-_-)^ "<< endl;
                break;
            }
            r = r->next;
        }
        cout << endl;
    }
}

void zhongzufenbu(Lnode *h,char *g){//����ֲ�
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

void chujuanzhuzongjia(Lnode *h){//�������г�Ȧ��ļ۸���ճ�Ȧ���
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

void suijizhu(pig *u){//���һ����
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

void shezhibingyuanzhu(Lnode *h,int n,int m){//����һ����Դ��
    Lnode *p = h;
    for (int j = 0; j < n;j++){
        p = p->next;
    }
    p->Data.illpignum++;
    lnode *r = p->Data.a;
    for (int d = 0; d < m;d++){
        r = r->next;
    }
    r->data.ill = true;
}

void outputill(Lnode *h){//��ʾ��Ȧ���λ�ù��û�ѡ��
    Lnode *p;
    p = h;
    while(p->next!=NULL)
    {
        if(p->Data.pignum!=0){
            cout<<p->Data.no<<"����Ȧ"<<" ";
            lnode *r = p->Data.a;
            while(r->next!=NULL){
                if(r->data.weight!=0)
                cout << r->data.num << " ";
                r=r->next;
            }
            cout << endl;
        }
        p=p->next;
    }
}

static int contagionda;
void chuanran(Lnode *h,int n){//��Ⱦ����Ȧ��������Ȧ
    int contagion=2;
    double loss;
    Lnode *p;
    p = h;
    for (int j = 0; j < n; j++)
    {
        p = p->next;
    }
    lnode *r = p->Data.a;
    for (; r->next != NULL; r = r->next)
        {
            if (r->data.weight != 0 && r->data.ill == false)
            {
                int t = rand() % 100;
                if (t < 50)
                {
                    p->Data.illpignum++;
                    r->data.ill = true;
                    contagion = 1;
                    if (r->data.type == &a[0])
                    {
                        loss = r->data.weight * 30;
                    }
                    if (r->data.type == &b[0])
                    {
                        loss = r->data.weight * 14;
                    }
                    if (r->data.type == &c[0])
                    {
                        loss = r->data.weight * 12;
                    }
                    cout << r->data.pigstynum << "����Ȧ" << r->data.num << r->data.type << "����Ⱦ "
                         << "��ʧ" << loss << "Ԫ" << endl;
                }
            }
        }
    if(n!=99){
        r = p->next->Data.a;
        for (; r->next != NULL; r = r->next)
        {
            if(r->data.weight!=0&&r->data.ill==false){
                int t = rand() % 100;
                if (t < 15)
                {
                    p->Data.illpignum++;
                    r->data.ill = true;
                    contagion = 1;
                    if (r->data.type == &a[0])
                    {
                        loss = r->data.weight * 30;
                    }
                    if (r->data.type == &b[0])
                    {
                        loss = r->data.weight * 14;
                    }
                    if (r->data.type == &c[0])
                    {
                        loss = r->data.weight * 12;
                    }
                    cout << r->data.pigstynum <<"����Ȧ"<< r->data.num << r->data.type << "����Ⱦ "<< "��ʧ" << loss << "Ԫ" << endl;
                }
            }
        }
    }
    p = h;
    if(n!=0){
        for (int j = 0; j < n - 1; j++)
        {
            p = p->next;
        }
        r = p->Data.a;
        for (; r->next != NULL; r = r->next)
        {
            if(r->data.weight!=0&&r->data.ill==false){
                int t = rand() % 100;
                if (t < 15)
                {
                    p->Data.illpignum++;
                    r->data.ill = true;
                    contagion = 1;
                    if (r->data.type == &a[0])
                    {
                        loss = r->data.weight * 30;
                    }
                    if (r->data.type == &b[0])
                    {
                        loss = r->data.weight * 14;
                    }
                    if (r->data.type == &c[0])
                    {
                        loss = r->data.weight * 12;
                    }
                    cout << r->data.pigstynum <<"����Ȧ"<< r->data.num << r->data.type << "����Ⱦ "<< "��ʧ" << loss << "Ԫ" << endl;
                }
            }
        }
    }
    if(contagion==1) contagionda = 1;
    else contagionda = 0;
}

static int head=0;
static int back=99;
void ganranzhujuan(Lnode *h){//�����Ⱦ����Ȧ��
    Lnode *p;
    p = h;
    while(p->next!=NULL){
        int k = 0;
        lnode *r;
        r = p->Data.a;
        while(r->next!=NULL){
            if(r->data.ill==true&&r->data.weight!=0){
                head = p->Data.no;
                k = 1;
                break;
            }
            r = r->next;
        }
        if(k==1) break;
        p = p->next;
    }
    while(p->next!=NULL){
        lnode *r;
        r = p->Data.a;
        int j = 0;
        while(r->next!=NULL){
            if(r->data.ill==false&&r->data.weight!=0){
                j++;
            }
            r = r->next;
        }
        if(j==p->Data.pignum) {
            back = p->Data.no - 1;
            break;
        }
        p = p->next;
    }
}

bool allill(Lnode *h){//�ж��Ƿ�ȫ����Ⱦ
    Lnode *p;
    p = h;
    while(p->next!=NULL){
        lnode *r;
        r = p->Data.a;
        while(r->next!=NULL){
            if(r->data.weight!=0&&r->data.ill==false){
                return false;
            }
            r = r->next;
        }
        p = p->next;
    }
    return true;
}

void allhealthy(Lnode *h){//����������Ϊû��
    Lnode *p;
    p = h;
    while(p->next!=NULL){
        lnode *r;
        r = p->Data.a;
        p->Data.illpignum = 0;
        while(r->next!=NULL){
            if(r->data.weight!=0){
                r->data.ill = false;
            }
            r = r->next;
        }
        p = p->next;
    }
}

void fengxiankongzhi(Lnode *h){//���տ���
    Lnode *p;
    p = h;
    int J = 0,f=0;
    lnode *r;
    while(p->next!=NULL){
        r = p->Data.a;
        while(r->next!=NULL){
            if(r->data.ill==true){
                f = 1;
                break;
            }
            r = r->next;
        }
        if(f==1){
            Lnode *pp;
            pp = h;
            for (int jj = 0; jj < J-1;jj++){
                pp = pp->next;
            }
            int x = 0;
			double Pric = 0;
            while(pp->next!=NULL&&x<3){
                pp->Data.illpignum = 10;
                r = pp->Data.a;
                while(r->next!=NULL){
                    if(r->data.weight!=0&&r->data.ill==false){
                        if (r->data.type == &a[0])
                        {
                            Pric = Pric + r->data.weight * 30;
                        }
                        else if (r->data.type == &b[0])
                        {
                            Pric = Pric + r->data.weight * 14;
                        }
                        else if (r->data.type == &c[0])
                        {
                            Pric = Pric + r->data.weight * 12;
                        }
                        r->data.time = 0;
                        r->data.type = &d[0];
                        r->data.weight = 0;
                        r->data.ill = false;
                        pp->Data.pignum--;
                    }
                    r = r->next;
                }
                x++;
                pp = pp->next;  
            }
            cout << "*****************************" << endl;
            if(J==0) cout << "������"<< J <<" "<< J + 1 << "����Ȧ" << endl;
            else if(J==99) cout << "������" << J - 1 <<" "<< J << "����Ȧ" << endl;
            else cout << "������" << J - 1 <<" "<< J <<" "<< J + 1 << "����Ȧ" << endl;
            cout << "����" << Pric << "Ԫ" << endl;
            cout << "******************************" << endl;
            f = 0;
        }
        J++;
        p = p->next;
    }
}

void Clearsipig(Lnode *h){//��������60kg�����ˣ����������
    Lnode *p;
    p = h;
    while(p->next!=NULL){
        lnode *r;
        r = p->Data.a;
        if(p->Data.illpignum==10){
            p->Data.illpignum = 0;
            while(r->next!=NULL){
                if(r->data.ill==true&&r->data.weight>=60){
                    r->data.ill = false;
                    r->data.pri = 0;
                    r->data.time = 0;
                    r->data.type = &d[0];
                    r->data.weight = 0;
                    r->data.num = 0;
                    p->Data.pignum--;
                }
                r = r->next;
            }
        }
        p = p->next;
    }
}

int main() 
{
    int xx = 1;
    int button;
    char smallbutton='0';
    while(xx){  
        cout << endl;
		cout << endl;
		cout << endl;
		cout << "                                          ����һ�����ֵ�����ģ��С��Ϸ" << endl;
		cout << endl;
        cout << "                                 *********************************************" << endl;
        cout << endl; 
        cout << "                                               1.��ʼ��������֮��" << endl;
        cout << "                                               2.������������¸�" << endl;
        cout << "                                               3.�˳���Ϸ���Զ�����" << endl;
        cout << endl;
        cout << "                                 *********************************************" << endl;
        cin >> button;
        system("cls");
        while(button!=1&&button!=2&&button!=3){
            cout << "                                   �ɴ��۾���ϸ�����������������ѡ��  *_*" << endl;
            cin >> button;
        }
        if(button==1){
            xx = 0; 
            cout << "                                    ****************************************" << endl;
            cout << endl;
            cout << endl;
            cout << "                                            1.��ʼһ���µ���Ϸ" << endl;
            cout << "                                            2.������һ�ε���Ϸ" << endl;
            cout << endl; 
            cout << endl;
            cout << "                                    ****************************************" << endl;
            cin >> smallbutton;
            system("cls");
        }
        if(button==2){
            cout << "                        ******************************************************************************" << endl;
            cout << endl; 
            cout << "                            ����һ��ũ��������һ����100����Ȧ������0-99��ţ���ÿ����Ȧ���" << endl;
            cout << "                            ��10ͷ������0��9��ţ�����һ��������Ʒ�֣�����С����ʹ󻨰�" << endl;
            cout << "                            �����ں���ö�����Ϊ֮����������Ȧ��ÿ3���£��������Ȧһ����" << endl;
            cout << "                            �����������س���150��ĺ���������1��ģ�ͬʱ����һ�����̶������" << endl;
            cout << "                            Ʒ�֡�����¼�����ѡ��������ɣ�����ĳ�ʼ������20-50kg,��ÿһͷ" << endl;
            cout << "                            ���ÿ����������0.0-1.2kg֮�䣨��Ϸ��1s����һ�죩��������ȷ֣�" << endl;
            cout << "                            ����100����Ȧ����ǻ�Ϊ��ͳ�������������ۼۡ�������15Ԫһ�С" << endl;
            cout << "                            ����7Ԫһ��󻨰���6Ԫһ���" << endl;
            cout << endl;
            cout << "                                                  Ϲ������һ��������Ϸ" << endl;
            cout << endl; 
            cout << "                        ******************************************************************************" << endl;
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
            suijizhu(&u);
            Input(p, u);
        }
    }
    int days = 1;
    if(smallbutton=='2'){
        if(!InFile1){
            cout << "                                              ��һ�ΰ�С���ӣ�û�м�¼\n";
            cout << "                                             ������һ����ȥ����......" << endl;
            return 0;
        }
        //cout << 1;
        ReadingFiles(p);
        InFile1.close();
        //cout << 1;
        output(p);
        getch();
        
    }
    cout << "                                              **************************************************" << endl;
    cout << endl;
	cout << "                                               �Ѿ�������Ϊ��Ͷ�ʽ���һ��������Ȧ������һ������" <<endl;
	cout << endl;
	cout << "                                                               ����л�ң��ǵû�Ǯ" <<endl;
	cout << endl; 
    cout << "                                                                �Զ������С�����"<<endl;
    cout << endl;
    cout << endl;
    cout << "                                                      ���ѯ��Ȧ���������˫��666" << endl;
    cout << endl;
    cout << "                                              **************************************************" << endl;
    while (1)
    {   pigweightgrow(p);
        if (days % 90 == 0)
        {
            chujuanzhuzongjia(p);
            Clearsipig(p);
            int littlepig = rand() % 100;
            for (int jj = 0; jj < littlepig; jj++)
            {
                if(Full(p)) break;
                suijizhu(&u);
				OutFile3 << u.type << u.weight <<"kg ";
				if(u.ill==false) OutFile3 << "����"<<endl;
                else if(u.ill==true) OutFile3 << "����"<<endl;
				Input(p, u);
            }
        }
        cout <<"��"<< days <<"�� ";
       
        if (_kbhit()){//����а������£���_kbhit()���������棬ͷ�ļ�conio.h
            getch();//�������룬������ʾ
            system("cls");
            int ff;
            while(ff){
                cout << endl;
                cout << "                                       ***********************************************" << endl;
                cout << "                                                              �˵���" << endl;
            	cout << endl;
                cout << "                                                           1.��һ���ж����" << endl;
                cout << endl;
                cout << "                                                           2.�鿴��Ȧ�����" << endl;
                cout << endl;
                cout << "                                                           3.�ҵ���ɶƷ��" << endl;
                cout << endl;
                cout << "                                                           4.��ֵ�ֵ����Ǯ" << endl;
                cout << endl;
                cout << "                                                           5.����Ը��������" << endl;
                cout << endl;
                cout << "                                                           6.ģ��С�������" << endl;
                cout << endl;
                cout << "                                                           7.�ұ����˳���Ϸ" << endl;
                cout << "                                       ***********************************************" << endl;
                cin >> button;
                system("cls");
                if (button == 1){
                    cout << "���ǵ�"<<days<<"���������Ȧ�����" << endl;
                    output(p);
                }
                else if (button == 2){
                    cout << "��������Ȧ��ţ�0-99" << endl;
                    cin >> button;
                    while(button>99||button<0){
                        cout << "�������ѡ���ȷ�����������루��ɫЦ����" << endl;
                        cin >> button;
                    }
                    cout << "���ǵ�" << days << "��ĵ�" << button << "����Ȧ�������" << endl;
                    outputonepig(p, button);
                }
                else if(button==3){
                    while(1){
                        cout << "                              *****************************************************" << endl;
                        cout << endl; 
                        cout << "                                 ���һ���⼸��������鿴������ķֲ����" << endl;
                        cout << endl;
						cout << "                                                  �����밴1" << endl;
                        cout << endl;
						cout << "                                                  С�����밴2 " << endl;
                        cout << endl;
						cout << "                                                  �󻨰����밴3" << endl;
                        cout << endl;
						cout << "                                                  ������һ���밴4" << endl;
                        cout << endl;
						cout << "                              ******************************************************" << endl;
                        int sr;
                        cin >> sr;
                        system("cls");
                        if(sr==4) {system("cls");break;}
                        switch(sr){
                            case 1:zhongzufenbu(p, &a[0]);
                                break;
                            case 2:zhongzufenbu(p, &b[0]);
                                break;
                            case 3:zhongzufenbu(p, &c[0]);
                                break;
                        }
                        if(sr!=1&&sr!=2&&sr!=3&&sr!=4) cout << "�������ѡ���д����أ��ֶ���ͷ��" << endl;
                        cout << "Ϲ��һ��������һ����" << endl;
                        //system("cls");
                        getch();
                        system("cls");
                    }
                }
                else if (button == 4){
                    cout << "������������" << endl;
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
                        cout << "                            ��Ҳ̫�ļ��˰ɣ����̶���û�дﵽ���۱�׼��" << endl;
                    else{
                        cout << endl;
                        cout << "һ��������" << price << "Ԫ" << endl;
                    }
                }
                else if(button==5) break;
                else if(button==6){
                    cout << "����Ŀǰ��ӵ�е�������" << endl;
                    outputill(p);
                    //allhealthy(p);
                    cout << "                                 ��ѡ��һ��������С��ù��������������Դͷ" << endl;
                    cout << endl; 
                    cout << "                                          �����룺��Ȧ���(0-99)  " << endl;
                    cout << endl;
					cout << "                                                  ������(0-9)" << endl;
                    int n, m;
                    cin >> n >> m;
                    shezhibingyuanzhu(p, n, m);
                    system("cls");
                    cout << "����Ϊ��ʵʱ����������Ⱦ���" << endl;
                    int jj = 1;
                    for (;allill(p)!=true;jj++){
                        days++;
                        pigweightgrow(p);
                        int contagionDa = 0;
                        ganranzhujuan(p);
                        for (int rr = head; rr <= back;rr++){
                            chuanran(p, rr);
                            if(contagionda==1) contagionDa = 1;
                        }
                        if(contagionDa==1) {
                            cout << "��" << days << "��" << endl;
                            cout << "******************************" << endl;
                        }
                        Sleep(100);
                        if(days%90==0){
                            chujuanzhuzongjia(p);
                        }
                        double uu=0;
                        if (_kbhit()){//����а������£���_kbhit()���������棬ͷ�ļ�conio.h
                            getch();//�������룬������ʾ
                            int yy = 1;
                            while(yy){
                                system("cls");
                                cout << "                                   ******************************************"<<endl;
                                cout << endl; 
                                cout <<  "                                        ���Ƿ����ķ�����Ⱦ������" << endl;
                                cout << endl;
								cout << "                                                   1.��" << endl;
                                cout << endl;
								cout << "                                                   2.��" << endl;
                                cout << endl;
								cout << "                                                   3.����" << endl;
                                cout << endl;
								cout << "                                   *******************************************"<<endl;
                                cin >> button;
                                if(button==1){
                                    system("cls");
                                    fengxiankongzhi(p);
                                    yy = 0;
                                    cout << "                              *********************************************" << endl;
                                    cout << endl;
									cout << "                                    �ѳɹ���ֹ�˼��������ӣ��ɵ�Ư��" << endl;
                                    cout << endl;
                                	cout << "                              *********************************************" << endl;
                                    cout << endl; 
									cout << "                                             �밴���������" << endl;
                                    uu = 1.876;
                                }
                                else if(button==2){
                                    system("cls");
                                    cout << "                                           ��������ɼ�������" << endl;
                                    yy = 0;
                                }
                                else if(button==3){
                                    system("cls");
                                    cout << "                             **********************************************" << endl;
                                    cout << endl;
                                    cout << "                            ���ط�ʽ�ܼ򵥣��Ͱ��в�����Ȧ�Լ�������Ȧ��������" << endl;
                                    cout << endl;
									cout << "                            �����ٽ������С�����̶��Ž���Щ��Ȧ�������������ơ�" << endl;
                                    cout << endl;
									cout << "                                                 1.����" << endl;
                                    cout << endl;
									cout << "                             **********************************************" << endl;
                                    cin >> button;
                                    system("cls");
                                    if(button==1) yy=1;
                                }	
                            }
                            getch();
                            system("cls");
                        }
                        if(uu==1.876) cout << "      ..........���ĵ�һ�ᣬ��Ϊ�޸�Ⱦ���Բ���ʾ�����ڼ��㽡������ۼۣ�����һ�����Լ���Ϲ��.........." << endl;
                    }
                    if(price[0]==0) cout << "                                         ����������0Ԫ" << endl;
                    else cout << "                                            ����������" << price << "Ԫ" << endl;
                    cout << endl; 
                    cout << "                                          ���˰ɣ���������Ⱦ������,��"<<jj<<"������������" << endl;
                    //return 0;
                }
                else if(button==7) {
                    File(p,days);
                    OutFile2.close();
                    OutFile3.close();
                    return 0;
                }
                else{
                    cout << "                ���ڰ�ο�Լ��������һ����������Ҫ���ˣ�" << endl;
                }
                if(button!=3){
                    cout << "                           �������������һ����" << endl;
                    getch();
                    system("cls");
                }
                ff = 1;
            }
            cout << "                                   ����������ܼ���������" << endl;
            getch();
            cout << "                          **************************************" << endl;
            cout << endl;
			cout << "                                     ���ڿ̿������...." << endl;
            cout << endl;
			cout << "                              �����������ͣ��ѯ��Ȧ���" << endl;
            cout << endl;
			cout << "                          **************************************" << endl;
        }
        days++; 
    }
    OutFile1.close();
    OutFile2.close();
    OutFile3.close();
    return 0;
}
