import matplotlib.pyplot as plt
import numpy as np

fig, axes = plt.subplots(2, 2, figsize=(12, 8))


axes[0, 0].text(0.5, 0.5, "Default (None)",
                fontsize=20,
                fontfamily='serif',
                fontfeatures=None,
                ha='center', va='center')
axes[0, 0].set_title("fontfeatures=None")


axes[0, 1].text(0.5, 0.5, "0123456789",
                fontsize=30,
                fontfamily='serif',
                fontfeatures=['onum'],  
                ha='center', va='center')
axes[0, 1].set_title("fontfeatures=['onum'] — oldstyle numerals")


axes[1, 0].text(0.5, 0.5, "0123456789",
                fontsize=30,
                fontfamily='serif',
                fontfeatures=('lnum', 'tnum'),  
                ha='center', va='center')
axes[1, 0].set_title("fontfeatures=('lnum', 'tnum')")


axes[1, 1].text(0.5, 0.5, "fi fl AV",
                fontsize=30,
                fontfamily='serif',
                fontfeatures=['liga', 'kern'],
                ha='center', va='center')
axes[1, 1].set_title("fontfeatures=['liga', 'kern']")

fig.suptitle("fontfeatures examples")
fig.tight_layout()
plt.show()