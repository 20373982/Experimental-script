# Commonly-Used Scripts for Experimental Evaluation

### Environment

GCC/G++ version: 8.4.0

Python version: 3.9.16

cmake version: 3.22.1

OS: Ubuntu 18.04.4 LTS

### Description about the Dataset

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

The **unzip -d** command  will create a new directory, "SPANN/enron", to contain two files: **enron_dataset.txt** and **enron_query.txt**.

#### Generate the query parameter file

Run the following commands in Linux:

```
cd batchRun
mkdir ../SPANN/data
python generate_data_0.py
```

This **generate_data_0.py** file will generate the experimental parameter settings for queries. 
After running the commands, there will be several directories in the path **../SPANN/data/**, and there will be one file **data_0.dat** that contains the parameter setting in each directory.

### Test All Parameter Settings by Scripts

#### Compile the algorithm, SPANN

Run the following commands in Linux:

```
cd SPANN
cmake .
make
```

The **cmake** command  will create the **Makefile**, and the **make** command will compile the algorithm and produce an executable program called **SPANN**.

#### Test the query parameters in parallel by scripts

Run the following commands in Linux:

```
cd batchRun
mkdir ../SPANN/result
python runRealData.py
```

This **runRealData.py** file will run the experimental test based on the parameter settings for queries. 
After running the command, there will be several directories in the path **../SPANN/result/SPANN**, and there will be one file **data_0.dat** that contains the experimental result that corresponds to the specific parameter setting in each directory.

#### Draw the figures of experimental results

Run the following command:

```
cd batchRun
ipython ./figure_draw.ipynb
```

Or, you can directly open the **figure_draw.ipynb** file through **Jupyter Notebook** or **Visual Studio Code**.

