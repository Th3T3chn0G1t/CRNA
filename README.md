![CRNA Logo](LogoROW.png)

[![Documentation](https://img.shields.io/badge/api-reference-blue.svg)](https://th3t3chn0g1t.github.io/CRNA/index.html)
[![Build Status](https://api.travis-ci.com/Th3T3chn0G1t/CRNA.svg)](https://api.travis-ci.com/Th3T3chn0G1t/CRNA)

[![GPLV3LOGO](https://www.gnu.org/graphics/gplv3-or-later.png)](LICENCE)

**NB. CRNA is currently being developed for and on Unix based systems and does not officially support Windows. Keep this in mind for contributions**

CRNA is a game engine written in the C programming language using libSDL2 for rendering and input. It provides high level processes for managing a visual application and its facets. You can use CRNA to develop games and production-ready applications.

A template project can be generated using ```scripts/generateApplicationTemplate.sh```

CRNA as of the time of writing has the following features:
    - Registry based scene management
    - Automatic sprite rendering with the option for overrides
    - Hooks for extending application start, update and destroy functions
    - Full documentation of all functions
    - Templating of scene components and crna applications

A tutorial for creating a basic project can be found [here](https://th3t3chn0g1t.github.io/CRNA/md_res_docs_tutorial_tutorial_welcome.html)

Project General TODO:
    - Readme
    - Roadmap
    - Find good bug tracker

CRNA TODO: 
    - **Write tests**
    - Hardware Acceleration with all SDL APIs
    - Sound
    - GUI
    - Scene editor
    - Proper camera interface instead of contexts
    - Seperate physics from gameobject 
    - Proper gameobject scripting
    - 3D Maybe?
