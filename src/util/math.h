#pragma once

namespace Math {

namespace ODE {

template <typename T>
T rk4(T xi, float dt, T (*func)(T)) {
        T k1 = func(xi);
        T k2 = func(xi + dt*k1/2);
        T k3 = func(xi + dt*k2/2);
        T k4 = func(xi + dt*k3);
        return xi + dt/6 * (k1 + 2*k2 + 2*k3 + k4);
        // return xn;
}

}

}
