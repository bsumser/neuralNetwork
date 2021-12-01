## Table of Contents

- [Description](#description)
- [Citation](#citation)
- [Installation](#installation)

## Description

This program is a Neural Net to determine which of 3 possible cultivars of wine a set
of data is based on these characteristics:

1) Alcohol
2) Malic acid
3) Ash
4) Alcalinity of ash
5) Magnesium
6) Total phenols
7) Flavanoids
8) Nonflavanoid phenols
9) Proanthocyanins
10) Color intensity
11) Hue
12) OD280/OD315 of diluted wines
13) Proline 

The program compiles with make or make clean. You can enter the amount of epochs to
loop through the input file, and the amount of lines (1-178) to loop through.

The output values are rated from -1 to 1 based which cultivar the network thinks it 
is.

The network uses 13 input neurons, a hidden layer of 6 neurons, and an output layer
of 3 neurons. Each output neuron outputs a value from -1 to 1. The first neuron
represents cultivar 1, output neuron 2 is cultivar 2, and the same for output neuron
3. 

The data is normalized using a zero unit variance function:
data = (data - mean_data) / standard deviation

Each neuron applies a hyperbolic tan function to the normalized data.


The data set was found in the UCI machine learning database.

## Installation
This program includes a makefile, and can be compiled with the command make. To run, use 
"./main data/wine.csv".

Remove object files and executables with make clean.

## Citation

Original Owners:

Forina, M. et al, PARVUS -
An Extendible Package for Data Exploration, Classification and Correlation.
Institute of Pharmaceutical and Food Analysis and Technologies, Via Brigata Salerno,
16147 Genoa, Italy.

Donor:

Stefan Aeberhard, email: stefan '@' coral.cs.jcu.edu.au

![Your Repository's Stats](https://github-readme-stats.vercel.app/api?username=Your_GitHub_Username&show_icons=true)
