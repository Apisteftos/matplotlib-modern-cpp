import matplotlib.pyplot as plt

x = [1, 2, 3, 4, 5]
y = [10, 24, 36, 48, 55]

plt.plot(x, y)

plt.tick_params(
    axis='both',      
    labelsize=12,     
    length=8,         
    width=2,          
    colors='navy',    
    direction='inout' 
)

plt.show()