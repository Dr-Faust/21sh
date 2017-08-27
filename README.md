# 21sh

**Caution! This project fully works on MacOS only. There is no garanty that it will work correctly on any other UNIX/Linux system.**

Extended version of minishell.
***The project must not leak in any manner. Memory management is crucial.***

Within the mandatory part, we were allowed to use only the following libc functions:
 - *malloc, free*
 - *access*
 - *open, close, read, write*
 - *opendir, readdir, closedir*
 - *getcwd, chdir*
 - *stat, lstat, fstat*
 - *fork, execve*
 - *wait, waitpid, wait3, wait4*
 - *signal, sigaction, kill*
 - *exit*
 - *pipe*
 - *dup, dup2*
 - *isatty, ttyname, ttyslot*
 - *ioctl*
 - *getenv*
 - *tcsetattr, tcgetattr*
 - *tgetent, tgetflag, tgetnum, tgetstr, tgoto, tpurs*

## Built in functions

|Function|Implemented|Arguments|Comments
|:-:|:-:|:-:|:--
|exit|Done|[exit]|Exit minishell
|cd|Done|[cd], [cd ~]<br>[cd -]<br>[cd folder]<br>[cd .././folder]<br>[cd ~/folder]|Return to the home folder<br>Go to previous folder<br>Go to folder from current<br>Complex dots solved<br>Retrieve home path
|pwd|Done|[pwd]|Give the current directory path
|echo|Done|[echo foo]<br>[echo "foo"]<br>[echo $var]|Echo standard<br>Echo foo as it's writed<br>Echo the var from env
|env|Done|[env]|Shows environment info
|setenv|Done|[setenv foo bar]|Add the var to the env
|unsetenv|Done|[unsetenv foo]|Remove the var from env

## Line Editing

Key|Comments|
:-:|:--
<kbd>Cmd</kbd>+<kbd>C</kbd><br><kbd>Cmd</kbd>+<kbd>X</kbd><br><kbd>Cmd</kbd>+<kbd>V</kbd>|Copy<br>Cut<br>Paste
<kbd><</kbd><br><kbd>></kbd>|Move the cursor left / right one character.
<kbd>Alt</kbd>+<kbd><</kbd><br><kbd>Alt</kbd>+<kbd>></kbd>|Move the cursor per words.
<kbd>Alt</kbd>+<kbd>^</kbd><br><kbd>Alt</kbd>+<kbd>v</kbd>|Move the currsor per line.
<kbd>Home</kbd><br><kbd>End</kbd>|Move the cursor to the beginning / end of a line.

## Signals management

|Signal|Key|Comments
|:-:|:-:|:--
|SIGINT|<kbd>Ctrl</kbd>+<kbd>C</kbd>|Interrupt 21sh
|SIGQUIT|<kbd>Ctrl</kbd>+<kbd>D</kbd>|Quit 21sh after cleaning the memory
|SIGTSTP|<kbd>Ctrl</kbd>+<kbd>Z</kbd>|Pauses process running in 21sh and puts it in the background
|SIGCONT|[fg]|Resumes suspended process and puts it in the foreground
|SIGWINCH|win resize|Retrieve the new window size upon resizing
