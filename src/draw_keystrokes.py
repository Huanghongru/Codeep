import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import spline


freq_log = "_codeep.log"
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
    Smoothing the curve.
    Basic idea is to insert more points.
    """
    x_smooth = np.linspace(time.min(), time.max(), len(time)*128)
    y_smooth = spline(time, ks, x_smooth)
    return x_smooth, y_smooth

def draw():
    """
    Draw the keystrokes frequency graph.
    To draw a gradient color line, the most simple method is to scatter
    the splined points according to build-in colormap!
    """
    t_, k_ = get_log_data()
    timestamp, keystrokes = normalize(t_, k_)
    t_smooth, k_smooth = smoothing(timestamp, keystrokes)
    print (len(t_smooth))

    fig, ax = plt.subplots(figsize=(10, 4))
    s = np.ones(len(t_smooth))*1.25

    # Map the keystrokes to colormap.
    c = k_smooth
    plt.scatter(t_smooth, k_smooth, s=s, c=c, 
        cmap=plt.get_cmap('summer_r'), marker='.')

    ax.set_ylim(0, k_smooth.max()+10)
    plt.show()

draw()
