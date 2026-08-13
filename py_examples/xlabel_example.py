import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2 * np.pi, 100)
y = np.sin(x)

# ============================================================
# 1 — axes.Axes.set_xlabel 
# ============================================================
fig, axes = plt.subplots(1, 2, figsize=(12, 4))

axes[0].plot(x, y, 'b')
axes[0].set_xlabel("Time (seconds)",  
                   color='blue',
                   fontsize=14,
                   fontweight='bold',
                   labelpad=10,
                   loc='center')
axes[0].set_title("axes.set_xlabel()")
axes[0].grid(True)

axes[1].plot(x, y, 'r')
axes[1].set_xlabel("Amplitude",
                   color='red',
                   fontstyle='italic',
                   loc='right')
axes[1].set_title("axes.set_xlabel() — loc='right'")
axes[1].grid(True)

fig.suptitle("Axes.set_xlabel — OOP style")
fig.tight_layout()


# ============================================================
# 2 — pyplot.xlabel 
# ============================================================
fig2, _ = plt.subplots(1, 2, figsize=(12, 4))

plt.subplot(1, 2, 1)
plt.plot(x, y, 'g')
plt.xlabel("Time (seconds)",          
           color='green',
           fontsize=14,
           fontweight='bold',
           labelpad=10)
plt.title("plt.xlabel()")
plt.grid(True)

plt.subplot(1, 2, 2)
plt.plot(x, y, 'm')
plt.xlabel("Amplitude",
           color='purple',
           fontstyle='italic',
           loc='right')
plt.title("plt.xlabel() — loc='right'")
plt.grid(True)

plt.suptitle("pyplot.xlabel — state-machine style")
plt.tight_layout()
plt.show()