import DataApi as d
import numpy as np
import pylab as pl

d.init_connection("dsdsa")
data = d.get_data( "device_333", "sensor_1")

x_data = np.array(range(0,len(data)))
y_data = np.array(data)

pl.plot(x_data,y_data)
pl.show()