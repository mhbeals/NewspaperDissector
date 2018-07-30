# Newspaper Dissector v.0.3.5.2

The *Newspaper Dissector* is visualisation software for categorising and visualising newspaper pages based on category and word count. Based upon code built at the Software Sustainability Institute's 2017 Collaboration Workshop with the support of Geraint Palmer and Vince Knight (Cardiff University).

An example of its use can be seen in the [Anatomy of a Newspaper blog series](http://mhbeals.com/anatomy-of-a-newspaper-the-caledonian-mercury-20-june-1825/) and the forthcoming article "Close readings of big data: Triangulating patterns of textual reappearance and attribution in the Caledonian Mercury, 1820-1840" *Victorian Periodicals Review*, 2018.

## Requirements

This programme requires 

+ [Visual C++ Redistributable for Visual Studio 2015](https://www.microsoft.com/en-gb/download/details.aspx?id=48145)
+ [Python 3](https://www.python.org/downloads/)

## Configuration of Input Data

### Data File

**Each row of the data file should include the following fields:**

+ Document ID
+ Page number
+ Column number 
  + Must be numbered left to right
+ Snippet number
  + Must be numbered top to bottom
+ Category (advert, commentary, miscellany, news, numerical, local, etc)
  + Category text will appear as a label on the final visualisation
  + Category may be left blank to exclude labels on the visualisation
+ Legend Key (a, b, c, d, etc)
  + The key can be any single character
  + The key will be matched to keys given in the legend file to colourise the final visualisation
  + The legend key does not need to represent the same information as the Category
+ Text of the article *OR* a numeric size value, such as word count, line count or column inches
  + Text values should not contain any line breaks ("\n") or tab markers ("\t")
  + Numeric values may be integers ("130") or decimal values ("3.4")

**For example:**

    1820_06_15_Caledonian Mercury	1	1	1	Meeting	r	"Sample Text"
    1820_06_15_Caledonian Mercury	1	1	2	Loan/Borrow	l	"Sample Text"
    1820_06_15_Caledonian Mercury	1	1	3	Loan/Borrow	l	"Sample Text"
    1820_06_15_Caledonian Mercury	1	1	4	Loan/Borrow	r	"Sample Text"

**Or:**

    1820_06_15_Caledonian Mercury	1	1	1	Meeting	r	1.5
    1820_06_15_Caledonian Mercury	1	1	2	Loan/Borrow	l	2.0
    1820_06_15_Caledonian Mercury	1	1	3	Loan/Borrow	l	3
    1820_06_15_Caledonian Mercury	1	1	4	Loan/Borrow	r	1.5

Example *data.tsv* and *datanum.tsv* files are included in the release directory, alongside the executable.

### Legend File

**Each row of the data file should include the following fields:**

+ Legend Label
+ Legend Key (a, b, c, d, etc)
  + The key can be any single character
  + The key will be matched to keys given in the data file to colourise the final visualisation

**For example:**

	News	a
	Commentary	b
	Advertising	c
	Miscellany	d

An example *legend.tsv* file is included in the release directory, alongside the executable.

Please report any errors or exceptions to the author, [M. H. Beals](m.h.beals@lboro.ac.uk)

## Use

To use the Newspaper Dissector, place the executable file (NewspaperDissector.exe) in a directory/folder with one or more tab-separated (.tsv) data and legend data files. The files should have no headers and include only the raw data.

Once run, the programme will ask for your working directory. You must include the full path to your data files (usually the folder in which NewspaperDissector.exe has been placed) including the final "\".

The programme will then provide you with 3 options, plus the option to exit the programme.

### A) Configure data files

This options allows you to change which files the programme accesses and how it interprets them. 

#### F) Main data file

This options allows you to change the file name of the page/snippet data, as well as indicate if you have used text (from which a wordcount will be automatically calculated) or a numeric value in the final column.  By default, the programme expects a file named *data.tsv* which contains text in the final column.

#### G) Legend data File

This options allows you to change the file name of the legend data or to manually enter labels and keys.  By default, the programme expects a file named *legend.tsv*.

### B) Configure visualisation

This option allows you to set (or change) the colour scheme of your visualisation. You currently have three options.  

+ (F)ull colour, using MatPlotLib *hsv*, allowing 9 values
+ (C)olourblind friendly, using MatPlotLib *nipy_spectral*, allowing 5 values
+ (G)reyscale, using MatPlotLib *Greys*, allowing 10 values
+ (P)atterns, using MatPlotLib *Greys*, and a variety of patterns, allowing 10 values

Samples of these can be found [here](samples.md)

If you do not configure this option, you will be prompted to do so the first time you create a visualisation. You must use this option if you wish to change the colour scheme during subsequent runs.

### C) Configure the python command

This option will allow you to replace *python* with another command in the final batch file, for example, *python3*. 

### D) Create a visualisation

This option create two python files, one containing the code to create the page visualisations and one to create the horizontal and vertical legend images.  It will then attempt to run both programmes and create the PNG images.  The programme is currently set to use the command "python" rather than "python3". If your python installation requires the later (or another variant) you will need to run the python command line configuration (above).

## Changelog

**v.0.3.5.2**: 

+ Improved colourblind scheme
+ Updated samples

**v.0.3.5.1**: 

+ Bug fixes 
+ Add colour scheme samples

**v.0.3.5.0**: 

+ Allow configuration of python command line
+ Improved patterns to avoid dark backgrounds

**v.0.3.4.0**: 

+ Improved greyscale
+ Added patterned colour scheme

**v.0.3.3.0**: 

+ Added word count / line count / column inches option to data file
+ Simplified input structure to combine date and title data into document identifier

**v.0.3.2.0**: 

+ Redesigned menus
+ Allowed for manual input of legend details
+ Allowed for in-application specification of colour scheme
+ Simplified input structure

**v.0.2.2.0**: 

+ Fixed fatal error in compiled version
