#define _CRT_SECURE_NO_WARNINGS 1

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <vector>
#include <assert.h>

#include "cppjieba/jieba.hpp"

using namespace std;

const string DICT_PATH = "E://cppjieba/dict/jieba.dict.utf8";
const string HMM_PATH = "E://cppjieba/dict/hmm_model.utf8";
const string USER_DICT_PATH = "E://cppjieba/dict/user.dict.utf8";
const string IDF_PATH = "E://cppjieba/dict/idf.utf8";
const string STOP_WORD_PATH = "E://cppjieba/dict/stop_words.utf8";

class TextSimilarity
{
public:
	typedef unordered_map<string, int> wordFreq;
	typedef unordered_set<string> wordSet;	// �������ļ�����������Ƶ����ǰn�Ĵ�

	TextSimilarity();

	void getStopWordTable(const char* stopWordFile);	// ��ȡͣ�ôʱ�
	wordFreq getWordFreq(const char* file);	// ͳ�ƴ�Ƶ
	string UTF8ToGBK(string str);	// ��ʽ����
	string GBKToUTF8(string str);	// ��ʽת��
	vector<pair<string, int>> sortByValueReverse(wordFreq& wf);	// ����
	void selectAimWords(vector<pair<string, int>>& wfvec, wordSet& wset);	// ��ǰn���������wset
	vector<double> getOneHot(wordSet& wset, wordFreq& wf);	// �õ���Ƶ����
	double cosine(vector<double> oneHot1, vector<double> oneHot2);	// ����cos���������ƶ�
	double getTextSimialrity(const char* file1, const char* file2);	// �������ı����ƶ�

	// ����һ��jieba����
	cppjieba::Jieba _jieba;
	wordSet _stopWordSet;
	int _maxWordNumber;
};