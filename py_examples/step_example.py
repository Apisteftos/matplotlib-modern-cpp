import matplotlib.pyplot as plt
import numpy as np

x = np.arange(0, 10, 1)
y = np.array([2, 3, 5, 4, 6, 5, 7, 8, 6, 9])

fig, axes = plt.subplots(2, 2, figsize=(10, 8))


axes[0, 0].step(x, y, where='pre', color='b')
axes[0, 0].plot(x, y, 'o', color='gray', alpha=0.3)
axes[0, 0].set_title("where='pre' (default)")
axes[0, 0].grid(True)


axes[0, 1].step(x, y, where='post', color='r')
axes[0, 1].plot(x, y, 'o', color='gray', alpha=0.3)
axes[0, 1].set_title("where='post'")
axes[0, 1].grid(True)


axes[1, 0].step(x, y, where='mid', color='g')
axes[1, 0].plot(x, y, 'o', color='gray', alpha=0.3)
axes[1, 0].set_title("where='mid'")
axes[1, 0].grid(True)


axes[1, 1].step(x, y, where='pre', color='purple', linewidth=2,
                marker='o', markersize=6, linestyle='--')
axes[1, 1].set_title("Styled step plot")
axes[1, 1].grid(True)

fig.suptitle("step() examples")
fig.tight_layout()
plt.show()