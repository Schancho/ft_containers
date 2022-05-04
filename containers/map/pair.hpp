#pragma once

namespace ft
{
    template<class T1, class T2>
    class pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        public:
            first_type first;
            second_type second;

            pair() {}

            template<class U1, class U2>
            pair (const pair<U1, U2>& x) : first(x.first), second(x.second) {}

            pair(const &first_type, const &second_type) : first(first), second(second) {}

            template<class U1, class U2>
            pair& operator=(const pair<U1, U2>& x)
            {
                first = x.first;
                second = x.second;
                return *this;
            }
    };

    template<class T1, class T2>
    bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return x.first == y.first && x.second == y.second;
    }

    template<class T1, class T2>
    bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return !(x == y);
    }

    template<class T1, class T2>
    bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
    }

    template<class T1, class T2>
    bool operator>(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return y < x;
    }

    template<class T1, class T2>
    bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return !(y < x);
    }

    template<class T1, class T2>
    bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return !(x < y);
    }

    template<class T1, class T2>
    pair<T1, T2> make_pair(const T1& x, const T2& y)
    {
        return pair<T1, T2>(x, y);
    }
}