import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2 * np.pi, 100)

fig, axes = plt.subplots(2, 2, figsize=(10, 8))

axes[0, 0].plot(x, np.sin(x), 'b')
axes[0, 0].set_title('Sine')
axes[0, 0].set_xlabel('x')
axes[0, 0].set_ylabel('y')

axes[0, 1].plot(x, np.cos(x), 'r')
axes[0, 1].set_title('Cosine')
axes[0, 1].set_xlabel('x')
axes[0, 1].set_ylabel('y')

axes[1, 0].plot(x, np.tan(x), 'g')
axes[1, 0].set_title('Tangent')
axes[1, 0].set_xlabel('x')
axes[1, 0].set_ylabel('y')
axes[1, 0].set_ylim(-5, 5)

axes[1, 1].plot(x, np.sin(x) + np.cos(x), 'm')
axes[1, 1].set_title('Sin + Cos')
axes[1, 1].set_xlabel('x')
axes[1, 1].set_ylabel('y')

plt.tight_layout()
plt.show()