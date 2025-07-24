using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Jacobian_Test
{
    public class SimpleRecursionFunctionStack<T, U>
    {
        public Func<T, IEnumerable<T>> f { get; private set; }
        public Func<T, bool> g { get; private set; }
        public Func<T, U> h { get; private set; }
        //h의 집합 H이라고 할 시 H->h
        public Func<IEnumerable<U>, U> Oneh { get; private set; }
        //h가 새롭게 나올 때 마다 새로운 h'로 갱신 : 주의! : 처음 값에 유의할 것
        public Func<U,U,U> Controlh { get; private set; }

        public SimpleRecursionFunctionStack(
            Func<T, IEnumerable<T>> f,
            Func<T, bool> g,
            Func<T, U> h)
        {
            this.f = f;
            this.g = g;
            this.h = h;
        }
        public SimpleRecursionFunctionStack(
            Func<T, IEnumerable<T>> f,
            Func<T, bool> g,
            Func<T, U> h,
            Func<IEnumerable<U>,U> Oneh)
        {
            this.f = f;
            this.g = g;
            this.h = h;
            this.Oneh = Oneh;
        }
        public SimpleRecursionFunctionStack(
            Func<T, IEnumerable<T>> f,
            Func<T, bool> g,
            Func<T, U> h,
            Func<IEnumerable<U>, U> Oneh,
            Func<U, U, U> Controlh)
        {
            this.f = f;
            this.g = g;
            this.h = h;
            this.Oneh = Oneh;
            this.Controlh = Controlh;
        }
        public SimpleRecursionFunctionStack() { }
        public void SetF(Func<T, IEnumerable<T>> f)
        {
            this.f = f;
        }
        public void SetG(Func<T, bool> g)
        {
            this.g = g;
        }
        public void SetH(Func<T, U> h)
        {
            this.h = h;
        }
        public void SetOneH(Func<IEnumerable<U>, U> Oneh)
        {
            this.Oneh = Oneh;
        }
        public void SetControlH(Func<U, U, U> Controlh)
        {
            this.Controlh = Controlh;
        }

        public void RunLeafVold(params T[] StartStates)
        {
            Stack<T> stack = new(StartStates);

            while (stack.Count > 0)
            {
                var current = stack.Pop();

                if (g(current))
                {
                    h(current);
                }
                else
                {
                    foreach (var next in f(current))
                    {
                        stack.Push(next);
                    }
                }
            }
            return;
        }

        public U RunLeafFold(U OutDefault, params T[] StartStates)
        {
            Stack<T> stack = new(StartStates);
            U result = OutDefault;

            while (stack.Count > 0)
            {
                var current = stack.Pop();

                if (g(current))
                {
                    result = Controlh(h(current), result);
                }
                else
                {
                    foreach (var next in f(current))
                    {
                        stack.Push(next);
                    }
                }
            }
            return result;
        }

        public U RunLeafReduce(params T[] StartStates)
        {
            Stack<T> stack = new(StartStates);
            List<U> results = new();

            while (stack.Count > 0)
            {
                var current = stack.Pop();

                if (g(current))
                {
                    results.Add(h(current));
                }
                else
                {
                    foreach (var next in f(current))
                    {
                        stack.Push(next);
                    }
                }
            }
            return Oneh(results);
        }

        public List<U> RunLeafList(params T[] StartStates)
        {
            Stack<T> stack = new(StartStates);
            List<U> results = new();

            while (stack.Count > 0)
            {
                var current = stack.Pop();

                if (g(current))
                {
                    results.Add(h(current));
                }
                else
                {
                    foreach (var next in f(current))
                    {
                        stack.Push(next);
                    }
                }
            }
            return results;
        }
    }
}
