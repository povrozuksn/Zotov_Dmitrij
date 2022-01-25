//========================================================================
//! @file       Main.cpp
//{=======================================================================
//!
//! @brief      <Заголовок>\n
//! @brief      <Подзаголовок>
//!
//! @version    [Version 0.01 alpha, build 1]
//! @author     Copyright (C) <Автор>, <Год> (<Имя> <Почта>)
//! @date       <Дата>
//!
//! @par        Протестировано
//!           - (TODO: список платформ)
//!
//! @todo     - (TODO: список ближайших планов по этому файлу)
//!
//! @bug      - (TODO: список найденных ошибок в этом файле)
//!
//! @par        История изменений файла
//!           - Версия 0.01 Alpha
//!             - Только что созданный файл
//!
//}=======================================================================

#include "TXLib.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "dirent.h"

struct Button
{
 int x;
 int y;
 const char* text;
 string category;
};

void drawButton(Button btn)
{
  txSetColor (TX_WHITE);
  txSetFillColor (TX_BLACK);
  Win32::RoundRect (txDC(), btn.x, btn.y, btn.x+160, btn.y+60, 20, 20);
  txSelectFont("Arial", 45);
  txDrawText(btn.x, btn.y, btn.x+160, btn.y+60, btn.text);
}

struct Picture
{
 int x;
 int y;
 string adress;
 HDC image;
 int w;
 int h;
 bool visible;
 string category;
};


int get_w(string adress)
{
 FILE *f1 = fopen(adress.c_str(), "rb");

 unsigned char headerinfo[54];
 fread(headerinfo, sizeof(unsigned char), 54, f1);

 int w = *(int*)&headerinfo[18];

 return w;
}

int get_h(string adress)
{
 FILE *f1 = fopen(adress.c_str(), "rb");

 unsigned char headerinfo[54];
 fread(headerinfo, sizeof(unsigned char), 54, f1);

 int h = *(int*)&headerinfo[22];

 return h;
}

int readFromDir(string adress, Picture menuPicture[], int count_pics)
{
 DIR *dir;
 struct dirent *ent;
 int lastY = 20;
 if((dir = opendir (adress.c_str())) != NULL)
 {
 while ((ent = readdir(dir)) != NULL)
  {
   if((string)ent->d_name != "." &&
      (string)ent->d_name != "..")
      {
       menuPicture[count_pics].y = lastY;
       menuPicture[count_pics].adress = adress + (string)ent->d_name;
       count_pics++;
       lastY+=100;

      }
  }
  closedir(dir);
 }
 return count_pics;
}

void drawPicture(Picture pct)
{
if (pct.visible)
{
Win32::TransparentBlt(txDC(), pct.x, pct.y, 100, 100, pct.image, 0, 0, pct.w, pct.h, TX_WHITE);
}
}

void drawPicture2(Picture pct)
{
if (pct.visible)
{
Win32::TransparentBlt(txDC(), pct.x, pct.y, pct.w, pct.h, pct.image, 0, 0, pct.w, pct.h, TX_WHITE);
}
}

 bool Click(Button btn)
 {
  if(txMouseButtons() == 1 &&
   txMouseX() >= btn.x &&
   txMouseX() <= btn.x+160 &&
   txMouseY() >= btn.y &&
   txMouseY() <= btn.y+60)
   {
    return 1;
   }
   else
   {
    return 0;
   }

 }









int main()
    {
    txCreateWindow (1200, 600);

     HDC backgroundgraf = txLoadImage("backgroundgraf.bmp");

int count_pics = 0;


     Picture menuPicture[1000];
     /*
     menuPicture[0] = {50, 120, "Chairs/chair.bmp"};
     menuPicture[1] = {50, 280, "Chairs/chair2.bmp"};
     menuPicture[2] = {50, 440, "Chairs/chair3.bmp"};
     menuPicture[3] = {50, 120, "Tables/table.bmp"};
     menuPicture[4] = {50, 280, "Tables/table2.bmp"};
     menuPicture[5] = {50, 440, "Tables/table3.bmp"};
     menuPicture[6] = {50, 120, "Walls/wall.bmp"};
     menuPicture[7] = {50, 280, "Walls/wall2.bmp"};
     menuPicture[8] = {50, 440, "Walls/wall3.bmp"};
     menuPicture[9] = {50, 120, "Windows/window.bmp"};
     menuPicture[10] = {50, 280, "Windows/window2.bmp"};
     menuPicture[11] = {50, 440, "Windows/window3.bmp"};
     menuPicture[12] = {50, 120, "Sofa/sofa1.bmp"};
     menuPicture[13] = {50, 280, "Sofa/sofa2.bmp"};
     menuPicture[14] = {50, 440, "Sofa/sofa3.bmp"};
      */


     Picture centralPicture[1000];

     count_pics = readFromDir("Pictures/Chairs/", menuPicture, count_pics);
     count_pics = readFromDir("Pictures/Tables/", menuPicture, count_pics);
     count_pics = readFromDir("Pictures/Walls/", menuPicture, count_pics);
     count_pics = readFromDir("Pictures/Windows/", menuPicture, count_pics);
     count_pics = readFromDir("Pictures/Sofa/", menuPicture, count_pics);

     Button btn[5];
     btn[0] = {35, 20, "Стул", "Chairs"};
     btn[1] = {240, 20,"Стол", "Tables"};
     btn[2] = {465, 20, "Стены", "Walls"};
     btn[3] = {675, 20, "Окно", "Windows"};
     btn[4] = {875, 20, "Диваны", "Sofa"};









   int numberpic = 0;

   int choose = -1;
   int vybor = -1;
   bool mouse_release = false;

for(int npic=0; npic<count_pics; npic++)
{
menuPicture[npic].x = 10;

 menuPicture[npic].image =txLoadImage(menuPicture[npic].adress.c_str());

 menuPicture[npic].w=get_w(menuPicture[npic].adress);
 menuPicture[npic].h=get_h(menuPicture[npic].adress);
 menuPicture[npic].visible = false;


 string stroka = menuPicture[npic].adress;

 int pos_1 = stroka.find("/");
 int pos_2 = stroka.find("/", pos_1+1);

 menuPicture[npic].category = stroka.substr(pos_1+1, pos_2-pos_1-1);

}



    while(!GetAsyncKeyState (VK_ESCAPE))
    {
      txBegin();


    txClear();





    for (int nk=0; nk<5; nk++)
{
drawButton (btn[nk]);
}



for(int npic=0; npic<count_pics; npic++)
{
drawPicture(menuPicture[npic]);
}

for(int npic=0; npic<count_pics; npic++)
{
drawPicture2(centralPicture[npic]);
}

for (int npic=0; npic<count_pics; npic++)
{
  if (txMouseButtons() == 1 &&
      menuPicture[npic].visible &&
      txMouseX() >= menuPicture[npic].x &&
      txMouseX() <= menuPicture[npic].x+menuPicture[npic].w &&
      txMouseY() >= menuPicture[npic].y &&
      txMouseY() <= menuPicture[npic].y+menuPicture[npic].h)
      {
      while(txMouseButtons() == 1)
      {
       txSleep(10);
      }
         centralPicture[numberpic] = {300,
                                      100,
                                      menuPicture[npic].adress,
                                      menuPicture[npic].image,
                                      menuPicture[npic].w,
                                      menuPicture[npic].h,
                                      menuPicture[npic].visible,
                                      menuPicture[npic].category};
          numberpic++;
      }
}
/*
char str[100];
sprintf(str, "numberpic = %d", numberpic);
txTextOut(800, 300, str);
*/

   for(int npic = 0; npic< count_pics; npic++)
   {
   if(txMouseButtons() == 1 &&
    txMouseX() >=  centralPicture[npic].x &&
    txMouseX() <=  centralPicture[npic].x + centralPicture[npic].w &&
    txMouseY() >= centralPicture[npic].y &&
    txMouseY() <= centralPicture[npic].y + centralPicture[npic].h)
     {
      choose = npic;
      mouse_release = false;
     }
    }

if(choose>=0)
{
if(txMouseButtons() == 1 && !mouse_release)
{
centralPicture[choose].x = txMouseX() - centralPicture[choose].w/2;
centralPicture[choose].y = txMouseY() - centralPicture[choose].h/2;
}
else
if(txMouseButtons() != 1)
{
mouse_release=true;
}
}

for (int nk=0; nk<5; nk++)
{
if (Click(btn[nk]))
{
for (int npic=0; npic<count_pics; npic++)
{
menuPicture[npic].visible=false;
if (menuPicture[npic].category == btn[nk].category)
{
menuPicture[npic].visible=true;
}
}
}

}


if(choose >= 0 && GetAsyncKeyState(VK_DELETE))
     {
       centralPicture[choose] = centralPicture[count_pics - 1];
       numberpic--;
       choose = -1;

     }


     txEnd();
    }

for (int npic=0; npic<count_pics; npic++)
{
txDeleteDC(menuPicture[npic].image);
txDeleteDC(centralPicture[npic].image);
}




    return 0;
    }

