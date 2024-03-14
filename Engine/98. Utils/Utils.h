#pragma once

class Utils
{
public:
	static bool StartsWith(const string& str, const string& comp);
	static bool StartsWith(const wstring& str, const wstring& comp);

	static wstring ToWString(const string& value);
	static string ToString(const wstring& value);



	// 여기는 개인적으로 추가한 기능
	// 대/소문자 변환
	static void makeUpperCase(string& str);
	static void makeLowerCase(string& str);

	// 스트링을 div 기준으로 쪼개줌
	static void splitString(
		const string& str,
		const char div,
		vector<string>& strings);
};

