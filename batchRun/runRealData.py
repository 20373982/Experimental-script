import os
import sys
import random
import subprocess
import multiprocessing

execNames = ["SPANN"]
prefix = '../SPANN'


def run(execName, dataFile, logFile):
    cmdLine = prefix + "/%s %s %s" % (execName, dataFile, prefix)
    print(cmdLine)
    try:
        line = subprocess.check_output(cmdLine, shell=True, text=True)
    except subprocess.CalledProcessError as e:
        line = e.output
    print(line)
    print("[Finish]", cmdLine)
    with open(logFile, "w") as fout:
        fout.write(line)


def batchRun(srcFilePath, desFilePath, dataSetN, nprocess):
    pool = multiprocessing.Pool(processes=nprocess)

    if not os.path.exists(desFilePath):
        os.mkdir(desFilePath)
    dirNames = os.listdir(srcFilePath)
    for dataSetId in range(dataSetN):
        for execName in execNames:
            tmpFilePath = os.path.join(desFilePath, execName)
            if not os.path.exists(tmpFilePath):
                os.mkdir(tmpFilePath)
            for dirName in dirNames:
                tmpFilePath = os.path.join(desFilePath, execName, dirName)
                if not os.path.exists(tmpFilePath):
                    os.mkdir(tmpFilePath)
                srcFileName = "data_%d.dat" % (dataSetId)
                desFileName = os.path.join(desFilePath, execName, dirName, srcFileName)
                srcFileName = os.path.join(srcFilePath, dirName, srcFileName)
                if os.path.exists(desFileName):
                    continue
                pool.apply_async(run, (execName, srcFileName, desFileName,))

    pool.close()
    pool.join()


def test():
    dataSetN = 1
    nprocess = 3
    srcFilePath = prefix + "/realData"
    desFilePath = prefix + "/realResult"
    batchRun(srcFilePath, desFilePath, dataSetN, nprocess)


if __name__ == '__main__':
    test()
