# a4tasks

[![Build Status](https://travis-ci.com/nklapste/a4tasks.svg?branch=master)](https://travis-ci.com/nklapste/a4tasks)

## Description
a4tasks is a C++ program that utilizes `pthreads` to simulate the concurrent 
execution of a set of tasks. The system has a number of resource types, and 
each resource type has a number of available units. All resource units in the
system are non-sharable non-preemptable resources.

## Compiling 
a4tasks uses c++17 it can be compiled using either `cmake` or `make`.

To compile a4tasks with make run:
```bash
make
```

## Usage
After compiling the `a4tasks` binary it can be invoked using the command line:
```bash
./a4tasks inputFile monitorTime NITER
```

Where the following arguments are defined as:

`inputFile`: input file describing the tasks to be executed. 
    (input file specification noted below)

`monitorTime`: integer (in milliseconds) that specifies how often a monitor
    thread runs.

`NITER`: integer noting the amount of iterations each task executes 
    before the simulator finishes.
    
### Input File
a4tasks reads the system parameters from an input file specified by the
`inputFile` argument. The file has a number of lines formatted as follows:

A line can be empty

A Line that starts with a `#` is a comment line

A line of the form:
```text
resources name1:value1 name2:value2 ...
```
specifies the resource types available in the system. The line starts with 
the keyword `resources`, followed by one, or more, `name:value` pairs of a
resource type name, and the number of available units of this resource type, 
respectively.

A line of the form:
```text
task taskName busyTime idleTime name1:value1 name2:value2 ...
```
specifies a task in the system. The line has the following fields:

`task`: a keyword that specifies a task line

`taskName`: the task’s name

`busyTime`: an integer specifying the real time (in milliseconds) spent by the 
    task when executing

`idleTime`: an integer specifying the real time (in milliseconds) spent by the
    task after finishing execution and before it can be executed again

`name:value`: specifies the name of a resource type, and the number of
    units of this resource type needed for the task to execute

#### Notes
A simulation made by a4tasks may have up to `NRES TYPES = 10` resource types, 
and `TASKS = 25` tasks. Each string (a task or a resource type name) has at
most 32 characters. Each white space between fields is composed of one, or
more, space character(s). There is no white space around the `:` field separator.

#### Example Input File
The following input file corresponds to an instance of the Dining Philosophers
Problem with 5 people, denoted `t1` to `t5`. The five chopsticks correspond to
five resource types, denoted `A` to `E`. Each philosopher (task) spends
50 milliseconds eating, followed by 100 milliseconds thinking, before getting
hungry again.

```text
# An instance of the Dining Philosophers Problem with 5 people
#
resources  A:1 B:1 C:1 D:1 E:1
task       t1 50 100  A:1 B:1
task       t2 50 100  B:1 C:1
task       t3 50 100  C:1 D:1
task       t4 50 100  D:1 E:1
task       t5 50 100  E:1 A:1
```
