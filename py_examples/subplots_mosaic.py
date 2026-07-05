import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 2 * np.pi, 100)


mosaic = [
    ['A', 'A', 'B'],
    ['C', 'D', 'B'],
    ['C', 'D', 'E'],
]

fig, axes = plt.subplot_mosaic(mosaic, figsize=(12, 8))


axes['A'].plot(x, np.sin(x), 'b')
axes['A'].set_title("Sine — full width")
axes['A'].grid(True)


axes['B'].plot(x, np.cos(x), 'r')
axes['B'].set_title("Cosine — tall")
axes['B'].grid(True)


axes['C'].plot(x, np.tan(x), 'g')
axes['C'].set_title("Tangent")
axes['C'].set_ylim(-5, 5)
axes['C'].grid(True)


axes['D'].scatter(np.random.randn(50), np.random.randn(50), color='purple')
axes['D'].set_title("Scatter")
axes['D'].grid(True)


axes['E'].bar([1, 2, 3], [4, 2, 5], color='orange')
axes['E'].set_title("Bar")
axes['E'].grid(True)

fig.suptitle("subplot_mosaic example")
fig.tight_layout()
plt.show()