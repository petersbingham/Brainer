# Brainer

This is a little app that I put together early in my career to demonstrate use of runtime dependencies and different IDEs. Sorta based around the brain games that were popular at that time with addition of trivia questions. I sometimes add puzzles and trivia that I encounter and find interesting.

## Development Setup

### Main Application

 * Install Visual Studio 2017
 	* If build errors complaining about missing standard header files, goto: Project Properties --> Configuration Properties --> Windows SDK Version --> set to 10.x.x
 * Install the vb_vbpowerpacks.exe
 
### Dlls

 * Borland BDS2006 Turbo and HotFixRollup2
 * Dependencies of the above may or may not be required (untested):
 	* Microsoft .NET Framework v1.1 Redistributable
 	* Microsoft .NET Framework v1.1 SP1
 	* Microsoft .NET SDK v1.1
 	* Microsoft Internet Explorer 6 SP1
 	* Microsoft Visual J# v1.1 Redistributable
 	* Microsoft XML Core Services (MSXML) v4.0 SP2

## Runtime Setup
  
 * VS 2017 runtimes
 * cc3270mt.dll is a Borland runtime dependency obtained from installation of Borland Turbo Express. A copy is included in the binary directory .\Brainer\Game
 * The dll dependencies listed above may or may not be required (untested)
