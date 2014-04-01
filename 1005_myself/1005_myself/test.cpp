//test envp
//YD


//#include <iostream>
//#include <string>
//using namespace std;
//void main(int argc, char*argv[], char*envp[])//envp[] 表述环境变量数组
//{
//	int iNumberLines = 0; // Default is no line numbers.
//	// If more than .EXE filename supplied, and if the /n command-line option is specified, the listing
//	// of environment variables is line-numbered.
//	if (argc == 2 && _stricmp(argv[1], "/n") == 0)
//	{
//		iNumberLines = 1;
//	} // Walk through list of strings until a NULL is encountered.
//	for (int i = 0; envp[i] != NULL; ++i)
//	{
//		if (!iNumberLines)
//			cout << i << ":" << envp[i] << "\n";
//	}
//	getchar();
//}