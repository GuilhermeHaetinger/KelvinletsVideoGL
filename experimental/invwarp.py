import numpy as np

pos   = [.45, .45]
pivot = [.30, .30]
f     = [.15, .15]

# x, y as initial regression position
x, y   = np.array(pos) - np.array(f)

# ox, oy as the pivot positions
ox, oy = pivot

# The force coefficients
fx, fy = f

z       = 20.
poiss   = 1.
elshear = .4
a       = 1 / (4*np.pi * poiss)
b       = a / (4 - 4*elshear)
c       = 2 / (3 * a - 2 * b)

# Power function
def Power(a, b):
    return a ** b

# Square root function
def Sqrt(a):
    return np.sqrt(a)

def Kelv(x, y):
    rbold = np.array([x, y]) - np.array(pivot)
    r     = np.linalg.norm(rbold)
    re    = Sqrt(r**2 + z**2)
    kelvinState = (((a - b)/re) * np.identity(2) + \
                   (b / re**3) * rbold * np.transpose(rbold) + \
                   (a / 2) * (z**2 / re**3) * np.identity(2))

    return c * z * np.dot(kelvinState, np.array([fx, fy]))

def r_epslon_setup(w, v):
    print("w, v : ", w, v)
    kelv = Kelv(w, v)
    print("Kelv", kelv)
    x = w + kelv[0]
    y = v + kelv[1]
    rbold = np.array([x, y]) - np.array(pivot)
    r     = np.linalg.norm(rbold)
    return Sqrt(r**2 + z**2)

# X function
def getx(w, v):
    re = r_epslon_setup(w, v)
    return (2*Power(re,6)*(ox - w) + 2*(a - b)*c*fx*Power(re,5)*z + 4*b*(-a + b)*Power(c,2)*(Power(fx,2) + Power(fy,2))*ox*Power(re,2)*Power(z,2) - 2*a*b*Power(c,2)*(Power(fx,2) + Power(fy,2))*ox*Power(z,4) + c*Power(re,3)*z*(4*b*ox*(fy*(-oy + v) + fx*(-ox + w)) + a*fx*Power(z,2)) + Sqrt(Power(2*Power(re,3)*(ox - w) + 2*(a - b)*c*fx*Power(re,2)*z + a*c*fx*Power(z,3),2)*(Power(re,6) + 4*b*c*Power(re,3)*(fy*(-oy + v) + fx*(-ox + w))*z + 4*b*(-a + b)*Power(c,2)*(Power(fx,2) + Power(fy,2))*Power(re,2)*Power(z,2) - 2*a*b*Power(c,2)*(Power(fx,2) + Power(fy,2))*Power(z,4))))/(2.*b*c*z*(2*Power(re,3)*(fy*(-oy + v) + fx*(-ox + w)) + 2*(-a + b)*c*(Power(fx,2) + Power(fy,2))*Power(re,2)*z - a*c*(Power(fx,2) + Power(fy,2))*Power(z,3)))

# Y function
def gety(w, v):
    re = r_epslon_setup(w, v)
    return (8*b*c*fx*Power(ox,2)*oy*Power(re,6)*z + 4*b*c*fy*Power(oy,2)*Power(re,3)*z*(-2*Power(re,3)*w + 2*(a - b)*c*fx*Power(re,2)*z + a*c*fx*Power(z,3)) + 2*ox*Power(re,3)*(2*Power(re,6)*(-oy + v) + 2*c*Power(re,3)*(-(a*fy*Power(re,2)) + b*fy*(Power(re,2) + 2*oy*(oy - v)) - 4*b*fx*oy*w)*z + 4*(a - b)*b*Power(c,2)*(2*Power(fx,2) + Power(fy,2))*oy*Power(re,2)*Power(z,2) - a*c*fy*Power(re,3)*Power(z,3) + 2*a*b*Power(c,2)*(2*Power(fx,2) + Power(fy,2))*oy*Power(z,4)) + (2*Power(re,3)*v + 2*(-a + b)*c*fy*Power(re,2)*z - a*c*fy*Power(z,3))*(-2*Power(re,6)*w + 2*(a - b)*c*fx*Power(re,5)*z + a*c*fx*Power(re,3)*Power(z,3) + Sqrt(Power(2*Power(re,3)*(ox - w) + 2*(a - b)*c*fx*Power(re,2)*z + a*c*fx*Power(z,3),2)*(Power(re,6) + 4*b*c*Power(re,3)*(-(fx*ox) - fy*oy + fy*v + fx*w)*z + 4*b*(-a + b)*Power(c,2)*(Power(fx,2) + Power(fy,2))*Power(re,2)*Power(z,2) - 2*a*b*Power(c,2)*(Power(fx,2) + Power(fy,2))*Power(z,4)))) - 2*oy*(-2*Power(re,9)*w + 2*(a - b)*c*fx*Power(re,8)*z + 4*(a - b)*b*Power(c,2)*Power(re,5)*(fx*fy*v + 2*Power(fx,2)*w + Power(fy,2)*w)*Power(z,2) - 4*Power(a - b,2)*b*Power(c,3)*fx*(Power(fx,2) + Power(fy,2))*Power(re,4)*Power(z,3) - 4*a*(a - b)*b*Power(c,3)*fx*(Power(fx,2) + Power(fy,2))*Power(re,2)*Power(z,5) - Power(a,2)*b*Power(c,3)*fx*(Power(fx,2) + Power(fy,2))*Power(z,7) + c*Power(re,6)*z*(-4*b*w*(fy*v + fx*w) + a*fx*Power(z,2)) + Power(re,3)*(2*a*b*Power(c,2)*(fx*fy*v + 2*Power(fx,2)*w + Power(fy,2)*w)*Power(z,4) + Sqrt(Power(2*Power(re,3)*(ox - w) + 2*(a - b)*c*fx*Power(re,2)*z + a*c*fx*Power(z,3),2)*(Power(re,6) + 4*b*c*Power(re,3)*(-(fx*ox) - fy*oy + fy*v + fx*w)*z + 4*b*(-a + b)*Power(c,2)*(Power(fx,2) + Power(fy,2))*Power(re,2)*Power(z,2) - 2*a*b*Power(c,2)*(Power(fx,2) + Power(fy,2))*Power(z,4))))))/(2.*b*c*z*(2*Power(re,3)*(ox - w) + 2*(a - b)*c*fx*Power(re,2)*z + a*c*fx*Power(z,3))*(2*Power(re,3)*(fy*(oy - v) + fx*(ox - w)) + 2*(a - b)*c*(Power(fx,2) + Power(fy,2))*Power(re,2)*z + a*c*(Power(fx,2) + Power(fy,2))*Power(z,3)))

while True:
    # calculate new position
    npos  = np.array([getx(x, y), gety(x, y)])
    print(npos)

    # get the error between new and old
    error = np.linalg.norm(npos - np.array([x, y]))

    # if error is less than 1, break
    # if error < 1:
    #     break

    # show error
    input()

    # setup new old position
    x, y = npos
