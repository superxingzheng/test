import matplotlib.pyplot as plt
from numpy import genfromtxt

data = genfromtxt('result.csv', delimiter=',')
capital = data[:,0]
value = data[:,1]
best_action = data[:,2]

plt.figure(1)

plt.subplot(211)
plt.plot(capital, value, 'b^')

plt.subplot(212)
plt.plot(capital, best_action, 'gs')
#plt.axis([0, 100, 0, 50])
plt.show()
