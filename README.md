# OOP-Piano-Project
Final Project for OOP course

(details)


Game Introduction
Piano Ustaad is a rhythm-based memory game where players must press the correct piano keys (using keyboard or mouse) in time with the displayed sequence. It can be played infinitely many times. The game tracks your score, accuracy, and max combo, and time taken for correct and incorrect notes to help players improve their timing and memory.


Requires:
- SFML (preferably 2.5 or above)
- C++17 compatible compiler (g++, MinGW, Clang, MSVC etc.)

How to compile, use this command:
//g++ src/*.cpp src/screens/*.cpp src/core/*.cpp src/piano/*.cpp ^-I./src -I./src/screens -I./src/core -I./src/piano ^-o PianoGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

How to run: 
.\PianoGame

Resources:
They should be present in the zip file, but just in case, there are code lines such as this:     
//font.loadFromFile("src/resources/fonts/ARIAL.TTF");
meaning the correct heirarchy of the folders is that there should be a resources folder inside src folder. resources folder consists of /fonts and /sounds. /sounds contains all note files A.wav, B.wav, Asharp.wav, Bsharp.wav etc.
If you see "failed to load sound" or "failed to load font",
make sure the resources/ folder is placed in the same directory as the executable.

Controls:
Keys of keyboard mapping to piano : A(C) W(Csharp) S(D) E(Dsharp) D(E) F(F) T(Fsharp) G(G) Y(Gsharp) H(A) U(Asharp) J(B)

Developers:
- Aiman Asim Zubedi
- Ghos Usmani
- Fouzail Ahmed

