

#include <iostream>
#include <Windows.h>
#include<conio.h>
#include <stdio.h>
using namespace std;
char ar[8][8];

HANDLE hConsole;    // ЦВЕТ
int x, y;
char x2,y2;
int chet = 0;       // ОЧЕРЕДНОСТЬ ХОДА
int counterLWL = 0;   // счетчик ладьи белой    левой
int counterLWR = 0;   // счетчик ладьи белой    правой
int counterLBL = 0;   // счетчик ладби черной   левой
int counterLBR = 0;   // счетчик ладби черной   правой
int counterKW = 0;   // счетчик короля белого
int counterKB = 0;   // счетчик короля черного
int rok;            //Рокировка


int BPW=0;                 // счетчик битого поля для белых
int BPB=0;                 // счетчик битого поля для Черных
int BPsB=-1;                   // столбец черных (битого поля)
int BPsW=-1;                   // столбец белых (битого поля)


//bool check;         // флаг определения ШАХ
//bool check2;         // флаг определения ШАХ
int a2 = 0;           //  коорд."x" короля белый
int b2 = 4;           // координ. "y" короля белый
int a1 = 7;           //  коорд."x" короля черный
int b1 = 4;           // координ. "y" короля черный
int counterK=0;


void initChess();   //  КООРДИНАТЫ ФИГУР ФИГУР
void showAr();      //  ВЫВОД ДОСКИ
void dialog();      //  ДИАЛОГ
void inputAr(int x, int y, int x1, int y1); //ХОДЫ
bool hod(int x, int y, int x1, int y1);       // проверка хода




// проверка хода
bool hod(int x, int y, int x1, int y1) 
{
    bool flag = false;
    bool flagL = false;
    switch (ar[x][y])
    {
        // Пешка Белая
    case 'P':
        if (chet % 2 == 0 && ar[x1][y1] >= 'A' && ar[x1][y1] <= 'Z' || chet % 2 != 0 && ar[x1][y1] >= 'a' && ar[x1][y1] <= 'z')break;
        if ((y == BPsB + 1 || y == BPsB - 1) && x == 4 && BPB > 0 && x1 == 5 && y1 == BPsB)
        {
            if ((x1 - 1) % 2 == y1 % 2)ar[x1 - 1][y1] = char(219);
            else ar[x1 - 1][y1] = ' ';
            BPB--;
            flag = true;
        }
        else if (x == 1 && x1 - x == 1 && y == y1 && (ar[x1][y] == ' ' || ar[x1][y] == char(219)))
        {
            BPB--;
            flag = true;
        }
        else if (x == 1 && x1 - x == 2 && y == y1 && (ar[x1][y] == ' ' || ar[x1][y] == char(219)))
        {
            BPW = 1;
            BPB--;
            BPsW = y;
            flag = true;
        }
        else if (x > 1 && y == y1 && x1 - x == 1 && (ar[x1][y] == ' ' || ar[x1][y] == char(219)))
        {
            BPB--;
            flag = true;
        }
        else if ((y1 == y + 1 || y1 == y - 1) && (ar[x1][y1] != ' ' && ar[x1][y1] != char(219)) && x1 - x == 1)
        {
            BPB--;
            flag = true;
        }
        break;
        // Пешка Черная
    case 'p':
        if (chet % 2 == 0 && ar[x1][y1] >= 'A' && ar[x1][y1] <= 'Z' || chet % 2 != 0 && ar[x1][y1] >= 'a' && ar[x1][y1] <= 'z')break;
        if ((y == BPsW + 1 || y == BPsW - 1) && x == 3 && BPW > 0 && x1 == 2 && y1 == BPsW)
        {
            if ((x1 + 1) % 2 == y1 % 2)ar[x1 + 1][y1] = char(219);
            else ar[x1 + 1][y1] = ' ';
            BPW--;
            flag = true;
        }
        if (x == 6 && (x - x1 == 1) && y == y1 && (ar[x1][y] == ' ' || ar[x1][y] == char(219)))
        {
            BPW--;
            flag = true;
        }
        else if (x == 6 && (x - x1 == 2) && y == y1 && (ar[x1][y] == ' ' || ar[x1][y] == char(219)))
        {
            BPB = 1;
            BPW--;
            BPsB = y;
            flag = true;
        }
        else if (x < 6 && y == y1 && x - x1 == 1 && (ar[x1][y] == ' ' || ar[x1][y] == char(219)))
        {
            BPW--;
            flag = true;
        }
        else if ((y1 == y + 1 || y1 == y - 1) && (ar[x1][y1] != ' ' && ar[x1][y1] != char(219)) && x - x1 == 1)
        {
            BPW--;
            flag = true;
        }
        break;
        // Ладья Белая
    case 'L':
        if (chet % 2 == 0 && ar[x1][y1] >= 'A' && ar[x1][y1] <= 'Z' || chet % 2 != 0 && ar[x1][y1] >= 'a' && ar[x1][y1] <= 'z')break;
        if (x1 - x > 1 || x - x1 > 1 || y1 - y > 1 || y - y1 > 1)
        {
            if (x1 > x && y1 == y)
            {
                for (int i = x + 1; i < x1; i++)
                {
                    if (ar[i][y] != ' ' && ar[i][y] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)
                {
                    flag = true;
                    if (x == 0 && y == 0)counterLWL++;
                    else if (x == 0 && y == 7)counterLWR++;
                }
            }

            //рокировка белой левой
            else if (y1 == 3 && y == 0 && x1 == 0 && x == 0 && counterKW == 0 && counterLWL == 0)
            {
                for (int i = y + 1; i < y1; i++)
                {
                    if (ar[x][i] != ' ' && ar[x][i] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)
                {
                    flag = true;
                    counterLWL++;

                    cout << "compleat the castling?" << endl;
                    cout << "1 - yes, 2 -no" << endl;
                    do
                    {
                        cin >> rok;
                        if (rok == 1)
                        {
                            ar[0][4] = char(219);
                            ar[0][2] = 'K';
                            counterKW++;
                        }
                        else if (rok == 2)
                        {
                            counterLWL--;
                            break;
                        }
                        else if (rok > 2 || rok < 1)
                        {
                            cout << "unacceptable symbol" << endl;
                            cout << "try again" << endl;
                        }
                    } while (rok != 1 && rok != 2);
                }
            }
            //рокировка белой правой
            else if (y1 == 5 && y == 7 && x1 == 0 && x == 0 && counterKW == 0 && counterLWR == 0)
            {
                for (int i = y - 1; i > y1; i--)
                {
                    if (ar[x][i] != ' ' && ar[x][i] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)
                {
                    flag = true;
                    counterLWR++;

                    cout << "compleate the castling again?" << endl;
                    cout << "1 - yes, 2 -no" << endl;
                    do
                    {
                        cin >> rok;
                        if (rok == 1)
                        {
                            ar[0][4] = char(219);
                            ar[0][6] = 'K';
                            counterKW++;
                        }
                        else if (rok == 2)
                        {
                            counterLWR--;
                            break;
                        }
                        else if (rok > 2 || rok < 1)
                        {
                            cout << "unacceptable symbol" << endl;
                            cout << "try again" << endl;
                        }
                    } while (rok != 1 && rok != 2);
                }
            }

            else if (x1 < x&& y1 == y)
            {
                for (int i = x - 1; i > x1; i--)
                {
                    if (ar[i][y] != ' ' && ar[i][y] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)
                {
                    flag = true;
                    if (x == 0 && y == 0)counterLWL++;
                    else if (x == 0 && y == 7)counterLWR++;
                }
            }

            else if (y1 > y && x1 == x)
            {
                for (int i = y + 1; i < y1; i++)
                {
                    if (ar[x][i] != ' ' && ar[x][i] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)
                {
                    flag = true;
                    if (x == 0 && y == 0)counterLWL++;
                    else if (x == 0 && y == 7)counterLWR++;
                }
            }

            else if (y1 < y&& x1 == x)
            {
                for (int i = y - 1; i > y1; i--)
                {
                    if (ar[x][i] != ' ' && ar[x][i] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)
                {
                    flag = true;
                    if (x == 0 && y == 0)counterLWL++;
                    else if (x == 0 && y == 7)counterLWR++;
                }
            }
        }
        else if (x1 - x == 1 || x - x1 == 1 || y1 - y == 1 || y - y1 == 1)
        {
            if (x1 > x && y1 == y)
            {
                flag = true;
                if (x == 0 && y == 0)counterLWL++;
                else if (x == 0 && y == 7)counterLWR++;
            }
            else if (x1 < x && y1 == y)
            {
                flag = true;
                if (x == 0 && y == 0)counterLWL++;
                else if (x == 0 && y == 7)counterLWR++;
            }
            else if (y1 > y && x1 == x)
            {
                flag = true;
                if (x == 0 && y == 0)counterLWL++;
                else if (x == 0 && y == 7)counterLWR++;
            }
            else if (y1 < y && x1 == x)
            {
                flag = true;
                if (x == 0 && y == 0)counterLWL++;
                else if (x == 0 && y == 7)counterLWR++;
            }
        }
        break;
        // Ладья Черная
    case 'l':
        if (chet % 2 == 0 && ar[x1][y1] >= 'A' && ar[x1][y1] <= 'Z' || chet % 2 != 0 && ar[x1][y1] >= 'a' && ar[x1][y1] <= 'z')break;
        if (x1 - x > 1 || x - x1 > 1 || y1 - y > 1 || y - y1 > 1)
        {
            if (x1 > x && y1 == y)
            {
                for (int i = x + 1; i < x1; i++)
                {
                    if (ar[i][y] != ' ' && ar[i][y] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)
                {
                    flag = true;
                    if (x == 7 && y == 0)counterLBL++;
                    else if (x == 7 && y == 7)counterLBR++;
                }
            }
            //рокировка черной правой
            else if (y1 == 5 && y == 7 && x1 == 7 && x == 7 && counterKB == 0 && counterLBR == 0)
            {
                for (int i = y - 1; i > y1; i--)
                {
                    if (ar[x][i] != ' ' && ar[x][i] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)
                {
                    flag = true;
                    counterLBR++;

                    cout << "compleate the castling?" << endl;
                    cout << "1 - yes, 2 -no" << endl;
                    do
                    {
                        cin >> rok;
                        if (rok == 1)
                        {
                            ar[7][4] = ' ';
                            ar[7][6] = 'k';
                            counterKB++;
                        }
                        else if (rok == 2)
                        {
                            counterLBR--;
                            break;
                        }
                        else if (rok > 2 || rok < 1)
                        {
                            cout << "unacceptable symbol" << endl;
                            cout << "try again" << endl;
                        }
                    } while (rok != 1 && rok != 2);
                }
            }
            //рокировка черной левой
            else if (y1 == 3 && y == 0 && x1 == 7 && x == 7 && counterKB == 0 && counterLBL == 0)
            {
                for (int i = y + 1; i < y1; i++)
                {
                    if (ar[x][i] != ' ' && ar[x][i] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)
                {
                    flag = true;
                    counterLBL++;

                    cout << "compleate the castling?" << endl;
                    cout << "1 - yes, 2 -no" << endl;
                    do
                    {
                        cin >> rok;
                        if (rok == 1)
                        {
                            ar[7][4] = ' ';
                            ar[7][6] = 'k';
                            counterKB++;
                        }
                        else if (rok == 2)
                        {
                            counterLBL--;
                            break;
                        }
                        else if (rok > 2 || rok < 1)
                        {
                            cout << "unacceptable symbol" << endl;
                            cout << "try again" << endl;
                        }
                    } while (rok != 1 && rok != 2);
                }
            }
            else if (x1 < x&& y1 == y)
            {
                for (int i = x - 1; i > x1; i--)
                {
                    if (ar[i][y] != ' ' && ar[i][y] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)
                {
                    flag = true;
                    if (x == 7 && y == 0)counterLBL++;
                    else if (x == 7 && y == 7)counterLBR++;
                }
            }
            else if (y1 > y && x1 == x)
            {
                for (int i = y + 1; i < y1; i++)
                {
                    if (ar[x][i] != ' ' && ar[x][i] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)
                {
                    flag = true;
                    if (x == 7 && y == 0)counterLBL++;
                    else if (x == 7 && y == 7)counterLBR++;
                }
            }

            else if (y1 < y&& x1 == x)
            {
                for (int i = y - 1; i > y1; i--)
                {
                    if (ar[x][i] != ' ' && ar[x][i] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)
                {
                    flag = true;
                    if (x == 7 && y == 0)counterLBL++;
                    else if (x == 7 && y == 7)counterLBR++;
                }
            }
        }
        if (x1 - x == 1 || x - x1 == 1 || y1 - y == 1 || y - y1 == 1)
        {
            if (x1 > x && y1 == y)
            {
                flag = true;
                if (x == 7 && y == 0)counterLBL++;
                else if (x == 7 && y == 7)counterLBR++;
            }
            else if (x1 < x && y1 == y)
            {
                flag = true;
                if (x == 7 && y == 0)counterLBL++;
                else if (x == 7 && y == 7)counterLBR++;
            }
            else if (y1 > y && x1 == x)
            {
                flag = true;
                if (x == 7 && y == 0)counterLBL++;
                else if (x == 7 && y == 7)counterLBR++;
            }
            else if (y1 < y && x1 == x)
            {
                flag = true;
                if (x == 7 && y == 0)counterLBL++;
                else if (x == 7 && y == 7)counterLBR++;
            }
        }
        break;
        // Офицер Черный
    case 'e':
        if (chet % 2 == 0 && ar[x1][y1] >= 'A' && ar[x1][y1] <= 'Z' || chet % 2 != 0 && ar[x1][y1] >= 'a' && ar[x1][y1] <= 'z')break;
        if (x1 - x > 1 || x - x1 > 1)
        {
            if (x1 > x && x1 - x == y1 - y)                                       // Диагональ верхняя правая
            {
                for (int i = x + 1, j = y + 1; i < x1; i++, j++)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (y > y1 && y1 == y - (x1 - x))                              // Диагональ верхняя левая
            {
                for (int i = x + 1, j = y - 1; i < x1; i++, j--)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (x > x1 && x1 == x - (y1 - y))                              // Диагональ нижняя правая
            {
                for (int i = x - 1, j = y + 1; i > x1; i--, j++)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (x > x1 && x - x1 == y - y1)                                // Диагональ нижняя левая
            {
                for (int i = x - 1, j = y - 1; i > x1; i--, j--)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
        }
        else if (x1 - x == 1 || x - x1 == 1)                               //На один ход
        {
            if (x1 - x == y1 - y)
            {
                flag = true;
            }
            else if (y1 == y - (x1 - x))
            {
                flag = true;
            }
            else if (x1 == x - (y1 - y))
            {
                flag = true;
            }
            else if (x - x1 == y - y1)
            {
                flag = true;
            }
        }
        break;
        //  Офицер белый
    case 'E':
        if (chet % 2 == 0 && ar[x1][y1] >= 'A' && ar[x1][y1] <= 'Z' || chet % 2 != 0 && ar[x1][y1] >= 'a' && ar[x1][y1] <= 'z')break;
        if (x1 - x > 1 || x - x1 > 1)
        {
            if (x1 > x && x1 - x == y1 - y)                                       // Диагональ верхняя правая
            {
                for (int i = x + 1, j = y + 1; i < x1; i++, j++)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (y > y1 && y1 == y - (x1 - x))                              // Диагональ верхняя левая
            {
                for (int i = x + 1, j = y - 1; i < x1; i++, j--)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (x > x1 && x1 == x - (y1 - y))                              // Диагональ нижняя правая
            {
                for (int i = x - 1, j = y + 1; i > x1; i--, j++)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (x > x1 && x - x1 == y - y1)                                // Диагональ нижняя левая
            {
                for (int i = x - 1, j = y - 1; i > x1; i--, j--)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
        }
        else if (x1 - x == 1 || x - x1 == 1)
        {
            if (x1 - x == y1 - y)
            {
                flag = true;
            }
            else if (y1 == y - (x1 - x))
            {
                flag = true;
            }
            else if (x1 == x - (y1 - y))
            {
                flag = true;
            }
            else if (x - x1 == y - y1)
            {
                flag = true;
            }
        }
        break;
        // Королева (Ферзь) Белая
    case 'Q':
        if (chet % 2 == 0 && ar[x1][y1] >= 'A' && ar[x1][y1] <= 'Z' || chet % 2 != 0 && ar[x1][y1] >= 'a' && ar[x1][y1] <= 'z')break;
        if (x1 - x > 1 || x - x1 > 1 || y1 - y > 1 || y - y1 > 1)
        {
            if (x1 > x && x1 - x == y1 - y)                                       // Диагональ верхняя правая
            {
                for (int i = x + 1, j = y + 1; i < x1; i++, j++)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (y > y1 && y1 == y - (x1 - x))                              // Диагональ верхняя левая
            {
                for (int i = x + 1, j = y - 1; i < x1; i++, j--)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (x > x1 && x1 == x - (y1 - y))                              // Диагональ нижняя правая
            {
                for (int i = x - 1, j = y + 1; i > x1; i--, j++)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (x > x1 && x - x1 == y - y1)                                // Диагональ нижняя левая
            {
                for (int i = x - 1, j = y - 1; i > x1; i--, j--)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;

            }
            else if (x1 > x && y1 == y)
            {
                for (int i = x + 1; i < x1; i++)
                {
                    if (ar[i][y] != ' ' && ar[i][y] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false) flag = true;
            }
            else if (x1 < x&& y1 == y)
            {
                for (int i = x - 1; i > x1; i--)
                {
                    if (ar[i][y] != ' ' && ar[i][y] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false) flag = true;
            }
            else if (y1 > y && x1 == x)
            {
                for (int i = y + 1; i < y1; i++)
                {
                    if (ar[x][i] != ' ' && ar[x][i] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false) flag = true;
            }
            else if (y1 < y&& x1 == x)
            {
                for (int i = y - 1; i > y1; i--)
                {
                    if (ar[x][i] != ' ' && ar[x][i] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false) flag = true;
            }
        }
        else if (x1 - x == 1 || x - x1 == 1 || y1 - y == 1 || y - y1 == 1)    // На один ход
        {
            if (x1 > x && y1 == y)
            {
                flag = true;
            }
            else if (x1 < x && y1 == y)
            {
                flag = true;
            }
            else if (y1 > y && x1 == x)
            {
                flag = true;
            }
            else if (y1 < y && x1 == x)
            {
                flag = true;
            }
            else if (x1 - x == y1 - y)
            {
                flag = true;
            }
            else if (y1 == y - (x1 - x))
            {
                flag = true;
            }
            else if (x1 == x - (y1 - y))
            {
                flag = true;
            }
            else if (x - x1 == y - y1)
            {
                flag = true;
            }
        }
        break;

        // Королева (Ферзь) Черная
    case 'q':
        if (chet % 2 == 0 && ar[x1][y1] >= 'A' && ar[x1][y1] <= 'Z' || chet % 2 != 0 && ar[x1][y1] >= 'a' && ar[x1][y1] <= 'z')break;
        if (x1 - x > 1 || x - x1 > 1 || y1 - y > 1 || y - y1 > 1)
        {
            if (x1 > x && x1 - x == y1 - y)                                       // Диагональ верхняя правая
            {
                for (int i = x + 1, j = y + 1; i < x1; i++, j++)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (y > y1 && y1 == y - (x1 - x))                              // Диагональ верхняя левая
            {
                for (int i = x + 1, j = y - 1; i < x1; i++, j--)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (x > x1 && x1 == x - (y1 - y))                              // Диагональ нижняя правая
            {
                for (int i = x - 1, j = y + 1; i > x1; i--, j++)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (x > x1 && x - x1 == y - y1)                                // Диагональ нижняя левая
            {
                for (int i = x - 1, j = y - 1; i > x1; i--, j--)
                {
                    if (ar[i][j] != ' ' && ar[i][j] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false)flag = true;
            }
            else if (x1 > x && y1 == y)
            {
                for (int i = x + 1; i < x1; i++)
                {
                    if (ar[i][y] != ' ' && ar[i][y] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false) flag = true;
            }
            else if (x1 < x&& y1 == y)
            {
                for (int i = x - 1; i > x1; i--)
                {
                    if (ar[i][y] != ' ' && ar[i][y] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false) flag = true;
            }
            else if (y1 > y && x1 == x)
            {
                for (int i = y + 1; i < y1; i++)
                {
                    if (ar[x][i] != ' ' && ar[x][i] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false) flag = true;
            }

            else if (y1 < y&& x1 == x)
            {
                for (int i = y - 1; i > y1; i--)
                {
                    if (ar[x][i] != ' ' && ar[x][i] != char(219))
                    {
                        flagL = true;
                        break;
                    }
                }
                if (flagL == false) flag = true;
            }
        }
        else if (x1 - x == 1 || x - x1 == 1 || y1 - y == 1 || y - y1 == 1)    // На один ход
        {
            if (x1 > x && y1 == y)
            {
                flag = true;
            }
            else if (x1 < x && y1 == y)
            {
                flag = true;
            }
            else if (y1 > y && x1 == x)
            {
                flag = true;
            }
            else if (y1 < y && x1 == x)
            {
                flag = true;
            }
            else if (x1 - x == y1 - y)
            {
                flag = true;
            }
            else if (y1 == y - (x1 - x))
            {
                flag = true;
            }
            else if (x1 == x - (y1 - y))
            {
                flag = true;
            }
            else if (x - x1 == y - y1)
            {
                flag = true;
            }
        }
        break;
        // Король Белый
    case 'K':
        if (chet % 2 == 0 && ar[x1][y1] >= 'A' && ar[x1][y1] <= 'Z' || chet % 2 != 0 && ar[x1][y1] >= 'a' && ar[x1][y1] <= 'z')break;
        if (x1 - x == 1 || x - x1 == 1 || y1 - y == 1 || y - y1 == 1)    // На один ход
        {
            if (x1 > x && y1 == y)
            {
                flag = true;
                counterKW++;
            }
            else if (x1 < x && y1 == y)
            {
                flag = true;
                counterKW++;
            }
            else if (y1 > y && x1 == x)
            {
                flag = true;
                counterKW++;
            }
            else if (y1 < y && x1 == x)
            {
                flag = true;
                counterKW++;
            }
            else if (x1 - x == y1 - y)
            {
                flag = true;
                counterKW++;
            }
            else if (y1 == y - (x1 - x))
            {
                flag = true;
                counterKW++;
            }
            else if (x1 == x - (y1 - y))
            {
                flag = true;
                counterKW++;
            }
            else if (x - x1 == y - y1)
            {
                flag = true;
                counterKW++;
            }
        }
        if (counterK % 2 == 0) {

            a2 = x1;
            b2 = y1;
        }
        counterK++;
        break;

        // Король Черный
    case 'k':
        if (chet % 2 == 0 && ar[x1][y1] >= 'A' && ar[x1][y1] <= 'Z' || chet % 2 != 0 && ar[x1][y1] >= 'a' && ar[x1][y1] <= 'z')break;
        if (x1 - x == 1 || x - x1 == 1 || y1 - y == 1 || y - y1 == 1)    // На один ход
        {
            if (x1 > x && y1 == y)
            {
                flag = true;
                counterKB++;
            }
            else if (x1 < x && y1 == y)
            {
                flag = true;
                counterKB++;
            }
            else if (y1 > y && x1 == x)
            {
                flag = true;
                counterKB++;
            }
            else if (y1 < y && x1 == x)
            {
                flag = true;
                counterKB++;
            }
            else if (x1 - x == y1 - y)
            {
                flag = true;
                counterKB++;
            }
            else if (y1 == y - (x1 - x))
            {
                flag = true;
                counterKB++;
            }
            else if (x1 == x - (y1 - y))
            {
                flag = true;
                counterKB++;
            }
            else if (x - x1 == y - y1)
            {
                flag = true;
                counterKB++;
            }
        }
        if (counterK % 2 == 0) {

            a1 = x1;
            b1 = y1;
        }
        counterK++;
        break;
        // Конь Белый
    case 'H':
        if (chet % 2 == 0 && ar[x1][y1] >= 'A' && ar[x1][y1] <= 'Z' || chet % 2 != 0 && ar[x1][y1] >= 'a' && ar[x1][y1] <= 'z')break;
        if ((x1 == x + 2 && (y1 == y + 1 || y1 == y - 1)) || (y1 == y + 2 && (x1 == x - 1 || x1 == x + 1)) || (x1 == x - 2 && (y1 == y - 1 || y1 == y + 1)) || (y1 == y - 2 && (x1 == x + 1 || x1 == x - 1)))
        {
            flag = true;
        }
        break;
        // Конь Черный
    case 'h':
        if (chet % 2 == 0 && ar[x1][y1] >= 'A' && ar[x1][y1] <= 'Z' || chet % 2 != 0 && ar[x1][y1] >= 'a' && ar[x1][y1] <= 'z')break;
        if ((x1 == x + 2 && (y1 == y + 1 || y1 == y - 1)) || (y1 == y + 2 && (x1 == x - 1 || x1 == x + 1)) || (x1 == x - 2 && (y1 == y - 1 || y1 == y + 1)) || (y1 == y - 2 && (x1 == x + 1 || x1 == x - 1)))
        {
            flag = true;
        }
        break;
    }
    return flag;
}   









void initChess()
{
    
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 7; j >= 0; j--)
        {
            if (i % 2 == j % 2) ar[i][j] = char(219);
            else ar[i][j] =' ';
        }
    }
    ar[7][7] = 'l';
    ar[7][0] = 'l';
    ar[7][6] = 'h';
    ar[7][1] = 'h';
    ar[7][5] = 'e';
    ar[7][2] = 'e';
    ar[7][4] = 'k';
    ar[7][3] = 'q';

    ar[0][7] = 'L';
    ar[0][0] = 'L';
    ar[0][6] = 'H';
    ar[0][1] = 'H';
    ar[0][5] = 'E';
    ar[0][2] = 'E';
    ar[0][4] = 'K';
    ar[0][3] = 'Q';
    for (int i = 7; i >= 0; i--)
    {
        ar[6][i] = 'p';
        ar[1][i] = 'P';

    }
}
enum ConsoleColor
{
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    LightGray,
    DarkGray,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightMagenta,
    Yellow,
    White
};

void SetColor(int text, int bg) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);                   //Получаем дескриптор вывода на консоль
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));         //Устанавливаем атрибуты текста
}

void showAr()
{
    cout << "\t\t\t\tCHESS" << endl << endl << endl;
    char letter = 'a';
    cout << "\t\t\t  ";
    for (int i = 0; i < 8; i++)
    {
        cout << letter << " ";
        letter++;
    }
    cout << endl;
    cout << "\t\t\t";
    for (int i = 7; i >=0; i--)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < 8; j++)
        {
            if (ar[i][j] == 32 || ar[i][j] == char(219)) 
            {
                cout << ar[i][j] << ar[i][j];
            }
            else 
            {
                if (i % 2 == j % 2)
                {
                   SetColor(White,0);
                    cout << ar[i][j] << " ";                    
                }
                else if (i % 2 != j % 2)
                {
                    SetColor(0,White);
                    cout << ar[i][j] << " ";
                }
            }
            SetColor(0, White);
        }
        cout << i + 1 << " ";
        cout << endl;
        cout << "\t\t\t";

    }
    cout << "  ";
    letter = 'a';
    for (int i = 0; i < 8; i++)
    {
        cout << letter << " ";
        letter++;
    }
    cout << endl << endl;
}
void dialog()
{
    while (true)
    {
        cout << " input chessman's location : ";
        cin >> x2;
        if (x2 == 113)
        {
            system("cls");
            cout << "\t\t\t\tGAME OVER" << endl << endl << endl;
            break;
        }
        cin >> x;
        if (x == 113)
        {
            system("cls");
            cout << "\t\t\t\tGAME OVER" << endl << endl << endl;
            break;
        }
        cout << "what location to chose? :  ";
        cin >> y2;
        if (y2 == 113)
        {
            system("cls");
            cout << "\t\t\t\tGAME OVER" << endl << endl << endl;
            break;
        }
        cin >> y;
        if (y == 113)
        {
            system("cls");
            cout << "\t\t\t\tGAME OVER" << endl << endl << endl;
            break;
        }
        int yv1 = x2 - 97;
        int yv2 = y2 - 97;
        int xv1 = x - 1;
        int xv2 = y - 1;
        inputAr(xv1, yv1, xv2, yv2);
        system("cls");
        showAr();
        //if (checkW(xv2, yv2) == 1)cout << endl<<" wah";

    }
}
    
void inputAr(int x, int y, int x1, int y1)
{
    if (chet % 2 == 0 && ar[x][y] >= 'a' && ar[x][y] <= 'z' || chet % 2 != 0 && ar[x][y] >= 'A' && ar[x][y] <= 'Z')                 // Определение чей ход
    {
        cout << " not your turn " << endl;
        cout << "try again " << endl;
        system("pause");
        system("cls");
        showAr();
        dialog();
    }
    

    if (hod(x,y,x1,y1)==false)
    {
        cout << "wrong move" << endl;
        system("pause");
        system("cls");
        showAr();
        dialog();
    }
    char a = ar[x][y];             // ИЗМЕНЕНИЕ КООРДИНАТ ФИГУРЫ
    if (x % 2 == y % 2)
    {
        ar[x][y] = char(219);
    }
    else if (x % 2 != y % 2)
    {
        ar[x][y] = ' ';
    }
    ar[x1][y1] = a;
    if (x1 == 7 && ar[x1][y1]=='P')
    {
        char w;
        cout << "imput necessary chessman ?" << endl;
        cin >> w;
        while (w != 'L' && w != 'H' && w != 'E' && w != 'Q' && w != 'P')
        {
            cout << "unaccaptable chessman" << endl;
            cin >> w;
        }
        ar[x1][y1] = w;        
    }
    else if (x1 == 0 && ar[x1][y1] == 'p')
    {
        char w;
        cout << "imput necessary chessman ?" << endl;
        cin >> w;
        while (w != 'l' && w != 'h' && w != 'e' && w != 'q' && w != 'p')
        {
            cout << "unaccaptable chessman" << endl;
            cin >> w;
        }
        ar[x1][y1] = w;
    }
    if (chet % 2 == 0) {
        if (hod(x1, y1, a1, b1) == true)
        {
            system("cls");
            showAr();
            cout << endl << "CHECK" << endl;
            system("pause");
        }
    }
    else if (chet % 2 != 0) {
        if (hod(x1, y1, a2, b2) == true) 
        {
            system("cls");
            showAr();
            cout << endl << "CHECK"<<endl;
             system("pause");
        }
    }
    
    chet++;    
}
//bool matt(int x,int y)
//{
//    if (ar[x][y] == 'Q')
//    {
//        if()
//    }
//}

int main()
{
    //setlocale(LC_ALL, "rus");
    char ar[8][8];
    initChess();
	showAr();
    dialog();
}

