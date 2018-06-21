import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import spline


freq_log = "codeep.log"
time_interval = 10

def get_log_data():
    """
    Get keystrokes record from log
    """
    timestamp = []
    keystrokes = []
    with open(freq_log, "r") as f:
        for line in f.readlines():
            t, k = line.split('\t')[0], line.split('\t')[1]
            timestamp.append(int(t))
            keystrokes.append(int(k))
    return timestamp, keystrokes

def normalize(time, ks):
    """
    Normalize the data. Set time interval as [t, t+10].
    """
    time_ = np.arange(0, time[-1]+time_interval, time_interval)
    normalized_ks = []
    t = 0
    for i in range(len(time_)):
        if t < len(time) and abs(time_[i]-time[t]) <= time_interval/2:
            normalized_ks.append(ks[t])
            t += 1
        else:
            normalized_ks.append(0)
    return time_, np.array(normalized_ks)

def smoothing(time, ks):
    """
    Smoothing the curve
    """
    x_smooth = np.linspace(time.min(), time.max(), len(time)*5)
    y_smooth = spline(time, ks, x_smooth)
    return x_smooth, y_smooth

def draw():
    """
    Draw the keystrokes frequency graph.
    """
    t_, k_ = get_log_data()
    timestamp, keystrokes = normalize(t_, k_)
    t_smooth, k_smooth = smoothing(timestamp, keystrokes)

    fig, ax = plt.subplots(figsize=(10, 4))
    plt.plot(t_smooth, k_smooth, 'r-')
    ax.set_ylim(0, k_smooth.max()+10)
    plt.show()

draw()
