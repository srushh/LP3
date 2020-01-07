#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


# In[2]:


data = pd.read_csv('/home/srushti/BE/LP3/dataset.csv')


# In[3]:


X = data.iloc[:, 0]
Y = data.iloc[:, 1]


# In[4]:


plt.scatter(X, Y)
plt.show()


# In[5]:


m = 0
b = 0

alpha = 0.0001  
epochs = 1000  

n = float(len(X)) 

 
for i in range(epochs): 
    Y_pred = m*X + b  
    updated_m = (-2/n) * sum(X * (Y - Y_pred))  
    updated_b = (-2/n) * sum(Y - Y_pred)  
    m = m - alpha * updated_m  
    b = b - alpha * updated_b  
    
print (m, b)


# In[6]:


regression_line=[(m*x)+b for x in X]

plt.scatter(X, Y) 
plt.plot(X,regression_line, color='red')  
plt.show()


# In[7]:


regression_line=[(m*x)+b for x in X]

plt.scatter(X, Y) 
plt.plot(X,regression_line, color='red')  

X_new = 8

Y_new = m*X_new + b
print(Y_new)
plt.scatter(X_new,Y_new)
plt.show()
