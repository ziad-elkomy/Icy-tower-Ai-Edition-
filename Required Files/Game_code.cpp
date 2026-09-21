#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include<sstream>
#include <chrono>

using namespace std;
using namespace sf;
/// <global>


int windowWidth = 1345;
int windowHeight = 1020;
View camera(sf::FloatRect(0, 0, windowWidth, windowHeight));
float camspeed = 0.0;
const int numStairs = 6;
const int maxplayers = 13;
RenderWindow window(VideoMode(windowWidth, windowHeight), "ICY TOWER");
bool var = false;
const int numBackgrounds = 10;
double velocityY;
bool ismoving = 0;
int calccoins = 0;
int indexstair = 0;
bool iseasy = false;/////new
bool ismedium = false;//////new
bool ishard = false;///////new
bool iswarning = false;
int combo = 0;
int totalcombo = 0;
int difficultyIndex = 2;
bool istouchleftwall = true, istouchrightwall = true;
bool isstart = 1;
bool ispower = false;
bool is_back1 = true;
bool is_back2 = false;
bool is_wall1 = true;
bool is_wall2 = false;
bool iskeyboard = false;
bool is_ai = true;
bool is_joystick = false;
string text;
string temp;
string temp1 = temp;
enum PlayerState { Stand, Left, Right, Jump, Jump_Right, Jump_Left, Fall_Right, Fall_Left, Super_Jump };
PlayerState CurrentState = Stand;

struct Stair {
    Sprite sprite;
    int num;
    double velocitystairX;//////new
    bool flip = false;//////new
};
Stair stairs[numStairs];

struct user
{
    int totalscore;
    int highscore;
    int highfloor;
    int coins;
    struct character
    {
        bool poor = 0;
        bool patrick = 0;
    }players;
    int gameplayed;

    string name;
}person[maxplayers];
fstream file;
fstream counter;



/// </golbal>

/// <clocks>
Clock shaketime;
Clock gameClock;
Clock countdownClock;
Clock warnclock;
Clock runclock;
Clock tempt;
Clock Time_action;
Clock Time_page;
Time totalElapsedTime = Time::Zero;
Time pauseStartTime;
float Page_delay = 1.5;
float Action_delay = 0.62;
/// </clocks>

/// <sounds>
SoundBuffer jump, playbuffer, backgroundbuffer, menu, good, great, amazing, super, hurryup, menuchange, menuchoose, ring, jumppoor, jumppatrick, jumppowerr,
jumppoorpower, jumppatrickpower, startpoor, startpatrick, Warningbuf, buycharacter, flip, flippoor, flippatrick, getcoin, gameoverbuffer;

Sound jumpsound, playsound, backgroundsound, menusound, goodsound, greatsound, amazingsound, supersound, hurryupsound, changesound, choosesound, ringsound, jumppoorsound, jumppatricksound,
jumppowersound, jumppoorpowersound, jumppatrickpowersound, startpoorsound, startpatricksound, warningsound, buycharactersound, flipsound, flippoorsound, flippatricksound, getcoinsound, gameoversound;
/// </sounds>

/// <pictures>
Texture PlayerTex, truetex, squaretex, ChooseTex, lock, lock2, BackgroundTex, rightwallTex1, leftwallTex1, BackgroundTex2, rightwallTex2,
leftwallTex2, BackgroundTex3, rightwallTex3, leftwallTex3, BackgroundTex4, rightwallTex4, leftwallTex4, BackgroundTex5, rightwallTex5,
leftwallTex5, tapee, StairTex1, StairTex2, StairTex3, StairTex4, StairTex5, StartTex, clockTex, clockwiseTex, Rtthrone, Lfthrone, Bomb, Profile,
Hand, gold, silver, bronze, Coin, buyy, PipeTex, barTex, Warning, numm;


Sprite player, squarelevel[3], squaresetting[5], squaretrue[6], choose, buy,
background[8], rightwall[8], leftwall[8], startplay, lockk, lockk2,
Clock1, clockwise, rtthrone, lfthrone, bomb, profile, hand, trophies[3], tape, num, coin, Pipe, barfill, warning;

RectangleShape bar(Vector2f(40, 220));
/// </pictures>
Text txbuttons[4];

Keyboard::Key keys[4];
int numjoys[4];
string buttons_str[2][4] = { {"Right" , "Left" , "Space" , "Esc"} , {"X-pov" , "X-neg" , "Circle" , "R1"} };

/// <Texts>
Font font, font2;

/// <pause>
Text resume("Resume", font);
Text settingpause("Settings", font);
Text quit("Quit", font);
/// </pause>

/// <gameover>
Text gameover("Gameover", font);
Text finalscore("score", font);
Text numscore("Numscore", font);
Text floorofstair("Floorofstair", font);
Text floornum("Floor", font);
Text coinss("coins :", font);
Text countercoins;
Text finalbonus("Bonus", font);
Text bonusnum;
Text total("Total score", font);
Text totalnum;
Text counterText;
Text playagain("play again", font);
Text continuee("    continue \n pay 20 coin", font);
Text back("Back", font);
/// </gameover>
Text textusers[maxplayers];

Text score("Score :", font);
Text txbonus("Bouns !", font);
Text hurry("Hurry Up !", font);

Text goodtext("GOOD", font2);
Text greattext("GREAT", font2);
Text amazingtext("AMAZING", font2);
Text supertext("SUPER", font2);


Text txcombo;
/// </Texts>


void getfromfile(int& countperson);

string inputuser();

void Choose_System(bool issound, bool& endstart);

void showStartScreen(bool& end, int& countperson, bool& isedit, bool& isdelete, bool& isplay,
    bool& ishistory, int& indexuser, int& Hero, bool& issound, bool& ismusic);

void showprofile(bool& endstart, int& countperson, bool& isedit, bool& isdelete, bool& isplay,
    bool& ishistory, int& indexuser, int& Hero, bool& issound, bool& ismusic);

void setting(bool& issound, bool& ismusic, bool ispause);

void configuration();

void ranking(user person[], int& countperson, bool issound);

void showdatanumber(int n);

void controlprofile(bool& endstart, int& countperson, bool& isedit, bool& isdelete, bool& isplay,
    bool& ishistory, int& indexuser, int& Hero, bool& issound, bool& ismusic);

void addprofile(int& countperson);

void chooseplayer(bool& end, int& countperson, bool& isedit, bool& isdelete, bool& isplay,
    bool& ishistory, int& Hero, int& indexuser, bool& issound, bool& ismusic);

void decide(int n, int indexuser, int countperson, int k, bool& issound);

void difficulty(bool& isplay, bool& endstart, bool& issound);

void initializeStairs(int& number);

void movement(double jumpBoost, double playerSpeed, double& velocityX, double& velocityY, bool& onGround,
    bool& spacePressed, double& jumppower, bool& isMoving, double& ddistance, double maxplayerspeed,
    double maxJumpPower, double& runtime, int& Hero, bool& issound);

void applyPhysics(double gravity, double friction, double& velocityX, double& velocityY, bool& onGround);

void updateStairs(int& number, double& velocitystair, bool& onGround, double& velocityY, int& nextscores, int stairlevel, bool& iscoin, double& vx, bool& isthrone, int& bounds);

void Animation(double& velocityY, double& velocityX, int& Hero, bool& onGround, double jumppower, double maxJumpPower, bool& issound);

void clock_animation(bool& shake, double& velocitystair, bool& issound);

void movethrones(int& indexthrone, int& countthrone, double& velocitystair);

void movebomb(double& velocitystair, int& countbombs);

void showbonus(bool& isbonus);

void movecoins(double& velocitystair, int& countcoins);

void features(int& number, double& velocitystair, int& nlevel, int& nextscores, bool& isbomb, int& countbombs,
    bool& isthrone, int& indexthrone, int& countthrone, bool& isbonus, bool& iscoin, int& bonus, int& countcoins, int stairlevel, bool& issound);

void levels(int countbg, double& velocitystair);

void Draw(bool& shake, int& nlevel, int& nextscores, int& prevscores, int& bounds, bool& isbounds, bool& isbomb,
    bool& isthrone, int& indexthrone, int& countthrone, bool& isbonus, bool& iscoin, bool& iscontinue, int& currentnumber, int stairlevel, double& velocitystair,
    bool ispaused, bool isgameover, bool issorry, bool& issound);

void gameLoop(int& countperson);

void pause(bool& issound, bool& ismusic, bool& isPaused, int& selectedIndex, bool& isquit, bool& isresume);

void updatedata(int& bonus, int& finalscores, int& indexuser, int& countcoins);

void showGameOver(int indexuser, bool issound, bool ismusic, int nextscores, int prevscores, int bonus, int countcoins, int countperson, bool& isquit, bool& isgameover,
    bool& issorry, bool& iscontinue, int& currentnumber, int& selectedIndex);

void countdownBeforeRestart(bool& iscontinue, int& currentNumber);

void savetofile(int& countperson);

int numfromjoy();

string tojoy(int num);

int main() {
    window.setPosition(Vector2i(0, 0));
    is_joystick = Joystick::isConnected(0);
    keys[0] = Keyboard::Right;
    keys[1] = Keyboard::Left;
    keys[2] = Keyboard::Space;
    keys[3] = Keyboard::Escape;
    numjoys[0] = 10;
    numjoys[1] = 11;
    numjoys[2] = 1;
    numjoys[3] = 5;
    txbuttons[0].setString("Right");
    txbuttons[1].setString("Left");
    txbuttons[2].setString("Space");
    txbuttons[3].setString("Esc");
    for (int i = 0;i < 4;i++)
    {
        txbuttons[i].setFont(font);
        txbuttons[i].setCharacterSize(50);
        txbuttons[i].setPosition(500, 150 + 150 * i);
    }
    numm.loadFromFile("pictures/num.png");
    tapee.loadFromFile("pictures/tape.jpg");
    StartTex.loadFromFile("pictures/startplay.jpg");
    squaretex.loadFromFile("pictures/square.jpg");
    lock.loadFromFile("pictures/lock.png");
    lock2.loadFromFile("pictures/lock.png");
    truetex.loadFromFile("pictures/squaretrue.png");
    Hand.loadFromFile("pictures/hand.png");
    Profile.loadFromFile("pictures/profile.jpg");
    ChooseTex.loadFromFile("pictures/choose.png");
    buyy.loadFromFile("pictures/buy.png");
    clockTex.loadFromFile("pictures/clock.png");
    clockwiseTex.loadFromFile("pictures/clockwise.png");
    BackgroundTex.loadFromFile("pictures/background1.jpg");
    rightwallTex1.loadFromFile("pictures/rightwall1.jpg");
    leftwallTex1.loadFromFile("pictures/leftwall1.jpg");
    BackgroundTex2.loadFromFile("pictures/background2.jpg");
    rightwallTex2.loadFromFile("pictures/rightwall2.jpg");
    leftwallTex2.loadFromFile("pictures/leftwall2.jpg");
    BackgroundTex3.loadFromFile("pictures/background3.jpg");
    rightwallTex3.loadFromFile("pictures/rightwall3.jpg");
    leftwallTex3.loadFromFile("pictures/leftwall3.jpg");
    BackgroundTex4.loadFromFile("pictures/background4.jpg");
    rightwallTex4.loadFromFile("pictures/rightwall4.jpg");
    leftwallTex4.loadFromFile("pictures/leftwall4.jpg");
    BackgroundTex5.loadFromFile("pictures/background5.jpg");
    rightwallTex5.loadFromFile("pictures/rightwall5.jpg");
    leftwallTex5.loadFromFile("pictures/leftwall5.jpg");
    gold.loadFromFile("pictures/gold.png");
    silver.loadFromFile("pictures/silver.png");
    bronze.loadFromFile("pictures/pronze.png");
    StairTex1.loadFromFile("pictures/stair1.jpg");
    StairTex2.loadFromFile("pictures/stair2.png");
    StairTex3.loadFromFile("pictures/stair3.png");
    StairTex4.loadFromFile("pictures/stair4.jpg");
    StairTex5.loadFromFile("pictures/stair5.png");
    Rtthrone.loadFromFile("pictures/righttriangle.png");
    Lfthrone.loadFromFile("pictures/lefttriangle.png");
    Bomb.loadFromFile("pictures/bombs.png");
    Coin.loadFromFile("pictures/coin.png");
    PipeTex.loadFromFile("pictures/pipe.png");
    barTex.loadFromFile("pictures/fillbar.png");
    Coin.loadFromFile("pictures/coin.png");
    Warning.loadFromFile("pictures/warning.png");

    Pipe.setTexture(PipeTex);
    barfill.setTexture(barTex);
    num.setTexture(numm);
    Pipe.setPosition(25, 200);
    Pipe.setScale(2, 2);
    bar.setFillColor(Color::Black);
    bar.setPosition(65, 230);
    barfill.setPosition(42, 450);
    barfill.setScale(0.5, 0.5);
    num.setPosition(25, 441);
    num.setScale(0.26, 0.25);

    buy.setTexture(buyy);
    buy.setPosition(330, 400);
    buy.setScale(1.5, 1.3);
    buy.setColor(Color(255, 255, 255, 120));

    lockk.setTexture(lock);
    lockk.setPosition(615, 550);
    lockk.setScale(.25, .25);
    lockk2.setTexture(lock2);
    lockk2.setPosition(1130, 550);
    lockk2.setScale(.25, .25);

    for (int i = 0;i < 5;i++)
    {
        squaresetting[i].setTexture(squaretex);
        squaresetting[i].setScale(0.09, 0.09);
        squaresetting[i].setPosition(645, 130 + i * 180);
    }
    for (int i = 0;i < 3;i++)
    {
        squarelevel[i].setTexture(squaretex);
        squarelevel[i].setScale(.12, .12);
        squarelevel[i].setPosition(800 + i * 150, 430);
    }

    squaretrue[0].setTexture(truetex);
    squaretrue[0].setScale(0.33, 0.33);
    squaretrue[0].setPosition(653, 133);
    squaretrue[1].setTexture(truetex);
    squaretrue[1].setScale(0.33, 0.33);
    squaretrue[1].setPosition(653, 313);
    squaretrue[2].setTexture(truetex);
    squaretrue[2].setScale(0.33, 0.33);
    squaretrue[3].setTexture(truetex);
    squaretrue[3].setScale(0.33, 0.33);
    squaretrue[4].setTexture(truetex);
    squaretrue[4].setScale(0.33, 0.33);
    squaretrue[5].setTexture(truetex);
    squaretrue[5].setScale(0.48, 0.48);


    player.setTexture(PlayerTex);
    player.setScale(2, 2);
    player.setPosition(100, 750);
    player.setTextureRect(IntRect(0, 0, 33.4, 55));
    startplay.setTexture(StartTex);
    startplay.setScale(float(windowWidth) / startplay.getGlobalBounds().width, float(windowHeight) / startplay.getGlobalBounds().height);
    tape.setTexture(tapee);
    tape.setPosition(0, 940);
    tape.setScale(float(windowWidth) / tape.getGlobalBounds().width, .7);
    hand.setTexture(Hand);
    hand.setScale(0.7, 0.7);
    hand.setPosition(0, 20);
    profile.setTexture(Profile);
    profile.setScale(1.5, 1.2);
    Clock1.setTexture(clockTex);
    Clock1.setScale(0.25, 0.25);
    Clock1.setPosition(0, 0);
    clockwise.setTexture(clockwiseTex);
    clockwise.setPosition(65, 50);
    clockwise.setScale(0.17, 0.17);
    choose.setTexture(ChooseTex);
    choose.setScale(0.85, 1);



    // Poor.setPosition(525, 400);
    //1345,1020

    for (int i = 0; i < 8; i++) {
        if (i / 2 == 0)
        {
            background[i].setTexture(BackgroundTex);
            rightwall[i].setTexture(rightwallTex1);
            leftwall[i].setTexture(leftwallTex1);
        }
        else if (i / 2 == 1)
        {
            background[i].setTexture(BackgroundTex2);
            rightwall[i].setTexture(rightwallTex2);
            leftwall[i].setTexture(leftwallTex2);
        }
        else if (i / 2 == 2)
        {
            background[i].setTexture(BackgroundTex3);
            rightwall[i].setTexture(rightwallTex3);
            leftwall[i].setTexture(leftwallTex3);
        }
        else if (i / 2 == 3)
        {
            background[i].setTexture(BackgroundTex4);
            rightwall[i].setTexture(rightwallTex4);
            leftwall[i].setTexture(leftwallTex4);
        }
        background[i].setScale(995.00 / background[i].getGlobalBounds().width, 1020.0 / background[i].getGlobalBounds().height);
        rightwall[i].setScale(1, 1020.0 / rightwall[i].getGlobalBounds().height);
        leftwall[i].setScale(1, 1020.0 / leftwall[i].getGlobalBounds().height);
        /*else if (i / 2 == 4)
        {
            background5[i].setTexture(BackgroundTex5);
            background5[i].setScale(0.66, 0.7);
            rightwall5[i].setTexture(rightwallTex5);
            leftwall5[i].setTexture(leftwallTex5);
        }*/

    }



    trophies[0].setTexture(gold);
    trophies[1].setTexture(silver);
    trophies[2].setTexture(bronze);
    for (int i = 0;i < 3;i++)
    {
        trophies[i].setPosition(55, (i + 1) * 78);
        trophies[i].setScale(.3, .2);

    }
    bomb.setTexture(Bomb);
    bomb.setScale(.3, .3);

    coin.setTexture(Coin);
    coin.setScale(.08, .08);

    warning.setTexture(Warning);
    warning.setPosition(400, 50);
    warning.setScale(2.3, 2);
    warning.setColor(Color(255, 255, 255, 120));


    rtthrone.setTexture(Rtthrone);
    rtthrone.setScale(0.4, 0.4);

    lfthrone.setTexture(Lfthrone);
    lfthrone.setScale(0.4, 0.4);

    txcombo.setFont(font);
    txcombo.setPosition(num.getPosition().x + 50, num.getPosition().y + 20);
    txcombo.setCharacterSize(40);

    barfill.setOrigin(0, 1536);
    ////////Text
    font.loadFromFile("fonts/font.ttf");
    font2.loadFromFile("fonts/font2.ttf");
    score.setFont(font);
    score.setCharacterSize(60);
    score.setPosition(30, 900);
    score.setOutlineThickness(2);
    numscore.setCharacterSize(55);
    numscore.setPosition(200, 760);
    numscore.setOutlineThickness(2);


    resume.setFont(font);
    resume.setCharacterSize(70);
    resume.setPosition(590, 260);
    resume.setOutlineThickness(2);
    settingpause.setFont(font);
    settingpause.setCharacterSize(70);
    settingpause.setPosition(565, 390);
    settingpause.setOutlineThickness(2);
    quit.setFont(font);
    quit.setCharacterSize(70);
    quit.setPosition(610, 520);
    quit.setOutlineThickness(2);


    coinss.setCharacterSize(60);
    coinss.setOutlineThickness(2);
    countercoins.setFont(font);
    countercoins.setCharacterSize(65);
    countercoins.setOutlineThickness(2);


    gameover.setFont(font);
    gameover.setCharacterSize(200);
    gameover.setPosition(310, 0);
    gameover.setFillColor(Color(255, 215, 0));
    gameover.setOutlineThickness(5);
    back.setFont(font);
    back.setCharacterSize(65);
    back.setPosition(80, 870);
    back.setOutlineThickness(2);
    continuee.setCharacterSize(65);
    continuee.setPosition(520, 800);
    continuee.setOutlineThickness(2);
    playagain.setFont(font);
    playagain.setCharacterSize(65);
    playagain.setPosition(1020, 870);
    playagain.setOutlineThickness(2);

    finalscore.setFont(font);
    finalscore.setCharacterSize(65);
    finalscore.setPosition(300, 240);
    finalscore.setOutlineThickness(2);
    floornum.setFont(font);
    floornum.setCharacterSize(65);
    floornum.setPosition(290, 380);
    floornum.setOutlineThickness(2);
    floorofstair.setCharacterSize(65);
    floorofstair.setPosition(840, 380);
    floorofstair.setFillColor(Color::White);
    floorofstair.setOutlineThickness(2);
    finalbonus.setCharacterSize(65);
    finalbonus.setPosition(300, 520);
    finalbonus.setOutlineThickness(2);
    bonusnum.setFont(font);
    bonusnum.setCharacterSize(65);
    bonusnum.setPosition(840, 520);
    bonusnum.setOutlineThickness(2);
    total.setCharacterSize(65);
    total.setPosition(300, 660);
    total.setOutlineThickness(2);
    totalnum.setFont(font);
    totalnum.setCharacterSize(65);
    totalnum.setPosition(840, 660);
    totalnum.setOutlineThickness(2);


    txbonus.setCharacterSize(70);
    txbonus.setPosition(580, 0);
    txbonus.setFillColor(Color::White);

    hurry.setCharacterSize(90);
    hurry.setPosition(420, 0);


    goodtext.setCharacterSize(200);
    goodtext.setPosition(420, 0);
    goodtext.setFillColor(Color::Yellow);

    greattext.setCharacterSize(200);
    greattext.setPosition(420, 0);
    greattext.setFillColor(Color::Yellow);



    counterText.setFont(font);
    counterText.setCharacterSize(150);
    counterText.setFillColor(Color::White);
    counterText.setStyle(Text::Bold);
    counterText.setPosition(550, 300);


    amazingtext.setCharacterSize(200);
    amazingtext.setPosition(420, 0);
    amazingtext.setFillColor(Color::Yellow);

    supertext.setCharacterSize(200);
    supertext.setPosition(420, 0);
    supertext.setFillColor(Color::Yellow);



    jump.loadFromFile("sounds/jump.wav");
    jumpsound.setBuffer(jump);
    jumpsound.setVolume(500.0f);



    menu.loadFromFile("sounds/sound main menu.wav");
    menusound.setBuffer(menu);
    menusound.setVolume(50.0f);


    playbuffer.loadFromFile("sounds/play.wav");
    playsound.setBuffer(playbuffer);
    playsound.setVolume(200.0f);



    backgroundbuffer.loadFromFile("sounds/background.wav");
    backgroundsound.setBuffer(backgroundbuffer);
    backgroundsound.setVolume(50.0f);


    hurryup.loadFromFile("sounds/hurryup.wav");
    hurryupsound.setBuffer(hurryup);
    hurryupsound.setVolume(800.0f);


    good.loadFromFile("sounds/good.wav");
    goodsound.setBuffer(good);
    goodsound.setVolume(800.0f);

    great.loadFromFile("sounds/great.wav");
    greatsound.setBuffer(great);
    greatsound.setVolume(800.0f);

    getcoin.loadFromFile("sounds/get coin.wav");
    getcoinsound.setBuffer(getcoin);
    getcoinsound.setVolume(1000.0f);

    amazing.loadFromFile("sounds/amazing.wav");
    amazingsound.setBuffer(amazing);
    amazingsound.setVolume(800.0f);


    super.loadFromFile("sounds/super.wav");
    supersound.setBuffer(super);
    supersound.setVolume(800.0f);

    ring.loadFromFile("sounds/ring.wav");
    ringsound.setBuffer(ring);
    ringsound.setVolume(10000.0f);

    menuchange.loadFromFile("sounds/menu_change.wav");
    changesound.setBuffer(menuchange);
    changesound.setVolume(100.0f);

    menuchoose.loadFromFile("sounds/menu_choose.wav");
    choosesound.setBuffer(menuchoose);
    choosesound.setVolume(50000.0f);

    jumppoor.loadFromFile("sounds/jump vini.wav");
    jumppoorsound.setBuffer(jumppoor);
    jumppoorsound.setVolume(500.0f);

    jumppatrick.loadFromFile("sounds/jump blonde.wav");
    jumppatricksound.setBuffer(jumppatrick);
    jumppatricksound.setVolume(500.0f);

    jumppatrickpower.loadFromFile("sounds/jump blonde power.wav");
    jumppatrickpowersound.setBuffer(jumppatrickpower);
    jumppatrickpowersound.setVolume(500.0f);

    startpatrick.loadFromFile("sounds/start patrick.wav");
    startpatricksound.setBuffer(startpatrick);
    startpatricksound.setVolume(500.0f);

    startpoor.loadFromFile("sounds/start poor.wav");
    startpoorsound.setBuffer(startpoor);
    startpoorsound.setVolume(500.0f);

    Warningbuf.loadFromFile("sounds/warning.wav");
    warningsound.setBuffer(Warningbuf);
    warningsound.setVolume(500.0f);


    buycharacter.loadFromFile("sounds/buy character.wav");
    buycharactersound.setBuffer(buycharacter);
    buycharactersound.setVolume(800.0f);

    flip.loadFromFile("sounds/flip.wav");
    flipsound.setBuffer(flip);
    flipsound.setVolume(500.0f);

    flippoor.loadFromFile("sounds/flip poor.wav");
    flippoorsound.setBuffer(flippoor);
    flippoorsound.setVolume(500.0f);

    flippatrick.loadFromFile("sounds/flip patrick.wav");
    flippatricksound.setBuffer(flippatrick);
    flippatricksound.setVolume(500.0f);

    gameoverbuffer.loadFromFile("sounds/gameover.wav");
    gameoversound.setBuffer(gameoverbuffer);
    gameoversound.setVolume(500.0f);


    for (int i = 0;i < maxplayers;i++)
    {
        textusers[i].setFont(font);
        textusers[i].setCharacterSize(60);
        textusers[i].setPosition(100, (i + 1) * 70);
        textusers[i].setFillColor(Color::White);
    }

    srand(time(0));
    int countperson = 0;
    getfromfile(countperson);
    gameLoop(countperson);
    savetofile(countperson);
}

string inputuser()
{
    fstream f_temp_page;
    f_temp_page.open("files/pagetxt.txt", ios::out);
    f_temp_page << 1;
    f_temp_page.close();
    fstream file_in;
    Texture Mouse_tex;
    Mouse_tex.loadFromFile("pictures/MousePointer.png");
    Sprite Mouse_sp;
    Mouse_sp.setTexture(Mouse_tex);
    Mouse_sp.setScale(0.2, 0.2);
    float x_pos = 0.5;
    float y_pos = 0.5;
    float x_prev = 0;
    float y_prev = 0;
    int selecting = 0;
    int prev_select = 0;
    int selectedIndex = 0;
    int cols = 0;
    string name = "";
    Font font;
    font.loadFromFile("fonts/font.ttf");
    Text enter("Enter the profile name : ", font);
    enter.setFillColor(Color::White);
    enter.setCharacterSize(100);
    Text str;
    str.setFont(font);
    str.setPosition(100, 100);
    str.setCharacterSize(100);
    str.setFillColor(Color::White);
    Text txt_chars[28];
    for (int i = 0;i < 28;i++)
    {
        txt_chars[i].setFont(font);
        txt_chars[i].setCharacterSize(70);
        txt_chars[i].setPosition(10 + (i % 13) * 90, i / 13 * 60 + 600);
        txt_chars[i].setString(char(65 + i));
    }
    txt_chars[0].setFillColor(Color::Red);
    txt_chars[26].setString("Enter");
    txt_chars[27].setString("Erase");
    txt_chars[26].setPosition(300, 540);
    txt_chars[27].setPosition(600, 540);
    while (window.isOpen())
    {
        float x = Joystick::getAxisPosition(0, Joystick::X);
        float y = Joystick::getAxisPosition(0, Joystick::Y);
        file_in.open("files/positions.txt", ios::in);
        file_in >> x_pos;
        file_in >> y_pos;
        file_in >> selecting;
        file_in.close();
        cout << "X = " << x_pos << "\n";
        cout << "Y = " << y_pos << "\n";
        if (x_prev != x_pos || y_prev != y_pos)
        {
            selectedIndex = -1;
        }
        else if (x_prev == x_pos && y_prev == y_pos && selectedIndex == -1)
        {
            selectedIndex = 0;
        }
        x_prev = x_pos;
        y_prev = y_pos;
        cout << "Selecting = " << selecting << "\n";
        if (selecting == 0)
        {
            prev_select = 0;
        }
        FloatRect Mouse_rect(x_pos * windowWidth, y_pos * windowHeight, 1, 1);
        Mouse_sp.setPosition(x_pos * windowWidth, y_pos * windowHeight);
        bool exit = false;
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed)
            {
                if (event.key.code == Keyboard::Right || x > 50)
                {
                    txt_chars[selectedIndex].setFillColor(Color::White);
                    selectedIndex++;
                    if (cols == 0)
                    {
                        if (selectedIndex > 12)
                        {
                            selectedIndex = 12;
                        }
                    }
                    else if (cols == 1)
                    {
                        if (selectedIndex > 25)
                        {
                            selectedIndex = 25;
                        }
                    }
                    else if (cols == -1)
                    {
                        if (selectedIndex > 27)
                        {
                            selectedIndex = 27;
                        }
                    }
                    txt_chars[selectedIndex].setFillColor(Color::Red);
                }
                else if (event.key.code == Keyboard::Left || x < -50)
                {
                    txt_chars[selectedIndex].setFillColor(Color::White);
                    selectedIndex--;
                    if (cols == 0)
                    {
                        if (selectedIndex < 0)
                        {
                            selectedIndex = 0;
                        }
                    }
                    else if (cols == 1)
                    {
                        if (selectedIndex < 13)
                        {
                            selectedIndex = 13;
                        }

                    }
                    else if (cols == -1)
                    {
                        if (selectedIndex < 26)
                        {
                            selectedIndex = 26;
                        }
                    }
                    txt_chars[selectedIndex].setFillColor(Color::Red);
                }
                else if (event.key.code == Keyboard::Up || y < -50)
                {
                    txt_chars[selectedIndex].setFillColor(Color::White);
                    selectedIndex -= 13;
                    if (selectedIndex < 0)
                    {
                        cols = -1;
                        selectedIndex = 26;
                    }
                    else
                    {
                        cols = 0;
                    }
                    txt_chars[selectedIndex].setFillColor(Color::Red);
                }
                else if (event.key.code == Keyboard::Down || y > 50)
                {
                    txt_chars[selectedIndex].setFillColor(Color::White);
                    if (cols == -1)
                    {
                        selectedIndex = 0;
                        cols = 0;
                    }
                    else
                    {
                        selectedIndex += 13;
                        if (selectedIndex > 25)
                        {
                            selectedIndex -= 13;
                        }
                        else
                        {
                            cols = 1;
                        }
                    }

                    txt_chars[selectedIndex].setFillColor(Color::Red);
                }
                if (event.key.code == Keyboard::Enter || Joystick::isButtonPressed(0, 2))
                {
                    if (selectedIndex < 26)
                    {
                        name += char(selectedIndex + 65);
                        prev_select = 1;
                        str.setString(name);
                    }
                    else
                    {
                        if (selectedIndex == 26)
                        {
                            if (name.length() > 0)
                                exit = true;
                        }
                        else if (selectedIndex == 27)
                        {
                            if (name.length() > 0)
                            {
                                prev_select = 1;
                                name.erase(name.length() - 1, 1);
                                str.setString(name);
                            }

                        }
                    }
                }
            }
        }


        window.clear();
        window.draw(profile);
        window.draw(enter);
        window.draw(str);

        for (int i = 0;i < 28;i++)
        {
            if (Mouse_rect.intersects(txt_chars[i].getGlobalBounds()))
            {
                txt_chars[i].setFillColor(Color::Red);
                if (selecting == 1 && prev_select == 0)
                {
                    if (i < 26)
                    {
                        name += char(i + 65);
                        prev_select = 1;
                        str.setString(name);
                    }
                    else
                    {
                        if (i == 26)
                        {
                            if (name.length() > 0)
                                exit = true;
                        }
                        else if (i == 27)
                        {
                            if (name.length() > 0)
                            {
                                prev_select = 1;
                                name.erase(name.length() - 1, 1);
                                str.setString(name);
                            }

                        }
                    }
                }
            }
            else
            {
                if (i != selectedIndex)
                    txt_chars[i].setFillColor(Color::White);
            }
            window.draw(txt_chars[i]);
        }
        window.draw(Mouse_sp);
        window.display();
        if (exit)
        {
            fstream f_temp_page;
            f_temp_page.open("files/pagetxt.txt", ios::out);
            f_temp_page << 0;
            f_temp_page.close();
            break;
        }
    }

    return name;
}

void configuration()
{
    string btn_arr[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","0"
                        ,"1","2","3","4","5","6","7","8","9","Escape","L-CTRL","L-SHIFT","L-ALT","L-WINDOWS","R-CTRL","R-SHIFT","R-ALT"
                        ,"R-WINDOWS" ,"MENU","[","]",";",",",".","'","/","\\","`","=","-","SPACE","ENTER","BACKSPACE","TAB"
                        ,"PAGE-UP","PAGE-DOWN","END","HOME","INSERT","DELETE","+","-","*","/","LEFT","RIGHT","UP","DOWN"
                        ,"NUMPAD0","NUMPAD1", "NUMPAD2", "NUMPAD3", "NUMPAD4", "NUMPAD5", "NUMPAD6", "NUMPAD7", "NUMPAD8", "NUMPAD9"
                        ,"F1","F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "PAUSE" };
    bool exit = false;
    bool isinput = false;
    bool error = false;
    bool errorjoy = false;
    int selectedIndex = 0;
    int rows = 0;

    Clock temp;

    Texture Hand_Tex;
    Hand_Tex.loadFromFile("pictures/hand.png");

    Sprite Hand;
    Hand.setTexture(Hand_Tex);
    Hand.setScale(0.7, 0.7);

    Texture Profile_Tex;
    Profile_Tex.loadFromFile("pictures/profile.jpg");

    Sprite Profile;
    Profile.setTexture(Profile_Tex);
    Profile.setScale(1.5, 1.2);

    Texture alert_tex;
    alert_tex.loadFromFile("pictures/alert.png");

    Sprite alert;
    alert.setTexture(alert_tex);
    alert.setPosition(330, 400);
    alert.setScale(1.5, 1.3);
    alert.setColor(Color(255, 255, 255, 120));

    Text kbuttons("Keyboard", font);
    kbuttons.setCharacterSize(60);
    kbuttons.setPosition(500, 0);

    Text jbuttons("joystick", font);
    jbuttons.setCharacterSize(60);
    jbuttons.setPosition(900, 0);

    Text notuse("This button isn't usable\nChoose another button", font);
    notuse.setCharacterSize(50);
    notuse.setOutlineThickness(2);
    notuse.setPosition(360, 480);
    notuse.setFillColor(Color(255, 215, 0));

    Text erjoy("Error! joystick isn't activated", font);
    erjoy.setCharacterSize(50);
    erjoy.setOutlineThickness(2);
    erjoy.setPosition(360, 480);
    erjoy.setFillColor(Color(255, 215, 0));


    Text txbuttons[2][4];
    for (int i = 0;i < 2;i++)
    {
        for (int j = 0;j < 4;j++)
        {
            txbuttons[i][j].setFont(font);
            txbuttons[i][j].setCharacterSize(60);
            txbuttons[i][j].setString(buttons_str[i][j]);
            txbuttons[i][j].setPosition(500 + 400 * i, 150 * j + 150);
        }
    }

    Text basic[4];
    string basic_str[4] = { "move-right" , "move-left" , "jump" , "pause" };
    for (int i = 0;i < 4;i++)
    {
        basic[i].setFont(font);
        basic[i].setCharacterSize(60);
        basic[i].setString(basic_str[i]);
        basic[i].setPosition(150, 150 * i + 150);
    }
    Hand.setPosition(50, 150);
    txbuttons[0][0].setFillColor(Color::Green);
    while (window.isOpen())
    {
        is_joystick = Joystick::isConnected(0);
        float y = Joystick::getAxisPosition(0, Joystick::Y);
        float x = Joystick::getAxisPosition(0, Joystick::X);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed)
            {
                if (isinput)
                {
                    if (rows == 0)
                    {
                        buttons_str[0][selectedIndex] = btn_arr[int(event.key.code)];
                        txbuttons[0][selectedIndex].setString(btn_arr[int(event.key.code)]);
                        keys[selectedIndex] = Keyboard::Key(event.key.code);
                    }
                    else if (rows == 1)
                    {
                        int choice = numfromjoy();
                        if (choice >= 0 && choice <= 13)
                        {
                            buttons_str[1][selectedIndex] = tojoy(choice);
                            txbuttons[1][selectedIndex].setString(tojoy(choice));
                            numjoys[selectedIndex] = choice;
                        }
                        else
                        {
                            isinput = true;
                            error = true;
                            break;
                        }
                    }
                    isinput = false;
                    error = false;
                    for (int i = 0;i < 4;i++)
                    {
                        if (i != selectedIndex)
                        {
                            if (txbuttons[rows][selectedIndex].getString() == txbuttons[rows][i].getString())
                            {
                                txbuttons[rows][selectedIndex].setString("....");
                                isinput = true;
                                error = true;
                                temp.restart();
                                break;
                            }
                        }
                    }

                }
                else
                {
                    if (event.key.code == Keyboard::Up || (y < -50))
                    {
                        txbuttons[rows][selectedIndex].setFillColor(Color::White);
                        selectedIndex--;
                        if (selectedIndex < 0)
                            selectedIndex = 3;
                        txbuttons[rows][selectedIndex].setFillColor(Color::Green);
                        Hand.setPosition(50, 150 * selectedIndex + 150);
                    }
                    else if (event.key.code == Keyboard::Down || (y > 50))
                    {
                        txbuttons[rows][selectedIndex].setFillColor(Color::White);
                        selectedIndex++;
                        if (selectedIndex > 3)
                            selectedIndex = 0;
                        txbuttons[rows][selectedIndex].setFillColor(Color::Green);
                        Hand.setPosition(50, 150 * selectedIndex + 150);
                    }
                    else if (event.key.code == Keyboard::Right || (x > 50))
                    {
                        txbuttons[rows][selectedIndex].setFillColor(Color::White);
                        rows++;
                        if (rows > 1)
                            rows = 0;
                        txbuttons[rows][selectedIndex].setFillColor(Color::Green);

                    }
                    else if (event.key.code == Keyboard::Left || (x < -50))
                    {
                        txbuttons[rows][selectedIndex].setFillColor(Color::White);
                        rows--;
                        if (rows < 0)
                            rows = 1;
                        txbuttons[rows][selectedIndex].setFillColor(Color::Green);

                    }
                    else if (event.key.code == Keyboard::Enter || (Joystick::isButtonPressed(0, 2)))
                    {
                        if (rows == 1 && !is_joystick)
                        {
                            isinput = false;
                            errorjoy = true;
                            temp.restart();
                        }
                        else
                        {
                            txbuttons[rows][selectedIndex].setString("....");
                            isinput = true;
                        }

                    }
                    else if ((event.key.code == Keyboard::Escape || (Joystick::isButtonPressed(0, 4))) && !isinput)
                    {
                        exit = true;
                    }
                }

            }
        }


        window.clear();
        window.draw(Profile);
        window.draw(Hand);
        window.draw(kbuttons);
        window.draw(jbuttons);
        for (int i = 0;i < 4;i++)
        {
            window.draw(basic[i]);
            for (int j = 0;j < 2;j++)
                window.draw(txbuttons[j][i]);
        }
        if (error && temp.getElapsedTime().asSeconds() < 3)
        {
            window.draw(alert);
            window.draw(notuse);
        }
        else if (errorjoy && temp.getElapsedTime().asSeconds() < 3)
        {
            window.draw(alert);
            window.draw(erjoy);
        }
        window.display();
        if (exit)
        {
            break;
        }
    }
}

string tojoy(int num)
{
    switch (num)
    {
    case 0:
        return "triangle";
    case 1:
        return "circle";
    case 2:
        return "cross";
    case 3:
        return "square";
    case 4:
        return "L1";
    case 5:
        return "R1";
    case 6:
        return "L2";
    case 7:
        return "R2";
    case 8:
        return "select";
    case 9:
        return "start";
    case 10:
        return "X_pov";
    case 11:
        return "X_neg";
    case 12:
        return "Y_pov";
    case 13:
        return "Y_neg";
    }
}

int numfromjoy()
{
    float x = Joystick::getAxisPosition(0, Joystick::X);
    float y = Joystick::getAxisPosition(0, Joystick::Y);
    if (y < -50)
    {
        return 12;
    }
    else if (y > 50)
    {
        return 13;
    }
    else if (x > 50)
    {
        return 10;
    }
    else if (x < -50)
    {
        return 11;
    }
    for (int i = 0;i <= 9;i++)
    {
        if (Joystick::isButtonPressed(0, i))
        {
            return i;
        }
    }
    return -1;
}

void getfromfile(int& countperson)
{
    counter.open("files/file counter.txt", ios::in);
    file.open("files/file history.txt", ios::in);
    counter >> countperson;
    for (int i = 0;i < countperson;i++)
    {

        getline(file, person[i].name);
        textusers[i].setString(person[i].name);

        file >> person[i].totalscore;

        file >> person[i].highscore;

        file >> person[i].highfloor;

        file >> person[i].gameplayed;

        file >> person[i].coins;

        file >> person[i].players.poor;

        file >> person[i].players.patrick;

        file.ignore(1, '\n');
    }
    file.close();
    counter.close();
}

void addprofile(int& countperson)
{
    Text txlimit("You Have Limited The Number of Users", font);
    txlimit.setCharacterSize(70);
    txlimit.setPosition(200, 300);
    if (countperson < maxplayers)
    {
        person[countperson].name = inputuser();
        textusers[countperson].setString(person[countperson].name);
        person[countperson].totalscore = 0;
        person[countperson].highscore = 0;
        person[countperson].highfloor = 0;
        person[countperson].gameplayed = 0;
        person[countperson].coins = 0;
        person[countperson].players.poor = 0;
        person[countperson].players.patrick = 0;
        countperson++;
        savetofile(countperson);
    }
    else
    {
        bool exit = false;
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed || event.type == Event::JoystickButtonPressed)
                {
                    if (event.key.code == Keyboard::Escape || Joystick::isButtonPressed(0, 4))
                    {
                        exit = true;
                    }
                }
            }
            window.clear();
            window.draw(profile);
            window.draw(txlimit);
            window.display();
            if (exit)
            {
                break;
            }
        }
    }
}

void Choose_System(bool issound, bool& endstart)
{
    bool exit = false;
    bool err_joy = false;
    Clock temp;
    int selectedIndex = 0;
    const int num_of_system = 3;
    Text system_txt[num_of_system];
    string system_str[num_of_system] = { "Keyboard" , "Ai" , "Joystick" };
    Texture Key_tex, Ai_tex, Joy_tex;

    Key_tex.loadFromFile("pictures/keyboard.png");
    Ai_tex.loadFromFile("pictures/hand_ai.png");
    Joy_tex.loadFromFile("pictures/joystick.png");
    Sprite sprites[num_of_system];

    sprites[0].setTexture(Key_tex);
    sprites[1].setTexture(Ai_tex);
    sprites[2].setTexture(Joy_tex);
    for (int i = 0;i < num_of_system;i++)
    {
        sprites[i].setPosition(i * 400 + 100, 300);
        system_txt[i].setFont(font);
        system_txt[i].setCharacterSize(40);
        system_txt[i].setPosition(i * 400 + 100, 700);
        system_txt[i].setString(system_str[i]);
    }
    system_txt[0].setFillColor(Color::Red);
    system_txt[0].setScale(2.5, 2.5);

    Texture alert_tex;
    alert_tex.loadFromFile("pictures/alert.png");

    Sprite alert;
    alert.setTexture(alert_tex);
    alert.setPosition(330, 400);
    alert.setScale(1.5, 1.3);
    alert.setColor(Color(255, 255, 255, 120));

    Text erjoy("Error! joystick isn't activated", font);
    erjoy.setCharacterSize(50);
    erjoy.setOutlineThickness(2);
    erjoy.setPosition(360, 480);
    erjoy.setFillColor(Color(255, 215, 0));

    float x = 0;
    while (window.isOpen())
    {
        is_joystick = Joystick::isConnected(0);
        x = Joystick::getAxisPosition(0, Joystick::X);
        if (Time_page.getElapsedTime().asSeconds() > Page_delay)
        {
            ifstream file("files/gesture.txt");
            getline(file, text);
            if (text == "player one")
            {
                selectedIndex = 0;
                system_txt[2].setScale(1, 1);
                system_txt[2].setFillColor(Color::White);
                system_txt[1].setScale(1, 1);
                system_txt[1].setFillColor(Color::White);
                system_txt[0].setScale(2.5, 2.5);
                system_txt[0].setFillColor(Color::Red);
            }
            else if (text == "player two")
            {
                selectedIndex = 1;
                system_txt[2].setScale(1, 1);
                system_txt[2].setFillColor(Color::White);
                system_txt[0].setScale(1, 1);
                system_txt[0].setFillColor(Color::White);
                system_txt[1].setScale(2.5, 2.5);
                system_txt[1].setFillColor(Color::Red);
            }
            else if (text == "J")
            {
                selectedIndex = 2;
                system_txt[1].setScale(1, 1);
                system_txt[1].setFillColor(Color::White);
                system_txt[0].setScale(1, 1);
                system_txt[0].setFillColor(Color::White);
                system_txt[2].setScale(2.5, 2.5);
                system_txt[2].setFillColor(Color::Red);
            }
            if (text == "s" && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                Time_action.restart();
                Time_page.restart();
                if (!issound) {
                    choosesound.stop();
                }
                else
                {
                    choosesound.play();
                }
                if (selectedIndex == 0)
                {
                    iskeyboard = true;
                    is_ai = false;
                    is_joystick = false;
                    exit = true;
                    endstart = true;
                }
                else if (selectedIndex == 1)
                {
                    iskeyboard = false;
                    is_ai = true;
                    is_joystick = false;
                    exit = true;
                    endstart = true;
                }
                else if (selectedIndex == 2)
                {
                    if (is_joystick)
                    {
                        iskeyboard = false;
                        is_ai = false;
                        is_joystick = true;
                        exit = true;
                        endstart = true;
                    }
                    else
                    {
                        temp.restart();
                        err_joy = true;
                    }

                }
            }
            else if (text == "R" && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                exit = true;
                endstart = false;
                Time_page.restart();
                Time_action.restart();
            }
        }
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed) {
                if (event.key.code == Keyboard::Left || x < -50) {
                    system_txt[selectedIndex].setScale(1, 1);
                    system_txt[selectedIndex].setFillColor(Color::White);
                    selectedIndex--;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex < 0) selectedIndex = num_of_system - 1;
                    system_txt[selectedIndex].setScale(2.5, 2.5);
                    system_txt[selectedIndex].setFillColor(Color::Red);
                }
                else if (event.key.code == Keyboard::Right || x > 50) {
                    system_txt[selectedIndex].setFillColor(Color::White);
                    system_txt[selectedIndex].setScale(1, 1);
                    selectedIndex++;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex > num_of_system - 1) selectedIndex = 0;
                    system_txt[selectedIndex].setScale(2.5, 2.5);
                    system_txt[selectedIndex].setFillColor(Color::Red);
                }
                else if (event.key.code == Keyboard::Enter || Joystick::isButtonPressed(0, 2)) {

                    if (!issound) {
                        choosesound.stop();
                    }
                    else
                    {
                        choosesound.play();
                    }
                    if (selectedIndex == 0)
                    {
                        iskeyboard = true;
                        is_ai = false;
                        is_joystick = false;
                        exit = true;
                        endstart = true;
                    }
                    else if (selectedIndex == 1)
                    {
                        iskeyboard = false;
                        is_ai = true;
                        is_joystick = false;
                        exit = true;
                        endstart = true;
                    }
                    else
                    {
                        if (is_joystick)
                        {
                            iskeyboard = false;
                            is_ai = false;
                            is_joystick = true;
                            exit = true;
                            endstart = true;
                        }
                        else
                        {
                            temp.restart();
                            err_joy = true;
                        }
                    }

                }
                else if (event.key.code == Keyboard::Escape || Joystick::isButtonPressed(0, 4))
                {
                    exit = true;
                    endstart = false;
                }
            }
        }
        window.clear();
        window.draw(profile);
        for (int i = 0;i < num_of_system;i++)
        {
            window.draw(sprites[i]);
            window.draw(system_txt[i]);
        }
        if (err_joy && temp.getElapsedTime().asSeconds() < 3)
        {
            window.draw(alert);
            window.draw(erjoy);
        }
        window.display();
        if (exit)
        {
            break;
        }
    }
}

void Show_Tutorial()
{
    string temp_str = to_string(1) + "  OF  4";
    Text txt_str;
    txt_str.setFont(font);
    txt_str.setPosition(600, 870);
    txt_str.setString(temp_str);
    /// <instructions>
    string txts[4] = { " HELP HERO TO CLIMB THE TOWER"," AVOID DANGEROUS THINGS"," COLLECT COINS TO BUY CHARACTERS" };
    Texture lfttriatex, righttriatex;
    Texture tut_ai_tex, tut_keyboard_tex, tut_joy_tex;
    lfttriatex.loadFromFile("pictures/triangle.png");
    righttriatex.loadFromFile("pictures/triangle1.png");
    tut_ai_tex.loadFromFile("pictures/tutorial_ai.png");
    tut_keyboard_tex.loadFromFile("pictures/keyboard_tut.png");
    tut_joy_tex.loadFromFile("pictures/joy_tut.png");
    Sprite lefttria, righttria, tut_ai, tut_keyboard, tut_joy;
    lefttria.setTexture(lfttriatex);
    righttria.setTexture(righttriatex);
    righttria.setPosition(windowWidth - righttria.getGlobalBounds().width + 124, windowHeight / 2);
    lefttria.setPosition(0, windowHeight / 2);
    righttria.setScale(0.3, 0.3);
    lefttria.setScale(0.3, 0.3);
    tut_ai.setTexture(tut_ai_tex);
    tut_ai.setScale(windowWidth / tut_ai.getGlobalBounds().width, windowHeight / tut_ai.getGlobalBounds().height);
    tut_keyboard.setTexture(tut_keyboard_tex);
    tut_keyboard.setScale(windowWidth / tut_keyboard.getGlobalBounds().width, windowHeight / tut_keyboard.getGlobalBounds().height);
    tut_joy.setTexture(tut_joy_tex);
    tut_joy.setScale(windowWidth / tut_joy.getGlobalBounds().width, windowHeight / tut_joy.getGlobalBounds().height);
    int selectedIndex = 0;
    Text rules[4];
    for (int i = 0;i < 4;i++)
    {
        rules[i].setFont(font);
        rules[i].setString(txts[i]);
        rules[i].setCharacterSize(80);
        rules[i].setPosition(100, 80 + 200 * i);
        rules[i].setOutlineThickness(2);
    }
    bool exit = false;
    /// </instructions>
    float x = 0;
    float y = 0;
    while (window.isOpen()) {
        x = Joystick::getAxisPosition(0, Joystick::X);
        if (Time_page.getElapsedTime().asSeconds() > Page_delay && is_ai)
        {
            ifstream file("files/gesture.txt");
            string text = "";
            getline(file, text);


            bool isESCAPE = false;
            // Only update if text changed
            if (temp != text)
            {
                vector<string> words;
                stringstream ss(text);
                string word;
                while (ss >> word)
                    words.push_back(word);

                // reset buttons


                for (auto& w : words)
                {
                    if (w == "u" && Time_action.getElapsedTime().asSeconds() > Action_delay + 0.5)
                    {
                        selectedIndex++;
                        if (selectedIndex > 3)
                        {
                            selectedIndex = 0;
                        }
                        temp_str = to_string(selectedIndex + 1) + "  OF  4";
                        txt_str.setString(temp_str);
                        Time_action.restart();
                    }
                    else if (w == "d" && Time_action.getElapsedTime().asSeconds() > Action_delay + 0.5)
                    {
                        selectedIndex--;
                        if (selectedIndex < 0)
                        {
                            selectedIndex = 3;
                        }
                        temp_str = to_string(selectedIndex + 1) + "  OF  4";
                        txt_str.setString(temp_str);
                        Time_action.restart();
                    }
                    if (w == "R") isESCAPE = true;
                }// left
                cout << text << endl;
                temp = text;
            }
            if (isESCAPE) {
                Time_page.restart();
                break;
            }
            file.close();

        }

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed)
            {
                if (event.key.code == Keyboard::Right || x > 50)
                {
                    selectedIndex++;
                    if (selectedIndex > 3)
                    {
                        selectedIndex = 0;
                    }
                    temp_str = to_string(selectedIndex + 1) + "  OF  4";
                    txt_str.setString(temp_str);
                }
                else if (event.key.code == Keyboard::Left || x < -50)
                {
                    selectedIndex--;
                    if (selectedIndex < 0)
                    {
                        selectedIndex = 3;
                    }
                    temp_str = to_string(selectedIndex + 1) + "  OF  4";
                    txt_str.setString(temp_str);

                }
                else if (event.key.code == Keyboard::Escape || Joystick::isButtonPressed(0, 4))
                {
                    exit = true;
                }
            }

        }
        window.clear();
        if (selectedIndex == 0)
        {
            window.draw(profile);
            for (int i = 0;i < 4;i++)
            {
                window.draw(rules[i]);
            }
        }
        else if (selectedIndex == 1)
        {
            window.draw(tut_keyboard);
        }
        else if (selectedIndex == 2)
        {
            window.draw(tut_ai);
        }
        else if (selectedIndex == 3)
        {
            window.draw(tut_joy);
        }
        window.draw(righttria);
        window.draw(lefttria);
        window.draw(txt_str);

        window.display();
        if (exit)
        {
            break;
        }
    }
}

void controlprofile(bool& endstart, int& countperson, bool& isedit, bool& isdelete,
    bool& isplay, bool& ishistory, int& indexuser, int& Hero, bool& issound, bool& ismusic)
{
    int selectedIndex = 0;
    bool exit = false;
    bool end = false;
    /// <profile>
    string txts[3] = { "Add profile" ,"Edit profile","Delete profile" };
    Text operates[3];
    for (int i = 0;i < 3;i++)
    {
        operates[i].setFont(font);
        operates[i].setString(txts[i]);
        operates[i].setCharacterSize(60);
        operates[i].setPosition(400, 200 * i + 200);
    }
    /// </profile>
    hand.setPosition(300, 200);
    operates[0].setFillColor(Color::Red);
    while (window.isOpen())
    {
        if (Time_page.getElapsedTime().asSeconds() > Page_delay && is_ai)
        {
            bool isUP = false;
            bool isDOWN = false;
            bool isSELECT = false;
            bool isESCAPE = false;
            ifstream file("files/gesture.txt");
            string text = "";
            getline(file, text);
            file.close();

            // Only update if text changed
            if (temp1 != text)
            {
                vector<string> words;
                stringstream ss(text);
                string word;
                while (ss >> word)
                    words.push_back(word);

                // reset buttons


                for (auto& w : words)
                {
                    if (w == "u") isUP = true;   // left
                    else if (w == "d") isDOWN = true; // right
                    if (w == "s") isSELECT = true;
                    if (w == "R") isESCAPE = true; // escape
                }

                cout << text << endl;
                temp1 = text;
            }

            if (isUP && Time_action.getElapsedTime().asSeconds() > Action_delay)
            {
                operates[selectedIndex].setFillColor(Color::White);
                selectedIndex--;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                if (selectedIndex < 0) selectedIndex = 2;
                hand.setPosition(300, 190 * selectedIndex + 200);
                operates[selectedIndex].setFillColor(Color::Red);
                Time_action.restart();
            }
            else if (isDOWN && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                operates[selectedIndex].setFillColor(Color::White);
                selectedIndex++;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                if (selectedIndex > 2) selectedIndex = 0;
                hand.setPosition(300, 190 * selectedIndex + 200);
                operates[selectedIndex].setFillColor(Color::Red);
                Time_action.restart();
            }
            if (isSELECT && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                Time_action.restart();
                Time_page.restart();
                if (!issound) {
                    choosesound.stop();
                }
                else
                {
                    choosesound.play();
                }
                if (selectedIndex == 0)
                {
                    addprofile(countperson);
                }
                else if (selectedIndex == 1)
                {
                    isedit = true;
                    showprofile(endstart, countperson, isedit, isdelete, isplay, ishistory,
                        indexuser, Hero, issound, ismusic);
                }
                else if (selectedIndex == 2)
                {
                    isdelete = true;
                    showprofile(endstart, countperson, isedit, isdelete, isplay, ishistory,
                        indexuser, Hero, issound, ismusic);
                }
                hand.setPosition(300, 190 * selectedIndex + 200);

            }
            if (isESCAPE && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                exit = true;
                Time_action.restart();
                Time_page.restart();
                break;
            }
        }



        Event event;
        while (window.pollEvent(event))
        {
            float y = Joystick::getAxisPosition(0, Joystick::Y);
            if (event.type == Event::Closed)
            {
                window.close();
            }

            else if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed) {
                if (event.key.code == Keyboard::Down || y > 50)
                {
                    operates[selectedIndex].setFillColor(Color::White);
                    selectedIndex++;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex > 2) selectedIndex = 0;
                    hand.setPosition(300, 190 * selectedIndex + 200);
                    operates[selectedIndex].setFillColor(Color::Red);
                }

                else if (event.key.code == Keyboard::Up || y < -50)
                {
                    operates[selectedIndex].setFillColor(Color::White);
                    selectedIndex--;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex < 0) selectedIndex = 2;
                    hand.setPosition(300, 190 * selectedIndex + 200);
                    operates[selectedIndex].setFillColor(Color::Red);
                }

                else if (event.key.code == Keyboard::Enter || Joystick::isButtonPressed(0, 2))
                {
                    if (!issound) {
                        choosesound.stop();
                    }
                    else
                    {
                        choosesound.play();
                    }
                    if (selectedIndex == 0)
                    {
                        addprofile(countperson);
                    }
                    else if (selectedIndex == 1)
                    {
                        isedit = true;
                        showprofile(endstart, countperson, isedit, isdelete, isplay, ishistory,
                            indexuser, Hero, issound, ismusic);
                    }
                    else if (selectedIndex == 2)
                    {
                        isdelete = true;
                        showprofile(endstart, countperson, isedit, isdelete, isplay, ishistory,
                            indexuser, Hero, issound, ismusic);
                    }
                    hand.setPosition(300, 190 * selectedIndex + 200);
                }
                else if (event.key.code == Keyboard::Escape || Joystick::isButtonPressed(0, 4))
                {
                    exit = true;
                    break;
                }
            }
        }
        window.clear();
        window.draw(profile);
        window.draw(hand);
        for (int i = 0;i < 3;i++)
        {
            window.draw(operates[i]);
        }
        window.display();
        if (exit)
        {
            break;
        }
    }
}

void showprofile(bool& endstart, int& countperson, bool& isedit, bool& isdelete, bool& isplay,
    bool& ishistory, int& indexuser, int& Hero, bool& issound, bool& ismusic)
{
    Text txchoose("Choose the profile : ", font);
    txchoose.setCharacterSize(60);
    txchoose.setPosition(200, 0);
    txchoose.setFillColor(Color::White);
    Text txaddfirst("No profile is found\nplease add profile first", font);
    txaddfirst.setCharacterSize(60);
    txaddfirst.setPosition(300, 100);
    txaddfirst.setFillColor(Color::White);
    Text txnoprofile("No profile is found\nplease press Enter to add profile", font);
    txnoprofile.setCharacterSize(60);
    txnoprofile.setPosition(300, 100);
    txnoprofile.setFillColor(Color::White);
    int selectedIndex = 0;
    bool exit = false;
    while (window.isOpen())
    {
        if (Time_page.getElapsedTime().asSeconds() > Page_delay && is_ai)
        {
            bool isUP = false;
            bool isDOWN = false;
            bool isSELECT = false;
            bool isESCAPE = false;
            ifstream file("files/gesture.txt");
            string text = "";
            getline(file, text);
            file.close();

            // Only update if text changed
            if (temp1 != text)
            {
                vector<string> words;
                stringstream ss(text);
                string word;
                while (ss >> word)
                    words.push_back(word);

                // reset buttons


                for (auto& w : words)
                {
                    if (w == "u") isUP = true;   // left
                    else if (w == "d") isDOWN = true; // right
                    if (w == "s") isSELECT = true; // jump
                    if (w == "R") isESCAPE = true; // escape
                }

                cout << text << endl;
                temp1 = text;
            }

            if (isUP && Time_action.getElapsedTime().asSeconds() > Action_delay)
            {
                selectedIndex--;
                if (selectedIndex < 0) selectedIndex = countperson - 1;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                Time_action.restart();
            }
            else if (isDOWN && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                selectedIndex++;
                if (selectedIndex > countperson - 1) selectedIndex = 0;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                Time_action.restart();
            }
            if (isSELECT && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                Time_page.restart();
                Time_action.restart();
                if (!issound) {
                    choosesound.stop();
                }
                else
                {
                    choosesound.play();
                }
                if (isplay)
                {
                    if (countperson == 0)
                    {
                        addprofile(countperson);
                    }
                    else
                    {
                        exit = true;
                        endstart = true;
                    }
                }
                else if (ishistory)
                {
                    if (countperson > 0)
                    {
                        showdatanumber(selectedIndex);
                    }


                }
                else if (isedit)
                {
                    if (countperson > 0)
                    {
                        person[selectedIndex].name = inputuser();
                        textusers[selectedIndex].setString(person[selectedIndex].name);
                        savetofile(countperson);
                    }

                }
                else if (isdelete)
                {
                    if (countperson > 0)
                    {
                        for (int i = selectedIndex;i < countperson - 1;i++)
                        {
                            person[i].name = person[i + 1].name;
                            textusers[i].setString(person[i].name);
                            person[i].totalscore = person[i + 1].totalscore;
                            person[i].highscore = person[i + 1].highscore;
                            person[i].highfloor = person[i + 1].highfloor;
                            person[i].gameplayed = person[i + 1].gameplayed;
                            person[i].coins = person[i + 1].coins;


                        }
                        if (selectedIndex > 0)
                        {
                            selectedIndex--;
                        }
                        countperson--;
                        savetofile(countperson);
                    }
                }


                break;
            }
            if (isESCAPE) {
                exit = true;
                endstart = false;
                isplay = false;
                ishistory = false;
                isedit = false;
                isdelete = false;
                Time_page.restart();
                break;
            }
        }



        Event event;
        while (window.pollEvent(event))
        {
            float y = Joystick::getAxisPosition(0, Joystick::Y);
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed) {

                if (event.key.code == Keyboard::Down || y > 50)
                {
                    selectedIndex++;
                    if (selectedIndex > countperson - 1) selectedIndex = 0;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                }

                else if (event.key.code == Keyboard::Up || y < -50)
                {
                    selectedIndex--;
                    if (selectedIndex < 0) selectedIndex = countperson - 1;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                }

                else if (event.key.code == Keyboard::Enter || Joystick::isButtonPressed(0, 2))
                {
                    if (!issound) {
                        choosesound.stop();
                    }
                    else
                    {
                        choosesound.play();
                    }
                    if (isplay)
                    {
                        if (countperson == 0)
                        {
                            addprofile(countperson);
                        }
                        else
                        {
                            exit = true;
                            endstart = true;
                        }
                    }
                    else if (ishistory)
                    {
                        if (countperson > 0)
                        {
                            showdatanumber(selectedIndex);
                        }


                    }
                    else if (isedit)
                    {
                        if (countperson > 0)
                        {
                            person[selectedIndex].name = inputuser();
                            textusers[selectedIndex].setString(person[selectedIndex].name);
                            savetofile(countperson);
                        }

                    }
                    else if (isdelete)
                    {
                        if (countperson > 0)
                        {
                            for (int i = selectedIndex;i < countperson - 1;i++)
                            {
                                person[i].name = person[i + 1].name;
                                textusers[i].setString(person[i].name);
                                person[i].totalscore = person[i + 1].totalscore;
                                person[i].highscore = person[i + 1].highscore;
                                person[i].highfloor = person[i + 1].highfloor;
                                person[i].gameplayed = person[i + 1].gameplayed;
                                person[i].coins = person[i + 1].coins;


                            }
                            if (selectedIndex > 0)
                            {
                                selectedIndex--;
                            }
                            countperson--;
                            savetofile(countperson);
                        }
                    }


                    break;
                }
                else if (event.key.code == Keyboard::Escape || Joystick::isButtonPressed(0, 4))
                {
                    exit = true;
                    endstart = false;
                    isplay = false;
                    ishistory = false;
                    isedit = false;
                    isdelete = false;
                    break;
                }
            }
        }
        window.clear();
        window.draw(profile);
        if (countperson == 0)
        {
            if (isplay)
                window.draw(txnoprofile);
            else
                window.draw(txaddfirst);

        }
        else
        {
            window.draw(txchoose);
            hand.setPosition(30, textusers[selectedIndex].getPosition().y);
            for (int i = 0;i < countperson;i++)
            {
                window.draw(textusers[i]);
            }
            window.draw(hand);
        }
        window.display();
        if (exit && endstart)
        {
            indexuser = selectedIndex;
            break;
        }
        else if (exit && !endstart)
        {
            break;
        }
    }
}

void showdatanumber(int n)
{
    /// <History>
    Text textusers[maxplayers];
    Text txprofilename;
    txprofilename.setFont(font);
    txprofilename.setCharacterSize(60);
    txprofilename.setPosition(300, 0);
    txprofilename.setFillColor(Color::White);
    Text txdata("Total score : \n\nHigh score : \n\nHigh floor : \n\nGames played : \n\nyour coins :", font);
    txdata.setCharacterSize(60);
    txdata.setPosition(100, 120);
    txdata.setFillColor(Color::White);
    Text txnumbers;
    txnumbers.setFont(font);
    txnumbers.setCharacterSize(60);
    txnumbers.setPosition(500, 120);
    txnumbers.setFillColor(Color::White);
    Text txrank("Press enter to show data \t\t\thigh score :", font);
    txrank.setCharacterSize(60);
    txrank.setPosition(70, 0);
    txrank.setFillColor(Color(100, 100, 100));
    /// </History>

    bool exit = false;
    while (window.isOpen())
    {
        if (Time_page.getElapsedTime().asSeconds() > Page_delay && is_ai)
        {
            ifstream file("files/gesture.txt");
            string text = "";
            getline(file, text);
            file.close();
            bool isESCAPE = false;

            // Only update if text changed
            if (temp != text)
            {
                vector<string> words;
                stringstream ss(text);
                string word;
                while (ss >> word)
                    words.push_back(word);

                // reset buttons


                for (auto& w : words)
                {
                    if (w == "R") isESCAPE = true;
                }// left
                cout << text << endl;
                temp = text;
            }
            if (isESCAPE && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                Time_action.restart();
                Time_page.restart();
                break;
            }
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed || event.type == Event::JoystickButtonPressed)
            {
                if (event.key.code == Keyboard::Escape || Joystick::isButtonPressed(0, 4))
                {
                    exit = true;
                }
            }

        }
        window.clear();
        window.draw(profile);
        txprofilename.setString("Profile name : " + person[n].name);
        window.draw(txdata);
        txnumbers.setString(to_string(person[n].totalscore) + "\n\n" + to_string(person[n].highscore) +
            "\n\n" + to_string(person[n].highfloor) + "\n\n" + to_string(person[n].gameplayed) + "\n\n" + to_string(person[n].coins));
        window.draw(txprofilename);
        window.draw(txnumbers);
        window.display();
        if (exit)
        {
            break;
        }
    }

}

void setting(bool& issound, bool& ismusic, bool ispause)
{
    static Clock temp;
    bool starting = true;
    bool errjoy = false;
    /// <settigns>
    string txts[5] = { "Sound","Music","AI","configuration Keyboard" };
    int elements = 4;
    if (ispause)
    {
        txts[3] = "Keyboard";
        txts[4] = "Joystick";
        elements++;
    }
    Text settingselements[5];
    for (int i = 0;i < elements;i++)
    {
        settingselements[i].setFont(font);
        settingselements[i].setString(txts[i]);
        settingselements[i].setCharacterSize(60);
        settingselements[i].setOutlineThickness(2);
        settingselements[i].setStyle(Text::Italic);
        settingselements[i].setPosition(430, 120 + i * 180);
    }
    Text nojoystick("Joystick isn't connected !", font);
    nojoystick.setCharacterSize(50);
    nojoystick.setOutlineThickness(2);
    nojoystick.setPosition(360, 480);
    nojoystick.setFillColor(Color(255, 215, 0));
    /// </settings>
    int isgame = -1;
    int selectedIndex = 0;
    difficultyIndex = 2;
    bool exit = false;
    squaretrue[2].setPosition(squaresetting[2].getPosition().x + 8, squaresetting[2].getPosition().y + 3);
    if (ispause)
    {
        squaretrue[3].setPosition(squaresetting[3].getPosition().x + 8, squaresetting[3].getPosition().y + 3);
        squaretrue[4].setPosition(squaresetting[4].getPosition().x + 8, squaresetting[4].getPosition().y + 3);
    }

    hand.setPosition(330, 105);
    settingselements[0].setFillColor(Color::Red);
    int time_plus = 0;
    while (window.isOpen())
    {
        if (Time_page.getElapsedTime().asSeconds() > Page_delay && is_ai)
        {
            bool isUP = false;
            bool isDOWN = false;
            bool isSELECT = false;
            bool isESCAPE = false;
            ifstream file("files/gesture.txt");
            string text = "";
            getline(file, text);
            file.close();

            // Only update if text changed
            if (temp1 != text)
            {
                vector<string> words;
                stringstream ss(text);
                string word;
                while (ss >> word)
                    words.push_back(word);

                // reset buttons


                for (auto& w : words)
                {
                    if (w == "u") isUP = true;   // left
                    else if (w == "d") isDOWN = true; // right
                    if (w == "s") isSELECT = true; // jump
                    if (w == "R") isESCAPE = true; // escape
                }

                cout << text << endl;
                temp1 = text;
            }
            //float y = Joystick::getAxisPosition(0, Joystick::Y);
            if (isUP && Time_action.getElapsedTime().asSeconds() > Action_delay)
            {
                settingselements[selectedIndex].setFillColor(Color::White);
                selectedIndex--;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                if (selectedIndex < 0) selectedIndex = elements - 1;
                hand.setPosition(330, 185 * selectedIndex + 105);
                settingselements[selectedIndex].setFillColor(Color::Red);
                time_plus = 0;
                Time_action.restart();
            }
            else if (isDOWN && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                settingselements[selectedIndex].setFillColor(Color::White);
                selectedIndex++;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                if (selectedIndex > elements - 1) selectedIndex = 0;
                hand.setPosition(330, 185 * selectedIndex + 105);
                settingselements[selectedIndex].setFillColor(Color::Red);
                time_plus = 0;
                Time_action.restart();
            }
            if (isSELECT && Time_action.getElapsedTime().asSeconds() > Action_delay + time_plus) {
                Time_action.restart();
                time_plus = 1;
                if (!issound) {
                    choosesound.stop();
                }
                else
                {
                    choosesound.play();
                }
                if (selectedIndex == 0)
                {
                    issound = !issound;
                }
                else if (selectedIndex == 1)
                {
                    ismusic = !ismusic;
                    if (!ismusic) {
                        menusound.stop();

                    }
                    else {
                        menusound.play();
                        menusound.setLoop(true);
                    }
                }
                else if (selectedIndex == 2)
                {
                    if (!ispause)
                        is_ai = !is_ai;
                    else
                    {
                        iskeyboard = false;
                        is_ai = true;
                        is_joystick = false;
                    }
                }
                else if (selectedIndex == 3)
                {
                    if (!ispause)
                    {
                        configuration();
                    }
                    else
                    {
                        iskeyboard = true;
                        is_ai = false;
                        is_joystick = false;
                    }
                    hand.setPosition(330, 185 * selectedIndex + 105);
                }
                else if (selectedIndex == 4)
                {
                    if (Joystick::isConnected(0))
                    {
                        iskeyboard = false;
                        is_ai = false;
                        is_joystick = true;
                    }
                    else
                    {
                        errjoy = true;
                        temp.restart();
                    }
                    hand.setPosition(330, 185 * selectedIndex + 105);
                }
            }
            if (isESCAPE && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                Time_action.restart();
                exit = true;
            }
        }

        Event event;
        while (window.pollEvent(event)) {
            float y = Joystick::getAxisPosition(0, Joystick::Y);
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed) {
                if (event.key.code == Keyboard::Up || y < -50) {
                    settingselements[selectedIndex].setFillColor(Color::White);
                    selectedIndex--;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex < 0) selectedIndex = elements - 1;
                    hand.setPosition(330, 185 * selectedIndex + 105);
                    settingselements[selectedIndex].setFillColor(Color::Red);
                }
                else if (event.key.code == Keyboard::Down || y > 50)
                {
                    settingselements[selectedIndex].setFillColor(Color::White);
                    selectedIndex++;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex > elements - 1) selectedIndex = 0;
                    hand.setPosition(330, 185 * selectedIndex + 105);
                    settingselements[selectedIndex].setFillColor(Color::Red);
                }
                else if (event.key.code == Keyboard::Enter || Joystick::isButtonPressed(0, 2)) {
                    if (!issound) {
                        choosesound.stop();
                    }
                    else
                    {
                        choosesound.play();
                    }
                    if (selectedIndex == 0)
                    {
                        issound = !issound;
                    }
                    else if (selectedIndex == 1)
                    {
                        ismusic = !ismusic;
                        if (!ismusic) {
                            menusound.stop();

                        }
                        else {
                            menusound.play();
                            menusound.setLoop(true);
                        }
                    }
                    else if (selectedIndex == 2)
                    {
                        if (!ispause)
                            is_ai = !is_ai;
                        else
                        {
                            iskeyboard = false;
                            is_ai = true;
                            is_joystick = false;
                        }
                    }
                    else if (selectedIndex == 3)
                    {
                        if (!ispause)
                        {
                            configuration();
                        }
                        else
                        {
                            iskeyboard = true;
                            is_ai = false;
                            is_joystick = false;
                        }
                        hand.setPosition(330, 185 * selectedIndex + 105);
                    }
                    else if (selectedIndex == 4)
                    {
                        if (Joystick::isConnected(0))
                        {
                            iskeyboard = false;
                            is_ai = false;
                            is_joystick = true;
                        }
                        else
                        {
                            errjoy = true;
                            temp.restart();
                        }
                        hand.setPosition(330, 185 * selectedIndex + 105);
                    }
                }
                else if (event.key.code == Keyboard::Escape || Joystick::isButtonPressed(0, 4))
                {
                    exit = true;
                }
            }
        }

        window.clear();
        window.draw(profile);
        for (int i = 0;i < elements;i++)
        {
            window.draw(settingselements[i]);
        }
        for (int i = 0;i < elements;i++)
        {
            if (!ispause)
            {
                if (i != 3 && i != 4)
                    window.draw(squaresetting[i]);
            }
            else
            {
                window.draw(squaresetting[i]);
            }
        }
        if (issound)
            window.draw(squaretrue[0]);
        if (ismusic)
            window.draw(squaretrue[1]);
        if (is_ai)
            window.draw(squaretrue[2]);
        if (iskeyboard && ispause)
            window.draw(squaretrue[3]);
        if (is_joystick && ispause)
            window.draw(squaretrue[4]);
        if (temp.getElapsedTime().asSeconds() < 3 && errjoy)
        {
            window.draw(nojoystick);
        }
        window.draw(hand);
        if (temp.getElapsedTime().asSeconds() < 3 && !starting)
        {
            window.draw(buy);
            window.draw(nojoystick);
        }
        window.display();
        if (exit)
        {
            break;
        }
    }
}

void ranking(user person[], int& countperson, bool issound)
{
    if (countperson == 0)
    {
        Text txaddfirst("No profile is found\nplease add profile first", font);
        bool exit = false;
        while (window.isOpen())
        {
            // Only update if text changed
            if (Time_page.getElapsedTime().asSeconds() > Page_delay && is_ai)
            {
                ifstream file("files/gesture.txt");
                string text = "";
                getline(file, text);
                file.close();
                bool isESCAPE = false;
                if (temp != text)
                {
                    vector<string> words;
                    stringstream ss(text);
                    string word;
                    while (ss >> word)
                        words.push_back(word);

                    // reset buttons


                    for (auto& w : words)
                    {
                        if (w == "R") isESCAPE = true;
                    }// left
                    cout << text << endl;
                    temp = text;
                }
                if (isESCAPE) {
                    break;
                }
            }


            Event event;
            while (window.pollEvent(event))
            {
                float x = Joystick::getAxisPosition(0, Joystick::X);
                if (event.type == Event::Closed)
                {
                    window.close();
                }
                if (event.key.code == Keyboard::Escape || Joystick::isButtonPressed(0, 4))
                {
                    exit = true;
                }
            }
            if (exit)
            {
                break;
            }
            window.clear();
            window.draw(profile);
            window.draw(txaddfirst);
            window.display();
        }
    }
    else if (countperson > 0)
    {
        Text txrank("Press enter to show data \t\t\thigh score :", font);
        txrank.setCharacterSize(60);
        txrank.setPosition(70, 0);
        txrank.setFillColor(Color(100, 100, 100));
        int selectedIndex = 0;
        int n = 0;
        bool exit = false;
        int* temp = new int[countperson];
        int* indecies = new int[countperson];
        Text* numbers = new Text[countperson];
        Text* players = new Text[countperson];
        int y;
        int max;
        for (int i = 0;i < countperson;i++)
        {
            temp[i] = person[i].highscore;
        }
        for (int i = 0;i < countperson;i++)
        {
            max = temp[0];
            y = 0;
            for (int z = 1;z < countperson;z++)
            {
                if (max < temp[z])
                {
                    max = temp[z];

                    y = z;
                }
            }
            indecies[i] = y;
            temp[y] = -1;
        }
        for (int i = 0;i < countperson;i++)/////////////////////////////////high score
        {
            numbers[i].setFont(font);
            numbers[i].setString(to_string(person[indecies[i]].highscore));
            numbers[i].setPosition(840, (i + 1) * 70);
            numbers[i].setCharacterSize(60);
        }
        for (int i = 0;i < countperson;i++)
        {
            players[i].setFont(font);
            if (i >= 0 && i <= 2)
                players[i].setString(" \t" + person[indecies[i]].name);
            else
                players[i].setString(to_string(i + 1) + '\t' + person[indecies[i]].name);
            players[i].setCharacterSize(60);
            players[i].setPosition(70, (i + 1) * 70);
        }
        while (window.isOpen())
        {
            if (Time_page.getElapsedTime().asSeconds() > Page_delay && is_ai)
            {
                ifstream file("files/gesture.txt");
                string text = "";
                getline(file, text);
                file.close();
                bool isUP = false;
                bool isDOWN = false;
                bool isSELECT = false;
                bool isESCAPE = false;

                // Only update if text changed
                if (temp1 != text)
                {
                    vector<string> words;
                    stringstream ss(text);
                    string word;
                    while (ss >> word)
                    {
                        words.push_back(word);
                        cout << "w : " << word << '\n';

                    }


                    // reset buttons


                    for (auto& w : words)
                    {
                        if (w == "u") isUP = true;   // left
                        else if (w == "d") isDOWN = true;
                        if (w == "s")
                        {
                            isSELECT = true;
                        }
                        else if (w == "R") isESCAPE = true;
                    }// left
                    cout << text << endl;
                    temp1 = text;
                }
                if (isUP && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                    selectedIndex--;
                    if (issound)
                        changesound.play();
                    if (selectedIndex < 0) selectedIndex = countperson - 1;

                    Time_action.restart();
                }
                if (isDOWN && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                    selectedIndex++;
                    if (issound)
                        changesound.play();
                    if (selectedIndex > countperson - 1) selectedIndex = 0;

                    Time_action.restart();
                }
                if (isSELECT && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                    if (issound)
                        choosesound.play();
                    showdatanumber(indecies[selectedIndex]);
                    Time_action.restart();
                }

                if (isESCAPE && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                    exit = true;
                    Time_action.restart();
                    Time_page.restart();
                }
            }

            Event event;
            while (window.pollEvent(event))
            {
                float y = Joystick::getAxisPosition(0, Joystick::Y);
                if (event.type == Event::Closed)
                {
                    window.close();
                }

                else if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed) {
                    if (event.key.code == Keyboard::Up || y < -50) {
                        selectedIndex--;
                        if (issound)
                            changesound.play();
                        if (selectedIndex < 0) selectedIndex = countperson - 1;
                    }
                    else if (event.key.code == Keyboard::Down || y > 50) {
                        selectedIndex++;
                        if (issound)
                            changesound.play();
                        if (selectedIndex > countperson - 1) selectedIndex = 0;
                    }
                    else if (event.key.code == Keyboard::Enter || Joystick::isButtonPressed(0, 2))
                    {
                        if (issound)
                            choosesound.play();
                        showdatanumber(indecies[selectedIndex]);
                    }
                    else if (event.key.code == Keyboard::Escape || Joystick::isButtonPressed(0, 4))
                    {
                        exit = true;
                    }
                }

            }

            window.clear();
            window.draw(profile);
            for (int i = 0;i < countperson;i++)
            {
                window.draw(players[i]);
                window.draw(numbers[i]);
            }
            for (int i = 0;i < 3;i++)
            {
                if (i <= countperson - 1)
                {
                    window.draw(trophies[i]);
                }
            }
            hand.setPosition(0, (selectedIndex + 1) * 68);

            window.draw(hand);
            window.draw(txrank);
            window.display();
            if (exit)
            {
                break;
            }
        }
        delete[]temp;
        temp = NULL;
        delete[]indecies;
        indecies = NULL;
        delete[]numbers;
        numbers = NULL;
        delete[]players;
        players = NULL;
    }

}

void chooseplayer(bool& endstart, int& countperson, bool& isedit, bool& isdelete, bool& isplay, bool& ishistory, int& Hero,
    int& indexuser, bool& issound, bool& ismusic)
{
    coinss.setPosition(550, 250);
    countercoins.setPosition(720, 250);
    /// <purchase>
    Text peter("Peter", font);
    peter.setCharacterSize(40);
    peter.setPosition(130, 340);
    Text poor("Poor", font);
    poor.setCharacterSize(40);
    poor.setPosition(630, 340);
    Text patrek("Patrek", font);
    patrek.setCharacterSize(40);
    patrek.setPosition(1130, 340);
    Text locked("locked! Press enter to Buy..", font);
    locked.setCharacterSize(60);
    locked.setFillColor(Color::Red);
    locked.setPosition(380, 800);
    locked.setOutlineThickness(2);
    /// </purchase>
    int highscore = person[indexuser].highscore;
    int selectedIndex = 0;
    endstart = false;
    static int frame = 0;
    static Clock animationClock;
    bool exit = false;

    Sprite Peter, Poor, Patrek;
    Texture petertext, poortext, patrektext;
    petertext.loadFromFile("pictures/HERO1.png");
    poortext.loadFromFile("pictures/HERO2.png");
    patrektext.loadFromFile("pictures/HERO3.png");
    Peter.setTexture(petertext);
    Poor.setTexture(poortext);
    Patrek.setTexture(patrektext);

    Peter.setScale(7, 7);
    Poor.setScale(3.475, 3.475);
    Patrek.setScale(5, 5.5);

    Peter.setTextureRect(IntRect(0, 5, 33.4, 60));
    Poor.setTextureRect(IntRect(0, 0, 73.66, 105));
    Patrek.setTextureRect(IntRect(0, 0, 54.33, 64));


    Peter.setPosition(40, 420);
    Poor.setPosition(525, 400);
    Patrek.setPosition(1060, 410);

    while (window.isOpen())
    {
        if (Time_page.getElapsedTime().asSeconds() > Page_delay && is_ai)
        {
            ifstream file("files/gesture.txt");
            getline(file, text);
            if (text == "player one")
            {
                selectedIndex = 0;
            }
            else if (text == "player two")
            {
                selectedIndex = 1;
            }
            else if (text == "J")
            {
                selectedIndex = 2;
            }
            if (text == "s" && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                Time_action.restart();
                Time_page.restart();
                if (!issound) {
                    choosesound.stop();
                }
                else
                {
                    choosesound.play();
                }
                if (selectedIndex == 0) {
                    Hero = 1;
                    PlayerTex.loadFromFile("pictures/HERO1.png");
                    difficulty(isplay, endstart, issound);

                }
                else if (selectedIndex == 1 && person[indexuser].players.poor == 1)
                {
                    Hero = 2;
                    PlayerTex.loadFromFile("pictures/HERO2.png");
                    difficulty(isplay, endstart, issound);

                }
                else if (selectedIndex == 2 && person[indexuser].players.patrick == 1)
                {
                    Hero = 3;
                    PlayerTex.loadFromFile("pictures/HERO3.png");
                    difficulty(isplay, endstart, issound);

                }
                else if (selectedIndex == 1 && person[indexuser].players.poor == 0)
                {
                    decide(selectedIndex, indexuser, countperson, 1, issound);
                }
                else if (selectedIndex == 2 && person[indexuser].players.patrick == 0)
                {
                    decide(selectedIndex, indexuser, countperson, 2, issound);
                }

            }
            else if (text == "R" && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                exit = true;
                endstart = false;
                Time_page.restart();
                Time_action.restart();
            }
        }
        countercoins.setString(to_string(person[indexuser].coins));
        Event event;
        while (window.pollEvent(event)) {
            float x = Joystick::getAxisPosition(0, Joystick::X);
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed) {
                if (event.key.code == Keyboard::Left || x < -50) {
                    selectedIndex--;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex < 0) selectedIndex = 2;
                }
                else if (event.key.code == Keyboard::Right || x > 50) {
                    selectedIndex++;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex > 2) selectedIndex = 0;
                }
                else if (event.key.code == Keyboard::Enter || Joystick::isButtonPressed(0, 2)) {

                    if (!issound) {
                        choosesound.stop();
                    }
                    else
                    {
                        choosesound.play();
                    }
                    if (selectedIndex == 0) {
                        Hero = 1;
                        PlayerTex.loadFromFile("pictures/HERO1.png");
                        difficulty(isplay, endstart, issound);
                    }
                    else if (selectedIndex == 1 && person[indexuser].players.poor == 1)
                    {
                        Hero = 2;
                        PlayerTex.loadFromFile("pictures/HERO2.png");
                        difficulty(isplay, endstart, issound);

                    }
                    else if (selectedIndex == 2 && person[indexuser].players.patrick == 1)
                    {
                        Hero = 3;
                        PlayerTex.loadFromFile("pictures/HERO3.png");
                        difficulty(isplay, endstart, issound);

                    }
                    else if (selectedIndex == 1 && person[indexuser].players.poor == 0)
                    {
                        decide(selectedIndex, indexuser, countperson, 1, issound);
                    }
                    else if (selectedIndex == 2 && person[indexuser].players.patrick == 0)
                    {
                        decide(selectedIndex, indexuser, countperson, 2, issound);
                    }
                }

                else if (event.key.code == Keyboard::Escape || Joystick::isButtonPressed(0, 4))
                {
                    exit = true;
                    endstart = false;
                }

            }
        }
        peter.setFillColor(selectedIndex == 0 ? Color::Red : Color::White);
        poor.setFillColor(selectedIndex == 1 ? Color::Red : Color::White);
        patrek.setFillColor(selectedIndex == 2 ? Color::Red : Color::White);

        if (animationClock.getElapsedTime().asMilliseconds() > 300) {
            frame = (frame + 1) % 3;
            if (selectedIndex == 0)
                Peter.setTextureRect(IntRect(frame * 33.4, 5, 33.4, 60));
            if (selectedIndex == 1 && person[indexuser].players.poor == 1)
                Poor.setTextureRect(IntRect(frame * 73.66, 0, 73.66, 105));
            if (selectedIndex == 2 && person[indexuser].players.patrick == 1)
                Patrek.setTextureRect(IntRect(frame * 54.33, 0, 54.33, 64));
            animationClock.restart();
        }

        if (exit)
        {
            break;
        }

        if (endstart)
        {
            break;
        }
        window.clear();
        window.draw(choose);
        window.draw(Peter);
        window.draw(Patrek);
        window.draw(Poor);
        window.draw(coinss);
        window.draw(countercoins);
        window.draw(peter);
        window.draw(poor);
        window.draw(patrek);
        if (person[indexuser].players.poor == 0)
        {
            window.draw(lockk);
        }
        if (person[indexuser].players.patrick == 0)
        {
            window.draw(lockk2);
        }
        if ((selectedIndex == 1 && person[indexuser].players.poor == 0) || (selectedIndex == 2 && person[indexuser].players.patrick == 0))
        {
            window.draw(locked);
        }
        window.display();
    }
}

void decide(int n, int indexuser, int countperson, int k, bool& issound)///////////ziad
{
    /// <purchase>
    Text peter("Peter", font);
    peter.setCharacterSize(40);
    peter.setPosition(130, 340);
    Text poor("Poor", font);
    poor.setCharacterSize(40);
    poor.setPosition(630, 340);
    Text patrek("Patrek", font);
    patrek.setCharacterSize(40);
    patrek.setPosition(1130, 340);
    Text locked("locked! Press enter to Buy..", font);
    locked.setCharacterSize(60);
    locked.setFillColor(Color::Red);
    locked.setPosition(380, 800);
    locked.setOutlineThickness(2);
    Text decision("Are you sure to buy this character with \n" + to_string(n * 10) + " coins ?", font);
    decision.setCharacterSize(45);
    decision.setOutlineThickness(2);
    decision.setPosition(380, 430);
    decision.setFillColor(Color(255, 215, 0));
    Text sorry("Sorry you don't have enough coins\npress escape to back", font);
    sorry.setCharacterSize(50);
    sorry.setOutlineThickness(2);
    sorry.setPosition(360, 480);
    sorry.setFillColor(Color(255, 215, 0));
    Text yes("Yes", font);
    yes.setCharacterSize(45);
    yes.setOutlineThickness(2);
    yes.setPosition(540, 575);
    yes.setStyle(Text::Italic);
    Text no("No", font);
    no.setCharacterSize(45);
    no.setOutlineThickness(2);
    no.setPosition(800, 575);
    no.setStyle(Text::Italic);
    /// </purchase>
    bool exit = false;
    bool enough = true;
    int selectedIndex = 0;
    Sprite Peter, Poor, Patrek;
    Texture petertext, poortext, patrektext;
    petertext.loadFromFile("pictures/HERO1.png");
    poortext.loadFromFile("pictures/HERO2.png");
    patrektext.loadFromFile("pictures/HERO3.png");
    Peter.setTexture(petertext);
    Poor.setTexture(poortext);
    Patrek.setTexture(patrektext);

    Peter.setScale(7, 7);
    Poor.setScale(3.475, 3.475);
    Patrek.setScale(5, 5.5);

    Peter.setTextureRect(IntRect(0, 5, 33.4, 60));
    Poor.setTextureRect(IntRect(0, 0, 73.66, 105));
    Patrek.setTextureRect(IntRect(0, 0, 54.33, 64));

    Peter.setPosition(40, 420);
    Poor.setPosition(525, 400);
    Patrek.setPosition(1060, 410);

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event)) {
            float x = Joystick::getAxisPosition(0, Joystick::X);
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed) {
                if (event.key.code == Keyboard::Left || x < -50) {
                    selectedIndex--;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex < 0) selectedIndex = 1;
                }
                else if (event.key.code == Keyboard::Right || x > 50) {
                    selectedIndex++;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex > 1) selectedIndex = 0;
                }
                else if (event.key.code == Keyboard::Enter || Joystick::isButtonPressed(0, 2))
                {
                    if (selectedIndex == 0)////yes
                    {
                        if (person[indexuser].coins >= n * 10)
                        {
                            person[indexuser].coins -= n * 10;
                            if (k == 1)
                                person[indexuser].players.poor = 1;
                            else
                                person[indexuser].players.patrick = 1;
                            savetofile(countperson);
                            exit = true;
                            if (!issound) {
                                buycharactersound.stop();
                            }
                            else
                            {
                                buycharactersound.play();
                            }
                        }
                        else
                        {
                            enough = false;
                            buycharactersound.stop();

                        }

                    }
                    else///////no
                    {

                        exit = true;
                        buycharactersound.stop();

                    }
                }
                else if (event.key.code == Keyboard::Escape || Joystick::isButtonPressed(0, 4))
                {

                    exit = true;
                    buycharactersound.stop();

                }

            }
        }
        yes.setFillColor(selectedIndex == 0 ? Color::Red : Color::White);
        no.setFillColor(selectedIndex == 1 ? Color::Red : Color::White);

        window.clear();
        window.draw(choose);
        window.draw(Peter);
        window.draw(Patrek);
        window.draw(Poor);
        window.draw(coinss);
        window.draw(countercoins);
        window.draw(peter);
        window.draw(poor);
        window.draw(patrek);
        if (person[indexuser].players.poor == 0)
        {
            window.draw(lockk);
        }
        if (person[indexuser].players.patrick == 0)
        {
            window.draw(lockk2);
        }
        if ((selectedIndex == 1 && person[indexuser].players.poor == 0) || (selectedIndex == 2 && person[indexuser].players.patrick == 0))
        {
            window.draw(locked);
        }
        window.draw(buy);
        if (enough)
        {
            window.draw(decision);
            window.draw(yes);
            window.draw(no);
        }
        else
        {
            window.draw(sorry);
        }
        window.display();
        if (exit)
        {
            break;
        }
    }
}

void difficulty(bool& isplay, bool& endstart, bool& issound)
{
    /// <difficulty>
    Text game_difficulty("game difficulty", font);
    game_difficulty.setCharacterSize(120);
    game_difficulty.setPosition(70, 390);
    game_difficulty.setStyle(Text::Italic);
    game_difficulty.setOutlineThickness(2);
    Text easy("Easy", font);
    easy.setCharacterSize(35);
    easy.setPosition(810, 515);
    easy.setOutlineThickness(2);
    Text medium("medium", font);
    medium.setCharacterSize(35);
    medium.setPosition(940, 515);
    medium.setOutlineThickness(2);
    Text hard("Hard", font);
    hard.setCharacterSize(35);
    hard.setPosition(1110, 515);
    hard.setOutlineThickness(2);
    /// </difficulty>
    int selectedIndex = 0;
    bool exit = false;

    while (window.isOpen())
    {
        ////////////////////////////////////////
        if (Time_page.getElapsedTime().asSeconds() > Page_delay && is_ai)
        {
            bool one = false;
            bool two = false;
            bool three = false;
            bool isSELECT = false;
            bool isESCAPE = false;
            ifstream file("files/gesture.txt");
            string text = "";
            getline(file, text);
            file.close();

            // Only update if text changed
            if (temp1 != text)
            {
                vector<string> words;
                stringstream ss(text);
                string word;
                while (ss >> word)
                    words.push_back(word);

                // reset buttons


                for (auto& w : words)
                {
                    if (w == "u") one = true;   // left
                    if (w == "d") two = true; // right
                    //if(w == "J") three = true;
                    if (w == "R") isESCAPE = true;
                    if (w == "s") isSELECT = true; // jump
                }

                cout << text << endl;
                temp1 = text;
            }

            if (one && Time_action.getElapsedTime().asSeconds() > Action_delay)
            {
                selectedIndex++;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                if (selectedIndex > 2) selectedIndex = 0;
                Time_action.restart();
            }
            else if (two && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                selectedIndex--;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                if (selectedIndex < 0) selectedIndex = 2;

                Time_action.restart();
            }
            //      else if (three) {
            //      selectedIndex = 2;
            //      if (!issound) {
            //              changesound.stop();
            //          }
            //          else
            //          {
            //              changesound.play();
                  //}
            //      }
            else if (isSELECT && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                if (!issound) {
                    choosesound.stop();
                }
                else
                {
                    choosesound.play();
                }
                if (selectedIndex == 0)
                {
                    iseasy = true;
                    ismedium = false;
                    ishard = false;
                }
                else if (selectedIndex == 1)
                {
                    iseasy = false;
                    ismedium = true;
                    ishard = false;
                }
                else if (selectedIndex == 2)
                {
                    iseasy = false;
                    ismedium = false;
                    ishard = true;
                }
                Time_page.restart();
                Choose_System(issound, endstart);
            }
            if (isESCAPE && Time_action.getElapsedTime().asSeconds() > Action_delay)
            {
                exit = true;
                endstart = false;
                Time_action.restart();
            }
        }


        ///////////////////////////////////////

        Event event;
        while (window.pollEvent(event)) {
            float x = Joystick::getAxisPosition(0, Joystick::X);
            if (event.type == Event::Closed)
                window.close();

            else if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed) {
                if (event.key.code == Keyboard::Left || x < -50) {
                    selectedIndex--;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex < 0) selectedIndex = 2;
                }
                else if (event.key.code == Keyboard::Right || x > 50)
                {
                    selectedIndex++;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex > 2) selectedIndex = 0;
                }
                else if (event.key.code == Keyboard::Enter || Joystick::isButtonPressed(0, 2)) {
                    if (!issound) {
                        choosesound.stop();
                    }
                    else
                    {
                        choosesound.play();
                    }
                    if (selectedIndex == 0)
                    {
                        iseasy = true;
                        ismedium = false;
                        ishard = false;
                    }
                    else if (selectedIndex == 1)
                    {
                        iseasy = false;
                        ismedium = true;
                        ishard = false;
                    }
                    else if (selectedIndex == 2)
                    {
                        iseasy = false;
                        ismedium = false;
                        ishard = true;
                    }
                    Choose_System(issound, endstart);
                }
                if (event.key.code == (Keyboard::Escape) || Joystick::isButtonPressed(0, 4))
                {

                    exit = true;
                    endstart = false;
                }
            }
        }
        easy.setFillColor(selectedIndex == 0 ? Color::Red : Color::White);
        medium.setFillColor(selectedIndex == 1 ? Color::Red : Color::White);
        hard.setFillColor(selectedIndex == 2 ? Color::Red : Color::White);
        squaretrue[5].setPosition(squarelevel[selectedIndex].getPosition().x + 8, squarelevel[selectedIndex].getPosition().y + 3);
        window.clear();
        window.draw(profile);
        window.draw(easy);
        window.draw(medium);
        window.draw(hard);
        window.draw(game_difficulty);
        for (int i = 0;i < 3;i++)
        {
            window.draw(squarelevel[i]);
        }
        window.draw(squaretrue[5]);
        window.display();
        if (exit || endstart)
        {
            break;
        }
    }

}

void showStartScreen(bool& end, int& countperson, bool& isedit, bool& isdelete, bool& isplay,
    bool& ishistory, int& indexuser, int& Hero, bool& issound, bool& ismusic)
{
    //<main menu>
    Text menuelements[6];
    string txts[6] = { "Play","instructions","Profile","History","Settings","Exit" };
    for (int i = 0;i < 6;i++)
    {
        menuelements[i].setFont(font);
        menuelements[i].setString(txts[i]);
        menuelements[i].setCharacterSize(70);
        menuelements[i].setPosition(170, 270 + 100 * i);
        menuelements[i].setOutlineThickness(2);
    }
    Text txwelcome("Welcome to our game", font);
    txwelcome.setCharacterSize(60);
    txwelcome.setPosition(-txwelcome.getGlobalBounds().width, 940);
    txwelcome.setOutlineThickness(2);
    txwelcome.setFillColor(Color(255, 215, 0));
    menuelements[0].setFillColor(Color::Red);
    /// </main menu>
    int selectedIndex = 0;
    bool endstart = false;
    goodsound.stop();
    greatsound.stop();
    supersound.stop();
    amazingsound.stop();
    if (ismusic) {
        menusound.setLoop(true);
        menusound.play();
    }
    else {
        menusound.stop();
    }
    hand.setPosition(100, 271);
    while (window.isOpen())
    {

        if (Time_page.getElapsedTime().asSeconds() > Page_delay && is_ai)
        {
            bool isUP = false;
            bool isDOWN = false;
            bool isSELECT = false;
            ifstream file("files/gesture.txt");
            string text = "";
            getline(file, text);
            file.close();

            // Only update if text changed
            if (temp != text)
            {
                vector<string> words;
                stringstream ss(text);
                string word;
                while (ss >> word)
                {
                    cout << "Text : " << text << "\n";
                    cout << word << "\n";
                    words.push_back(word);
                }


                // reset buttons


                for (auto& w : words)
                {
                    if (w == "u") isUP = true;   // left
                    else if (w == "d") isDOWN = true; // right
                    if (w == "s") isSELECT = true; // jump
                }

                //cout << text << endl;
                temp = text;
            }
            if (isUP && Time_action.getElapsedTime().asSeconds() > Action_delay)
            {
                menuelements[selectedIndex].setFillColor(Color::White);
                selectedIndex--;

                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                if (selectedIndex < 0) selectedIndex = 5;
                menuelements[selectedIndex].setFillColor(Color::Red);
                hand.setPosition(100, 100 * selectedIndex + 271);
                Time_action.restart();
            }
            else if (isDOWN && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                menuelements[selectedIndex].setFillColor(Color::White);
                selectedIndex++;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                if (selectedIndex > 5) selectedIndex = 0;
                menuelements[selectedIndex].setFillColor(Color::Red);
                hand.setPosition(100, 100 * selectedIndex + 271);
                Time_action.restart();
            }
            if (isSELECT && Time_action.getElapsedTime().asSeconds() > Action_delay) {
                Time_action.restart();
                Time_page.restart();
                if (!issound) {
                    choosesound.stop();
                }
                else
                {
                    choosesound.play();
                }
                if (selectedIndex == 0) ///play
                {
                    isplay = true;
                    while (window.isOpen())
                    {
                        showprofile(endstart, countperson, isedit, isdelete, isplay, ishistory,
                            indexuser, Hero, issound, ismusic);
                        if (endstart)
                        {
                            chooseplayer(endstart, countperson, isedit, isdelete, isplay, ishistory, Hero, indexuser, issound, ismusic);
                        }
                        if (!isplay)
                        {
                            hand.setPosition(100, 100 * selectedIndex + 271);
                            break;
                        }
                        if (endstart)
                        {
                            hand.setPosition(100, 100 * selectedIndex + 271);
                            break;
                        }
                    }
                }
                else if (selectedIndex == 1)///tutorial
                {
                    Show_Tutorial();
                    hand.setPosition(100, 100 * selectedIndex + 271);
                }
                else if (selectedIndex == 2)///profile
                {
                    controlprofile(endstart, countperson, isedit, isdelete, isplay, ishistory, indexuser, Hero, issound, ismusic);
                    hand.setPosition(100, 100 * selectedIndex + 271);
                }
                else if (selectedIndex == 3)//ranking
                {
                    ranking(person, countperson, issound);
                    hand.setPosition(100, 100 * selectedIndex + 271);
                }
                else if (selectedIndex == 4)//setting
                {
                    setting(issound, ismusic, false);
                    hand.setPosition(100, 100 * selectedIndex + 271);
                }
                else if (selectedIndex == 5)//exit
                {
                    window.close();
                }
            }
        }
        Event event;
        while (window.pollEvent(event)) {


            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed)
            {
                float y = Joystick::getAxisPosition(0, Joystick::Y);
                cout << "Y : " << y << "\n";
                if (event.key.code == Keyboard::Up || y < -50) {
                    menuelements[selectedIndex].setFillColor(Color::White);
                    selectedIndex--;

                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex < 0) selectedIndex = 5;
                    menuelements[selectedIndex].setFillColor(Color::Red);
                    hand.setPosition(100, 100 * selectedIndex + 271);
                }
                else if (event.key.code == Keyboard::Down || y > 50) {
                    menuelements[selectedIndex].setFillColor(Color::White);
                    selectedIndex++;
                    if (!issound) {
                        changesound.stop();
                    }
                    else
                    {
                        changesound.play();
                    }
                    if (selectedIndex > 5) selectedIndex = 0;
                    menuelements[selectedIndex].setFillColor(Color::Red);
                    hand.setPosition(100, 100 * selectedIndex + 271);
                }
                else if (event.key.code == Keyboard::Enter || Joystick::isButtonPressed(0, 2)) {
                    if (!issound) {
                        choosesound.stop();
                    }
                    else
                    {
                        choosesound.play();
                    }
                    if (selectedIndex == 0) ///play
                    {
                        isplay = true;
                        while (window.isOpen())
                        {
                            showprofile(endstart, countperson, isedit, isdelete, isplay, ishistory,
                                indexuser, Hero, issound, ismusic);
                            if (endstart)
                            {
                                chooseplayer(endstart, countperson, isedit, isdelete, isplay, ishistory, Hero, indexuser, issound, ismusic);
                            }
                            if (!isplay)
                            {
                                hand.setPosition(100, 100 * selectedIndex + 271);
                                break;
                            }
                            if (endstart)
                            {
                                hand.setPosition(100, 100 * selectedIndex + 271);
                                break;
                            }
                        }
                    }
                    else if (selectedIndex == 1)///tutorial
                    {
                        Show_Tutorial();
                        hand.setPosition(100, 100 * selectedIndex + 271);
                    }
                    else if (selectedIndex == 2)///profile
                    {
                        controlprofile(endstart, countperson, isedit, isdelete, isplay, ishistory, indexuser, Hero, issound, ismusic);
                        hand.setPosition(100, 100 * selectedIndex + 271);
                    }
                    else if (selectedIndex == 3)//ranking
                    {
                        ranking(person, countperson, issound);
                        hand.setPosition(100, 100 * selectedIndex + 271);
                    }
                    else if (selectedIndex == 4)//setting
                    {
                        setting(issound, ismusic, false);
                        hand.setPosition(100, 100 * selectedIndex + 271);
                    }
                    else if (selectedIndex == 5)//exit
                    {
                        window.close();
                    }
                }
            }

        }
        txwelcome.move(0.7, 0);//////abdallah
        if (txwelcome.getPosition().x > 1260)///////abdallah
        {
            txwelcome.setPosition(-txwelcome.getGlobalBounds().width, 940);////////abdallah
        }
        if (endstart)
        {
            menusound.stop();
            break;
        }
        window.clear();
        window.draw(startplay);
        for (int i = 0;i < 6;i++)
        {
            window.draw(menuelements[i]);
        }
        window.draw(hand);
        window.draw(tape);
        window.draw(txwelcome);
        window.display();
    }

}

void initializeStairs(int& number) {
    for (int i = 0; i < numStairs; i++) {
        stairs[i].num = number;
        stairs[i].sprite.setTexture(StairTex1);
        if (i == 0) {

            stairs[i].sprite.setScale(3.25, 1.7);
            stairs[i].sprite.setPosition(170, windowHeight - stairs[i].sprite.getGlobalBounds().height);
            player.setPosition(stairs[0].sprite.getPosition().x + 50, stairs[0].sprite.getPosition().y - 20);

        }
        else {
            int x = rand() % 3;
            if (x == 0)stairs[i].sprite.setScale(1, 1.7);
            else if (x == 1)stairs[i].sprite.setScale(.5, 1.7);
            else if (x == 2)stairs[i].sprite.setScale(.75, 1.7);
            stairs[i].sprite.setPosition(200 + rand() % (windowWidth - 700), windowHeight - (i * 204));
        }

        number++;
    }
}

void movement(double jumpBoost, double playerSpeed, double& velocityX, double& velocityY, bool& onGround,
    bool& spacePressed, double& jumppower, bool& isMoving, double& ddistance, double maxPlayerSpeed,
    double maxJumpPower, double& runtime, int& Hero, bool& issound)
{
    static bool b0 = false, b1 = false, b2 = false; // right, left, jump
    static string temp = "";
    if (is_joystick)
    {
        float x, y;
        x = Joystick::getAxisPosition(0, Joystick::X);
        y = Joystick::getAxisPosition(0, Joystick::Y);
        b1 = (numjoys[1] == 11 && x < -50) ||
            (numjoys[1] == 10 && x > 50) || (numjoys[1] == 12 && y < -50) ||
            (numjoys[1] == 13 && y > 50) || (numjoys[1] >= 0 && numjoys[1] <= 9 && Joystick::isButtonPressed(0, numjoys[1]));
        b0 = (numjoys[0] == 11 && x < -50) ||
            (numjoys[0] == 10 && x > 50) || (numjoys[0] == 12 && y < -50) ||
            (numjoys[0] == 13 && y > 50) || (numjoys[0] >= 0 && numjoys[0] <= 9 && Joystick::isButtonPressed(0, numjoys[0]));
        b2 = (numjoys[2] == 11 && x < -50) ||
            (numjoys[2] == 10 && x > 50) || (numjoys[2] == 12 && y < -50) ||
            (numjoys[2] == 13 && y > 50) || (numjoys[2] >= 0 && numjoys[2] <= 9 && Joystick::isButtonPressed(0, numjoys[2]));
    }
    else if (iskeyboard)
    {
        if (Keyboard::isKeyPressed(keys[0]))
        {
            b0 = true;
            b1 = false;
        }
        else if (Keyboard::isKeyPressed(keys[1]))
        {
            b1 = true;
            b0 = false;
        }
        else
        {
            b0 = false;
            b1 = false;
        }
        if (Keyboard::isKeyPressed(keys[2]))
        {
            b2 = true;
        }
        else
        {
            b2 = false;
        }
    }

    ///////////////////////////////////
    // Read gesture from file
    else if (is_ai)
    {
        ifstream file("files/gesture.txt");
        string text = "";
        getline(file, text);
        file.close();

        // Only update if text changed
        if (temp != text || true)
        {
            vector<string> words;
            stringstream ss(text);
            string word;
            while (ss >> word)
                words.push_back(word);

            // reset buttons
            b0 = b1 = b2 = false;

            for (auto& w : words)
            {
                if (w == "L") b1 = true;   // left
                else if (w == "R") b0 = true; // right
                else if (w == "J") b2 = true; // jump
            }

            temp = text;
        }
    }


    // Horizontal movement
    if (b1) // left
    {
        velocityX = -playerSpeed;
        isMoving = true;
        //cout << "Moving Left" << endl;
    }
    else if (b0) // right
    {
        velocityX = playerSpeed;
        isMoving = true;
        //cout << "Moving Right" << endl;
    }
    else
    {
        isMoving = false;
        velocityX = 0;
    }

    // Update speed and jump power based on distance
    if (isMoving)
    {
        runtime = runclock.getElapsedTime().asSeconds();
        ddistance = abs(velocityX) * runtime;

        playerSpeed = 0.5 + ddistance;
        if (playerSpeed > maxPlayerSpeed)
            playerSpeed = maxPlayerSpeed;

        jumppower = 1 + (playerSpeed - 0.4) * 3.50;
        if (jumppower > maxJumpPower)
            jumppower = maxJumpPower;
    }
    else
    {
        runclock.restart();
        runtime = 0.f;
        ddistance = 0;
    }

    // Jump
    if (b2 && onGround)
    {
        velocityY = -jumppower;
        spacePressed = true;

        // Play sound based on hero
        if (Hero == 1)
        {
            if (!issound) jumpsound.stop();
            else jumpsound.play();
        }
        else if (Hero == 2)
        {
            if (!issound) jumppoorsound.stop();
            else jumppoorsound.play();
        }
        else
        {
            if (!issound) jumppatricksound.stop();
            else jumppatricksound.play();
        }

        // Horizontal boost while jumping
        if (b1) velocityX = -jumpBoost;
        if (b0) velocityX = jumpBoost;

        runclock.restart();
        runtime = 0;
        ddistance = 0;
    }

    //if (!b2) spacePressed = false;
}

void applyPhysics(double gravity, double friction, double& velocityX, double& velocityY, bool& onGround) {
    velocityY += gravity;
    if (onGround) velocityX *= friction;
    player.move(velocityX, velocityY);
    if (player.getPosition().x <= 200 && istouchleftwall) {
        player.setPosition(220, player.getPosition().y);
        velocityX = -velocityX;
        velocityY *= 2;
        (velocityY < -2) ? velocityY = -2 : velocityY = velocityY;
        player.move(velocityX, velocityY);
        istouchleftwall = false;
    }
    else if (player.getPosition().x <= 195 && !istouchleftwall) {
        player.setPosition(220, player.getPosition().y);
        player.move(-velocityX, velocityY);
    }
    if (player.getPosition().x >= 1120 && istouchrightwall) {
        player.setPosition(1110, player.getPosition().y);
        velocityX = -velocityX;
        velocityY *= 2;
        (velocityY < -2) ? velocityY = -2 : velocityY = velocityY;
        player.move(velocityX, velocityY);
        istouchrightwall = false;
    }
    else if (player.getPosition().x >= 1120 && !istouchrightwall) {
        player.setPosition(1110, player.getPosition().y);
        player.move(-velocityX, velocityY);
    }
}

void updateStairs(int& number, double& velocitystair, bool& onGround, double& velocityY, int& nextscores, int stairlevel, bool& iscoin, double& vx,
    bool& isthrone, int& bounds) {
    onGround = false;

    for (int i = 0; i < numStairs; i++)
    {
        if (stairs[i].num % stairlevel >= 1 && stairs[i].num % stairlevel <= 7 && stairs[i].num > 9 && !isthrone)//////new
        {
            if (stairs[i].num % 2 == 0)
                if (stairs[i].flip)
                    stairs[i].velocitystairX = -vx;//////you can change the speed of velocity x
                else
                    stairs[i].velocitystairX = vx;
            else
                if (stairs[i].flip)
                    stairs[i].velocitystairX = vx;
                else
                    stairs[i].velocitystairX = -vx;
        }
        else
        {
            stairs[i].velocitystairX = 0;
        }
        if (stairs[i].sprite.getPosition().x + stairs[i].sprite.getGlobalBounds().width >= 1080 && stairs[i].num % 2 == 0)//////new
        {
            stairs[i].flip = true;
        }
        else if (stairs[i].sprite.getPosition().x + stairs[i].sprite.getGlobalBounds().width >= 1080 && stairs[i].num % 2 != 0)////new
        {
            stairs[i].flip = false;
        }
        else if (stairs[i].sprite.getPosition().x <= 160 && stairs[i].num % 2 != 0)///new
        {
            stairs[i].flip = true;
        }
        else if (stairs[i].sprite.getPosition().x <= 160 && stairs[i].num % 2 == 0)///new
        {
            stairs[i].flip = false;
        }
        if (iscoin)
        {
            if (stairs[i].num % 5 == 1 && stairs[i].num > 5)
            {
                coin.setPosition(stairs[i].sprite.getPosition().x + 30, stairs[i].sprite.getPosition().y - 100);
            }
        }
        stairs[i].sprite.move(stairs[i].velocitystairX, velocitystair);//////new

        if (stairs[i].sprite.getPosition().y > camera.getCenter().y + windowHeight / 2)
        {
            indexstair = i;
            stairs[i].num = number;
            if (stairs[i].num % stairlevel == 0)
            {
                var = true;
            }
            if (stairs[i].num >= bounds && stairs[i].num < bounds + stairlevel) {
                stairs[i].sprite.setTexture(StairTex1);
            }
            else if (stairs[i].num >= bounds + stairlevel && stairs[0].num < bounds + stairlevel * 2) {
                stairs[i].sprite.setTexture(StairTex2);
            }
            else if (stairs[i].num >= bounds + stairlevel * 2 && stairs[i].num < bounds + stairlevel * 3) {
                stairs[i].sprite.setTexture(StairTex3);
            }
            else if (stairs[i].num >= bounds + stairlevel * 3 && stairs[i].num < bounds + stairlevel * 4) {
                stairs[i].sprite.setTexture(StairTex4);
            }
            if (stairs[i].num % 5 == 1 && !iseasy)
            {
                iscoin = true;
            }
            if (stairs[i].num % stairlevel >= 5 && stairs[i].num % stairlevel <= 8 && stairs[i].num > 9)//////////new
            {
                stairs[i].flip = false;
            }
            float newY = camera.getCenter().y - 600;
            float newX;
            if (stairs[i].num % stairlevel != 0) {
                int x = rand() % 3;
                if (x == 0)stairs[i].sprite.setScale(1, 1.7);
                else if (x == 1)stairs[i].sprite.setScale(.5, 1.7);
                else if (x == 2)stairs[i].sprite.setScale(.75, 1.7);
                newX = 200 + rand() % (windowWidth - 700);
            }
            else
            {
                stairs[i].sprite.setScale(3.25, 1.7);
                newX = 180;
            }
            stairs[i].sprite.setPosition(newX, newY);
            number++;

        }


        FloatRect bounds = player.getGlobalBounds();
        FloatRect feet(bounds.left, bounds.top + bounds.height - 10, bounds.width, 10);

        if (feet.intersects(stairs[i].sprite.getGlobalBounds()) && velocityY > 0) {

            velocityY = 0;
            player.setPosition(player.getPosition().x, stairs[i].sprite.getPosition().y - 53);
            onGround = true;
            nextscores = stairs[i].num * 10;
            istouchleftwall = true;
            istouchrightwall = true;
        }
    }

}

void Animation(double& velocityY, double& velocityX, int& Hero, bool& onGround, double jumppower, double maxJumpPower, bool& issound) {
    static int frame = 0;
    static Clock animationClock;
    static Clock FlipClock;
    static Clock Bar;
    bool flip = false;
    float Fillpercent = 0;
    float x;
    x = Joystick::getAxisPosition(0, Joystick::X);

    if (ispower && !onGround && velocityY <= 0) {
        flip = true;
        if (Hero == 1) {
            if (!issound) {
                flipsound.stop();
            }
            else
            {
                flipsound.play();
            }
        }
        else if (Hero == 2)
        {
            if (!issound) {
                flippoorsound.stop();
            }
            else
            {
                flippoorsound.play();
            }
        }

        else
        {
            if (!issound) {
                flippatricksound.stop();
            }
            else
            {
                flippatricksound.play();
            }
        }
    }
    else if (onGround) {
        flip = false;
    }
    if (flip)
        player.setRotation(FlipClock.getElapsedTime().asSeconds() * 600);
    else {
        FlipClock.restart();

        player.setRotation(0);
    }

    if ((flip == true)) {
        CurrentState = Super_Jump;
    }
    else if ((!onGround) && velocityX < 0 && (velocityY <= 0)) {
        CurrentState = Jump_Left;
    }
    else if ((!onGround) && velocityX > 0 && (velocityY <= 0)) {
        CurrentState = Jump_Right;
    }
    else if ((!onGround) && velocityX < 0 && (velocityY >= 0)) {
        CurrentState = Fall_Left;
    }
    else if ((!onGround) && velocityX > 0 && (velocityY >= 0)) {
        CurrentState = Fall_Right;
    }
    else if (!onGround) {
        CurrentState = Jump;
    }
    else if (velocityX < 0) {
        CurrentState = Left;
    }
    else if (velocityX > 0) {
        CurrentState = Right;
    }
    else {
        CurrentState = Stand;
    }
    if (Hero == 1) {
        switch (CurrentState) {
        case Stand:
            player.setOrigin(33.4 / 2, 23);
            player.setScale(2.3, 2.3);
            if (animationClock.getElapsedTime().asMilliseconds() > 300) {
                frame = (frame + 1) % 3;
                player.setTextureRect(IntRect(frame * 33.4, 5, 33.4, 60));
                animationClock.restart();
            }
            break;
        case Left:
            player.setOrigin(37.4 / 2, 57 / 2);
            player.setScale(2, 2);
            if (animationClock.getElapsedTime().asMilliseconds() > 200) {
                frame = (frame + 1) % 5;
                player.setTextureRect(IntRect(frame * 37.4, 133, 37.4, 57));
                animationClock.restart();
            }
            break;
        case Right:
            player.setOrigin(37.4 / 2, 57 / 2);
            player.setScale(2, 2);
            if (animationClock.getElapsedTime().asMilliseconds() > 200) {
                frame = (frame + 1) % 5;
                player.setTextureRect(IntRect(frame * 37.4, 66, 37.4, 57));
                animationClock.restart();
            }
            break;
        case Jump:
            player.setOrigin(37.4 / 2, 57 / 2);
            player.setScale(2, 2);
            player.setTextureRect(IntRect(3 * 34.4, 0, 37.4, 57));
            break;
        case Jump_Left:
            player.setOrigin(34 / 2, 53 / 2);
            player.setScale(2, 2);
            player.setTextureRect(IntRect(77, 198, 34, 53));
            break;
        case Jump_Right:
            player.setOrigin(34 / 2, 53 / 2);
            player.setScale(2, 2);
            player.setTextureRect(IntRect(0, 198, 34, 53));
            break;
        case Fall_Left:
            player.setOrigin(35 / 2, 53 / 2);
            player.setScale(2, 2);
            player.setTextureRect(IntRect(113, 198, 35, 53));
            break;
        case Fall_Right:
            player.setOrigin(35 / 2, 53 / 2);
            player.setScale(2, 2);
            player.setTextureRect(IntRect(38, 198, 35, 53));
            break;
        case Super_Jump:
            player.setScale(2, 2);
            player.setTextureRect(IntRect(139, 0, 45, 57));
            player.setOrigin(45 / 2, 57 / 2);
            break;
        }
    }
    else if (Hero == 2) {
        switch (CurrentState) {
        case Stand:
            player.setOrigin(73.66 / 2, 105 / 2);
            player.setScale(1.1, 1.1);
            if (animationClock.getElapsedTime().asMilliseconds() > 300) {
                frame = (frame + 1) % 3;
                player.setTextureRect(IntRect(frame * 73.66, 0, 73.66, 105));
                animationClock.restart();
            }
            break;
        case Left:
            player.setOrigin(72 / 2, 101 / 2);
            player.setScale(1.1, 1.1);
            if (animationClock.getElapsedTime().asMilliseconds() > 200) {
                frame = (frame + 1) % 4;
                player.setTextureRect(IntRect(frame * 72, 206, 72, 101));
                animationClock.restart();
            }
            break;
        case Right:
            player.setOrigin(72 / 2, 101 / 2);
            player.setScale(1.1, 1.1);
            if (animationClock.getElapsedTime().asMilliseconds() > 200) {
                frame = (frame + 1) % 4;
                player.setTextureRect(IntRect(frame * 72, 105, 72, 101));
                animationClock.restart();
            }
            break;
        case Jump:
            player.setOrigin(68 / 2, 102 / 2);
            player.setScale(1.1, 1.1);
            player.setTextureRect(IntRect(0, 304, 68, 102));
            break;
        case Jump_Left:
            player.setOrigin(65 / 2, 100 / 2);
            player.setScale(1.1, 1.1);
            player.setTextureRect(IntRect(158, 408, 65, 100));
            break;
        case Jump_Right:
            player.setOrigin(66 / 2, 102 / 2);
            player.setScale(1.1, 1.1);
            player.setTextureRect(IntRect(68, 304, 66, 102));
            break;
        case Fall_Left:
            player.setOrigin(68 / 2, 100 / 2);
            player.setScale(1.1, 1.1);
            player.setTextureRect(IntRect(88, 408, 68, 100));
            break;
        case Fall_Right:
            player.setOrigin(68 / 2, 102 / 2);
            player.setScale(1.1, 1.1);
            player.setTextureRect(IntRect(134, 304, 68, 102));
            break;
        case Super_Jump:
            player.setScale(1.1, 1.1);
            player.setTextureRect(IntRect(0, 407, 89, 101));
            player.setOrigin(89 / 2, 101 / 2);
            break;
        }
    }
    else {
        switch (CurrentState) {
        case Stand:
            player.setScale(1.8, 1.8);
            player.setOrigin(54.33 / 2, 28);
            if (animationClock.getElapsedTime().asMilliseconds() > 300) {
                frame = (frame + 1) % 3;
                player.setTextureRect(IntRect(frame * 54.33, 0, 54.33, 64));
                animationClock.restart();
            }
            break;
        case Left:
            player.setOrigin(54.33 / 2, 64 / 2);
            player.setScale(1.8, 1.8);
            if (animationClock.getElapsedTime().asMilliseconds() > 200) {
                frame = (frame + 1) % 4;
                player.setTextureRect(IntRect(frame * 54.33, 129, 54.33, 64));
                animationClock.restart();
            }
            break;
        case Right:
            player.setOrigin(54.33 / 2, 64 / 2);
            player.setScale(1.8, 1.8);
            if (animationClock.getElapsedTime().asMilliseconds() > 200) {
                frame = (frame + 1) % 4;
                player.setTextureRect(IntRect(frame * 54.33, 64, 54.33, 64));
                animationClock.restart();
            }
            break;
        case Jump:
            player.setOrigin(50 / 2, 64 / 2);
            player.setScale(1.7, 1.7);
            player.setTextureRect(IntRect(0, 200, 50, 76));
            break;
        case Jump_Left:
            player.setOrigin(53 / 2, 76 / 2);
            player.setScale(1.7, 1.7);
            player.setTextureRect(IntRect(120, 275, 53, 76));
            break;
        case Jump_Right:
            player.setOrigin(55 / 2, 77 / 2);
            player.setScale(1.7, 1.7);
            player.setTextureRect(IntRect(50, 196, 55, 77));
            break;
        case Fall_Left:
            player.setOrigin(55 / 2, 76 / 2);
            player.setScale(1.7, 1.7);
            player.setTextureRect(IntRect(65, 275, 55, 76));
            break;
        case Fall_Right:
            player.setOrigin(55 / 2, 77 / 2);
            player.setScale(1.7, 1.7);
            player.setTextureRect(IntRect(105, 196, 55, 77));
            break;
        case Super_Jump:
            player.setScale(1.7, 1.7);
            player.setTextureRect(IntRect(166, 198, 58, 78));
            player.setOrigin(58 / 2, 78 / 2);
            break;
        }
    }
}

void clock_animation(bool& shake, double& velocitystair, bool& issound) {
    float activeSeconds = totalElapsedTime.asSeconds();
    FloatRect bounds = clockwise.getLocalBounds();
    clockwise.setPosition(83, 107);
    clockwise.setOrigin(bounds.width / 2, bounds.height / 1.5);
    clockwise.setRotation(activeSeconds * 12);

    if (activeSeconds >= 30 && !shake) {

        shake = true;
        totalElapsedTime = Time::Zero;

        if (!issound) {
            ringsound.stop();
        }
        else
        {
            ringsound.play();
        }
        gameClock.restart();
        shaketime.restart();
    }

    if (shake) {

        hurryupsound.play();
        if (shaketime.getElapsedTime().asSeconds() <= 3) {
            float shakeX = static_cast<float>((rand() % 5) - 2.5);
            float shakeY = static_cast<float>((rand() % 5) - 2.5);
            Clock1.setPosition(shakeX, shakeY);
            clockwise.setPosition(83 + shakeX, 107 + shakeY);
        }
        else {

            velocitystair += 0.08;
            shake = false;
            Clock1.setPosition(0, 0);
        }
    }
}

void movethrones(int& indexthrone, int& countthrone, double& velocitystair) {

    float cameraTop = camera.getCenter().y - camera.getSize().y / 2;

    if (countthrone % 2 == 0)
    {
        if (warnclock.getElapsedTime().asSeconds() < 2)
        {


            rtthrone.setPosition(50, cameraTop + 15 + indexthrone * 105);
        }
        else
        {
            rtthrone.move(velocitystair, 0);
            rtthrone.setPosition(rtthrone.getPosition().x, cameraTop + 15 + indexthrone * 105);
            iswarning = false;
        }

        if (rtthrone.getPosition().x > 1260)
        {
            countthrone++;
            indexthrone = rand() % 8;
            warnclock.restart();

        }

    }
    else
    {
        if (warnclock.getElapsedTime().asSeconds() < 2)
        {


            lfthrone.setPosition(1130, cameraTop + 15 + indexthrone * 105);
        }
        else
        {
            iswarning = false;
            lfthrone.move(-velocitystair, 0);
            lfthrone.setPosition(lfthrone.getPosition().x, cameraTop + 15 + indexthrone * 105);
        }
        if (lfthrone.getPosition().x < 0)
        {
            countthrone++;
            indexthrone = rand() % 8;
            warnclock.restart();

        }
    }
}

void movebomb(double& velocitystair, int& countbombs) {

    float cameraTop = camera.getCenter().y - camera.getSize().y / 2;
    float cameraBottom = camera.getCenter().y + camera.getSize().y / 2;
    int positionx;
    if (bomb.getPosition().y > cameraBottom || countbombs == 1)
    {
        positionx = 170 + rand() % 830;
        bomb.setPosition(positionx, cameraTop - 200);

        countbombs++;
        warnclock.restart();
    }
    if (warnclock.getElapsedTime().asSeconds() < 2)
    {
        bomb.setPosition(bomb.getPosition().x, cameraTop - 200);
        warning.setPosition(warning.getPosition().x, cameraTop);

    }
    else
    {
        iswarning = false;
        bomb.move(0, 1.67 * velocitystair);
    }
}

void showbonus(bool& isbonus) {
    if (txbonus.getPosition().y > 900)
    {
        txbonus.setPosition(580, 0);
        isbonus = false;
    }
    txbonus.move(0, 0.3);
}

void movecoins(double& velocitystair, int& countcoins)//////ziad
{
    float cameraTop = camera.getCenter().y - camera.getSize().y / 2;
    float cameraBottom = camera.getCenter().y + camera.getSize().y / 2;

    if (coin.getPosition().y > cameraBottom)
    {
        coin.setPosition(170 + rand() % 830, cameraTop - 190);
        countcoins++;
    }
    coin.move(0, 1.67 * velocitystair);
}

void features(int& number, double& velocitystair, int& nlevel, int& nextscores, bool& isbomb, int& countbombs,
    bool& isthrone, int& indexthrone, int& countthrone, bool& isbonus, bool& iscoin, int& bonus, int& countcoins, int stairlevel, bool& issound) {
    if (stairs[0].num % stairlevel >= 0 && stairs[0].num % stairlevel <= 10 && stairs[0].num > 10 && !isbomb && !isthrone && !isbonus)
    {
        if (stairs[0].num % (stairlevel * 2) >= 0 && stairs[0].num % (stairlevel * 2) <= 4)
        {
            if (nlevel == 1)
            {
                bonus += 100;
                isbonus = true;
            }
        }
        else
        {
            if (nlevel == 2 && ishard)
            {
                float cameraTop = camera.getCenter().y - camera.getSize().y / 2;
                warningsound.play();
                iswarning = true;
                isthrone = true;
                countthrone++;
                warning.setPosition(170, cameraTop);
                warnclock.restart();
                if (issound)
                    warningsound.play();
            }
            else if (nlevel == 4)
            {
                float cameraTop = camera.getCenter().y - camera.getSize().y / 2;
                if (issound)
                    warningsound.play();
                iswarning = true;
                isbomb = true;
                warning.setPosition(170, cameraTop);
                countbombs++;
            }
        }


    }
    if (isbomb)
    {

        if (countbombs % 4 != 0)
        {
            movebomb(velocitystair, countbombs);
        }
        else
        {
            bomb.setPosition(170 + rand() % 860, 0);
            isbomb = false;
            iswarning = false;
        }


    }
    if (isthrone)
    {

        if (countthrone % 4 != 0)
        {

            movethrones(indexthrone, countthrone, velocitystair);
        }
        else
        {
            iswarning = false;
            isthrone = false;
        }
    }
    if (isbonus)
    {
        showbonus(isbonus);
    }

}

void levels(int countbg, double& velocitystair) {
    float cameraY = camera.getCenter().y;
    if (var)
    {
        background[2 * countbg - 1].setPosition(175, cameraY - (windowHeight / 2.0) - 1 * background[2 * countbg - 1].getGlobalBounds().height);
        rightwall[2 * countbg - 1].setPosition(1170, cameraY - (windowHeight / 2.0) - 1 * rightwall[2 * countbg - 1].getGlobalBounds().height);
        leftwall[2 * countbg - 1].setPosition(3, cameraY - (windowHeight / 2.0) - 1 * leftwall[2 * countbg - 1].getGlobalBounds().height);
        var = false;
    }
    window.clear();
    for (int i = 2 * countbg - 2; i <= 2 * countbg - 1; ++i) {
        float height = background[i].getGlobalBounds().height;
        float heightright = rightwall[i].getGlobalBounds().height;
        float heightleft = leftwall[i].getGlobalBounds().height;

        if (is_back1)
        {
            if (i == 2 * countbg - 1)
            {
                background[i].setPosition(background[i - 1].getPosition().x, background[i - 1].getPosition().y - background[i].getGlobalBounds().height);
            }
        }
        else if (is_back2)
        {
            if (i == 2 * countbg - 2)
            {
                background[i].setPosition(background[i + 1].getPosition().x, background[i + 1].getPosition().y - background[i].getGlobalBounds().height);
            }
        }
        if (is_wall1)
        {
            if (i == 2 * countbg - 1)
            {
                rightwall[i].setPosition(rightwall[i - 1].getPosition().x, rightwall[i - 1].getPosition().y - rightwall[i].getGlobalBounds().height);
                leftwall[i].setPosition(leftwall[i - 1].getPosition().x, leftwall[i - 1].getPosition().y - leftwall[i].getGlobalBounds().height);
            }
        }
        else if (is_wall2)
        {
            if (i == 2 * countbg - 2)
            {
                rightwall[i].setPosition(rightwall[i + 1].getPosition().x, rightwall[i + 1].getPosition().y - rightwall[i].getGlobalBounds().height);
                leftwall[i].setPosition(leftwall[i + 1].getPosition().x, leftwall[i + 1].getPosition().y - leftwall[i].getGlobalBounds().height);
            }
        }

        if (background[i].getPosition().y > cameraY + windowHeight / 2.0) {
            background[i].setPosition(175, cameraY - (windowHeight / 2.0) - height);
            is_back1 = !is_back1;
            is_back2 = !is_back2;
        }
        if (rightwall[i].getPosition().y > cameraY + windowHeight / 2.0) {
            rightwall[i].setPosition(1170, cameraY - (windowHeight / 2.0) - heightright);
            is_wall1 = !is_wall1;
            is_wall2 = !is_wall2;
        }
        if (leftwall[i].getPosition().y > cameraY + windowHeight / 2.0)
        {
            leftwall[i].setPosition(3, cameraY - (windowHeight / 2.0) - heightleft);
        }
    }
    for (int i = 0;i < 8;i++)
    {
        if (ismoving)
        {
            background[i].move(0, velocitystair);
            rightwall[i].move(0, .8);
            leftwall[i].move(0, .8);
        }
    }

    window.draw(background[(2 * countbg + 4) % 8]);
    window.draw(background[(2 * countbg + 5) % 8]);
    window.draw(background[(2 * countbg - 2) % 8]);
    window.draw(background[(2 * countbg - 1) % 8]);
    window.draw(rightwall[(2 * countbg + 4) % 8]);
    window.draw(rightwall[(2 * countbg + 5) % 8]);
    window.draw(rightwall[(2 * countbg - 2) % 8]);
    window.draw(rightwall[(2 * countbg - 1) % 8]);
    window.draw(leftwall[(2 * countbg + 4) % 8]);
    window.draw(leftwall[(2 * countbg + 5) % 8]);
    window.draw(leftwall[(2 * countbg - 2) % 8]);
    window.draw(leftwall[(2 * countbg - 1) % 8]);

    for (int i = 0; i < numStairs; i++) {
        window.draw(stairs[i].sprite);
    }
}

void Draw(bool& shake, int& nlevel, int& nextscores, int& prevscores, int& bounds, bool& isbounds, bool& isbomb,
    bool& isthrone, int& indexthrone, int& countthrone, bool& isbonus, bool& iscoin, bool& iscontinue, int& currentnumber,
    int stairlevel, double& velocitystair, bool isPaused, bool isgameover, bool issorry, bool& issound)
{

    numscore.setPosition(210, 905);
    coinss.setPosition(30, 820);
    coinss.setFillColor(Color::White);
    countercoins.setString(to_string(calccoins));
    countercoins.setPosition(210, 830);
    countercoins.setCharacterSize(55);
    static Clock Bar;
    float Fillpercent;
    float cameraY = camera.getCenter().y;
    if ((nextscores - prevscores) / 10 >= 4)
    {
        ispower = true;
        combo += (nextscores - prevscores) / 10;
        Bar.restart();
        txcombo.setString(to_string(combo));
        isstart = false;
    }
    if (Bar.getElapsedTime().asSeconds() <= 3)
        Fillpercent = 3 - Bar.getElapsedTime().asSeconds();
    if (Bar.getElapsedTime().asSeconds() > 3)
        Fillpercent = 0;
    barfill.setScale(0.08, 0.155 * (Fillpercent / 3));
    // camera.move(0, -camspeed);
    window.setView(camera);

    int scorelvl;
    if (prevscores > nextscores)   scorelvl = prevscores;
    else  scorelvl = nextscores;
    if (stairs[0].num % (4 * stairlevel) >= 0 && stairs[0].num % (4 * stairlevel) <= 4 && stairs[0].num > 10 && !isbounds)
    {
        bounds += (4 * stairlevel);
        isbounds = true;
    }
    if (stairs[0].num >= bounds && stairs[0].num < bounds + stairlevel) {
        nlevel = 1;
        if (issound)
            goodsound.play();
    }
    else if (stairs[0].num >= bounds + stairlevel && stairs[0].num < bounds + stairlevel * 2) {
        nlevel = 2;
        if (issound)
            greatsound.play();
    }
    else if (stairs[0].num >= bounds + stairlevel * 2 && stairs[0].num < bounds + stairlevel * 3) {
        nlevel = 3;
        if (issound)
            supersound.play();
    }
    else if (stairs[0].num >= bounds + stairlevel * 3 && stairs[0].num < bounds + stairlevel * 4) {
        nlevel = 4;
        if (issound)
            amazingsound.play();
        isbounds = false;
    }

    levels(nlevel, velocitystair);
    if (nextscores >= prevscores) {
        numscore.setString(to_string(nextscores + totalcombo));
        numscore.setFont(font);
        prevscores = nextscores;
    }
    else {
        numscore.setString(to_string(prevscores + totalcombo));
        numscore.setFont(font);
    }

    window.draw(player);
    float playerScreenY = (player.getPosition().y - camera.getCenter().y + camera.getSize().y / 2) - 180;

    if (playerScreenY < 00) {
        camera.move(0, playerScreenY);
    }

    if (isbomb)
    {
        window.draw(bomb);
    }
    if (isthrone)
    {
        if (countthrone % 2 == 0)
        {
            window.draw(rtthrone);
        }
        else
        {
            window.draw(lfthrone);
        }
    }
    if (iscoin)
    {
        window.draw(coin);
    }
    if (iswarning)
    {
        window.draw(warning);
    }
    window.setView(window.getDefaultView());
    if (isPaused)
    {
        window.draw(resume);
        window.draw(settingpause);
        window.draw(quit);
    }
    if (isgameover)
    {
        numscore.setPosition(840, 240);
        coinss.setCharacterSize(65);
        coinss.setPosition(1050, 50);
        countercoins.setPosition(1230, 55);
        window.draw(gameover);
        window.draw(playagain);
        window.draw(continuee);
        window.draw(back);
        window.draw(numscore);
        window.draw(finalscore);
        window.draw(floornum);
        window.draw(finalbonus);
        window.draw(coinss);
        window.draw(countercoins);
        window.draw(bonusnum);
        window.draw(total);
        window.draw(totalnum);
        window.draw(floorofstair);
        if (issorry)
        {
            Text sorry("Sorry you don't have enough coins", font);
            sorry.setCharacterSize(50);
            sorry.setOutlineThickness(2);
            sorry.setPosition(360, 480);
            sorry.setFillColor(Color(255, 215, 0));
            window.draw(buy);
            window.draw(sorry);
        }
        window.draw(Clock1);
        window.draw(clockwise);
    }
    if (!isgameover)
    {
        window.draw(score);
        window.draw(coinss);
        window.draw(numscore);
        window.draw(countercoins);
    }


    if (isbonus)
    {
        window.draw(txbonus);
    }

    if (shake)
    {
        hurry.move(0, 0.6);
        window.draw(hurry);
    }
    else
    {
        hurry.setPosition(420, 0);

    }

    window.draw(bar);
    window.draw(Pipe);
    window.draw(Clock1);
    window.draw(clockwise);
    if (Bar.getElapsedTime().asSeconds() <= 3 && !isstart)
    {
        window.draw(num);
        window.draw(txcombo);
        window.draw(barfill);
    }
    else
    {
        totalcombo += (combo * combo);
        combo = 0;
        ispower = false;
    }

    if (iscontinue)
    {
        countdownBeforeRestart(iscontinue, currentnumber);
    }
    window.display();
}

void gameLoop(int& countperson)
{

    while (window.isOpen())
    {
        int stairlevel = 30;
        bool x = false;
        int y = 0;
        bool endstart = false;
        double velocitystair = 0.39;
        double velocityX = 0;
        double velocityY = 0;
        double runtime;
        double ddistance;
        double playerSpeed = .8;
        double jumppower;
        double maxPlayerSpeed = 1.2;
        double maxJumpPower = 2.9;
        bool shake = false;
        int nlevel = 1;
        int Hero = 0;
        double gravity = 0.0089;
        double friction = 0.98;
        double jumpBoost = 1;
        bool spacePressed = false;
        int indexuser = 0;
        bool isedit = false;
        bool isdelete = false;
        bool isplay = false;
        bool ishistory = false;
        bool stopclock = false;
        bool isMoving = false;
        bool isPaused = false;
        static bool issound = false;
        static bool ismusic = false;
        double vx = 0;




        countercoins.setString("0");
        numscore.setString("0");

        fstream f_temp_page;
        f_temp_page.open("files/pagetxt.txt", ios::out);
        f_temp_page << 0;
        f_temp_page.close();
        showStartScreen(endstart, countperson, isedit, isdelete, isplay, ishistory, indexuser, Hero, issound, ismusic);

        if (iseasy)
        {
            velocitystair = 0.39;
            vx = 0.3;
        }
        else if (ismedium)
        {
            velocitystair = 0.7;
            vx = 0.55;
        }
        else if (ishard)
        {
            velocitystair = 0.9;
            vx = 0.8;
        }
        while (window.isOpen())
        {
            fstream f_temp_page;
            f_temp_page.open("files/pagetxt.txt", ios::out);
            f_temp_page << 2;
            f_temp_page.close();

            var = false;

            camera.setCenter(windowWidth / 2, windowHeight / 2);
            for (int i = 0;i < 8;i++)
            {
                if (i > 1)
                {
                    background[i].setPosition(175, 1020);
                    rightwall[i].setPosition(1170, 1020);
                    leftwall[i].setPosition(3, 1020);
                }
                else
                {
                    if (i == 0)
                    {
                        background[i].setPosition(175, 0);
                        rightwall[i].setPosition(1170, 0);
                        leftwall[i].setPosition(3, 0);
                    }
                    else
                    {
                        background[i].setPosition(175, -background[i].getGlobalBounds().height);
                        rightwall[i].setPosition(1170, -rightwall[i].getGlobalBounds().height);
                        leftwall[i].setPosition(3, -leftwall[i].getGlobalBounds().height);
                    }
                }
            }
            int nextscores = 0;
            int prevscores = 0;
            int bounds = 0;
            bool isbounds = false;
            bool isbomb = false;
            int countbombs = 0;
            bool isthrone = false;
            int indexthrone = rand() % 8;
            int countthrone = 0;
            bool isbonus = false;
            bool iscoin = false;
            int bonus = 0;
            int countcoins = 0;
            bool onGround = true;
            int number = 0;
            totalcombo = 0;
            combo = 0;
            calccoins = 0;
            is_back1 = true;
            is_back2 = false;
            is_wall1 = true;
            is_wall2 = false;
            //background[0].setPosition(camera.getCenter().x - background[0].getGlobalBounds().width / 2.0, camera.getCenter().y - background[0].getGlobalBounds().height / 2.0);


            initializeStairs(number);
            clockwise.setRotation(0);

            totalElapsedTime = Time::Zero;
            gameClock.restart();
            if (!ismusic) {
                backgroundsound.stop();
            }
            else {
                backgroundsound.play();
                backgroundsound.setLoop(true);
            }
            if (Hero == 1)
            {
                if (!issound) {
                    playsound.stop();
                }
                else
                {
                    playsound.play();
                }
            }

            else if (Hero == 2) {
                if (!issound) {
                    startpoorsound.stop();
                }
                else
                {
                    startpoorsound.play();
                }
            }
            else {
                if (!issound) {
                    startpatricksound.stop();
                }
                else
                {
                    startpatricksound.play();
                }
            }
            if (issound) {
                jumpsound.play();
            }
            else {
                jumpsound.stop();
            }
            bool isquit = false;
            isstart = 1;
            while (window.isOpen()) {
                float x1, y1;
                x1 = Joystick::getAxisPosition(0, Joystick::X);
                y1 = Joystick::getAxisPosition(0, Joystick::Y);
                bool b3 = false;

                if (is_ai) {
                    ifstream file("files/gesture.txt");
                    string text = "";
                    getline(file, text);
                    file.close();
                    if (temp1 != text)
                    {

                        if (text == "pause pause") {
                            b3 = true;
                        }

                        cout << text << endl;
                        temp1 = text;
                    }
                }
                else {
                    b3 = Keyboard::isKeyPressed(keys[3]) || Joystick::isButtonPressed(0, numjoys[3]);
                }
                if (b3)
                {
                    fstream f_temp_page;
                    f_temp_page.open("files/pagetxt.txt", ios::out);
                    f_temp_page << 0;
                    f_temp_page.close();
                    isPaused = true;
                    int selectedIndex = 0;
                    bool isresume = false;
                    while (window.isOpen())
                    {
                        pause(issound, ismusic, isPaused, selectedIndex, isquit, isresume);
                        if (!isPaused)
                        {
                            break;
                        }
                        Draw(shake, nlevel, nextscores, prevscores, bounds, isbounds, isbomb, isthrone, indexthrone, countthrone,
                            isbonus, iscoin, x, y, stairlevel, velocitystair, isPaused, 0, 0, issound);
                    }

                }
                shaketime.restart();
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed)
                        window.close();
                    if (b3)
                    {
                        isPaused = true;
                        int selectedIndex = 0;
                        bool isresume = false;
                        while (window.isOpen())
                        {
                            pause(issound, ismusic, isPaused, selectedIndex, isquit, isresume);
                            if (!isPaused)
                            {
                                break;
                            }
                            Draw(shake, nlevel, nextscores, prevscores, bounds, isbounds, isbomb, isthrone, indexthrone, countthrone,
                                isbonus, iscoin, x, y, stairlevel, velocitystair, isPaused, 0, 0, issound);
                        }

                    }
                }

                if (isquit)
                {
                    break;
                }

                movement(jumpBoost, playerSpeed, velocityX, velocityY, onGround, spacePressed, jumppower, isMoving,
                    ddistance, maxPlayerSpeed, maxJumpPower, runtime, Hero, issound);
                Animation(velocityY, velocityX, Hero, onGround, jumppower, maxJumpPower, issound);
                applyPhysics(gravity, friction, velocityX, velocityY, onGround);
                onGround = false;

                if (player.getGlobalBounds().intersects(stairs[0].sprite.getGlobalBounds()) && velocityY > 0) {
                    velocityY = 0;
                    player.setPosition(player.getPosition().x, stairs[0].sprite.getPosition().y - 53);
                    onGround = true;
                }
                if (player.getGlobalBounds().intersects(stairs[1].sprite.getGlobalBounds()) && velocityY > 0) {
                    velocityY = 0;
                    player.setPosition(player.getPosition().x, stairs[1].sprite.getPosition().y - 53);
                    onGround = true;
                }
                if (player.getGlobalBounds().intersects(stairs[2].sprite.getGlobalBounds()) && velocityY > 0) {
                    velocityY = 0;
                    player.setPosition(player.getPosition().x, stairs[2].sprite.getPosition().y - 53);
                    onGround = true;
                    totalElapsedTime = Time::Zero;
                    gameClock.restart();
                    isPaused = false;
                    ismoving = 1;
                    break;
                }
                if (player.getGlobalBounds().intersects(stairs[3].sprite.getGlobalBounds()) && velocityY > 0) {
                    velocityY = 0;
                    player.setPosition(player.getPosition().x, stairs[3].sprite.getPosition().y - 53);
                    onGround = true;
                    totalElapsedTime = Time::Zero;
                    gameClock.restart();
                    isPaused = false;
                    ismoving = 1;
                    break;
                }

                Draw(shake, nlevel, nextscores, prevscores, bounds, isbounds, isbomb, isthrone, indexthrone, countthrone,
                    isbonus, iscoin, x, y, stairlevel, velocitystair, isPaused, 0, 0, issound);
            }

            if (!issound) {
                jumpsound.stop();
                gameoversound.stop();
            }
            playsound.stop();
            if (isquit)
            {
                break;
            }
            isstart = 0;
            while (window.isOpen()) {
                float x1, y1;
                x1 = Joystick::getAxisPosition(0, Joystick::X);
                y1 = Joystick::getAxisPosition(0, Joystick::Y);
                bool b3 = false;
                if (is_ai) {
                    ifstream file("files/gesture.txt");
                    string text = "";
                    getline(file, text);
                    file.close();
                    if (temp1 != text)
                    {

                        if (text == "pause pause") {
                            b3 = true;
                        }

                        cout << text << endl;
                        temp1 = text;
                    }
                }
                else {
                    b3 = Keyboard::isKeyPressed(keys[3]) || Joystick::isButtonPressed(0, numjoys[3]);
                }
                if (b3)
                {
                    fstream f_temp_page;
                    f_temp_page.open("files/pagetxt.txt", ios::out);
                    f_temp_page << 0;
                    f_temp_page.close();
                    isPaused = true;
                    int selectedIndex = 0;
                    bool isresume = false;
                    while (window.isOpen())
                    {
                        pause(issound, ismusic, isPaused, selectedIndex, isquit, isresume);
                        if (!isPaused)
                        {
                            break;
                        }
                        Draw(shake, nlevel, nextscores, prevscores, bounds, isbounds, isbomb, isthrone, indexthrone, countthrone,
                            isbonus, iscoin, x, y, stairlevel, velocitystair, isPaused, 0, 0, issound);
                    }

                }

                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed)
                        window.close();
                }

                if (b3) {
                    pauseStartTime = gameClock.getElapsedTime();
                    isPaused = true;
                    int selectedIndex = 0;
                    bool isresume = false;
                    while (window.isOpen())
                    {
                        pause(issound, ismusic, isPaused, selectedIndex, isquit, isresume);
                        if (!isPaused)
                        {
                            break;
                        }
                        Draw(shake, nlevel, nextscores, prevscores, bounds, isbounds, isbomb, isthrone, indexthrone, countthrone,
                            isbonus, iscoin, x, y, stairlevel, velocitystair, isPaused, 0, 0, issound);
                    }
                    if (isquit)
                    {
                        break;
                    }
                }

                if (!isPaused) {
                    totalElapsedTime += gameClock.getElapsedTime();
                    gameClock.restart();
                }
                if (player.getGlobalBounds().intersects(coin.getGlobalBounds()) && iscoin)
                {
                    if (!issound) {
                        getcoinsound.stop();
                    }
                    else
                    {
                        getcoinsound.play();
                    }
                    iscoin = false;
                    float cameraTop = camera.getCenter().y - camera.getSize().y / 2;
                    coin.setPosition(3000, cameraTop - 200);
                    if (ismedium)
                    {
                        calccoins += 5;
                    }
                    if (ishard)
                    {
                        calccoins += 10;
                    }
                }
                if (player.getPosition().y > camera.getCenter().y + windowHeight / 2.0 + 40
                    || ((player.getGlobalBounds().intersects(rtthrone.getGlobalBounds()) ||
                        player.getGlobalBounds().intersects(lfthrone.getGlobalBounds())) && isthrone) ||
                    (player.getGlobalBounds().intersects(bomb.getGlobalBounds()) && isbomb))
                {
                    fstream f_temp_page;
                    f_temp_page.open("files/pagetxt.txt", ios::out);
                    f_temp_page << 0;
                    f_temp_page.close();
                    gameoversound.play();
                    bool issorry = false;
                    bool iscontinue = false;
                    bool isagain = false;
                    int currentnumber = 4;
                    int selectedIndex = 0;
                    bool isgameover = true;
                    backgroundsound.stop();
                    Time_page.restart();
                    while (window.isOpen())
                    {
                        showGameOver(indexuser, issound, ismusic, nextscores, prevscores, bonus, countcoins, countperson, isquit, isgameover,
                            issorry, iscontinue, currentnumber, selectedIndex);
                        if (isquit)
                        {
                            break;
                        }
                        if (!isgameover)
                        {
                            if (iscontinue)
                            {
                                countdownClock.restart();
                                warnclock.restart();
                                player.setPosition(stairs[(indexstair + 2) % 4].sprite.getPosition().x + 30, stairs[(indexstair + 2) % 4].sprite.getPosition().y - 106);
                                while (iscontinue)
                                {
                                    Draw(shake, nlevel, nextscores, prevscores, bounds, isbounds, isbomb, isthrone, indexthrone,
                                        countthrone, isbonus, iscoin, iscontinue, currentnumber, stairlevel, velocitystair, 0, 0, 0, issound);

                                    if (!ismusic) {
                                        backgroundsound.stop();
                                    }
                                    else {
                                        backgroundsound.play();
                                        backgroundsound.setLoop(true);
                                    }
                                }
                                gameClock.restart();
                                ismoving = 1;
                            }
                            else
                            {
                                isagain = true;
                            }
                            break;
                        }
                        Draw(shake, nlevel, nextscores, prevscores, bounds, isbounds, isbomb, isthrone, indexthrone,
                            countthrone, isbonus, iscoin, iscontinue, currentnumber, stairlevel, velocitystair, isPaused, isgameover, issorry, issound);
                    }
                    if (isagain)
                    {
                        break;
                    }
                    if (isquit)
                    {
                        break;
                    }
                }

                movement(jumpBoost, playerSpeed, velocityX, velocityY, onGround, spacePressed, jumppower, isMoving,
                    ddistance, maxPlayerSpeed, maxJumpPower, runtime, Hero, issound);
                applyPhysics(gravity, friction, velocityX, velocityY, onGround);
                Animation(velocityY, velocityX, Hero, onGround, jumppower, maxJumpPower, issound);
                if (ismedium || ishard)
                {
                    features(number, velocitystair, nlevel, nextscores, isbomb, countbombs, isthrone, indexthrone,
                        countthrone, isbonus, iscoin, bonus, countcoins, stairlevel, issound);
                }

                clock_animation(shake, velocitystair, issound);
                updateStairs(number, velocitystair, onGround, velocityY, nextscores, stairlevel, iscoin, vx, isthrone, bounds);
                Draw(shake, nlevel, nextscores, prevscores, bounds, isbounds, isbomb, isthrone, indexthrone, countthrone,
                    isbonus, iscoin, x, y, stairlevel, velocitystair, isPaused, 0, 0, issound);

            }
            if (isquit)
            {
                break;
            }
        }

    }
}

void pause(bool& issound, bool& ismusic, bool& isPaused, int& selectedIndex, bool& isquit, bool& isresume)
{

    goodsound.stop();
    supersound.stop();
    amazingsound.stop();
    greatsound.stop();
    backgroundsound.stop();
    warningsound.stop();
    ismoving = 0;


    bool isUP = false;
    bool isDOWN = false;
    bool isSELECT = false;
    ifstream file("files/gesture.txt");
    string text = "";
    getline(file, text);
    file.close();

    // Only update if text changed
    if (temp != text)
    {
        vector<string> words;
        stringstream ss(text);
        string word;
        while (ss >> word)
            words.push_back(word);

        // reset buttons


        for (auto& w : words)
        {
            if (w == "u") isUP = true;   // left
            else if (w == "d") isDOWN = true; // right
            if (w == "s") isSELECT = true; // jump
        }

        cout << text << endl;
        temp = text;
    }
    //float y = Joystick::getAxisPosition(0, Joystick::Y);
    if (isUP && Time_action.getElapsedTime().asSeconds() > Action_delay)
    {
        selectedIndex--;
        if (!issound) {
            changesound.stop();
        }
        else
        {
            changesound.play();
        }
        if (selectedIndex < 0) selectedIndex = 2;

        Time_action.restart();
    }
    else if (isDOWN && Time_action.getElapsedTime().asSeconds() > Action_delay) {

        selectedIndex++;
        if (!issound) {
            changesound.stop();
        }
        else
        {
            changesound.play();
        }
        if (selectedIndex > 2) selectedIndex = 0;

        Time_action.restart();
    }
    if (isSELECT && Time_action.getElapsedTime().asSeconds() > Action_delay) {

        if (selectedIndex == 0)//resue
        {
            if (!isstart)
                ismoving = 1;
            else
                ismoving = 0;
            isPaused = false;
            gameClock.restart();
            isresume = true;
            menusound.stop();
            if (!ismusic) {
                backgroundsound.stop();
            }
            else {
                backgroundsound.play();
                backgroundsound.setLoop(true);
            }
            fstream f_temp_page;
            f_temp_page.open("files/pagetxt.txt", ios::out);
            f_temp_page << 2;
            f_temp_page.close();
        }
        else if (selectedIndex == 1) //settings
        {
            Time_page.restart();
            Time_action.restart();
            setting(issound, ismusic, 1);

        }
        else if (selectedIndex == 2) //exit
        {
            backgroundsound.stop();
            menusound.stop();
            isPaused = false;
            isquit = true;
            is_ai = true;
            if (!ismusic) {
                menusound.stop();
                backgroundsound.stop();
            }

        }
    }

    Event event;
    while (window.pollEvent(event))
    {
        float y = Joystick::getAxisPosition(0, Joystick::Y);
        if (event.type == Event::Closed)
        {
            window.close();
        }
        else if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed) {
            if (event.key.code == Keyboard::Up || y < -50) {
                selectedIndex--;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                if (selectedIndex < 0) selectedIndex = 2;
            }
            else if (event.key.code == Keyboard::Down || y > 50) {
                selectedIndex++;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                if (selectedIndex > 2) selectedIndex = 0;
            }
            else if (event.key.code == Keyboard::Enter || Joystick::isButtonPressed(0, 2)) {
                if (selectedIndex == 0)//resue
                {
                    if (!isstart)
                        ismoving = 1;
                    else
                        ismoving = 0;
                    isPaused = false;
                    gameClock.restart();
                    isresume = true;
                    menusound.stop();
                    if (!ismusic) {
                        backgroundsound.stop();
                    }
                    else {
                        backgroundsound.play();
                        backgroundsound.setLoop(true);
                    }
                }
                else if (selectedIndex == 1) //settings
                {
                    setting(issound, ismusic, 1);

                }
                else if (selectedIndex == 2) //exit
                {
                    backgroundsound.stop();
                    menusound.stop();
                    isPaused = false;
                    fstream f_temp_page;
                    f_temp_page.open("files/pagetxt.txt", ios::out);
                    f_temp_page << 0;
                    f_temp_page.close();
                    isquit = true;
                    if (!ismusic) {
                        menusound.stop();
                        backgroundsound.stop();
                    }

                }
            }
        }
    }
    resume.setFillColor(selectedIndex == 0 ? Color::Red : Color::White);
    settingpause.setFillColor(selectedIndex == 1 ? Color::Red : Color::White);
    quit.setFillColor(selectedIndex == 2 ? Color::Red : Color::White);
}

void updatedata(int& bonus, int& finalscores, int& indexuser, int& countcoins)
{
    person[indexuser].totalscore += bonus + (finalscores + totalcombo);
    if (person[indexuser].highscore < bonus + (finalscores + totalcombo))
    {
        person[indexuser].highscore = bonus + (finalscores + totalcombo);
    }
    if (person[indexuser].highfloor < finalscores / 10)
    {
        person[indexuser].highfloor = finalscores / 10;
    }
    person[indexuser].gameplayed++;
    person[indexuser].coins += calccoins;
}

void showGameOver(int indexuser, bool issound, bool ismusic, int nextscores, int prevscores, int bonus, int countcoins, int countperson, bool& isquit, bool& isgameover,
    bool& issorry, bool& iscontinue, int& currentnumber, int& selectedIndex)
{

    int finalscores = 0;
    buy.setColor(Color(255, 255, 255, 180));
    numscore.setPosition(840, 240);
    coinss.setCharacterSize(65);
    coinss.setPosition(1050, 50);
    countercoins.setPosition(1230, 55);
    countercoins.setString(to_string(person[indexuser].coins));
    goodsound.stop();
    supersound.stop();
    amazingsound.stop();
    greatsound.stop();
    warningsound.stop();
    ismoving = false;

    if (!issound)
    {
        jumpsound.stop();
        gameoversound.stop();
    }

    if (nextscores >= prevscores) {
        finalscores = nextscores;

    }
    else {
        finalscores = prevscores;
    }
    totalnum.setString(to_string(bonus + (finalscores + totalcombo)));
    floorofstair.setString(to_string(finalscores / 10));
    bonusnum.setString(to_string(bonus));
    if (Time_page.getElapsedTime().asSeconds() > Page_delay)
    {
        ifstream file("files/gesture.txt");
        getline(file, text);
        if (text == "u" && Time_action.getElapsedTime().asSeconds() > Action_delay)
        {
            selectedIndex--;
            if (!issound) {
                changesound.stop();
            }
            else
            {
                changesound.play();
            }
            if (selectedIndex < 0) selectedIndex = 2;
            Time_action.restart();
        }
        else if (text == "d" && Time_action.getElapsedTime().asSeconds() > Action_delay)
        {
            selectedIndex++;
            if (!issound) {
                changesound.stop();
            }
            else
            {
                changesound.play();
            }
            if (selectedIndex > 2) selectedIndex = 0;
            Time_action.restart();
        }
        if (text == "s" && Time_action.getElapsedTime().asSeconds() > Action_delay) {
            Time_action.restart();
            Time_page.restart();
            if (selectedIndex == 0 || selectedIndex == 2) /////////////////////playagain
            {
                updatedata(bonus, finalscores, indexuser, countcoins);
                savetofile(countperson);
                if (!issound) {
                    choosesound.stop();
                }
                else
                {
                    choosesound.play();
                }
                gameoversound.stop();
                if (selectedIndex == 0)
                {
                    fstream f_temp_page;
                    f_temp_page.open("files/pagetxt.txt", ios::out);
                    f_temp_page << 2;
                    f_temp_page.close();
                    isgameover = false;
                }
                else if (selectedIndex == 2)
                {
                    isquit = true;
                }
            }
            else if (selectedIndex == 1)
            {
                if (person[indexuser].coins >= 20 || calccoins >= 20 || (calccoins == 10 && person[indexuser].coins > 10))
                {
                    fstream f_temp_page;
                    f_temp_page.open("files/pagetxt.txt", ios::out);
                    f_temp_page << 2;
                    f_temp_page.close();
                    isgameover = false;
                    score.setPosition(30, 900);
                    numscore.setPosition(200, 760);
                    if (calccoins == 10 && person[indexuser].coins > 10)
                    {
                        calccoins -= 10;
                        person[indexuser].coins -= 10;

                    }
                    else if (calccoins >= 20)
                    {
                        calccoins -= 20;
                    }
                    else if (person[indexuser].coins >= 20)
                    {
                        person[indexuser].coins -= 20;

                    }
                    iscontinue = true;
                }
                else
                {
                    issorry = true;
                }
            }

        }
    }
    Event event;
    while (window.pollEvent(event)) {
        float x = Joystick::getAxisPosition(0, Joystick::X);
        if (event.type == Event::Closed)
        {
            updatedata(bonus, finalscores, indexuser, countcoins);
            savetofile(countperson);
            window.close();
        }
        else if (event.type == Event::KeyPressed || event.type == Event::JoystickMoved || event.type == Event::JoystickButtonPressed) {
            if (event.key.code == Keyboard::Right || x > 50) {
                selectedIndex--;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                if (selectedIndex < 0) selectedIndex = 2;
            }
            else if (event.key.code == Keyboard::Left || x < -50) {
                selectedIndex++;
                if (!issound) {
                    changesound.stop();
                }
                else
                {
                    changesound.play();
                }
                if (selectedIndex > 2) selectedIndex = 0;
            }
            else if (event.key.code == Keyboard::Enter || Joystick::isButtonPressed(0, 2)) {
                if (selectedIndex == 0 || selectedIndex == 2) /////////////////////playagain
                {
                    updatedata(bonus, finalscores, indexuser, countcoins);
                    savetofile(countperson);
                    if (!issound) {
                        choosesound.stop();
                    }
                    else
                    {
                        choosesound.play();
                    }
                    gameoversound.stop();
                    if (selectedIndex == 0)
                    {
                        fstream f_temp_page;
                        f_temp_page.open("files/pagetxt.txt", ios::out);
                        f_temp_page << 2;
                        f_temp_page.close();
                        isgameover = false;
                    }
                    else if (selectedIndex == 2)
                    {
                        isquit = true;
                    }
                }
                else if (selectedIndex == 1)///////////////////continue
                {

                    if (person[indexuser].coins >= 20 || calccoins >= 20 || (calccoins == 10 && person[indexuser].coins > 10))
                    {
                        fstream f_temp_page;
                        f_temp_page.open("files/pagetxt.txt", ios::out);
                        f_temp_page << 2;
                        f_temp_page.close();
                        isgameover = false;
                        score.setPosition(30, 900);
                        numscore.setPosition(200, 760);
                        if (calccoins == 10 && person[indexuser].coins > 10)
                        {
                            calccoins -= 10;
                            person[indexuser].coins -= 10;

                        }
                        else if (calccoins >= 20)
                        {
                            calccoins -= 20;
                        }
                        else if (person[indexuser].coins >= 20)
                        {
                            person[indexuser].coins -= 20;

                        }
                        iscontinue = true;
                    }
                    else
                    {
                        issorry = true;
                    }

                }
            }
        }
    }

    continuee.setFillColor(selectedIndex == 1 ? Color::Red : Color(105, 105, 105));
    playagain.setFillColor(selectedIndex == 0 ? Color::Red : Color::White);
    back.setFillColor(selectedIndex == 2 ? Color::Red : Color::White);
}

void savetofile(int& countperson)
{
    counter.open("files/file counter.txt", ios::out);
    file.open("files/file history.txt", ios::out);
    counter << countperson;
    for (int i = 0;i < countperson;i++)
    {

        file << person[i].name << "\n";
        file << person[i].totalscore << "\n";
        file << person[i].highscore << "\n";
        file << person[i].highfloor << "\n";
        file << person[i].gameplayed << "\n";
        file << person[i].coins << "\n";
        file << person[i].players.poor << "\n";
        file << person[i].players.patrick << "\n";
    }
    file.close();
    counter.close();
}

void countdownBeforeRestart(bool& iscontinue, int& currentNumber)
{

    float elapsed = countdownClock.getElapsedTime().asSeconds();

    if (elapsed >= 1.0f) {
        currentNumber--;
        countdownClock.restart();
    }

    if (currentNumber > 0)
        counterText.setString(to_string(currentNumber));
    else if (currentNumber == 0)
        counterText.setString("GO!");



    window.draw(counterText);

    if (currentNumber < 0)
    {
        iscontinue = false;
    }


}