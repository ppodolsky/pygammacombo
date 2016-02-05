# Python wrapper for GammaCombo

## Requirements (tested on)

* Root 5.34.32+
* OS X or Ubuntu 15.10+
* Python 3.3+
* Gammacombo sources

## Preparation

Nb.: Change _brew_ to your package manager (_apt-get_ for Ubuntu)

* brew install root
* brew install python3
* pip3 install megazord pybindgen

## Installation

### Compile gammacombo
You can (actually now you can't) assembly gammacombo manually, take libgammacomboCoreComponents.so and put it
to _pygammacombo/_  OR assembly it by _python3 compile-gammacombo.mz.py_.

__Now it requires modification of gammacombo source codes.__
Look at proposed pull requests to the upstream to know the state of the issue.

* Put gammacombo sources (both public and private) into gammacombo folder.
* Put ExpNll into ExpNll folder
* Regenerate dictionaries by _python3 prepare-dict.py_
* Compile by _python3 compile-gammacombo.mz.py_

### Compile pygammacombo

* Compile by _python3 compile-pygammacombo.mz.py_

## Quick start

_ToDo: :)_
As a result, you will get PyGammaCombo.so (and soft link libPyGammaCombo.so) which can be imported in
python script via import: _import PyGammaCombo_
For example of usage you can look at https://github.com/PashaPodolsky/PyBayCor
