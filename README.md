# Experimental-script

### Usage of the algorithms

#### Environment

gcc/g++ version: 7.4.0

OS: Ubuntu

####Compile the algorithms

Object code ：cd SPANN  &&  cmake .  &&  make

Script code ：cd batchRun

#### Run the algorithms

Object code ：./SPANN

Script code ： python generate_data_0.py    --  generate batch experiment parameters

​						  mv ./tmp/* ../SPANN/realData/    --  move the parameters to the object code dir

​						  python runRealData.py    --  run object code in batches

​						  ipython .\figure_draw.ipynb    --  draw

### Description of the datasets

#### Environment

python 3.9

#### Dataset

enron/enron_dataset ：Database data , 94,987 vectors, each with 1369 dimensions

enron/enron_query ：the vector to be queried