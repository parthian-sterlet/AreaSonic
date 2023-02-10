# AreaSonic
Significance of overlap between whole genome tracks using Monte Carlo simulation and normal distribution modeling
# Description
AreaSonic program estimates the significance (P-value) of an overlap between two sets of while-genome regions (tracks) that described in BED format. The one of the pillars of probability theory, [Central limit theorem](https://en.wikipedia.org/wiki/Central_limit_theorem) proved that the overlap between two tracks should possess the normal distribution. AreaSonic fits a normal model of the total overlap length, and applies Monte Carlo simulation to estimate the distribution of expected overlap length. AreaSonic takes into account and perfectly models both the distributions of lengths of tracks regions and those of spacers lengths between regions. At first step, the observed value Obs of overlap length is computed. AreaSonic assigns to the first track the label 'fixed', while the second one is marked as 'permuted'. Now, the first iteration is started. In particular, regions and spacers between them for the permuted track are indexed, this gives two arrays {Regions} and {Spacers}; indices of each array are swapped, and chimeric sequence od regions and spacers is assembled; thus, an estimate of overlap length between the fixed and permuted track is computed at the end of the first itatation. Multiple iterations allow to estimate the expected overlap length Exp and its standard deviation SD. These values are used to compute Z-score estimate as follows: Z = (Obs - Exp) / SD. Positive/negative Z-score imply the enrichment/depletion in the total overlap length between two tracks. Finally, for extremly large Z-scores (Z > 14) the asymptotic expansion of the [complementary error function](https://en.wikipedia.org/wiki/Error_function) is used to compute P-value, otherwise it computed directly as the integral for the stadard normal distribution. The Areasonic program was successively applied earlier in [Khoroshko et al. (2016)](https://doi.org/10.1371/journal.pone.0157147) and [Boldyreva et al. (2017)](https://www.researchgate.net/publication/303295899_Protein_and_Genetic_Composition_of_Four_Chromatin_Types_in_Drosophila_melanogaster_Cell_Lines)

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

# How to run separate modules
Lists of command line arguments for all modules are described below

## 1. Partition of a genome track by separate chromosomes
This is just a parsing of a bed formatted file according to values in the first column designating chromosomes
[tabnslolbik_wordget.cpp](https://github.com/parthian-sterlet/areasonic/blob/master/src/tabnslolbik_wordget.cpp)

Command line arguments:
1. input file, text table
2. output file, processed text table
3. int number of criteria
4. int list of columns numbers, comma separated 
5. char list of words respecting columns 
6. int match type: 1 exact coincidence (word in a column exactly equal to given input word), 0 only occurrence (substring in a string is enough)
7. int contain type: 0/1 mean searches of lines containing / do not containing words 
8. int logic: 1 means stringent requirement for criteria in all columns, 0 means mild requirement for only one of criteria in at least one of columns

## 2. Permutations
The main part of algorithm performing Monte Carlo simulation
[area_shuffling.cpp](https://github.com/parthian-sterlet/areasonic/blob/master/src/area_shuffling.cpp)

Command line arguments:
1. input file in BED format, permuted track 
2. input file, the list of chromosome lengths 
3. input file in BED format, fixed track 
4. integer number of iterations, minimal 100, at least 500 is required for stable results
5. output file, statistical estimates for the overlap length between two tracks
6. output file, distribution of expected overlap length 
7. input file, list of chromosome names

Perl script file [test.pl](https://github.com/parthian-sterlet/AreaSonic/blob/main/src/test.pl) shows the example run of AreaSonic for tracks of (1) domains of active aquamarine D.melanogaster chromatin from the [HMM model from Boldyreva et al. (2017)](https://www.researchgate.net/publication/303295899_Protein_and_Genetic_Composition_of_Four_Chromatin_Types_in_Drosophila_melanogaster_Cell_Lines) and (2) peaks of Chriz/Chromator protein from [GSM1147251](https://www.ncbi.nlm.nih.gov/geo/query/acc.cgi?acc=GSM1147251). Example presents two runs of programs alternatively using first and second tracks as permuted one. The output [as.txt](https://github.com/parthian-sterlet/AreaSonic/blob/main/src/as.txt) lists the following results as follows.
| Label                | Value                          | Meaning |
|----------------------|--------------------------------|---------|
| AreaVar              | chriz_GSM1147251 3863 8906852  | Permuted track: file name, total count of regions, total length of regions in bp
| AreaConst            | aquamarine       5748 14078400 | Fixed track: file name, total count of regions, total length of regions in bp
| Ncyc                 |                                | Number of iterations
| Real                 | 6950.760                       | Observed overlap length between two input tracks, in kbp (1000 bp)
| PvalueLarger         | 0                              | Fraction of iterations possesssing the higher overlap length than an observed one
| PvalueSmaller        | 1.000000                       | Fraction of iterations possesssing the lower overlap length than an observed one
| Av                   | 1059.620106                    | Average expected overlap length between fixed and permuted tracks, in kbp (1000 bp)
| SD                   | 41.342050                      | Standard deviation of expected overlap length between fixed and permuted tracks, in kbp (1000 bp)
| Zsco                 | 142.497526                     | Z-score of expected overlap length between fixed and permuted tracks, Z-score = (Real - Av) / SD, positive/negative Z-score implies the enrichment/depletion in the total overlap length between two tracks
| -Log10[Pval_approx]  | 4411.54                        | P-value in logarithmic scale, estimation the significance of the total overlap length
