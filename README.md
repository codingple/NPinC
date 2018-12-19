# NPinC
#### An implementation of Nested Partition Algorithm for TSP problem in C  

### Description
This program solves Treveling Salesman Problem using Nested Partition.
> Nested Partitions Method for Global Optimization  
> [10.1287/opre.48.3.390.12436](https://pubsonline.informs.org/doi/10.1287/opre.48.3.390.12436)  

The algorithm, in short, gets the local optimum as selecting the subregion with the optimal cost step by step. The input is a textfile containing 2-dimension coordinates of "cities" to go through. It determines the several routes randomly, and choose the _promising_ route for the total distance. With determining the next city gradually, in need, the selected city could be canceled due to the other _promising_ trajectory. The final result is the order of cities and the distance.  
  
### Input
"Citys.txt" is the input textfile. Each line consists of the city name, longitude, and latitude. It assumes that the first line is the start.  
  
