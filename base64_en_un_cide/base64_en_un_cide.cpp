// base64_en_un_cide.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdio.h>  
#include <cstdio>
#include <stdlib.h>
#include <bitset> 
using namespace std;
void myencoded(char *source, char *tag);
char c_base_char[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d',
                        'e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/' };
int main()
{
    char source[64] = "testAcount.txt";
    char tag[64] = "encode.txt";
    myencoded(source, tag);
    system("pause");
    return 0;
}

void myencoded(char *source, char *tag)
{
    ifstream ifs(source);
    ofstream ofs(tag);
    ofstream ofsoure("soureceAgain.txt");
    ifs.seekg(0, ifs.end);   //追溯到流的尾部
    int ui_file_length = ifs.tellg();  //获取流的长度
    cout << "ui_file_length:" << ui_file_length << endl;
    system("pause");
    ifs.seekg(0, ifs.beg);  //回到流的头部
    char sz_buf[4] = { '\0' };
    char c_tmp[1] = { '\0' };
    char sz_encode[5] = { '\0' };
    sz_encode[4] = '\0';
    int i_encode = 0;
    char c_ch1;
    char c_ch2;
    char c_ch3;
    int b00111111 = 0x3f;
    int b11111111 = 0xff;
    for (int i = 0; i < ui_file_length / 3; i++)
    {
        ifs.read(sz_buf, 3);
        if (!ifs.eof())
        {

            int i_file = 0;
            c_ch1 = sz_buf[i_file];
            i_file++;
            c_ch2 = sz_buf[i_file];
            i_file++;
            c_ch3 = sz_buf[i_file];
            i_encode = 0;
            sz_encode[i_encode] = c_base_char[(c_ch1 >> 2) & b00111111];
            i_encode++;
            sz_encode[i_encode] = c_base_char[((c_ch1 << 4) | ((c_ch2 & b11111111) >> 4)) & b00111111];
            i_encode++;
            sz_encode[i_encode] = c_base_char[((c_ch2 << 2) | ((c_ch3 & b11111111) >> 6)) & b00111111];
            i_encode++;
            sz_encode[i_encode] = c_base_char[c_ch3 & b00111111];
            cout << sz_encode;
            ofs.write(sz_encode, 4);
            ofsoure.write(sz_buf, 3);
        }
        else
        {
            break;
        }
    }
    //处理等号
    i_encode = 0;

    switch (ui_file_length % 3)
    {
    case 1:
        /*ifs.read(sz_buf, 1);
        c_ch1 = sz_buf[0];*/
        /*sz_encode[i_encode] = c_base_char[(c_ch1 >> 2) & b00111111];
        i_encode++;
        sz_encode[i_encode] = c_base_char[ (c_ch1 << 4) & b00111111];*/
        //i_encode++;
        sz_encode[2] = '=';
        //i_encode++;
        sz_encode[3] = '=';
        break;
    case 2:
        /*ifs.read(sz_buf, 2);
        c_ch1 = sz_buf[0];
        c_ch2 = sz_buf[1];*/

        /*sz_encode[i_encode] = c_base_char[(c_ch1 >> 2) & b00111111];
        i_encode++;*/
        //sz_encode[i_encode] = c_base_char[((c_ch1 << 4 & 0x30) | (c_ch2 >> 4 & 0x0f) )];
        //i_encode++;
        //sz_encode[i_encode] = c_base_char[c_ch2 << 2 & 0x3c];
        //i_encode++;
        sz_encode[3] = '=';
        break;
        default:
            break;
        }
    printf("%c%c%c%c", '\b', '\b', '\b', '\b');
    cout << sz_encode;
    ofs.seekp(-4, ios::end);
    ofs.write(sz_encode, 4);
    ofs.close();
    ifs.close();
}