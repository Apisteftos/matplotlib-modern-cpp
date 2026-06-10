import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2 * np.pi, 100)

fig = plt.figure(figsize=(10, 8))


ax1 = plt.subplot2grid((3, 3), (0, 0), colspan=3)
ax1.plot(x, np.sin(x), 'b')
ax1.set_title("Sine - full width")


ax2 = plt.subplot2grid((3, 3), (1, 0), colspan=2)
ax2.plot(x, np.cos(x), 'r')
ax2.set_title("Cosine - 2 cols")

ax3 = plt.subplot2grid((3, 3), (1, 2), rowspan=2)
ax3.plot(x, np.tan(x), 'g')
ax3.set_title("Tan - 2 rows")
ax3.set_ylim(-5, 5)


ax4 = plt.subplot2grid((3, 3), (2, 0))
ax4.plot(x, np.sin(x) * np.cos(x), 'm')
ax4.set_title("sin*cos")

ax5 = plt.subplot2grid((3, 3), (2, 1))
ax5.plot(x, np.sin(x) ** 2, 'orange')
ax5.set_title("sin²")

fig.suptitle("subplot2grid example")
fig.tight_layout()
plt.show()