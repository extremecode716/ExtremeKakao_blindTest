//ExtremeCode
#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

// 솔루션 선택
#define 가사검색
// 솔루션 선택
//*
#ifdef 문자열압축
// 코드작성자: ExtremeCode
// 링크: https://programmers.co.kr/learn/courses/30/lessons/60057
// 제목: 문자열 압축 string compression
// 풀이설명: 문자열을 분할(절반부터~3까지)하여 모든압축방법을 찾고, 최적의 방법을 선택하여 압축한다.
// 여담: 혹시 문자열을 이런 방식으로 압축하는 곳이있을까? 7zip은 text파일을 어떤 방식으로 압축하는지 찾아봐야겠다.
int solution( string s ) {
	size_t s_lenght = s.length();
	if ( s_lenght < 3 )
		return s_lenght;

	int answer = s_lenght;
	int iSplitSize = s_lenght / 2;
	int iSplitCount = 0;
	do
	{
		vector<string> vecStrSplit;
		iSplitCount = s_lenght / iSplitSize;
		for ( size_t i = 0; i < s_lenght; i += iSplitSize )
		{
			string strSplit = s.substr( i, iSplitSize );

			vecStrSplit.push_back( strSplit );
		}

		string strResult;
		int iCompareCount = 1;
		string strCompareStr = vecStrSplit[0];
		for ( size_t i = 1; i < vecStrSplit.size(); ++i )
		{
			//문자열이 같다면 카운트 증가, 다르다면 결과 담고 진행.
			if ( !strCompareStr.compare( vecStrSplit[i] ) )
			{
				++iCompareCount;
			}
			else
			{
				if ( iCompareCount > 1 ) {
					strResult.append( to_string( iCompareCount ) );
				}
				iCompareCount = 1;
				strResult.append( strCompareStr );

				strCompareStr = vecStrSplit[i];
			}
		}
		{
			if ( iCompareCount > 1 ) {
				strResult.append( to_string( iCompareCount ) );
			}
			strResult.append( vecStrSplit[vecStrSplit.size() - 1] );
		}
		cout << strResult << endl;

		answer = answer < strResult.size() ? answer : strResult.size();

	} while ( --iSplitSize && iSplitSize > 0 );

	return answer;
}
#endif //문자열압축
//*/

//*
#ifdef 괄호변환
// 코드작성자: ExtremeCode
// 링크: https://programmers.co.kr/learn/courses/30/lessons/60058
// 제목: 괄호 변환 parenthesis conversion
// 풀이설명: 괄호의 짝을 맞추는 알고리즘 

//균형잡힌 괄호 문자열
bool isBalancedParenthesisString( string _str )
{
	int iCheck = 0;
	for ( const auto& i : _str )
	{
		if ( i == '(' ) ++iCheck;
		else --iCheck;
	}

	if ( iCheck == 0 )
		return true;

	return false;
}

int splitting_ParenthesisString_Return_CorrectStringIndex( string _str )
{
	int iCheck = 0;
	for ( size_t i = 0; i < _str.length(); ++i )
	{
		if ( _str[i] == '(' ) ++iCheck;
		else --iCheck;

		if ( iCheck == 0 ) return i + 1;
	}

	return 0;
}

//올바른 괄호 문자열
bool isCorrectParenthesisString( string _str )
{
	int iCount = 0;
	for ( size_t i = 0; i < _str.length(); ++i )
	{
		if ( _str[i] == '(' ) ++iCount;
		else --iCount;

		if ( iCount < 0 ) return false;
	}
	return true;
}
string solution( string p )
{
	size_t iStrLength = p.length();
	//빈 문자열인 경우, 완전 괄호 문자열인 경우 반환.
	if ( iStrLength == 0 || isCorrectParenthesisString( p ) )
		return p;

	string answer = "";

	int iSplitIndex = splitting_ParenthesisString_Return_CorrectStringIndex( p );

	string u = p.substr( 0, iSplitIndex );
	string v = p.substr( iSplitIndex );

	if ( isCorrectParenthesisString( u ) )
		answer = u + solution( v );
	else
	{
		answer.append( "(" );
		answer.append( solution( v ) );
		answer.append( ")" );

		for ( size_t i = 1; i < u.length() - 1; ++i )
		{
			if ( u[i] == '(' ) answer.append( ")" );
			else answer.append( "(" );
		}
	}

	return answer;
}

#endif //괄호변환
//*/

//*
#ifdef 자물쇠와열쇠
// 작성자: ExtremeCode
// 링크: https://programmers.co.kr/learn/courses/30/lessons/60059
// 제목: 자물쇠와 열쇠 Lock and key
// 풀이설명: 문제를 최적으로 바꿔서 풀어보았다. Lock을 기준으로 키를 돌려 깍아가면서 맞추는 방식이 아닌, Lock의 최소한의 영역을 구하고 key를 기준으로 Lock을 돌려 맞춰보는 방식으로 풀었다.

//key를 기준으로 일치하는 영역을 발견시 탐색을 시작한다.
bool isOpen( const vector<vector<int>>& key, const vector<vector<int>>& spaceToLock )
{
	int ikeyYSize = static_cast<int>(key.size());
	int iKeyXSize = static_cast<int>(key[0].size());
	int iSpaceToLockYSize = static_cast<int>(spaceToLock.size());
	int iSpaceToLockXSize = static_cast<int>(spaceToLock[0].size());

	// key가 spaceToLock보다 작다면 맞추어 볼 필요도 없이 false이다.
	if ( ikeyYSize < iSpaceToLockYSize || iKeyXSize < iSpaceToLockXSize )
		return false;

	int iCount = 0;
	int iMaxCount = iSpaceToLockXSize * iSpaceToLockYSize;

	for ( int row = 0; row <= ikeyYSize - iSpaceToLockYSize; ++row )
	{
		for ( int col = 0; col <= iKeyXSize - iSpaceToLockXSize; ++col )
		{
			// 일치-> 탐색 시작.
			if ( spaceToLock[0][0] == key[row][col] )
			{
				bool bBreak = false;
				iCount = 0;
				for ( int i = 0; i < iSpaceToLockYSize; ++i )
				{
					for ( int j = 0; j < iSpaceToLockXSize; ++j )
					{
						if ( spaceToLock[i][j] == key[row + i][col + j] )
							++iCount;
						else
						{
							bBreak = true;
							iCount = 0;
							break;
						}
					}
					if ( bBreak )
						break;
				}

				if ( iCount == iMaxCount )
					return true;
			}
		}
	}

	return false;
}

// SpaceToLock이 정배열이 아니기 때문에 이 회전 방식을 채택했다.
vector<vector<int>> Rotation_2DVector_Right( const vector<vector<int>>& SpaceToLock )
{
	int iYSize = static_cast<int>(SpaceToLock.size());
	int iXSize = static_cast<int>(SpaceToLock[0].size());
	vector<vector<int>> vecResult;

	for ( int i = 0; i < iXSize; ++i )
	{
		vector<int> vecNewRow;
		for ( int j = iYSize - 1; j >= 0; --j )
		{
			vecNewRow.push_back( SpaceToLock[j][i] );
		}
		vecResult.push_back( vecNewRow );
	}

	return vecResult;
}

// Lock의 빈 공간을 찾아 새로운 2d vector을 만들어 사용한다. 이 방식을 사용할 시 padding과 shift없이 key와 맞추어 볼 수 있는 방법이다.
vector<vector<int>> SpaceToLock( const vector<vector<int>>& lock )
{
	vector<vector<int>> vecSpaceToLock;
	vector<pair<int, int>> vecSpaceTmp;
	// 매직넘버
	int iX_Start = 999, iX_End = -1;
	int iY_Start = 999, iY_End = -1;
	for ( int row = 0; row < static_cast<int>(lock.size()); ++row )
	{
		for ( int col = 0; col < static_cast<int>(lock.size()); ++col )
		{
			if ( lock[row][col] == 0 )
			{
				iX_Start = iX_Start < col ? iX_Start : col;
				iX_End = iX_End < col ? col : iX_End;

				iY_Start = iY_Start < row ? iY_Start : row;
				iY_End = iY_End < row ? row : iY_End;

				vecSpaceTmp.push_back( make_pair( row, col ) );
			}
		}
	}

	if ( iX_Start != 999 && iX_End != -1 && iY_Start != 999 && iY_End != -1 )
	{
		vecSpaceToLock.assign( iY_End + 1 - iY_Start, vector<int>( iX_End + 1 - iX_Start, 0 ) );

		for ( const auto& i : vecSpaceTmp )
		{
			vecSpaceToLock[i.first - iY_Start][i.second - iX_Start] = 1;
		}
	}

	return vecSpaceToLock;
}

bool solution( vector<vector<int>> key, vector<vector<int>> lock ) {
	bool answer = false;
	vector<vector<int>> vecSpaceToLock;
	vecSpaceToLock = SpaceToLock( lock ); // move

	if ( vecSpaceToLock.empty() )
		return true;

	answer = isOpen( key, vecSpaceToLock );
	if ( answer )
		return answer;

	//3번 회전
	for ( int i = 0; i < 3; ++i ) {
		vecSpaceToLock = Rotation_2DVector_Right( vecSpaceToLock ); // move
		answer = isOpen( key, vecSpaceToLock );
		if ( answer )
			return answer;
	}

	return answer;
}
#endif //자물쇠와열쇠
//*/

//*
#ifdef 가사검색
// 작성자: ExtremeCode
// 링크: https://programmers.co.kr/learn/courses/30/lessons/60060
// 제목: 가사 검색 lyrics Search
// 풀이설명: 
// 여담: 
#include <regex>
#include <algorithm>

bool compString( const string& _str1, const string& _str2 )
{
	bool _bAscending = true;
	if ( _str1.length() != _str2.length() ) {
		if ( _bAscending )
			return _str1.length() < _str2.length();
		else
			return _str1.length() > _str2.length();
	}
	else
	{
		if ( _bAscending )
			return _str1 < _str2;
		else
			return _str1 > _str2;
	}
}

void replaceAll( std::string& str, const std::string& from, const std::string& to ) {
	if ( from.empty() )
		return;
	size_t start_pos = 0;
	while ( (start_pos = str.find( from, start_pos )) != std::string::npos ) {
		str.replace( start_pos, from.length(), to );
		start_pos += to.length();
	}
}

vector<int> solution( vector<string> words, vector<string> queries ) {
	vector<int> answer;

	std::sort( words.begin(), words.end(), compString );

	for ( auto& str_q : queries )
	{
		int iCount = 0;
		string str_lower = str_q;
		string str_upper = str_q;
		int iLower, iUpper;

		replaceAll( str_q, "?", "." );
		replaceAll( str_lower, "?", "a" );
		replaceAll( str_upper, "?", "z" );

		iLower = lower_bound( words.begin(), words.end(), str_lower, compString ) - words.begin();
		iUpper = upper_bound( words.begin(), words.end(), str_upper, compString ) - words.begin();

		//str_q = std::regex_replace( str_q, std::regex("[?]"), "." ); // 오래 걸렸다.

		regex re( str_q );

		for ( size_t i = iLower; i < iUpper; ++i )
		{
			bool bSearch = std::regex_match( words[i], re );

			if ( bSearch )
				++iCount;
		}

		answer.push_back( iCount );
	}

	return answer;
}

template<typename T>
std::ostream &operator <<( std::ostream &os, const std::vector<T> &v ) {
	std::copy( v.begin(), v.end(), std::ostream_iterator<T>( os, ", " ) );
	return os;
}
#endif //가사검색
//*/

//*/
#ifdef 소수판별
//ExtremeCode
bool isPrimeNumber( uint64_t _num )
{
	// 뒤자리 수를 찾는다.
	uint64_t iLastNum = _num % 10;

	if ( iLastNum == 1 || iLastNum == 3 || iLastNum == 7 || iLastNum == 9 )
	{
		return true; // 진행중
	}
	else if ( _num < 7 )
	{
		if ( iLastNum == 2 || iLastNum == 5 )
			return true;
	}
	else
		return false;

	// 7초과의 수는 뒤 자리가 1,3,7,9 만 소수가 될 수 있다. 1차체크
}
#include <iomanip>
#include <set>
void EXC_Stlye( const set<uint64_t>& _vecPrime )
{
	uint64_t num = 10;
	vector<int> vecLastNum = { 1, 3, 7, 9 };
	string str;

	bool bFlag = true;
	bool bPrevFlag = bFlag;

	uint64_t iCount = 0;
	vector<uint64_t> vecCount;

	while ( num <= *(--_vecPrime.end()) )
	{
		for ( size_t i = 0; i < 4; ++i )
		{
			uint64_t newNum = num + vecLastNum[i];

			set<uint64_t>::iterator iter = _vecPrime.find( newNum );
			if ( iter != _vecPrime.end() ) // 존재 
			{
				str.append( "1" );

				bFlag = true;
			}
			else //없음
			{
				str.append( "0" );

				bFlag = false;
			}
		
			++iCount;

			if ( bFlag != bPrevFlag )
			{
				--iCount;
				vecCount.push_back( iCount );
				iCount = 1;
			}

			bPrevFlag = bFlag;
		}
		num += 10;
	}

	const char *pStr = str.c_str();

	size_t i = 0;
	uint64_t iAddNum = 0;

	vector<pair<uint64_t, uint64_t>> vecPair;
	while ( pStr[i] != 0 )
	{
		size_t iLastNum = i % 4;
		//if ( iLastNum == 0 )
		//{
		//	if ( pStr[i] == '1' )
		//		iAddNum = 2 * 2 * 2;
		//}
		//else if ( iLastNum == 1 )
		//{
		//	if ( pStr[i] == '1' )
		//		iAddNum += 2 * 2;
		//}
		//else if ( iLastNum == 2 )
		//{
		//	if ( pStr[i] == '1' )
		//		iAddNum += 2;
		//}
		//else
		//{
		//	if ( pStr[i] == '1' )
		//		iAddNum += 1;
		//}

		cout << pStr[i];
		++i;


		//if ( i % 4 == 0 )
		//{
		//	cout << std::setw( 6 ) << i / 4 * 10 << std::setw( 6 ) << iAddNum;
		//	vecPair.push_back( make_pair( i / 4 * 10, iAddNum ) );
		//	cout << endl;
		//	iAddNum = 0;
		//}
	}
	cout << "\n"<<str.length() << "개의 문자" << endl;

	cout << "2차 압축" << endl;
	for ( const auto& uNum : vecCount )
	{
		cout << uNum;
	}
	cout << "\n압축 성공" << "  " << vecCount.size() << "개의 문자"<< endl;

	cout << "총 압축한 개수" << str.length() - vecCount.size() << "    총 압축률 : " << (float)(str.length() - vecCount.size()) / str.length() * 100<< endl;



	/*/
	sort( vecPair.begin(), vecPair.end(), []( const pair<uint64_t, uint64_t>& _number1, const pair<uint64_t, uint64_t>& _number2 )
	{
		if ( _number1.second == _number2.second )
		{
			return _number1.first < _number2.first;
		}

		return _number1.second < _number2.second;
	} );


	for ( const auto& vec : vecPair )
	{
		cout << vec.first << std::setw( 6 ) << vec.second << endl;
	}
	//*/
}

#endif //소수판별
//*/

#ifdef 암호생성기
//ExtremeCode
typedef struct tData
{
	int iData;

	tData() : iData( 0 ) {};
}tData;

const size_t MAX_SIZE = 8;
const size_t MAX_SINGLE_CYCLE = 5;
const size_t MAX_TEST_CASE = 10;

class TestClass
{
private:
	size_t m_iPos;
	int m_iUpdateDataPos;

public:
	tData m_tData[MAX_SIZE * 2];

	bool InputData( int _iData )
	{
		if ( m_iPos >= MAX_SIZE )
			m_iPos = 0;

		m_tData[m_iPos].iData = _iData;

		++m_iPos;

		return true;
	}

	bool Update()
	{
		int iSingleCycle = 0;
		int iUpdateDataPos = 0;
		int iMinusData = 1;

		while ( true )
		{
			if ( iUpdateDataPos >= MAX_SIZE * 2 )
				iUpdateDataPos = 0;

			if ( iSingleCycle >= MAX_SINGLE_CYCLE )
			{
				iSingleCycle = 0;
				iMinusData = 1;

				if ( m_tData[iUpdateDataPos].iData < 10 )
				{
					int iFlag = 0;

					for ( size_t i = iUpdateDataPos; i < iUpdateDataPos + MAX_SIZE; ++i )
					{
						if ( m_tData[i % (MAX_SIZE * 2)].iData < 10 )
						{
							++iFlag;
						}
					}

					if ( iFlag >= MAX_SIZE )
					{
						m_iUpdateDataPos = iUpdateDataPos;
					}
				}
			}

			if ( iUpdateDataPos >= MAX_SIZE )
			{
				m_tData[iUpdateDataPos - MAX_SIZE].iData = m_tData[iUpdateDataPos].iData - iMinusData;

				if ( m_tData[iUpdateDataPos - MAX_SIZE].iData <= 0 )
				{
					m_tData[iUpdateDataPos - MAX_SIZE].iData = 0;
					m_iUpdateDataPos = iUpdateDataPos;

					break;
				}
			}
			else
			{
				m_tData[iUpdateDataPos + MAX_SIZE].iData = m_tData[iUpdateDataPos].iData - iMinusData;

				if ( m_tData[iUpdateDataPos + MAX_SIZE].iData <= 0 )
				{
					m_tData[iUpdateDataPos + MAX_SIZE].iData = 0;
					m_iUpdateDataPos = iUpdateDataPos;

					break;
				}
			}

			++iSingleCycle;
			++iMinusData;
			++iUpdateDataPos;
		}

		return true;
	}

	void ShowData( size_t _iTestCaseNum )
	{
		std::cout << "#" << _iTestCaseNum;
		for ( size_t i = m_iUpdateDataPos + 1; i < m_iUpdateDataPos + MAX_SIZE + 1; ++i )
		{
			std::cout << " " << m_tData[i % (MAX_SIZE * 2)].iData;
		}
		std::cout << std::endl;
	}

public:
	TestClass() : m_iPos( 0 ), m_iUpdateDataPos( 0 ) {}
	~TestClass() {}
};


int main( int argc, char** argv )
{
	TestClass testClass[MAX_TEST_CASE];
	size_t iTestNum = 0;
	int iInputNum = 0;

	for ( size_t i = 0; i < MAX_TEST_CASE; ++i )
	{
		std::cin >> iTestNum;

		for ( size_t j = 0; j < MAX_SIZE; ++j )
		{
			std::cin >> iInputNum;

			testClass[i].InputData( iInputNum );
		}

		testClass[i].Update();
	}

	for ( size_t i = 0; i < MAX_TEST_CASE; ++i )
	{
		testClass[i].ShowData( i + 1 );
	}

	return 0;
}
#endif

#ifdef 농작물 수확하기
//ExtremeCode
#include <cstdlib>

#define SAFE_DELETE_ARR(p) if(nullptr != p) { delete[] p; (p) = nullptr; }

int CharToInt( char _char )
{
	int iNum = _char - 48;

	return iNum;
}

int* arrTotalNum = nullptr;
void ShowData( size_t _iTestCaseNum )
{
	std::cout << "#" << _iTestCaseNum + 1;
	std::cout << " " << arrTotalNum[_iTestCaseNum];
	std::cout << std::endl;
}

int main( int argc, char** argv )
{
	size_t iMaxTestCaseNum;
	size_t iTileSize;

	std::cin >> iMaxTestCaseNum;

	arrTotalNum = new int[iMaxTestCaseNum] {0, };

	for ( size_t iTestNum = 0; iTestNum < iMaxTestCaseNum; ++iTestNum )
	{
		std::cin >> iTileSize;

		char* arrTile = new char[iTileSize + 1];

		int iTempPos = 0;
		int iSingleNum = 0;
		int iTempBlankNum = 0;

		for ( size_t i = 0; i < iTileSize; ++i )
		{
			std::cin >> arrTile;

			iTempBlankNum = iTileSize / 2 - iTempPos;
			iTempBlankNum = std::abs( iTempBlankNum );

			for ( size_t j = iTempBlankNum; j < iTileSize - iTempBlankNum; ++j )
			{
				iSingleNum = CharToInt( arrTile[j] );

				arrTotalNum[iTestNum] += iSingleNum;
			}

			++iTempPos;
		}

		SAFE_DELETE_ARR( arrTile );
	}

	for ( size_t iTestNum = 0; iTestNum < iMaxTestCaseNum; ++iTestNum )
	{
		ShowData( iTestNum );
	}

	SAFE_DELETE_ARR( arrTotalNum );

	return 0;
}
#endif

#ifdef Test1
int solution( string s )
{
	int answer = 1;

	int strLength = s.length();

	bool bLoop = false;
	char* cmp = &s[0];
	for ( int i = 1; i < strLength; ++i )
	{
		if ( s[i - 1] != 1 )
		{
			cmp = &s[i - 1];
		}
		if ( s[i] != 1 && s[i] == *cmp )
		{
			bLoop = true;
			int startIndex = i;
			int endIndex = i + 1;
			for ( int j = i; j < strLength; ++j )
			{
				if ( s[j] != *cmp )
				{
					endIndex = j;
					break;
				}
				s[j] = 1;
			}
			*cmp = 1;
			i = endIndex;
		}

		if ( i >= strLength - 1 )
		{
			if ( bLoop == true )
			{
				i = 0;
				bLoop = false;
			}
		}
	}

	for ( int i = 0; i < strLength; ++i )
	{
		if ( s[i] != 1 )
		{
			answer = 0;
			break;
		}
	}

	return answer;
}
#endif

#ifdef Test2
int solution( string name ) {
	int answer = 0, i = 0;
	string temp( name.length(), 'A' );
	while ( true ) {
		temp[i] = name[i];
		name[i] - 'A' > 'Z' + 1 - name[i] ? answer += 'Z' + 1 - name[i] : answer += name[i] - 'A';
		if ( temp == name )    break;
		for ( int move = 1; move < name.length(); move++ ) {
			if ( name[(i + move) % name.length()] != temp[(i + move) % name.length()] ) {
				i = (i + move) % name.length();
				answer += move;
				break;
			}
			else if ( name[(i + name.length() - move) % name.length()]
				!= temp[(i + name.length() - move) % name.length()] ) {
				i = (i + name.length() - move) % name.length();
				answer += move;
				break;
			}
		}
	}
	return answer;
}
#endif

#ifdef 달팽이와사각형
//# 2017.11.13
//#ExtremeCode
//# 문제 풀이: 1707: 달팽이 사각형 문제.(while 문 한번)

#include <iostream>
using namespace std;
//#include <ppl.h>
//using namespace concurrency;
//#include <time.h>

#define MAX_SIZE 100
#define SAFE_DELETE_ARRAY(p)  {if(p){ delete[] (p);  (p) = 0;}}

//# enum 방향
enum class Direction : unsigned char
{
	None = 0,
	Right = 1,
	Bottom,
	Left,
	Top,
	Total
};

//# 달팽이 사각형 클래스(바닥)
class SnailRectClass
{
public:
	SnailRectClass() :
		m_index( s_maxIndex ),
		m_direction( Direction::None ), //# default 방향 0. (방향이 없는 상태)
		m_number( -1 )    //# default -1 (값이 없는 상태)
	{
		s_maxIndex++;
	}
	SnailRectClass( const SnailRectClass& ) {};
	~SnailRectClass() {};

private:
	int m_index; //# 인덱스
public:
	Direction m_direction; //# vector (달팽이가 지나갈 방향.)
	int m_number;  //# 달팽이가 지나간 순서
private:
	static int s_maxIndex;
};
int SnailRectClass::s_maxIndex = 0;

template <typename T>
void CheckDirection( T *_snail, const size_t _size, const int _index, Direction& _dir );
template <typename T>
void NextIndex( T *_snail, const size_t _size, const int _index, int& _outIndex );

int main( int argc, char** argv )
{
#pragma region Initialize
	size_t N;   //# 크기
	SnailRectClass *snail; //# 달팽이 사각형

	cin >> N;  //# 크기 입력.
	if ( N > MAX_SIZE || N < 0 ) return 0;  //# 예외 처리.
											//int start = clock();

	const size_t SNAILSIZE = N*N; //# 전체 사이즈
	snail = new SnailRectClass[SNAILSIZE]; //# 객체 생성.

	int i = 0;
	Direction dir = Direction::Right; //# 처음 오른쪽으로  (IF 확장해서 처음 방향을 바꿔주고 싶다면 우선순위도 그에 맞게 변경 할 것.)
	int currentIndex = 0;
	int nextIndex = 0;
#pragma endregion Initialize

#pragma region Update
	///////////////////////////////////////////////////////////////////////////////
	//# 한 방향으로 진행하면서 막혀있을 경우에 방향을 트는 방식을 사용
	//# 1. 현재 위치에서 진행 방향을 선택을 한다.
	//# 2. 현재 위치에서 다음에 갈 위치를 선택한다.
	//# 3. 달팽이가 지나간 위치를 가시적으로 보여주기 위해 값을 넣어준다.
	//# 4. 동기화를 해준다.
	//////////////////////////////////////////////////////////////////////////////
	while ( i < SNAILSIZE )
	{
		CheckDirection( snail, N, currentIndex, dir );
		NextIndex( snail, N, currentIndex, nextIndex );
		snail[currentIndex].m_number = ++i;
		currentIndex = nextIndex;
	}

#pragma endregion Update

#pragma region Rendering
	//# 렌더링
	for ( i = 0; i < SNAILSIZE; i++ )
	{
		cout << snail[i].m_number << " ";
		if ( i % N == N - 1 ) cout << endl;
	}
#pragma endregion Rendering

#pragma region Shutdown
	//# 메모리 해제.
	SAFE_DELETE_ARRAY( snail );
	//cout << "\n time:" << clock() - start << endl;
#pragma endregion Shutdown
	return 0;
}

//# 현재 달팽이의 방향에 따라 갈 수 있는 방향을 설정한다. 
//# 우선순위: 오른쪽 -> 아래 -> 왼쪽 -> 위
template <typename T>
void CheckDirection( T *_snail, const size_t _size, const int _index, Direction& _dir )
{
	switch ( _dir ) //# 진행 방향.
	{
	case Direction::Right: //# 오른쪽으로 진행하다가 갈 수 없을 경우. //# (두가지. 1.값이 있을 경우(즉,갔던 경우) || 2.벽이 있을 경우 (즉, 바닥 끝))
		if ( _snail[_index + 1].m_number != -1 || (_index + 1) % _size == 0 )
		{
			_snail[_index].m_direction = Direction::Bottom;
			_dir = Direction::Bottom;
		}
		else
		{
			_snail[_index].m_direction = Direction::Right;
		}
		break;
	case Direction::Bottom: //# 아래로 진행하다가 갈 수 없을 경우.
		if ( _snail[_index + _size].m_number != -1 || (_index + _size) / _size >= _size )
		{
			_snail[_index].m_direction = Direction::Left;
			_dir = Direction::Left;
		}
		else
		{
			_snail[_index].m_direction = Direction::Bottom;
		}
		break;
	case Direction::Left: //# 왼쪽으로 진행하다가 갈 수 없을 경우.
		if ( _snail[_index - 1].m_number != -1 || (_index - 1) % _size == _size - 1 )
		{
			_snail[_index].m_direction = Direction::Top;
			_dir = Direction::Top;
		}
		else
		{
			_snail[_index].m_direction = Direction::Left;
		}
		break;
	case Direction::Top: //# 위쪽으로 진행하다가 갈 수 없을 경우.
		if ( _snail[_index - _size].m_number != -1 || (_index - _size) < 0 )
		{
			_snail[_index].m_direction = Direction::Right;
			_dir = Direction::Right;
		}
		else
		{
			_snail[_index].m_direction = Direction::Top;
		}
		break;
	default:
		cout << "CheckDirection function error " << endl; //# error
		break;
	}
}

//# 달팽이가 바닥의 방향을 보고 다음 지역의 index로 이동. / out ref
template <typename T>
void NextIndex( T *_snail, const size_t _size, const int _index, int& _outIndex )
{
	switch ( _snail[_index].m_direction )
	{
	case Direction::Right: //# 오른쪽으로
		_outIndex = _index + 1;
		break;
	case Direction::Bottom: //# 아래로
		_outIndex = _index + _size;
		break;
	case Direction::Left: //# 왼쪽으로
		_outIndex = _index - 1;
		break;
	case Direction::Top: //# 위로
		_outIndex = _index - _size;
		break;
	default:
		cout << "NextIndex function error " << endl;  //# error
		break;
	}
}

#endif

#ifdef 행운의문자열
////https://www.acmicpc.net/problem/1342
//ExtremeCode

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <crtdbg.h>
using namespace std;

struct Node
{
	int iDepth;
	char cValue;
	Node* parrentNodeP;
	vector<Node*> vecChildNodeP;
};

string strInput;
size_t ans;
int iMaxDepth;
size_t iMapSize;
size_t iNum;
map<char, size_t> mapKeyCount;

vector<Node*> vecAllNode;

void luckyString( Node* _pParrent, map<char, size_t>& _mapTemp );
void CalKeyCount( const char* strInput )
{
	size_t iStrSize = strlen( strInput );
	iMaxDepth = iStrSize;

	for ( size_t i = 0; i < iStrSize; ++i )
	{
		mapKeyCount[strInput[i]] = (mapKeyCount.find( strInput[i] ) == mapKeyCount.end()) ? 1 : mapKeyCount[strInput[i]] + 1;
	}

	iMapSize = mapKeyCount.size();
}

void luckyString()
{
	for ( auto it = mapKeyCount.begin(); it != mapKeyCount.end(); ++it )
	{
		//++iNum;
		if ( it->second < 1 )
			continue;
		Node* pParrent = new Node;
		vecAllNode.push_back( pParrent );

		pParrent->iDepth = 1;
		pParrent->cValue = it->first;
		pParrent->parrentNodeP = nullptr;

		it->second -= 1;

		luckyString( pParrent, mapKeyCount );
		mapKeyCount[pParrent->cValue] += 1;
	}
}

void luckyString( Node* _pParrent, map<char, size_t>& _mapTemp )
{
	if ( _pParrent->iDepth == iMaxDepth )
	{
		//string strTemp;
		//Node* pTempNode = _pParrent;
		//while (pTempNode != nullptr)
		//{
		//	strTemp.push_back(pTempNode->cValue);

		//	pTempNode = pTempNode->parrentNodeP;
		//}
		//std::reverse(strTemp.begin(), strTemp.end());
		//cout << strTemp << endl;
		++ans;
		return;
	}

	for ( auto it = _mapTemp.begin(); it != _mapTemp.end(); ++it )
	{
		//++iNum;
		if ( it->second < 1 )					// erase비용이 더들어 이렇게 표현 erase사용시 for문 횟수 줄일수있음.
			continue;
		if ( _pParrent->cValue != it->first )
		{
			Node* pChild = new Node;
			vecAllNode.push_back( pChild );

			pChild->iDepth = _pParrent->iDepth + 1;
			pChild->cValue = it->first;
			pChild->parrentNodeP = _pParrent;

			_pParrent->vecChildNodeP.push_back( pChild );

			it->second -= 1;

			luckyString( pChild, _mapTemp );
			_mapTemp[pChild->cValue] += 1;
		}
	}
}

void deleteAllNode()
{
	for ( auto it = vecAllNode.begin(); it != vecAllNode.end(); ++it )
		delete *it;

	vecAllNode.clear();
}
int main()
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(0000);
	strInput.reserve( 11 );
	cin >> strInput;

	CalKeyCount( strInput.c_str() );
	luckyString();

	cout << ans << endl;
	//cout << iNum << endl;

	deleteAllNode();

	return 0;
}
#endif

int main()
{
	//vector<string> words = { "frodo", "front", "frost", "frozen", "frame", "kakao" };
	//vector<string> queries = { "fro??", "????o", "fr???", "fro???", "pro?" };
	//vector<int> result;
	//result = solution( words, queries );

	//cout << result << endl;

	return 0;
}

