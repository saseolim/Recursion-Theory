namespace RecursionFuntion
{
    internal class Program
    {
        public struct A
        {
            public int control { get; set; }
            public long value { get; set; }
            public A(int control, long value)
            {
                this.control = control;
                this.value = value;
            }

            public static A F(A x)
            {
                A a = new(x.control, x.value);
                a.value = a.value * a.control;
                a.control--;
                return a;
            }
            public static bool G(A x, Func<A,A> F)
            {
                if (x.control == 0 && F(x).value == 0)
                    return true;
                else
                    return false;
            }
            public static long H(A x, Func<A,A> F, Func<A,Func<A,A>,bool> G)
            {
                return x.value;
            }

        }
        static void Main(string[] args)
        {
            RecursionFuntion<A, long> recursionFuntionZero = new RecursionFuntion<A, long>(
                A =>
                {
                    A a = new(A.control, A.value);
                    a.value = a.value * a.control;
                    a.control--;
                    return a;
                },

                (A, F) =>
                {
                    if (A.control == 0 && F(A).value == 0)
                        return true;
                    else
                        return false;
                },

                (A, F, G) => { return A.value; });

            RecursionFuntion<A, long> recursionFuntion = new RecursionFuntion<A, long>(A.F, A.G, A.H);
            Console.WriteLine( recursionFuntion.Run(new(10,1)) );
        }
    }
}
