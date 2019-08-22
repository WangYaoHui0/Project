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
	typedef unordered_set<string> wordSet;	// 存两个文件合起来，词频最大的前n的词

	TextSimilarity();

	void getStopWordTable(const char* stopWordFile);	// 获取停用词表
	wordFreq getWordFreq(const char* file);	// 统计词频
	string UTF8ToGBK(string str);	// 格式传换
	string GBKToUTF8(string str);	// 格式转换
	vector<pair<string, int>> sortByValueReverse(wordFreq& wf);	// 排序
	void selectAimWords(vector<pair<string, int>>& wfvec, wordSet& wset);	// 将前n个词语插入wset
	vector<double> getOneHot(wordSet& wset, wordFreq& wf);	// 得到词频向量
	double cosine(vector<double> oneHot1, vector<double> oneHot2);	// 计算cos，评估相似度
	double getTextSimialrity(const char* file1, const char* file2);	// 求两个文本相似度

	// 定义一个jieba对象
	cppjieba::Jieba _jieba;
	wordSet _stopWordSet;
	int _maxWordNumber;
};