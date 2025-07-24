#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <functional>

using namespace std;

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
	template <typename T, typename U>
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
			function<bool(T)> g,
			function<U(T)> h
		)
		{
			this->f = f;
			this->g = g;
			PointerTesting();
		}

		void SetF(function<T(T)> f) { this->f = f; }
		void SetG(function<bool(T)> g) { this->g = g; }

		U Run(T StartStates)
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

int main()
{
	RecursionFunction_OldFunctionPointer::RecursionFunctionStack<OldPointerRFStackTestingStruct, float> RF1 
		= RecursionFunction_OldFunctionPointer::RecursionFunctionStack<OldPointerRFStackTestingStruct, float>
		(OldPointerRFStackTestingStruct::F, OldPointerRFStackTestingStruct::G, OldPointerRFStackTestingStruct::H);
	vector<int> Shape = vector<int>();
	Shape.push_back(3);
	Shape.push_back(4);
	Shape.push_back(2);
	vector<OldPointerRFStackTestingStruct> In = vector<OldPointerRFStackTestingStruct>();
	In.push_back(OldPointerRFStackTestingStruct(vector<int>(), Shape));
	vector<float> norm;
	norm = RF1.RunLeafList(In);
	float sum = 0;
	for (int i = 0; i < norm.size(); i++)
	{
		sum += norm[i];
	}
	std::cout << sum / norm.size() << std::endl;
}