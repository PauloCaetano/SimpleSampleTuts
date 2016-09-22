SimpleSampleTuts
================

Simple code samples/concepts and tutorials, in C++.

Contains the following samples/tutorials:
* ProjectConfig

 An utility to share a common structure for Qt Creator/MSVC projects.
 Each tool has its own project directory, but share the same source code.
 Uses Boost and code from the [bluesy](https://github.com/PauloCaetano/bluesy) repository.
 
* Logger

 A solution for implementing logging in a library. See posts [here](http://cidebycide.blogspot.pt/2013/05/logger-wrapper-revisited.html).
 Uses POCO C++'s classes, but these can be easily removed. Includes project files for MSVC and Qt Creator.

* Macro Logger

 Another shot at implementing logging in a library. See posts [here](http://cidebycide.blogspot.pt/2014/05/logger-abstraction-poc.html).
 This time, everything is "done with macros".
 
* Qt\LayoutTutorial

 Files for the three-part Qt layout tutorial [here](http://cidebycide.blogspot.pt/2013/04/qt-layout-tutorial-part-i.html).
 
* Qt\MSVCIDERules

 MSBuild .targets files with rules for working with Qt in the MSVC Express IDE. See post [here](http://cidebycide.blogspot.com/2013/04/developing-with-qt-on-msvc-express-ide.html).

* SSHExec

 A basic example using the mix of libssh2/boost asio I did a couple of years ago. It needs a
 design change, but my time has been invested elsewhere. I haven't abandoned it, and I know
 what are the next steps - minimize build times, by redesigning the headers; and use a single
 io_service, by relying on the "shared pointer in message queue" idiom, which will ensure
 there will be no calls on already-destroyed objects.
 
 Still, for the basic use-case in this example (running some commands on a remote host and
 exiting), it has worked flawlessly, so far. OTOH, it has never been used on anything critical,
 so, test it first. Test thoroughly, test often.
