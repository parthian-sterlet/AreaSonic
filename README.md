# AreaSonic
Significance of overlap between whole genome tracks using Monte Carlo simulation and normal distribution modeling
# Description
AreaSonic program estimates the significance of overlap between two sets of while-genome regions (tracks) described in BED format. One of the one of the pillars 
of probability theory, [Central limit theorem](https://en.wikipedia.org/wiki/Central_limit_theorem) proved that the overlap between two tracks should possess the normal
distribution. AreaSonic fits a normal model of the total overlap length, and applies Monte Carlo simulation to estimate the distribution of expected overlap length. 
taking into account and perfectly modeling both the distributions of lengths of regions and specers between them. At first step, the observed value Obs of overlap length 
is computed. AreaSonic assigns to the first track the label 'fixed', while the second one is marked as 'permuted'. Now, the first iteration is pefrormed. In particular, 
regions and spacers between them for the permuted track are indexed, this gives two arrays {Regions} and {Spacers}; indices of each array are swapped, and chimeric 
sequence od regions and spacers is assembled; thus, an estimate of overlap length between the fixed and permuted track is computed at the end of the first itatation.
Multiple iterations allow to estimate the expected overlap length Exp and its standard deviation SD. These values are used to compute Z-score estimate as follow: 
Z = (Obs - Exp) / SD. Positive/negative imply the enrichment/depletion in overlaps between two tracks. asymptotic expansion of the complementary error function 
The Areasonic program was successively applied earlier in [Khoroshko et al. (2016)](https://doi.org/10.1371/journal.pone.0157147) and 
[Boldyreva et al. (2017)](https://www.researchgate.net/publication/303295899_Protein_and_Genetic_Composition_of_Four_Chromatin_Types_in_Drosophila_melanogaster_Cell_Lines)

Scheme of AreaSonic algorithm is given below

![scheme](https://github.com/parthian-sterlet/AreaSonic/blob/main/examples/AreaSonic_github.png)

# Requirements
AreaSonic source code is written in C++ language. To compile exetubables from the source code you need:

* In Linux system, C++ compiler, e.g. [GCC](https://gcc.gnu.org/) compiler 
* In Windiws system any VC++ package, e.g. [Microsoft Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)

# Input data
Input data include two tracks in [BED format](https://genome.ucsc.edu/FAQ/FAQformat.html#format1). First three columns are critically important, they represent a notations of chromosomes and left/right positions of genomic regions. 

# Source code
Folder [**src**](https://github.com/parthian-sterlet/areasonic/tree/master/src) contains files with AreaSonic source codes, they respect to decribed below separate modules of pipeline.

# How to compile
* In Linux system: 

git clone https://github.com/parthian-sterlet/areasonic \
cd areasonic\src\
chmod a+x build.sh\
./build.sh

* In Windiws system:

separate compilation of all source files in VC++

Modules **Partition of a genome track by separate chromosomes** and **Permutations** should run consequently if input files are given as whole-genome track, if they are already partitioned by chromosomes, the second module **Permutations** can be used alone

## 1. Partition of a genome track by separate chromosomes
This is just a parsing of a bed formatted file according to values in the first column designating chromosomes

## 2. Permutations
The main part of algorithm performing Monte Carlo simulation

# How to run separate modules
Lists of command line arguments for all modules are described below
