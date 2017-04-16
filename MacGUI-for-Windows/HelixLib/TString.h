#pragma once

#include <tchar.h>

namespace HelixLib {
	
	class TString {
	private:
		TCHAR* m_str;
		size_t m_str_length;
		size_t m_str_size;

		void UseDefault();
	public:
		~TString();
		TString();
		TString(_In_ const TCHAR* srcString);
		TString(_In_ const TString& srcString);
		

		TString& operator=(const TString& srcString);
		TString& operator=(const TCHAR* srcString);
		TString& operator=(const TCHAR& srcTChar);
	};
}