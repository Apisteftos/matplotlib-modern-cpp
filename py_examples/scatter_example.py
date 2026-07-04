import matplotlib.pyplot as plt
import numpy as np

np.random.seed(42)
x = np.random.randn(100)
y = np.random.randn(100)
sizes  = np.random.randint(20, 300, 100)   
colors = np.random.rand(100)               

fig, axes = plt.subplots(2, 2, figsize=(12, 8))


axes[0, 0].scatter(x, y, color='blue')
axes[0, 0].set_title("Basic scatter")
axes[0, 0].grid(True)


axes[0, 1].scatter(x, y, s=sizes, color='red', alpha=0.5)
axes[0, 1].set_title("Variable size")
axes[0, 1].grid(True)


sc = axes[1, 0].scatter(x, y, c=colors, cmap='viridis', alpha=0.7)
fig.colorbar(sc, ax=axes[1, 0])
axes[1, 0].set_title("Colormap")
axes[1, 0].grid(True)


sc2 = axes[1, 1].scatter(x, y, s=sizes, c=colors, cmap='plasma',
                          alpha=0.7, edgecolors='black', linewidths=0.5)
fig.colorbar(sc2, ax=axes[1, 1])
axes[1, 1].set_title("Size + color + colormap")
axes[1, 1].grid(True)

fig.suptitle("scatter examples")
fig.tight_layout()
plt.show()