bitfighter-experiments
======================

Basically bitfighter is awesome and I want to help make it awesomer

the changes
===========
Like most programmers, I hate the idea of changing a code base, especially one I'm familiar with.  As much as it has pained me, I've changed a lot of the source code in bitfighter to be more minimalistic and extendible in the future.  Many of the classes have been destroyed, or merged into more abstract classes, as an example.

I took a few liberties in converting the code, and have been using some fundamental ideas in how things get implemented, which in some cases is different from the original bitfighter.
  * Rather than events having threads, the application has n threads, and distributes events between these
  * Much of the game relied on gridDB, which handled the physics, this has changed to chipmunk physics, not only because slembcke (the author of chipmunk) is awesome, but because it opens up a bunch of possibilities for new and exciting game mechanics.
  * I've taken many more liberties about using exceptions, because not only do they notify the program of an error, but they also encapsulate what the error was.
  * I'm quite torn still over whether or not to keep Lua, or replace it with GameMonkey...more on this later

todo
====
  * Finish this doc
  * Write an API/programmers guide
  * Encourage more opensource silliness :)
  * Get the first working compile out

contact
=======
I'd post my website on here, but it's not functional right now (changed from third-party server to now hosting locally, and in progress of working on a ruby on rails version of the site).
For now, you can contact me through my gmail address, alex.barry