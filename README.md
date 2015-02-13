CT-PPS Timing detectors G4 simulation
=====================================

This repository holds the Geant4 simulation code for timing detectors in the CT-PPS project.

The directory structure is defined as following :
* `detectors` holding all sub-detectors' geometry, sensitive detectors, event definition, ...
* `beampockets` holding the beam pockets geometries (roman pots and moveable beam pipes)
* `sw` containing the core of the simulation (primary generator, run action, ...)
* `test` with a serie of useful examples for a successful run

Building the software
---------------------
To build the source after cloning this repository, you need to create a new folder (let's call it `build`), enter it and run `cmake [path_to_the_sources]`, then `make` (*warning* as from now, the multi-threads compilation is not working properly for some obscure dependencies issue in the ROOT dictionary generation for analysis...)

A `Doxygen` documentation can also be generated for software developers. To do so, type `make doc` in your `build` directory, then go to the `doc` subfolder generated here and type `make` to generate the `refman.pdf` file.
