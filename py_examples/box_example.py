import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2 * np.pi, 100)

fig, axes = plt.subplots(1, 3, figsize=(15, 4))


axes[0].plot(x, np.sin(x), 'b')
axes[0].set_title("box on (default)")


axes[1].plot(x, np.sin(x), 'r')
axes[1].set_frame_on(False)
axes[1].set_title("box off")


plt.sca(axes[2])             
axes[2].plot(x, np.sin(x), 'g')
plt.box(False)          
axes[2].set_title("plt.box(False)")

fig.suptitle("box example")
fig.tight_layout()
plt.show()