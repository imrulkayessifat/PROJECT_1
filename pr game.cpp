#include <dos.h>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>;

using namespace std;
void help();
void game();
void game1();
void game2();
void check();
void check_game();
void check_game1();
void dead();
void level();
void high();
void skill();
void border_End();
//void game1();
int page=0;
int snake_x[500],snake_y[500],snake_size = 5,score,highscore,spd =100,l;
bool checkdied = false,BONUS = false;


main()
{

    int gdirect = DETECT,gmode;  /* request autodetection */
    initgraph(&gdirect,&gmode,""); /* initialize graphics and local variables */

    int cursor_y = 130;
    char ch;


    int maxx=getmaxx();
    int maxy=getmaxy();


    int page=0;

    while(1)
    {




        setcolor(GREEN);

        for(int e=25,w=90,q=165,r=400;e>=20,w<=95,q>=160,r<=405;e--,w++,q--,r++)
        {

            rectangle(q,e,r,w);
        }
        settextstyle(8,0,6);
        setcolor(RED);

        outtextxy(180,30," Snake ");

        setcolor(YELLOW);
        settextstyle(3,0,3); /*this part prints menu again but inside while loop,because other functions will return here*/
        rectangle(160,125,390,163);
        outtextxy(200,130,"New Game");
        rectangle(160,167,390,201);
        outtextxy(200,170,"Help");
        rectangle(160,205,390,247);
        outtextxy(200,210,"Select Level");
        rectangle(160,243,390,287);
        outtextxy(200,250,"Highscore");
        rectangle(160,283,390,327);
        outtextxy(200,290,"Exit");
        setcolor(RED);
        outtextxy(170,cursor_y,"-->");
        setcolor(WHITE);
        settextstyle(3,0,3);
        outtextxy(200,340,"<<<Please Select Level First>>>");

        if(1){
        ch = getch();
        //setcolor(BLACK);
        //outtextxy(160,cursor_y,">");
        cleardevice();
        if(ch == 13) {
            if(cursor_y==290) exit(0);
            else if(cursor_y==170) help();
            else if(cursor_y==130) skill();
            else if(cursor_y==210) level();
            else if(cursor_y==250) high();
        }
        }
        //setcolor(WHITE);
        if(ch==80) {cursor_y+=40;
        if(cursor_y > 290) {cursor_y=130;}
        }
        if(ch==72) {cursor_y-=40;
        if(cursor_y < 130) {cursor_y=290;}
        }
        //outtextxy(160,cursor_y,">");
        //page=1-page;
    }

    return 0;
}
void help()
{
    setcolor(WHITE);
    outtextxy(100,300,"Move the snake using the Arrow keys.");
    outtextxy(100,330,"Press 'Alt' to Pause");
    char ch = getch();
    clearviewport();
    return;
}
void game()
{
    snake_size=5;
    score=0;

    int maxx = getmaxx();
    int maxy = getmaxy();

    setcolor(GREEN);
//    settextstyle();
    int k;
    clearviewport();
    freopen("GameData3.dat","r",stdin);
    cin >> highscore;

    cleardevice();
    char ch;
    string key = "right";

    int x = 130,y = 130;

    ram:
    int food_x = rand()%maxx,food_y = rand()%maxy;
    int temp;
    temp = food_x%13;
    food_x-=temp;
    temp = food_y%13;
    food_y-=temp;
    ///if(food_x<15 || food_y<50)
    if(food_x<15||food_x>=maxx-30 || food_y<50||food_y>=maxy-15)/*||((food_x>=130&&food_x<=140)||
       (food_y>=100&&food_y<=300))||(food_x>=500&&food_x<=510)||(food_y>=100&&food_y<=300))*/
    goto ram;
    //goto ram;

    int i = 0;
    int bonus = 500;
    int page=0;
    while(true)
        {

            setcolor(3);
            setfillstyle(SOLID_FILL,3);
            rectangle(0,0,10,maxy);
            floodfill(5,10,3);

            setcolor(3);
            setfillstyle(SOLID_FILL,3);
            rectangle(0,60,maxx,50);
            floodfill(50,55,3);

            setcolor(3);
            setfillstyle(SOLID_FILL,3);
            rectangle(0,460,maxx,470);
            floodfill(50,465,3);

            setcolor(3);
            setfillstyle(SOLID_FILL,3);
            rectangle(maxx-10,0,maxx,maxy);
            floodfill(maxx-5,100,3);


         //clearviewport();
         //cleardevice();
        if(score >0 && score%5==4) BONUS = true;
        else{ //bonus = 500;
        BONUS = false;
        }
        if(BONUS==false || bonus == 0){
        setcolor(BLACK);
        outtextxy(250,0,"Hurry!! 888");
        setcolor(4);
        setfillstyle(SOLID_FILL,4);
        circle(food_x,food_y,6); //x position,y position,size
        floodfill(food_x,food_y,4);

        }
        else
        {
        setcolor(10);
        setfillstyle(SOLID_FILL,10);
        circle(food_x,food_y,9);
        floodfill(food_x,food_y,10);

        char spp[1000];
        setcolor(RED);
        sprintf(spp,"Hurry!! %d",bonus);
        outtextxy(250,0,"Hurry!! 888");
        setcolor(MAGENTA);
        outtextxy(250,0,spp);
        // clears
        }
        //maxx = getmaxx();
        //maxy = getmaxy()-50;

        if(kbhit())
        {
            ch = getch(); if(ch == 0) ch = getch();
            if(ch == 72 && key != "down" ) key = "up";
            if(ch == 80 && key != "up") key = "down";
            if(ch == 75 && key != "right") key = "left";
            if(ch == 77 && key != "left") key = "right";
            if(ch == 27) {
            cleardevice();
            return;
        }

        }

        if(i < 5)
        {
            snake_x[i] = x-240;
            snake_y[i] = y-285;
            i++;
        }
        else {
        for(int _size = snake_size-2;_size >= 0;_size--) {
        snake_x[_size+1] = snake_x[_size];
        snake_y[_size+1] = snake_y[_size];
        }
        snake_x[0] = x;
        snake_y[0] = y;

        setcolor(6);
        circle(snake_x[0],snake_y[0],9);
        setfillstyle(SOLID_FILL,6);
        floodfill(snake_x[0],snake_y[0],6);

        setcolor(1);
        for(int _size = 1; _size < snake_size;_size++)
        {
        circle(snake_x[_size],snake_y[_size],5);
        setfillstyle(SOLID_FILL,1);
        floodfill(snake_x[_size],snake_y[_size],1);
        }

        char ara[100];
        sprintf(ara,"Score: %d",score);
        setcolor(9);
        outtextxy(20,0,ara);
        sprintf(ara,"Bestscore: %d",highscore);
        setcolor(9);
        outtextxy(450,0,ara);


        delay(spd);

        }
        if(x == food_x && y== food_y)
        {
        Beep(5000,spd);
        snake_size++;score++;
            /* Snake eats food*/
        if(score%5==0 && score>0)score+=bonus;

        ran:
        food_x = rand()%maxx,food_y = rand()%maxy;
        temp = food_x%13;
        food_x-=temp;
        temp = food_y%13;
        food_y-=temp;
        if(food_x<20 || food_y<50)
        goto ran;


        if(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5)
        {
            while(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5) {
            food_x = rand()%maxx,food_y = rand()%maxy;
            temp = food_x%13;
            food_x-=temp;
            temp = food_y%13;
            food_y-=temp;
            }
        }
        }
        if(score>=100)game2();
        if(key == "right") x = x+13; if(x>maxx-12) border_End();
        if(key == "left") x = x-13; if(x<=10) border_End();
        if(key == "up") y = y-13; if(y<=60) border_End();
        if(key == "down") y = y+13; if(y>maxy-12) border_End();


        check_game();
        if(checkdied){
        dead();

        return;
        }

    if(BONUS){
    if(bonus>0)
    bonus-=10;
      }
      cleardevice();


    }

}
void check()
{
    int k;
    int maxx=getmaxx();
    int maxy=getmaxy();
    freopen("GameData.dat","w",stdout);
    if(highscore < score)
    cout << score << endl;
    else cout << highscore << endl;

    for(int i = 1;i < snake_size;i++)
    {
        if(snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]||
           (snake_x[0]>=130&&snake_x[0]<=144&&snake_y[0]>=100&&snake_y[0]<=300)||
           (snake_x[0]>=500&&snake_x[0]<=510&&snake_y[0]>=100&&snake_y[0]<=300))
        {
            delay(50);

            for(int i = 0;i < snake_size;i++)
            {
                setcolor(RED);
                circle(snake_x[i],snake_y[i],5);
                setfillstyle(SOLID_FILL,RED);
                floodfill(snake_x[i],snake_y[i],RED);
            }

            cleardevice();

            setcolor(4);
            settextstyle(3,0,4);
            outtextxy(200,200,"    GAME OVER ");
            outtextxy(200,250," PLEASE ENTER ");
            while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
            cleardevice();
            checkdied = true;
            return;
            }
            }
            }
        }

    }
}
void dead()
{
    checkdied = false;
    snake_size = 5;
    score = 0;
//    clearviewport();
}
void level()
{
    char ch;
    char ara[100];
    while(true){

    int i = abs(spd/10.-10);
    sprintf(ara,"SELECT LEVEL : %d",i);
    setcolor(WHITE);
    outtextxy(180,350,ara);

    if(kbhit())
    {
        ch = getch();
        if(ch == 80) {
        spd-=10;
        if(spd < 0) spd = 100;
        }
        else if(ch == 72) {
            spd+=10;
        if(spd > 100) spd = 0;
        }
        else if(ch == 13)
            break;
    sprintf(ara,"SELECT LEVEL : %d",i);
    setcolor(BLACK);
    outtextxy(180,350,ara);
    }
    }

    clearviewport();
}

void high()
{
        freopen("GameData.dat","r",stdin);
        cin >> highscore;
        char ara[100];
        sprintf(ara,"Highscore: %d",highscore);
        setcolor(WHITE);
        outtextxy(200,350,ara);
        char ch = getch();
        clearviewport();
}


void border_End()

{

    int j,i;
   setcolor(WHITE);
   for(i=0;i<5;i++){
   delay(500);
    cleardevice();
    delay(500);
    //cleardevice();
    //clearviewport();
   for(j=0;j<=snake_size;j++){
		   setfillstyle(SOLID_FILL,RED);
		   circle(snake_x[j],snake_y[j],5);
		   floodfill(snake_x[j],snake_y[j],WHITE);
		  }

		 }
    cleardevice();
    setcolor(RED);
    settextstyle(3,0,4);
    outtextxy(200,200,"    GAME OVER ");
    outtextxy(200,250," PLEASE ENTER ");
    while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
                    cleardevice();
            checkdied = true;
            return;
            }
            }
            }
            //cleardevice();
            //clearviewport();
    }
    void skill()
    {
        int cursor_y=130;
        char ch;
        while(1)
        {
            setcolor(BLUE);
        settextstyle(3,0,3);/*this part prints menu again but inside while loop,because other functions will return here*/
        outtextxy(160,70,"SELECT YOUR SKILL");

        rectangle(160,125,390,163);
        outtextxy(200,130,"EASY");
        rectangle(160,167,390,201);
        outtextxy(200,170,"MEDIUM");
        rectangle(160,205,390,247);
        outtextxy(200,210,"HARD");
        outtextxy(170,cursor_y,"-->");


        if(1){
        ch = getch();
        //setcolor(BLACK);
        //outtextxy(160,cursor_y,">");
        cleardevice();
        if(ch == 13) {
            if(cursor_y==130) game1();
            else if(cursor_y==170) game();
            else if(cursor_y==210) game2();
        }
        }
        //setcolor(WHITE);
        if(ch==80) {cursor_y+=40;
        if(cursor_y > 210) {cursor_y=130;}
        }
        if(ch==72) {cursor_y-=40;
        if(cursor_y < 130) {cursor_y=210;}
        }


        }

    }



    void game1()
{
    score=0;
    clearviewport();
    freopen("GameData2.dat","r",stdin);
    cin >> highscore;

    cleardevice();
    char ch;
    string key = "right";
    int maxx = getmaxx();
    int maxy = getmaxy()-50;
    int x = 13,y = 13;

    int food_x = rand()%maxx,food_y = rand()%maxy;
    int temp;
    temp = food_x%13;
    food_x-=temp;
    temp = food_y%13;
    food_y-=temp;
    int i = 0;
    int bonus = 500;
    while(true)
        {
         clearviewport();
        if(score >0 && score%5==4) BONUS = true;
        else{ bonus = 500;
        BONUS = false;
        }
        if(!BONUS || bonus == 0){
                //cleardevice();
        setcolor(BLACK);
        outtextxy(250,10,"Hurry!! 888");
        setcolor(2);
        setfillstyle(SOLID_FILL,2);
        circle(food_x,food_y,6); //x position,y position,size
        floodfill(food_x,food_y,2);

        }
        else
        {
        setcolor(9);
        setfillstyle(SOLID_FILL,9);
        circle(food_x,food_y,8);
        floodfill(food_x,food_y,9);

        char spp[1000];
        setcolor(BLACK);
        sprintf(spp,"Hurry!! %d",bonus);
        outtextxy(250,10,"Hurry!! 888");
        setcolor(MAGENTA);
        outtextxy(250,10,spp);
        // clears
        }
        maxx = getmaxx();
        maxy = getmaxy()-50;
        setcolor(WHITE);
        line(0,maxy+8,maxx,maxy+8);
        if(kbhit())
        {
            ch = getch(); if(ch == 0) ch = getch();
            if(ch == 72 && key != "down" ) key = "up";
            if(ch == 80 && key != "up") key = "down";
            if(ch == 75 && key != "right") key = "left";
            if(ch == 77 && key != "left") key = "right";
            if(ch == 27) {
            cleardevice();
            return;
        }

        }

        if(i < 5)
        {
            snake_x[i] = x-240;
            snake_y[i] = y-285;
            i++;
        }
        else {
        for(int _size = snake_size-2;_size >= 0;_size--) {
        snake_x[_size+1] = snake_x[_size];
        snake_y[_size+1] = snake_y[_size];
        }
        snake_x[0] = x;
        snake_y[0] = y;

        setcolor(11);
        circle(snake_x[0],snake_y[0],8);
        setfillstyle(SOLID_FILL,11);
        floodfill(snake_x[0],snake_y[0],11);

        setcolor(13);
        for(int _size = 1; _size < snake_size;_size++)
        {
        circle(snake_x[_size],snake_y[_size],5);
        setfillstyle(SOLID_FILL,13);
        floodfill(snake_x[_size],snake_y[_size],13);
        }

        char ara[100];
        sprintf(ara,"Score: %d",score);
        setcolor(WHITE);
        outtextxy(00,maxy+10,ara);
        sprintf(ara,"Bestscore: %d",highscore);
        setcolor(WHITE);
        outtextxy(450,maxy+10,ara);

        delay(spd);

        }
        if(x == food_x && y== food_y)
        {
             Beep(5000,spd);
        snake_size++;score++;
            /* Snake eats food*/
        if(score%5==0 && score>0)score+=bonus;

        food_x = rand()%maxx,food_y = rand()%maxy;
        temp = food_x%13;
        food_x-=temp;
        temp = food_y%13;
        food_y-=temp;

        if(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5)
        {
            while(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5) {
            food_x = rand()%maxx,food_y = rand()%maxy;
            temp = food_x%13;
            food_x-=temp;
            temp = food_y%13;
            food_y-=temp;
            }
        }
        }
        if(score>=10)game();
        if(key == "right") x = x+13; if(x > maxx) x =0;
        if(key == "left") x = x-13; if(x < 0) x = maxx-(maxx%13);
        if(key == "up") y = y-13; if(y > maxy) y = 0;
        if(key == "down") y = y+13; if(y < 0) y = maxy-(maxy%13);
        check_game1();
        if(checkdied){
        dead();
        return;
        }

    if(BONUS){
    if(bonus>0)
    bonus-=10;
      }
        setcolor(BLACK);
        circle(snake_x[0],snake_y[0],8);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[0],snake_y[0],BLACK);

        for(int _size = 1; _size < snake_size;_size++)
        {
        circle(snake_x[_size],snake_y[_size],5);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[_size],snake_y[_size],BLACK);
        }

    }
}
void game2()
{
    snake_size=5;
    score=0;

    int maxx = getmaxx();
    int maxy = getmaxy();

    setcolor(GREEN);
//    settextstyle();
    int k;
    clearviewport();
    freopen("GameData1.dat","r",stdin);
    cin >> highscore;

    cleardevice();
    char ch;
    string key = "right";

    int x = 130,y = 130;

    ram:
    int food_x = rand()%maxx,food_y = rand()%maxy;
    int temp;
    temp = food_x%13;
    food_x-=temp;
    temp = food_y%13;
    food_y-=temp;
    if(food_x<15||food_x>=maxx-40 || food_y<50||food_y>=maxy-15||((food_x>=130&&food_x<=140)||
       (food_y>=100&&food_y<=300))||(food_x>=500&&food_x<=510)||(food_y>=100&&food_y<=300))
    goto ram;

    int i = 0;
    int bonus = 500;
    int page=0;
    while(true)
        {

            setcolor(3);
            setfillstyle(SOLID_FILL,3);
            rectangle(0,0,10,maxy);
            floodfill(5,10,3);

            setcolor(3);
            setfillstyle(SOLID_FILL,3);
            rectangle(0,60,maxx,50);
            floodfill(50,55,3);

            setcolor(3);
            setfillstyle(SOLID_FILL,3);
            rectangle(0,460,maxx,470);
            floodfill(50,465,3);

            setcolor(3);
            setfillstyle(SOLID_FILL,3);
            rectangle(maxx-10,0,maxx,maxy);
            floodfill(maxx-5,100,3);

            rectangle(130,100,140,300);
            rectangle(500,100,510,300);


         //clearviewport();
         //cleardevice();
        if(score >0 && score%5==4) BONUS = true;
        else{ //bonus = 500;
        BONUS = false;
        }
        if(BONUS==false || bonus == 0){
        setcolor(BLACK);
        outtextxy(250,0,"Hurry!! 888");
        setcolor(11);
        setfillstyle(SOLID_FILL,11);
        circle(food_x,food_y,6); //x position,y position,size
        floodfill(food_x,food_y,11);

        }
        else
        {
        setcolor(4);
        setfillstyle(SOLID_FILL,4);
        circle(food_x,food_y,8);
        floodfill(food_x,food_y,4);

        char spp[1000];
        setcolor(RED);
        sprintf(spp,"Hurry!! %d",bonus);
        outtextxy(250,0,"Hurry!! 888");
        setcolor(MAGENTA);
        outtextxy(250,0,spp);
        // clears
        }
        //maxx = getmaxx();
        //maxy = getmaxy()-50;

        if(kbhit())
        {
            ch = getch(); if(ch == 0) ch = getch();
            if(ch == 72 && key != "down" ) key = "up";
            if(ch == 80 && key != "up") key = "down";
            if(ch == 75 && key != "right") key = "left";
            if(ch == 77 && key != "left") key = "right";
            if(ch == 27) {
            cleardevice();
            return;
        }

        }

        if(i < 5)
        {
            snake_x[i] = x-240;
            snake_y[i] = y-285;
            i++;
        }
        else {
        for(int _size = snake_size-2;_size >= 0;_size--) {
        snake_x[_size+1] = snake_x[_size];
        snake_y[_size+1] = snake_y[_size];
        }
        snake_x[0] = x;
        snake_y[0] = y;

        setcolor(RED);
        circle(snake_x[0],snake_y[0],8);
        setfillstyle(SOLID_FILL,RED);
        floodfill(snake_x[0],snake_y[0],RED);

        setcolor(YELLOW);
        for(int _size = 1; _size < snake_size;_size++)
        {
        circle(snake_x[_size],snake_y[_size],5);
        setfillstyle(SOLID_FILL,YELLOW);
        floodfill(snake_x[_size],snake_y[_size],YELLOW);
        }

        char ara[100];
        sprintf(ara,"Score: %d",score);
        setcolor(9);
        outtextxy(20,0,ara);
        sprintf(ara,"Bestscore: %d",highscore);
        setcolor(9);
        outtextxy(450,0,ara);


        delay(spd);

        }
        if(x == food_x && y== food_y)
        {
        Beep(5000,spd);
        snake_size++;score++;
            /* Snake eats food*/
        if(score%5==0 && score>0)score+=bonus;

        ran:
        food_x = rand()%maxx,food_y = rand()%maxy;
        temp = food_x%13;
        food_x-=temp;
        temp = food_y%13;
        food_y-=temp;
        if(food_x<20 || food_y<50)
        goto ran;


        if(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5)
        {
            while(food_x < 5 || food_x > maxx - 5 || food_y < 5 || food_y > maxy - 5) {
            food_x = rand()%maxx,food_y = rand()%maxy;
            temp = food_x%13;
            food_x-=temp;
            temp = food_y%13;
            food_y-=temp;
            }
        }
        }
        if(score>=100)
        {
            cleardevice();
            setcolor(RED);
            outtextxy(300,200," YOU WIN ");
            //clearviewport();
            while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
                    cleardevice();
            checkdied = true;
            return;
            }
            }
            }
        }
        if(key == "right") x = x+13; if(x>maxx-15) border_End();
        if(key == "left") x = x-13; if(x<=12) border_End();
        if(key == "up") y = y-13; if(y<=64) border_End();
        if(key == "down") y = y+13; if(y>maxy-12) border_End();


        check();
        if(checkdied){
        dead();
        //page=1-page;
        return;
        }

    if(BONUS){
    if(bonus>0)
    bonus-=10;
      }
     /// cleardevice();
        setcolor(BLACK);
        circle(snake_x[0],snake_y[0],8);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[0],snake_y[0],BLACK);

        for(int _size = 1; _size < snake_size;_size++)
        {
        circle(snake_x[_size],snake_y[_size],5);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[_size],snake_y[_size],BLACK);
        }


    }


}
void check_game()
{

    int k;
    int maxx=getmaxx();
    int maxy=getmaxy();
    freopen("GameData.dat","w",stdout);
    if(highscore < score)
    cout << score << endl;
    else cout << highscore << endl;

    for(int i = 1;i < snake_size;i++)
    {
        if(snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])//||(snake_x[0]>=100&&snake_x[0]<=110&&snake_y[0]>=100&&snake_y[0]<=300))
        {
            delay(50);

            for(int i = 0;i < snake_size;i++)
            {
                setcolor(RED);
                circle(snake_x[i],snake_y[i],5);
                setfillstyle(SOLID_FILL,RED);
                floodfill(snake_x[i],snake_y[i],RED);
            }

            cleardevice();

            setcolor(4);
            settextstyle(3,0,4);
            outtextxy(200,200,"    GAME OVER ");
            outtextxy(200,250," PLEASE ENTER ");
            while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
                    cleardevice();
            checkdied = true;
            return;
            }
            }
            }
        }

    }
}

void check_game1()
{
    freopen("GameData.dat","w",stdout);
    if(highscore < score)
    cout << score << endl;
    else cout << highscore << endl;

    for(int i = 1;i < snake_size;i++)
    {
        if(snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
        {
            delay(50);
            setcolor(WHITE);
            for(int i = 0;i < snake_size;i++)
            {
                circle(snake_x[i],snake_y[i],5);
                setfillstyle(SOLID_FILL,RED);
                floodfill(snake_x[i],snake_y[i],WHITE);
            }
            cleardevice();

            setcolor(4);
            settextstyle(3,0,4);
            outtextxy(200,200,"    GAME OVER ");
            outtextxy(200,250," PLEASE ENTER ");
            //cleardevice();

            while(1){
            if(kbhit()){
            char ch = getch();
            if(ch == 13){
                    cleardevice();
            checkdied = true;
            return;
            }
            }
            }
        }
    }
}



