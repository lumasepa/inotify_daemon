Inotify Daemon 
=================

Daemon that watch a directory with the inotify library


This package contains the source code for Inotify Daemon
-------------------------------------------------------

# Step 1 - Build process
------------------------

Run in the root of the project
> cmake .

> make

# Step 2 - Execution
---------------------
 
To execute the daemon  
 -p | --path directory to listen  
 -d | --daemon starts as a daemon  
 -h | --help | -? Shows the help  

> ./inotify_daemon -p /tmp -d 

