import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2 * np.pi, 100)
y1 = np.sin(x)
y2 = np.cos(x)

fig, axes = plt.subplots(2, 2, figsize=(12, 8))


axes[0, 0].plot(x, y1, 'b', label='sin(x)')
axes[0, 0].plot(x, y2, 'r', label='cos(x)')
axes[0, 0].fill_between(x, y1, y2, alpha=0.3, color='purple')
axes[0, 0].set_title("fill_between two curves")
axes[0, 0].legend()
axes[0, 0].grid(True)


axes[0, 1].plot(x, y1, 'b')
axes[0, 1].fill_between(x, y1, 0, alpha=0.3, color='blue')
axes[0, 1].set_title("fill_between curve and zero")
axes[0, 1].grid(True)


axes[1, 0].plot(x, y1, 'b', label='sin(x)')
axes[1, 0].plot(x, y2, 'r', label='cos(x)')
axes[1, 0].fill_between(x, y1, y2, where=(y1 > y2), alpha=0.3, color='green', label='sin > cos')
axes[1, 0].fill_between(x, y1, y2, where=(y1 < y2), alpha=0.3, color='red',   label='cos > sin')
axes[1, 0].set_title("fill_between with condition")
axes[1, 0].legend()
axes[1, 0].grid(True)


axes[1, 1].fill(x, y1, alpha=0.3, color='orange')
axes[1, 1].set_title("fill — closed polygon")
axes[1, 1].grid(True)

fig.suptitle("fill examples")
fig.tight_layout()
plt.show()