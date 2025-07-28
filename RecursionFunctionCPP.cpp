#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <functional>

using namespace std;

/*
2025월 07월 29일 화요일 내용 추가
본 코드의 구성

재귀 함수 라이브러리

namespace RecursionhFunction
- RecursionFunctionLinear<T, U>
- RecursionFunctionLinearSimple<T, U>
- RecursionFunctionLinearSimpleNonH<T>
- RecursionFunctionStack<T, U>
- RecursionFunctionStackSimple<T, U>

namespace RecursionFunction_OldFunctionPointer
- RecursionFunctionLinear<T, U>
- RecursionFunctionLinearSimple<T, U>
- RecursionFunctionLinearSimpleNonH<T>
- RecursionFunctionStack<T, U>
- RecursionFunctionStackSimple<T, U>

라이브러리 실험 구현체

struct OldPointerRFStackTestingStruct - 함수 포인터로 만든 비선형 재귀 함수 클래스에 대하여 테스트하기 위한 구현체
struct RFLtesting - std::function으로 만든 선형 재귀 함수 클래스에 대하여 테스트 하기
struct RFSsimpletesting - std::function으로 만든 비선형 SIMPLE버전 재귀 함수 클래스에 대하여 테스트 하기

int main()
*/

/*
미리 알려드립니다. 본 코드는 아직 검증이 끝나지 않은 시험용 코드입니다. 너무 맹신하고 사용하시지 말고 구조를 보고 
이해하는데에 중점을 두시는 것을 추천드립니다. 또한 코드의 설명이 어려우시다면 관련 문서도 올려놓았으니 이를 참고해주시기 바랍니다.

본 코드는 재귀 함수를 반복 함수 F, 재귀 종료 조건 함수 G, 재귀 종료 후 처리 함수 H로 나누는 
추상화를 진행한 클래스들입니다.

코드는 크게 두가지 버전으로 RecursionFunction, RecursionFunction_OldFunctionPointer namespace버전으로 나뉩니다.
이때 namespace별로 구현 방법을 말해보겠습니다.
RecursionFunction namespace안에 구현한 클래스들은 모던 C++ 기본 라이브러리인 functional의 std::function을 이용하여
추상화하였습니다. 본 namespace안에 있는 클래스 각각은 PointerTesting이라는 메소드가 있어 f, g, h 등의 선재되어야 하는
함수가 잘 정의되어있는지 확인 할 수 있습니다.
RecursionFunction_OldFunctionPointer namespace안에 구현한 클래스들은 고전 C++ 문법인 함수 포인터(예시 : int(*p)(int) )
를 이용하여 추상화하였습니다. 본 namespace안에 있는 클래스 각각은 고전적인 포인터를 이용함으로 nullptr가 아닌 댕글링 포인터를
막을 방법을 찾지 못하여 함수가 잘 정의되어있는지 확힌 하는 기능은 제외하였습니다.

이어서 각 namespace에 있는 5개의 클래스에 대해서 말씀드리겠습니다. 아래의 5개의 클래스를 열거한 후 자세하게 설명드리겠습니다.
- RecursionFunctionLinear<T, U>
- RecursionFunctionLinearSimple<T, U>
- RecursionFunctionLinearSimpleNonH<T>
- RecursionFunctionStack<T, U>
- RecursionFunctionStackSimple<T, U>

이제 기본적인 선형 재귀 클래스인 RecursionFunctionLinear<T, U>에 대하여 설명드리겠습니다. 본 클래스의 함수 정의는 R:T->U 입니다. 즉 재귀하는
공간 T와 결과 공간 U는 서로 다른 공간일 수 있는 재귀 함수 클래스입니다.
본 클래스는 선형 재귀 함수를 f, g, h와 x로 나눈 R(f,g,h)(x)로 추상화 시킨 것으로 Run종류 함수를 돌리기 전에 반드시
f, g, h에 관한 정의가 선재되어야 x를 넣어서 동작 시킬 수 있습니다. 본 클래스는 반드시 선형적인 재귀(예시 : 정수 팩토리얼 재귀)만
돌릴 수 있음으로 이를 유의해야만 합니다. 또한 반드시 f, g, h는 각각 f는 T(T), g는 bool(T, T(T)), h는 U(T, T(T), bool(T, T(T)))형식인 함수로
짜야만 합니다. Run메소드는 h를 return하는 형식의 선형 재귀 함수입니다.RunVoid메소드는 h를 재귀가 끝난 후 실행은 하되 h의 공역을 반환하지 않는
void형 반환 형식의 선형 재귀 함수입니다. 만약 RecursionFunction namespace에 있는 본 클래스를 이용하실 경우 PointerTesting메소드를 사용하여
f, g, h 함수가 전부 잘 정의 되어있는지를 확인하고, 잘 정의되어 있지 않은 모든 함수에 대하여 throw std::runtime_error를 보내어서 관리의 편안함을
추구할 수 있도록 돕습니다.

다음으로 RecursionFunctionLinear<T, U>의 f, g, h 함수의 정의역을 간략화한 RecursionFunctionLinearSimple<T, U>에 대하여 설명드리겠습니다.
본 클래스는 선형 재귀 함수 R(f,g,h)(x)에서 f, g, h 각각의 정의역을 간략화 시킨 것으로 모두 정의역이 T입니다. 구체적으로 말하자면 f는 T(T),
g는 bool(T), h는 U(T)로 간략화되었습니다. 이 외의 동작은 RecursionFunctionLinear<T, U>과 모두 동일합니다.

다음으로는 RecursionFunctionLinearSimple<T, U>에서 함수 h를 제거한 RecursionFunctionLinearSimpleNonH<T>에 대하여 설명드리겠습니다.
본 클래스의 함수 정의는 R:T->T 입니다. 즉 재귀하는 공간과 결과 공간은 서로 공간 T로 같아야하는 고전적인 재귀 함수 클래스입니다. 이외의 함수 f, g는
f는 T(T), g는 bool(T)로 동일합니다. 본 클래스는 RecursionFunctionLinearSimple<T, U>의 메소드를 모두 지원합니다. 다만 Run은 마지막으로 동작한
f(x)의 결과인 T를 반환하고 RunVoid는 마지막으로 동작한 f(x) 이후 바로 동작이 끝나는 void 반환형이라는 차이점이 존재합니다.

이번에는 기본적인 비선형 재귀 클래스인 RecursionFunctionStack<T, U>에 대하여 설명드리겠습니다. 본 클래스의 함수 정의는 R:T->vector<U>가
기본 정의입니다. 본 클래스는 비선형 재귀 함수를 f, g, h와 x로 나눈 R(f,g,h)(x)로 추상화 시킨 것으로 Run종류 함수를 돌리기 전에 반드시
f, g, h에 관한 정의가 선재되어야 하고 필요시 관련 함수인 Oneh나 Controlh도 선재되어 있어야 x를 넣어서 동작 시킬 수 있습니다. 본 클래스는
비선형 재귀 함수를 추상화 시킨 클래스이지만 선형 재귀 함수도 돌릴 수 있습니다. 이때 f, g, h는 각각 f는 vector<T>(T), g는 bool(T, vector<T>(T)),
h는 U(T, vector<T>(T), bool(T, vector<T>(T)))형식인 함수로 짜야만 합니다. 각각의 Run종류 함수인 RunLeafList, RunLeafReduce, RunLeafFold, RunLeafVold에 대하여
하나하나씩 알아보겠습니다. 먼저 RunLeafList메소드를 알아보겠습니다. 본 메소드는 R:vector<T>->vector<U>인 비선형 재귀 함수로서 순수하게 f, g, h만을
이용하여 vector<U>를 return하는 메소드입니다. 다음으로 RunLeafReduce메소드에 대하여 알아보자면 Oneh:vector<U>->U인 vector<U>를 U로 축약하는 함수 Oneh가 존재합니다.
또한 본 메소드는 RunLeafList로직과 동일하게 작동하다가 h들의 결과인 vector<U>가 다 모이게 되고 재귀가 완전히 끝나고 나서 Oneh를 거쳐서 U로 축약되어서
U를 return 하는 메소드입니다. 그 다음으로 RunLeafFold메소드에 대하여 알아보자면 RunLeafReduce메소드와 return 유형이 U로서 유사하나 U로 만드는 과정이 다릅니다.
이를 구체적으로 설명하자면 맨 처음 재귀가 돌아가기 전에 내보낼 U에 대한 초기값으로 StartDefaultStates를 받고 비선형 재귀 중에 g=true여서 h가 동작해서
발생하는 U와 직전의 U(맨 처음 h가 동작 했을 시에는 StartDefaultStates인 U)를 합성하여 Controlh:U x U->U 나 Controlh:h x U->U의 메소드 오버로드 중 하나를 택하여
계속 내보낼 U를 갱신하고 비선형 재귀가 완전히 끝나면 마지막으로 갱신된 U를 return하는 메소드입니다. 마지막으로 RunLeafVold메소드에 대해서 알아보겠습니다.
본 메소드는 비선형 재귀 함수에서 g=true일 때 마다 h가 동작하지만 h의 출력을 수집하지 않고 return이 void인 메소드입니다.

다음으로 RecursionFunctionStack<T, U>의 f, g, h 함수의 정의역을 간략화한 RecursionFunctionStackSimple<T, U>에 대하여 설명드리겠습니다.
본 클래스는 비선형 재귀 함수 R(f,g,h)(x)에서 f, g, h 각각의 정의역을 간략화 시킨 것으로 모두 정의역이 T입니다. 구체적으로 말하자면 f는 vector<T>(T),
g는 bool(T), h는 U(T)로 간략화되었습니다. 이 외의 동작은 RecursionFunctionStack<T, U>과 모두 동일합니다.

-설명 내용 끝-
*/

namespace RecursionFunction
{
	//일반 선형 재귀 함수 버전
	template <typename T, typename U>
	class RecursionFunctionLinear
	{
	protected:
		function<T(T)> f = nullptr; //재귀 반복 함수
		function<bool(T, function<T(T)>)> g = nullptr; //재귀 종료 조건 함수
		function<U(T, function<T(T)>, function<bool(T, function<T(T)>)>)> h = nullptr; //종료 후 처리 함수

		void PointerTesting()
		{
			bool Isthrow = false;
			vector<string> str = vector<string>();
			string str_out = "";

			if (!f | !g | !h)
				Isthrow = true;

			if (!f)
				str.push_back("F");
			if (!g)
				str.push_back("G");
			if (!h)
				str.push_back("H");

			for (int i = 0; i < str.size(); i++)
			{
				if (i < str.size() - 1)
					str[i] += ", ";
				str_out += str[i];
			}

			if (Isthrow)
				throw runtime_error(str_out + " function is not initialized");
		}

	public:
		void FunctionTester()
		{
			this->PointerTesting();
		}
		RecursionFunctionLinear<T, U>() {}
		RecursionFunctionLinear<T, U>(
			function<T(T)> f,
			function<bool(T, function<T(T)>)> g,
			function<U(T, function<T(T)>, function<bool(T, function<T(T)>)>)> h
		)
		{
			this->f = f;
			this->g = g;
			this->h = h;
			PointerTesting();
		}

		void SetF(function<T(T)> f) { this->f = f; }
		void SetG(function<bool(T, function<T(T)>)> g) { this->g = g; }
		void SetH(function<U(T, function<T(T)>, function<bool(T, function<T(T)>)>)> h) { this->h = h; }

		U Run(T StartStates)
		{
			PointerTesting();

			T x = StartStates;

			while (!g(x, f))
				x = f(x);
			return h(x, f, g);
		}
		void RunVoid(T StartStates)
		{
			PointerTesting();

			T x = StartStates;

			while (!g(x, f))
				x = f(x);
			h(x, f, g);
			return;
		}
	};

	//Simple 선형 재귀 함수 버전
	template <typename T, typename U>
	class RecursionFunctionLinearSimple
	{
	protected:
		function<T(T)> f = nullptr; //재귀 반복 함수
		function<bool(T)> g = nullptr; //재귀 종료 조건 함수
		function<U(T)> h = nullptr; //종료 후 처리 함수

		void PointerTesting()
		{
			bool Isthrow = false;
			vector<string> str = vector<string>();
			string str_out = "";

			if (!f | !g | !h)
				Isthrow = true;

			if (!f)
				str.push_back("F");
			if (!g)
				str.push_back("G");
			if (!h)
				str.push_back("H");

			for (int i = 0; i < str.size(); i++)
			{
				if (i < str.size() - 1)
					str[i] += ", ";
				str_out += str[i];
			}

			if (Isthrow)
				throw runtime_error(str_out + " function is not initialized");
		}

	public:
		void FunctionTester()
		{
			this->PointerTesting();
		}
		RecursionFunctionLinearSimple() {}
		RecursionFunctionLinearSimple(
			function<T(T)> f,
			function<bool(T)> g,
			function<U(T)> h
		)
		{
			this->f = f;
			this->g = g;
			this->h = h;
			PointerTesting();
		}

		void SetF(function<T(T)> f) { this->f = f; }
		void SetG(function<bool(T)> g) { this->g = g; }
		void SetH(function<U(T)> h) { this->h = h; }

		U Run(T StartStates)
		{
			PointerTesting();

			T x = StartStates;

			while (!g(x))
				x = f(x);
			return h(x);
		}
		void RunVoid(T StartStates)
		{
			PointerTesting();

			T x = StartStates;

			while (!g(x))
				x = f(x);
			h(x);
			return;
		}
	};

	//Simple And Non-H 선형 재귀 함수 버전
	template <typename T>
	class RecursionFunctionLinearSimpleNonH
	{
	protected:
		function<T(T)> f = nullptr; //재귀 반복 함수
		function<bool(T)> g = nullptr; //재귀 종료 조건 함수

		void PointerTesting()
		{
			bool Isthrow = false;
			vector<string> str = vector<string>();
			string str_out = "";

			if (!f | !g)
				Isthrow = true;

			if (!f)
				str.push_back("F");
			if (!g)
				str.push_back("G");

			for (int i = 0; i < str.size(); i++)
			{
				if (i < str.size() - 1)
					str[i] += ", ";
				str_out += str[i];
			}

			if (Isthrow)
				throw runtime_error(str_out + " function is not initialized");
		}

	public:
		void FunctionTester()
		{
			this->PointerTesting();
		}
		RecursionFunctionLinearSimpleNonH() {}
		RecursionFunctionLinearSimpleNonH(
			function<T(T)> f,
			function<bool(T)> g
		)
		{
			this->f = f;
			this->g = g;
			PointerTesting();
		}

		void SetF(function<T(T)> f) { this->f = f; }
		void SetG(function<bool(T)> g) { this->g = g; }

		T Run(T StartStates)
		{
			PointerTesting();

			T x = StartStates;

			while (!g(x))
				x = f(x);
			return x;
		}
		void RunVoid(T StartStates)
		{
			PointerTesting();

			T x = StartStates;

			while (!g(x))
				x = f(x);
			return;
		}
	};

	//일반 비선형 재귀 함수 버전
	template <typename T, typename U>
	class RecursionFunctionStack
	{
	protected:
		function<vector<T>(T)> f = nullptr; //반복 시행 함수
		function<bool(T, function<vector<T>(T)>)> g = nullptr; //재귀 종료 조건 함수
		function<U(T, function<vector<T>(T)>, function<bool(T, function<vector<T>(T)>)>)> h = nullptr; //종료 처리 함수

		void PointerTesting(vector<string> BeforeStr = vector<string>())
		{
			vector<string> str = vector<string>();
			string str_out = "";

			if (!f)
				str.push_back("F");
			if (!g)
				str.push_back("G");
			if (!h)
				str.push_back("H");

			for (int i = 0; i < str.size(); i++)
			{
				if (!str_out.empty())
					str_out += ", ";
				str_out += str[i];
			}
			for (int i = 0; i < BeforeStr.size(); i++)
			{
				if (!str_out.empty())
					str_out += ", ";
				str_out += BeforeStr[i];
			}

			if (!str_out.empty())
				throw runtime_error(str_out + " function is not initialized");
		}
		void PointerTesting(function<U(vector<U>)> other_function, string function_name)
		{
			vector<string> str = vector<string>();
			if (!other_function)
				str.push_back(function_name);

			this->PointerTesting(str);
		}
		void PointerTesting(function<U(U,U)> other_function, string function_name)
		{
			vector<string> str = vector<string>();
			if (!other_function)
				str.push_back(function_name);

			this->PointerTesting(str);
		}
		void PointerTesting(function<U(function<U(T, function<vector<T>(T)>, function<bool(T, function<vector<T>(T)>)>)>, U)> other_function, string function_name)
		{
			vector<string> str = vector<string>();
			if (!other_function)
				str.push_back(function_name);

			this->PointerTesting(str);
		}
	public:
		void FunctionTester(function<U(vector<U>)> other_function, string function_name)
		{
			this->PointerTesting(other_function, function_name);
		}
		void FunctionTester(function<U(U, U)> other_function, string function_name)
		{
			this->PointerTesting(other_function, function_name);
		}
		void FunctionTester(function<U(function<U(T, function<vector<T>(T)>, function<bool(T, function<vector<T>(T)>)>)>, U)> other_function, string function_name)
		{
			this->PointerTesting(other_function, function_name);
		}
		void FunctionTester()
		{
			this->PointerTesting();
		}
		RecursionFunctionStack() {}
		RecursionFunctionStack(
			function<vector<T>(T)> f,
			function<bool(T, function<vector<T>(T)>)> g,
			function<U(T, function<vector<T>(T)>, function<bool(T, function<vector<T>(T)>)>)> h
		)
		{
			this->f = f;
			this->g = g;
			this->h = h;
			this->PointerTesting();
		}

		void SetF(function<vector<T>(T)> f) { this->f = f; }
		void SetG(function<bool(T, function<vector<T>(T)>)> g) { this->g = g; }
		void SetH(function<U(T, function<vector<T>(T)>, function<bool(T, function<vector<T>(T)>)>)> h) { this->h = h; }

		vector<U> RunLeafList(vector<T> StartStates) //말단 노드 각각의 U를 Array화 시켜서 내보내는 재귀 함수
		{
			this->PointerTesting();
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			vector<U> Result = vector<U>();

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current, f))
					Result.push_back(h(current, f, g));
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Result;
		}
		//말단 노드 결과 U_Array를 마지막에 정리해서 하나의 U로 만드는 재귀 함수
		U RunLeafReduce(vector<T> StartStates, function<U(vector<U>)> Oneh)
		{
			this->PointerTesting(Oneh, "Oneh");
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			vector<U> Result = vector<U>();

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current, f))
					Result.push_back(h(current, f, g));
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Oneh(Result);
		}
		//말단 노드 결과가 하나하나씩 나올 때 마다 최종 return으로 쓰일 U를 이전 결과와 지금 결과를 함수로 넣어 새로운 U를 구하는 것을 반복하고 최종 U 하나를 내보내는 재귀 함수
		U RunLeafFold(vector<T> StartStates, U StartDefaultStates, function<U(function<U(T, function<vector<T>(T)>, function<bool(T, function<vector<T>(T)>)>)>, U)> Controlh)
		{
			this->PointerTesting(Controlh, "Controlh");
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			U Result = StartDefaultStates;

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current, f))
					Result = Controlh(h, Result);
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Result;
		}
		//말단 노드 결과가 하나하나씩 나올 때 마다 최종 return으로 쓰일 U를 이전 결과와 지금 결과를 함수로 넣어 새로운 U를 구하는 것을 반복하고 최종 U 하나를 내보내는 재귀 함수
		U RunLeafFold(vector<T> StartStates, U StartDefaultStates, function<U(U,U)> Controlh)
		{
			this->PointerTesting(Controlh, "Controlh");
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			U Result = StartDefaultStates;

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current, f))
					Result = Controlh(h(current, f, g), Result);
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Result;
		}
		//아무것도 안 내보내는 재귀 함수
		void RunLeafVold(vector<T> StartStates)
		{
			this->PointerTesting();
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current, f))
					h(current, f, g);
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return;
		}
	};

	//Simple 비선형 재귀 함수 버전
	template <typename T, typename U>
	class RecursionFunctionStackSimple
	{
	protected:
		function<vector<T>(T)> f = nullptr; //반복 시행 함수
		function<bool(T)> g = nullptr; //재귀 종료 조건 함수
		function<U(T)> h = nullptr; //종료 처리 함수

		void PointerTesting(vector<string> BeforeStr = vector<string>())
		{
			vector<string> str = vector<string>();
			string str_out = "";

			if (!f)
				str.push_back("F");
			if (!g)
				str.push_back("G");
			if (!h)
				str.push_back("H");

			for (int i = 0; i < str.size(); i++)
			{
				if (!str_out.empty())
					str_out += ", ";
				str_out += str[i];
			}
			for (int i = 0; i < BeforeStr.size(); i++)
			{
				if (!str_out.empty())
					str_out += ", ";
				str_out += BeforeStr[i];
			}

			if (!str_out.empty())
				throw runtime_error(str_out + " function is not initialized");
		}
		void PointerTesting(function<U(vector<U>)> other_function, string function_name)
		{
			vector<string> str = vector<string>();
			if (!other_function)
				str.push_back(function_name);

			this->PointerTesting(str);
		}
		void PointerTesting(function<U(U, U)> other_function, string function_name)
		{
			vector<string> str = vector<string>();
			if (!other_function)
				str.push_back(function_name);

			this->PointerTesting(str);
		}
		void PointerTesting(function<U(function<U(T)>, U)> other_function, string function_name)
		{
			vector<string> str = vector<string>();
			if (!other_function)
				str.push_back(function_name);

			this->PointerTesting(str);
		}
	public:
		void FunctionTester(function<U(vector<U>)> other_function, string function_name)
		{
			this->PointerTesting(other_function, function_name);
		}
		void FunctionTester(function<U(U, U)> other_function, string function_name)
		{
			this->PointerTesting(other_function, function_name);
		}
		void FunctionTester(function<U(function<U(T)>, U)> other_function, string function_name)
		{
			this->PointerTesting(other_function, function_name);
		}
		void FunctionTester()
		{
			this->PointerTesting();
		}
		RecursionFunctionStackSimple() {}
		RecursionFunctionStackSimple(
			function<vector<T>(T)> f,
			function<bool(T)> g,
			function<U(T)> h
		)
		{
			this->f = f;
			this->g = g;
			this->h = h;
			this->PointerTesting();
		}

		void SetF(function<vector<T>(T)> f) { this->f = f; }
		void SetG(function<bool(T)> g) { this->g = g; }
		void SetH(function<U(T)> h) { this->h = h; }

		vector<U> RunLeafList(vector<T> StartStates) //말단 노드 각각의 U를 Array화 시켜서 내보내는 재귀 함수
		{
			this->PointerTesting();
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			vector<U> Result = vector<U>();

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current))
					Result.push_back(h(current));
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Result;
		}
		//말단 노드 결과 U_Array를 마지막에 정리해서 하나의 U로 만드는 재귀 함수
		U RunLeafReduce(vector<T> StartStates, function<U(vector<U>)> Oneh)
		{
			this->PointerTesting(Oneh, "Oneh");
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			vector<U> Result = vector<U>();

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current))
					Result.push_back(h(current));
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Oneh(Result);
		}
		//말단 노드 결과가 하나하나씩 나올 때 마다 최종 return으로 쓰일 U를 이전 결과와 지금 결과를 함수로 넣어 새로운 U를 구하는 것을 반복하고 최종 U 하나를 내보내는 재귀 함수
		U RunLeafFold(vector<T> StartStates, U StartDefaultStates, function<U(function<U(T)>, U)> Controlh)
		{
			this->PointerTesting(Controlh, "Controlh");
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			U Result = StartDefaultStates;

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current))
					Result = Controlh(h, Result);
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Result;
		}
		//말단 노드 결과가 하나하나씩 나올 때 마다 최종 return으로 쓰일 U를 이전 결과와 지금 결과를 함수로 넣어 새로운 U를 구하는 것을 반복하고 최종 U 하나를 내보내는 재귀 함수
		U RunLeafFold(vector<T> StartStates, U StartDefaultStates, function<U(U, U)> Controlh)
		{
			this->PointerTesting(Controlh, "Controlh");
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			U Result = StartDefaultStates;

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current))
					Result = Controlh(h(current), Result);
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Result;
		}
		//아무것도 안 내보내는 재귀 함수
		void RunLeafVold(vector<T> StartStates)
		{
			this->PointerTesting();
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current))
					h(current);
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return;
		}
	};
}

namespace RecursionFunction_OldFunctionPointer
{
	//일반 버전
	template <typename T, typename U>
	class RecursionFunctionLinear
	{
	protected:
		T(*f)(T) = nullptr; //반복 시행 함수
		bool(*g)(T, T(*)(T)) = nullptr; //재귀 종료 조건 함수
		U(*h)(T, T(*)(T), bool(*)(T, T(*)(T))) = nullptr; //종료 처리 함수

	public:
		RecursionFunctionLinear<T, U>() {}
		RecursionFunctionLinear<T, U>(
			T(*f)(T),
			bool(*g)(T, T(*)(T)),
			U(*h)(T, T(*)(T), bool(*)(T, T(*)(T)))
		)
		{
			this->f = f;
			this->g = g;
			this->h = h;
		}

		void SetF(T(*f)(T)) { this->f = f; }
		void SetG(bool(*g)(T, T(*)(T))) { this->g = g; }
		void SetH(U(*h)(T, T(*)(T), bool(*)(T, T(*)(T)))) { this->h = h; }

		U Run(T StartStataes)
		{
			T x = StartStataes;

			while (!g(x, f))
				x = f(x);
			return h(x, f, g);
		}
		void RunVoid(T StartStataes)
		{
			T x = StartStataes;

			while (!g(x, f))
				x = f(x);
			h(x, f, g);
			return;
		}
	};

	template <typename T, typename U>
	class RecursionFunctionStack
	{
	protected:
		vector<T>(*f)(T) = nullptr; //반복 시행 함수 F:T->T_Array
		bool(*g)(T, vector<T>(*)(T)) = nullptr; //재귀 종료 조건 함수
		U(*h)(T, vector<T>(*)(T), bool(*)(T, vector<T>(*)(T))) = nullptr; //종료 처리 함수

	public:
		RecursionFunctionStack<T, U>() {}
		RecursionFunctionStack<T, U>(
			vector<T>(*f)(T),
			bool(*g)(T, vector<T>(*)(T)),
			U(*h)(T, vector<T>(*)(T), bool(*)(T, vector<T>(*)(T)))
		)
		{
			this->f = f;
			this->g = g;
			this->h = h;
		}

		void SetF(vector<T>(*f)(T)) { this->f = f; }
		void SetG(bool(*g)(T, vector<T>(*)(T))) { this->g = g; }
		void SetH(U(*h)(T, vector<T>(*)(T), bool(*)(T, vector<T>(*)(T)))) { this->h = h; }

		vector<U> RunLeafList(vector<T> StartStates) //말단 노드 각각의 U를 Array화 시켜서 내보내는 재귀 함수
		{
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			vector<U> Result = vector<U>();

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current, f))
					Result.push_back(h(current, f, g));
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Result;
		}
		//말단 노드 결과 U_Array를 마지막에 정리해서 하나의 U로 만드는 재귀 함수
		U RunLeafReduce(vector<T> StartStates, U(*Oneh)(vector<U>))
		{
			return Oneh(this->RunLeafList(StartStates));
		}
		//말단 노드 결과가 하나하나씩 나올 때 마다 최종 return으로 쓰일 U를 이전 결과와 지금 결과를 함수로 넣어 새로운 U를 구하는 것을 반복하고 최종 U 하나를 내보내는 재귀 함수
		U RunLeafFold(vector<T> StartStates, U StartDefaultStates, U(*Controlh)(U(*)(T, vector<T>(*)(T), bool(*)(T, vector<T>(*)(T))), U))
		{
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			U Result = StartDefaultStates;

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current, f))
					Result = Controlh(h, Result);
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Result;
		}
		//말단 노드 결과가 하나하나씩 나올 때 마다 최종 return으로 쓰일 U를 이전 결과와 지금 결과를 함수로 넣어 새로운 U를 구하는 것을 반복하고 최종 U 하나를 내보내는 재귀 함수
		U RunLeafFold(vector<T> StartStates, U StartDefaultStates, U(*Controlh)(U, U))
		{
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			U Result = StartDefaultStates;

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current, f))
					Result = Controlh(h(current, f, g), Result);
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Result;
		}
		//아무것도 안 내보내는 재귀 함수
		void RunLeafVold(vector<T> StartStates)
		{
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current, f))
					h(current, f, g);
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return;
		}
		
	};

	//Simple 버전
	template <typename T, typename U>
	class RecursionFunctionLinearSimple
	{
	protected:
		T(*f)(T) = nullptr; //반복 시행 함수
		bool(*g)(T) = nullptr; //재귀 종료 조건 함수
		U(*h)(T) = nullptr; //종료 처리 함수

	public:
		RecursionFunctionLinearSimple<T, U>() {}
		RecursionFunctionLinearSimple<T, U>(
			T(*f)(T),
			bool(*g)(T),
			U(*h)(T)
		)
		{
			this->f = f;
			this->g = g;
			this->h = h;
		}

		void SetF(T(*f)(T)) { this->f = f; }
		void SetG(bool(*g)(T)) { this->g = g; }
		void SetH(U(*h)(T)) { this->h = h; }

		U Run(T StartStates)
		{
			T x = StartStates;

			while (!g(x))
				x = f(x);
			return h(x);
		}
		void RunVoid(T StartStates)
		{
			T x = StartStates;

			while (!g(x))
				x = f(x);
			h(x);
			return;
		}
	};

	template <typename T, typename U>
	class RecursionFunctionStackSimple
	{
	protected:
		vector<T>(*f)(T) = nullptr; //반복 시행 함수 F:T->T_Array
		bool(*g)(T) = nullptr; //재귀 종료 조건 함수
		U(*h)(T) = nullptr; //종료 처리 함수

	public:
		RecursionFunctionStackSimple<T, U>() {}
		RecursionFunctionStackSimple<T, U>(
			vector<T>(*f)(T),
			bool(*g)(T),
			U(*h)(T)
		)
		{
			this->f = f;
			this->g = g;
			this->h = h;
		}

		void SetF(vector<T>(*f)(T)) { this->f = f; }
		void SetG(bool(*g)(T)) { this->g = g; }
		void SetH(U(*h)(T)) { this->h = h; }

		vector<U> RunLeafList(vector<T> StartStates) //말단 노드 각각의 U를 Array화 시켜서 내보내는 재귀 함수
		{
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			vector<U> Result = vector<U>();

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current))
					Result.push_back(h(current));
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Result;
		}
		//말단 노드 결과 U_Array를 마지막에 정리해서 하나의 U로 만드는 재귀 함수
		U RunLeafReduce(vector<T> StartStates, U(*Oneh)(vector<U>))
		{
			return Oneh(this->RunLeafList(StartStates));
		}
		//말단 노드 결과가 하나하나씩 나올 때 마다 최종 return으로 쓰일 U를 이전 결과와 지금 결과를 함수로 넣어 새로운 U를 구하는 것을 반복하고 최종 U 하나를 내보내는 재귀 함수
		U RunLeafFold(vector<T> StartStates, U StartDefaultStates, U(*Controlh)(U(*)(T), U))
		{
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			U Result = StartDefaultStates;

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current))
					Result = Controlh(h, Result);
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Result;
		}
		//말단 노드 결과가 하나하나씩 나올 때 마다 최종 return으로 쓰일 U를 이전 결과와 지금 결과를 함수로 넣어 새로운 U를 구하는 것을 반복하고 최종 U 하나를 내보내는 재귀 함수
		U RunLeafFold(vector<T> StartStates, U StartDefaultStates, U(*Controlh)(U, U))
		{
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			U Result = StartDefaultStates;

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current))
					Result = Controlh(h(current), Result);
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return Result;
		}
		//아무것도 안 내보내는 재귀 함수
		void RunLeafVold(vector<T> StartStates)
		{
			stack<T> Stack = stack<T>();
			for (auto it = StartStates.begin(); it != StartStates.end(); it++)
			{
				Stack.push(*it);
			}

			while (Stack.size() > 0)
			{
				T current = Stack.top();
				Stack.pop();

				if (g(current))
					h(current);
				else
				{
					vector<T> Loop = f(current);
					for (int i = 0; i < Loop.size(); i++)
						Stack.push(Loop[i]);
				}
			}
			return;
		}

	};

	//Simple And Non-H 버전
	template <typename T>
	class RecursionFunctionLinearSimpleNonH
	{
	protected:
		T(*f)(T) = nullptr; //반복 시행 함수
		bool(*g)(T) = nullptr; //재귀 종료 조건 함수

	public:
		RecursionFunctionLinearSimpleNonH<T>() {}
		RecursionFunctionLinearSimpleNonH<T>(
			T(*f)(T),
			bool(*g)(T)
		)
		{
			this->f = f;
			this->g = g;
		}

		void SetF(T(*f)(T)) { this->f = f; }
		void SetG(bool(*g)(T)) { this->g = g; }

		T Run(T StartStates)
		{
			T x = StartStates;

			while (!g(x))
				x = f(x);
			return x;
		}
		void RunVoid(T StartStates)
		{
			T x = StartStates;

			while (!g(x))
				x = f(x);
			return;
		}
	};
}

//함수 포인터를 이용한 비선형 재귀 함수 클래스 사용 예시 구조체
struct OldPointerRFStackTestingStruct
{
public:
	vector<int> Shape;
	vector<int> Index;
	OldPointerRFStackTestingStruct(vector<int> index, vector<int> Shape)
	{
		this->Index = index;
		this->Shape = Shape;
	}

	static vector<OldPointerRFStackTestingStruct> F(OldPointerRFStackTestingStruct x)
	{
		vector<OldPointerRFStackTestingStruct> Out = vector<OldPointerRFStackTestingStruct>();
		for (int i = 0; i < x.Shape[x.Index.size()]; i++)
		{
			vector<int> Temp = x.Index;
			Temp.push_back(i);
			Out.push_back(OldPointerRFStackTestingStruct(Temp, x.Shape));
		}
		return Out;
	}

	static bool G(OldPointerRFStackTestingStruct x, vector<OldPointerRFStackTestingStruct>(*f)(OldPointerRFStackTestingStruct))
	{
		if (x.Shape.size() == x.Index.size())
			return true;
		else
			return false;
	}

	static float H(OldPointerRFStackTestingStruct x, vector<OldPointerRFStackTestingStruct>(*f)(OldPointerRFStackTestingStruct), bool(*)(OldPointerRFStackTestingStruct, vector<OldPointerRFStackTestingStruct>(*g)(OldPointerRFStackTestingStruct)))
	{
		string str = "";
		for (int i = 0; i < x.Index.size(); i++)
		{
			str += to_string(x.Index[i]);
			if (i + 1 < x.Index.size())
				str += ", ";
		}

		vector<float> V = vector<float>();
		for (int i = 0; i < x.Index.size(); i++)
		{
			V.push_back((float)x.Index[i] * (float)x.Index[i]);
		}
		float norm = 0;
		for (int i = 0; i < V.size(); i++)
		{
			norm += V[i];
		}
		norm = sqrt(norm);

		std::cout << str << " : " << "norm = " << norm << std::endl;
		return norm;
	}
};

//std::function을 이용한 선형 재귀 함수 클래스 사용 예시 구조체
struct RFLtesting
{
public:
	int number = 0;
	int value = 0;
	RFLtesting(int num, int val)
	{
		this->number = num;
		this->value = val;
	}

	static RFLtesting F(RFLtesting x)
	{
		return RFLtesting(x.number - 1, x.value * (x.number));
	}
	static bool G(RFLtesting x, function<RFLtesting(RFLtesting)> f)
	{
		if (x.number == 1)
			return true;
		else
			return false;
	}
	static int H(RFLtesting x, function<RFLtesting(RFLtesting)> f, function<bool(RFLtesting, function<RFLtesting(RFLtesting)>)> g)
	{
		return x.value;
	}
};

struct RFSsimpletesting
{
public:
	vector<int> Shape;
	vector<int> NowIndex;
	float value = 0;
	float save_value = 0;
	RFSsimpletesting(vector<int> shape, vector<int> now_index, float val, float save)
	{
		this->Shape = shape;
		this->NowIndex = now_index;
		this->value = val;
		this->save_value = save;
	}
	RFSsimpletesting() {}

	static vector<RFSsimpletesting> F(RFSsimpletesting x)
	{
		vector<RFSsimpletesting> out = vector<RFSsimpletesting>();
		for (int i = 0; i < x.Shape[x.NowIndex.size()]; i++)
		{
			vector<int> Temp = x.NowIndex;
			Temp.push_back(i);
			float temp_val = 0;
			for (int j = 0; j < Temp.size(); j++)
				temp_val += Temp[j];
			out.push_back(RFSsimpletesting(x.Shape, Temp, temp_val, x.save_value + temp_val));
		}
		return out;
	}
	static bool G(RFSsimpletesting x)
	{
		if (x.Shape.size() == x.NowIndex.size())
			return true;
		else
			return false;
	}
	static float H(RFSsimpletesting x)
	{
		string str = "";
		for (int i = 0; i < x.NowIndex.size(); i++)
		{
			str += to_string(x.NowIndex[i]);
			if (i + 1 < x.NowIndex.size())
				str += ", ";
		}

		std::cout << str << " : " << x.save_value << std::endl;
		return x.save_value;
	}
};

int main()
{
	//함수 포인터를 이용한 비선형 재귀 파트
	std::cout << "[함수 포인터를 이용한 비선형 재귀 함수 클래스 실험]" << std::endl;
	std::cout << "- [3,4,2] 다차원 배열에 접근하는 재귀 함수" << std::endl;

	RecursionFunction_OldFunctionPointer::RecursionFunctionStack<OldPointerRFStackTestingStruct, float> RF1 
		= RecursionFunction_OldFunctionPointer::RecursionFunctionStack<OldPointerRFStackTestingStruct, float>
		(OldPointerRFStackTestingStruct::F, OldPointerRFStackTestingStruct::G, OldPointerRFStackTestingStruct::H);
	vector<int> Shape = vector<int>();
	Shape.push_back(3);
	Shape.push_back(4);
	Shape.push_back(2);
	vector<OldPointerRFStackTestingStruct> In1 = vector<OldPointerRFStackTestingStruct>();
	In1.push_back(OldPointerRFStackTestingStruct(vector<int>(), Shape));
	vector<float> norm;
	norm = RF1.RunLeafList(In1);
	float sum = 0;
	for (int i = 0; i < norm.size(); i++)
	{
		sum += norm[i];
	}
	std::cout << sum / norm.size() << std::endl;

	std::cout << std::endl << std::endl;

	//std::function을 이용한 선형 재귀 파트
	std::cout << "[std::function을 이용한 선형 재귀 함수 클래스 실험]" << std::endl;
	std::cout << "- 7! 팩토리얼 계산" << std::endl;

	RecursionFunction::RecursionFunctionLinear<RFLtesting, int> RF2
		= RecursionFunction::RecursionFunctionLinear<RFLtesting, int>
		(RFLtesting::F, RFLtesting::G, RFLtesting::H);

	RFLtesting In2 = RFLtesting(7, 1);

	std::cout << RF2.Run(In2) << std::endl;

	std::cout << std::endl << std::endl;

	//std::function을 이용한 Simple 비선형 재귀 파트
	std::cout << "[std::function을 이용한 Simple 비선형 재귀 함수 클래스 실험]" << std::endl;
	std::cout << "- [3.4.5] 다차원 배열에 접근하는 재귀 함수" << std::endl;
	RecursionFunction::RecursionFunctionStackSimple<RFSsimpletesting, float> RF3
		= RecursionFunction::RecursionFunctionStackSimple<RFSsimpletesting, float>
		(RFSsimpletesting::F, RFSsimpletesting::G, RFSsimpletesting::H);
	vector<int> Shape2 = vector<int>();
	Shape2.push_back(3);
	Shape2.push_back(4);
	Shape2.push_back(5);
	vector<RFSsimpletesting> In3 = vector<RFSsimpletesting>();
	In3.push_back(RFSsimpletesting(Shape2, vector<int>(), 0, 0));
	RF3.RunLeafVold(In3);
}