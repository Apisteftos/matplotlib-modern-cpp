import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2 * np.pi, 100)

fig, axes = plt.subplots(1, 2, figsize=(10, 4))

# Sine
axes[0].plot(x, np.sin(x), 'b')
axes[0].set_title('Sine')
axes[0].grid(True)

# Cosine
axes[1].plot(x, np.cos(x), 'r')
axes[1].set_title('Cosine')
axes[1].grid(True)


fig.suptitle("Subplots")
fig.savefig("./pics/subplots_example.png")
fig.tight_layout()

plt.tight_layout()
plt.show()