#pragma once

class Utils
{
public:
	static bool StartsWith(const string& str, const string& comp);
	static bool StartsWith(const wstring& str, const wstring& comp);

	static wstring ToWString(const string& value);
	static string ToString(const wstring& value);



	// ����� ���������� �߰��� ���
	// ��/�ҹ��� ��ȯ
	static void makeUpperCase(string& str);
	static void makeLowerCase(string& str);

	// ��Ʈ���� div �������� �ɰ���
	static void splitString(
		const string& str,
		const char div,
		vector<string>& strings);
};

