# DFSM-simulator
Deterministic finite state machine (or DFSM) are finite state machines that accept or reject strings of characters by parsing them through a sequence that is uniquely determined by each string. The term “deterministic” refers to the fact that each string, and thus each state sequence, is unique.
Some DFSM uses include protocol analysis, text parsing, video game character behavior, security analysis, CPU control units, natural language processing, and speech recognition

For this project I implemented a DFSM simulator in C++ that reads a deterministic finite state machine defined in a file and a user input considered as the language to be analyzed. It parses the language to check if it can be accepted or rejected. 

Format of the DFSM file:
First row is alphabet separated by comma
Second row is the number of states of the DFSM, implicitly the states are 0,1, 2.. where 0 is the initial state
Third row is the accepting states: one or more separated by comma.
The remaining rows are the function, one or more rows for each state

a, b
3
0,1
(0,a,1)
(0,b,0)
(1,a,2)
(1,b,0)
(2,a, 2)
(2, b, 2)

![image](https://user-images.githubusercontent.com/92817993/196299515-de9d60fd-ca3a-48c0-bd1d-59f8ec03e00a.png)
