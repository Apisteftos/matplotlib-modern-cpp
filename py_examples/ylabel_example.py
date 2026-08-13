import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2 * np.pi, 100)
y = np.sin(x)

# ============================================================
# 1 — axes.Axes.set_ylabel 
# ============================================================
fig, axes = plt.subplots(1, 2, figsize=(12, 4))

axes[0].plot(x, y, 'b')
axes[0].set_ylabel("Amplitude",
                   color='blue',
                   fontsize=14,
                   fontweight='bold',
                   labelpad=10,
                   loc='center')
axes[0].set_title("axes.set_ylabel()")
axes[0].grid(True)

axes[1].plot(x, y, 'r')
axes[1].set_ylabel("Signal (mV)",
                   color='red',
                   fontstyle='italic',
                   loc='top')           # 'bottom', 'center', 'top'
axes[1].set_title("axes.set_ylabel() — loc='top'")
axes[1].grid(True)

fig.suptitle("Axes.set_ylabel — OOP style")
fig.tight_layout()


# ============================================================
# 2 — pyplot.ylabel 
# ============================================================
plt.figure(figsize=(12, 4))

plt.subplot(1, 2, 1)
plt.plot(x, y, 'g')
plt.ylabel("Amplitude",
           color='green',
           fontsize=14,
           fontweight='bold',
           labelpad=10)
plt.title("plt.ylabel()")
plt.grid(True)

plt.subplot(1, 2, 2)
plt.plot(x, y, 'm')
plt.ylabel("Signal (mV)",
           color='purple',
           fontstyle='italic',
           loc='top')
plt.title("plt.ylabel() — loc='top'")
plt.grid(True)

plt.suptitle("pyplot.ylabel — state-machine style")
plt.tight_layout()
plt.show()