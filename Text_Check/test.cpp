#include"TextSimilarity.h"

void Test()
{
	TextSimilarity tsy;
	const char* file1 = "E://txt1.txt";
	const char* file2 = "E://txt2.txt";

	double cos;
	cos = tsy.getTextSimialrity(file1, file2);

	cout << "两个文档的相似度：" << cos << endl;
}

int main()
{
	Test();

	system("pause");
	return 0;
}