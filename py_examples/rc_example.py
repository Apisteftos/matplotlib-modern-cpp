import matplotlib.pyplot as plt
import numpy as np



plt.rc('grid',       color='#b0b0b0', linewidth=0.8)
plt.rc('grid.major', color='blue',    linewidth=1.2)
plt.rc('grid.minor', color='red',     linewidth=0.6)


plt.rc('legend', loc='best',
                 frameon=True,
                 framealpha=0.2,
                 facecolor='cyan',
                 edgecolor='0.4',
                 fancybox=True)


plt.rc('figure',          figsize=(10, 5),
                          titlesize='medium',
                          facecolor='#f0f0f0')
plt.rc('figure.subplot',  wspace=0.5,
                          left=0.125,
                          right=0.9,
                          top=0.88,
                          bottom=0.11)


plt.rc('axes',        facecolor='white',
                      linewidth=0.8)
plt.rc('axes.spines', right=False,
                      top=False,
                      left=False,
                      bottom=False)


plt.rc('lines', linewidth=2.0,
                markersize=8.0,
                markeredgewidth=1.0,
                markerfacecolor='black',
                markeredgecolor='black')


plt.rc('font', family='serif',
               stretch='normal',
               style='normal',
               variant='normal',
               weight='bold')


plt.rc('xtick', labelsize='medium')
plt.rc('ytick', labelsize=10,
                direction='in')
plt.rc('ytick.minor', ndivs=5)


n = 100
x  = np.linspace(0, 2 * np.pi, n)
y1 = np.sin(x)
y2 = np.cos(x)
y3 = np.tan(x)

fig, axes = plt.subplots(1, 2)

axes[0].plot(x, y1, 'b', label='sin(x)')
axes[0].plot(x, y2, 'r', label='cos(x)')
axes[0].set_title("Sine and Cosine")
axes[0].set_xlabel("X")
axes[0].set_ylabel("Y")
axes[0].legend()

axes[1].plot(x, y3, 'g', label='tan(x)')
axes[1].set_ylim(-5, 5)
axes[1].set_title("Tangent")
axes[1].set_xlabel("X")
axes[1].set_ylabel("Y")
axes[1].legend()

fig.tight_layout()
fig.suptitle("plt.rc example — global styles")
fig.savefig("../pics/rc_py_example.png")
plt.show()

plt.rcdefaults()