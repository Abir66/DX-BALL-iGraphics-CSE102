#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<mmsystem.h>
# include "iGraphics.h"
#include "dxHeader.h"

//int windowWidth = 1366;
//int windowHeight = 786;
int  windowWidth = GetSystemMetrics(SM_CXSCREEN);
int windowHeight = GetSystemMetrics(SM_CYSCREEN);

double var(double d)
{

    return d*(windowWidth*1.0/1366);

}
int scene = 0;
double scene0Timer = 0;
double scene1Timer = 0;
double scene2Timer = 0;
double scene12Timer = 0;
int overButton = 0;
int settingsButton = 0;

int musicOn = 1;

char menuButtons[8][30] = {"assets\\menu\\exit.bmp","assets\\menu\\credits.bmp",
                           "assets\\menu\\inst.bmp","assets\\menu\\high.bmp","assets\\menu\\settings.bmp",
                           "assets\\menu\\create.bmp","assets\\menu\\new.bmp","assets\\menu\\resume.bmp"
                          };
char menulogo[40] = "assets\\menu\\dxball2020.bmp";
char levelFile[40] = "assets\\ALL_LEVELS_bi";
char OriginalLevelFile[40] = "assets\\ORIGINAL_ALL_LEVELS_bi";

char backButtonStr[40] = "assets\\images\\back.bmp";
char nextButtonStr[40] = "assets\\images\\next.bmp";
int backButtonSelected = 0;
int nextButtonSelected = 0;

int menuButtonSelected = 6;
double menuRedX = windowWidth - 450-40;
int thereIsResume = 0;
int gameMode = 1;
int levelIndex = 1;

char scene13[5][40] = {"assets\\levelmaker\\single.bmp","assets\\levelmaker\\edit.bmp","assets\\levelmaker\\caution.bmp","assets\\levelmaker\\play.bmp","assets\\levelmaker\\save.bmp"};
int scene13Button = 0;
int createButton = 0;



int editIndex = 1;
int editmaxIndex = 3;
char editChar[5] = "";
int editcharIndex = 0;
int maxLevels = 20;
int editerror = 0;


double menuButtonWidth[8] = {93,185,319,290,213,305,238,186};



//form gameplay

void int_to_str(int n, char *s)
{

    int i=0,j = 0;
    char t;
    while(n>0)
    {
        s[i] = n%10 -0 + '0';
        n = n/10;
        i++;
    }
    s[i] = '\0';
    for(j = 0; j+j<i; j++)
    {
        t = s[i-j-1];
        s[i-j-1] = s[j];
        s[j] = t;
    }


    if(s[0]=='\0')
        strcpy(s,"0");
}


int randomint(int lower, int upper)
{

    return (rand() % (upper - lower + 1)) + lower;
}

double pi = acos(-1);



int boxn = 10;
int boxType[] = {1,2,3,4,5,6,7,8,9,-1};
int setboxType = 1;
int boxmap[19][16];
int eraserON = 0;
int blinkTimer = 0;
int blink = 1;

double boxWidth = var(64);
double boxHeight = var(32);
double lowerlimit = var(180);
double higherlimit = lowerlimit + boxHeight*16;
double leftlimit = var(74.7); //138.7
double rightlimit = leftlimit + boxWidth*19;


int totalboxs;
int ballReviveTime = 0;
int ballFullReviveTime = 1000;
int currentLives = 3;

//ball constants
double ballRegularR = var(10);
double ballMinR = var(5);
double ballMaxR = var(20);
double ballRegularV = var(20);
double ballMinV = var(10);
double ballMaxV = var(50);
int ballFireball = 0;
double ballVelocityTimer = 0;
int breakthrough = 0;

int score = 0;
char scoreChar[15];

int gameplayPause = 0;
int gameplayPauseTimer = 0;
int gameplayTimer = 0;
int totalSeconds = 0;
int gameSeconds = 0;
int gameMinutes = 0;
char gameTimeStr[10] = "00:00";




char perkImage[16][25] = {"","assets\\perk\\1.bmp","assets\\perk\\2.bmp","assets\\perk\\3.bmp","assets\\perk\\4.bmp","assets\\perk\\5.bmp",
                          "assets\\perk\\6.bmp","assets\\perk\\7.bmp","assets\\perk\\8.bmp","assets\\perk\\9.bmp","assets\\perk\\10.bmp",
                          "assets\\perk\\11.bmp","assets\\perk\\12.bmp","assets\\perk\\13.bmp","assets\\perk\\14.bmp","assets\\perk\\15.bmp",
                         };

char resumeDataFile[25] = "assets\\RESUME_DATA";
char resumeButtons [5][30] = {"","assets\\resume\\resume.bmp", "assets\\resume\\restart.bmp","assets\\resume\\sound.bmp","assets\\resume\\quit.bmp"};
double resumeButtonWidth[5] = {0,184,197,340,426};
double resumeButtonSelected = 0;
char LifeIcon[25] = "assets\\images\\life.bmp";
char HighscoreFile[30] = "assets\\HIGH_SCORES";
int  showLessBoxMessage = 0;

char highScorePrinter[10];

//user
typedef struct
{

    char name[20];
    int score;
    int i = 1;
} _user;
_user users[11];

//paddle
struct _paddle
{
    double x=var(500);
    double y=var(30);
    double width=var(100);
    double height = var(15);
    char shooter = 0;
    double radius = height/2;
    double len = width + radius;
    double move = var(50);
    double leftpoint = x-len;
    double rightpoint = x+len;
    double regularWidth = var(100);
    double minWidth = var(50);
    double maxWidth = var(250);
    int ballGrabber = 0;

} paddle;

//ball
typedef struct
{

    double r = var(10);
    double x = paddle.x;
    double y = paddle.y+paddle.height+r;
    double v = var(20);
    double angle = 80*pi/180;
    double vx = v*cos(angle);
    double vy = v*sin(angle);
    double dx = v*cos(angle);
    double dy = v*sin(angle);
    int live = 0;
    int launch = 0;
    double rx = 0;
    double ry = 0;
} _ball;
_ball ball;


typedef struct
{
    double x;
    double y;
    char live = 0;
} _bullets;


//shooter
int shooterPaddle = 1;
double bulletx = var(4);
double bullety = paddle.height;
double bulletv = var(75);
_bullets bulletArray[20];
double bulletTimer = 0;
double bulletMaxTime = var(7);

int dhakka = 5;
int timeBonus = 0;
int totalScore = 0;
int takeHighScore = 1;
char GameOverScore[10];
char GameOverbonus[10];
char GameOvertotal[10];

//delay
int generalDelay = 0;
int generalDelayTimer = 0;
int generalDelayLimit = 0;
int maxUsernameIdx = 20;
char currentUsername[22];
int currentUsername_idx = 0;


void doGeneralDelay(int i)
{

    generalDelay = 1;
    generalDelayTimer = 0;
    generalDelayLimit = i;

}


//box
typedef struct
{

    double x;
    double y;
    int type;

} _box;
_box boxs[19][16];
int tempBoxMap[19][16];
int tempTotalBoxs;


int totalLevel = 20;


typedef struct
{
    int totalboxs;
    int boxs_type[19][16];

} _levelMap;

_levelMap levelMap[20];


typedef struct
{

    double x;
    double y;
    int type;
    int live;
    double width = 64;
    double height = 64;
    double vy = -var(7);
    double vx = var(1.5);

} _perk;

_perk perk;



struct _resumeData
{



    int isResume = 0;
    int gameMode = 1;
    int levelIndex = 1;

    _ball ball;
    _paddle paddle;
    _perk perk;
    _box boxs[19][16];
    int totalboxs;

    //shooter
    int shooterPaddle;
    double bulletx;
    double bullety;
    double bulletv;
    _bullets bulletArray[20];
    double bulletTimer;

    //score
    int score;
    //time
    int gameplayTimer;
    char gameTimeStr[5];
    int currentLives = 3;
    int timeBonus = 0;

    int tempBoxMap[19][16];
    int tempTotalBoxs;



} resumeData;


void loadLevel(int levelIndex);

//levlemaker
void clearLevelMaker()
{
    for(int i=0; i<19; i++)
    {
        for(int j=0; j<16; j++)
        {
            boxmap[i][j] = 0;
        }
    }
}



void sort_users()
{


    int idx = 10;
    _user tempUser = users[10];

    while(idx >= 1 && users[idx-1].score< users[10].score)
        idx--;

    for(int i = 9; i>=idx; i--)
    {
        users[i+1] = users[i];
    }

    users[idx] = tempUser;
}


void readHighscores()
{

    FILE *fp;
    if((fp = fopen(HighscoreFile,"rb"))==NULL)
    {
        printf("ERROR OPENING RESUME DATA FILE");
        exit(1);
    }

    if(fread(users, sizeof(users), 1, fp) != 1)
    {
        printf("ERROR READING RESUME DATA FILE");
        exit(1);
    }
    fclose(fp);

}

void writeHighScores()
{

    FILE *fp;
    if((fp = fopen(HighscoreFile,"wb"))==NULL)
    {
        printf("ERROR OPENING RESUME DATA FILE");
        exit(1);
    }

    if(fwrite(users, sizeof(users), 1, fp) != 1)
    {
        printf("ERROR WRITING RESUME DATA FILE");
        exit(1);
    }
    fclose(fp);
}


void restoreHighscore()
{


    int i = 0;
    for(i=0; i<11; i++)
    {
        users[i].score = 0;
        strcpy(users[i].name, "UNKNOWN");
    }
}




void restoreLevelMap()
{

    FILE *fp;
    if((fp = fopen(OriginalLevelFile,"rb"))==NULL)
    {
        printf("ERROR OPENING LEVEL DATA FILE");
        exit(1);
    }

    if(fread(levelMap, sizeof(levelMap), 1, fp) != 1)
    {
        printf("ERROR READING LEVEL DATA FILE");
        exit(1);
    }
    fclose(fp);
    if(gameMode == 1){
        thereIsResume = 0;

    }

}



void readLevelMap()
{

    FILE *fp;
    if((fp = fopen(levelFile,"rb"))==NULL)
    {
        printf("ERROR OPENING LEVEL DATA FILE");
        exit(1);
    }

    if(fread(levelMap, sizeof(levelMap), 1, fp) != 1)
    {
        printf("ERROR READING LEVEL DATA FILE");
        exit(1);
    }
    fclose(fp);
}


void writeLevelMap()
{

    FILE *fp;
    if((fp = fopen(levelFile,"wb"))==NULL)
    {
        printf("ERROR OPENING LEVEL DATA FILE");
        exit(1);
    }


    if(fwrite(levelMap, sizeof(levelMap), 1, fp) != 1)
    {
        printf("ERROR writing LEVEL DATA FILE");
        exit(1);
    }
    fclose(fp);
}



void readResumeData()
{

    FILE *fp;
    if((fp = fopen(resumeDataFile,"rb"))==NULL)
    {
        printf("ERROR OPENING RESUME DATA FILE");
        exit(1);
    }

    if(fread(&resumeData, sizeof(resumeData), 1, fp) != 1)
    {
        printf("ERROR READING RESUME DATA FILE");
        exit(1);
    }
    fclose(fp);
    thereIsResume = resumeData.isResume;
}


void writeResumeData()
{

    FILE *fp;
    if((fp = fopen(resumeDataFile,"wb"))==NULL)
    {
        printf("ERROR OPENING RESUME DATA FILE");
        exit(1);
    }

    if(fwrite(&resumeData, sizeof(resumeData), 1, fp) != 1)
    {
        printf("ERROR WRITING RESUME DATA FILE");
        exit(1);
    }
    fclose(fp);
    thereIsResume = resumeData.isResume;

}

void reloadResumeData()
{

    thereIsResume = resumeData.isResume;
    gameMode = resumeData.gameMode;
    levelIndex = resumeData.levelIndex;

    ball = resumeData.ball;
    paddle = resumeData.paddle;
    perk = resumeData.perk;
    totalboxs = resumeData.totalboxs;

    for(int i = 0; i<19; i++)
    {
        for(int j = 0; j<16; j++)
        {
            boxs[i][j] = resumeData.boxs[i][j] ;
        }
    }


    shooterPaddle = resumeData.shooterPaddle;
    bulletx = resumeData.bulletx;
    bullety = resumeData.bullety ;
    bulletv = resumeData.bulletv ;

    for(int i=0; i<20; i++)
    {
        bulletArray[i] = resumeData.bulletArray[i];
    }
    bulletTimer = resumeData.bulletTimer;

    score = resumeData.score;
    gameplayTimer = resumeData.gameplayTimer;
    for(int i=0; i<5; i++)
    {
        gameTimeStr[i] = resumeData.gameTimeStr[i];
    }

    currentLives = resumeData.currentLives;
    timeBonus = resumeData.timeBonus;




    for(int i = 0; i<19; i++)
    {
        for(int j = 0; j<16; j++)
        {
            tempBoxMap[i][j] = resumeData.tempBoxMap[i][j] ;
        }
    }

    tempTotalBoxs = resumeData.tempTotalBoxs;


}



void loadTempResumeData()
{

    resumeData.isResume = thereIsResume;
    resumeData.gameMode = gameMode;
    resumeData.levelIndex = levelIndex;

    resumeData.ball = ball;
    resumeData.paddle = paddle;
    resumeData.perk = perk;

    for(int i = 0; i<19; i++)
    {
        for(int j = 0; j<16; j++)
        {
            resumeData.boxs[i][j] = boxs[i][j];
        }
    }

    resumeData.totalboxs = totalboxs;
    resumeData.shooterPaddle = shooterPaddle;
    resumeData.bulletx = bulletx;
    resumeData.bullety = bullety;
    resumeData.bulletv = bulletv;

    for(int i=0; i<20; i++)
    {
        resumeData.bulletArray[i] = bulletArray[i];
    }
    resumeData.bulletTimer = bulletTimer;

    resumeData.score = score;
    resumeData.gameplayTimer = gameplayTimer;
    for(int i=0; i<5; i++)
    {
        resumeData.gameTimeStr[i] = gameTimeStr[i];
    }

    resumeData.currentLives = currentLives;
    resumeData.timeBonus = timeBonus;

    for(int i = 0; i<19; i++)
    {
        for(int j = 0; j<16; j++)
        {
            resumeData.tempBoxMap[i][j] =  tempBoxMap[i][j];
        }
    }

    resumeData.tempTotalBoxs = tempTotalBoxs ;

    //timeBonus;

}

void ToggleMusic()
{

    musicOn =  !musicOn;

    if(musicOn)
    {

        if(scene != 3)
            PlaySound("assets\\bgmusic.wav", NULL, SND_LOOP | SND_ASYNC);

    }

    else
    {

        PlaySound(NULL, NULL, 0);
    }




}





void GameOver()
{

    doGeneralDelay(20);
    thereIsResume = 0;
    resumeData.isResume = 0;
    scene = 5;
    totalScore = score + timeBonus;
    if(totalScore > users[9].score)
    {

        takeHighScore = 1;
    }
    else
    {

        takeHighScore = 0;

    }

    //printf("%d %d %d\n",totalScore,users[9].score,takeHighScore);

    int_to_str(timeBonus, GameOverbonus);
    int_to_str(score, GameOverScore);
    int_to_str(totalScore,GameOvertotal);


    char n[15] = "";
    int l = strlen(GameOvertotal) - strlen(GameOverScore);
    while(l--)
    {
        strcat(n," ");
    }

    strcat(n, GameOverScore);
    strcpy(GameOverScore,n);
    strcpy(n,"");


    l = strlen(GameOvertotal) - strlen(GameOverbonus);
    while(l--)
    {
        strcat(n," ");
    }

    strcat(n, GameOverbonus);
    strcpy(GameOverbonus,n);
    strcpy(n,"");






}






void nextLevel()
{

    //ifGameMode == 1;

    if(gameMode == 1)
    {

        doGeneralDelay(20);

        int seconds = ((gameTimeStr[3]-'0')*10+(gameTimeStr[4]-'0'));
        int minutes =  ((gameTimeStr[0]-'0')*10+(gameTimeStr[1]-'0'));

        int bonus = 0;
        if(minutes < 3)
            bonus += (3-minutes) * 100;
        if(seconds <50)
            bonus += (50-seconds);

        timeBonus = +bonus;


        strcpy(gameTimeStr,"00:00");

        levelIndex++;

        if(levelIndex > totalLevel)
        {
            GameOver();
            scene = 5;
            return;
        }
        else
        {

            loadLevel(levelIndex);
        }
    }

    else if(gameMode == 2)
    {
        GameOver();
    }
}




int boxkill(int i, int j);
void ballDeath(int i);

void perkEffect(int i)
{
    score += 7;
    int_to_str(score, scoreChar);

    if(i==1)
    {
        ballDeath(1);


        if(!ball.live)
        {
            currentLives--;
            if(currentLives < 0)
            {
                GameOver();
                //game over show score
            }
        }

    }


    if(i==10)
    {
        nextLevel();
        score += 50;
    }

    if(i == 11)  //minusLives
    {
        currentLives--;
        if(currentLives < 0)
        {
            GameOver();
            //game over show score
        }
        /*
        if(currentLives<0)
            currentLives = 0;
            */

    }
    else if(i == 15)  //extraLive
    {
        currentLives++;
        if(currentLives>5)
            currentLives = 5;

    }

    else if(i == 12)  //shooter
    {
        shooterPaddle = 1;

    }
    else if(i == 9)  //breakthrough
    {
        breakthrough = 1;


    }
    else if(i == 13)  //reveal hidden bricks
    {
        for(int j=0; j<19; j++)
        {
            for(int k = 0; k<16; k++)
            {
                if(boxs[j][k].type==-1)
                    boxkill(j,k);
                //boxkill(j,k);
                //thik hoise?
            }
        }
    }
    else if(i == 5)  //fireball
    {
        ballFireball = 1;
    }
    else if(i == 7)  //mini ball
    {
        ball.r = ballMinR;
    }
    else if(i == 14)  //mega ball
    {
        ball.r = ballMaxR;
    }
    else if(i == 8)  //slow ball
    {
        ball.v = ballMinV;
    }
    else if(i == 4)  //fast Ball
    {
        ball.v = ballMaxV;
    }
    else if(i == 6) //ball grabber
    {
        paddle.ballGrabber = 1;
    }

    else if(i == 2) //wider paddle
    {
        if(paddle.width <= paddle.maxWidth)
        {
            paddle.len += var(25);
            paddle.width += var(25);
        }
    }

    else if(i == 3) //smaller paddle
    {
        if(paddle.width >= paddle.minWidth)
        {
            paddle.len -= var(25);
            paddle.width -= var(25);
        }
    }

}

void perkf()
{

    perk.x += perk.vx;
    perk.y += perk.vy;

    if(perk.y<= 0)
        perk.live = 0;
    if(perk.x<=0)
    {
        perk.x = 0;
        perk.vx *= -1;
    }
    if(perk.x>=windowWidth-perk.width)
    {
        perk.x = windowWidth-perk.width;
        perk.vx *= -1;
    }

    if(perk.x + perk.width >= paddle.x - paddle.len &&  perk.x <= paddle.x + paddle.len)
    {

        if(perk.y <= paddle.y+paddle.height && perk.y + perk.height >= paddle.y)
        {
            perk.live = 0;
            perkEffect(perk.type);
        }
    }

}

void perkDraw()
{
    double x = perk.x;
    double y = perk.y;
    double a = perk.width;
    iSetColor(255,255,255);
    iShowBMP(x,y,perkImage[perk.type]);

}


void generatePerk(int i, int j)
{
    perk.x = leftlimit+i*boxWidth;
    perk.y = lowerlimit+j*boxHeight,
         perk.type = randomint(1,15);
    //perk.type = 11;
    if(randomint(1,5)%2)
        perk.vx *= -1;
    perk.live = 1;
}



int boxkill(int i, int j)
{

    if(i<0 || j<0 || i>=19 || j>=16)
        return 0;

    dhakka++;
    score += 5;

    int_to_str(score, scoreChar);

    if(dhakka%7==0 && !perk.live)
    {
        dhakka = 0;
        generatePerk(i,j);
    }

    if(boxs[i][j].type>0 && boxs[i][j].type<9)
    {
        totalboxs--;

        if(totalboxs<=0)
        {
            nextLevel();
            return 1;
        }

        boxs[i][j].type = 0;
        return 0;

    }

    else if(boxs[i][j].type==9)
    {
        totalboxs--;

        if(totalboxs<=0)
        {
            nextLevel();
            return 1;
        }
        boxs[i][j].type = 0;

        if(boxkill(i,j+1))
            return 1;



        if(boxkill(i,j-1))
            return 1;;

        if(boxkill(i+1,j))
            return 1;

        if(boxkill(i-1,j))
            return 1;

        return 0;

    }
    else if(boxs[i][j].type == 10)
    {
        totalboxs--;

        if(totalboxs<=0)
        {
            nextLevel();
            return 1;
        }
        boxs[i][j].type = 0;
        return 0;
    }

    else if(boxs[i][j].type == -1)
    {
        totalboxs++;
        if(totalboxs<=0)
        {
            nextLevel();
            return 1;
        }
        boxs[i][j].type = 10;
        return 0;
    }


}


void cornerf(double x,double y,double r,double a,double b)
{

    double nx = x-a, ny = y-b;
    double n = sqrt(nx*nx+ny*ny);
    nx = nx/n, ny=ny/n;
    double dot = ball.vx*nx+ball.vy*ny;
    ball.vx = ball.vx-2*dot*nx;
    ball.vy = ball.vy-2*dot*ny;

}

int cornerCheck(int x,int y,int r,int a,int b)
{

    double d = sqrt((x-a)*(x-a)+(y-b)*(y-b));
    if(d<=r)
    {
        return 1;
    }
    return 0;
}

int collision(int i, int j)
{

    int whatToReturn = 0;

    if(boxs[i][j].type==0)
        return 0;

    double olvx = ball.vx, olvy = ball.vy,x = ball.x, y = ball.y, r = ball.r;

    if(x>=boxs[i][j].x && x<=boxs[i][j].x+boxWidth)
    {
        if(y+r>=boxs[i][j].y && y-r<=boxs[i][j].y+boxHeight)
        {
            if(!breakthrough)
                ball.vy*=-1;
            return 1;
        }
    }
    else if(y>=boxs[i][j].y && y<=boxs[i][j].y+boxHeight)
    {
        if(x+r>=boxs[i][j].x && x-r<=boxs[i][j].x+boxWidth)
        {
            if(!breakthrough)
                ball.vx*=-1;
            return 1;
        }
    }


    if(olvx==ball.vx && olvy==ball.vy)
    {

        if(cornerCheck(x,y,r,boxs[i][j].x,boxs[i][j].y))
            cornerf(x,y,r,boxs[i][j].x,boxs[i][j].y);
        if(!(olvx==ball.vx && olvy==ball.vy))
            whatToReturn = 1; //return 1;
        else if(cornerCheck(x,y,r,boxs[i][j].x,boxs[i][j].y+boxHeight))
            cornerf(x,y,r,boxs[i][j].x,boxs[i][j].y+boxHeight);
        if(!(olvx==ball.vx && olvy==ball.vy))
            whatToReturn = 1; //return 1;
        else if(cornerCheck(x,y,r,boxs[i][j].x+boxWidth,boxs[i][j].y))
            cornerf(x,y,r,boxs[i][j].x+boxWidth,boxs[i][j].y);
        if(!(olvx==ball.vx && olvy==ball.vy))
            whatToReturn = 1; //return 1;
        else if(cornerCheck(x,y,r,boxs[i][j].x+boxWidth,boxs[i][j].y+boxHeight))
            cornerf(x,y,r,boxs[i][j].x+boxWidth,boxs[i][j].y+boxHeight);
        if(!(olvx==ball.vx && olvy==ball.vy))
            whatToReturn = 1; //return 1;

    }

    if(olvx==ball.vx && olvy==ball.vy)
        whatToReturn = 0; //return 1;

    if(whatToReturn && breakthrough && boxs[i][j].type!= 100)
    {
        ball.vx = olvx;
        ball.vy = olvy;
    }
    return whatToReturn;


}

void bulletKill()
{

    for(int i=0; i<20; i++)
        bulletArray[i].live = 0;
    bulletTimer = 0;

}




void ballRevive()
{

    //ball.live = 1;

    //change paddle to regular size
    paddle.width = paddle.regularWidth;
    paddle.len = paddle.width + paddle.radius;
    paddle.ballGrabber = 0;
    ball.rx = 0;
    ball.r = ballRegularR;
    ball.v = ballRegularV;
    ballFireball = 0;
    breakthrough = 0;
    shooterPaddle = 0;


}

void ballDeath(int i)
{

    if(i)
        ball.live = 0;
    ball.launch = 0;
    perk.live = 0;
    bulletKill();
    //ballRevive();

}


void ballLauncher()
{

    double r = ball.r;
    paddle.leftpoint = paddle.x - paddle.len;
    paddle.rightpoint = paddle.x+paddle.len;

    ball.angle = (paddle.rightpoint - ball.x)/(paddle.rightpoint-paddle.leftpoint) * pi;

    if (ball.angle<(5*pi/180))
        ball.angle = 5*pi/180;
    else if (ball.angle>(175*pi/180))
        ball.angle = 175*pi/180;
    if(ball.x == paddle.x)
        ball.angle -= 10*pi/180;

    ball.y = paddle.y + paddle.height + ball.r;
    ball.dx = ball.v*cos(ball.angle);
    ball.dy = ball.v*sin(ball.angle);
    ball.angle = atan2(ball.dy, ball.dx);

    if(ball.v>r-2)
    {
        ball.vx = ball.dx/ball.v*(r-2);
        ball.vy = ball.dy/ball.v*(r-2);
    }
    else
    {
        ball.vx = ball.dx;
        ball.vy = ball.dy;
    }




}


void ballf()
{
    double r = ball.r;
    if(ball.launch)
    {

        //printf("%lf\n",ball.v);
        //dx vx ke pass kortese


        ball.dx = ball.v*cos(ball.angle);
        ball.dy = ball.v*sin(ball.angle);

        if(ball.v>r-2)
        {
            ball.vx = ball.dx/ball.v*(r-2);
            ball.vy = ball.dy/ball.v*(r-2);
        }
        else
        {
            ball.vx = ball.dx;
            ball.vy = ball.dy;
        }


        int koybar = ball.v/(r-2);
        if(koybar<1)
            koybar = 1;

        int koybarr = koybar;

        /////////////////////////////////////
        while(koybar--)
        {


            ball.x += ball.vx;
            ball.y += ball.vy;

            for(int i =0; i<19; i++)
            {
                for(int j=0; j<16; j++)
                {
                    if(collision(i,j)==1)
                    {
                        boxkill(i,j);
                        if(ballFireball)
                        {
                            boxkill(i+1,j);
                            boxkill(i-1,j);
                            boxkill(i,j+1);
                            boxkill(i,j-1);
                            boxkill(i+1,j+1);
                            boxkill(i+1,j-1);
                            boxkill(i-1,j+1);
                            boxkill(i-1,j-1);
                        }
                        break;
                    }
                }

            }

            if(ball.vx==0)
            {
                ball.vx = var(2);
                if(ball.vy < 0)
                {
                    ball.vy =-sqrt(ball.vy*ball.vy-var(4));
                }
                else
                {
                    ball.vy =sqrt(ball.vy*ball.vy-var(4));
                }

            }

            if(ball.vy==0)
            {
                ball.vy == var(3);
                if(ball.vx<0)
                {
                    ball.vx = -sqrt(ball.vx*ball.vx-var(9));
                }
                else
                {
                    ball.vx = sqrt(ball.vx*ball.vx-var(9));
                }

            }

            if(ball.x - ball.r <=0)
            {
                ball.x = ball.r;
                ball.vx*=-1;
            }

            if(ball.x + ball.r>=windowWidth)
            {
                ball.x = windowWidth - ball.r;
                ball.vx*=-1;
            }

            if(ball.y + ball.r>=windowHeight)
            {
                ball.y = windowHeight - ball.r;
                ball.vy*=-1;
            }


            if(ball.y<=ball.r)
            {
                ballDeath(1);
                //ball.launch = 0;

            }


            paddle.leftpoint = paddle.x - paddle.len;
            paddle.rightpoint = paddle.x+paddle.len;


            if(ball.x+ball.r>=paddle.leftpoint && ball.x-ball.r<=paddle.rightpoint)
            {

                if(ball.y + ball.r >= paddle.y && ball.y - ball.r <= paddle.y+paddle.height)
                {

                    ball.rx = ball.x - paddle.x;
                    ballLauncher();
                    if(paddle.ballGrabber)
                        ball.launch = 0;

                }
            }

        }


        if(!ball.live)
        {
            currentLives--;
            if(currentLives < 0)
            {
                GameOver();
                //game over show score
            }
        }

        //back nicche


        if(ball.v>r-2)
        {
            ball.dx=ball.vx*ball.v/(r-2);
            ball.dy=ball.vy*ball.v/(r-2);
        }
        else
        {
            ball.dx = ball.vx;
            ball.dy = ball.vy;
        }


        //ball.dx=ball.vx*koybarr;
        //ball.dy=ball.vy*koybarr;

        ball.v = sqrt(ball.dx*ball.dx + ball.dy*ball.dy);

        ball.angle = atan2(ball.dy,ball.dx);

    }

}

void boxDraw(double x, double y, int type)
{

    if(type==1)
    {
        iSetColor(145,18,255);
        dxFilledRectangle(x,y,boxWidth,boxHeight,22,249,255);
        iSetColor(25,25,25);
        iRectangle(x,y,boxWidth,boxHeight);

    }

    else if(type==2)
    {
        iSetColor(255,22,95);
        dxFilledRectangle(x,y,boxWidth,boxHeight,255,194,46);
        iSetColor(25,25,25);
        iRectangle(x,y,boxWidth,boxHeight);

    }

    else if(type==3)
    {
        iSetColor(253,99,113);
        dxFilledRectangle(x,y,boxWidth,boxHeight,255,213,146);
        iSetColor(25,25,25);
        iRectangle(x,y,boxWidth,boxHeight);

    }
    else if(type==4)
    {
        iSetColor(22,181,188);
        dxFilledRectangle(x,y,boxWidth,boxHeight,228,227,114);
        iSetColor(25,25,25);
        iRectangle(x,y,boxWidth,boxHeight);

    }

    else if(type==5)
    {
        iSetColor(11,108,230);
        dxFilledRectangle(x,y,boxWidth,boxHeight,104,245,16);
        iSetColor(25,25,25);
        iRectangle(x,y,boxWidth,boxHeight);
    }
    else if(type==6)
    {
        iSetColor(255,135,66);
        dxFilledRectangle(x,y,boxWidth,boxHeight,255,203,44);
        iSetColor(25,25,25);
        iRectangle(x,y,boxWidth,boxHeight);
    }
    else if(type==7)
    {
        iSetColor(241,40,185);
        dxFilledRectangle(x,y,boxWidth,boxHeight,246,190,110);
        iSetColor(25,25,25);
        iRectangle(x,y,boxWidth,boxHeight);
    }

    else if(type==8)
    {
        iSetColor(100,100,100);
        dxFilledRectangle(x,y,boxWidth,boxHeight,200,200,200);
        iSetColor(25,25,25);
        iRectangle(x,y,boxWidth,boxHeight);
    }
    else if(type==9)
    {

        if(blink)
        {
            iSetColor(255,255,255);
            iFilledRectangle(x,y,boxWidth,boxHeight);
            iSetColor(255,106,0);
            iFilledRectangle(x+var(10),y+var(10),boxWidth-var(20),boxHeight-var(20));
            iSetColor(25,25,25);
            iRectangle(x,y,boxWidth,boxHeight);
        }

        else
        {
            iSetColor(255,106,0);

            iFilledRectangle(x,y,boxWidth,boxHeight);
            iSetColor(255,255,255);
            iFilledRectangle(x+7,y+7,boxWidth-14,boxHeight-14);
            iSetColor(25,25,25);
            iRectangle(x,y,boxWidth,boxHeight);
        }
    }
    else if(type == -1)
    {

        //jodi creator mode thake taile type 10 draw korbe

        if(scene == 14|| scene == 15)
        {

            iSetColor(237,28,36);
            iFilledRectangle(x,y,boxWidth,boxHeight);
            iSetColor(50,50,50);
            iLine(x,y,x,y+boxHeight);
            iLine(x+boxWidth/4,y,x+boxWidth/4,y+boxHeight);
            iLine(x+boxWidth/4*2,y,x+boxWidth/4*2,y+boxHeight);
            iLine(x+boxWidth/4*3,y,x+boxWidth/4*3,y+boxHeight);
            iLine(x+boxWidth/4*4,y,x+boxWidth/4*4,y+boxHeight);
            iSetColor(25,25,25);
            iRectangle(x,y,boxWidth,boxHeight);

        }


    }

    else if(type==10)
    {

        iSetColor(237,28,36);
        iFilledRectangle(x,y,boxWidth,boxHeight);
        iSetColor(50,50,50);
        iLine(x,y,x,y+boxHeight);
        iLine(x+boxWidth/4,y,x+boxWidth/4,y+boxHeight);
        iLine(x+boxWidth/4*2,y,x+boxWidth/4*2,y+boxHeight);
        iLine(x+boxWidth/4*3,y,x+boxWidth/4*3,y+boxHeight);
        iLine(x+boxWidth/4*4,y,x+boxWidth/4*4,y+boxHeight);
        iSetColor(25,25,25);
        iRectangle(x,y,boxWidth,boxHeight);

    }


}



int xToArray(int x)
{
    return (x-leftlimit)/boxWidth;
}
int yToArray(int y)
{
    return (y-lowerlimit)/boxHeight;
}







void bulletf()
{

    int i,j,k,koybar = bulletv/bullety;
    if(koybar<1)
        koybar = 1;

    while(koybar--)
    {

        for(i=0; i<20; i++)
        {
            if(bulletArray[i].live)
            {
                bulletArray[i].y += bulletv/bullety;

                if(bulletArray[i].y>= windowHeight)
                    bulletArray[i].live = 0;

                for(j=0; j<19; j++)
                {
                    if(!bulletArray[i].live)
                        break;

                    for(k=0; k<16; k++)
                    {
                        if(boxs[j][k].type==0)
                            continue;
                        if(bulletArray[i].x + bulletx >=  boxs[j][k].x && bulletArray[i].x<= boxs[j][k].x +boxWidth)
                        {
                            if(bulletArray[i].y + bullety >= boxs[j][k].y && bulletArray[i].y <= boxs[j][k].y + boxHeight)
                            {
                                boxkill(j,k);
                                bulletArray[i].live = 0;
                                break;
                            }
                        }

                    }
                }

            }

        }



    }




}

void bulletGenerator(double x, double y,double dis)
{

    int i,j;
    for(i=0; i<20; i++)
    {
        if(!bulletArray[i].live)
        {
            bulletArray[i].x = x;
            bulletArray[i].y = y;
            bulletArray[i].live = 1;

            break;
        }
    }
    for(; i<20; i++)
    {
        if(!bulletArray[i].live)
        {
            bulletArray[i].x = x + dis;
            bulletArray[i].y = y;
            bulletArray[i].live = 1;
            break;
        }
    }

}


void loadLevel(int levelIndex)
{

    if(levelIndex)
    {

        for(int i=0; i<19; i++)
        {
            for(int j=0; j<16; j++)
            {
                boxs[i][j].type = levelMap[levelIndex-1].boxs_type[i][j];
                boxs[i][j].x = leftlimit+i*boxWidth;
                boxs[i][j].y = lowerlimit+j*boxHeight;

            }
        };

        totalboxs = levelMap[levelIndex-1].totalboxs;
        //printf("%d\n",totalboxs);

        ball.live = 1;
        ballDeath(0);
        ballRevive();
    }

    else
    {
        for(int i=0; i<19; i++)
        {
            for(int j=0; j<16; j++)
            {
                boxs[i][j].type = tempBoxMap[i][j];
                boxs[i][j].x = leftlimit+i*boxWidth;
                boxs[i][j].y = lowerlimit+j*boxHeight;

            }
        };
        totalboxs = tempTotalBoxs;
        //printf("%d\n",totalboxs);

        ball.live = 1;
        ballDeath(0);
        ballRevive();
    }


}





void NewGameInitialize()
{

    score = 0;
    strcpy(scoreChar,"0");
    strcpy(gameTimeStr, "00:00");
    timeBonus = 0;
    currentLives = 3;
    levelIndex = 1;
    if(gameMode==1)
        loadLevel(1);
    else
        loadLevel(0);

}


void resumeButtonEffect(int i)
{

    if(i==4)
    {
        //menu
        thereIsResume = 1;
        loadTempResumeData();
        gameplayPause = 0;
        scene = 3;
    }
    else if(i==3)
    {
        //sound
        ToggleMusic();
    }

    else if(i==2)
    {
        //restart
        NewGameInitialize();
        gameplayPause = 2;
    }

    else
    {
        //resume
        gameplayPause = 2;
    }

}


//end gameplay


void menuButtonEffect(int i)
{

    if(i==0)
    {
        //exit
        scene = 12;
    }
    else if(i==1)
    {
        //credits
        scene = 11;
    }
    else if(i==2)
    {
        //instruction
        scene = 9;
    }
    else if(i==3)
    {
        //highscore
        scene = 8;
    }
    else if(i==4)
    {
        //settings
        scene = 7;
    }
    else if(i==5)
    {
        scene = 13;
    }
    else if(i==6)
    {
        //newgame
        //reloadResumeData();
        gameMode = 1;
        NewGameInitialize();
        scene = 4;
    }
    else if(i==7)
    {
        //resume
        //loadOldGame (GameMode)
        reloadResumeData();
        scene = 4;
    }
}


void gameExit(int errorCode)
{

    resumeData.isResume = thereIsResume;
    writeResumeData();
    writeLevelMap();
    writeHighScores();
    exit(errorCode);
}


void displayHighScore()
{

    double x,y;
    char s[15];
    x = var(200);
    y = windowHeight-var(175);


    iSetColor(255,255,255);

    for(int i=0; i<10; i++)
    {
        iText(x,y,users[i].name, GLUT_BITMAP_TIMES_ROMAN_24);

        int_to_str(users[i].score,s);
        iText(x+400,y,s,GLUT_BITMAP_TIMES_ROMAN_24);

        y-= var(50);
    }

    y = windowHeight-var(175) - var(20);
    iSetColor(237,28,36);
    for(int i=0; i<9; i++)
    {
        iFilledRectangle(x-50, y, 600, 3);

        y-= var(50);
    }

}



void levelmakerButtonEffect(int button)
{

    int i,j;
    if(button == 1)
    {
        for(i=0; i<19; i++)
        {
            for(j=0; j<16; j++)
            {
                boxmap[i][j] = 0;
            }
        }
        scene = 14;
        showLessBoxMessage = 0;
    }

    else if(button == 2)
    {

        editerror = 0;
        scene = 16;
    }

    else if(button == 3)
    {
        for(i=0; i<19; i++)
        {
            for(j=0; j<16; j++)
            {
                boxmap[i][j] = levelMap[editIndex-1].boxs_type[i][j] ;
            }
        }
        showLessBoxMessage = 0;
        scene = 15;
    }




}

void createButtonEffect(int button)
{


    if(button == 1)
    {

        int boxCount = 0,i,j;
        for(i=0; i<19; i++)
        {
            for(j=0; j<16; j++)
            {
                tempBoxMap[i][j] = boxmap[i][j];
                if(boxmap[i][j]>0 && boxmap[i][j]<10)
                {
                    boxCount++;
                }
            }
        }

        tempTotalBoxs = boxCount;


        if(boxCount<10)
        {
            //error need more Block
            showLessBoxMessage = 1;
        }

        else
        {

            showLessBoxMessage = 0;
            gameMode = 2;
            NewGameInitialize();
            scene = 4;
            thereIsResume = 0;
            gameplayPause = 2; // really

        }




    }

    else if(button == 2)
    {

        int boxCount = 0,i,j;
        for(i=0; i<19; i++)
        {
            for(j=0; j<16; j++)
            {

                if(boxmap[i][j]>0 && boxmap[i][j]<10)
                {
                    boxCount++;
                }
            }
        }


        if(boxCount<10)
        {
            //error need more Block
            showLessBoxMessage = 1;
        }

        else
        {
            boxCount = 0;
            for(i=0; i<19; i++)
            {
                for(j=0; j<16; j++)
                {
                    levelMap[editIndex-1].boxs_type[i][j] = boxmap[i][j];
                    if(boxmap[i][j]>0 && boxmap[i][j]<10)
                    {
                        boxCount++;
                    }
                }
            }

            showLessBoxMessage = 0;
            levelMap[editIndex-1].totalboxs = boxCount;
            editIndex = 0;
            thereIsResume = 0;
            scene = 3;

        }

    }

}


void overButtonEffect(int button)
{
    if(strlen(currentUsername)==0)
    {
        strcpy(currentUsername, "UNKNOWN");
    }

    strcpy(users[10].name, currentUsername);
    users[10].score = totalScore;
    sort_users();
    if(button==1)
    {

        NewGameInitialize();
        scene = 4;
        gameplayPause = 2;

    }

    else if(button == 2)
    {

        thereIsResume = 0;
        scene = 3;

    }

}




void change()
{

    if(generalDelay)
    {
        generalDelayTimer++;
        if(generalDelayTimer>=generalDelayLimit)
        {
            generalDelayTimer = 0;
            generalDelay = 0;
        }
    }


    else
    {


        if(scene==0)
        {
            scene0Timer++;
            if(scene0Timer>=20)
            {
                scene0Timer = 0;
                scene++;
            }
        }
        if(scene==1)
        {
            scene1Timer++;
            if(scene1Timer>=40)
            {
                scene1Timer = 0;
                readResumeData();
                //reloadResumeData();
                readHighscores();
                //printf("%d\n",thereIsResume);
                scene++;

            }
        }

        else if(scene ==2 )
        {
            scene2Timer++;
            if(scene2Timer>=80)
            {
                scene2Timer = 0;
                readLevelMap();
                scene++;
                PlaySound("assets\\bgmusic.wav",NULL, SND_LOOP | SND_ASYNC);
            }

        }
        else if(scene == 3)
        {




        }
        else if(scene == 4)
        {


            blinkTimer++;
            if(blinkTimer>=4)
            {
                blinkTimer = 0;
                blink = !blink;
            }


            if(gameplayPause==0)
            {
                if(!ball.live)
                {
                    ballReviveTime += 25;


                    if(ballReviveTime >= ballFullReviveTime)
                    {
                        ball.live = 1;
                        ballReviveTime = 0;
                        ballRevive();
                    }


                }


                else if(ball.live)
                {

                    gameplayTimer++;
                    if(gameplayTimer>=35)
                    {

                        gameTimeStr[4]++;
                        totalSeconds++;
                        gameplayTimer = 0;

                        if(gameTimeStr[4]>'9')
                        {
                            gameTimeStr[4] = '0';
                            gameTimeStr[3]++;
                        }
                        if(gameTimeStr[3]>'6')
                        {
                            gameTimeStr[3] = '0';
                            gameTimeStr[1]++;
                        }
                        if(gameTimeStr[1]>'9')
                        {
                            gameTimeStr[1] = '0';
                            gameTimeStr[0]++;
                        }
                        if(gameTimeStr[0]>'9')
                        {
                            gameTimeStr[0] = '9';
                        }



                    }

                    if(ball.launch)
                    {
                        ballf();

                    }
                    if(perk.live)
                        perkf();

                    ballVelocityTimer++;
                    if(ballVelocityTimer >= 50)
                    {
                        ballVelocityTimer = 0;
                        ball.v += var(0.5);
                        //printf("%lf %lf\n",ball.v,ball.r);
                        if(ball.v >= ballMaxV)
                            ball.v = ballMaxV;
                    }

                    if(shooterPaddle)
                    {
                        if(bulletTimer)
                            bulletTimer++;
                        if(bulletTimer>=bulletMaxTime)
                            bulletTimer = 0;
                        bulletf();
                    }

                }

            }

            else if(gameplayPause == 2)
            {
                gameplayPauseTimer++;
                if(gameplayPauseTimer>=15)
                {
                    gameplayPauseTimer = 0;
                    gameplayPause = 0;
                }
            }

        }

        else if(scene ==5 )
        {

        }
        else if(scene == 6)
        {

        }
        else if(scene == 7)
        {

        }
        else if(scene ==8 )
        {

        }
        else if(scene == 9)
        {

        }
        else if(scene == 10)
        {

        }
        else if(scene ==11 )
        {

        }
        else if(scene == 12)
        {
            scene12Timer++;
            if(scene12Timer>=60)
            {
                scene12Timer = 0;
                gameExit(0);
            }

        }


        else if(scene == 14 || scene == 15)
        {

            blinkTimer++;
            if(blinkTimer>=4)
            {
                blinkTimer = 0;
                blink = !blink;
            }

        }




    }
}


void iDraw()
{

    //place your drawing codes here
    iClear();
    if(scene == 0)
    {
        iSetColor(25,25,25);
        iFilledRectangle(0,0, windowWidth, windowHeight);

    }
    else if(scene == 1)
    {
        iSetColor(25,25,25);
        iFilledRectangle(0,0,windowWidth,windowHeight);
        iShowBMP(windowWidth/2-986/2, windowHeight/2-274/2, "assets\\images\\scene1.bmp");
        iShowBMP(windowWidth/2-606/2, var(50), "assets\\images\\scene1_2.bmp");

    }
    else if(scene == 2)
    {
        iSetColor(25,25,25);
        iFilledRectangle(0,0,windowWidth,windowHeight);
        iShowBMP(windowWidth/2-1030/2, windowHeight/2-300/2, "assets\\images\\scene2.bmp");

    }
    else if(scene == 3)
    {
        iSetColor(25,25,25);
        iFilledRectangle(0,0, windowWidth, windowHeight);

        double x = windowWidth - 450;
        double y = 71;

        iShowBMP(x/2 - 697/2, windowHeight/2-501/2, menulogo);

        for(int i=0; i<8; i++)
        {

            if(!thereIsResume && i == 7)
                continue;

            if(menuButtonSelected == i)
            {
                iSetColor(237,28,36);
                iFilledRectangle(x-40,y,menuButtonWidth[i] + 100,71);
                iShowBMP2(x+10,y+5,menuButtons[i],0);
            }

            else
            {
                iShowBMP2(x,y+5,menuButtons[i],0);
            }
            y+=71;
        }



    }
    else if(scene == 4)
    {
        iSetColor(25,25,25);
        iFilledRectangle(0,0,windowWidth,windowHeight);
        double x = leftlimit;
        double y = lowerlimit;

        //time

        iSetColor(255,255,255);
        iText(var(10), windowHeight-20, "Score :",GLUT_BITMAP_HELVETICA_18);
        iText(var(10)+80, windowHeight-20, scoreChar,GLUT_BITMAP_HELVETICA_18);
        iText(windowWidth - 60,windowHeight-20,gameTimeStr,GLUT_BITMAP_HELVETICA_18);

        //life

        double lifepos = windowWidth/2 - currentLives*25;
        for(int i = 0; i<currentLives ; i++)
        {
            iShowBMP(lifepos, windowHeight - 40, LifeIcon);
            lifepos += 50;
        }


        for(int i=0; i<19; i++)
        {
            for(int j=0; j<16; j++)
            {
                boxDraw(leftlimit+i*boxWidth, lowerlimit+j*boxHeight, boxs[i][j].type);
            }
        }


        iSetColor(255,0,0);
        if(shooterPaddle)
        {
            for(int i = 0; i<20; i++)
            {

                if(bulletArray[i].live)
                {
                    iFilledRectangle(bulletArray[i].x, bulletArray[i].y, bulletx, bullety);
                }
            }
        }


        //ball Grabber
        if(paddle.ballGrabber)
        {
            iSetColor(255,0,0);

            /*
            iFilledRectangle(paddle.x - paddle.width, paddle.y+paddle.height+ballRegularR - ballRegularR/8 , paddle.width*2,ballRegularR/4);
            iSetColor(255,255,255);
            iFilledRectangle(paddle.x-paddle.width, paddle.y+paddle.height + var(3), var(3), ballRegularR*2);
            iFilledRectangle(paddle.x+paddle.width-var(3) , paddle.y+paddle.height + var(3), var(3),  ballRegularR*2);
            */
            iFilledRectangle(paddle.x - paddle.len, paddle.y+paddle.height+ballRegularR - ballRegularR/8, paddle.len*2,ballRegularR/4);
        }

        if(paddle.ballGrabber || shooterPaddle)
        {

            if(shooterPaddle)
                iSetColor(255,0,0);
            else
                iSetColor(255,255,255);
            //iFilledRectangle(paddle.x-paddle.len, paddle.y+paddle.height/2 + var(3), var(3), ballRegularR*2 + paddle.height/2);
            //iFilledRectangle(paddle.x+paddle.len-var(3), paddle.y+paddle.height/2 + var(5), var(3),  ballRegularR*2+ paddle.height/2);
            iFilledRectangle(paddle.x-paddle.width, paddle.y+paddle.height/2 + var(4), var(4), ballRegularR*2);
            iFilledRectangle(paddle.x+paddle.width-var(4), paddle.y+paddle.height/2 + var(5), var(4),  ballRegularR*2);
        }



        //ball

        if(!ball.launch)
        {
            ball.x = paddle.x + ball.rx;
            ball.y = paddle.y + paddle.height + ball.r;
        }

        if(ball.live)
        {



            if(ballFireball)
            {
                iSetColor(255,41,0);
                iFilledCircle(ball.x,ball.y,ball.r);
                iSetColor(255,80,0);
                iFilledCircle(ball.x,ball.y,ball.r/2);
                iSetColor(255,109,0);
            }
            else
            {
                iSetColor(255,255,255);
                iFilledCircle(ball.x,ball.y,ball.r);

            }
        }

        //paddle
        iSetColor(0,255,255);
        iFilledCircle(paddle.x+paddle.width, paddle.y+paddle.height/2,paddle.radius);
        iFilledCircle(paddle.x-paddle.width, paddle.y+paddle.height/2,paddle.radius);
        iFilledRectangle(paddle.x-paddle.width, paddle.y, paddle.width*2, paddle.height);



        //perk;

        if(perk.live)
        {
            perkDraw();
        }




        //pause menu
        if(gameplayPause==1)
        {
            iSetColor(50,50,50);
            double x = windowWidth/2;
            double y = windowHeight/2-71*3;
            iFilledRectangle(windowWidth/2-426/2-100, y+20, 626, 71*6-40);

            y = y+71;
            for(int i = 4; i>=1; i--)
            {
                if(i==resumeButtonSelected)
                {
                    iSetColor(237,28,36);
                    iFilledRectangle(x-resumeButtonWidth[i]/2-50,y,resumeButtonWidth[i]+100,71);
                }
                iShowBMP2(x-resumeButtonWidth[i]/2, y, resumeButtons[i],0 );
                y = y+71;
            }

        }


    }
    else if(scene == 5)
    {
        iSetColor(25,25,25);
        iFilledRectangle(0,0, windowWidth, windowHeight);

        double yy = windowHeight-var(50)-88;


        iShowBMP(windowWidth/2 - 184, yy, "assets\\images\\over.bmp");


        iSetColor(255,255,255);
        yy = windowHeight/2 +60;
        iText(windowWidth/2 - 150, yy, "Score",GLUT_BITMAP_HELVETICA_18);
        iText(windowWidth/2, yy, ":",GLUT_BITMAP_HELVETICA_18);
        iText(windowWidth/2 + 50, yy, GameOverScore,GLUT_BITMAP_HELVETICA_18);



        yy -= 48;
        iText(windowWidth/2 - 150, yy, "Time Bonus",GLUT_BITMAP_HELVETICA_18);
        iText(windowWidth/2, yy, ":",GLUT_BITMAP_HELVETICA_18);
        iText(windowWidth/2 + 50, yy, GameOverbonus,GLUT_BITMAP_HELVETICA_18);

        yy -= 60;
        iText(windowWidth/2 - 150, yy, "Total Score",GLUT_BITMAP_HELVETICA_18);
        iText(windowWidth/2, yy, ":",GLUT_BITMAP_HELVETICA_18);
        iText(windowWidth/2 + 50, yy, GameOvertotal,GLUT_BITMAP_HELVETICA_18);


        yy += 30;
        iSetColor(237,28,36);
        iFilledRectangle(windowWidth/2 - 200,yy,400,5);

        iSetColor(255,255,255);
        if(overButton != 1)
            iRectangle(windowWidth/2-336,var(50),286, 100);
        if(overButton != 2)
            iRectangle(windowWidth/2+50,var(50), 286, 100);

        if(overButton == 1)
        {
            iSetColor(237,28,36);
            iFilledRectangle(windowWidth/2-336,var(50),286, 100);
        }
        else if(overButton == 2)
        {
            iSetColor(237,28,36);
            iFilledRectangle(windowWidth/2+50,var(50), 286, 100);
        }


        iShowBMP2(windowWidth/2-336,var(50),"assets\\images\\again.bmp",0);
        iShowBMP2(windowWidth/2+50,var(50),"assets\\images\\menu.bmp",0);



        if(takeHighScore)
        {

            yy = var(250);
            iSetColor(255,255,255);
            iText(windowWidth/2 - 280, yy, "Well Done! You're on the leaderboard. Enter your name",GLUT_BITMAP_TIMES_ROMAN_24);

            yy -= 70;
            double xx = windowWidth/2 - 350;
            iSetColor(237,28,36);
            iFilledRectangle(xx, yy-5, 700, 5);
            iFilledRectangle(xx, yy+45, 700, 5);
            iFilledRectangle(xx, yy-5, 5, 50);
            iFilledRectangle(xx + 695, yy-5, 5, 50);

            iSetColor(255,255,255);
            iText(xx + 235, yy + 15, currentUsername, GLUT_BITMAP_HELVETICA_18);

        }



    }
    else if(scene == 6)
    {
        iSetColor(25,25,25);
        iFilledRectangle(0,0, windowWidth, windowHeight);


    }
    else if(scene == 7)
    {
        //highScore
        iSetColor(25,25,25);
        iFilledRectangle(0,0, windowWidth, windowHeight);
        if(backButtonSelected)
        {
            iSetColor(237,28,36);
            iFilledRectangle(10,windowHeight-60,50,50);
        }
        iShowBMP2(20,windowHeight-50,backButtonStr,0);

        if(settingsButton == 1)
        {
            iSetColor(237,28,36);
            iFilledRectangle(windowWidth/2 - 465/2 - 50,windowHeight/2 + 150 -50,565, 182);
        }

        if(settingsButton == 2)
        {

            iSetColor(237,28,36);
            iFilledRectangle(windowWidth/2 - 514/2 - 50,windowHeight/2 - 50 -50,618, 182);
        }

        if(settingsButton == 3)
        {

            iSetColor(237,28,36);
            iFilledRectangle(windowWidth/2 - 589/2 - 50,windowHeight/2 - 250 -50,689, 182);

        }


        iShowBMP2(windowWidth/2 - 465/2, windowHeight/2 + 150, "assets\\images\\sound.bmp",0);
        iShowBMP2(windowWidth/2 - 518/2, windowHeight/2 - 50, "assets\\images\\levels.bmp",0);
        iShowBMP2(windowWidth/2 - 589/2, windowHeight/2 -250, "assets\\images\\clear.bmp",0);









    }
    else if(scene == 8)
    {
        //highScore
        iSetColor(25,25,25);
        iFilledRectangle(0,0, windowWidth, windowHeight);
        iShowBMP(windowWidth*3/4-430/2, windowHeight/2-520/2, "assets\\images\\scene8.bmp");
        if(backButtonSelected)
        {
            iSetColor(237,28,36);
            iFilledRectangle(10,windowHeight-60,50,50);
        }
        iShowBMP2(20,windowHeight-50,backButtonStr,0);
        displayHighScore();


    }
    else if(scene == 9)
    {
        iSetColor(25,25,25);
        iFilledRectangle(0,0, windowWidth, windowHeight);
        iShowBMP(windowWidth/2-1248/2, windowHeight/2-372/2, "assets\\images\\scene9.bmp");
        if(backButtonSelected)
        {
            iSetColor(237,28,36);
            iFilledRectangle(10,windowHeight-60,50,50);
        }
        iShowBMP2(20,windowHeight-50,backButtonStr,0);


        if(nextButtonSelected)
        {
            iSetColor(237,28,36);
            iFilledRectangle(70,windowHeight-60,50,50);
        }
        iShowBMP2(80,windowHeight-50,nextButtonStr,0);







    }
    else if(scene == 10)
    {
        iSetColor(25,25,25);
        iFilledRectangle(0,0, windowWidth, windowHeight);
        iShowBMP(windowWidth/2-1100/2, windowHeight/2-608/2, "assets\\images\\scene10.bmp");
        if(backButtonSelected)
        {
            iSetColor(237,28,36);
            iFilledRectangle(10,windowHeight-60,50,50);
        }
        iShowBMP2(20,windowHeight-50,backButtonStr,0);

    }
    else if(scene == 11)
    {
        iSetColor(25,25,25);
        iFilledRectangle(0,0,windowWidth,windowHeight);
        iShowBMP(windowWidth/2-812/2, windowHeight/2-597/2, "assets\\images\\scene11.bmp");
        if(backButtonSelected)
        {
            iSetColor(237,28,36);
            iFilledRectangle(10,windowHeight-60,50,50);
        }
        iShowBMP2(20,windowHeight-50,backButtonStr,0);


    }
    else if(scene == 12)
    {
        iSetColor(25,25,25);
        iFilledRectangle(0,0,windowWidth,windowHeight);
        iShowBMP(windowWidth/2-788/2, windowHeight/2-380/2, "assets\\images\\scene12.bmp");

    }
    else if(scene == 13)
    {
        iSetColor(25,25,25);
        iFilledRectangle(0,0,windowWidth,windowHeight);
        if(backButtonSelected)
        {
            iSetColor(237,28,36);
            iFilledRectangle(10,windowHeight-60,50,50);
        }
        iShowBMP2(20,windowHeight-50,backButtonStr,0);

        iSetColor(255,255,255);


        if(scene13Button != 1)
            iRectangle(windowWidth/2 - 445 - var(50), windowHeight/2 - 94.5,445, 189);
        if(scene13Button != 2)
            iRectangle(windowWidth/2 + var(50), windowHeight/2 - 94.5,445, 189);

        if(scene13Button == 1)
        {
            iSetColor(237,28,36);
            iFilledRectangle(windowWidth/2 - 445 - var(50), windowHeight/2 - 94.5,445, 189);
        }
        else if(scene13Button == 2)
        {
            iSetColor(237,28,36);
            iFilledRectangle(windowWidth/2 + var(50), windowHeight/2 - 94.5,445, 189);
        }

        iShowBMP(windowWidth/2 - 611.5, var(50), scene13[2]);
        iShowBMP2(windowWidth/2 - 445 - var(50), windowHeight/2 - 94.5, scene13[0],0);
        iShowBMP2(windowWidth/2 + var(50), windowHeight/2 - 94.5, scene13[1],0);





    }



    else if(scene == 14)
    {
        //highScore
        iSetColor(25,25,25);
        iFilledRectangle(0,0, windowWidth, windowHeight);
        if(backButtonSelected)
        {
            iSetColor(237,28,36);
            iFilledRectangle(10,windowHeight-60,50,50);
        }
        iShowBMP2(20,windowHeight-50,backButtonStr,0);


    }

    else if(scene == 15)
    {
        //highScore
        iSetColor(25,25,25);
        iFilledRectangle(0,0, windowWidth, windowHeight);
        if(backButtonSelected)
        {
            iSetColor(237,28,36);
            iFilledRectangle(10,windowHeight-60,50,50);
        }
        iShowBMP2(20,windowHeight-50,backButtonStr,0);


    }

    else if(scene == 16)
    {

        iSetColor(25,25,25);
        iFilledRectangle(0,0,windowWidth,windowHeight);
        if(backButtonSelected)
        {
            iSetColor(237,28,36);
            iFilledRectangle(10,windowHeight-60,50,50);
        }
        iShowBMP2(20,windowHeight-50,backButtonStr,0);






        double yy = windowHeight/2;
        iSetColor(255,255,255);
        iText(windowWidth/2 - 250, yy, "Enter a valid level index (1-20) and press Enter",GLUT_BITMAP_TIMES_ROMAN_24);

        yy -= 70;
        double xx = windowWidth/2 - 350;
        iSetColor(237,28,36);
        iFilledRectangle(xx, yy-5, 700, 5);
        iFilledRectangle(xx, yy+45, 700, 5);
        iFilledRectangle(xx, yy-5, 5, 50);
        iFilledRectangle(xx + 695, yy-5, 5, 50);

        iSetColor(255,255,255);
        iText(xx + 350, yy + 15, editChar, GLUT_BITMAP_HELVETICA_18);

        if(editerror)
        {
            iSetColor(255,255,255);
            iText(50,50,"Please type a VALID index");
        }


    }


    if(scene == 14 || scene == 15)
    {


        double x = leftlimit;
        double y = lowerlimit;

        if(showLessBoxMessage)
        {
            iSetColor(237,28,36);
            iText(x,y-100,"Add at least 10 non-hidden blocks to continue.", GLUT_BITMAP_HELVETICA_18);
        }

        iSetColor(255,255,255);
        iText(x,y-50, "Left click on one of the blocks to select it. Left click and drag to add blocks, Right click to remove. Press 'R' to clear everything.", GLUT_BITMAP_HELVETICA_18);

        for(double i=y; i<=higherlimit; i+=boxHeight)
        {
            iLine(x,i,rightlimit,i);
        }
        for(double i=x; i<=rightlimit; i+=boxWidth)
        {
            iLine(i,y,i,higherlimit);
        }

        x = var(30), y = var(20); //gotta change this
        for(int i=0; i<boxn; i++)
        {
            if(boxType[i]==setboxType)
            {
                iSetColor(255,255,255);
                iFilledRectangle(x-10,y-10,boxWidth+20,boxHeight+20); //gotta change this
            }
            boxDraw(x,y,boxType[i]);
            x+=var(110); //gotta change this
        }

        for(int i=0; i<19; i++)
        {
            for(int j=0; j<16; j++)
            {
                boxDraw(leftlimit+i*boxWidth, lowerlimit+j*boxHeight, boxmap[i][j]);
            }
        }


        if(!createButton)
        {
            iSetColor(255,255,255);
            iRectangle(windowWidth - var(20) - 160, var(20), 160,82);
        }
        else
        {

            iSetColor(237,28,36);
            iFilledRectangle(windowWidth - var(20) - 160, var(20), 160,82);
        }

        if(scene==14)
        {
            iShowBMP2(windowWidth - var(20) - 160, var(20), scene13[3],0);
        }
        else if(scene == 15)
        {
            iShowBMP2(windowWidth - var(20) - 160, var(20), scene13[4],0);
        }

    }




}

void iPassiveMouseMove(int mx, int my)
{


    if(scene==0)
    {

    }

    else if(scene == 1)
    {

    }
    else if(scene ==2 )
    {

    }
    else if(scene == 3)
    {


        for(int i=0; i<8; i++)
        {
            if(!thereIsResume&& i == 7)
                continue;
            if(mx>=menuRedX && mx<=menuRedX + menuButtonWidth[i] + 100 )
            {
                if(my>=(i+1)*71 && my<=(i+2)*71)
                {
                    menuButtonSelected = i;
                }
            }
        }




    }
    else if(scene == 4)
    {
        if(gameplayPause==0)
        {

            if(mx>=0 + paddle.len && mx<=windowWidth-paddle.len)
                paddle.x = mx;
            else if(mx<=0+paddle.len)
                paddle.x = 0 + paddle.len;
            else if(mx>=windowWidth-paddle.len)
                paddle.x =windowWidth-paddle.len;
        }

        else if(gameplayPause==1)
        {

            double x = windowWidth/2;
            double y = windowHeight/2-71*3 + 71;

            for(int i = 4; i>=1; i--)
            {

                if(mx >= x-resumeButtonWidth[i]/2-50 && mx<= x + resumeButtonWidth[i]/2+50)
                {
                    if(my>=y && my<=y+71)
                    {
                        resumeButtonSelected = i;
                    }
                }

                y = y+71;
            }

        }

    }
    else if(scene ==5 )
    {

        if(mx >= windowWidth/2-336 && mx<= windowWidth/2-336 + 286)
        {
            if(my>= var(50) && my<= var(50) + 100 )
            {
                overButton = 1;
            }
        }

        else if(mx >= windowWidth/2+50 && mx<= windowWidth/2+50+ 286)
        {
            if(my>= var(50) && my<= var(50) + 100 )
            {
                overButton = 2;
            }
        }
        else
            overButton = 0;


    }
    else if(scene == 6)
    {

    }
    else if(scene == 7)
    {
        if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
        {
            backButtonSelected = 1;
        }
        else
        {
            backButtonSelected = 0;
        }

        if(mx >= windowWidth/2 - 282.5 && mx<= windowWidth/2 - 465/2 - 50 + 565 && my>= windowHeight/2 + 100  && my<= windowHeight/2 + 282 )
        {
            settingsButton = 1;
        }
        else if(mx >= windowWidth/2 - 309 && mx<= windowWidth/2 - 518/2 - 50 + 618 && my>= windowHeight/2 -100 && my<= windowHeight/2 +82 )
        {
            settingsButton = 2;
        }
        else if(mx >= windowWidth/2 - 344.5 && mx<= windowWidth/2 - 518/2 - 50 + 689 && my>= windowHeight/2 -300  && my<= windowHeight/2 -118 )
        {
            settingsButton = 3;
        }
        else
        {
            settingsButton = 0;
        }


    }
    else if(scene ==8 )
    {

        if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
        {
            backButtonSelected = 1;
        }
        else
        {
            backButtonSelected = 0;
        }
    }
    else if(scene == 9)
    {
        if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
        {
            backButtonSelected = 1;
        }
        else
        {
            backButtonSelected = 0;
        }


        if(mx>=70 && mx<=120 && my>= windowHeight-60 && my<= windowHeight-10)
        {
            nextButtonSelected = 1;
        }
        else
        {
            nextButtonSelected = 0;
        }
    }
    else if(scene == 10)
    {
        if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
        {
            backButtonSelected = 1;
        }
        else
        {
            backButtonSelected = 0;
        }
    }
    else if(scene ==11 )
    {
        if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
        {
            backButtonSelected = 1;
        }
        else
        {
            backButtonSelected = 0;
        }
    }
    else if(scene == 12)
    {

    }

    else if(scene == 13)
    {

        if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
        {
            backButtonSelected = 1;
        }
        else
        {
            backButtonSelected = 0;
        }


        if(mx >= windowWidth/2 - 445 - var(50) && mx<= windowWidth/2 - var(50))
        {
            if(my>= windowHeight/2 - 94.5 && my<= windowHeight/2 - 94.5 + 189 )
            {
                scene13Button = 1;
            }
        }

        else if(mx >= windowWidth/2 + var(50) && mx<= windowWidth/2 + var(50) + 445)
        {
            if(my>= windowHeight/2 - 94.5 && my<= windowHeight/2 - 94.5 + 189 )
            {
                scene13Button = 2;
            }
        }
        else
            scene13Button = 0;
    }


    else if(scene == 14 )
    {

        if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
        {
            backButtonSelected = 1;
        }
        else
        {
            backButtonSelected = 0;
        }



        if(mx>=windowWidth - var(20) - 160 && mx<=windowWidth - var(20) && my>= var(20) && my<=var(20)+82)
        {
            createButton = 1;
        }
        else
        {
            createButton = 0;
        }


    }

    else if(scene == 15 )
    {

        if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
        {
            backButtonSelected = 1;
        }
        else
        {
            backButtonSelected = 0;
        }

        if(mx>=windowWidth - var(20) - 160 && mx<=windowWidth - var(20) && my>= var(20) && my<=var(20)+82)
        {
            createButton = 1;
        }
        else
        {
            createButton = 0;
        }
    }

    else if(scene == 16)
    {

        if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
        {
            backButtonSelected = 1;
        }
        else
        {
            backButtonSelected = 0;
        }
    }



}





/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/

void iMouseMove(int mx, int my)
{

    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
    if(scene==0)
    {

    }

    else if(scene == 1)
    {

    }
    else if(scene ==2 )
    {

    }
    else if(scene == 3)
    {

    }
    else if(scene == 4)
    {

    }
    else if(scene ==5 )
    {

    }
    else if(scene == 6)
    {

    }
    else if(scene == 7)
    {

    }
    else if(scene ==8 )
    {

    }
    else if(scene == 9)
    {

    }
    else if(scene == 10)
    {

    }
    else if(scene ==11 )
    {

    }
    else if(scene == 12)
    {

    }

    else if(scene == 14 || scene == 15)
    {

        if(mx>leftlimit&&mx<rightlimit&&my>lowerlimit&&my<higherlimit)
        {
            if(eraserON)
                boxmap[xToArray(mx)][yToArray(my)] = 0;
            else
                boxmap[xToArray(mx)][yToArray(my)] = setboxType;
        }



    }
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/

void iMouse(int button, int state, int mx, int my)
{


    if(scene==0)
    {

    }

    else if(scene == 1)
    {

    }
    else if(scene ==2 )
    {

    }
    else if(scene == 3)
    {
        for(int i=0; i<8; i++)
        {
            if(!thereIsResume&& i == 7)
                continue;
            if(mx>=menuRedX && mx<=menuRedX + menuButtonWidth[i] + 100 )
            {
                if(my>=(i+1)*71 && my<=(i+2)*71)
                {
                    menuButtonSelected = i;
                    menuButtonEffect(i);
                }
            }
        }

    }
    else if(scene == 4)
    {

        if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {

            if(!gameplayPause)
                gameplayPause = 1;

        }


        if(gameplayPause==0)
        {
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {


                if(ball.live)
                {
                    if(!ball.launch)
                    {
                        ball.launch = 1;
                        ballLauncher();
                        //ball.dx = ball.v*cos(80*pi/180);
                        //ball.dy = ball.v*sin(80*pi/180);
                    }
                    if(shooterPaddle && !bulletTimer)
                    {

                        bulletTimer = 1;
                        bulletGenerator(paddle.x - paddle.width, paddle.y + paddle.height, paddle.width*2-bulletx);
                    }

                }




            }
        }

        else if(gameplayPause == 1)
        {


            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {
                double x = windowWidth/2;
                double y = windowHeight/2-71*3 + 71;

                for(int i = 4; i>=1; i--)
                {

                    if(mx >= x-resumeButtonWidth[i]/2-50 && mx<= x + resumeButtonWidth[i]/2+50)
                    {
                        if(my>=y && my<=y+71)
                        {
                            resumeButtonEffect(i);
                            break;
                        }
                    }

                    y = y+71;
                }
            }

        }

        if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {

        }
    }
    else if(scene ==5 )
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx >= windowWidth/2-336 && mx<= windowWidth/2-336 + 286)
            {
                if(my>= var(50) && my<= var(50) + 100 )
                {
                    overButtonEffect(1);
                }
            }

            else if(mx >= windowWidth/2+50 && mx<= windowWidth/2+50+ 286)
            {
                if(my>= var(50) && my<= var(50) + 100 )
                {
                    overButtonEffect(2);
                }
            }

        }
    }
    else if(scene == 6)
    {

    }
    else if(scene == 7)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
            {
                scene = 3;
                backButtonSelected = 0;
                nextButtonSelected = 0;
            }

            if(mx >= windowWidth/2 - 282.5 && mx<= windowWidth/2 - 465/2 - 50 + 565 && my>= windowHeight/2 + 100  && my<= windowHeight/2 + 282 )
            {
                settingsButton = 0;
                ToggleMusic();
            }
            else if(mx >= windowWidth/2 - 309 && mx<= windowWidth/2 - 518/2 - 50 + 618 && my>= windowHeight/2 -100 && my<= windowHeight/2 +82 )
            {
                restoreLevelMap();
                scene = 3;
                settingsButton = 0;
            }
            else if(mx >= windowWidth/2 - 344.5 && mx<= windowWidth/2 - 518/2 - 50 + 689 && my>= windowHeight/2 -300  && my<= windowHeight/2 -118 )
            {
                restoreHighscore();
                scene = 8;
                settingsButton = 0;
            }




        }


    }
    else if(scene ==8 )
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
            {
                scene = 3;
                backButtonSelected = 0;
                nextButtonSelected = 0;
            }
        }
    }
    else if(scene == 9)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
            {
                scene = 3;
                backButtonSelected = 0;
                nextButtonSelected = 0;
            }

            if(mx>=70 && mx<=120 && my>= windowHeight-60 && my<= windowHeight-10)
            {
                scene = 10;
                backButtonSelected = 0;
                nextButtonSelected = 0;
            }
        }

    }
    else if(scene == 10)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
            {
                scene = 9;
                backButtonSelected = 0;
                nextButtonSelected = 0;
            }
        }

    }
    else if(scene ==11 )
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
            {
                scene = 3;
                backButtonSelected = 0;
                nextButtonSelected = 0;
            }
        }

    }
    else if(scene == 12)
    {

    }


    else if(scene == 13)
    {

        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
            {
                scene = 3;
                backButtonSelected = 0;
                nextButtonSelected = 0;
            }

            else if(mx >= windowWidth/2 - 445 - var(50) && mx<= windowWidth/2 - var(50))
            {
                if(my>= windowHeight/2 - 94.5 && my<= windowHeight/2 - 94.5 + 189 )
                {
                    //printf("1\n");
                    levelmakerButtonEffect(1);

                    return;
                }
            }

            else if(mx >= windowWidth/2 + var(50)  && mx<= windowWidth/2 + var(50) + 445)
            {
                if(my>= windowHeight/2 - 94.5 && my<= windowHeight/2 - 94.5 + 189 )
                {
                    levelmakerButtonEffect(2);

                    return ;
                }
            }




        }





    }


    else if(scene == 14 || scene == 15 )
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
            {
                scene = 13;
                backButtonSelected = 0;
                nextButtonSelected = 0;
            }
        }


        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {

            if(mx>leftlimit&&mx<rightlimit&&my>lowerlimit&&my<higherlimit)
            {
                boxmap[xToArray(mx)][yToArray(my)] = setboxType;
            }

            else
            {
                for(int i=0; i<boxn; i++)
                {
                    if(mx>=var(30)+i*var(110) && mx<=var(30)+i*var(110)+boxWidth && my>=var(20) && my<=var(20)+boxHeight)  //gotta change this
                    {
                        setboxType = boxType[i];
                    }
                }
            }



            if(mx>=windowWidth - var(20) - 160 && mx<=windowWidth - var(20) && my>= var(20) && my<=var(20)+82)
            {

                int i = scene == 14 ? 1 : 2;
                createButtonEffect(i);
                return;
            }



        }

        if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            eraserON = 1;
            if(mx>=leftlimit&&mx<=rightlimit&&my>=lowerlimit&&my<=higherlimit)
            {
                boxmap[xToArray(mx)][yToArray(my)] = 0;
            }
        }
        if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
        {
            eraserON = 0;
        }





    }

    else if(scene == 16)
    {

        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=10 && mx<=60 && my>= windowHeight-60 && my<= windowHeight-10)
            {
                scene = 13;
                backButtonSelected = 0;
                nextButtonSelected = 0;
            }
        }

    }






}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    //if(key == 'q')
    //{
    //    exit(0);
    //}

    /*
    if(key == 'm' || key =='M')
    {
        ToggleMusic();
    }
    */

    /*
    if(key=='4')
    {
        scene++;
    }

    else if(key=='5')
        scene--;
        */

    if(scene==0)
    {

    }

    else if(scene == 1)
    {

    }
    else if(scene ==2 )
    {

    }
    else if(scene == 3)
    {
        if(key == 27)
        {
            scene = 12;
        }

    }
    else if(scene == 4)
    {
        if(key == 'p')
        {

            if(!gameplayPause)
                gameplayPause = 1;
            else if(gameplayPause == 1)
            {
                gameplayPause = 2;
            }

        }







        if(gameplayPause==0)
        {
            if(key == 'd')
            {
                if(paddle.x+paddle.move<=windowWidth-paddle.len)
                    paddle.x+=paddle.move;
                else
                    paddle.x = windowWidth-paddle.len;
            }
            else if(key == 'a')
            {

                if(paddle.x-paddle.move>=0 + paddle.len)
                    paddle.x-=paddle.move;
                else
                    paddle.x = 0 + paddle.len;
            }


            else if(key == ' ')
            {



                if(ball.live)
                {
                    if(!ball.launch)
                    {
                        ball.launch = 1;
                        ballLauncher();
                    }
                    if(shooterPaddle && !bulletTimer)
                    {

                        bulletTimer = 1;
                        bulletGenerator(paddle.x - paddle.width, paddle.y + paddle.height, paddle.width*2-bulletx);
                    }

                }

            }

        }

    }
    else if(scene ==5 )
    {
        if(takeHighScore)
        {


            if(key==13)
            {

                if(strlen(currentUsername)==0)
                {
                    strcpy(currentUsername, "UNKNOWN");
                }


                takeHighScore = 0;
                //scene = 3;
            }



            else if(key!='\b')
            {

                if(currentUsername_idx < maxUsernameIdx)
                {
                    currentUsername[currentUsername_idx] = key;
                    currentUsername[++currentUsername_idx] = '\0';
                }
            }

            else if(key == '\b')
            {

                if(currentUsername_idx > 0)
                {
                    currentUsername_idx--;
                    currentUsername[currentUsername_idx] = '\0';
                }

            }




        }

    }
    else if(scene == 6)
    {

    }
    else if(scene == 7)
    {

    }
    else if(scene ==8 )
    {

    }
    else if(scene == 9)
    {

    }
    else if(scene == 10)
    {

    }
    else if(scene ==11 )
    {

    }
    else if(scene == 12)
    {

    }

    else if(scene == 14 || scene == 15)
    {
        if(key=='r' || key == 'R')
        {
            clearLevelMaker();
        }
    }


    else if(scene == 16)
    {





        if(key==13)
        {

            if(strlen(editChar)==0)
            {
                strcpy(editChar, "0");
            }


            int x = atoi(editChar);
            if(x>=1 && x<= maxLevels)
            {
                strcpy(editChar,"");
                editcharIndex = 0;
                editerror = 0;
                editIndex = x;
                levelmakerButtonEffect(3);

            }

            else
            {

                strcpy(editChar,"");
                editcharIndex = 0;
                editerror = 1;
            }
        }


        else if(key>='0' && key<='9')
        {

            if(editcharIndex < editmaxIndex)
            {
                editChar[editcharIndex] = key;
                editChar[++editcharIndex] = '\0';
            }
        }

        else if(key == '\b')
        {

            if(editcharIndex > 0)
            {
                editcharIndex--;
                editChar[editcharIndex] = '\0';
            }

        }



    }


}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }

    if(scene == 4)
    {

        if(gameplayPause==0)
        {
            if(key == GLUT_KEY_RIGHT)
            {
                if(paddle.x+paddle.move<=windowWidth-paddle.len)
                    paddle.x+=paddle.move;
                else
                    paddle.x = windowWidth-paddle.len;
            }
            else if(key == GLUT_KEY_LEFT)
            {

                if(paddle.x-paddle.move>=0 + paddle.len)
                    paddle.x-=paddle.move;
                else
                    paddle.x = 0 + paddle.len;
            }
        }

    }


}


int main()
{
    //place your own initialization codes here.

    iSetTimer(20, change);
    iInitializeNew(windowWidth, windowHeight, "DX-BALL 1905066");

    return 0;
}
