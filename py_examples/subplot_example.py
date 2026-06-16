import matplotlib.pyplot as plt
import numpy as np

n = 100
x = np.linspace(0, 2 * np.pi, n)
sinY = np.sin(x)
cosY = np.cos(x)

plt.subplot(1, 2, 1)
plt.plot(x, sinY, 'b')
plt.title("Sine")
plt.grid(True)

plt.subplot(1, 2, 2)
plt.plot(x, cosY, 'r')
plt.title("Cosine")
plt.grid(True)

plt.tight_layout()
plt.show()