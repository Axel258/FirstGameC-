#include <iostream> //0-равнина,1-игрок,5 - меч,-1 - пустота
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

const int A = 24;// длина карты
const int B = 48; // ширина карты
const int N = 11; // количество монстров
const char G = '@'; // обозначение монстров
const int WALL   = -1;         
const int BLANK  = -2;
// -----------------------------------
class tMap
{
    public:
        int i,j,bk,rr,mm;
        // mountain='m',river='r', bridge='b', woods='w',ground='g';
        int Game_map[A][B];
        tMap(int r=2,int m=4){
         rr=r;mm=m;
         i=A; j=B;
        for (int c = 0;c<i;c++)
      
        for (int d=0;d<j;d++)
        {
            if ((c==0 )|( d ==0)|(c == (A-1)) | (d ==(B-1))) Game_map[c][d] = 10; else Game_map[c][d]= 0;
         }                
                              }
                                
        void set();
    
        void GenM(int,int,double);
        bool OK(int m[A][B],int c=0,int d=0, int o=1){if(m[c][d]==0){m[c][d]=o; return true;} else return false;}
        int GenR(int,int,double);
     //   void GenB(int,int,double);
    //    double GenW(double);
   //     void Gen(char,double);
        void out();
        char out1(int,int);
      
};

void tMap::set()
{    srand(time(0));
    for (int c = 0;c<A;c++)
      for (int d=0;d<B;d++)
          if ((c==0 )|( d ==0)|(c == (A-1)) | (d ==(B-1))) Game_map[c][d] = 10; else Game_map[c][d]= 0;
     GenR(rr,10,0.1);
   //  GenB(3,3,0.1);
     GenM(mm,10,0.1);
    Game_map[i/2][j/3]= 5;
}

void tMap::GenM(int m=4,int num = 10,double freq=0.1)
{
    int k=int((A-2)*(B-2)*freq/num),xy=0,k2;
    int *mas;
    mas= new int [2*k];
    for(int c=0;c<=2*k;c+=2) {do{mas[c]=rand()%(A-2)+2;mas[c+1]=rand()%(B-2)+2;}while(Game_map[mas[c]][mas[c+1]]!=0);}
    while(xy<=2*k)
    {
     int xx=mas[xy],yy=mas[xy+1];
     Game_map[xx][yy]=m;
     for(int c=0;c<num;c++)
     {
      k2 = rand()%100;
      if(Game_map[xx][yy]==10 || xx>=A || yy>=B) break;
      if (k2<25 && OK(Game_map,xx+1,yy,m))
       xx+=1;
        else 
            if (k2>=25 && k2<50&& OK(Game_map,xx-1,yy,m))
                xx-=1;
        else
            if (k2>=50 && k2<75&& OK(Game_map,xx,yy+1,m))
                yy+=1;
        else
            if(OK(Game_map,xx,yy-1,m)) 
                yy-=1;
        else
            {c--;do{xx=rand()%(A-2)+2;yy=rand()%(B-2)+2;}while(Game_map[xx][yy]!=0);}
      }
    xy+=2;    
    }
    
}
int tMap::GenR(int r=2,int num = 10,double freq=0.1)
{
    int k=int((A-2)*(B-2)*freq/num),xy=0,k2;
    int *mas;
    mas= new int [2*k];
    for(int c=0;c<=2*k;c+=2) {do{mas[c]=rand()%(A-2)+1;mas[c+1]=rand()%(B-2)+1;}while(Game_map[mas[c]][mas[c+1]]!=0);}
    while(xy<=2*k)
    {
     int xx=mas[xy],yy=mas[xy+1];
     Game_map[xx][yy]=r;
     k2 = rand()%100;
          for(int c=0;c<num;c++)
          {
                if(Game_map[xx][yy]==10|| xx>=A || yy>=B) break;
                if (k2<25 && OK(Game_map,xx+1,yy,r)==true)
                 xx+=1;
                else 
                    if (k2>=25 && k2<50&& OK(Game_map,xx-1,yy,r)==true)
                     xx-=1;
                else
                    if (k2>=50 && k2<75&& OK(Game_map,xx,yy+1,r)==true)
                  yy+=1;
                else
                    if(OK(Game_map,xx,yy-1,r)==true) 
                     yy-=1;
                else
            {c--;do{xx=rand()%(A-2)+2;yy=rand()%(B-2)+2;}while(Game_map[xx][yy]!=0);}
          }  
    xy+=2;    
    }
    k*=num;
    return k;
}
/*void tMap::GenB(int b=3,int num = 2,double freq=0.1)
{
    int k=int(bk*freq/num),xy=0,k2;
    int *mas;
    mas= new int [2*k];
    for(int c=0;c<=2*k;c+=2) {while(Game_map[c][c+1]==(b-1))mas[c]=rand()%(i-2)+1;mas[c+1]=rand()%(j-2)+1;}
    while(xy<=2*k)
    {
     int xx=mas[xy],yy=mas[xy+1];
     Game_map[xx][yy]=b;
     k2 = rand()%100;
          for(int c=0;c<num;c++)
          {
                if(Game_map[xx][yy]==10) break;
                if (k2<25 && OK(Game_map,xx+1,yy,b)==true)
                 xx+=1;
                else 
                    if (k2>=25 && k2<50&& OK(Game_map,xx-1,yy,b)==true)
                     xx-=1;
                else
                    if (k2>=50 && k2<75&& OK(Game_map,xx,yy+1,b)==true)
                     yy+=1;
                else
                    if(OK(Game_map,xx,yy-1,b)==true) 
                     yy-=1;
                else
            {c--;xx+=rand()%2-1;yy+=rand()%2-1;}
          }  
    xy+=2;    
    }
    
}*/
char tMap::out1(int d=1,int c=1)
{
    char o;
    if (Game_map[c][d] == mm)
    {
     
     o=static_cast<char>(131);
    }
    if (Game_map[c][d] == 10)
    {
     
     o=static_cast<char>(176);
    }
    if (Game_map[c][d] == 0)
    { 
      o=' ';
    }
    if (Game_map[c][d] == 5)
    { 
      o=' ';
    }
    if (Game_map[c][d] == rr)
    {
      o=static_cast<char>(130);
    }
    if (Game_map[c][d] == 3)
    {
      o=static_cast<char>(140);
    }
   return o;
}

void tMap::out()
{
    for (int c=0;c<i;c++){
      for (int d=0;d<j;d++){
      if (Game_map[c][d] == mm)
    {
     cout << static_cast<char>(131);
    }
    if (Game_map[c][d] == 10)
    {
     cout << static_cast<char>(176);
    }
    if (Game_map[c][d] == 0)
    {
      cout << ' ';
    }
    if (Game_map[c][d] == rr)
    {
      cout << static_cast<char>(130);
    }
    if (Game_map[c][d] == 3)
    {
      cout << static_cast<char>(140);
    }
    if (Game_map[c][d] == 5)
    { 
      cout <<'+';
    }
   }
   cout << endl;
  }
}

tMap m;

// -----------------
 void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle( STD_OUTPUT_HANDLE );
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo( consoleHandle, &info );
}
bool OK(int,int,int);
class tPlayer
{   public:
    bool warrior;
    int x, y,live;
    long int time, firstTime , pressButtonTime;
    SYSTEMTIME t1, t2;
    double speed;
    char p;
    tPlayer(int, int,int, double, char,bool);
    void info();
    void gotoxy();
    bool OK(int, int);

void out(int=0);
void start(int, int);
long int getTime();
};
tPlayer:: tPlayer(int xx=5, int yy=5,int li=9, double s=1.0,char pp='p',bool k=false)
{
    m.set();
    m.out();
    //m.Game_map[xx][yy]=0;
    live=li;
    x=xx;
    y=yy;
    speed=s;
    p=pp;
    warrior = k;
    out(1);
    info();
    time = 0;
    GetLocalTime(&t1);
    firstTime=(t1.wHour*3600+t1.wMinute*60+t1.wSecond)* 1000+ t1.wMilliseconds;
    pressButtonTime= firstTime;
}
void tPlayer::info()
{
    int x1=x,y1=y;
    x=50;y=10;
    gotoxy();
    cout<<"Lives="<<live;
    x=x1; y=y1;
}
void tPlayer:: gotoxy()
{
    COORD scrn;    
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = x; scrn.Y = y;
  SetConsoleCursorPosition(hOuput,scrn);
}

bool tPlayer::OK(int yy, int xx)
{
    if (m.Game_map[xx][yy]>4 || m.Game_map[xx][yy]==0)
    {
        if (m.Game_map[xx][yy]==0||m.Game_map[xx][yy]==5) return true;      // настроить на монстров
        else return false;
    }
    else return false;
}
void tPlayer::out(int a){
gotoxy();
a==0 ? cout<<m.out1(x,y): cout<<p; 
}

void tPlayer::start(int a, int b)
{
    getTime();
    if (time - pressButtonTime > (int)(100/speed))
    {
        if(m.Game_map[b][a]==5){p='w'; warrior=true;}
        if (OK(a, b )){ out();
         x=a;
        y=b;
        GetLocalTime(&t2);
        out(1);
        pressButtonTime=(t2.wHour *3600+ t2.wMinute* 60 + t2.wSecond)* 1000+ t2.wMilliseconds;
    }
}
}


long int tPlayer:: getTime()
{
    GetLocalTime(&t2);
    time=(t2.wHour* 3600+t2.wMinute* 60+t2.wSecond)*1000+ t2.wMilliseconds;
    return time;
}
tPlayer g;
//------------------------------------
class monstr
{ 
    void gotoxy(); 
    public:
    // tMap m0;
    int **map;
    int map2[A][B];
    int x,y,xx,yy,abillity,len,vision;
    bool live;
    double speed;
    long int time, firstTime,pressButtonTime;
    SYSTEMTIME t1, t2;
    char type,p;
    monstr(int = 1, int = 1, char = '0', double = 2.0, int = 0,bool=1);
    void set_monstr(int,int,char,double,int,bool);
    bool OK(int,int,int,bool);
    long int getTime();
    void start();
    bool alg(int,int,int,int,int);
    void out(int = 0);
    };

//---------------------
class listMonstr:public monstr
{
    public:
        monstr Goblin[N];
        int count;
        listMonstr()
        {
        count = N;
        m.Game_map[3][3]=0;
        for(int i=0;i<count;i++){ 
         Goblin[i].x = 3;
         Goblin[i].y = 3;
         Goblin[i].speed = 5.5+(double)(rand()%5);
         Goblin[i].type = G;
         Goblin[i].abillity =2;
         Goblin[i].live =1;
         Goblin[i].out(1);}
         }
        void monstrStart(){
            if (g.live<1) outL();
            if (count==0) outW();
            for (int i = 0; i < count; i++)
            if(Goblin[i].live)
     Goblin[i].start();
     else
     delMonstr(Goblin[i].x,Goblin[i].y);
     }
         bool outW(){
                if(count<1)
                {
                    //system("cls"); 
                    g.x=2;g.y=50;
                    g.gotoxy();
                    cout<<"You Are Winner"; 
                    getch(); 
                    Sleep(3000);
                    return true;
                    }
                 else; 
                 return false;
                 }
                 
        bool outL() {
     if(g.live<1){
            g.x=2;g.y=50;
                    g.gotoxy();
                    cout<<"You Are Losser!"; 
                    getch(); 
                    Sleep(3000);
                    return true;
                    }
                 else; 
                 return false;
                 }
            void delMonstr(int a,int b)
            {
                for(int i=0;i<count;i++)
                {
                    if(Goblin[i].x==a && Goblin[i].y==b)
                    {
                       while(i<count-1)
                       {
                            Goblin[i]=Goblin[i+1];
                            i++;
                       }
                       
                       
                    }
                }
                count--;
            }
};
listMonstr lm;
//---------------------------------

void monstr::gotoxy()
{ COORD scrn;    
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = x; scrn.Y = y;
  SetConsoleCursorPosition(hOuput,scrn); }
    
monstr::monstr(int a, int b, char c, double d, int t,bool n)
{ 
    set_monstr(a,b,c,d,t,n);
    vision=5;
    p=m.out1(x,y);
    time = 0;
    for (int c = 0;c<A;c++)
       for (int d=0;d<B;d++)
       if(m.Game_map[c][d]<=abillity)  map2[c][d]=BLANK;else map2[c][d]=WALL;
    map= new int *[A];
    for (int c = 0;c<A;c++)
    { map[c]=new int [B];
      for (int d=0;d<B;d++)
         map[c][d]=map2[c][d];
        }  
	GetLocalTime(&t1);
	firstTime = (t1.wHour*3600+t1.wMinute*60+t1.wSecond)*1000+t1.wMilliseconds;
	pressButtonTime = firstTime;
}

void monstr::set_monstr(int a, int b, char c, double d, int t,bool n)
{ x = a; y = b; 
  abillity = t;
  speed = d;
  type = c; 
  live = n;}

long int monstr::getTime()
{
	GetLocalTime(&t2);
	time = (t2.wHour*3600+t2.wMinute*60+t2.wSecond)*1000+t2.wMilliseconds-firstTime;
	return time;
}

void monstr::start()
{ 
  int k1;
  xx = x,yy = y;
  getTime();
  if((x==g.x)&(y==g.y)&(g.p=='w')) live=0;
  if(live==false) pressButtonTime=0;
  if (time+firstTime-pressButtonTime > (int)(1000/speed)) {
  k1 = rand()%100;
  p=m.out1(x,y);
     if(alg(x,y,g.x,g.y,vision)==false){
    
  if (k1<25)
    xx+=1; else if (k1>=25 && k1<50) xx-=1;
    else if (k1>=50 && k1<75)yy+=1; else yy-=1;}
    pressButtonTime = (t2.wHour*3600+t2.wMinute*60+t2.wSecond)*1000+t2.wMilliseconds;
  if (OK(xx,yy,abillity,live)){
 out();
 x = xx; y = yy;
  out(1);
  }    
}
}
bool monstr::alg(int ax, int ay, int bx, int by, int vis)     // волновой алгоритм нужен для того, чтобы монстр преследовал игрока
{
    int px[A*B];
    int py[A*B];
    int dx[4] = {1, 0, -1, 0};   // смещения, соответствующие соседям ячейки
    int dy[4] = {0, 1, 0, -1};   // справа, снизу, слева и сверху
    int d, x0, y0, k;
  bool stop;
  
for (int c = 0;c<A;c++)
      for (int d=0;d<B;d++)
         map[c][d]=map2[c][d];

  if (map[ay][ax] == WALL || map[by][bx] == WALL) return false;  // ячейка (ax, ay) или (bx, by) - стена

  // распространение волны
  d = 0;
  map[ay][ax] = 0;            // стартовая ячейка помечена 0
  do {
    stop = true;               // предполагаем, что все свободные клетки уже помечены
    for ( y0 = 0; y0 < A; ++y0 )
      for ( x0 = 0; x0 < B; ++x0 )
        if ( map[y0][x0] == d )                         // ячейка (x, y) помечена числом d
        {
          for ( k = 0; k < 4; ++k )                    // проходим по всем непомеченным соседям
          {
             int iy=y0 + dy[k], ix = x0 + dx[k];
             if ( iy >= 0 && iy < A && ix >= 0 && ix < B &&
                  map[iy][ix] == BLANK )
             {
                stop = false;              // найдены непомеченные клетки
                map[iy][ix] = d + 1;      // распространяем волну
             }
          }
        }
    d++;
  } while ( !stop && map[by][bx] == BLANK );

  if (map[by][bx] == BLANK) return false;  // путь не найден

  // восстановление пути
  len = map[by][bx];            // длина кратчайшего пути из (ax, ay) в (bx, by)
  x0 = bx;
  y0 = by;
  d = len;
  while ( d > 0 )
  {
    px[d] = x0;
    py[d] = y0;                   // записываем ячейку (x, y) в путь
    d--;
    for (k = 0; k < 4; ++k)
    {
       int iy=y0 + dy[k], ix = x0 + dx[k];
       if ( iy >= 0 && iy < A && ix >= 0 && ix < B &&
            map[iy][ix] == d)
      {
          x0 = x0 + dx[k];
          y0 = y0 + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
          break;
      }
    }
  }
  px[0] = ax;
  py[0] = ay;       // теперь px[0..len] и py[0..len] - координаты ячеек пути
    
   if(len > vis) return false;
   else{          
    xx=px[1]; yy=py[1];
    if((xx==g.x)&(yy==g.y)&(g.p=='p')) {g.live--;g.info();xx=px[0]; yy=py[0];}
  //  if((xx==g.x)&(yy==g.y)&(g.p=='w')) {xx=px[0]; yy=py[0];out();lm.delMonstr(x,y);}
}
        return true;
}
void monstr::out(int a)
{ gotoxy();
  a == 0 ? cout<< p : cout<<type; 
  }


bool monstr::OK(int b, int a, int c,bool d)
{   int v=0;
    if(d==false) return false;
      for (int i=0;i<lm.count;i++)
    {
        if((lm.Goblin[i].x==b)&(lm.Goblin[i].y==a)) v++;       
    }         
    if (m.Game_map[a][b]>c) v++; 
    if (v!=0) 
    return false; 
    else
    return true;
 }

int main()
{ 
  hidecursor();
  char c=getch();
  while (c!=27)
  {
  if(lm.outL()) return 0;
  if(lm.count>0)lm.monstrStart();
  if(GetAsyncKeyState(VK_LEFT)){g.start(g.x-1,g.y);}
  if(GetAsyncKeyState(VK_UP)) {g.start(g.x,g.y-1);}
  if(GetAsyncKeyState(VK_RIGHT)){g.start(g.x+1,g.y);}
  if(GetAsyncKeyState(VK_DOWN)){g.start(g.x,g.y+1);}
  if(lm.outW()) c=27;
  }
  return 0;
 }
