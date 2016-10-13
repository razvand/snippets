The lab repository stores support files to be used during the Operating
Systems Internals (SO2) lab.

== Structure ==

Each lab uses a separate folder: lab01, lab02, lab03.

There are three subfoldes in each lab folder:
  * skel/: for task skeleton code
  * sol/: for task solutions (to be used internally and published
          _after_ the lab has taken place
  * slides/: for slides

Slides are not usually used. But if we want to toy around with them
check the README.slides file.

== Adding Support Files ==

When adding a new skeleton, create a folder within the skel/ subfolder
with a name starting with the task index: 1-intro/, 2-minfs/,
3-jiffies/, 4-5-read-ops/ (for two tasks using the same skeleton). If
required, create a top level util/ folder storing utility files that are
not specific to a given task.

For each task use a Kbuild file, a Makefile file and the source code
file(s) required for the task.

The same file tree structure should be part of the sol/ subfolder.

We recommend solving the task in its respective subfolder in the sol/
subfolder and then copying the files in the respective subfolder in the
skel/ subfolder. Then edit the source code file(s), remove the parts
that are to be filled by students and replace them with TODO comments,
such as:

/* TODO: Initialize file system structure and register it. */

When building the task statements on the wiki, mention a phrase such as:
"Fill the parts marked with TODO comments".

== Publishing Support Files ==

In order to publish support files we use the top-level scripts in the
repository. Assuming we want to publish support files for lab02, we
would use the following commands:
./make-clean 2
./publish-tasks 2
./publish-slides 2

We clean the lab skeleton/solution folder, then publish the lab skeleton
archive and then build and publish the lab slides.

The running of the ./publish-slides script is optional, as we are not
using slides.

If the lab has taken place and we want to publish solutions, we use the
command:
./publish-sol 2

If we did a mistake and the solution shouldn't have been published we
can revert the publishing of the solution by using:
./unpublish-sol 2

Any of those scripts can be run with no arguments in which case all labs
will be gone through (clean all of them, publish all skeleton code for
all of them, etc.)
