### Install latest bison first

#### Compile commands
lex while.l
yacc while.y
gcc y.tab.c -ll -ly

#### Input
Put expression in the following format only : **`while(`**`expression`**`)`**`expression`**`;`**

For eg:
expression : `while(k=c/s)k=a*d+c/10;`

