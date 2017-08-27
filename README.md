# 21sh

OSX Status: ![Build Status](https://travis-ci.org/m600x/minishell.svg?branch=master)

As the name suggest, this project aim to produce a functional miniature version of a shell like bash, zsh and so on.  
***The project must not leak in any manner. Memory management is crucial.***

Authorized functions are restricted to these for the core functions:
 - *malloc, free*
 - *access*
 - *open, close, read, write*
 - *opendir, readdir, closedir*
 - *getcwd, chdir*
 - *stat, lstat, fstat*
 - *fork, execve*
 - *wait, waitpid, wait3, wait4*
 - *signal, kill*
 - *exit*

<p align="center">CORE FUNCTIONS STATUS</p>

|Functions|Implemented|Leaks|Arguments|Comments
|:-:|:-:|:-:|:-:|:--
|exit|Done|No|[exit]<br>[exit 42]|Exit minishell<br>Exit with code 42
|cd|Done|No|[cd]<br>[cd -]<br>[cd folder]<br>[cd .././folder]<br>[cd ~/folder]|Return to the home folder<br>Go to previous folder<br>Go to folder from current<br>Complex dots solved<br>Retrieve home path
|pwd|Done|No|[pwd]|Give the current directory
|echo|Done|No|[echo foo]<br>[echo "foo"]<br>[echo $var]|Echo standard<br>Echo foo as it's writed<br>Echo the var from env
|env|Done|No|[env -i]<br>[env -u var]<br>[env -v]|Empty the env<br>Unset a var<br>Verbose mode
|setenv|Done|No|[setenv foo=bar]|Add the var to the env
|unsetenv|Done|No|[unsetenv foo]|Remove the var from env
|fork()|Done|No|-|

<p align="center">EXTRA FEATURE</p>

|Functions|Status|Comments
|:--|:-:|:--
|Edition|Done|Command line edition (Arrows, Del, Return, Home and End)
|Move per word|Done|Move per word through the command with Alt+Left or Alt+Right
|Commands history|Done|Put back the previously executed commands
|Chain commands with ;|Done|Chained as [cd ; ls ; cd / ; ls -l]
|Autocompletion|Done|Browse the folder in the command and display the selection
|Execution rights in path|Done|Check if the file is a binary and if the user can access it
|Tilde support|Done|Solve a path input in the command with tilde or dots support
|2 SIGINT (Ctrl + C)<br>3 SIGQUIT (Ctrl + D)<br>18 SIGTSTP (Ctrl + Z)<br>19 SIGCONT (fg)<br>28 SIGWINCH (Win resize)|Done<br>Done<br>Done<br>Done<br>Done|Interrupt minishell<br>Quit minishell after cleaning the memory<br>Pause minishell and put it in the background<br>Resume minishell and put it in the foreground<br>Retrieve the new window size upon resizing
