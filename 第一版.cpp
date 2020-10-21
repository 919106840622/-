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
static int I = 0;//猪圈序号
static int i = 0;//猪的序号
static string a = "黑猪";
static string b = "小花猪";
static string c = "大花白猪";
static string d = "空";
char price[500];
static int soldpignum=0;


static char fileName[500];
void DouStr(double freq1)//double变char
{
    ostringstream oss1;
    oss1<<freq1;
    memset(fileName,0,500);
//先转化为流，再转换为string,然后再转换为char
    strcat(fileName,(oss1.str()).c_str());
}

void HugeNumber(char aaa[500],char bbb[500])//价钱的计算大数相加
{
    int i,tb,ta;
    ta = strlen(aaa);
    int tr1 = strlen(aaa);
    for (i = 0; i < tr1; i++) //找出小数点的位置
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
    memset(xs,0,sizeof(xs));//表示小数点后的数字
    memset(zhs,0,sizeof(zhs));//表示整数
    ta--;tb--;
    i=j=0;
    while(1)//计算整数的和
    {
        if(ta>=0)
        {zhs[i]+=aaa[ta]-'0';ta--;}
        if(tb>=0)
        {zhs[i]+=bbb[tb]-'0';tb--;}
        i++;         //i表示整数位的长度
        if(ta<0&&tb<0)
        break;
    }
    while(1)//计算出小数点的数之和
    {
        if(ia<tr1)
        {xs[j]+=aaa[ia]-'0';ia++;}
        if(ib<tr2)
        {xs[j]+=bbb[ib]-'0';ib++;}
        j++;         //j表示小数点后数的长度

        if(ia>=tr1&&ib>=tr2)
        break;
    }
    c=0;
    for(e=j-1;e>=0;e--)//开始进位
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
    for(e=j-1;e>=0;e--)//去掉无意义的零
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
    for(e=i-1;e>=0;e--)//输出两数字的和
    {
        price[jj] = zhs[e]+'0';
        jj++;
    }
    if(j>0)//如果小数点后有数字则输出小数点
    { 
        price[jj] = '.';
        jj++;
    }
    for(e=0;e<j;e++){
        price[jj] = xs[e]+'0';
        jj++;
    }
    if(j<=0&&i<=0){//当两个数都为零时上面的不会输出，则输出零
        price[jj] = '0';
        jj++;
    }
}

typedef struct Pig{//猪
    int pigstynum;
    int num;
    char *type;
    double weight;
    double time;
    double pri;
    bool ill;
}pig;
static Pig soldpig[10000];

typedef struct Pigsty{//猪圈
    int no;
    int pignum;
    int black;
    struct node *a;
    int illpignum;
}pigsty;

typedef struct Node//猪圈指针
{
    pigsty Data;
    struct Node *next;
}Lnode;

typedef struct node//猪指针
{
    pig data;
    struct node *next;
}lnode;

void Clean(Lnode *p){//将猪圈清空
    Lnode *r = p;
    r->Data.black = 0;
    r->Data.no = 0;
    r->Data.pignum = 0;
    r->Data.illpignum = 0;
}

void clean(lnode *p){//将猪槽清空
    lnode *r = p;
    r->data.num = 0;
    r->data.pigstynum = 0;
    r->data.time = 0;
    r->data.type = &d[0];
    r->data.weight = 0;
    r->data.ill = false;
}

void creat(lnode *hh,int n)//生成猪槽
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

void Creat(Lnode *b,int n)//生成猪圈
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

void Input(Lnode *p,pig u)//放1猪进猪圈
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

void output(Lnode *h)//输出所有猪圈
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
                cout << r->data.num << r->data.type << r->data.weight <<"kg"<<r->data.time<< "天";
                if(r->data.ill==false) cout << "健康 ";
                else if(r->data.ill==true) cout << "患病 ";}
                r=r->next;
            }
            cout << endl;
        }
        p=p->next;
    }
}




void ergoPW(Lnode *h){//遍历并增加每头猪1天的体重
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

void onlyergo(Lnode *h,int n){//找到对应猪圈并输出这个猪圈的猪情况
    Lnode *p = h;
    while (p->Data.no!=n){
        p = p->next;
    }
    lnode *r = p->Data.a;
    if(p->Data.pignum==0)
        cout << "这个猪圈暂时没有养猪哦" << endl;
    else{
        cout << "===============================" << endl;
        while(r->next!=NULL){
            if(r->data.weight!=0){
                cout << r->data.num << r->data.type << " ";  
            }
            r = r->next;
        }
        cout << endl;
        cout << "         查看第几头猪" << endl;
        cout << "===============================" << endl;
        int y;
        cin >> y;
        r = p->Data.a;
        while(r->next!=NULL){
            if(r->data.num==y) {
                if(r->data.weight!=0)
                    cout << r->data.num << r->data.type << r->data.weight << "kg" << r->data.time << "天 ";
                else
                    cout << "您搜索的猪不存在哦" << endl;
                break;
            }
            r = r->next;
        }
        cout << endl;
    }
    //system("cls");
}

void raceergo(Lnode *h,char *g){//种族分布
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
                    cout << r->data.num << r->data.type << r->data.weight <<"kg"<<r->data.time<< "天 ";
                }
                r=r->next;
            }
            cout << endl;
        }
        p=p->next;
    }
    cout << "一共有" << racenum << "头" << *g << endl;
}


bool Full(Lnode *h){//看看猪圈满了没有
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

void random(pig *u){//随机一个猪
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
        cout << "               养猪模拟" << endl;
        cout << "======================================" << endl;
        cout << "             1.开始养猪" << endl;
        cout << "             2.养猪规则" << endl;
        cout << "             3.退出游戏" << endl;
        cout << "======================================" << endl;
        cin >> button;
        system("cls");
        while(button!=1&&button!=2&&button!=3){
            cout << "您输入的数字不正确哦，请重新输入" << endl;
            cin >> button;
        }
        if(button==1){
            xx = 0;
            cout << "=================================" << endl;
            cout << "            1.新的游戏" << endl;
            cout << "            2.继续游戏" << endl;
            cout << "=================================" << endl;
            cin >> smallbutton;
            system("cls");
        }
        if(button==2){
            cout << "================================================================" << endl;
            cout << "您是一个农场主，您一共有100个猪圈（按照0-99编号），每个猪圈最多" << endl;
            cout << "养10头猪（按照0到9编号），猪一共有三个品种：黑猪、小花猪和大花白" << endl;
            cout << "猪。由于黑猪好斗，将为之单独开辟猪圈。每3个月，养猪场会出圈一批猪" << endl;
            cout << "，包括：体重超过150斤的和饲养超过1年的；同时补充一批猪崽儿（猪的" << endl;
            cout << "品种、数量录入或者选择随机生成）。猪的初始体重在20-50kg,而每一头" << endl;
            cout << "猪的每日体重增长0.0-1.2kg之间（游戏中1s等于一天）。猪将会均匀分，" << endl;
            cout << "布在100个猪圈里，我们会为您统计您的猪总体售价。（黑猪15元一斤，小" << endl;
            cout << "花猪7元一斤，大花白猪6元一斤）。" << endl;
            cout << "                     按任意键返回游戏" << endl;
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
    
    cout << "==============================" << endl;
    //cout << "          开始养猪" << endl;
    cout << "           养猪中。。。"<<endl;
    cout << "  按任意键可暂停查询猪圈情况" << endl;
    cout << "==============================" << endl;
    while (1)
    {   ergoPW(p);
        if (days % 90 == 0)
        {
          
            
            int littlepig = rand() % 100;
            for (int jj = 0; jj < littlepig; jj++)
            {
                if(Full(p)) break;
                random(&u);
			
				
				Input(p, u);
            }
        }
        cout <<"第"<< days <<"天 ";
        if(days%5==0) {
            cout<<endl;
            system("cls");
            cout << "==============================" << endl;
            //cout << "          开始养猪" << endl;
            cout << "           养猪中。。。"<<endl;
            cout << "  按任意键可暂停查询猪圈情况" << endl;
            cout << "==============================" << endl;
        }
        if (_kbhit()){//如果有按键按下，则_kbhit()函数返回真，头文件conio.h
            getch();//键盘输入，不会显示
            system("cls");
            int ff;
            while(ff){
                cout << endl;
                cout << "====================================" << endl;
                cout << "               选项：" << endl;
                cout << "           1.猪圈总览" << endl;
                cout << "           2.查看猪圈" << endl;
                cout << "           3.种族分布" << endl;
                cout << "           4.已售的猪" << endl;
                cout << "           5.继续养猪" << endl;
                cout << "           6.退出游戏" << endl;
                cout << "====================================" << endl;
                cin >> button;
                system("cls");
                if (button == 1){
                    cout << "这是第"<<days<<"天的所有猪圈情况：" << endl;
                    output(p);
                }
                else if (button == 2){
                    cout << "选择猪圈编号：0-99" << endl;
                    cin >> button;
                    while(button>99||button<0){
                        cout << "您输入的选项不正确，请重新输入" << endl;
                        cin >> button;
                    }
                    cout << "这是第" << days << "天的第" << button << "个猪圈的情况：" << endl;
                    onlyergo(p, button);
                }
                else if(button==3){
                    while(1){
                        cout << "==================================" << endl;
                        cout << "      你想查看哪一种族分布情况" << endl;
                        cout << "             1.黑猪" << endl;
                        cout << "             2.小花猪" << endl;
                        cout << "             3.大花白猪" << endl;
                        cout << "             4.返回" << endl;
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
                        if(sr!=1&&sr!=2&&sr!=3&&sr!=4) cout << "您输入的选项不正确哦" << endl;
                        cout << "按任意键返回上一界面" << endl;
                        //system("cls");
                        getch();
                        system("cls");
                    }
                }
                else if (button == 4){
                    cout << "卖猪情况：" << endl;
                    int kk;
                    for (int jj = 0; jj < 100;jj++){
                        kk = 0;
                        for (int rr = 0; soldpig[rr].weight != 0;rr++){
                            if (soldpig[rr].pigstynum == jj){
                                if(kk==0){
                                    cout << jj << endl;
                                    kk = 1;
                                }
                                cout<< soldpig[rr].num <<"号"<< soldpig[rr].type << soldpig[rr].weight <<"kg"<< soldpig[rr].time << "天 卖了"<<soldpig[rr].pri<<"元"<<endl;
                            }
                        }  
                    }
                    if(price[0]==0)
                        cout << "您还未有合格的猪卖出哦" << endl;
                    else{
                        cout << endl;
                        cout << "一共卖出：" << price << "元" << endl;
                    }
                }
                else if(button==5) break;
                
                else if(button==6) {
                    return 0;
                }
                else{
                    cout << "您输入的选项不正确哦" << endl;
                }
                if(button!=3){
                    cout << "按任意键返回上一界面" << endl;
                    getch();
                    system("cls");
                }
                ff = 1;
            }
            cout << "按任意键可继续养猪" << endl;
            getch();
            cout << "==============================" << endl;
            cout << "            养猪中。。。" << endl;
            cout << "   按任意键可暂停查询猪圈情况" << endl;
            cout << "==============================" << endl;
        }
        days++; 
    }
   
    return 0;
}
