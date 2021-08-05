KamiClone v0.2.0:
  Great changes in code base compared to v0.1.0:
    - Removed specific layer calls on OnUserUpdate
    - Removed old layer management
    + Generalized layer calls based on scene vector
    + Stack-based layer management so that only the rightmost (newest) layer gets rendered, this means any layer left of (older than) it will be disabled until it is popped from the vector
    + Further encapsulation of variables and functions
    + Improved performance by reducing redundancy of drawing routines
    + Replaced "includes.h" with self-contained includes with guards
    + Adoption of Google's cpp style guide (for the most part)
KamiClone v0.1.0:
  Minimal game playing functions added:
    + Added two layers: menuLayer for the level select, gameLayer for the game playing
    + Square painting function added
    + Five levels added
    + Tkinter-like Button class added
    + Triangle drawing methods added for each cardinal direction (unused)
    + AI-like hint solving system added (unused)
