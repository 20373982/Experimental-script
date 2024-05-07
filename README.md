# General Scripts for Experimental Evaluation

### Environment

GCC/G++ version: 8.4.0

Python version: 3.9.16

cmake version: 3.22.1

OS: Ubuntu 18.04.4 LTS

### Description about the datasets

#### Dataset: enron.zip

**enron_dataset.txt**：a vector database that consists of 94,987 vectors in total, each with 1369 dimensions

**enron_query.txt**：the vector to be queried

**enron_groundtruth.txt**：the exact result for the queries

#### Unzip the dataset

Run the following commands in Linux:

```
cd SPANN
unzip -d enron enron.zip
```

The command **unzip -d** will create a new directory, "SPANN/enron", to contain two files: **enron_dataset.txt** and **enron_query.txt**.



### Usage of the Scripts


Object code ：./SPANN


Script code ：cd batchRun

Script code ： python generate_data_0.py    --  generate batch experiment parameters

​						  mv ./tmp/* ../SPANN/realData/    --  move the parameters to the object code dir

​						  python runRealData.py    --  run object code in batches

​						  ipython .\figure_draw.ipynb    --  draw

