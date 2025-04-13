
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RecursionFuntion
{
    public class RecursionFuntion<T,U>
    {
        public Func<T, T> f { get; private set; }
        public Func<T,Func<T,T>, bool> g { get; private set; }
        public Func<T,Func<T,T>, Func<T, Func<T, T>, bool>,U> h { get; private set; }
        public RecursionFuntion() { }
        public RecursionFuntion(
            Func<T, T> f,
            Func<T, Func<T, T>, bool> g,
            Func<T, Func<T, T>, Func<T, Func<T, T>, bool>, U> h)
        {
            this.f = f;
            this.g = g;
            this.h = h;
        }
        public void SetF(Func<T, T> f)
        {
            this.f = f;
        }
        public void SetG(Func<T, Func<T, T>, bool> g)
        {
            this.g = g;
        }
        public void SetH(Func<T, Func<T, T>, Func<T, Func<T, T>, bool>, U> h)
        {
            this.h = h;
        }
        public U Run(T x)
        {
            while (!g(x, f))
                x = f(x);
            return h(x, f, g);
        }
    }
}
