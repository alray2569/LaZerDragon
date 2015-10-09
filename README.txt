LaZerDragon - Project 3
Andrew Ray (alray)
Gareth Solbeck (grsolbeck)
IMGD 3000

Build platform: OS X (Yosemite 10.10.5)

Note: this game has also been compiled on Windows in Visual Studio, but the
VS-specific files are not included in our shared codebase, so submitting the
OS X build is much more straightforward. We can provide a Virtual Studio
compatible build upon request.

Structure:
    bin/        (game executable)
    build/      (game .o files)
    sprites/    (game sprites)
    src/        (game engine .h and .cpp files)
    df-font.ttf (font asset)
    Makefile    (for compiling on OS X systems)
    README.txt

Compiling:
    When testing, the Makefile assumes that SFML has been installed using
    Homebrew. If this is not the case, you can either:
     a) Install SFML using Homebrew (brew install sfml).
     b) Modify the Makefile. Change the second argument of the INCLUDE line to
        point to the location of your SFML headers.

    To compile the game, run:
    $ make
    The game executable will be saved in bin/game

Running:
    To run the game, use the following command after compiling:
    $ ./bin/game

Playing:
    The goal of the level is to send each laser to the matching receiver.
    Left click an empty space to place a mirror.
    Left click a mirror to rotate it.
    Right click a mirror to remove it.
    You have a limited number of mirrors (shown at the bottom).
    Once you complete the level, the game will automatically exit.

Implementation:
    - Mouse control has been implemented: place, rotate, and remove components
    - The color class (LaserColor) has been written, including various
      combination operators
        - The + operator combines colors
            - Useful for the Joiner component
        - The - operator subtracts any colors that exist in both arguments
        - The * operator returns the common color (e.g: MAGENTA * YELLOW = RED)
            - Useful for the Splitter component
    - Laser movement and reflection is complete
        - Reflection is handled by the Mirror component
        - Combination and splitting will be handled by the joiner/splitter
    - Component display shows the number of components available to place

To be completed:
    - Joiner/Splitter components
        - like Mirror, these will be simple extensions of the Component class
    - Selecting the active component by clicking its display
        - only relevant once more components exist
    - Level selection & menu
    - Sound assets

If you are unable to compile or run the project for any reason, please email us
and we'll do our best to help troubleshoot.
