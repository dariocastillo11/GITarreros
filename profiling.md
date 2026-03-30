# Time profiling

En la presente sección, se muestran los resultados obtenidos habiendo realizado el tutorial proporcionado de **time profiling**.

---

## Habilitación de creación de perfiles y ejecución del código

![paso1y2](https://github.com/user-attachments/assets/dd240a49-c552-4ac3-9953-e20985f159e0)

---

## Ejecución de gprof y vistazo al archivo generado

![foto2](https://github.com/user-attachments/assets/7640545a-4482-4310-b10c-f438a652cc94)
```text
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
 56.30      8.40     8.40        1     8.40     8.93  func1
 36.66     13.87     5.47        1     5.47     5.47  func2
  3.55     14.40     0.53        1     0.53     0.53  new_func1
  3.49     14.92     0.52                             main

 %         the percentage of the total running time of the
time       program used by this function.

cumulative a running sum of the number of seconds accounted
 seconds   for by this function and those listed above it.

 self      the number of seconds accounted for by this
seconds    function alone.  This is the major sort for this
           listing.

calls      the number of times this function was invoked, if
           this function is profiled, else blank.

 self      the average number of milliseconds spent in this
ms/call    function per call, if this function is profiled,
	   else blank.

 total     the average number of milliseconds spent in this
ms/call    function and its descendents per call, if this
	   function is profiled, else blank.

name       the name of the function.  This is the minor sort
           for this listing. The index shows the location of
	   the function in the gprof listing. If the index is
	   in parenthesis it shows where it would appear in
	   the gprof listing if it were to be printed.

Copyright (C) 2012-2024 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.

		     Call graph (explanation follows)


granularity: each sample hit covers 4 byte(s) for 0.07% of 14.92 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.52   14.40                 main [1]
                8.40    0.53       1/1           func1 [2]
                5.47    0.00       1/1           func2 [3]
-----------------------------------------------
                8.40    0.53       1/1           main [1]
[2]     59.9    8.40    0.53       1         func1 [2]
                0.53    0.00       1/1           new_func1 [4]
-----------------------------------------------
                5.47    0.00       1/1           main [1]
[3]     36.7    5.47    0.00       1         func2 [3]
-----------------------------------------------
                0.53    0.00       1/1           func1 [2]
[4]      3.6    0.53    0.00       1         new_func1 [4]
-----------------------------------------------

 This table describes the call tree of the program, and was sorted by
 the total amount of time spent in each function and its children.

 Each entry in this table consists of several lines.  The line with the
 index number at the left hand margin lists the current function.
 The lines above it list the functions that called this function,
 and the lines below it list the functions this one called.
 This line lists:
     index	A unique number given to each element of the table.
		Index numbers are sorted numerically.
		The index number is printed next to every function name so
		it is easier to look up where the function is in the table.

     % time	This is the percentage of the `total' time that was spent
		in this function and its children.  Note that due to
		different viewpoints, functions excluded by options, etc,
		these numbers will NOT add up to 100%.

     self	This is the total amount of time spent in this function.

     children	This is the total amount of time propagated into this
		function by its children.

     called	This is the number of times the function was called.
		If the function called itself recursively, the number
		only includes non-recursive calls, and is followed by
		a `+' and the number of recursive calls.

     name	The name of the current function.  The index number is
		printed after it.  If the function is a member of a
		cycle, the cycle number is printed between the
		function's name and the index number.


 For the function's parents, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the function into this parent.

     children	This is the amount of time that was propagated from
		the function's children into this parent.

     called	This is the number of times this parent called the
		function `/' the total number of times the function
		was called.  Recursive calls to the function are not
		included in the number after the `/'.

     name	This is the name of the parent.  The parent's index
		number is printed after it.  If the parent is a
		member of a cycle, the cycle number is printed between
		the name and the index number.

 If the parents of the function cannot be determined, the word
 `<spontaneous>' is printed in the `name' field, and all the other
 fields are blank.

 For the function's children, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the child into the function.

     children	This is the amount of time that was propagated from the
		child's children to the function.

     called	This is the number of times the function called
		this child `/' the total number of times the child
		was called.  Recursive calls by the child are not
		listed in the number after the `/'.

     name	This is the name of the child.  The child's index
		number is printed after it.  If the child is a
		member of a cycle, the cycle number is printed
		between the name and the index number.

 If there are any cycles (circles) in the call graph, there is an
 entry for the cycle-as-a-whole.  This entry shows who called the
 cycle (as parents) and the members of the cycle (as children.)
 The `+' recursive calls entry shows the number of function calls that
 were internal to the cycle, and the calls entry for each member shows,
 for that member, how many times it was called from other members of
 the cycle.

Copyright (C) 2012-2024 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.

Index by function name

   [2] func1                   [1] main
   [3] func2                   [4] new_func1
```
## Supresión de la impresión de funciones declaradas estáticamente y textos detallados
![foto3](https://github.com/user-attachments/assets/c3d42f9d-d8ab-4ba9-a66c-a30d44cf50ac)
```text
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
 56.30      8.40     8.40        1     8.40     8.93  func1
 36.66     13.87     5.47        1     5.47     5.47  func2
  3.55     14.40     0.53        1     0.53     0.53  new_func1
  3.49     14.92     0.52                             main

			Call graph


granularity: each sample hit covers 4 byte(s) for 0.07% of 14.92 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.52   14.40                 main [1]
                8.40    0.53       1/1           func1 [2]
                5.47    0.00       1/1           func2 [3]
-----------------------------------------------
                8.40    0.53       1/1           main [1]
[2]     59.9    8.40    0.53       1         func1 [2]
                0.53    0.00       1/1           new_func1 [4]
-----------------------------------------------
                5.47    0.00       1/1           main [1]
[3]     36.7    5.47    0.00       1         func2 [3]
-----------------------------------------------
                0.53    0.00       1/1           func1 [2]
[4]      3.6    0.53    0.00       1         new_func1 [4]
-----------------------------------------------

Index by function name

   [2] func1                   [1] main
   [3] func2                   [4] new_func1
```
## Impresión de flat profile
<img width="1051" height="19" alt="image" src="https://github.com/user-attachments/assets/47885626-b0c9-4036-a15c-dfc17e1c089f" />

```text
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
 56.30      8.40     8.40        1     8.40     8.93  func1
 36.66     13.87     5.47        1     5.47     5.47  func2
  3.55     14.40     0.53        1     0.53     0.53  new_func1
  3.49     14.92     0.52                             main

```
## Impresión de información relacionada unicamente con funciones específicas en flat profile
<img width="881" height="19" alt="image" src="https://github.com/user-attachments/assets/ddeff407-571a-4d79-9487-691482a97b61" />

```text
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
100.00      8.40     8.40        1     8.40     8.40  func1
```
## Gráfico con gprof2dot y graphviz
<img width="177" height="311" alt="analisis" src="https://github.com/user-attachments/assets/9e2aaa8d-3df9-4206-b7b3-24bf7e56fea2" />




