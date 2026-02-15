/*

============ Source code ============
Link        : https://raw.githubusercontent.com/zoelabbb/conio.h/master/conio.h
GitHub      : https://github.com/zoelabbb/conio.h.git
=====================================

*/

/**
 * conio4linux (Conio.h for linux)
 * Copyright (C) 2013 by Alif Ryuu B R
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @author Alif Ryuu B R <zoelabbb@gmail.com>
 * @date 2023-12-21
 * @version 1.1
 */

/*
List funtions
=============
    cprintf
    cscanf
    gotoxy
    clrscr
    textcolor
    textbackground
    wherex
    wherey
    getch
    getche
    ungetch
    kbhit
    putch
    putchar
    cputs
    clreol
    insline (not implemented)
    delline (not implemented)
    cgets   (not implemented)
    getpass (not implemented)
    gettext (not implemented)
    _cprintf
    _cscanf
    _cputs
    _getche
    _kbhit
    _putch
    _ungetch

Instalation for linux
=====================
    Copy file conio.h to /usr/include/
    Run as root user:
      cp conio.h /usr/include/

Example program
===============
//File name: main.cpp
//Compilation: gcc main.cpp -o program_conio -lstdc++
//Test program: ./program_conio
#include<conio.h>
int main(int argc, char *argv[]){
  textbackground(BLUE);
  clrscr();
  textcolor(WHITE);
  gotoxy(30,5);
  cprintf("Hello World WHITE");
  textcolor(YELLOW);
  gotoxy(30,6);
  cprintf("Hello World YELLOW");
  for(int i=0;i<16;i++){
    textcolor(i);
    gotoxy(1,2+i);
    cprintf("Hello World");
    }
  getch();
  return 0;
  }

I need help for
===============
  *Document funtions.
  *Implement funtions not implemented.
  *Add funtions new.
  *Report bugs.

  For any case:
  Send a mail to zoelabbb@gmail.com with the modifications and information: Email, Autor and changes.
  Thanks!!!

*/
#ifndef __CONIO4LINUX_H
#define __CONIO4LINUX_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define BLINK 128

static int background_color = 40;

void reset()
{
    printf("\033[m");
}

void clearLine()
{
    printf("\033[K");
}

void insertLine()
{
    printf("\x1b[1L");
}

void deleteLine()
{
    printf("\033[1M");
}

void setCursorPosition(int x, int y)
{
    printf("\033[%d;%df", y, x);
}

void clearScreen()
{
    printf("\033[%dm\033[2J\033[1;1f", background_color);
}

void setBackgroundColor(int color)
{
    background_color = (color % 16) + 40;
}

void setTextColor(short color)
{
    if (color >= 0 && color < 16)
    {
        printf("\033[0;%d;%dm", 30 + color, background_color);
    }
}

int ungetch(int ch)
{
    return ungetc(ch, stdin);
}

int setEchoMode(int enable)
{
    // 1. 定义变量
    // termios 结构体：用于存储终端的属性配置（比如回显、行缓冲等）
    struct termios oldt, newt;
    int ch;  // 存储读取到的字符

    // 2. 获取当前终端的属性，保存到 oldt（用于后续恢复）
    // STDIN_FILENO 表示标准输入（键盘）
    tcgetattr(STDIN_FILENO, &oldt);

    // 3. 复制原有配置到 newt，基于原有配置修改，避免破坏其他属性
    newt = oldt;

    // 4. 关闭“规范模式（ICANON）”—— 关闭行缓冲
    // 规范模式下，终端会等待回车键才把输入传给程序；关闭后，输入一个字符就立即传给程序
    newt.c_lflag &= ~ICANON;

    // 5. 控制终端回显（ECHO）：输入的字符是否显示在屏幕上
    if (enable)
        newt.c_lflag |= ECHO;  // enable=1：开启回显（输入的字符会显示）
    else
        newt.c_lflag &= ~ECHO; // enable=0：关闭回显（输入的字符不显示）

    // 6. 立即应用新的终端配置（TCSANOW 表示立刻生效）
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // 7. 读取一个字符（因为关闭了行缓冲，按一个键就会立即读取，无需回车）
    ch = getchar();

    // 8. 恢复终端原有配置，避免修改后影响后续操作
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // 9. 返回读取到的字符
    return ch;
}

int getch()
{
    return setEchoMode(0);
}

int getche()
{
    return setEchoMode(1);
}

int wherexy(int *x, int *y)
{
    printf("\033[6n");
    if (getch() != '\x1B')
        return 0;
    if (getch() != '\x5B')
        return 0;
    int in;
    int ly = 0;
    while ((in = getch()) != ';')
        ly = ly * 10 + in - '0';
    int lx = 0;
    while ((in = getch()) != 'R')
        lx = lx * 10 + in - '0';
    *x = lx;
    *y = ly;
}

int wherex()
{
    int x = 0, y = 0;
    wherexy(&x, &y);
    return x;
}

int wherey()
{
    int x = 0, y = 0;
    wherexy(&x, &y);
    return y;
}

int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int putch(const char c)
{
    printf("%c", c);
    return (int)c;
}

int cputs(const char *str)
{
    printf("%s", str);
    return 0;
}

#define _cprintf cprintf
#define _cscanf cscanf
#define _cputs cputs
#define _getche getche
#define _kbhit kbhit
#define _putch putch
#define _ungetch ungetch

#endif
