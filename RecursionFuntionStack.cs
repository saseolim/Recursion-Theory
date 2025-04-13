using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RecursionFuntion
{
    public class RecursionFuntionStack<T,U>
    {
        public Func<T, IEnumerable<T>> f { get; private set; }
        public Func<T, Func<T, IEnumerable<T>>, bool> g { get; private set; }
        public Func<T, Func<T, IEnumerable<T>>, Func<T, Func<T, IEnumerable<T>>, bool>, U> h { get; private set; }

        public RecursionFuntionStack(
            Func<T, IEnumerable<T>> f,
            Func<T, Func<T, IEnumerable<T>>, bool> g,
            Func<T, Func<T, IEnumerable<T>>, Func<T, Func<T, IEnumerable<T>>, bool>, U> h)
        {
            this.f = f;
            this.g = g;
            this.h = h;
        }
        public RecursionFuntionStack() { }
        public void SetF(Func<T, IEnumerable<T>> f)
        {
            this.f = f;
        }
        public void SetG(Func<T, Func<T, IEnumerable<T>>, bool> g)
        {
            this.g = g;
        }
        public void SetH(Func<T, Func<T, IEnumerable<T>>, Func<T, Func<T, IEnumerable<T>>, bool>, U> h)
        {
            this.h = h;
        }

        public List<U> Run(params T[] StartStates)
        {
            Stack<T> stack = new(StartStates);
            List<U> results = new();

            while (stack.Count > 0)
            {
                var current = stack.Pop();

                if (g(current,f))
                {
                    results.Add(h(current, f, g));
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
