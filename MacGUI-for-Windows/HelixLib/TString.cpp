//#define _CRT_SECURE_NO_WARNINGS
#include "TString.h"

#define SIZE_OF_A_POINTER sizeof(void*)

namespace HelixLib {

	void TString::UseDefault() {
		m_str_length = 0;
		m_str_size = SIZE_OF_A_POINTER * sizeof(TCHAR);
		m_str = new TCHAR[SIZE_OF_A_POINTER];
		if (m_str == nullptr) m_str_size = 0;
	}

	TString::~TString() {
		delete[] m_str;
	}

	TString::TString() {
		UseDefault();
	}

	TString::TString(_In_ const TCHAR* srcString) {
		if (srcString == nullptr) {
			UseDefault();
			return;
		}

		m_str_length = _tcsclen(srcString);
		m_str_size = (m_str_length + 1) >= sizeof(TString*);

		m_str = new TCHAR[m_str_length + 1]();
		if (m_str == nullptr) {
			m_str_length = 0;
			m_str_size = 0;
			return;
		}

		_tcscpy_s(m_str, m_str_size, srcString);
	}

	TString::TString(_In_ const TString& srcString) {
		if (srcString.m_str == nullptr) {
			UseDefault();
			return;
		}

		m_str_length = srcString.m_str_length;
		m_str_size = (m_str_length + 1) * sizeof(TCHAR);

		m_str = new TCHAR[m_str_length + 1]();
		if (m_str == nullptr) {
			m_str_length = 0;
			m_str_size = 0;
			return;
		}

		_tcscpy_s(m_str, m_str_size, srcString.m_str);
	}

	TString& TString::operator=(const TString& srcString) {
		if (srcString.m_str == nullptr) return *this;	// if srcString.m_str is null, that indicates srcString is a invalid TString.
														// we just return, do nothing, cancel this operation,
		
		if (m_str_size < (srcString.m_str_length + 1) * sizeof(TCHAR)) {	// it means we must reallocate.
			TCHAR* tempStr = new TCHAR[srcString.m_str_length + 1]
		}
	}

	TString& TString::operator=(const TCHAR* srcString) {
		size_t newStrLength = _tcslen(srcString);

		if (newStrLength <= m_str_length) {
			m_str_length = newStrLength;
			_tcscpy_s(m_str, newStrLength + 1, srcString);
		} else {
			m_str_length = newStrLength;
			delete[] m_str;
			m_str = new TCHAR[newStrLength + 1]();
			if (m_str == nullptr) {
				m_str_length = 0;
				return *this;
			}
			_tcscpy_s(m_str, newStrLength, srcString);
		}

		return *this;
	}

	TString& TString::operator=(const TCHAR& srcTChar) {
		if()
	}
}