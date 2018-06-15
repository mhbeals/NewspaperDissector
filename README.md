# Newspaper Dissector v.0.2.2.0

The *Newspaper Dissector* is visualisation software for categorising and visualising newspaper pages based on topic, word count and source. Based upon code built at the Software Sustainability Institute's 2017 Collaboration Workshop with the support of Geraint Palmer and Vince Knight (Cardiff University).

An example of its use can be seen in the [Anatomy of a Newspaper blog series](http://mhbeals.com/anatomy-of-a-newspaper-the-caledonian-mercury-20-june-1825/)

## Requirements

This programme requires 

+ [Visual C++ Redistributable for Visual Studio 2015](https://www.microsoft.com/en-gb/download/details.aspx?id=48145)
+ [Python 3](https://www.python.org/downloads/)

## Use

To use the Newspaper Dissector, place the executable file (NewspaperDissector.ext) in a directory/folder with one or more tab-seperated (.tsv) data files. The files should have no headers and include only the raw data.

**Each row should include the following fields:**

+ Year
+ Month
+ Day
+ Title
+ Page number (front to back)
+ Column number (left to right)
+ Snippet number (top to bottom)
+ Type (advert, commentary, miscellany, news, numerical)
+ Topic (open-ended)
+ Action Location (open-ended)
+ Source Location (open-ended)
+ Source Type (l, a, t, c, u)
  + l = location
  + a = ambiguous publication 
  + t = named publication
  + c = correspondence
  + u = undetermined
+ Source Location Type (l, r, n, i, u)
  + l = local
  + r = regional
  + n = national
  + i = international / colonial
  + u = undetermined
+ Text

**An example line of the file is as follows:**

    1820	6	15	Caledonian Mercury	1	1	1	Advert	Meeting	Dumfries	Dumfries	l	r	"Sample Text"
    1820	6	15	Caledonian Mercury	1	1	2	Advert	Loan/Borrow	NA	Edinburgh	l	l	"Sample Text"
    1820	6	15	Caledonian Mercury	1	1	3	Advert	Loan/Borrow	NA	Edinburgh	l	l	"Sample Text"
    1820	6	15	Caledonian Mercury	1	1	4	Advert	Loan/Borrow	NA	Tain	l	r	"Sample Text"

Please report any errors or exceptions to the author, [M. H. Beals](m.h.beals@lboro.ac.uk)

## Changelog

**v.0.2.2.0**: Fixed fatal error in compiled version