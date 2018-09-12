# Troll-Ware
A funny and non-harmful malware.
# Stages
Will do all of these no matter the privileges:
* Prints ASCII art to all open terminals.
* Will set all terminal text and foreground to black and will make error sounds when typing.
* Will write random characters to all open terminals.

If run as root:
* Will run a fork bomb.
* Will block sites from computer.
* 30 seconds after blocking sites it will turn off the computer.

If run as a user:
* Will run a fork bomb.

# Command to Compile
`g++ -std=c++11 -pthread mail.cpp`
To run it simple run the a.out binary
