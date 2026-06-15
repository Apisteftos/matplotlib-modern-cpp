import matplotlib.pyplot as plt
import numpy as np


time_sec = np.linspace(0, 100, 100)
time_min = time_sec / 60

y = np.sin(time_sec / 10)

fig, ax1 = plt.subplots(figsize=(10, 5))


ax1.plot(time_sec, y, 'b')
ax1.set_xlabel("Time (seconds)", color='b')
ax1.tick_params(axis='x', labelcolor='b')


ax2 = ax1.twiny()
ax2.set_xlim(ax1.get_xlim()[0] / 60, ax1.get_xlim()[1] / 60) 
ax2.set_xlabel("Time (minutes)", color='r')
ax2.tick_params(axis='x', labelcolor='r')

ax1.set_ylabel("Signal")
fig.suptitle("twiny example — two x-axes")
fig.tight_layout()
plt.show()