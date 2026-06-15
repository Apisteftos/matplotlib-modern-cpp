import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 10, 100)

fig, ax1 = plt.subplots(figsize=(10, 5))


ax1.plot(x, np.sin(x), 'b')
ax1.set_xlabel("X")
ax1.set_ylabel("Sine", color='b')
ax1.tick_params(axis='y', labelcolor='b')


ax2 = ax1.twinx()
ax2.plot(x, np.exp(x), 'r')
ax2.set_ylabel("Exponential", color='r')
ax2.tick_params(axis='y', labelcolor='r')

fig.suptitle("twinx example — two y-axes")
fig.tight_layout()
plt.show()