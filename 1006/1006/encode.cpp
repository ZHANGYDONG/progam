////本题目的 encode(编码)代码：
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <map>
//#include <string>
//using namespace std;
//
////求mod函数
//int _mod(int a, int b)
//{
//	int i = 1;
//	while (a < 0)
//	{
//		a += i*b;
//		i++;
//	}
//	return a % b;
//}
// 
////main
//int encode()
//{
//	fstream out("log.txt");
//	if (!out.is_open())
//	{
//		cout << "cannot open log.txt";
//	}
//
//
//	//字母表
//	map<string, int> word_num;
//	word_num[string("_")] = 0;
//	word_num[string("a")] = 1;
//	word_num[string("b")] = 2;
//	word_num[string("c")] = 3;
//	word_num[string("d")] = 4;
//	word_num[string("e")] = 5;
//	word_num[string("f")] = 6;
//	word_num[string("g")] = 7;
//	word_num[string("h")] = 8;
//	word_num[string("i")] = 9;
//	word_num[string("j")] = 10;
//	word_num[string("k")] = 11;
//	word_num[string("l")] = 12;
//	word_num[string("m")] = 13;
//	word_num[string("n")] = 14;
//	word_num[string("o")] = 15;
//	word_num[string("p")] = 16;
//	word_num[string("q")] = 17;
//	word_num[string("r")] = 18;
//	word_num[string("s")] = 19;
//	word_num[string("t")] = 20;
//	word_num[string("u")] = 21;
//	word_num[string("v")] = 22;
//	word_num[string("w")] = 23;
//	word_num[string("x")] = 24;
//	word_num[string("y")] = 25;
//	word_num[string("z")] = 26;
//	word_num[string(".")] = 27;
//
//	string ciplaintable = "_abcdefghijklmnopqrstuvwxyz.";
//	//运算的 k值
//	int key;
//	while (cin >> key && key != 0)
//	{
//		string plaintext;
//		string ciphertext = "";
//		//接收输入的信息
//		cin >> plaintext;
//		//建立对于动态数组
//		int len = plaintext.size();
//		int *plaincode = new int[len];
//		int *ciplaincode = new int[len];
//		for (int i = 0; i != len; i++)
//		{
//			string s(1, plaintext[i]);
//			plaincode[i] = word_num[string(s)];
//			out << "plain: " << plaincode[i] << endl;
//		}
//		for (int i = 0; i != len; i++)
//		{
//			int j = _mod(key * i, len);
//			ciplaincode[i] = _mod((plaincode[j] - i), 28);
//			ciphertext = ciphertext + ciplaintable[ciplaincode[i]];
//			out << "cipalin :" << ciplaincode[i] << endl;
//		}
//		ciphertext = ciphertext.c_str();
//		cout << ciphertext << endl;
//		plaintext.clear();
//		delete[] plaincode;
//		delete[] ciplaincode;
//	}
//	system("pause");
//	out.close();
//	return 0;
//}