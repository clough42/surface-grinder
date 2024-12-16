#ifndef LIMITER_H
#define LIMITER_H

template <typename T>
class Limiter {
    
public:
    Limiter(T limit1, T limit2) :
        m_lowerLimit(Limiter::_min(limit1, limit2)),
        m_upperLimit(Limiter::_max(limit1, limit2)) {}

    T Clamp(T value) const {
        if (value < m_lowerLimit) {
            return m_lowerLimit;
        }
        if (value > m_upperLimit) {
            return m_upperLimit;
        }
        return value;
    }

private:
    T m_lowerLimit;
    T m_upperLimit;

    T _min(T a, T b) const {
        return (a < b) ? a : b;
    }

    T _max(T a, T b) const {
        return (a > b) ? a : b;
    }

};

#endif // LIMITER_H