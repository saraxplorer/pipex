# Concepts for Bonus
**What if we do not want to use a separate input file and just write right from the command line?**
The solution to this is a *here_doc* with a limiter. This is how it looks like
```
#!/bin/bash

# Define a LIMITER
LIMITER="END_MARKER"

# Here document with executable
./executable << $LIMITER
This is line 1
This is line 2
This is line 3
$LIMITER
```
So end marker is acting like a paranthesis for the texts we want to use as input. 
