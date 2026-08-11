import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2 * np.pi, 20)
y1 = np.sin(x)
y2 = np.cos(x)

fig, axes = plt.subplots(2, 2, figsize=(12, 8))


axes[0, 0].stem(x, y1)
axes[0, 0].set_title("Basic stem")
axes[0, 0].grid(True)


axes[0, 1].stem(x, y1,
                linefmt='b-',      
                markerfmt='ro',    
                basefmt='k-')      
axes[0, 1].set_title("Custom colors")
axes[0, 1].grid(True)


axes[1, 0].stem(x, y2,
                linefmt='g-',
                markerfmt='g^',
                basefmt='r--')
axes[1, 0].set_title("Cosine with custom baseline")
axes[1, 0].grid(True)


axes[1, 1].stem(y1, x,
                linefmt='m-',
                markerfmt='ms',
                basefmt='k-',
                orientation='horizontal')
axes[1, 1].set_title("Horizontal stem")
axes[1, 1].grid(True)

fig.suptitle("stem examples")
fig.tight_layout()
plt.show()