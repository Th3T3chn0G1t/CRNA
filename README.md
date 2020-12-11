![CRNA Logo ROW](LogoROW.png)

[![Documentation](https://img.shields.io/badge/api-reference-blue.svg)](https://th3t3chn0g1t.github.io/CRNA/index.html)
[![Build Status](https://api.travis-ci.com/Th3T3chn0G1t/CRNA.svg)](https://api.travis-ci.com/Th3T3chn0G1t/CRNA)

[![GPLV3LOGO](https://www.gnu.org/graphics/gplv3-or-later.png)](https://www.gnu.org/licenses/gpl-3.0.txt)

**NB. CRNA is currently being developed for and on Unix based systems and does not officially support Windows. Keep this in mind for contributions**

CRNA is a game engine written in the C programming language using libSDL2 for rendering and input. It provides high level processes for managing a visual application and its facets. You can use CRNA to develop games and production-ready applications.

A template project can be generated using ```scripts/generateApplicationTemplate.sh```

CRNA as of the time of writing has the following features:
- Registry based scene management
- Automatic sprite rendering with the option for overrides
- Hooks for extending application start, update and destroy functions
- Full documentation of all functions
- Templating of scene components and crna applications

A tutorial for creating a basic project can be found [here](https://th3t3chn0g1t.github.io/CRNA/md_res_docs_tutorial_welcome.html)

## Installation

To download the project, just download the latest release or clone the directory (might be broken!)

There is no other installation required to start developing with CRNA apart from a few dependencies that need to be resolved. These can be installed using ```make get-deps```

## Documentation
Every part of every header contains documentation for its purpose and how to use it - you can either access this information directly or you can use Doxygen to generate docs (See the Doxyfile for more information)

The html documentation for the latest build is available [here](https://th3t3chn0g1t.github.io/CRNA/)

The Makefile is self documenting and can be accessed by running ```make help``` and the scripts folder will usually provide usage information when run without arguments - but scripts aren't requried to document themselves short of justifying their existence

## Config
There are a few build and execution settings that can be controlled by ini files in the ```.crna``` directory and all keys have ### documentation

Build settings for controlling the Makefile can be found here ```.crna/build_settings.ini```
Execution settings for controlling the program startup can be found here ```.crna/game_settings.ini```

## TODO
- **Write tests**
- Seperate physics from gameobject 
- Hardware Acceleration with all SDL APIs
- 3D
- Proper gameobject scripting
- Find good bug tracker
- GUI/Scene editor
- Sound
