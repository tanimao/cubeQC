from matplotlib import pyplot as plt
import numpy as np
import time
from numba.decorators import jit


##############サインコサイン
@jit
def sine(theta):
    si = np.sin(theta)
    return si
@jit
def cosine(theta):
    co = np.cos(theta)
    return co

def INITIAL():
    file = open('edgedata.txt')
    a = np.zeros(16)
    b = np.zeros(16)
    sine_iphi = np.zeros(16)
    cosine_iphi = np.zeros(16)
    for iphi in range(16):

        sine_iphi[iphi]   = sine(iphi*np.pi/8)
        cosine_iphi[iphi] = cosine(iphi*np.pi/8)
    for i, line in enumerate(file):
        if i == 0 :
            data0 = line.split()
            median_x = float(data0[0])
            median_y = float(data0[1])
            rhole    = float(data0[2])
        else :    
            data = line.split()
            a[i-1] = float(data[0])
            b[i-1] = float(data[1])
    initial = [median_x, median_y, rhole]
    #print(initial)
    const = [a, b, sine_iphi, cosine_iphi]
    out = [initial, const]
    file.close()
    #initial = [0, 0, 0]
    return out

def f(x, a, b, si, co):
    E = np.zeros(16)

    """偏微分したい関数: f(x) = x0^2 + x1^2"""
    Esum = 0
    for i in range(16):
        E[i] = (a[i]-x[0]-x[2]*co[i]) ** 2 + (b[i]-x[1]+x[2]*si[i]) ** 2
        Esum = Esum + E[i]

    return Esum

def numerical_diff(f, x, i):
    """中央差分を元に数値微分する関数 (偏微分)

    :param function f: 偏微分する関数
    :param numpy.ndarray x: 偏微分する引数
    :param int i: 偏微分する変数のインデックス
    """
    I, C = INITIAL()
    a=C[0]
    b=C[1]
    si=C[2]
    co=C[3]
    # 丸め誤差で無視されない程度に小さな値を用意する
    h = 1e-4
    # 偏微分する変数のインデックスにだけ上記の値を入れる
    h_vec = np.zeros_like(x)
    h_vec[i] = h
    # 数値微分を使って偏微分する
    return (f(x + h_vec, a, b, si, co) - f(x - h_vec, a, b, si, co)) / (2 * h)


def numerical_gradient(f, x):
    """勾配を計算する関数

    勾配というのは、全ての変数について偏微分した結果をベクトルとしてまとめたものを言う。
    """
    # 勾配を入れるベクトルをゼロで初期化する
    grad = np.zeros_like(x)

    for i, _ in enumerate(x):
        # i 番目の変数で偏微分する
        grad[i] = numerical_diff(f, x, i)
        


    # 計算した勾配を返す
    return grad


def gradient_descent(f, initial_position, const, learning_rate, steps):
    """勾配法で最小値を求める関数
    
    :param function f: 最小値を見つけたい関数
    :param numpy.ndarray initial_position: 関数の初期位置
    :param float learning_rate: 学習率
    :param int steps: 学習回数
    """
    # 現在地を示すカーソル
    x = initial_position

    # 学習を繰り返す
    for _ in range(steps):
        # 現在地の勾配 (どちらにどれだけ進むべきか) を得る
        grad = numerical_gradient(f, x)
        # 勾配を元にして現在地を移動する
        x -= learning_rate * grad
        #print('\ngradient[{}]={}'.format(_, grad))

#        print('Esum[{}]={}'.format(_, f(x, const[0], const[1], const[2], const[3])))
    # 最終的な位置を返す
    return x


def manualminimization():
        
    start_minimize = time.time()
    # 勾配法を使って関数 f() の最小値を探す (初期位置は 1, 2)
#    output  = f
    print('\n#call manualminimize') 
#    print(output)
#    Esum, initial = output
    initial, const = INITIAL()
    learning_rate = 0.01
    steps = 50
    print("learning_rate = {}, steps = {} ".format(learning_rate, steps))
    print('initial_position = {}'.format(initial))
    #print('a ={}'.format(const[0]) )
    print('はじめのEsumの値:{}'.format(f(initial, const[0], const[1], const[2], const[3])))
    min_pos = gradient_descent(f,initial, const, learning_rate, steps)
    print('勾配法が見つけた最小値: {0}'.format(min_pos))
    print('time:{} sec'.format(time.time()-start_minimize))
    print('最小値でのEsumの値:{}'.format(f(min_pos, const[0], const[1], const[2], const[3])))
    
    pos_Emin = [min_pos, f(min_pos, const[0], const[1], const[2], const[3])]
    return pos_Emin


if __name__ == '__main__':
    manualminimization()
