# 'Calpage' documantation
### Content:
1. [Input data, input formats](#p1);
2. [Output data, output style's settings](#p2);
3. [Secondary flags](#p3).

<h3 id='p1'>1. Input data, input formats</h3>

The general type of usage of **Calpage** is as follows:
```
calpage ~acceptable_input_format~
```
**Acceptable month and year input formats are:**
- ```MM YYYY```;
- ```YYYY MM```;

```MM``` must be number of month from 1 to 12 (1 - January, 12 - December). If the month number is less than 10, for example 5, then it can be entered both as ```05``` and as ```5```.

```YYYY``` must be number of year from 1900 to 9999 inclusive.

To make the program **automatically read the current month and year** you can use it as follows:
```
calpage today
```
<h3 id='p2'>2. Output data, output style's settings</h3>

**Calpage** displays calendar page as a table, where _rows are weeks_ and _columns are days of week_.

**Examle**:

Input:
```
calpage 01 2025
```
Output:
```
SU MO TU WE TH FR SA
          1  2  3  4
 5  6  7  8  9 10 11
12 13 14 15 16 17 18
19 20 21 22 23 24 25
26 27 28 29 30 31
```
By default, **Russian-style** of calendar page is used. To change it, following commands can be used:

- ```calpage ru``` - transition to **Russian-style** (week starts from _Monday_);
- ```calpage en``` - transition to **English-style** (week starts from _Sunday_).

If input data format is unacceptable, **Calpage** will crash **with error code 52**, displaying the corresponding message in the console.
<h3 id='p3'>3. Secondary flags</h3>

Using the ```-v``` or ```--version``` flags, you can get information about the current version of the program and its author.

Using the ```-h``` or ```--help``` flags, you can get help about usage of **Calpage**.
