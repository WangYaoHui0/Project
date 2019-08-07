#include"TextSimilarity.h"

using namespace std;

// ���幹�캯��
TextSimilarity::TextSimilarity()
	:_jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH), _maxWordNumber(30)
{
	getStopWordTable(STOP_WORD_PATH.c_str());
}

// ��ȡͣ�ôʱ�
void TextSimilarity::getStopWordTable(const char* stopWordFile)
{
	ifstream isf(stopWordFile);
	if (!isf.is_open())
	{
		cout << "open file:" << stopWordFile << endl;
		return;
	}

	while (!isf.eof())
	{
		string str;
		getline(isf, str);
		_stopWordSet.insert(str);
	}
	isf.close();
}

// ͳ�ƴ�Ƶ
TextSimilarity::wordFreq TextSimilarity::getWordFreq(const char* file)
{
	ifstream fln(file);
	if (!fln.is_open())
	{
		cout << "open file:" << file << "failed";
		return wordFreq();
	}

	string line;
	wordFreq wf;
	while (!fln.eof())
	{
		// ���ж�ȡ
		getline(fln, line);
		// GBK --> UTF8
		line = GBKToUTF8(line);
		vector<string> words;
		// ���ı���ǰ�зִ�
		_jieba.Cut(line, words, true);

		// ͳ�ƴ�Ƶ
		for (const auto& e : words)
		{
			// ȥ��ͣ�ô�
			if (_stopWordSet.count(e))
				continue;
			else
			{
				// ͳ�ƴ�Ƶ
				if (wf.count(e))
					wf[e]++;
				else
					wf[e] = 1;
			}
		}
	}
	return wf;
}

// GBK --> UTF8
string TextSimilarity::GBKToUTF8(string str)
{
	// ��ȡbuffer��С
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len];
	// GBK-->UTF16
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wstr, len);

	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* utf8 = new char[len];
	// UTF16-->UTF8
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, len, NULL, NULL);

	string ret(utf8);
	if (wstr != NULL)
	{
		delete[] wstr;
		wstr = NULL;
	}
	if (utf8 != NULL)
	{
		delete[] utf8;
		utf8 = NULL;
	}
	return ret;
}

// UTF8 --> GBK
string TextSimilarity::UTF8ToGBK(string str)
{
	// ��ȡbuffer��С
	int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len];
	// UTF8-->UTF16
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr, len);

	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* gbk = new char[len];
	// UTF16-->GBK
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, gbk, len, NULL, NULL);

	string ret(gbk);
	if (wstr != NULL)
	{
		delete[] wstr;
		wstr = NULL;
	}
	if (gbk != NULL)
	{
		delete[] gbk;
		gbk = NULL;
	}
	return ret;
}

// �Ƚ�
bool cmpReverse(pair<string, int> lp, pair<string, int> rp)
{
	return lp.second > rp.second;
}

// �Եõ��Ĵ�Ƶ������������
vector<pair<string, int>> TextSimilarity::sortByValueReverse(wordFreq& wf)
{
	vector<pair<string, int>> wfvector(wf.begin(), wf.end());
	sort(wfvector.begin(), wfvector.end(), cmpReverse);
	return wfvector;
}

// ����Ƶ����ǰn�Ĵʲ���set
void TextSimilarity::selectAimWords(vector<pair<string, int>>&wfvec, wordSet& wset)
{
	int len = wfvec.size();
	len = len > _maxWordNumber ? _maxWordNumber : len;
	for (int i = 0; i < len; i++)
	{
		wset.insert(wfvec[i].first);
	}
}

// ���Ƶ����
vector<double> TextSimilarity::getOneHot(wordSet& wset, wordFreq& wf)
{
	vector<double> oneHot;

	// ����wset�е�ÿһ����
	for (const auto& e : wset)
	{
		if (wf.count(e))
			oneHot.push_back(wf[e]);
		else
			oneHot.push_back(0);
	}
	return oneHot;
}

// ����cos���������ƶ�
double TextSimilarity::cosine(vector<double> oneHot1, vector<double> oneHot2)
{
	assert(oneHot1.size() == oneHot2.size());

	double numerator = 0;
	double modular1 = 0;
	double modular2 = 0;
	double ret = 0;
	size_t i = 0;
	for (i = 0; i < oneHot1.size(); i++)
	{
		numerator += oneHot1[i] * oneHot2[i];
	}

	for (i = 0; i < oneHot1.size(); i++)
	{
		modular1 += pow(oneHot1[i], 2);
	}
	modular1 = pow(modular1, 0.5);

	for (i = 0; i < oneHot2.size(); i++)
	{
		modular2 += pow(oneHot1[i], 2);
	}
	modular2 = pow(modular2, 0.5);

	ret = numerator / (modular1 * modular2);
	return ret;
}


// �����к�����װ��һ���ӿڣ��������ĵ����ı����ƶ�
double TextSimilarity::getTextSimialrity(const char* file1, const char*file2)
{
	// ��������
	TextSimilarity tsy;

	// ��ȡ��Ƶ
	wordFreq wf1 = tsy.getWordFreq(file1);
	wordFreq wf2 = tsy.getWordFreq(file2);

	// ����
	vector<pair<string, int>> v1 = tsy.sortByValueReverse(wf1);
	vector<pair<string, int>> v2 = tsy.sortByValueReverse(wf2);

	// ��ȡ���ĵ���Ƶ�����ǰn������set
	wordSet wset;
	tsy.selectAimWords(v1, wset);
	tsy.selectAimWords(v2, wset);

	// ���Ƶ����
	vector<double> oneHot1 = tsy.getOneHot(wset, wf1);
	vector<double> oneHot2 = tsy.getOneHot(wset, wf2);

	// ����cos���������ƶ�
	double cos = tsy.cosine(oneHot1, oneHot2);
	return cos;
}